#include "gameserver.h"
#include "md5.h"
#include "console.h"
#include "netstructs.h"

#define MAKE_MSG(x,_y,z);    x _y;_y.type=z;

void cGameServer::doDeath(int id)
{
	//printf("%d(%s) type %d died to %d(%s) type %d\n",id,player[id].name,player[id].type,player[id].target,player[player[id].target].name,player[player[id].target].type);
	//run death script
	
	mlscript.run(1005,id);

	if(player[id].hp > 0)//script revived player
		return;
	
	//announce death and assign experience
	if(player[id].type==PLAYER)
	{
		//exp loss
		
		player[id].exp = unsigned long( float(player[id].exp) * 0.666f);
		
		sendEXPMsg(id);
	}
	if(player[id].type==NPC && player[player[id].target].type==PLAYER && player[player[id].target].lvl<255)
	{
		
		player[player[id].target].exp+=player[id].worth;//+expBonus(player[player[id].target].wis,player[player[id].target].lvl);
		
		sendEXPMsg(player[id].target);
	}
	//set this spot to vacant
	
	world[player[id].map].map[player[id].y][player[id].x].space=VACANT;
	
	//do loot drop
	if(player[id].type==NPC && player[id].state != MERCHANT)
	{
		for(int c=0;c<MAX_INV;c++)
			if( player[id].inventory[c]>-1)
		{			
			int invitem=player[id].inventory[c];
			//switch from player to ground
			
			ml_items.item[invitem].owner=-1;
			ml_items.item[invitem].map=player[id].map;
			ml_items.item[invitem].x=player[id].x;
			ml_items.item[invitem].y=player[id].y;
			player[id].inventory[c]=-1;
			

			//send add map item
			sendAddMapItem(ml_items.item[invitem].graphic,player[id].map,player[id].x,player[id].y);

			//insert into db now that item is no longer on npc
			mydb.insertItem(&ml_items.item[invitem]);
		}
		//refill npcs inventory
		doNpcFill(id);
	}
	else if(player[id].type==PLAYER)
	{
		//unequip all
		
		player[id].eLeft=-1;
		player[id].eRight=-1;
		player[id].eBody=-1;
		player[id].eHead=-1;
		player[id].eSpecial=-1;
		

		sendEquipMsg(id);

		//death drop
		for(int c=0;c<MAX_INV;c++)
			if( player[id].inventory[c]>-1 &&
				rand()%3==0 && 
				player[id].lvl>=newbieLevel && 
				ml_items.item[player[id].inventory[c]].stack!=PERMANENT)
		{
			//send inventory removal
			sendInventoryRemove(itod(id),ml_items.item[player[id].inventory[c]].slot,ml_items.item[player[id].inventory[c]].qty);
			
			//send add map item
			sendAddMapItem(ml_items.item[player[id].inventory[c]].graphic,player[id].map,player[id].x,player[id].y);

			//switch from player to ground
			
			ml_items.item[player[id].inventory[c]].owner=-1;
			ml_items.item[player[id].inventory[c]].map=player[id].map;
			ml_items.item[player[id].inventory[c]].x=player[id].x;
			ml_items.item[player[id].inventory[c]].y=player[id].y;
			updateItem(player[id].inventory[c]);
			player[id].inventory[c]=-1;
			//save item
			
			
		}
		
		player[id].x = player[id].origin_x;
		player[id].y = player[id].origin_y;
		player[id].map = player[id].origin_map;
		
	}
	//reset hp
	
	player[id].hp=player[id].mhp;
	player[id].mp=player[id].mmp;
	if(player[id].origin_map!=-1)
	{
		player[id].x = player[id].origin_x;
		player[id].y = player[id].origin_y;
		player[id].map = player[id].origin_map;
	}
	
	if(player[id].type==PLAYER)
	{
		//send to origin
		sendMycrMsg(itod(id),id);
	}
	//Sleep(1000); //Death bug emulation
	//send back to origin for NPC
	if(player[id].type==NPC)
	{
		if(player[id].origin_map==-1)
		{
			removeFromMap(id,player[id].map);
			player[id].current_map=-1;
			player[id].access=-1;
		}
			
		player[id].randomize();

		//respawn time
		if(!player[id].total_time)
		{
			if(player[id].state==MERCHANT)
				player[id].total_time = 70;
			else
				player[id].total_time = 675;
		}
		
		int x=0;
		while(world[player[id].map].map[player[id].y][player[id].x].type!=OPEN || world[player[id].map].map[player[id].y][player[id].x].space!=VACANT)
		{
			
			player[id].randomize();
			
			x++;
			if(x>600)
			{
				newLine("map %d too crowded!\n",player[id].map);
				break;
			}
		}
	}
	//send hp if player
	if(player[id].type==PLAYER)
	{
		//save player
		mydb.updatePlayer(&player[id]);
		//send hp here
		sendHPMsg(id);
		sendMPMsg(id);
	} 
	else 
		player[id].target=-1;
}

void cGameServer::doLevel(int id)
{
	mlscript.run(1004,id);//just leveled script
	
	fprintf(chatLog,"*** %s has reached experience level %d! ***\n",player[id].name,player[id].lvl);
}

//drop a portion of an inventory slot
void cGameServer::doDrop(int id,int slot,int qty)
{
	int item=player[id].inventory[slot];

	if(item==-1 || qty<=0)
		return;
	
	//quantity same or more so drop all
	if(qty >= ml_items.item[item].qty)
	{
		doDrop(id,slot);
		return;
	}

	if(player[id].access<=0 || //no access
	   ml_items.item[item].qty<=0) //cant drop portion of single or empty
		return;
	
	//drop item on map
	sendAddMapItem(ml_items.item[item].graphic,player[id].map,player[id].x,player[id].y);
	
	//remove some from player inventory
	cItem portion = ml_items.item[item];
	portion.qty = qty;
	
	ml_items.item[item].qty-=qty;
	updateItem(item);
	item=ml_items.addMapItem(player[id].map,player[id].x,player[id].y,portion);
	addItem(item);

	//remove some from client inventory
	sendInventoryRemove(itod(id),slot,qty);
}

//drop inventory slot
void cGameServer::doDrop(int id,int slot)
{
	int item=player[id].inventory[slot];

	if(item<0 || item>=ml_items.item.size())
		return;

	if(ml_items.item[item].qty==0)//cant drop empty
		return;
	
	//unequip
	
	unequipSlot(id,slot);
	

	//drop item on map
	sendAddMapItem(ml_items.item[item].graphic,player[id].map,player[id].x,player[id].y);
	
	//remove from player inventory
	
	ml_items.item[item].owner=-1;
	ml_items.item[item].map=player[id].map;
	ml_items.item[item].x=player[id].x;
	ml_items.item[item].y=player[id].y;
	updateItem(item);
	player[id].inventory[slot]=-1;
	
	//remove from client inventory
	sendInventoryRemove(itod(id),slot,ml_items.item[item].qty);
}

//pickup first item under player
void cGameServer::doPickup(int id)
{
	//get slot of item at player
	int itemSlot = topmostItemAt(player[id].map,player[id].x,player[id].y);

	//return if no items
	if(itemSlot == -1)
		return;

	int invSlot=-1;
	int qty=ml_items.item[itemSlot].qty;

	if(getWeight(id) + ml_items.item[itemSlot].weight * abs(qty) > maxWeight(id))
	{
		sendChatMsg(itod(id),"^RIt's too heavy..");
		return;
	}

	//check if can stack
	if(ml_items.item[itemSlot].qty>0)
	{
		invSlot = firstItem(id,ml_items.item[itemSlot].item_template);
		if(invSlot!=-1)
		{
			//combine and remove
			
			ml_items.item[player[id].inventory[invSlot]].qty+=ml_items.item[itemSlot].qty;
			updateItem(player[id].inventory[invSlot]);
			removeItem(itemSlot);
		}
	}
	//check for empty space for new item if space not found
	if(invSlot==-1)
		invSlot=nextInventorySlot(id);

	//if past inventory limit then exit
	if(invSlot==-1)
		return;
	
	//if not combined and removed then move item into inventory from map
	if(ml_items.item[itemSlot].qty!=0)
	{
		
		ml_items.item[itemSlot].map=-1;
		ml_items.item[itemSlot].owner=id;
		ml_items.item[itemSlot].slot=invSlot;
		ml_items.item[itemSlot].life=10;
		updateItem(itemSlot);
		player[id].inventory[invSlot]=itemSlot;
	}	

	//update clients
	sendInventoryAdd(itod(id),ml_items.item[player[id].inventory[invSlot]].graphic,ml_items.item[player[id].inventory[invSlot]].name,invSlot,qty);
	sendRemoveMapItem(player[id].map,player[id].x,player[id].y);
}

void cGameServer::doAction(int id)
{

}

void cGameServer::doEquip(int id,int slot)
{

}

void cGameServer::doUnequip(int id,int slot)
{

}

void cGameServer::doMove(int id,int map,int x,int y)
{

}

void cGameServer::doLogout(int id)
{
	player[id].target=-1;
	player[id].target_at=-1;

	mydb.updatePlayer(&player[id]);
	
	for(int i=0;i<MAX_INV;i++)
		if(player[id].inventory[i]!=-1)
			ml_items.item[player[id].inventory[i]] = cItem();
	
}

int cGameServer::doLogin(int id,int slot)
{
	//verify login
	if(! mydb.loadPlayer(&player[id],slot))
		return 0;

	//load stored items in item array
	mydb.loadPlayerItems(player[id].id,id,&ml_items);

	//empty then fill player's inventory with references
	
	for(int i=0;i<MAX_INV;i++)
		player[id].inventory[i]=-1;
	for(i=0;i<ml_items.item.size();i++)
		if(ml_items.item[i].qty!=0 && ml_items.item[i].owner==id)
			player[id].inventory[ml_items.item[i].slot]=i;
	//fix equip pointers
	if(player[id].eLeft!=-1)
		if(player[id].inventory[player[id].eLeft]==-1)
			player[id].eLeft=-1;
	if(player[id].eRight!=-1)
		if(player[id].inventory[player[id].eRight]==-1)
			player[id].eRight=-1;
	if(player[id].eHead!=-1)
		if(player[id].inventory[player[id].eHead]==-1)
			player[id].eHead=-1;
	if(player[id].eBody!=-1)
		if(player[id].inventory[player[id].eBody]==-1)
			player[id].eBody=-1;
	if(player[id].eSpecial!=-1)
		if(player[id].inventory[player[id].eSpecial]==-1)
			player[id].eSpecial=-1;
	
	return 1;
}	

void cGameServer::doCreateAccount(int index,char *pass,char *conf,char *email)
{
	//password must match confirmation
	if(strcmp(pass,conf)!=0)
	{
		sendChatMsg(itod(index),"^BPassword confirmation does not match original");
		return;
	}

	//check length of password
	if(strlen(pass)<4 || strlen(pass)>16)
	{
		sendChatMsg(itod(index),"^BPassword must be between 4 and 16 characters in length.");
		return;
	}

	//no duplicate emails
	if(mydb.emailExists(email))
	{
		sendChatMsg(itod(index),"^BThere is already an account using that email address.");
		return;
	}

	//generate unique 7 number id
	char id[256];
	sprintf(id,"%d%d",(rand()%8000)+1999,(rand()%800)+199);
	while(mydb.accountExists(id))
		sprintf(id,"%d%d",(rand()%8000)+1999,(rand()%800)+199);

	//send email and create account
	char body[1024];
	sprintf(body,"Welcome to Mystera Legends!\n"
				 "Make sure to write down your account\n"
				 "information so you dont lose it:\n"
				 "Account ID:%s\n"
				 "Password  :%s\n"
				 ,id,pass);
	
	/*sendEmail(
		"mail.mysteralegends.com",
		"c3RlZWw5OQ==",
		"MDBqdWJibGU=",
		"accounts@mysteralegends.com",
		email,
		"Mystera Legends account information",
		body);*/
	
	mydb.createAccount(id,MD5.crypt(pass),email,player[index].ip);
	char themsg[128];
	sprintf(themsg,"^BAccount created. Please write down your new account ID: ^G%s",id);
	sendChatMsg(itod(index),themsg);
	MAKE_MSG(dlog_msg,pmsg,DLOG_MSG);
	pmsg.dialog=1;
	nh.send((unsigned char *)&pmsg,sizeof(dlog_msg),SEND_GUARANTEED,itod(index));
}

void cGameServer::doCreate(int id,char *name,int body,int clothes,int hair,int *player_id)
{
	int ac=1;
	
	if(strcmp(admin_name,name)==0)
		ac=10;

	mydb.createPlayer(name,body,clothes,hair,ac,origin_map,origin_x,origin_y,player_id);
}

int cGameServer::doDelete(char *name)
{
	int pid;
	if(pid=mydb.nameExists(name))
	{
		int id=ntoi(name);
		if(id>-1)//player is online
		{
			//check for items in array
			for(int i=0;i<MAX_INV;i++)
				if(player[id].inventory[i]!=-1)
					ml_items.item[player[id].inventory[i]]=cItem();
			//remove from player array
			player[id].access=-1;
			nh.disconnect(player[id].pid);
		}
		//delete from db(handles items and account slots too)
		mydb.deletePlayer(pid);
		return 1;
	}
	return 0;
}

void cGameServer::doNpcMove(int id)
{
	mlscript.run(1009,id);
}

void cGameServer::doNpcFill(int id)
{
	if(player[id].type!=NPC)
		return;

	
	cItem item;
	int slot=0;
	//clear any items already in inventory
	for(int i=0;i<MAX_INV;i++)
		if(player[id].inventory[i]>-1)
		{
			ml_items.item[player[id].inventory[i]]=cItem();
			player[id].inventory[i]=-1;
		}
	for(i=0;i<MAX_INV;i++)
	{
		if(	ml_loot.loot[player[id].player_template].loot[i].qty!=0 &&
			((rand()%1000)+1)<=ml_loot.loot[player[id].player_template].loot[i].chance)
		{
			item = mil[ml_loot.loot[player[id].player_template].loot[i].index];
			item.qty=ml_loot.loot[player[id].player_template].loot[i].qty;
			player[id].inventory[slot]=ml_items.addInventoryItem(id,slot,item);
			slot++;
		}
	}
	
}