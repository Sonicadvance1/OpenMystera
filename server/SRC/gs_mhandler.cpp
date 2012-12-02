
#include "gameserver.h"
#include "net.h"
#include "console.h"
#include "netstructs.h"
#include "censor.h"
#include "zlib.h"
#include "md5.h"

#define MAKE_MSG(x,_y,z);    x _y;_y.type=z;

void cGameServer::onConnect(PlayerID pid,char *ip)
{
	UNUSED(ip);
	int i=0;
	if(i==player.size())
		player.size(i+100);
	while(player[i].access>-1)
	{
		i++;
		if(i==player.size())
			player.size(i+100);
	}
	
	numConnections++;
	
	//get ip
	char tempip[16];
	strcpy(tempip,nh.getip(pid));

	player[i].access=0;
	player[i].pid=pid;

	/*if(findIP(tempip)>-1)//no dups
	{
		sendChatMsg(pid,"Duplicate IP address.");
		nh.disconnectPlayer(pid);
		return;
	}*/

	
	strcpy(player[i].ip,tempip);
	

	newLine("--(%s)Connection accepted into slot %d - connections: %d",player[i].ip,i,numConnections);
	
	fprintf(chatLog,"--(%s)Connection accepted into slot %d - connections: %d\n",player[i].ip,i,numConnections);
	
	//send session info
	sendSessionInfo(pid);
	//send server welcome
	//sendChatMsg(pid,"Welcome to the Official Mystera Legends Server!");
	//Post new player info
	//postServer();
}

void cGameServer::onDisconnect(PlayerID pid)
{
	int index = dtoi(pid);
	if(index==-1)
		return;
	if(player[index].access>0 && player[index].type==PLAYER)
	{
		numPlayers--;
		if(numPlayers<0)
			numPlayers=0;

		//post new player info
		//postServer(); <--- NO!
		
		//if(player[index].time_safe<120)//5 minute ban penalty
		//	player[index].boot_time+=((unsigned)time(0)+300);
	
		mlscript.run(1003,index);//disconnect script
		
		newLine("%s logs out. Players: %d\n",player[index].name,numPlayers);
		
		fprintf(chatLog,"%s logs out. Players: %d\n",player[index].name,numPlayers);
		
		doLogout(index);

		sendLeftMessage(index);
		
		world[player[index].map].map[player[index].y][player[index].x].space=VACANT;
		removeFromMap(index,player[index].map);
		player[index].current_map=-1;
		player[index] = cPlayer();
	} 
	
	player[index].access = -1;
	numConnections--;
	if(numConnections<0)
		numConnections=0;
	
	newLine("--Slot %d disconnected - connections: %d\n",index,numConnections);
	
	fprintf(chatLog,"--Slot %d disconnected - connections: %d\n",index,numConnections);

}

void cGameServer::onMessage(unsigned char *data,unsigned long dataSize,PlayerID pid,unsigned char type)
{
	UNUSED(dataSize);

	if(type==NULL_MSG)
		return;

	CHARLOG('m');

	int index = dtoi(pid);
	//printf("Message of type %d received, %d bytes\n",type,dataSize);
	
	//flood control
	int now=SDL_GetTicks();
	if(now-player[index].packet_time<300 && type != ATCK_MSG &&  type!=PICK_MSG && type!=CMND_MSG && type!=PARM_MSG)
	{
		if(type==MYCR_MSG)
		{
			CAST_MSG(mycr_msg,msg);
			if(msg->p.x==player[index].x && msg->p.y==player[index].y && msg->p.map ==player[index].map)
				player[index].npacket--;
		}

		player[index].npacket++;
		if(player[index].npacket>25)
		{
			newLine("***%s booted for packet flooding...",player[index].name);
			sendChatMsg(itod(index),"You have been booted for packet flooding (5 minutes).");
			player[index].boot_time += time(0) + (5*60);
			nh.disconnect(itod(index));
			onDisconnect(itod(index));
			return;
		}

	}
	else if(player[index].npacket>0)
		player[index].npacket--;
	player[index].packet_time=now;

	if(type==VRSN_MSG)
	{
		CAST_MSG(vrsn_msg,msg);
		if(msg->version!=client_version)
		{
			sendChatMsg(pid,"^cOld or incompatible client version: please download a newer version.");
			sendChatMsg(pid,"^cDownload from: www.mysteralegends.com");
			nh.disconnect(pid);
			return;
		}
	}
	else if(type==ALGN_MSG)
	{
		CAST_MSG(algn_msg,msg);

		//verify login
		if(nameOnline(msg->id))
		{
			sendChatMsg(player[index].pid,"^BThat account is already logged in.");
			return;
		}

		//send slot information
		
		if(!mydb.loginAccount(msg->id,MD5.crypt(msg->pass),player[index].ip))
		{
			sendChatMsg(pid,"^BInvalid account id or password.");
			return;
		}

		cPlayer slot[4];
		mydb.getAccountSlots(msg->id,&slot[0],&slot[1],&slot[2],&slot[3]);

		//store account id
		strcpy(player[index].accid,msg->id);

		MAKE_MSG(slot_msg,pmsg,SLOT_MSG);
		for(int i=0;i<4;i++)
		{
			strcpy(pmsg.name[i],slot[i].name);
			pmsg.lvl[i]=slot[i].lvl;
			pmsg.sprite[i]=slot[i].sprite;
			pmsg.body[i]=slot[i].body;
			pmsg.hair[i]=slot[i].hair;
			pmsg.clothes[i]=slot[i].clothes;
		}
		nh.send((unsigned char *)&pmsg,sizeof(slot_msg),SEND_GUARANTEED,player[index].pid);
	}
	else if(type==NWAC_MSG)
	{
		CAST_MSG(nwac_msg,msg);
		doCreateAccount(index,msg->pass,msg->conf,msg->email);
	}
	else if(type==LOGN_MSG)
	{
		CAST_MSG(logn_msg,msg);
	
		//verify account already logged in
		if(strcmp(player[index].accid,"")==0)
			return;

		if(player[index].access>0)//char logged in already
			return;
		
		if(!doLogin(index,msg->slot))
			return;

		//Check stats and boundaries
		if(player[index].access==10 && strcmp(player[index].name,admin_name)!=0)
			player[index].access=1;
		else if(strcmp(player[index].name,admin_name)==0)
			player[index].access=10;
		if(player[index].map<0)
			player[index].map=0;
		if(player[index].map>world.size())
			player[index].map=0;
		if(player[index].x>=MAP_COLS)
			player[index].x=MAP_COLS-1;
		if(player[index].y>=MAP_ROWS)
			player[index].y=MAP_ROWS-1;
		player[index].pid = pid;
		strcpy(player[index].ip,nh.getip(pid));
		

		//check if booted
		if(player[index].boot_time!=0)
		{
			if((unsigned)time(0)>=player[index].boot_time)
				player[index].boot_time=0;
			else
			{
				sendChatMsg(itod(index),"You have been booted(%d minutes left).",(player[index].boot_time-time(0))/60);
				nh.disconnect(itod(index));
				return;
			}
		}

		//ANNOUNCE NEW OR OLD ARRIVAL
		if(strcmp(player[index].logout_date,"0000-00-00 00:00:00")==0)
		{
			player[index].x = player[index].origin_x;
			player[index].y = player[index].origin_y;
			player[index].map = player[index].origin_map;
			
			sendChatMsg(ALL_CLIENTS,"^cAll hail %s, a new adventurer in this land.",player[index].name);
		}
		else
			sendChatMsg(ALL_CLIENTS,"^c%s has returned to the realm.",player[index].name);

		
		mlscript.run(1002,index);//login script
		
		newLine("slot %d logged in as %s\n",index,player[index].name);
		
		fprintf(chatLog,"slot %d logged in as %s\n",index,player[index].name);
		
		numPlayers++;

		//postServer(); NO NO NO

		if(player[index].map >= world.size())
		{
			world[player[index].map].map[player[index].y][player[index].x].space=VACANT;
			player[index].map = this->origin_map;
			player[index].x = this->origin_x;
			player[index].y = this->origin_y;
			world[player[index].map].map[player[index].y][player[index].x].space=index;
			if(player[index].type==PLAYER)
				sendMycrMsg(itod(index),index);
		}
		
		//int c;
		//SEND ALL PLAYERS NEW GUY
		sendPlyrMsg(index);
		//SEND HIS CURRENT MAP
		sendUpldMsg(pid,player[index].map);
		//SEND ACCESS
		sendAcssMsg(itod(index),index);
		//SEND POSITION
		sendMycrMsg(itod(index),index);
		//SEND HEALTH STATUS
		sendLevlMsg(itod(index),index);
		//SEND ATTRIBUTE STATUS
		sendAttrMsg(itod(index),index);
		//SEND INVENTORY ITEMS
		sendInventory(itod(index),index);
		//SEND EQUIP STATUS
		sendEquipMsg(index);
		//TELL NEW GUY HOW MANY PPL ARE ON
		sendChatMsg(pid,"^cWelcome! There are %d other players online.",numPlayers-1);
		//SEND SHADE
		//for(c=0;c<10;c++)
			sendShade(itod(index),ml_cycle[ml_hour]);
		//SEND NEW GUY ALL PLAYERS
		//for(c=0;c<1;c++)
		sendPlayerVMsg(index);
		//sendPlayerVMsg(index);
		//UPDATE TILE
		world[player[index].map].map[player[index].y][player[index].x].space=index;
		//remove dialog
		//MAKE_MSG(dlog_msg,dmsg,DLOG_MSG);
		//dmsg.dialog=-1;
		//nh.send(&dmsg,sizeof(dlog_msg),SEND_GUARANTEED,player[index].pid);
		//SEND ALL ITEMS ON GROUND
		//sendItemVMsg(index);//dont need to, version check on client will do
	}
	else if(type==NCHR_MSG )//new character && player[index].access == 0
	{
		CAST_MSG(nchr_msg,msg);

		//star out bad language
		CENSOR.star(msg->name);

		//check name length
		if(strlen(msg->name)<3 || strlen(msg->name)>16)
		{
			sendChatMsg(pid,"^BInvalid character name. Try again.");
			return;
		}
		
		//make sure only letters are used
		for(unsigned int c=0;c<strlen(msg->name);c++)
			if(msg->name[c]<'A' || (msg->name[c]>'Z' && msg->name[c]<'a') || msg->name[c]>'z')
			{
				sendChatMsg(pid,"^BInvalid character name. Try again.");
				return;
			}

		//make sure name doesnt already exist
		if(mydb.nameExists(msg->name))
		{
			sendChatMsg(pid,"^BName already exists, choose another");
			return;
		}

		if(msg->body < 0 || msg->body > 19 || msg->hair < 0 || msg->hair > 89 || msg->clothes < 0 || msg->clothes > 77)
		{
			sendChatMsg(pid,"^BIllegal option.");
			return;
		}

		//created successfully
		newLine("New character created: %s, player accounts at %d\n",msg->name,mydb.numPlayerAccounts()+1);
		
		fprintf(chatLog,"New character created: %s, player accounts at %d\n",msg->name,mydb.numPlayerAccounts()+1);
		

		int player_id;

		doCreate(index,msg->name,msg->body,msg->clothes,msg->hair,&player_id);
		mydb.setAccountSlot(player[index].accid,msg->slot,player_id);
		//notify client creation successful
		sendChatMsg(pid,"^BNew character created.");

		cPlayer slot[4];
		mydb.getAccountSlots(player[index].accid,&slot[0],&slot[1],&slot[2],&slot[3]);
		MAKE_MSG(slot_msg,pmsg,SLOT_MSG);
		for(int i=0;i<4;i++)
		{
			strcpy(pmsg.name[i],slot[i].name);
			pmsg.lvl[i]=slot[i].lvl;
			pmsg.sprite[i]=slot[i].sprite;
			pmsg.body[i]=slot[i].body;
			pmsg.hair[i]=slot[i].hair;
			pmsg.clothes[i]=slot[i].clothes;
		}
		nh.send((unsigned char *)&pmsg,sizeof(slot_msg),SEND_GUARANTEED,player[index].pid);
	}
	else if(player[index].access<1)
		return;
	else if(type==MYCR_MSG)
	{
		CAST_MSG(mycr_msg,msg);

		//make sure params are normal value
		if(msg->p.map<0 || msg->p.map>=world.size() || msg->dir > 3 || 
			msg->p.x>19 || msg->p.y>14)
		{
			sendMycrMsg(player[index].pid,index);
			return;
		}

		//Don't let player speed hack
		/*if(!player[index].move_timer.tick(100) && (msg->p.x != player[index].x || msg->p.y != player[index].y))
		{
			sendMycrMsg(player[index].pid,index);
			return;
		}*/

		player[index].stationary=0;
		
		//dont let client override origin warp (for death bug)
		if(player[index].map == player[index].origin_map && player[index].x == player[index].origin_x && player[index].y == player[index].origin_y && msg->p.map != player[index].map)
			return;
	
		//dont let player step on other player
		if(msg->p.map == player[index].map && world[msg->p.map].map[msg->p.row()][msg->p.col()].space != VACANT && world[msg->p.map].map[msg->p.row()][msg->p.col()].space != index)
		{
			sendMycrMsg(player[index].pid,index);
			return;
		}

		//if on wall or switch(and not an admin) set back and update map
		//This prevents laggy map warping and helps stuck players
		if((world[msg->p.map].map[msg->p.row()][msg->p.col()].type == WALL || 
				world[msg->p.map].map[msg->p.row()][msg->p.col()].type == SWCH) &&
		    player[index].access<3)
		{
			sendMycrMsg(player[index].pid,index);
			sendUpldMsg(player[index].pid,index);
			return;
		}

		//dont let player walk more than one square ahead of where they are
		if(player[index].map==msg->p.map && (abs(player[index].x-msg->p.x)+abs(player[index].y-msg->p.y))>1)
		{
			sendMycrMsg(player[index].pid,index);
			return;
		}
		else if(player[index].map!=msg->p.map &&
				!(player[index].x==0 && msg->p.x==19 && player[index].y==msg->p.y && world[player[index].map].w==msg->p.map) &&
				!(player[index].x==19 && msg->p.x==0 && player[index].y==msg->p.y && world[player[index].map].e==msg->p.map) &&
				!(player[index].y==0 && msg->p.y==14 && player[index].x==msg->p.x && world[player[index].map].n==msg->p.map) &&
				!(player[index].y==14 && msg->p.y==0 && player[index].x==msg->p.x && world[player[index].map].s==msg->p.map) )
		{
			sendMycrMsg(player[index].pid,index);
			sendUpldMsg(player[index].pid,index);
			return;
		}

		//make the move
		int old_x=player[index].x;
		int old_y=player[index].y;

		world[player[index].map].map[player[index].y][player[index].x].space=VACANT;
		player[index].map=msg->p.map;
		player[index].x=msg->p.x;
		player[index].y=msg->p.y;
		player[index].dir=msg->dir;
		world[player[index].map].map[player[index].y][player[index].x].space=index;
		
		
		//check for warp
		if(world[player[index].map].map[player[index].y][player[index].x].type==WARP)
		{
			
			world[player[index].map].map[player[index].y][player[index].x].space=VACANT;
			player[index].map=world[msg->p.map].map[msg->p.y][msg->p.x].warp.map;
			player[index].x=world[msg->p.map].map[msg->p.y][msg->p.x].warp.x;
			player[index].y=world[msg->p.map].map[msg->p.y][msg->p.x].warp.y;
			world[player[index].map].map[player[index].y][player[index].x].space=index;
			
			sendMycrMsg(pid,index);
		}
		//check for script
		else if((player[index].x!=old_x || player[index].y!=old_y) && world[player[index].map].map[player[index].y][player[index].x].type==SCPT)
			mlscript.run(world[player[index].map].map[player[index].y][player[index].x].warp.map,index);
	}
	else if(type==CHAT_MSG)
	{
		chat_msg msg;
		char theChat[256];
		memcpy((unsigned char *)&msg,data,sizeof(chat_msg));
		memcpy(theChat,data+sizeof(chat_msg),msg.size);
		for(unsigned int i=0;i<strlen(theChat);i++)
			if(theChat[i]=='%')
				theChat[i]='/';
		CENSOR.star(theChat);
		strcpy(last_chat,theChat);
		last_chatter=index;
		
		mlscript.run(1006,index);//run chat script
		
		for(int c=0;c<player.size();c++)
			if(player[c].access>0 && player[c].type!=NPC && player[c].map == player[index].map)
				sendChatMsg(itod(c),"%s:%s",player[index].name,theChat);
		for(int c=0;c<player.size();c++)
			if(player[c].access>0 && player[c].type==NPC && player[c].map == player[index].map && player[c].chat_script!=-1)
				eHandler.add(player[c].chat_script,c,0);
		newLine("%s:%s",player[index].name,theChat);
		
		fprintf(chatLog,"%s:%s\n",player[index].name,theChat);
		
	}
	else if(type==TRGT_MSG)
	{
		CAST_MSG(trgt_msg,msg);
		player[index].target_at=msg->index;
	}
	else if(type==QUIT_MSG)
	{
		if(player[index].time_safe>=120)
		{
			MAKE_MSG(quit_msg,pmsg,QUIT_MSG);
			nh.send((unsigned char *)&pmsg,sizeof(quit_msg),SEND_GUARANTEED,player[index].pid);
			//nh.disconnect(itod(index));
		}
		else
			sendChatMsg(itod(index),"You can't logout right after taking damage. 5 minute ban for force quitting[disabled].");
	}
	else if(type==CMND_MSG)
	{
		cmnd_msg msg;
		char theCmd[256];
		memcpy((unsigned char *)&msg,data,sizeof(cmnd_msg));
		memcpy(theCmd,data+sizeof(cmnd_msg),msg.size);
		for(int c=0;c<256;c++)
			if(theCmd[c] == '%')
				theCmd[c] = '/';
		CENSOR.star(theCmd);
		parse(theCmd,index);
	}
	else if(type==DROP_MSG)
	{
		CAST_MSG(drop_msg,msg);
		sprintf(last_command, "drop %d %d", msg->index, (int) ml_items.item[player[index].inventory[msg->index]].qty);
		mlscript.run(1008,index);
		doDrop(index,msg->index);
	}
	else if(type==PICK_MSG)
	{
		doPickup(index);
	}
	else if(type==ATCK_MSG)
	{
		double dex_factor = (1.0 - ((float)player[index].dex/100.0));

		if(dex_factor < 0.1)
		{
			dex_factor = 0.1;
		}

		int    total_cooldown = 0;

		if(player[index].eLeft != -1)
		{
			total_cooldown += ml_items.item[player[index].inventory[player[index].eLeft]].total_cooldown;
		}

		if(player[index].eRight != -1)
		{
			total_cooldown += ml_items.item[player[index].inventory[player[index].eRight]].total_cooldown;
		}

		if(total_cooldown == 0)
		{
			total_cooldown = 750;
		}

		if (player[index].mstl.tick(total_cooldown * dex_factor))
		{
			mlscript.run(1010,index);
		}
	}
	else if(type==PARM_MSG)
	{
		CAST_MSG(parm_msg,msg);
		if(msg->flag==3 && player[index].mstl.tick(750) && player[index].front().inBounds() && world[player[index].map].map[player[index].front().y][player[index].front().x].type==SWCH)
				mlscript.run(world[player[index].map].map[player[index].front().y][player[index].front().x].warp.map,index);
		else if(msg->parm==0)
		{
			if(world[player[index].map].version!=msg->flag)//map version check
				sendUpldMsg(pid,player[index].map);
			sendItemVMsg(index);
		}
	}
	else if(type==UPLD_MSG)
	{
		if(player[index].access < 6)
			return;
		upld_msg msg;
		char buf[5000];
		memcpy((unsigned char *)&msg,data,sizeof(upld_msg));
		memcpy((unsigned char *)&buf,data+sizeof(upld_msg),msg.size);
		cMap temp=world[player[index].map]; //store space ids
		unsigned long newlen = sizeof(cMap);
		
		uncompress ((unsigned char *)&world[player[index].map], &newlen, (unsigned char *)&buf, (unsigned long)newlen);
		compressInto(player[index].map);
		

		//save here
		char filename[32];
		sprintf(filename,"serverdata/maps/map%d.dat",player[index].map);
		
		saveData(&world[player[index].map],sizeof(cMap),filename);
		
		newLine("map %d uploaded and saved\n",player[index].map);
		int r,c;
		
		for(r=0;r<MAP_ROWS;r++)
			for(c=0;c<MAP_COLS;c++)
				world[player[index].map].map[r][c].space = temp.map[r][c].space; //restore space id
		

		//loop through players on map and send new map
		for(int count=0;count<player.size();count++)
		{
			if(player[count].access>0)
			{
				if(player[count].type==PLAYER && player[count].map==player[index].map && count!=index)
					sendUpldMsg(itod(count),player[index].map);
				if(player[count].type==NPC && player[count].origin_map == player[index].map)
				{
					removeFromMap(count,player[count].map);
					player[count].current_map=-1;
					//remove items in npcs inventory
					for(int i=0;i<MAX_INV;i++)
						if(player[count].inventory[i]>-1)
							ml_items.item[player[count].inventory[i]] = cItem();
					//set spot vacant
					world[player[count].map].map[player[count].y][player[count].x].space=VACANT;
					//kill off npc
					player[count].access=-1;
					player[count] = cPlayer();
					
				}
			}
		}
		
		loadNPC(player[index].map);
		

		//send new npcs
		for(int count=0;count<player.size();count++)if(player[count].access>0&&player[count].type==NPC&&player[count].origin_map == player[index].map)
			sendPlyrMsg(count);
	}
	else if(type==FILE_MSG)
	{
		if(player[index].access < 8)
			return;
		file_msg msg;
		memcpy((unsigned char *)&msg,data,sizeof(file_msg));
		char temp[64];
		char back[64];
		int ml=0;
		int map = -1;
	
		if(strstr(msg.name,".ml")!=NULL)
			ml=1;

		if(sscanf(msg.name, "map%d.dat", &map) != 1)
		{
			map = -1;
		}
	
		if(ml)
		{
			sprintf(temp,"serverdata/%s",msg.name);
			sprintf(back,"serverdata/backups/%s",msg.name);
		}
		else if(map != -1)
		{
			sprintf(temp,"serverdata/maps/%s",msg.name);
			sprintf(back,"serverdata/maps/backups/%s",msg.name);
		}
		else
		{
			sprintf(temp,"serverdata/scripts/%s",msg.name);
			sprintf(back,"serverdata/scripts/backups/%s",msg.name);
		}
	
		if(fileExists(temp))
			backupFile(temp,back);
		FILE *thefile = fopen(temp,"wb");

		if(thefile != NULL)
		{
			char buf[100000];
			unsigned long newlen = 100000;
			uncompress ((unsigned char *)&buf, &newlen,data+sizeof(file_msg), (unsigned long)msg.size);
			newLine("File %s uploaded: %d(%d) bytes.",msg.name,msg.size,newlen);
			fwrite(&buf,newlen,1,thefile);
			fclose(thefile);
			if(ml)
			{
				parse("/reload",index);
			}
			else if(map != -1)
			{
				cMap temp_map=world[map]; //store space ids
				loadData(&world[map], sizeof(cMap), temp);
				compressInto(map);
				int r,c;
		
				for(r=0;r<MAP_ROWS;r++)
					for(c=0;c<MAP_COLS;c++)
						world[map].map[r][c].space = temp_map.map[r][c].space; //restore space id
				//loop through players on map and send new map
				for(int count=0;count<player.size();count++)
				{
					if(player[count].access>0)
					{
						if(player[count].type==PLAYER && player[count].map==map)
							sendUpldMsg(itod(count),map);
						if(player[count].type==NPC && player[count].origin_map == map)
						{
							removeFromMap(count,player[count].map);
							player[count].current_map=-1;
							//remove items in npcs inventory
							for(int i=0;i<MAX_INV;i++)
								if(player[count].inventory[i]>-1)
									ml_items.item[player[count].inventory[i]] = cItem();
							//set spot vacant
							world[player[count].map].map[player[count].y][player[count].x].space=VACANT;
							//kill off npc
							player[count].access=-1;
							player[count] = cPlayer();
							
						}
					}
				}
				
				loadNPC(map);
				

				//send new npcs
				for(int count=0;count<player.size();count++)if(player[count].access>0&&player[count].type==NPC&&player[count].origin_map == map)
					sendPlyrMsg(count);
			}
			else
			{
				if(strstr(msg.name,".h")!=NULL)
					return;
				int id;
				sscanf(msg.name,"%d.txt",&id);
				
				mlscript.free(id);
				if(!mlscript.compile(id))
					sendChatMsg(pid,mlscript.getError());
				else
					sendChatMsg(pid,"Script compiled successfully.");
				
			}
		}
		else newLine("Error creating file\n");
	}
	else if(type==NULL_MSG)
	{
		//printf("received udp\n");
	}
	else
	{
		newLine("unknown type: %d from slot %d",type,index);
		//nh.disconnect(pid);
	}
}
