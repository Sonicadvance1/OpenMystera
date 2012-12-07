#ifndef _MLSCRIPT_H_
#define _MLSCRIPT_H_
#include <string.h>


void strlwr(char* xpString)
{
	while (*xpString != '\0')
		{
		if (*xpString >= 'A' && *xpString <= 'Z')
			*xpString |= 0x20;

		xpString++;
		}
}

void strupr(char* xpString)
{
	while (*xpString != '\0')
		{
		if (*xpString >= 'a' && *xpString <= 'z')
			*xpString &= ~0x20;

		xpString++;
		}
}

int stricmp(const char* xpString1, const char* xpString2)
{
	char Char1, Char2;

	while (true)
		{
		Char1 = *xpString1;
		Char2 = *xpString2;

		if (Char1 == '\0' && Char2 == '\0')
			break;

		if (Char1 >= 'A' && Char1 <= 'Z')
			Char1 |= 0x20;
		if (Char2 >= 'A' && Char2 <= 'Z')
			Char2 |= 0x20;

		if (Char1 != Char2)
			return Char1 - Char2;

		xpString1++;
		xpString2++;
		}

	return 0;
}

int strnicmp(const char* xpString1, const char* xpString2, size_t xCount)
{
	char Char1, Char2;
	int i;

	for (i = 0; i < xCount; i++)
		{
		Char1 = *xpString1;
		Char2 = *xpString2;

		if (Char1 == '\0' && Char2 == '\0')
			break;

		if (Char1 >= 'A' && Char1 <= 'Z')
			Char1 |= 0x20;
		if (Char2 >= 'A' && Char2 <= 'Z')
			Char2 |= 0x20;

		if (Char1 != Char2)
			return Char1 - Char2;

		xpString1++;
		xpString2++;
		}

	return 0;
}



#include <stdio.h>
#include <stdlib.h>

class string
{
private:
	char* mpString;
public:
	string()
	{
		mpString = new char[1];
		*mpString = '\0';
	}
	string(const char *xpString)
	{
		mpString = new char[strlen(xpString) + 1];
		strcpy(mpString, xpString);
	}
	string(const string& xString)
	{
		mpString = new char[strlen(xString.mpString) + 1];
		strcpy(mpString, xString.mpString);
	}
	~string()
	{
		delete [] mpString;
	}
	
    operator char*()
    {
        return mpString;
    }
    const char *c_str()
    {
        return mpString;
    }
	void operator=(const char* xpString)
	{
		delete [] mpString;
		mpString = new char[strlen(xpString) + 1];
		strcpy(mpString, xpString);
	}
	
	void operator+=(const char* xpString)
	{
		char* pNewString;
		pNewString = new char[strlen(mpString) + strlen(xpString) + 1];
		strcpy(pNewString, mpString);
		strcat(pNewString, xpString);
		delete [] mpString;
		mpString = pNewString;
	}
	
	bool operator==(const char* xpString)
	{
		return (strcmp(mpString, xpString) == 0);
	}
    bool operator==(char* xpString)
	{
		return (strcmp(mpString, xpString) == 0);
	}
	bool operator!=(const char* xpString)
	{
		return (strcmp(mpString, xpString) != 0);
	}
	
	string operator+(const char* xpString)
	{
		string Temp;
		Temp += *this;
		Temp += xpString;
		return Temp;
	}
    char operator[](long int num)
    {
        return mpString[num];
    }
};

// Constants added by Steve
const int COMMAND_LENGTH = 256;
const int ITEM_NAME_LENGTH = 32;

const int PLAYER_TYPE_PC = 0;
const int PLAYER_TYPE_NPC = 1;

const int LAYER_FLOOR = 0;
const int LAYER_OBJECT = 1;
const int LAYER_FLIP = 2;
const int LAYER_CEILING = 3;

const int TILE_TYPE_NONE = 1;
const int TILE_TYPE_WALL = 2;
const int TILE_TYPE_WARP = 3;
const int TILE_TYPE_NPC = 4;
const int TILE_TYPE_SCRIPT = 5;
const int TILE_TYPE_SWITCH = 6;
const int TILE_TYPE_KEEP = 7;

const int SEND_CHAT_GLOBAL = -1;
const int CHAT_SCRIPT_DEFAULT = -1;
const int MOVE_SCRIPT_DEFAULT = -1;

const int DIR_DOWN = 0;
const int DIR_UP = 1;
const int DIR_LEFT = 2;
const int DIR_RIGHT = 3;

const int MAP_WIDTH = 20;
const int MAP_HEIGHT = 15;

#define IT_EMPTY     0
#define IT_HAND      1
#define IT_ITEM      2
#define IT_CURRENCY  3
#define IT_ARMOR     4
#define IT_HELMET    5
#define IT_2HAND     6
#define IT_SPECIAL   7

#define PASSIVE   0
#define ATTACK    1
#define STANDING  2
#define MERCHANT  3



struct timer
{
    long start;
    bool started;
};

#if 0 // For reference only
struct pos
{
	unsigned char x,y;
	signed short map;
};

struct cItem
{
	signed long		id;
	unsigned char	life;
	signed long		qty;
	unsigned short	graphic;
	char			name[ITEM_NAME_LENGTH];
	signed short	map;
	unsigned char	x;
	unsigned char	y;
	signed short	owner;
	signed short	slot;
	unsigned char	type;
	unsigned char	stack;
	unsigned int	flags;
	signed char		uses;
	signed short	use_script;
	signed short	equip_script;
	signed short	unequip_script;
	signed short	pickup_script;
	signed short	drop_script;
	signed short	lose_script;
	signed short	atk;
	signed short	def;
	signed short	item_template;
	signed short	bonus;
	signed short	bonus2;
	signed short	userdata;
	signed short	userdata2;
	timer           cooldown;
	unsigned short  total_cooldown;
	float           weight;
};

struct cPlayer
{
	signed long		id;
	unsigned char	x;
	unsigned char	y;
	signed short	map;
	unsigned char	dir;
	unsigned char	type;
	unsigned char	state;
	unsigned char	range;
	unsigned char	str;
	unsigned char	dex;
	unsigned char	con;
	unsigned char	itl;
	unsigned char	wis;
	signed char		access;
	signed char		eLeft;
	signed char		eRight;
	signed char		eHead;
	signed char		eBody;
	signed char		eSpecial;
	unsigned short	lvl;
	signed short	player_template;
	signed short	sprite;
	signed short	body;
	signed short	hair;
	signed short	clothes;
	signed long		worth;
	signed short	atk;
	signed short	def;
	unsigned short	train;
	signed long		hp;
	signed long		mhp;
	signed long		mp;
	signed long		mmp;
	signed short	target;
	signed short	target_at;
	signed short	chat_script;
	signed short	move_script;
	signed long		exp;
	unsigned long	flags;
	unsigned char	origin_x;
	unsigned char	origin_y;
	signed	short	origin_map;
	char			name[32];
	char			title[64];
	char			create_date[64];
	char			login_date[64];
	char			logout_date[64];
	unsigned long	total_time;
	unsigned long	boot_time;
	unsigned long	serenity;
	unsigned long	unknown;

	//not stored
	char ip[16];
	int time_safe;
	int stationary;
	int premium;
	char accid[7];
	signed long		pid;
	int inventory[28];
	int current_map;
	timer mstl;
	unsigned long packet_time;
	signed char npacket;
	char ignore[32];
};

struct cTile
{
	unsigned short tile[4];
	unsigned char type;
	pos warp;
	signed short space;
};

struct cNPCRef
{
	int index,qty;
};

struct cMap
{
	cTile map[15][20];
	char name[32];
	int n,e,s,w;
	unsigned char version;
	cNPCRef npc[5];
};

//server data
_MLF int getPlayer();
_MLF int getChatPlayer();
_MLF char *getChat();
_MLF char *getCommand();
_MLF int myScript();

_MLF int playerLen();
_MLF void playerResize(int len);
_MLF cPlayer *playerStruct(int id);
_MLF void playerSave(int id);

_MLF int playerTemplateLen();
_MLF cPlayer *playerTemplateStruct(int id);

_MLF int mapLen();
_MLF void mapResize(int);
_MLF cMap *mapStruct(int id);
_MLF void mapSave(int id);
_MLF void mapCompleteSave(int id);

_MLF int itemLen();
_MLF void itemResize(int len);
_MLF cItem *itemStruct(int id);
_MLF void itemSave(int id);
_MLF void itemInsert(int id);
_MLF void itemDelete(int id);

_MLF int itemTemplateLen();
_MLF cItem *itemTemplateStruct(int id);

_MLF int inventoryLen();
_MLF int inventoryItem(int id, int slot);

_MLF int mapListLen(int);
_MLF int mapList(int,int);

_MLF int runScript(int,int);
_MLF int runScriptAs(int,int,int);
_MLF void haltScript(int);

_MLF void makeNPC(int,int,int,int);
_MLF void printMsg(int);
_MLF int getTime();
_MLF void disconnectPlayer(int);

_MLF void setGlobalInt(char *,int);
_MLF void setGlobalStr(char *,char *);
_MLF int isGlobal(char *);
_MLF int globalInt(char *);
_MLF char *globalStr(char *);
_MLF void freeGlobal(char *);

_MLF void DBupdateGlobal(char *,char *);
_MLF void DBinsertGlobal(char *,char *);
_MLF void DBdeleteGlobal(char *);
_MLF char *DBselectGlobal(char *);
_MLF bool DBisGlobal(char *);

_MLF int DBsendQuery(char *);

//messages
_MLF void sendPlayerUpdate(int id);
_MLF void sendMapUpdate(int);
_MLF void makeEffect(int,int,int,int);
_MLF void makeSound(int,int);
_MLF void sendChatf(int,char *,...);
_MLF void sendMapChatf(int,char *,...);
_MLF void sendChat(char *,int);
_MLF void sendMapChat(char *,int);

_MLF void sendAttribute(int id);
_MLF void sendLevel(int id);
_MLF void sendPosition(int id);
_MLF void sendAccess(int id);
_MLF void sendMap(int,int mapid);
_MLF void sendEquip(int id);
_MLF void sendHP(int id);
_MLF void sendMP(int id);
_MLF void sendEXP(int id);

_MLF void sendShade(int id,unsigned char shade);
_MLF void sendHPbar(int map,unsigned short id);

_MLF void sendAddMapItem(int graphic,int map,int x,int y);
_MLF void sendRemoveMapItem(int map,int x,int y);
_MLF void sendInventoryQty(int id,signed short index,signed long quantity);
_MLF void sendInventoryAdd(int id,unsigned short graphic, const char *name,unsigned char index,unsigned long quantity);

_MLF void sendPlayerList(int index);
_MLF void sendItemList(int index);

//item helpers
_MLF int takeItem(int,int);
_MLF int giveItem(int,int,int);
_MLF void makeItem(int,int,int,int,int);
_MLF int clearItem(int,int,int,int);
_MLF int getItemAt(int,int,int);
_MLF int hasItem(int,int);
_MLF int itemSlot(int,int);
_MLF int itemAt(int,int);
_MLF int qtyAt(int,int);
_MLF void setQty(int,int,int);
_MLF void dropItem(int id, int slot, int qty = -1);
_MLF void pickupItem(int id);

//npc helpers
_MLF void npcMove(int,int);
_MLF int npcCanMove(int,int,int);
_MLF void npcAttack(int);

//utils
_MLF int levelUpExp(int lvl);

//\/\/\/\/\old commands\/\/\/\/\/\/\/\/
_MLF int updateMap(int);
_MLF int getPlayerType(int);
_MLF int isConnected(int);
_MLF int getTile(int,int,int,int);
_MLF int getTileType(int,int,int);
_MLF void setTile(int,int,int,int,int);
_MLF void setTileType(int,int,int,int);
_MLF void setTileWarp(int,int,int,int,int,int);
_MLF void setTileScript(int,int,int,int);
_MLF int inBounds(int,int);
//_MLF int getID(int,int,int);

int getID(int mapid,int x,int y)
{
	cMap *map=mapStruct(mapid);

	for(int i = 0; i < mapListLen(mapid);i++)
	{
		cPlayer *target = playerStruct(mapList(mapid,i));
		if(target->x == x && target->y == y && (target->total_time == 0 || target->type == PLAYER_TYPE_PC))
		{
			return mapList(mapid,i);
		}
	}
	return -1;
}

_MLF int getLvl(int);
_MLF int getAccess(int);
_MLF int getStr(int);
_MLF int getCon(int);
_MLF int getDex(int);
_MLF int getInt(int);
_MLF int getWis(int);
_MLF int getBody(int);
_MLF int getClothes(int);
_MLF int getHair(int);
_MLF void setHP(int,int);
_MLF int getHP(int);
_MLF void setMP(int,int);
_MLF int getMP(int);
_MLF int getMaxHP(int);
_MLF int getMaxMP(int);
_MLF int getDir(int);
_MLF int getImg(int);
_MLF int getAtk(int);
_MLF void setPos(int,int,int,int);
_MLF int getMap(int);
_MLF int getX(int);
_MLF int getY(int);
_MLF void setOrigin(int,int,int,int);
_MLF void getOrigin(int,int &,int &,int &);
_MLF void setBounty(int,int);
_MLF void setBody(int,int);
_MLF void setClothes(int,int);
_MLF void setHair(int,int);
_MLF char *getName(int);
_MLF void setTarget(int,int);
_MLF int getMTarget(int);
_MLF int getTarget(int);
_MLF void setDir(int,int);
_MLF void setChatScript(int,int);
_MLF void setMoveScript(int,int);
_MLF void setMapLighting(int,int);
_MLF int getMapLighting(int);
_MLF void setMapMusic(int,int);
_MLF int getMapMusic(int);
_MLF void setMapLink(int,int,int);
_MLF int getMapLink(int,int);
_MLF void setImg(int,int);
_MLF void giveExp(int,int);
_MLF int getExp(int);
_MLF int getBounty(int);
_MLF char *getItemName(int);

//possibly useful
_MLF int damage(int);
_MLF int magicDamage(int);

//utilities
_MLF int getRand(int);
_MLF char *strCat(char *,char *);
_MLF int strCon(char *,char *);
_MLF char *stringLower(char *);
_MLF int stoi(char *p0);
_MLF char *itos(int p0);
_MLF char *intToString(int);
_MLF int stringToInt(char *);
_MLF char *getWord(char *,int);

#endif
//player utility functions

int itemDefense(int id)
{
	cItem *item = itemStruct(id);
	return item->def;
}

int equippedDefense(cPlayer *player)
{
	int def=0;
	if(player->eLeft>-1)
		def+=itemDefense(player->inventory[player->eLeft]);
	if(player->eRight>-1)
		def+=itemDefense(player->inventory[player->eRight]);
	if(player->eHead>-1)
		def+=itemDefense(player->inventory[player->eHead]);
	if(player->eBody>-1)
		def+=itemDefense(player->inventory[player->eBody]);
	if(player->eSpecial>-1)
		def+=itemDefense(player->inventory[player->eSpecial]);
	return def;
}

int move_check(int id,int dir, bool ignore_npc_tiles = false)//returns 0 for blocked, 1 for open, 2 for screen change
{
	cPlayer *player = playerStruct(id);
	cMap *map=mapStruct(player->map);
	
	int x=player->x,y=player->y;
	if(dir==DIR_UP)
	{
		if(y==0) return 2;
		y--;
	}
	else if(dir==DIR_DOWN)
	{
		if(y==14) return 2;
		y++;
	}
	else if(dir==DIR_LEFT)
	{
		if(x==0) return 2;
		x--;
	}
	else if(dir==DIR_RIGHT)
	{
		if(x==19) return 2;
		x++;
	}
	if(map->map[y][x].space!=-1 || map->map[y][x].type==2 || map->map[y][x].type==6 || (player->type==1 && ((map->map[y][x].type==4 && !ignore_npc_tiles) || map->map[y][x].type==3)))
		return 0;
	return 1;
}

void npc_warp(int id,int map,int x,int y)
{
	cPlayer *player = playerStruct(id);
	if(player->type!=1)
		return;
	cMap *pmap=mapStruct(player->map);
	pmap->map[player->y][player->x].space=-1;
	player->map=map;
	player->x=x;
	player->y=y;
	pmap=mapStruct(player->map);
	pmap->map[player->y][player->x].space=id;
}
void moveNpc(int id, int dir,bool ignore_npc_tiles)
{
	cPlayer *player = playerStruct(id);
	cMap *map = mapStruct(player->map);
	if(move_check(id,dir,ignore_npc_tiles) == 1)
	{
		int x=player->x,y=player->y;
		switch(dir)
		{
			case DIR_UP:
				y--;
				break;
			case DIR_DOWN:
				y++;
				break;
			case DIR_LEFT:
				x--;
				break;
			case DIR_RIGHT:
				x++;
				break;
		}
		setPos(id,player->map,x,y);
		player->dir = dir;
	}
	
}
void npc_move(int id,int dir,bool ignore_npc_tiles = false)
{
	cPlayer *player = playerStruct(id);
	if(player->type!=1)
		return;
	cMap *map=mapStruct(player->map);
	int res = move_check(id,dir,ignore_npc_tiles);
	if(res==2)
	{
		if(dir==DIR_UP)
		{
			npc_warp(id,map->n,player->x,14);
			return;
		}
		if(dir==DIR_DOWN)
		{
			npc_warp(id,map->s,player->x,0);
			return;
		}
		if(dir==DIR_LEFT)
		{
			npc_warp(id,map->w,19,player->y);
			return;
		}
		if(dir==DIR_RIGHT)
		{
			npc_warp(id,map->e,0,player->y);
			return;
		}
	}
	if(res==0)
	{
		if(dir==0)
			dir=getRand(2)+2;
		else if(dir==1)
			dir=getRand(2)+2;
		else if(dir==2)
			dir=getRand(2);
		else if(dir==3)
			dir=getRand(2);	
		moveNpc(id,dir,ignore_npc_tiles);
	}
	else
	{
		moveNpc(id,dir,ignore_npc_tiles);
	}
}

int npc_follow(int id,int target,bool ignore_npc_tiles = false,bool change_maps = true)//chases target and returns 1, if target lost returns 0
{
	cPlayer *player = playerStruct(id);
	if(player->type!=1)
		return 0;
	cPlayer *chased = playerStruct(target);
	cMap *map=mapStruct(player->map);
	int dir=player->dir;
	int dx=chased->x - player->x;
	int dy=chased->y - player->y;

	if(chased->map == player->map)
	{
		if(     dy<=0&&dx>=dy&&dx<=-dy)
			dir=1;
		else if(dy>=0&&dx<=dy&&dx>=-dy)
			dir=0;
		else if(dx<=0&&dy>=dx&&dy<=-dx)
			dir=2;
		else if(dx>=0&&dy<=dx&&dy>=-dx)
			dir=3;
	}
	else if(change_maps)
	{
		if(chased->map == map->n)
			dir = DIR_UP;
		else if(chased->map == map->s)
			dir = DIR_DOWN;
		else if(chased->map == map->w)
			dir = DIR_LEFT;
		else if(chased->map == map->e)
			dir = DIR_RIGHT;
		else return 0;
	}
	else
	{
		return 0;
	}
	npc_move(id,dir,ignore_npc_tiles);
	return 1;
}

int npc_attack(int id,int target)//returns 1 on successful attack, 0 otherwise
{
	cPlayer *player = playerStruct(id);
	if(player->type!=1)
		return 0;
	cPlayer *chased = playerStruct(target);

	int dx=chased->x - player->x;
	int dy=chased->y - player->y;

	if(chased->map == player->map && abs(dx)+abs(dy)==1)//attack
	{
		if(     dy<=0&&dx>=dy&&dx<=-dy)
			player->dir=1;
		else if(dy>=0&&dx<=dy&&dx>=-dy)
			player->dir=0;
		else if(dx<=0&&dy>=dx&&dy<=-dx)
			player->dir=2;
		else if(dx>=0&&dy<=dx&&dy>=-dx)
			player->dir=3;
		int dmg=player->atk-chased->def;
		if(chased->type==0)
			dmg-=equippedDefense(chased);
		//apply randomness
		dmg+=rand()%5-2;
		if(dmg<0)
			dmg=0;
		if(chased->hp-dmg <= 0)
			chased->hp = 0;
		else
			chased->hp-=dmg;
		if(chased->type==0)
			chased->target=id;
		//send blood/miss effect out
		if(dmg>0)
			makeEffect(player->map,chased->x,chased->y,0);
		else
			makeEffect(player->map,chased->x,chased->y,4);
		//send hp bar
		sendHPbar(player->map,target);
		if(chased->type==0)
			sendHP(target);
		return 1;
	}
	return 0;
}

int npc_find_player(int id)//returns a player id on npc's map, or -1 if not possible
{
	cPlayer *player = playerStruct(id);
	if(player->type!=1)
		return -1;
	cPlayer *target;
	int tgt=-1;
	int len=mapListLen(player->map);
	for(int x=0;x<len;x++)
	{
		target=playerStruct(mapList(player->map,x));
		if(target->type==0)
			return mapList(player->map,x);
	}
	return -1;
}

void npc_spell(int id, int target, int effect, int hp_change)//for custom healing/damage spells
{
	if(id < 0 || target < 0)
		return;

	cPlayer *player = playerStruct(id);
	if(player->type!=1)
		return;
	cPlayer *chased = playerStruct(target);
	
	if(chased->type==0 && hp_change <= 0)
		chased->target=id;

	//send effect out
	chased->hp += hp_change;

	if(chased->hp<0)
		chased->hp=0;
	else if(chased->hp>chased->mhp)
		chased->hp = chased->mhp;

	if(effect > -1) 
		makeEffect(chased->map,chased->x,chased->y,effect);
	
	//send hp bar
	sendHPbar(chased->map,target);

	if(chased->type==0)
		sendHP(target);
}

int distance(int id,int target)
{
	cPlayer *player = playerStruct(id);
	cPlayer *chased = playerStruct(target);

	int dx=chased->x - player->x;
	int dy=chased->y - player->y;

	return abs(dx)+abs(dy);
}


// Following code added by Steve

bool isAdmin(int xPlayerID)
{
	cPlayer* pPlayer;

	pPlayer = playerStruct(xPlayerID);

	return (pPlayer->access > 1);
}

// Overriding setHP function to take serenity into account, added by Steve
void setHP(int xPlayerID, int xHP)
{
	cPlayer* pVictim;
	pVictim = playerStruct(xPlayerID);

	if (xHP < 0)
		xHP = 0;
	if (xHP > pVictim->mhp)
		xHP = pVictim->mhp;

	if (xHP < pVictim->hp)	// If HP are decreasing
		{
		cPlayer* pAttacker;
		pAttacker = playerStruct(getPlayer());

		if (getPlayer() != xPlayerID && pVictim->type == PLAYER_TYPE_PC && pAttacker->type == PLAYER_TYPE_PC && (pVictim->serenity > 0 || pAttacker->serenity > 0))	// If this is player vs player and either player has serenity, nullify damage
			return;

		pVictim->target = getPlayer();
		}

	pVictim->hp = xHP;

	if (pVictim->type == PLAYER_TYPE_PC)
		sendHP(xPlayerID);

	if (myScript() != 1001)
		sendHPbar(pVictim->map, xPlayerID);
}

int attackOf(int xPlayerID)
{
	cPlayer* pPlayer;
	cItem* pItem;
	int i;
	int ItemID;
	int Attack;

	pPlayer = playerStruct(xPlayerID);
	Attack = pPlayer->atk+pPlayer->str/3;

	for (i = 0; i < 5; i++)
		{
		switch (i)
			{
			case 0:
				ItemID = pPlayer->eLeft;
				break;
			case 1:
				ItemID = pPlayer->eRight;
				break;
			case 2:
				ItemID = pPlayer->eHead;
				break;
			case 3:
				ItemID = pPlayer->eBody;
				break;
			case 4:
				ItemID = pPlayer->eSpecial;
				break;
			}

		if (ItemID == -1)
			continue;

		ItemID = pPlayer->inventory[ItemID];
		pItem = itemStruct(ItemID);
		Attack += pItem->atk;
		}

	return Attack;
}

int defenseOf(int xPlayerID)
{
	cPlayer* pPlayer;
	cItem* pItem;
	int i;
	int ItemID;
	int Defense;

	pPlayer = playerStruct(xPlayerID);
	Defense = pPlayer->def+pPlayer->con/4;

	for (i = 0; i < 5; i++)
		{
		switch (i)
			{
			case 0:
				ItemID = pPlayer->eLeft;
				break;
			case 1:
				ItemID = pPlayer->eRight;
				break;
			case 2:
				ItemID = pPlayer->eHead;
				break;
			case 3:
				ItemID = pPlayer->eBody;
				break;
			case 4:
				ItemID = pPlayer->eSpecial;
				break;
			}

		if (ItemID == -1)
			continue;

		ItemID = pPlayer->inventory[ItemID];
		pItem = itemStruct(ItemID);
		Defense += pItem->def;
		}

	return Defense;
}

int physicalDamage(int damage, int victim)
{
	cPlayer *target = playerStruct(victim);
	double damageResist = 1.0 - (defenseOf(victim)/100);
	if(damageResist < 0.01)
	{
		damageResist = 0.01;
	}
	return damage * damageResist;
}

int magicalDamage(int damage, int victim)
{
	cPlayer *target = playerStruct(victim);
	double damageResist = 1.0 - (target->wis/100);
	if(damageResist < 0.01)
	{
		damageResist = 0.01;
	}
	return damage * damageResist;
}


#define DISABLE_SCRIPT sendChat("^RSorry... this item is disabled for now", getPlayer()); return 0;


// Fatal signal handling - Added by Steve

/*#include <signal.h>
#include <setjmp.h>

jmp_buf gJmpEnv;

void SignalHandler(int xSignal)
{
	char* pSigMsg;

	switch (xSignal)
		{
		case SIGABRT:
			pSigMsg = "Abnormal termination";
			break;
		case SIGFPE:
			pSigMsg = "Floating-point exception";
			break;
		case SIGILL:
			pSigMsg = "Illegal instruction";
			break;
		case SIGSEGV:
			pSigMsg = "Segment violation";
			break;
		}

	sendChatf(-1, "^RFatal error in script #%d: %s", myScript(), pSigMsg);

	longjmp(gJmpEnv, 1);
}

void SafeMain();

void main()
{
	void (*pPrevSIGABRT)(int);
	void (*pPrevSIGFPE)(int);
	void (*pPrevSIGILL)(int);
	void (*pPrevSIGSEGV)(int);

	pPrevSIGABRT = signal(SIGABRT, SignalHandler);
	pPrevSIGFPE = signal(SIGFPE, SignalHandler);
	pPrevSIGILL = signal(SIGILL, SignalHandler);
	pPrevSIGSEGV = signal(SIGSEGV, SignalHandler);

	if (setjmp(gJmpEnv) == 0)
		SafeMain();

	signal(SIGABRT, pPrevSIGABRT);
	signal(SIGFPE, pPrevSIGFPE);
	signal(SIGILL, pPrevSIGILL);
	signal(SIGSEGV, pPrevSIGSEGV);
}

#define main SafeMain*/
#endif
