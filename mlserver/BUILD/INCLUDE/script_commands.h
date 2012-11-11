//\\//\\\// SCRIPT FUNCTIONS \\//\\//\\//
char scriptGlobalString[512];

#include "gameserver.h"
#include "console.h"

static cGameServer *mygs;

static void setScriptCommandGameServer(cGameServer *gs)
{
	mygs=gs;
}
//newer script access commands

//script runtime vars
_MLF int getPlayer()
{
	return mygs->mlscript.getPlayer();
}

_MLF char *getChat()
{
	return(mygs->last_chat);	
}

_MLF char *getCommand()
{
	return(mygs->last_command);
}

_MLF int getChatPlayer()
{
	return(mygs->last_chatter);
}
_MLF int myScript()
{
	return( mygs->mlscript.getScript() );	
}
//server commands
_MLF void printMsg(int p0)
{
	newLine("*%s\n",p0);//possible thread conflict
}

_MLF void makeNPC(int p0,int p1,int p2,int p3)
{
	int n=0;
	if(n==mygs->player.size())
		mygs->player.size(mygs->player.size()+100);
	while(mygs->player[n].access>-1)
	{
		n++;
		if(n==mygs->player.size())
			mygs->player.size(mygs->player.size()+100);
	}
	pos p;
	p.map = p1;
	p.x = p2;
	p.y = p3;
	if(p.inBounds() && p0>-1 && p0<mygs->mnl.size())
	{
		mygs->player[n] = mygs->mnl[p0];
		mygs->player[n].access=1;
		mygs->player[n].map=p.map;
		mygs->player[n].y=p.y;
		mygs->player[n].x=p.x;
		mygs->player[n].origin_map=-1;
		mygs->player[n].hp=mygs->player[n].mhp;
		mygs->player[n].mp=mygs->player[n].mmp;
		mygs->player[n].type=NPC;
		mygs->player[n].player_template=p0;
		mygs->sendPlyrMsg(n);
		//add items to npc's inventory
		mygs->doNpcFill(n);

		//fill map place of npc
		mygs->world[p1].map[p3][p2].space = n;
	}
}

_MLF int getTime()
{	
	return(mygs->ml_hour);
}


_MLF int takeItem(int p0,int p1)
{
	for(int i=0;i<mygs->ml_items.item.size();i++)
		if(mygs->ml_items.item[i].qty!=0 && mygs->ml_items.item[i].owner==p0 && mygs->ml_items.item[i].item_template==p1)
		{
			//unequip
			mygs->unequipSlot(p0,mygs->ml_items.item[i].slot);
			//remove from player inventory
			mygs->sendInventoryRemove(mygs->player[p0].pid,p1,mygs->ml_items.item[i].qty);
			return ( 1 );
		}
	return ( 0 );
}


_MLF void makeItem(int p0,int p1,int p2,int p3,int p4)
{
	if(p0<0 || p0>=mygs->mil.size() || p1==0)
		return;

	cItem item = mygs->mil[p0];
	if(item.stack!=STACKABLE)
		item.qty=-1;
	else
		item.qty=p1;
	item.owner=-1;
	item.map=p2;
	item.x=p3;
	item.y=p4;
	mygs->mydb.insertItem(&item);
	mygs->ml_items.addMapItem(p2,p3,p4,item);
	mygs->sendAddMapItem(item.graphic,p2,p3,p4);
}

_MLF int giveItem(int p0,int p1,int p2)
{
	if(p1<0 || p1>=mygs->mil.size() || p1==0)
		return 0;

	cItem item = mygs->mil[p1];

	if(mygs->getWeight(p0) + (item.weight * abs(p2)) <= mygs->maxWeight(p0))
	{

		int slot=-1;
		if(item.stack!=STACKABLE)
			item.qty=-1;
		else
		{
			item.qty=p2;
			slot = mygs->firstItem(p0,p1);
			if(slot!=-1)
			{
				//combine and remove
				mygs->ml_items.item[mygs->player[p0].inventory[slot]].qty+=item.qty;
				mygs->updateItem(mygs->player[p0].inventory[slot]);
				mygs->sendInventoryAdd(mygs->itod(p0),item.graphic,item.name,slot,item.qty);
				return 1;
			}
		}

		slot=mygs->nextInventorySlot(p0);

		if(slot==-1)
			return 0;

		item.owner=p0;



		item.slot=slot;
		item.map=-1;
		mygs->mydb.insertItem(&item,mygs->player[p0].id);
		mygs->player[p0].inventory[slot]=mygs->ml_items.addInventoryItem(p0,slot,item);
		mygs->sendInventoryAdd(mygs->itod(p0),item.graphic,item.name,slot,item.qty);
		return ( 1 );
	}
	else
	{
		mygs->sendChatMsg(mygs->itod(p0),"^RIt's too heavy..");
		makeItem(p1, p2, mygs->player[p0].map, mygs->player[p0].x, mygs->player[p0].y);
		return ( 0 );
	}
}

_MLF int clearItem(int p0,int p1,int p2,int p3)
{
	int item=mygs->topmostItemAt(p1,p2,p3);
	if(item==-1)
		return 0;
	if(mygs->ml_items.item[item].item_template!=p0)
		return 0;

	mygs->removeItem(item);
	mygs->sendRemoveMapItem(p1,p2,p3);

	return 1;
}

_MLF int getItemAt(int p0,int p1,int p2)
{
	int item=mygs->topmostItemAt(p0,p1,p2);
	if(item==-1)
		return -1;
	return mygs->ml_items.item[item].item_template;
}



_MLF void npcMove(int p0,int p1)
{
	int count=p0;
	int dir=p1;
	int canmove=0;
	if(dir==0&&mygs->world[mygs->player[count].map].canMove(mygs->player[count].down(),1))canmove=1;
	else if(dir==1&&mygs->world[mygs->player[count].map].canMove(mygs->player[count].up(),1))canmove=1;
	else if(dir==2&&mygs->world[mygs->player[count].map].canMove(mygs->player[count].left(),1))canmove=1;
	else if(dir==3&&mygs->world[mygs->player[count].map].canMove(mygs->player[count].right(),1))canmove=1;
	if(canmove)
	{
		mygs->world[mygs->player[count].map].map[mygs->player[count].y][mygs->player[count].x].space=VACANT;
		mygs->player[count].move(dir);
		mygs->world[mygs->player[count].map].map[mygs->player[count].y][mygs->player[count].x].space=count;
	}
}

_MLF int npcCanMove(int p0,int p1,int p2)
{
	pos temp;
	temp.map=mygs->player[p0].map;
	temp.x=p1;
	temp.y=p2;
	if(mygs->player[p0].type==PLAYER)
		return(mygs->world[temp.map].canMove(temp));
	else
		return(mygs->world[temp.map].canMove(temp,1));
}

_MLF void npcAttack(int p0)
{
	int count=p0;
	if(!(mygs->player[count].front().row()==255||mygs->player[count].front().row()==MAP_ROWS||mygs->player[count].front().col()==255||mygs->player[count].front().col()==MAP_COLS)&&
			mygs->player[count].target>-1&&mygs->world[mygs->player[count].map].map[mygs->player[count].front().row()][mygs->player[count].front().col()].space!=VACANT&&mygs->player[mygs->world[mygs->player[count].map].map[mygs->player[count].front().row()][mygs->player[count].front().col()].space].type==PLAYER&&mygs->player[mygs->world[mygs->player[count].map].map[mygs->player[count].front().row()][mygs->player[count].front().col()].space].access>0)
	{
		int dmg=mygs->wouldAttack(count,mygs->world[mygs->player[count].map].map[mygs->player[count].front().row()][mygs->player[count].front().col()].space);
		if(dmg==0)
			dmg=rand()%2;
		else if(rand()%2 && mygs->missBonus(mygs->player[mygs->world[mygs->player[count].map].map[mygs->player[count].front().row()][mygs->player[count].front().col()].space].dex))
			dmg=0;
		mygs->player[mygs->world[mygs->player[count].map].map[mygs->player[count].front().row()][mygs->player[count].front().col()].space].time_safe = 0;
		if(mygs->player[mygs->world[mygs->player[count].map].map[mygs->player[count].front().row()][mygs->player[count].front().col()].space].hp-dmg <= 0)
			mygs->player[mygs->world[mygs->player[count].map].map[mygs->player[count].front().row()][mygs->player[count].front().col()].space].hp = 0;
		else
			mygs->player[mygs->world[mygs->player[count].map].map[mygs->player[count].front().row()][mygs->player[count].front().col()].space].hp-=dmg;
		mygs->player[mygs->world[mygs->player[count].map].map[mygs->player[count].front().row()][mygs->player[count].front().col()].space].target=count;
		//send blood/miss effect out
		if(dmg>0)
			mygs->sendEffect(mygs->player[count].map,mygs->player[mygs->world[mygs->player[count].map].map[mygs->player[count].front().row()][mygs->player[count].front().col()].space].x,mygs->player[mygs->world[mygs->player[count].map].map[mygs->player[count].front().row()][mygs->player[count].front().col()].space].y,0);
		else
			mygs->sendEffect(mygs->player[count].map,mygs->player[mygs->world[mygs->player[count].map].map[mygs->player[count].front().row()][mygs->player[count].front().col()].space].x,mygs->player[mygs->world[mygs->player[count].map].map[mygs->player[count].front().row()][mygs->player[count].front().col()].space].y,4);
		//send hp bar
		mygs->sendHPbar(mygs->player[count].map,mygs->world[mygs->player[count].map].map[mygs->player[count].front().row()][mygs->player[count].front().col()].space);
		//send hp
		mygs->sendHPMsg(mygs->world[mygs->player[count].map].map[mygs->player[count].front().row()][mygs->player[count].front().col()].space);
	}
}


_MLF int hasItem(int p0,int p1)
{
	if(p0 < 0 || p0 >= mygs->player.size())
		return 0;
	for(int i=0;i<MAX_INV;i++)
		if(mygs->player[p0].inventory[i]!=-1 && mygs->ml_items.item[mygs->player[p0].inventory[i]].item_template==p1)
			return (1);
	return (0);
}

_MLF int itemSlot(int p0,int p1)
{
	for(int i=0;i<MAX_INV;i++)
		if(mygs->player[p0].inventory[i]!=-1 && mygs->ml_items.item[mygs->player[p0].inventory[i]].item_template==p1)
			return i;
	return -1;
}

_MLF int itemAt(int p0,int p1)
{
	if(mygs->player[p0].inventory[p1]==-1)
		return -1;
	return mygs->ml_items.item[mygs->player[p0].inventory[p1]].item_template;
}

_MLF int qtyAt(int p0,int p1)
{
	if(mygs->player[p0].inventory[p1]==-1)
		return -1;
	return mygs->ml_items.item[mygs->player[p0].inventory[p1]].qty;
}

_MLF void setQty(int p0,int p1,int p2)
{
	if(p1<0 || p1>MAX_INV || p0< 0 || p0>=mygs->player.size())
		return;
	int item=mygs->player[p0].inventory[p1];
	if(item==-1)
		return;
	int oldqty=mygs->ml_items.item[item].qty;
	if(p2<0)
		p2=0;
	mygs->ml_items.item[item].qty=p2;
	mygs->sendInventoryAdd(mygs->itod(p0),mygs->ml_items.item[item].graphic,mygs->ml_items.item[item].name,p1,mygs->ml_items.item[item].qty-oldqty);
	if(p2==0)
	{
		mygs->player[p0].inventory[p1]=-1;//PARTIAL INV BUG FIX??
		mygs->removeItem(item);
	}
	else
		mygs->updateItem(item);
}

//globals
_MLF void setGlobalInt(char *p0,int p1)
{
	mygs->gHandler.setInt(p0,p1);
}

_MLF void setGlobalStr(char * p0,char * p1)
{
	mygs->gHandler.setString(p0,p1);
}

_MLF int isGlobal(char * p0)
{
	return(mygs->gHandler.isGlobal(p0));
}

_MLF int globalInt(char * p0)
{
	return(mygs->gHandler.getInt(p0));
}

_MLF char *globalStr(char * p0)
{
	return(mygs->gHandler.getString(p0));
}

_MLF void freeGlobal(char *p0)
{
	mygs->gHandler.free(p0);
}

_MLF void DBupdateGlobal(char *name,char *value)
{
	mygs->mydb.updateGlobal(name,value);
}

_MLF void DBinsertGlobal(char *name,char *value)
{
	mygs->mydb.insertGlobal(name,value);
}

_MLF void DBdeleteGlobal(char *name)
{
	mygs->mydb.deleteGlobal(name);
}

_MLF char *DBselectGlobal(char *name)
{
	return mygs->mydb.selectGlobal(name);
}

_MLF bool DBisGlobal(char *name)
{
	return mygs->mydb.isGlobal(name);
}

_MLF int DBsendQuery(char *query)
{
	return mygs->mydb.sendQuery(query);
}

//server data accessors
_MLF int playerLen()
{
	return mygs->player.size();
}

_MLF cPlayer *playerStruct(int id)
{
	return &mygs->player[id];
}

_MLF void playerSave(int id)
{
	mygs->mydb.updatePlayer( &mygs->player[id] );
}

_MLF void playerResize(int len)
{
	mygs->player.size(len);
}
_MLF void itemResize(int len)
{
	mygs->ml_items.item.size(len);
}
_MLF void mapResize(int len)
{
	mygs->world.size(len);
}
_MLF int mapLen()
{
	return mygs->world.size();
}

_MLF cMap *mapStruct(int id)
{
	return &mygs->world[id];
}

_MLF void mapSave(int p0)
{
	mygs->compressInto(p0);
}

_MLF void mapCompleteSave(int id)
{
	char filename[32];
	sprintf(filename,"serverdata/maps/map%d.dat",id);
	cMap temp=mygs->world[id];
	temp.setAllVacant();
	saveData(&temp,sizeof(cMap),filename);
	newLine("map %d saved.\n",id);
}

_MLF int itemLen()
{
	return mygs->ml_items.item.size();
}
_MLF cItem *itemStruct(int id)
{
	return &mygs->ml_items.item[id];
}
_MLF void itemSave(int id)
{
	if(mygs->ml_items.item[id].qty==0)
		mygs->removeItem( id );
	else
		mygs->updateItem( id );
}

_MLF void itemInsert(int id)
{
	if(mygs->ml_items.item[id].owner==-1)
		mygs->mydb.insertItem(&mygs->ml_items.item[id]);
	else
		mygs->mydb.insertItem(&mygs->ml_items.item[id],mygs->player[mygs->ml_items.item[id].owner].id);
}

_MLF void itemDelete(int id)
{
	mygs->removeItem(id);
}

_MLF int playerTemplateLen()
{
	return mygs->mnl.size();
}
_MLF cPlayer *playerTemplateStruct(int id)
{
	if(id<0 || id>mygs->mnl.size())
		return 0;
	return &mygs->mnl[id];
}

_MLF int itemTemplateLen()
{
	return mygs->mil.size();
}
_MLF cItem *itemTemplateStruct(int id)
{
	if(id<0 || id>mygs->mil.size())
		return 0;
	return &mygs->mil[id];
}

_MLF int mapListLen(int p0)
{
	return(mygs->map_bucket[p0].size());
}

_MLF int mapList(int p0,int p1)
{
	return(mygs->map_bucket[p0][p1]);
}

_MLF int inventoryLen()
{
	return MAX_INV;
}

_MLF int inventoryItem(int id, int slot)
{
	return mygs->player[id].inventory[slot];
}

_MLF int runScript(int p0,int p1)
{
	if(p1<0)
		mygs->mlscript.run(p0,mygs->mlscript.getPlayer());
		//mygs->eHandler.add(p0,mygs->mlscript.getPlayer(),0);
	else
		return mygs->eHandler.add(p0,mygs->mlscript.getPlayer(),p1);
	return -1;
}

_MLF int runScriptAs(int p0,int p1,int p2)
{
	if(p1<0)
		mygs->mlscript.run(p0,p2);
		//mygs->eHandler.add(p0,p2,0);
	else
		return mygs->eHandler.add(p0,p2,p1);
	return -1;
}

_MLF void haltScript(int p0)
{
	mygs->eHandler.halt(p0);
}

//messages

_MLF void sendPlayerUpdate(int id)
{
	mygs->sendPlyrMsg(id);
}
_MLF void sendMapUpdate(int p0)
{
	//loop through players on map and send new map
	for(int k=0;k<mygs->map_bucket[p0].size();k++)if( mygs->player[mygs->map_bucket[p0][k]].type!=NPC)
		mygs->sendUpldMsg(mygs->itod(mygs->map_bucket[p0][k]),p0);
	mygs->world[p0].version++;
}

_MLF void sendAttribute(int id)
{
	mygs->sendAttrMsg(mygs->player[id].pid,id);
}
_MLF void sendLevel(int id)
{
	mygs->sendLevlMsg(mygs->player[id].pid,id);
}
_MLF void sendPosition(int id)
{
	mygs->sendMycrMsg(mygs->player[id].pid,id);
}
_MLF void sendAccess(int id)
{
	mygs->sendAcssMsg(mygs->player[id].pid,id);
}
_MLF void sendMap(int id,int mapid)
{
	mygs->sendUpldMsg(mygs->player[id].pid,mapid);
}
_MLF void sendEquip(int id)
{
	mygs->sendEquipMsg(id);
}
_MLF void sendHP(int id)
{
	mygs->sendHPMsg(id);
}
_MLF void sendMP(int id)
{
	mygs->sendMPMsg(id);
}
_MLF void sendEXP(int id)
{
	mygs->sendEXPMsg(id);
}
_MLF void sendShade(int id,unsigned char shade)
{
	mygs->sendShade(mygs->player[id].pid,shade);
}
_MLF void sendHPbar(int map,unsigned short id)
{
	mygs->sendHPbar(map,id);
}
_MLF void sendAddMapItem(int graphic,int map,int x,int y)
{
	mygs->sendAddMapItem(graphic,map,x,y);
}
_MLF void sendRemoveMapItem(int map,int x,int y)
{
	mygs->sendRemoveMapItem(map,x,y);
}
_MLF void sendInventoryQty(int id,signed short index,signed long quantity)
{
	mygs->sendInventoryQty(mygs->player[id].pid,index,quantity);
}
_MLF void sendInventoryAdd(int id,unsigned short graphic,char *name,unsigned char index,unsigned long quantity)
{
	mygs->sendInventoryAdd(mygs->player[id].pid,graphic,name,index,quantity);
}

_MLF void sendPlayerList(int index)
{
	mygs->sendPlayerVMsg(index);
}
_MLF void sendItemList(int index)
{
	mygs->sendItemVMsg(index);
}

_MLF void sendChatf(int p0,char *p1,...)
{
	char		text[1024];							// Holds Our String
	va_list		ap;									// Pointer To List Of Arguments
	if (p1 == NULL)
		return;
	// Parse The String For Variables
	va_start(ap, p1);							
	vsprintf(text, p1, ap);
	va_end(ap);

	if(p0<0)
		mygs->sendChatMsg(ALL_CLIENTS,text);
	else if(mygs->player[p0].type==PLAYER && mygs->player[p0].access>0)
		mygs->sendChatMsg(mygs->itod(p0),text);
}

_MLF void sendChat(char *p0,int p1)
{
	if(p1<0)
		mygs->sendChatMsg(ALL_CLIENTS,p0);
	else if(p1<mygs->player.size() && mygs->player[p1].type==PLAYER && mygs->player[p1].access>0)
		mygs->sendChatMsg(mygs->itod(p1),p0);
}

_MLF void sendMapChat(char *p0,int p1)
{
	if(p1>=0 && p1<mygs->world.size())
		for(int c=0;c<mygs->map_bucket[p1].size();c++)
			if(mygs->player[mygs->map_bucket[p1][c]].type==PLAYER)
				mygs->sendChatMsg(mygs->itod(mygs->map_bucket[p1][c]),p0);
}

_MLF void sendMapChatf(int p0,char *p1,...)
{
	char		text[256];							// Holds Our String
	va_list		ap;									// Pointer To List Of Arguments
	if (p1 == NULL)
		return;
	// Parse The String For Variables
	va_start(ap, p1);							
	vsprintf(text, p1, ap);
	va_end(ap);
	if(p0>=0 && p0<mygs->world.size())
		for(int c=0;c<mygs->map_bucket[p0].size();c++)
			if(mygs->player[mygs->map_bucket[p0][c]].type==PLAYER)
				mygs->sendChatMsg(mygs->itod(mygs->map_bucket[p0][c]),text);
}

_MLF int levelUpExp(int lvl)
{
	return int(100*(lvl*lvl));
}

_MLF void disconnectPlayer(int id)
{
	mygs->nh.disconnect(mygs->player[id].pid);
}

//old functions


_MLF int getPlayerType(int p0)
{
	int id=p0;
	if(id>-1 && id<mygs->player.size())
		return ( mygs->player[id].type );
	else 
		return(0);
}
_MLF int getMaxPlayers()
{
	return(mygs->player.size());	
}
_MLF int isConnected(int p0)
{
	if(mygs->player[p0].access>0)
		return(1);
	else
		return(0);
}

_MLF int getTile(int p0,int p1,int p2,int p3)
{
	return ( mygs->world[p0].map[p2][p1].tile[p3] );
}
_MLF int getTileType(int p0,int p1,int p2)
{
	return ( mygs->world[p0].map[p2][p1].type );
}
_MLF void setTile(int p0,int p1,int p2,int p3,int p4)
{
	mygs->world[p0].map[p2][p1].tile[p3] = p4;
}
_MLF void setTileType(int p0,int p1,int p2,int p3)
{
	mygs->world[p0].map[p2][p1].type = p3;
}
_MLF void setTileWarp(int p0,int p1,int p2,int p3,int p4,int p5)
{
	mygs->world[p0].map[p2][p1].warp.map = p3;
	mygs->world[p0].map[p2][p1].warp.x = p4;
	mygs->world[p0].map[p2][p1].warp.y = p5;
}
_MLF void setTileScript(int p0,int p1,int p2,int p3)
{
	mygs->world[p0].map[p2][p1].warp.map = p3;
}
_MLF int inBounds(int p0,int p1)
{
	pos ps;
	ps.x = p0; 
	ps.y = p1;
	if(ps.inBounds())
		return ( 1 );
	else
		return ( 0 );
}


_MLF void dropItem(int id, int slot, int qty = -1)
{
	if(qty != -1)
	{
		mygs->doDrop(id, slot, qty);
	}
	else
	{
		mygs->doDrop(id, slot);
	}
}

_MLF void pickupItem(int id)
{
	mygs->doPickup(id);
}

_MLF int getID(int p0,int p1,int p2)
{
	if(inBounds(p1,p2))
	{
		return ( mygs->world[p0].map[p2][p1].space );
	}
	else
	{
		newLine("Attempted to fetch an ID out of map boundaries in script %d", myScript());
		return -1;
	}
}
//effects
_MLF void makeEffect(int p0,int p1,int p2,int p3)
{
	mygs->sendEffect(p0,p1,p2,p3);
}

_MLF int maxInv()
{
	return ( MAX_INV );
}

//player stuff
_MLF int getLvl(int p0)
{
	if(p0 >= 0 && p0 < mygs->player.size())
		return(mygs->player[p0].lvl);
	return -1;
}

_MLF int getAccess(int p0)
{
	if(p0 >= 0 && p0 < mygs->player.size())
		return(mygs->player[p0].access);
	return -1;
}

_MLF int getStr(int p0)
{
	if(p0 >= 0 && p0 < mygs->player.size())
		return(mygs->player[p0].str);
	return -1;
}

_MLF int getCon(int p0)
{
	if(p0 >= 0 && p0 < mygs->player.size())
		return(mygs->player[p0].con);
	return -1;
}

_MLF int getDex(int p0)
{
	if(p0 >= 0 && p0 < mygs->player.size())
		return(mygs->player[p0].dex);
	return -1;
}

_MLF int getInt(int p0)
{
	if(p0 >= 0 && p0 < mygs->player.size())
		return(mygs->player[p0].itl);
	return -1;
}

_MLF int getWis(int p0)
{
	if(p0 >= 0 && p0 < mygs->player.size())
		return(mygs->player[p0].wis);
	return -1;
}

_MLF int getBody(int p0)
{
	if(p0 >= 0 && p0 < mygs->player.size())
		return(mygs->player[p0].body);
	return -1;
}

_MLF int getClothes(int p0)
{
	if(p0 >= 0 && p0 < mygs->player.size())
		return(mygs->player[p0].clothes);
	return -1;
}

_MLF int getHair(int p0)
{	
	if(p0 >= 0 && p0 < mygs->player.size())
		return(mygs->player[p0].hair);
	return -1;
}

_MLF void setHP(int p0,int p1)
{
	if(p0 > -1 && p0 < playerLen())
	{
		int protect=0;
		if(mygs->player[p0].type==PLAYER && (mygs->player[p0].lvl<mygs->newbieLevel || mygs->player[p0].state==2 ))
			protect=1;
		if(!protect || mygs->player[p0].hp<p1)
		{
			if(p1<0)
				mygs->player[p0].hp = 0;
			else
				mygs->player[p0].hp = p1;
			if(mygs->player[p0].hp > mygs->player[p0].mhp)
				mygs->player[p0].hp = mygs->player[p0].mhp;

			if(mygs->player[p0].type==PLAYER)
				mygs->sendHPMsg(p0);
		}
		if(!protect && mygs->player[p0].hp>=p1)//set target
		{
			mygs->player[p0].target = mygs->mlscript.getPlayer();
			mygs->sendHPbar(mygs->player[p0].map,p0);		
		}
	}
	else if (p0 <= -1)
	{
		newLine("Attempted to set the HP of a player ID below 0 in script %d", myScript());
	}
	else
	{
		newLine("Attempted to set the HP of a player ID above the length of the player list in script %d", myScript());
	}
}

_MLF int getHP(int p0)
{
	return ( mygs->player[p0].hp );
}

_MLF void setMP(int p0,int p1)
{
	mygs->player[p0].mp = p1;
	if(mygs->player[p0].mp < 0)
		mygs->player[p0].mp = 0;
	if(mygs->player[p0].mp > mygs->player[p0].mmp)
		mygs->player[p0].mp = mygs->player[p0].mmp;
	if(mygs->player[p0].type==PLAYER)
		mygs->sendMPMsg(p0);
}

_MLF int getMP(int p0)
{
	return ( mygs->player[p0].mp );
}

_MLF int getMaxHP(int p0)
{
	return ( mygs->player[p0].mhp );
}
_MLF int getMaxMP(int p0)
{
	return ( mygs->player[p0].mmp );
}
_MLF int getDir(int p0)
{
	
	return ( mygs->player[p0].dir );
	
}

_MLF int getImg(int p0)
{	
	return ( mygs->player[p0].sprite );
}

_MLF int getAtk(int p0)
{
	return ( mygs->player[p0].atk );	
}

_MLF void setPos(int p0,int p1,int p2,int p3)
{
	int id=p0;
	int nm=p1;
	int nx=p2;
	int ny=p3;
	if(id>=0 && id<mygs->player.size() && mygs->player[id].access>0&&nx<MAP_COLS&&nx>=0&&ny>=0&&ny<MAP_ROWS&&nm>=0&&nm<mygs->world.size())
	{
		mygs->world[mygs->player[id].map].map[mygs->player[id].y][mygs->player[id].x].space=VACANT;
		mygs->player[id].map = nm;
		mygs->player[id].x = nx;
		mygs->player[id].y = ny;
		mygs->world[mygs->player[id].map].map[mygs->player[id].y][mygs->player[id].x].space=id;
		if(mygs->player[id].type==PLAYER)
			mygs->sendMycrMsg(mygs->itod(id),id);
	}
}
_MLF int getMap(int p0)
{
	return ( mygs->player[p0].map );
}
_MLF int getX(int p0)
{
	return ( mygs->player[p0].x );
}
_MLF int getY(int p0)
{
	return ( mygs->player[p0].y );
}

_MLF void giveExp(int p0,int p1)
{
	mygs->player[p0].exp+=p1;
}

_MLF int getExp(int p0)
{
	return ( mygs->player[p0].exp );
}

_MLF int damage(int p0)
{
	return ( mygs->player[p0].atk );
}

_MLF int magicDamage(int p0)
{
	return ( mygs->player[p0].itl + mygs->player[p0].wis/3 );
	
	return 0;
}

//misc
_MLF int getRand(int p0)
{
	return ( rand()%p0 );
}


_MLF char *strCat(char *p0,char *p1)
{
	sprintf(scriptGlobalString,"%s%s",p0,p1);
	return ( scriptGlobalString );
}

_MLF int strCon(char * p0,char * p1)
{
	if( strstr(p0,p1)!=NULL )
		return ( 1 );
	else
		return ( 0 );
}

_MLF void setOrigin(int p0,int p1,int p2,int p3)
{
	mygs->player[p0].origin_map=p1;
	mygs->player[p0].origin_x=p2;
	mygs->player[p0].origin_y=p3;
}

_MLF void getOrigin(int p0,int &p1,int &p2,int &p3)
{
	p1=mygs->player[p0].origin_map;
	p2=mygs->player[p0].origin_x;
	p3=mygs->player[p0].origin_y;
}

_MLF void setBounty(int p0,int p1)
{
	mygs->player[p0].worth=p1;
	if(mygs->player[p0].worth<0)
		mygs->player[p0].worth=0;
	if(mygs->player[p0].type==PLAYER)
		mygs->sendPlyrMsg(p0);
}

_MLF void setImg(int p0,int p1)
{
	mygs->player[p0].sprite=p1;
mygs->	sendPlyrMsg(p0);
}

_MLF void setBody(int p0,int p1)
{
	mygs->player[p0].body=p1;
	mygs->sendPlyrMsg(p0);
}

_MLF void setClothes(int p0,int p1)
{
	mygs->player[p0].clothes=p1;
	mygs->sendPlyrMsg(p0);	
}

_MLF void setHair(int p0,int p1)
{
	mygs->player[p0].hair=p1;
	mygs->sendPlyrMsg(p0);
}

_MLF char *getName(int p0)
{
	return(mygs->player[p0].name);
}

_MLF void setTarget(int p0,int p1)
{
	if(mygs->player[p0].type==NPC)
		mygs->player[p0].target = p1;
}


_MLF char *stringLower(char * p0)
{
	strcpy(scriptGlobalString,p0);
	strlwr(scriptGlobalString);
	return(scriptGlobalString);
}


_MLF int stoi(char *p0)
{
	int num;
	sscanf(p0,"%d",&num);
	return num;
}

_MLF char *itos(int p0)
{
	sprintf(scriptGlobalString,"%d",p0);
	return scriptGlobalString;
}



_MLF char *getItemName(int p0)
{
	strcpy(scriptGlobalString,mygs->mil[p0].name);
	return(scriptGlobalString);
}

_MLF int getMTarget(int p0)
{
	if(p0 >= 0 && p0 < mygs->player.size())
		return(mygs->player[p0].target_at);
	return -1;
}

_MLF int getTarget(int p0)
{	
	if(p0 >= 0 && p0 < mygs->player.size())
		return(mygs->player[p0].target);
	return -1;
}

_MLF int getBounty(int p0)
{	
	return(mygs->player[p0].worth);
}

_MLF void setMTarget(int p0,int p1)
{
	if(mygs->player[p0].type==NPC)
		mygs->player[p0].target_at=p1;
}

_MLF void setDir(int p0,int p1)
{
	mygs->player[p0].dir=p1;
	mygs->sendMycrMsg(mygs->player[p0].pid,p0);
}

_MLF void setChatScript(int p0,int p1)
{
	if(mygs->player[p0].type==NPC)
		mygs->player[p0].chat_script=p1;
}

_MLF void setMoveScript(int p0,int p1)
{
	if(mygs->player[p0].type==NPC)
		mygs->player[p0].move_script=p1;	
}

_MLF char *intToString(int p0)
{
	sprintf(scriptGlobalString,"%d",p0);
	return(scriptGlobalString);
}

_MLF int stringToInt(char * p0)
{
	int temp;
	sscanf(p0,"%d",&temp);
	return(temp);
}



_MLF char *getWord(char* p0, int p1)
{
	char* pBeginWord;
	char* pEndWord;
	int i;
	i = 0;
	pBeginWord = p0;
	while (true)
	{
		pEndWord = strchr(pBeginWord, ' ');
		if (i == p1)
			break;
		if (pEndWord == NULL)
		{
			*scriptGlobalString = '\0';
			return scriptGlobalString;
		}
		pBeginWord = pEndWord + 1;
		i++;
	}
	if (pEndWord != NULL)
		*pEndWord = '\0';
	strcpy(scriptGlobalString, pBeginWord);
	if (pEndWord != NULL)
		*pEndWord = ' ';
	return scriptGlobalString;
}

_MLF void makeSound(int p0,int p1)
{
	mygs->sendSound(p0,p1);
}

_MLF void setMapLighting(int p0,int p1)
{
	mygs->world[p0].npc[4].qty=p1;
}

_MLF int getMapLighting(int p0)
{
	return mygs->world[p0].npc[4].qty;
}

_MLF void setMapMusic(int p0,int p1)
{
	mygs->world[p0].npc[4].index=p1;
}

_MLF int getMapMusic(int p0)
{
	return mygs->world[p0].npc[4].index;
}

_MLF void setMapLink(int p0,int p1,int p2)
{
	if(p1==0)
		mygs->world[p0].s=p2;
	else if(p1==1)
		mygs->world[p0].n=p2;
	else if(p1==2)
		mygs->world[p0].w=p2;
	else if(p1==3)
		mygs->world[p0].e=p2;
}

_MLF int getMapLink(int p0,int p1)
{
	if(p1==0)
		return mygs->world[p0].s;
	if(p1==1)
		return mygs->world[p0].n;
	if(p1==2)
		return mygs->world[p0].w;
	return mygs->world[p0].e;
}
_MLF int updateMap(int p0)
{
	return 0;
}
