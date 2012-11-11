//libraries

#ifndef _MYSQLDB_
#define _MYSQLDB_

#include <stdio.h>
#include <sqlite3.h>

#include "gamedefs.h"
#include "list.h"

struct mysqlDB
{
	sqlite3 *db;

	mysqlDB();
	char mystring[256];
	void runScript(char *filename);
	int connect();
	void disconnect();
	int accountExists(char *id);
	int emailExists(char *email);
	int loginAccount(char *id,char *pass,char *ip);
	void setAccountSlot(char *id,int slot,int index);
	int getAccountSlots(char *id,cPlayer *slot1,cPlayer *slot2,cPlayer *slot3,cPlayer *slot4);
	int createAccount(char *id,char *pass,char *email,char *ip);
	int createPlayer(char *name,int body,int clothes,int hair,int access,int map,int x,int y,int *player_id);
	void deletePlayer(int id);
	void updatePlayer(const cPlayer *player);
	void updateCorePlayer(const cPlayer *player);
	void updateEquipPlayer(const cPlayer *player);
	int nameExists(char *name);
	int numPlayerAccounts();
	int numAccounts();
	void updateItem(cItem *item);
	void removeItem(int permid);
	void insertItem(cItem *item,int perm_owner=-1);

	//void loadNPCTemplates();
	//void loadItemTemplates();

	void updateGlobal(char *name,char *value);
	void insertGlobal(char *name,char *value);
	void deleteGlobal(char *name);
	char *selectGlobal(char *name);
	bool isGlobal(char *name);
	void loadMapItems(cItemList *itemlist);
	int loadPlayer(cPlayer *player,int slot);
	void loadPlayerItems(int id,int tempid,cItemList *itemlist);
	int sendQuery(char *query);
};

#endif

