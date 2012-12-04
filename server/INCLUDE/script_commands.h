#ifndef _SCRIPT_COMMANDS_H_
#define _SCRIPT_COMMANDS_H_
//\\//\\\// SCRIPT FUNCTIONS \\//\\//\\//

#include "gameserver.h"
#include "console.h"

// (Sonic) Unused?
//static cGameServer *mygs;

void setScriptCommandGameServer(cGameServer *gs);
//newer script access commands

//script runtime vars
_MLF int getPlayer();

_MLF char *getChat();

_MLF char *getCommand();

_MLF int getChatPlayer();
_MLF int myScript();
//server commands
_MLF void printMsg(int p0);

_MLF void makeNPC(int p0,int p1,int p2,int p3);


_MLF int getTime();


_MLF int takeItem(int p0,int p1);


_MLF void makeItem(int p0,int p1,int p2,int p3,int p4);

_MLF int giveItem(int p0,int p1,int p2);

_MLF int clearItem(int p0,int p1,int p2,int p3);

_MLF int getItemAt(int p0,int p1,int p2);

_MLF void npcMove(int p0,int p1);

_MLF int npcCanMove(int p0,int p1,int p2);

_MLF void npcAttack(int p0);

_MLF int hasItem(int p0,int p1);

_MLF int itemSlot(int p0,int p1);

_MLF int itemAt(int p0,int p1);

_MLF int qtyAt(int p0,int p1);

_MLF void setQty(int p0,int p1,int p2);

//globals
_MLF void setGlobalInt(char *p0,int p1);

_MLF void setGlobalStr(char * p0,char * p1);

_MLF int isGlobal(char * p0);

_MLF int globalInt(char * p0);

_MLF char *globalStr(char * p0);

_MLF void freeGlobal(char *p0);

_MLF void DBupdateGlobal(char *name,char *value);

_MLF void DBinsertGlobal(char *name,char *value);

_MLF void DBdeleteGlobal(char *name);

_MLF char *DBselectGlobal(char *name);

_MLF bool DBisGlobal(char *name);

_MLF int DBsendQuery(char *query);

//server data accessors
_MLF int playerLen();

_MLF cPlayer *playerStruct(int id);

_MLF void playerSave(int id);

_MLF void playerResize(int len);
_MLF void itemResize(int len);
_MLF void mapResize(int len);
_MLF int mapLen();

_MLF cMap *mapStruct(int id);

_MLF void mapSave(int p0);

_MLF void mapCompleteSave(int id);

_MLF int itemLen();
_MLF cItem *itemStruct(int id);
_MLF void itemSave(int id);

_MLF void itemInsert(int id);

_MLF void itemDelete(int id);

_MLF int playerTemplateLen();
_MLF cPlayer *playerTemplateStruct(int id);

_MLF int itemTemplateLen();
_MLF cItem *itemTemplateStruct(int id);

_MLF int mapListLen(int p0);

_MLF int mapList(int p0,int p1);

_MLF int inventoryLen();

_MLF int inventoryItem(int id, int slot);

_MLF int runScript(int p0,int p1);

_MLF int runScriptAs(int p0,int p1,int p2);

_MLF void haltScript(int p0);

//messages

_MLF void sendPlayerUpdate(int id);
_MLF void sendMapUpdate(int p0);

_MLF void sendAttribute(int id);
_MLF void sendLevel(int id);
_MLF void sendPosition(int id);
_MLF void sendAccess(int id);
_MLF void sendMap(int id,int mapid);
_MLF void sendEquip(int id);
_MLF void sendHP(int id);
_MLF void sendMP(int id);
_MLF void sendEXP(int id);
_MLF void sendShade(int id,unsigned char shade);
_MLF void sendHPbar(int map,unsigned short id);
_MLF void sendAddMapItem(int graphic,int map,int x,int y);
_MLF void sendRemoveMapItem(int map,int x,int y);
_MLF void sendInventoryQty(int id,signed short index,signed long quantity);
_MLF void sendInventoryAdd(int id,unsigned short graphic,char *name,unsigned char index,unsigned long quantity);

_MLF void sendPlayerList(int index);
_MLF void sendItemList(int index);

_MLF void sendChatf(int p0,char *p1,...);

_MLF void sendChat(char *p0,int p1);

_MLF void sendMapChat(char *p0,int p1);

_MLF void sendMapChatf(int p0,char *p1,...);

_MLF int levelUpExp(int lvl);

_MLF void disconnectPlayer(int id);

//old functions


_MLF int getPlayerType(int p0);
_MLF int getMaxPlayers();
_MLF int isConnected(int p0);

_MLF int getTile(int p0,int p1,int p2,int p3);
_MLF int getTileType(int p0,int p1,int p2);
_MLF void setTile(int p0,int p1,int p2,int p3,int p4);
_MLF void setTileType(int p0,int p1,int p2,int p3);
_MLF void setTileWarp(int p0,int p1,int p2,int p3,int p4,int p5);
_MLF void setTileScript(int p0,int p1,int p2,int p3);
_MLF int inBounds(int p0,int p1);


_MLF void dropItem(int id, int slot, int qty = -1);

_MLF void pickupItem(int id);

_MLF int getID(int p0,int p1,int p2);
//effects
_MLF void makeEffect(int p0,int p1,int p2,int p3);

_MLF int maxInv();

//player stuff
_MLF int getLvl(int p0);

_MLF int getAccess(int p0);

_MLF int getStr(int p0);

_MLF int getCon(int p0);

_MLF int getDex(int p0);

_MLF int getInt(int p0);

_MLF int getWis(int p0);

_MLF int getBody(int p0);

_MLF int getClothes(int p0);

_MLF int getHair(int p0);

_MLF void setHP(int p0,int p1);

_MLF int getHP(int p0);

_MLF void setMP(int p0,int p1);

_MLF int getMP(int p0);

_MLF int getMaxHP(int p0);
_MLF int getMaxMP(int p0);
_MLF int getDir(int p0);



_MLF int getImg(int p0);

_MLF int getAtk(int p0);

_MLF void setPos(int p0,int p1,int p2,int p3);
_MLF int getMap(int p0);
_MLF int getX(int p0);
_MLF int getY(int p0);

_MLF void giveExp(int p0,int p1);

_MLF int getExp(int p0);

_MLF int damage(int p0);

_MLF int magicDamage(int p0);

//misc
_MLF int getRand(int p0);


_MLF char *strCat(char *p0,char *p1);

_MLF int strCon(char * p0,char * p1);

_MLF void setOrigin(int p0,int p1,int p2,int p3);

_MLF void getOrigin(int p0,int &p1,int &p2,int &p3);

_MLF void setBounty(int p0,int p1);

_MLF void setImg(int p0,int p1);


_MLF void setBody(int p0,int p1);

_MLF void setClothes(int p0,int p1);

_MLF void setHair(int p0,int p1);

_MLF char *getName(int p0);

_MLF void setTarget(int p0,int p1);


_MLF char *stringLower(char * p0);


_MLF int stoi(char *p0);

_MLF char *itos(int p0);



_MLF char *getItemName(int p0);

_MLF int getMTarget(int p0);

_MLF int getTarget(int p0);

_MLF int getBounty(int p0);

_MLF void setMTarget(int p0,int p1);

_MLF void setDir(int p0,int p1);

_MLF void setChatScript(int p0,int p1);

_MLF void setMoveScript(int p0,int p1);

_MLF char *intToString(int p0);

_MLF int stringToInt(char * p0);



_MLF char *getWord(char* p0, int p1);

_MLF void makeSound(int p0,int p1);

_MLF void setMapLighting(int p0,int p1);

_MLF int getMapLighting(int p0);

_MLF void setMapMusic(int p0,int p1);

_MLF int getMapMusic(int p0);

_MLF void setMapLink(int p0,int p1,int p2);

_MLF int getMapLink(int p0,int p1);
_MLF int updateMap(int p0);
#endif
