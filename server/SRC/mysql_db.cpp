#ifndef _MYSQLDBSRC_
#define _MYSQLDBSRC_

#include "mysql_db.h"

mysqlDB::mysqlDB()
{
	db = 0;
}

void mysqlDB::runScript(const char *filename)
{
	char *query;
	FILE *f=fopen(filename,"r");
	if(f==NULL)
		return;
	fseek(f,0,SEEK_END);
	unsigned int size = ftell(f);
	query = (char*)malloc(size);
	rewind(f);
	if(size != fread(query, size, 1, f)) return;
	fclose(f);
	for(unsigned int i = 0;i < size; ++i)
		if(query[i]=='\n')
			query[i]=' ';
	char *quer;
	while ((quer = strsep(&query, ";")) != NULL)
	{
		sqlite3_exec(db, quer, 0, 0, 0);
	}
	free(query);
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
int mysqlDB::GetRowCount(const char *sql)
{
	int numRows;
	int numCol;
	char *err;
	char **table;

	sqlite3_get_table(db, sql, &table, &numRows, &numCol, &err);
	sqlite3_free_table(table);
	return numRows;	
}
void mysqlDB::disconnect()
{
	sqlite3_close(db);
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
	numRows = GetRowCount(zSQL);
	sqlite3_free(zSQL);
	
	return (numRows > 0);
}

int mysqlDB::accountExists(char *id)
{
	int numRows;
	char *zSQL = sqlite3_mprintf("SELECT * FROM accounts WHERE accid='%s'",id);
	numRows = GetRowCount(zSQL);
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
	GetRowCount(zSQL);
	sqlite3_free(zSQL);

	*player_id = (int)sqlite3_last_insert_rowid(db);
	return 1;
}

void mysqlDB::deletePlayer(int id)//STRUCTUREFLAG
{
	char *zSQL;

	zSQL =sqlite3_mprintf("DELETE FROM players WHERE id='%d'",id);
	GetRowCount(zSQL);
	sqlite3_free(zSQL);

	zSQL = sqlite3_mprintf("DELETE FROM items WHERE owner='%d'",id);
	GetRowCount(zSQL);
	sqlite3_free(zSQL);

	zSQL = sqlite3_mprintf("UPDATE accounts SET char1=-1 WHERE char1=%d",id);
	GetRowCount(zSQL);
	sqlite3_free(zSQL);

	zSQL = sqlite3_mprintf("UPDATE accounts SET char2=-1 WHERE char2=%d",id);
	GetRowCount(zSQL);
	sqlite3_free(zSQL);

	zSQL = sqlite3_mprintf("UPDATE accounts SET char3=-1 WHERE char3=%d",id);
	GetRowCount(zSQL);
	sqlite3_free(zSQL);

	zSQL = sqlite3_mprintf("UPDATE accounts SET char4=-1 WHERE char4=%d",id);
	GetRowCount(zSQL);
	sqlite3_free(zSQL);

}

void mysqlDB::updatePlayer(const cPlayer *player)
{
	char *zSQL = sqlite3_mprintf("UPDATE players SET x=%d,y=%d,map=%d,direction=%d,type=%d,state=%d,range=%d,str=%d,dex=%d,con=%d,itl=%d,wis=%d,access=%d,eLeft=%d,eRight=%d,eHead=%d,eBody=%d,eSpecial=%d,level=%d,template=%d,sprite=%d,body=%d,hair=%d,clothes=%d,worth=%d,atk=%d,def=%d,train=%d,hp=%d,mhp=%d,mp=%d,mmp=%d,target=%d,target_at=%d,chat_script=%d,move_script=%d,exp=%d,flags=%d,origin_x=%d,origin_y=%d,origin_map=%d,name='%s',title='%s',boot_time=%d,serenity=%d,unknown=%d,logout_date=NOW() WHERE id=%d",
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
	GetRowCount(zSQL);
	sqlite3_free(zSQL);

}

void mysqlDB::updateCorePlayer(const cPlayer *player)
{
	char *zSQL = sqlite3_mprintf("UPDATE players SET x=%d,y=%d,map=%d,direction=%d,hp=%d,mp=%d,exp=%d,logout_date=NOW(),total_time=(total_time+10) WHERE id=%d",
		player->x,
		player->y,
		player->map,
		player->dir,
		player->hp,
		player->mp,
		player->exp,
		player->id);
	GetRowCount(zSQL);
	sqlite3_free(zSQL);

}

void mysqlDB::updateEquipPlayer(const cPlayer *player)
{
	char *zSQL = sqlite3_mprintf("UPDATE players SET eLeft=%d,eRight=%d,eHead=%d,eBody=%d,eSpecial=%d WHERE id=%d",
		player->eLeft,
		player->eRight,
		player->eHead,
		player->eBody,
		player->eSpecial,
		player->id);
	GetRowCount(zSQL);
	sqlite3_free(zSQL);
}

int mysqlDB::nameExists(char *name)
{
	int numRows;
	char *zSQL = sqlite3_mprintf("SELECT id FROM players WHERE name='%s'",name);
	numRows = GetRowCount(zSQL);
	sqlite3_free(zSQL);
	
	return (numRows > 0);
}

int mysqlDB::numPlayerAccounts()
{
	return GetRowCount("SELECT * FROM players");
}

int mysqlDB::numAccounts()
{
	return GetRowCount("SELECT * FROM accounts");
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
	GetRowCount(zSQL);
	sqlite3_free(zSQL);
}

void mysqlDB::removeItem(int permid)
{
	char *zSQL = sqlite3_mprintf("DELETE FROM items WHERE id='%d'",permid);
	GetRowCount(zSQL);
	sqlite3_free(zSQL);
}

void mysqlDB::insertItem(cItem *item,int perm_owner)
{
	int old = item->owner;
	item->owner=perm_owner;

	if(item->qty==0)
		return;
	char *zSQL = sqlite3_mprintf("INSERT INTO items(life, quantity, graphics, name, map, x, y, owner, slot, type, stack, flags, uses, use_script,"
	"equip_script, unequip_script, pickup_script, drop_script, lose_script, atk, def, template, bonus, bonus2, userdata, userdata2, total_cooldown,"
	"weight) VALUES(%d,%d,%d,'%s',%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%f)",
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
	GetRowCount(zSQL);
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
	char *zSQL = sqlite3_mprintf("SELECT value FROM globals WHERE name='%s'",name);

	int numRows;
	int numCol;
	char *err;
	char **table;

	sqlite3_get_table(db, zSQL, &table, &numRows, &numCol, &err);
	if (!numRows)
		strcpy(mystring, "");
	else
		strcpy(mystring, table[numCol + 0]);

	sqlite3_free_table(table);
	sqlite3_free(zSQL);

	return mystring;
}

bool mysqlDB::isGlobal(char *name)
{
	int numRows;
	char *zSQL = sqlite3_mprintf("SELECT id FROM globals WHERE name='%s'", name);
	numRows = GetRowCount(zSQL);
	sqlite3_free(zSQL);

	if (numRows > 0)
		return 1;
	else
		return 0;
}

void mysqlDB::loadMapItems(cItemList *itemlist)
{
	char *zSQL = sqlite3_mprintf("SELECT id, life, quantity, graphic, name, map, x, y, owner, slot, \
		type, stack, flags, uses, use_script, equip_script, unequip_script, pickup_script, drop_script, \
		lose_script, atk, def, template, bonus, bonus2, userdata, userdata2, total_cooldown, weight \
		FROM items WHERE map != -1");

	int numRows;
	int numCol;
	char *err;
	char **table;

	sqlite3_get_table(db, zSQL, &table, &numRows, &numCol, &err);

	cItem item;
	for (int r = 1; r <= numRows; ++r)
	{
		int i=0;
		item.id=atoi(table[r*numCol+i++]);
		item.life=atoi(table[r*numCol+i++]);
		item.qty=atoi(table[r*numCol+i++]);
		item.graphic=atoi(table[r*numCol+i++]);
		strcpy(item.name,table[r*numCol+i++]);
		item.map=atoi(table[r*numCol+i++]);
		item.x=atoi(table[r*numCol+i++]);
		item.y=atoi(table[r*numCol+i++]);
		item.owner=atoi(table[r*numCol+i++]);
		item.slot=atoi(table[r*numCol+i++]);
		item.type=atoi(table[r*numCol+i++]);
		item.stack=atoi(table[r*numCol+i++]);
		item.flags=atoi(table[r*numCol+i++]);
		item.uses=atoi(table[r*numCol+i++]);
		item.use_script=atoi(table[r*numCol+i++]);
		item.equip_script=atoi(table[r*numCol+i++]);
		item.unequip_script=atoi(table[r*numCol+i++]);
		item.pickup_script=atoi(table[r*numCol+i++]);
		item.drop_script=atoi(table[r*numCol+i++]);
		item.lose_script=atoi(table[r*numCol+i++]);
		item.atk=atoi(table[r*numCol+i++]);
		item.def=atoi(table[r*numCol+i++]);
		item.item_template=atoi(table[r*numCol+i++]);
		item.bonus=atoi(table[r*numCol+i++]);
		item.bonus2=atoi(table[r*numCol+i++]);
		item.userdata=atoi(table[r*numCol+i++]);
		item.userdata2=atoi(table[r*numCol+i++]);
		item.total_cooldown=atoi(table[r*numCol+i++]);
		item.weight = atof(table[r*numCol+i++]);
		//item.pDataSize=atoi(table[r*numCol+i++]);
		//memcpy(item.pData,table[r*numCol+i++],item.pDataSize);
		itemlist->addItem(item);
	}
	sqlite3_free_table(table);
	sqlite3_free(zSQL);
}

void mysqlDB::loadPlayerItems(int id,int tempid,cItemList *itemlist)
{

	char *zSQL = sqlite3_mprintf("SELECT id, life, quantity, graphic, name, map, x, y, owner, slot, \
		type, stack, flags, uses, use_script, equip_script, unequip_script, pickup_script, drop_script, \
		lose_script, atk, def, template, bonus, bonus2, userdata, userdata2, total_cooldown, weight \
		FROM items WHERE owner = %d", id);

	int numRows;
	int numCol;
	char *err;
	char **table;

	sqlite3_get_table(db, zSQL, &table, &numRows, &numCol, &err);

	cItem item;
	for (int r = 1; r <= numRows; ++r)
	{
		int i=0;
		item.id=atoi(table[r*numCol+i++]);
		item.life=atoi(table[r*numCol+i++]);
		item.qty=atoi(table[r*numCol+i++]);
		item.graphic=atoi(table[r*numCol+i++]);
		strcpy(item.name,table[r*numCol+i++]);
		item.map=atoi(table[r*numCol+i++]);
		item.x=atoi(table[r*numCol+i++]);
		item.y=atoi(table[r*numCol+i++]);
		item.owner=atoi(table[r*numCol+i++]);
		item.slot=atoi(table[r*numCol+i++]);
		item.type=atoi(table[r*numCol+i++]);
		item.stack=atoi(table[r*numCol+i++]);
		item.flags=atoi(table[r*numCol+i++]);
		item.uses=atoi(table[r*numCol+i++]);
		item.use_script=atoi(table[r*numCol+i++]);
		item.equip_script=atoi(table[r*numCol+i++]);
		item.unequip_script=atoi(table[r*numCol+i++]);
		item.pickup_script=atoi(table[r*numCol+i++]);
		item.drop_script=atoi(table[r*numCol+i++]);
		item.lose_script=atoi(table[r*numCol+i++]);
		item.atk=atoi(table[r*numCol+i++]);
		item.def=atoi(table[r*numCol+i++]);
		item.item_template=atoi(table[r*numCol+i++]);
		item.bonus=atoi(table[r*numCol+i++]);
		item.bonus2=atoi(table[r*numCol+i++]);
		item.userdata=atoi(table[r*numCol+i++]);
		item.userdata2=atoi(table[r*numCol+i++]);
		item.total_cooldown=atoi(table[r*numCol+i++]);
		item.weight = atof(table[r*numCol+i++]);
		//item.pDataSize=atoi(table[r*numCol+i++]);
		//memcpy(item.pData,table[r*numCol+i++],item.pDataSize);
		// tempid is the location of the player within the array of players on the server
		// This was kept this way since Jame's logic probably relies on it elsewhere.
		item.owner = tempid;
		itemlist->addItem(item);
	}
	sqlite3_free_table(table);
	sqlite3_free(zSQL);
}

int mysqlDB::loadPlayer(cPlayer *player,int slot)
{
	//obtain player id from account's slot
	int numRows;
	int numCol;
	char *err;
	char **table;
	char *zSQL;
	int player_id;

	zSQL = sqlite3_mprintf("SELECT char1, char2, char3, char4 FROM accounts WHERE accid='%s'", player->accid);
	sqlite3_get_table(db, zSQL, &table, &numRows, &numCol, &err);

	if(numRows!=1)
		return 0;

	player_id = atoi(table[numCol+slot - 1]);	
	sqlite3_free_table(table);
	sqlite3_free(zSQL);

//load player
	zSQL = sqlite3_mprintf("SELECT id, x, y, map, dir, type, state, range, str, dex, con, itl, wis, access, eLeft, eRight, eHead, eBody, eSpecial, \
 					lvl, player_temp, sprite, body, hair, clothes, worth, atk, def, train, hp, mp, mmp, target, target_at, chat_script, \
					move_script, exp, flags, origin_x, origin_y, origin_map, total_time, boot_time, serenity, unknown FROM players WHERE id=%d",player_id);
	sqlite3_get_table(db, zSQL, &table, &numRows, &numCol, &err);

	for (int r = 1; r <= numRows; ++r)
	{
		int i=0;
		player->id=atoi(table[r*numCol+i++]);
		player->x=atoi(table[r*numCol+i++]);
		player->y=atoi(table[r*numCol+i++]);
		player->map=atoi(table[r*numCol+i++]);
		player->dir=atoi(table[r*numCol+i++]);
		player->type=atoi(table[r*numCol+i++]);
		player->state=atoi(table[r*numCol+i++]);
		player->range=atoi(table[r*numCol+i++]);
		player->str=atoi(table[r*numCol+i++]);
		player->dex=atoi(table[r*numCol+i++]);
		player->con=atoi(table[r*numCol+i++]);
		player->itl=atoi(table[r*numCol+i++]);
		player->wis=atoi(table[r*numCol+i++]);
		player->access=atoi(table[r*numCol+i++]);
		player->eLeft=atoi(table[r*numCol+i++]);
		player->eRight=atoi(table[r*numCol+i++]);
		player->eHead=atoi(table[r*numCol+i++]);
		player->eBody=atoi(table[r*numCol+i++]);
		player->eSpecial=atoi(table[r*numCol+i++]);
		player->lvl=atoi(table[r*numCol+i++]);
		player->player_template=atoi(table[r*numCol+i++]);
		player->sprite=atoi(table[r*numCol+i++]);
		player->body=atoi(table[r*numCol+i++]);
		player->hair=atoi(table[r*numCol+i++]);
		player->clothes=atoi(table[r*numCol+i++]);
		player->worth=atoi(table[r*numCol+i++]);
		player->atk=atoi(table[r*numCol+i++]);
		player->def=atoi(table[r*numCol+i++]);
		player->train=atoi(table[r*numCol+i++]);
		player->hp=atoi(table[r*numCol+i++]);
		player->mhp=atoi(table[r*numCol+i++]);
		player->mp=atoi(table[r*numCol+i++]);
		player->mmp=atoi(table[r*numCol+i++]);
		player->target=atoi(table[r*numCol+i++]);
		player->target_at=atoi(table[r*numCol+i++]);
		player->chat_script=atoi(table[r*numCol+i++]);
		player->move_script=atoi(table[r*numCol+i++]);
		player->exp=atoi(table[r*numCol+i++]);
		player->flags=atoi(table[r*numCol+i++]);
		player->origin_x=atoi(table[r*numCol+i++]);
		player->origin_y=atoi(table[r*numCol+i++]);
		player->origin_map=atoi(table[r*numCol+i++]);
		strcpy(player->name,table[r*numCol+i++]);
		strcpy(player->title,table[r*numCol+i++]);
		strcpy(player->create_date,table[r*numCol+i++]);
		strcpy(player->login_date,table[r*numCol+i++]);
		strcpy(player->logout_date,table[r*numCol+i++]);
		player->total_time=atoi(table[r*numCol+i++]);
		player->boot_time=atoi(table[r*numCol+i++]);
		player->serenity=atoi(table[r*numCol+i++]);
		player->unknown=atoi(table[r*numCol+i++]);
	}

	sqlite3_free_table(table);
	sqlite3_free(zSQL);

	//update login_time
	zSQL = sqlite3_mprintf("UPDATE players SET login_date=datetime('now') WHERE id=%d",player->id);
	sqlite3_exec(db, zSQL, 0, 0, 0);
	sqlite3_free(zSQL);

	return 1;
}

void mysqlDB::setAccountSlot(char *id,int slot,int index)
{
	char *zSQL = sqlite3_mprintf("UPDATE accounts SET char%d=%d WHERE accid='%s'",slot,index,id);
	sqlite3_exec(db, zSQL, 0, 0, 0);
	sqlite3_free(zSQL);
}

int mysqlDB::loginAccount(char *id,char *pass,char *ip)
{

	int numRows;
	char *zSQL;
	zSQL = sqlite3_mprintf("SELECT * FROM accounts WHERE accid='%s' AND pass='%s'",id,pass);

	numRows = GetRowCount(zSQL);
	sqlite3_free(zSQL);

	if (numRows < 1)
		return 0; //Incorrect login

	zSQL = sqlite3_mprintf("UPDATE accounts SET ip='%s' WHERE accid='%s'",ip,id);
	sqlite3_exec(db, zSQL, 0, 0, 0);
	sqlite3_free(zSQL);

	return 1; //Login OK
}

int mysqlDB::getAccountSlots(char *id,cPlayer *slot1,cPlayer *slot2,cPlayer *slot3,cPlayer *slot4)
{

	int numRows;
	int numCol;
	char *err;
	char **table;
	char *zSQL;

	zSQL = sqlite3_mprintf("SELECT char1, char2, char3, char4 FROM accounts WHERE accid='%s'",id);
	sqlite3_get_table(db, zSQL, &table, &numRows, &numCol, &err);
	sqlite3_free(zSQL);

	if (numRows < 1)
		return 0; //man not found dog

	int slot[4];
	//fetch character slot representations

	slot[0]=atoi(table[numCol+0]);
	slot[1]=atoi(table[numCol+1]);
	slot[2]=atoi(table[numCol+2]);
	slot[3]=atoi(table[numCol+3]);

	sqlite3_free_table(table);
	sqlite3_free(zSQL);

	//load slot 1
	if(slot[0]==-1)
		slot1->lvl=0;
	else
	{
		zSQL = sqlite3_mprintf("SELECT name,level,sprite,body,hair,clothes FROM players WHERE id=%d",slot[0]);
		sqlite3_get_table(db, zSQL, &table, &numRows, &numCol, &err);
		strcpy(slot1->name,table[numCol+0]);
		slot1->lvl=atoi(table[numCol+1]);
		slot1->sprite=atoi(table[numCol+2]);
		slot1->body=atoi(table[numCol+3]);
		slot1->hair=atoi(table[numCol+4]);
		slot1->clothes=atoi(table[numCol+5]);
		sqlite3_free_table(table);
		sqlite3_free(zSQL);
	}

//load slot 2
	if(slot[1]==-1)
		slot2->lvl=0;
	else
	{
		zSQL = sqlite3_mprintf("SELECT name,level,sprite,body,hair,clothes FROM players WHERE id=%d",slot[1]);
		sqlite3_get_table(db, zSQL, &table, &numRows, &numCol, &err);
		strcpy(slot1->name,table[numCol+0]);
		slot2->lvl=atoi(table[numCol+1]);
		slot2->sprite=atoi(table[numCol+2]);
		slot2->body=atoi(table[numCol+3]);
		slot2->hair=atoi(table[numCol+4]);
		slot2->clothes=atoi(table[numCol+5]);
		sqlite3_free_table(table);
		sqlite3_free(zSQL);
	}

//load slot 3
	if(slot[2]==-1)
		slot3->lvl=0;
	else
	{
		zSQL = sqlite3_mprintf("SELECT name,level,sprite,body,hair,clothes FROM players WHERE id=%d",slot[2]);
		sqlite3_get_table(db, zSQL, &table, &numRows, &numCol, &err);
		strcpy(slot1->name,table[numCol+0]);
		slot3->lvl=atoi(table[numCol+1]);
		slot3->sprite=atoi(table[numCol+2]);
		slot3->body=atoi(table[numCol+3]);
		slot3->hair=atoi(table[numCol+4]);
		slot3->clothes=atoi(table[numCol+5]);
		sqlite3_free_table(table);
		sqlite3_free(zSQL);
	}

//load slot 4
	if(slot[3]==-1)
		slot4->lvl=0;
	else
	{
		zSQL = sqlite3_mprintf("SELECT name,level,sprite,body,hair,clothes FROM players WHERE id=%d",slot[3]);
		sqlite3_get_table(db, zSQL, &table, &numRows, &numCol, &err);
		strcpy(slot1->name,table[numCol+0]);
		slot4->lvl=atoi(table[numCol+1]);
		slot4->sprite=atoi(table[numCol+2]);
		slot4->body=atoi(table[numCol+3]);
		slot4->hair=atoi(table[numCol+4]);
		slot4->clothes=atoi(table[numCol+5]);
		sqlite3_free_table(table);
		sqlite3_free(zSQL);
	}
	return 1;
}

int mysqlDB::sendQuery(char *query)
{
	return sqlite3_exec(db, query, 0, 0, 0);
}

#endif


