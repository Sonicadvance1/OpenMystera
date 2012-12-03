#ifndef _MLGAMESERVER_
#define _MLGAMESERVER_

#include "mysql_db.h"
#include "script_system.h"
#include "List.h"
#include "utils.h"
#include "net.h"
#include <SDL/SDL_thread.h>

#ifdef _WIN32
#define _MLF extern "C" __declspec( dllexport ) 
#else
#define _MLF
#endif
//#define DEBUGLOG(x) fprintf(debugLog,"%s %d\n",x,time(0))
//#define CHARLOG(x) fputc(x,debugLog)
//#define DEBUGLOG(x) { printf("%s %d\n",x,time(0)); }
#define DEBUGLOG(x) { }
#define CHARLOG(x) { }

struct mapbox
{
	char buf[1000];
	int size;
};

struct cEffect
{
	signed short index;
	unsigned short map;
	unsigned char x;
	unsigned char y;
	cEffect()
	{
		index=-1;
	}
};

class cGameServer
{
public:

	int		numConnections,
			numPlayers,
			numSaves,
			port,
			benchmark_time,
			benchmark_loop,
			benchmark_flag,
			benchmark_iterations,
			done,
			last_chatter,
			ml_hour,
			ai,
			updt,
			check,
			newbieLevel,
			metaPost,
			serverPort,
			origin_map,
			origin_x,
			origin_y,
			num_effects;

	int ml_cycle[24];

	char	myIP[64],
			server_title[64], 
			server_welcome[128], 
			admin_name[16], 
			admin_pass[16],
			char_tiles[16],
			tile_tiles[16],
			last_chat[256],
			last_command[256],
			post_string[512],
			servTitle[512];

	FILE	*chatLog;
	FILE    *debugLog;

	float version;
	float client_version;
	
	timer ml_time,
		  checkTimer,
		  aiClock,
		  checkClock,
		  spawnClock,
		  saveClock,
		  shutdownClock,
		  rePostClock,
		  updateTimer,
		  itemTimer,
		  packetTimer,
		  regenTimer,
		  effectTimer;

	cList	<cEffect> effect_batch;
	cList	<cList <int> > map_bucket;
	cList	<cPlayer> player;
	cList	<cPlayer> mnl;
	cList	<cItem> mil;
	cList	<cMap>	world;
	cList	<mapbox> map_cache;

	SDL_Thread *post_thread;

	cScriptSystem mlscript;
	mysqlDB mydb;
	cItemList ml_items;
	serverLoot ml_loot;
	cGlobalHandler gHandler;
	cEventHandler eHandler;

	netServer nh;

	//server functions
	cGameServer();
	int initialize();
	void shutdownServer();
	int loadConfig();
	void consoleInput(const char *chat);
	int parse(const char *str,signed short index);
	void writeITEMfile();
	void loadITEMfile();
	void writeNPCfile();
	void loadNPCfile();
	void checkPlayers();
	void scheduler();
	void saveServerState();
	void postServer();

	//messages
	void sendChatMsg(PlayerID pid, const char *fmt,...);
	void sendAttrMsg(PlayerID pid,int id);
	void sendLevlMsg(PlayerID pid,int id);
	void sendMycrMsg(PlayerID pid,int id);
	void sendAcssMsg(PlayerID pid,int id);
	void sendUpdtMsg(PlayerID pid,int id);
	void sendUpldMsg(PlayerID pid,int mapid);
	void sendPlayerVMsg(int index);
	void sendItemVMsg(int index);
	void sendPlyrMsg(int id);
	void sendEquipMsg(int id);
	void sendHPMsg(int id);
	void sendMPMsg(int id);
	void sendEXPMsg(int id);
	void sendAddMapItem(int graphic,int map,int x,int y);
	void sendRemoveMapItem(int map,int x,int y);
	void sendEffect(int map,int x,int y,int effect);
	void sendSound(int map,int effect);
	void sendShade(PlayerID pid,unsigned char shade);
	void sendFile(PlayerID pid,char *filename);
	void sendInventoryRemove(PlayerID pid,signed short index,signed long quantity);
	void sendInventoryQty(PlayerID pid,signed short index,signed long quantity);
	void sendHPbar(int map,unsigned short target);
	void sendSessionInfo(PlayerID pid);
	void sendLeftMessage(unsigned short index);
	void sendInventory(PlayerID pid,unsigned short index);
	void sendParmMsg(PlayerID pid,unsigned char parm,unsigned char flag);
	void sendInventoryAdd(PlayerID pid,unsigned short graphic,char *name,unsigned char index,unsigned long quantity);


	//inventory
	int playerFull(int id);
	int playerFullOf(int id,int item);
	int nextInventorySlot(int id);
	int firstItem(int id,int item);
	void unequipSlot(int id,int slot);
	
	//map
	void addToMap(int id,int map);
	void removeFromMap(int id,int map);
	void compressInto(int mapid);
	void loadNPC(int k);

	//item stuff
	int topmostItemAt(int map,int x,int y);
	void removeItem(int id);
	void updateItem(int id);
	void addItem(int id);

	//player stuff
	void doDeath(int id);
	void doLevel(int id);
	void doDrop(int id,int slot,int qty);
	void doDrop(int id,int slot);
	void doPickup(int id);
	void doAction(int id);
	void doEquip(int id,int slot);
	void doUnequip(int id,int slot);
	void doMove(int id,int map,int x,int y);
	void doLogout(int id);
	int doLogin(int id,int slot);
	void doCreateAccount(int id,char *pass,char *conf,char *email);
	void doCreate(int id,char *name,int body,int clothes,int hair,int *player_id);
	int doDelete(char *name);
	float getWeight(int id);
	int maxWeight(int id);

	//npc stuff
	void doNpcMove(int id);
	void doNpcFill(int id);

	//stats
	int missBonus(int num);
	int hpBonus(int num);
	int manaBonus(int num);
	int expBonus(int num, int lvl);
	int strBonus(int num);
	int conBonus(int num);
	int wouldAttack(int index,int victim);
	int equippedAttack(int index);
	int equippedDefense(int index);
	int nextExp(int lvl);

	//utils
	PlayerID itod(int ind);
	int dtoi(PlayerID did);
	int ntoi(char *name);
	int nameOnline(char *name);
	int findIP(char *ip);
	
	//msg handler stuff
	void onConnect(PlayerID pid,char *ip);
	void onDisconnect(PlayerID pid);
	void onMessage(unsigned char *data,unsigned long dataSize,PlayerID pid,unsigned char type);
};

#endif

