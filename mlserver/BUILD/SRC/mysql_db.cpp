#ifndef _MYSQLDBSRC_
#define _MYSQLDBSRC_

#include "mysql_db.h"

mysqlDB::mysqlDB()
{
	db = 0;
}

void mysqlDB::runScript(char *filename)
{
	char query[10000];
	FILE *f=fopen(filename,"r");
	if(f==NULL)
		return;
	fseek(f,0,SEEK_END);
	int size = ftell(f);
	rewind(f);
	fread(query,size,1,f);
	fclose(f);
	for(int i=0;i<size;i++)
		if(query[i]=='\n')
			query[i]=' ';
	int mark=0;
	for(i=0;i<size;i++)
		if(query[i]==';')
		{
			mysql_real_query(pConnection,&query[mark],i-mark);
			mark=i+2;
		}
}

int mysqlDB::connect()
{
	int rc;
	rc = sqlite3_open_v2("mldb", &db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL);
	if (rc)
		return false;
	runScript("serverdata/mlegends.sql");
	return true;
}

void mysqlDB::disconnect()
{
	sqlite_close(db);
	db = 0;
}

int mysqlDB::createAccount(char *id,char *pass,char *email,char *ip)
{
	char *zSQL = sqlite3_mprintf("INSERT INTO accounts (accid, pass, email, ip) VALUES ('%s', '%s', '%s', '%s'", id, pass, email, ip);
	sqlite3_exec(db, zSQL, 0, 0, 0);
	sqlite3_free(zSQL);
	return 1;
}

int mysqlDB::emailExists(char *email)
{
	int numRows;
	char *zSQL = sqlite3_mprintf("SELECT * FROM accounts WHERE email = '%s'", email);
	sqlite3_get_table(db, zSQL, NULL, &numRows, NULL, NULL);
	sqlite3_free(zSQL);
	
	return (numRows > 0);
}

int mysqlDB::accountExists(char *id)
{
	int numRows;
	char *zSQL = sqlite3_mprintf("SELECT * FROM accounts WHERE accid='%s'",id);
	sqlite3_get_table(db, zSQL, NULL, &numRows, NULL, NULL);
	sqlite3_free(zSQL);
	
	return (numRows > 0);
}

int mysqlDB::createPlayer(char *name,int body,int clothes,int hair,int access,int map,int x,int y,int *player_id)
{
	char *zSQL = sqlite3_mprintf("INSERT INTO players (name,body,clothes,hair,sprite,access,create_date,origin_map,origin_x,origin_y) VALUES ('%s',%d,%d,%d,%d,%d,NOW(),%d,%d,%d)",
		name,
		body,
        clothes, 
		hair,
		0,
		access,
		map,
		x,
		y);
	sqlite3_get_table(db, zSQL, NULL, &numRows, NULL, NULL);
	sqlite3_free(zSQL);

	*player_id = (int)sqlite3_last_insert_rowid(db);
	return 1;
}

void mysqlDB::deletePlayer(int id)//STRUCTUREFLAG
{
	char *zSQL;

	sqlite3_mprintf("DELETE FROM players WHERE id='%d'",id);
	sqlite3_get_table(db, zSQL, NULL, &numRows, NULL, NULL);
	sqlite3_free(zSQL);

	sqlite3_mprintf("DELETE FROM items WHERE owner='%d'",id);
	sqlite3_get_table(db, zSQL, NULL, &numRows, NULL, NULL);
	sqlite3_free(zSQL);

	sqlite3_mprintf("UPDATE accounts SET char1=-1 WHERE char1=%d",id);
	sqlite3_get_table(db, zSQL, NULL, &numRows, NULL, NULL);
	sqlite3_free(zSQL);

	sqlite3_mprintf("UPDATE accounts SET char2=-1 WHERE char2=%d",id);
	sqlite3_get_table(db, zSQL, NULL, &numRows, NULL, NULL);
	sqlite3_free(zSQL);

	sqlite3_mprintf("UPDATE accounts SET char3=-1 WHERE char3=%d",id);
	sqlite3_get_table(db, zSQL, NULL, &numRows, NULL, NULL);
	sqlite3_free(zSQL);

	sqlite3_mprintf("UPDATE accounts SET char4=-1 WHERE char4=%d",id);
	sqlite3_get_table(db, zSQL, NULL, &numRows, NULL, NULL);
	sqlite3_free(zSQL);

}

void mysqlDB::updatePlayer(const cPlayer *player)
{
	sqlite3_mprintf("UPDATE players SET x=%d,y=%d,map=%d,direction=%d,type=%d,state=%d,range=%d,str=%d,dex=%d,con=%d,itl=%d,wis=%d,access=%d,eLeft=%d,eRight=%d,eHead=%d,eBody=%d,eSpecial=%d,level=%d,template=%d,sprite=%d,body=%d,hair=%d,clothes=%d,worth=%d,atk=%d,def=%d,train=%d,hp=%d,mhp=%d,mp=%d,mmp=%d,target=%d,target_at=%d,chat_script=%d,move_script=%d,exp=%d,flags=%d,origin_x=%d,origin_y=%d,origin_map=%d,name='%s',title='%s',boot_time=%d,serenity=%d,unknown=%d,logout_date=NOW() WHERE id=%d",
		player->x,
		player->y,
		player->map,
		player->dir,
		player->type,
		player->state,
		player->range,
		player->str,
		player->dex,
		player->con,
		player->itl,
		player->wis,
		player->access,
		player->eLeft,
		player->eRight,
		player->eHead,
		player->eBody,
		player->eSpecial,
		player->lvl,
		player->player_template,
		player->sprite,
		player->body,
		player->hair,
		player->clothes,
		player->worth,
		player->atk,
		player->def,
		player->train,
		player->hp,
		player->mhp,
		player->mp,
		player->mmp,
		player->target,
		player->target_at,
		player->chat_script,
		player->move_script,
		player->exp,
		player->flags,
		player->origin_x,
		player->origin_y,
		player->origin_map,
		player->name,
		player->title,
		player->boot_time,
		player->serenity,
		player->unknown,
		player->id);
	sqlite3_get_table(db, zSQL, NULL, &numRows, NULL, NULL);
	sqlite3_free(zSQL);

}

void mysqlDB::updateCorePlayer(const cPlayer *player)
{
	char query[5000];//STRUCTUREFLAG
	sqlite3_mprintf("UPDATE players SET x=%d,y=%d,map=%d,direction=%d,hp=%d,mp=%d,exp=%d,logout_date=NOW(),total_time=(total_time+10) WHERE id=%d",
		player->x,
		player->y,
		player->map,
		player->dir,
		player->hp,
		player->mp,
		player->exp,
		player->id);
	sqlite3_get_table(db, zSQL, NULL, &numRows, NULL, NULL);
	sqlite3_free(zSQL);

}

void mysqlDB::updateEquipPlayer(const cPlayer *player)
{
	sqlite3_mprintf("UPDATE players SET eLeft=%d,eRight=%d,eHead=%d,eBody=%d,eSpecial=%d WHERE id=%d",
		player->eLeft,
		player->eRight,
		player->eHead,
		player->eBody,
		player->eSpecial,
		player->id);
	sqlite3_get_table(db, zSQL, NULL, &numRows, NULL, NULL);
	sqlite3_free(zSQL);
}

int mysqlDB::nameExists(char *name)
{
	int numRows;
	char *zSQL = sqlite3_mprintf("SELECT id FROM players WHERE name='%s'",name);
	sqlite3_get_table(db, zSQL, NULL, &numRows, NULL, NULL);
	sqlite3_free(zSQL);
	
	return (numRows > 0);
}

int mysqlDB::numPlayerAccounts()
{
	int numRows;
	sqlite3_get_table(db, "SELECT * FROM players", NULL, &numRows, NULL, NULL);
	
	return numRows;
}

int mysqlDB::numAccounts()
{
	int numRows;
	sqlite3_get_table(db, "SELECT * FROM accounts", NULL, &numRows, NULL, NULL);
	
	return numRows;
}

void mysqlDB::updateItem(cItem *item)
{
	if(item->qty==0)
	{
		removeItem(item->id);
		return;
	}
	char *zSQL = sqlite3_mprintf("UPDATE items SET life=%d,quantity=%d,graphic=%d,name='%s',map=%d,x=%d,y=%d,owner=%d,slot=%d,type=%d,stack=%d,flags=%d,uses=%d,use_script=%d,equip_script=%d,unequip_script=%d,pickup_script=%d,drop_script=%d,lose_script=%d,atk=%d,def=%d,template=%d,bonus=%d,bonus2=%d,userdata=%d,userdata2=%d,total_cooldown=%d,weight = %f WHERE id=%d",
	 	item->life,
		item->qty,
		item->graphic,
		item->name,
		item->map,
		item->x,
		item->y,
		item->owner,
		item->slot,
		item->type,
		item->stack,
		item->flags,
		item->uses,
		item->use_script,
		item->equip_script,
		item->unequip_script,
		item->pickup_script,
		item->drop_script,
		item->lose_script,
		item->atk,
		item->def,
		item->item_template,
		item->bonus,
		item->bonus2,
		item->userdata,
		item->userdata2,
		item->total_cooldown,
		item->weight,
		item->id);
	sqlite3_get_table(db, zSQL, NULL, &numRows, NULL, NULL);
	sqlite3_free(zSQL);
}

void mysqlDB::removeItem(int permid)
{
	int numRows;
	char *zSQL = sqlite3_mprintf("DELETE FROM items WHERE id='%d'",permid);
	sqlite3_get_table(db, zSQL, NULL, &numRows, NULL, NULL);
	sqlite3_free(zSQL);
}

void mysqlDB::insertItem(cItem *item,int perm_owner)
{
	int old = item->owner;
	item->owner=perm_owner;

	if(item->qty==0)
		return;
	char *zSQL = sqlite3_mprintf("INSERT INTO items(life, quantity, graphics, name, map, x, y, owner, slot, type, stack, flags, uses, use_script,
	equip_script, unequip_script, pickup_script, drop_script, lose_script, atk, def, template, bonus, bonus2, userdata, userdata2, total_cooldown,
	weight) VALUES(%d,%d,%d,'%s',%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%f)",
	 	item->life,
		item->qty,
		item->graphic,
		item->name,
		item->map,
		item->x,
		item->y,
		item->owner,
		item->slot,
		item->type,
		item->stack,
		item->flags,
		item->uses,
		item->use_script,
		item->equip_script,
		item->unequip_script,
		item->pickup_script,
		item->drop_script,
		item->lose_script,
		item->atk,
		item->def,
		item->item_template,
		item->bonus,
		item->bonus2,
		item->userdata,
		item->userdata2,
		item->total_cooldown,
		item->weight,
		item->id);
	sqlite3_get_table(db, zSQL, NULL, &numRows, NULL, NULL);
	sqlite3_free(zSQL);

	item->owner=old;
}

void mysqlDB::updateGlobal(char *name,char *value)
{
	char *zSQL = sqlite3_mprintf("UPDATE globals SET value='%s' WHERE name='%s'",value,name);
	sqlite3_exec(db, zSQL, 0, 0, 0);
	sqlite3_free(zSQL);
}

void mysqlDB::insertGlobal(char *name,char *value)
{
	char *zSQL = sqlite3_mprintf("INSERT INTO globals (name,value) VALUES ('%s','%s')",name,value);
	sqlite3_exec(db, zSQL, 0, 0, 0);
	sqlite3_free(zSQL);
}

void mysqlDB::deleteGlobal(char *name)
{
	char *zSQL = sqlite3_mprintf("DELETE FROM globals WHERE name='%s'",name);
	sqlite3_exec(db, zSQL, 0, 0, 0);
	sqlite3_free(zSQL);
}

char *mysqlDB::selectGlobal(char *name)
{
/*	char query[1024];
	strcpy(mystring,"");
	sprintf(query, "SELECT value FROM globals WHERE name='%s'",name);
	if(mysql_query(pConnection, query) != 0)
		return mystring;
	res = mysql_store_result(pConnection);
	if(!(int)mysql_num_rows(res))
		return mystring;
	row=mysql_fetch_row(res);
	strcpy(mystring,row[0]);
	mysql_free_result(res);
	return mystring;*/ 
}

bool mysqlDB::isGlobal(char *name)
{
	/*char query[1024];
	sprintf(query, "SELECT id FROM globals WHERE name='%s'",name);

	if(mysql_query(pConnection, query) != 0)
		return 0;
	
	res = mysql_store_result(pConnection);

	int num= (int)mysql_num_rows(res);

	mysql_free_result(res);
	if(num>0)
		return 1;
	return 0;*/
}

void mysqlDB::loadMapItems(cItemList *itemlist)
{
/*	char query[1024];
	sprintf(query, "SELECT * FROM items WHERE map != -1");

	if(mysql_query(pConnection, query) != 0)
		return;

	res = mysql_store_result(pConnection);

	cItem item;
	while(row=mysql_fetch_row(res))//STRUCTUREFLAG
	{
		int i=0;
		item.id=atoi(row[i++]);
		item.life=atoi(row[i++]);
		item.qty=atoi(row[i++]);
		item.graphic=atoi(row[i++]);
		strcpy(item.name,row[i++]);
		item.map=atoi(row[i++]);
		item.x=atoi(row[i++]);
		item.y=atoi(row[i++]);
		item.owner=atoi(row[i++]);
		item.slot=atoi(row[i++]);
		item.type=atoi(row[i++]);
		item.stack=atoi(row[i++]);
		item.flags=atoi(row[i++]);
		item.uses=atoi(row[i++]);
		item.use_script=atoi(row[i++]);
		item.equip_script=atoi(row[i++]);
		item.unequip_script=atoi(row[i++]);
		item.pickup_script=atoi(row[i++]);
		item.drop_script=atoi(row[i++]);
		item.lose_script=atoi(row[i++]);
		item.atk=atoi(row[i++]);
		item.def=atoi(row[i++]);
		item.item_template=atoi(row[i++]);
		item.bonus=atoi(row[i++]);
		item.bonus2=atoi(row[i++]);
		item.userdata=atoi(row[i++]);
		item.userdata2=atoi(row[i++]);
		item.total_cooldown=atoi(row[i++]);
		item.weight = atof(row[i++]);
		//item.pDataSize=atoi(row[i++]);
		//memcpy(item.pData,row[i++],item.pDataSize);
		itemlist->addItem(item);
	}
	mysql_free_result(res);*/
}

void mysqlDB::loadPlayerItems(int id,int tempid,cItemList *itemlist)
{
	/*char query[1024];
	sprintf(query, "SELECT * FROM items WHERE owner = %d",id);

	if(mysql_query(pConnection, query) != 0)
		return;

	res = mysql_store_result(pConnection);

	cItem item;
	int i;
	while(row=mysql_fetch_row(res))//STRUCTUREFLAG
	{
		i=0;
		item.id=atoi(row[i++]);
		item.life=atoi(row[i++]);
		item.qty=atoi(row[i++]);
		item.graphic=atoi(row[i++]);
		strcpy(item.name,row[i++]);
		item.map=atoi(row[i++]);
		item.x=atoi(row[i++]);
		item.y=atoi(row[i++]);
		item.owner=atoi(row[i++]); 
		item.slot=atoi(row[i++]);
		item.type=atoi(row[i++]);
		item.stack=atoi(row[i++]);
		item.flags=atoi(row[i++]);
		item.uses=atoi(row[i++]);
		item.use_script=atoi(row[i++]);
		item.equip_script=atoi(row[i++]);
		item.unequip_script=atoi(row[i++]);
		item.pickup_script=atoi(row[i++]);
		item.drop_script=atoi(row[i++]);
		item.lose_script=atoi(row[i++]);
		item.atk=atoi(row[i++]);
		item.def=atoi(row[i++]);
		item.item_template=atoi(row[i++]);
		item.bonus=atoi(row[i++]);
		item.bonus2=atoi(row[i++]);
		item.userdata=atoi(row[i++]);
		item.userdata2=atoi(row[i++]);
		item.total_cooldown=atoi(row[i++]);
		item.weight =atof(row[i++]);
		//item.pDataSize=atoi(row[i++]);
		//memcpy(item.pData,row[i++],item.pDataSize);
		if(item.owner!=id)
			printf("***ITEM MISMATCH: mysql id %d received item from id %d\n",id,item.owner);
		else
		{
			item.owner = tempid;
			itemlist->addItem(item);
		}
	}
	mysql_free_result(res); */
}

int mysqlDB::loadPlayer(cPlayer *player,int slot)
{
	//obtain player id from account's slot
	/*char query[1024];
	sprintf(query, "SELECT * FROM accounts WHERE accid='%s'",player->accid);

	if(mysql_query(pConnection, query) != 0)
		return 0;

	res = mysql_store_result(pConnection);

	int num = (int)mysql_num_rows(res);
	if(num!=1)
		return 0;

	int player_id;
	if(row=mysql_fetch_row(res))//STRUCTUREFLAG
		player_id = atoi(row[slot+6]);	
	else
	{
		mysql_free_result(res);
		return 0;
	}
	mysql_free_result(res);

	sprintf(query, "SELECT * FROM players WHERE id=%d",player_id);

	if(mysql_query(pConnection, query) != 0)
		return 0;

	res = mysql_store_result(pConnection);

	num= (int)mysql_num_rows(res);
	if(num!=1)
		return 0;

	if(row=mysql_fetch_row(res))//STRUCTUREFLAG
	{
		int i=0;
		player->id=atoi(row[i++]);
		player->x=atoi(row[i++]);
		player->y=atoi(row[i++]);
		player->map=atoi(row[i++]);
		player->dir=atoi(row[i++]);
		player->type=atoi(row[i++]);
		player->state=atoi(row[i++]);
		player->range=atoi(row[i++]);
		player->str=atoi(row[i++]);
		player->dex=atoi(row[i++]);
		player->con=atoi(row[i++]);
		player->itl=atoi(row[i++]);
		player->wis=atoi(row[i++]);
		player->access=atoi(row[i++]);
		player->eLeft=atoi(row[i++]);
		player->eRight=atoi(row[i++]);
		player->eHead=atoi(row[i++]);
		player->eBody=atoi(row[i++]);
		player->eSpecial=atoi(row[i++]);
		player->lvl=atoi(row[i++]);
		player->player_template=atoi(row[i++]);
		player->sprite=atoi(row[i++]);
		player->body=atoi(row[i++]);
		player->hair=atoi(row[i++]);
		player->clothes=atoi(row[i++]);
		player->worth=atoi(row[i++]);
		player->atk=atoi(row[i++]);
		player->def=atoi(row[i++]);
		player->train=atoi(row[i++]);
		player->hp=atoi(row[i++]);
		player->mhp=atoi(row[i++]);
		player->mp=atoi(row[i++]);
		player->mmp=atoi(row[i++]);
		player->target=atoi(row[i++]);
		player->target_at=atoi(row[i++]);
		player->chat_script=atoi(row[i++]);
		player->move_script=atoi(row[i++]);
		player->exp=atoi(row[i++]);
		player->flags=atoi(row[i++]);
		player->origin_x=atoi(row[i++]);
		player->origin_y=atoi(row[i++]);
		player->origin_map=atoi(row[i++]);
		strcpy(player->name,row[i++]);
		strcpy(player->title,row[i++]);
		strcpy(player->create_date,row[i++]);
		strcpy(player->login_date,row[i++]);
		strcpy(player->logout_date,row[i++]);
		player->total_time=atoi(row[i++]);
		player->boot_time=atoi(row[i++]);
		player->serenity=atoi(row[i++]);
		player->unknown=atoi(row[i++]);
	}
	else
		return 0;

	mysql_free_result(res);

	//update login_time
	sprintf(query,"UPDATE players SET login_date=NOW() WHERE id=%d",player->id);
	mysql_query(pConnection,query);
	return 1;*/
}

void mysqlDB::setAccountSlot(char *id,int slot,int index)
{
	char *zSQL = sqlite3_mprintf("DELETE FROM globals WHERE name='%s'",name);
	sqlite3_exec(db, zSQL, 0, 0, 0);
	sqlite3_free(zSQL);
}

int mysqlDB::loginAccount(char *id,char *pass,char *ip)
{
/*	char query[1024];
	sprintf(query, "SELECT * FROM accounts WHERE accid='%s' AND pass='%s'",id,pass);

	if(mysql_query(pConnection, query) != 0)
		return 0;

	res = mysql_store_result(pConnection);
	
	int num= (int)mysql_num_rows(res);
	mysql_free_result(res);
	
	if(num<1)
		return 0;

	sprintf(query,"UPDATE accounts SET ip='%s' WHERE accid='%s'",ip,id);
	mysql_query(pConnection,query);

	return 1;*/
}

int mysqlDB::getAccountSlots(char *id,cPlayer *slot1,cPlayer *slot2,cPlayer *slot3,cPlayer *slot4)
{
	/*char query[1024];
	sprintf(query, "SELECT * FROM accounts WHERE accid='%s'",id);

	if(mysql_query(pConnection, query) != 0)
		return 0;

	res = mysql_store_result(pConnection);
	
	int num= (int)mysql_num_rows(res);
	
	if(num<1)
		return 0;

	int slot[4];
	//fetch character slot representations
	if(row=mysql_fetch_row(res))
	{
		slot[0]=atoi(row[6]);
		slot[1]=atoi(row[7]);
		slot[2]=atoi(row[8]);
		slot[3]=atoi(row[9]);
	}
	else
		return 0;

	mysql_free_result(res);

	if(slot[0]==-1)
		slot1->lvl=0;
	else
	{
		sprintf(query, "SELECT name,level,sprite,body,hair,clothes FROM players WHERE id=%d",slot[0]);
		mysql_query(pConnection,query);
		res = mysql_store_result(pConnection);
		row=mysql_fetch_row(res);
		strcpy(slot1->name,row[0]);
		slot1->lvl=atoi(row[1]);
		slot1->sprite=atoi(row[2]);
		slot1->body=atoi(row[3]);
		slot1->hair=atoi(row[4]);
		slot1->clothes=atoi(row[5]);
		mysql_free_result(res);
	}
	if(slot[1]==-1)
		slot2->lvl=0;
	else
	{
		sprintf(query, "SELECT name,level,sprite,body,hair,clothes FROM players WHERE id=%d",slot[1]);
		mysql_query(pConnection,query);
		res = mysql_store_result(pConnection);
		row=mysql_fetch_row(res);
		strcpy(slot2->name,row[0]);
		slot2->lvl=atoi(row[1]);
		slot2->sprite=atoi(row[2]);
		slot2->body=atoi(row[3]);
		slot2->hair=atoi(row[4]);
		slot2->clothes=atoi(row[5]);
		mysql_free_result(res);
	}
	if(slot[2]==-1)
		slot3->lvl=0;
	else
	{
		sprintf(query, "SELECT name,level,sprite,body,hair,clothes FROM players WHERE id=%d",slot[2]);
		mysql_query(pConnection,query);
		res = mysql_store_result(pConnection);
		row=mysql_fetch_row(res);
		strcpy(slot3->name,row[0]);
		slot3->lvl=atoi(row[1]);
		slot3->sprite=atoi(row[2]);
		slot3->body=atoi(row[3]);
		slot3->hair=atoi(row[4]);
		slot3->clothes=atoi(row[5]);
		mysql_free_result(res);
	}
	if(slot[3]==-1)
		slot4->lvl=0;
	else
	{
		sprintf(query, "SELECT name,level,sprite,body,hair,clothes FROM players WHERE id=%d",slot[3]);
		mysql_query(pConnection,query);
		res = mysql_store_result(pConnection);
		row=mysql_fetch_row(res);
		strcpy(slot4->name,row[0]);
		slot4->lvl=atoi(row[1]);
		slot4->sprite=atoi(row[2]);
		slot4->body=atoi(row[3]);
		slot4->hair=atoi(row[4]);
		slot4->clothes=atoi(row[5]);
		mysql_free_result(res);
	}
	return 1;*/
}

int mysqlDB::sendQuery(char *query)
{
	return mysql_query(pConnection,query);
}

#endif


