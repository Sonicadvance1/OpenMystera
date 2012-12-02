#include <SDL/SDL.h>
//#include "censor.h"
#include "zlib.h"
#include "console.h"
#include "gameserver.h"
#include "net.h"
#include "md5.h"
#include "netstructs.h"

#include "script_commands.h"


#define strcon(a,b)		strstr(a,b)!=NULL
#define MAP_PLAYERS(_map_,_count_)  for(_count_=0;_count_<map_bucket[_map_].size();_count_++)if(player[map_bucket[_map_][_count_]].type==PLAYER)

cGameServer::cGameServer()
{
	version=1.37f;
	client_version=0.984f;
	serverPort=20005;//20005
	done=0;
	numPlayers=0;
	numConnections=0;
	numSaves=0;
	newbieLevel=0;
	benchmark_time=0;
	benchmark_loop=0;
	benchmark_flag=1;
	benchmark_iterations=0;
	ml_hour=12;
	metaPost=0; // lets leave this at 0
	chatLog=0;
	ml_cycle[0]=45;
	ml_cycle[1]=45;
	ml_cycle[2]=45;
	ml_cycle[3]=45;
	ml_cycle[4]=45;
	ml_cycle[5]=52;
	ml_cycle[6]=64;
	ml_cycle[7]=76;
	ml_cycle[8]=88;
	ml_cycle[9]=100;
	ml_cycle[10]=100;
	ml_cycle[11]=100;
	ml_cycle[12]=100;
	ml_cycle[13]=100;
	ml_cycle[14]=100;
	ml_cycle[15]=100;
	ml_cycle[16]=100;
	ml_cycle[17]=100;
	ml_cycle[18]=100;
	ml_cycle[19]=88;
	ml_cycle[20]=76;
	ml_cycle[21]=64;
	ml_cycle[22]=52;
	ml_cycle[23]=45;

	//load chatlog
	chatLog = fopen("serverdata/server.log","a");
	debugLog = fopen("serverdata/debug.log","a");
}

int cGameServer::initialize()
{
	// initialize SDL
	if(SDL_Init(SDL_INIT_TIMER | SDL_INIT_NOPARACHUTE)==-1)
	{
		newLine("SDL_Init: %s\n",SDL_GetError());
		return 0;
	}
	
	//load maps
	char filename[32];
	int i=-1;
	while(1)
	{
		i++;
		if(i==world.size())
			world.size((world.size()*2) +1);
		sprintf(filename,"serverdata/maps/map%d.dat",i);
		if(!loadData(&world[i],sizeof(cMap),filename))
			break;
	}
	newLine("Maps loaded up to %d",world.size());
	//cache maps
	map_bucket.size(world.size());
	map_cache.size(world.size());
	for(int c=0;c<world.size();c++)
		compressInto(c);

	//connect to db
	if(!mydb.connect())
	{
		newLine("Could not connect to the mysql database...");
		return 0;
	}

	//load item/npc templates
	loadITEMfile();
	loadNPCfile();

	//load map items from db into array
	mydb.loadMapItems(&ml_items);

	//load scripts
	mlscript.loadAll();

	//load npcs
	for(int k=0;k<world.size();k++)
		loadNPC(k);

	//Write out again for formatting
	writeNPCfile();
	writeITEMfile();

	//convert server title's spaces
	i=0;
	int p=0;
	for(i=0;i<int(strlen(server_title))+1;i++)
	{
		if(server_title[i]==' '||server_title[i]==','||server_title[i]==':'||server_title[i]==';')
		{
			servTitle[p]='%';
			p++;
			servTitle[p]='2';
			p++;
			servTitle[p]='0';
		}
		else 
			servTitle[p]=server_title[i];
		p++;
	}

	DEBUGLOG("Server started");

	return 1;
}

void cGameServer::shutdownServer()
{
	DEBUGLOG("Shutdown beginning");
	done=1;
	newLine("*Shutting Down*\n");
	/*
	//tell auto we shutdown
	FILE *f = fopen("ns","w");
	if(f)
	{
		fprintf(f,"%d",-24);
		fclose(f);
	}*/
	//save all player accounts
	for(int i=0;i<player.size();i++)
		if(player[i].access>0&&player[i].type==PLAYER)
			mydb.updatePlayer(&player[i]);
	DEBUGLOG("Accounts saved");
	mydb.disconnect();
	DEBUGLOG("DB disconnect");
	fprintf(chatLog,"*Shutting Down*\n");
	DEBUGLOG("printed shutdown to chatlog");
	if(chatLog!=0)
		fclose(chatLog);
	DEBUGLOG("closed chatlog");

	nh.shutdown();
	DEBUGLOG("Net layer shutdown");
	
	SDL_Quit();
	DEBUGLOG("SDL Quit");
	mlscript.freeAll();
	DEBUGLOG("Scripts freed");
	if(debugLog!=0)
		fclose(debugLog);
	DEBUGLOG("Debug log closed");
}

int cGameServer::loadConfig()
{
	FILE *f = fopen("serverdata/serv.cfg","r");
	if(f!=NULL)
	{
		fscanf(f,"[Name]%[^\n]\n",server_title);
		fscanf(f,"[Port]%d\n",&serverPort);
		fscanf(f,"[Greeting]%[^\n]\n",server_welcome);
		fscanf(f,"[Admin]%[^\n]\n",admin_name);
		fscanf(f,"[Force IP]%[^\n]\n",myIP);
		fscanf(f,"[Post]%d\n",&metaPost);
		fscanf(f,"[Newbie Level]%d\n",&newbieLevel);
		fscanf(f,"[Origin]%d %d %d\n",&origin_map,&origin_x,&origin_y);
		fclose(f);
		return 1;
	}
	return 0;
}

void cGameServer::consoleInput(const char *chat)
{
	if(chat[0]=='/')
	{
		parse(chat,-45);
		newLine(chat);
		
		fwrite(chat, 1, sizeof(chat), chatLog);	
	}
	else
	{
		//CENSOR.star(chat); (need to either remove or fix censoring)
		sendChatMsg(ALL_CLIENTS,"^Y[SERVER]:%s",chat);
		newLine(chat);
		fwrite(chat, 1, sizeof(chat), chatLog);	
	}
}

void cGameServer::loadNPCfile()
{
	if(!fileExists("serverdata/npc.ml")) return;
	FILE *f=fopen("serverdata/npc.ml","r");
	char line[64];
	int npc=-1,temp;
	while(!feof(f))
	{
		fgets(line,64,f);
		if(feof(f))
			break;
		if(line[0]=='[')
		{
			npc++;
			if(npc>=mnl.size())
				mnl.size((npc+1)*(npc+1));
			if(mnl.size()>ml_loot.loot.size())
				ml_loot.loot.size(mnl.size());
			ml_loot.loot[npc].reset();
			sscanf(line,"[%[^]]]",mnl[npc].name);
			mnl[npc].player_template=npc;
		}
		else
		{
			if(strcon(line,"img="))
			{
				sscanf(line,"img=%d",&temp);
				mnl[npc].sprite = temp;
			}
			else if(strcon(line,"body="))
			{
				sscanf(line,"body=%d",&temp);
				mnl[npc].body=temp;
			}
			else if(strcon(line,"clothes="))
			{
				sscanf(line,"clothes=%d",&temp);
				mnl[npc].clothes=temp;
			}
			else if(strcon(line,"hair="))
			{
				sscanf(line,"hair=%d",&temp);
				mnl[npc].hair=temp;
			}
			else if(strcon(line,"type="))
				sscanf(line,"type=%d",(int*) &mnl[npc].state);
			else if(strcon(line,"atk="))
			{
				sscanf(line,"atk=%d",&temp);//because they are shorts and funny
				mnl[npc].atk = temp;
			}
			else if(strcon(line,"def="))
			{
				sscanf(line,"def=%d",&temp);
				mnl[npc].def = temp;
			}
			else if(strcon(line,"mhp="))
			{
				sscanf(line,"mhp=%d",&temp);
				mnl[npc].mhp = temp;
			}
			else if(strcon(line,"chatscript="))
			{
				sscanf(line,"chatscript=%d",&temp);
				mnl[npc].chat_script = temp;
			}
			else if(strcon(line,"movescript="))
			{
				sscanf(line,"movescript=%d",&temp);
				mnl[npc].move_script = temp;
			}
			else if(strcon(line,"rng="))
				sscanf(line,"rng=%d",(int*) &mnl[npc].range);
			else if(strcon(line,"exp="))
			{
				sscanf(line,"exp=%d",&temp);
				mnl[npc].worth = temp;
			}
			else if(strcon(line,"loot="))
			{
				int qty,index,chance;
				sscanf(line,"loot=%d,%d,%d",&index,&qty,&chance);
				if(index<mil.size())
				{
					if(mil[index].stack!=STACKABLE)
							qty=-1;
					ml_loot.addLoot(npc,index,qty,chance);
				}
			}
		}
	}
	mnl.size(npc+1);
	ml_loot.loot.size(npc+1);
	newLine("%d NPC templates loaded.",npc+1);
	fclose(f);
}

void cGameServer::writeNPCfile()
{
	FILE *f=fopen("serverdata/npc.ml","w");
	int l;
	for(int i=0;i<mnl.size();i++)if(strcmp(mnl[i].name,"_EMPTY_")!=0)
	{
		fprintf(f,"\n[%s] (%d)\n",mnl[i].name,i);
		fprintf(f,"img=%d\n",int(mnl[i].sprite));
		fprintf(f,"body=%d\n",int(mnl[i].body));
		fprintf(f,"clothes=%d\n",int(mnl[i].clothes));
		fprintf(f,"hair=%d\n",int(mnl[i].hair));
		fprintf(f,"type=%d\n",mnl[i].state);
		fprintf(f,"atk=%d\n",int(mnl[i].atk));
		fprintf(f,"def=%d\n",int(mnl[i].def));
		fprintf(f,"mhp=%d\n",int(mnl[i].mhp));
		fprintf(f,"rng=%d\n",int(mnl[i].range));
		fprintf(f,"exp=%d\n",int(mnl[i].worth));
		fprintf(f,"chatscript=%d\n",int(mnl[i].chat_script));
		fprintf(f,"movescript=%d\n",int(mnl[i].move_script));
		for(l=0;l<MAX_INV;l++)if(ml_loot.loot[i].loot[l].qty!=0)
			fprintf(f,"loot=%d,%d,%d\n",ml_loot.loot[i].loot[l].index,abs(ml_loot.loot[i].loot[l].qty),ml_loot.loot[i].loot[l].chance);
	}
	fclose(f);
}

void cGameServer::loadITEMfile()
{
	if(!fileExists("serverdata/item.ml"))
		return;
	FILE *f=fopen("serverdata/item.ml","r");
	char line[64];
	int item=-1,temp;

	while(!feof(f))
	{
		fgets(line,64,f);
		if(feof(f))
			break;
		if(line[0]=='[')
		{
			item++;
			if(item>=mil.size())
				mil.size((item+1)*(item+1));
			sscanf(line,"[%[^]]]",mil[item].name);
			mil[item].item_template=item;
		}
		else
		{
			if(strcon(line,"img="))
			{
				sscanf(line,"img=%d",&temp);
				mil[item].graphic=temp;
			}
			else if(strcon(line,"type="))
			{
				sscanf(line,"type=%d",&temp);
				mil[item].type=temp;
			}
			else if(strcon(line,"stack="))
			{
				sscanf(line,"stack=%d",&temp);
				mil[item].stack=temp;
			}
			else if(strcon(line,"atk="))
			{
				sscanf(line,"atk=%d",&temp);
				mil[item].atk = temp;
			}
			else if(strcon(line,"def="))
			{
				sscanf(line,"def=%d",&temp);
				mil[item].def = temp;
			}
			else if(strcon(line,"uses="))
			{
				sscanf(line,"uses=%d",&temp);
				mil[item].uses=temp;
			}
			else if(strcon(line,"script="))
			{
				sscanf(line,"script=%d",&temp);
				mil[item].use_script = temp;
			}
			else if(strcon(line,"cooldown="))
			{
				sscanf(line,"cooldown=%d",&temp);
				mil[item].total_cooldown = temp;
			}
			else if(strcon(line,"weight="))
			{
				float temp_float;
				sscanf(line,"weight=%f",&temp_float);
				mil[item].weight = temp_float;
			}
		}
	}
	mil.size(item+1);
	newLine("%d item templates loaded.",item+1);
	fclose(f);
}

void cGameServer::writeITEMfile()
{
	FILE *f=fopen("serverdata/item.ml","w");
	for(int i=0;i<mil.size();i++)if(strcmp(mil[i].name,"_EMPTY_")!=0)
	{
		fprintf(f,"\n[%s] (%d)\n",mil[i].name,i);
		fprintf(f,"img=%d\n",int(mil[i].graphic));
		fprintf(f,"type=%d\n",int(mil[i].type));
		fprintf(f,"stack=%d\n",int(mil[i].stack));
		fprintf(f,"atk=%d\n",int(mil[i].atk));
		fprintf(f,"def=%d\n",int(mil[i].def));
		fprintf(f,"uses=%d\n",int(mil[i].uses));
		fprintf(f,"script=%d\n",int(mil[i].use_script));
		fprintf(f,"cooldown=%d\n",int(mil[i].total_cooldown));
		fprintf(f,"weight=%f\n",float(mil[i].weight));
	}
	fclose(f);
}

void cGameServer::scheduler()
{
	CHARLOG('a');
	//set check flags
	ai=aiClock.tick(750);
	updt=updateTimer.tick(250);
	check = checkClock.tick(2000);

	//send out effects
	if(effectTimer.tick(200))
	{
		char buf[5000];
		int map,len=effect_batch.size();
		map = 0;
		while(map!=-1)
		{
			int i=0;
			while(i<len && effect_batch[i].index==-1)
				i++;
			if(i<len)
			{
				map=effect_batch[i].map;
				efpk_msg eff;eff.type=EFCT_MSG;
				efct_msg efct;
				eff.qty=0;
				for(int c=0;c<len;c++)if(effect_batch[c].index>-1 && effect_batch[c].map==map)
				{
					efct.index=(unsigned char)effect_batch[c].index;
					efct.x=effect_batch[c].x;
					efct.y=effect_batch[c].y;
					if(eff.qty<255)
					{
						memcpy(buf+sizeof(efpk_msg)+(eff.qty*sizeof(efct_msg)),(void *)&efct,sizeof(efct_msg));
						eff.qty++;
					}
					effect_batch[c].index=-1;
				}
				memcpy(buf,(void *)&eff,sizeof(efpk_msg));//store header
				int len = sizeof(efpk_msg)+(eff.qty*sizeof(efct_msg));
				int count;
				MAP_PLAYERS(map,count)
					nh.send((unsigned char *)&buf,len,SEND_NON_GUARANTEED,itod(map_bucket[map][count]));
			}
			else map=-1;
		}
	}
	//increment day cycle
	if(ml_time.tick(450000))
	{
		ml_hour++;
		if(ml_hour>23)
			ml_hour=0;
		sendShade(ALL_CLIENTS,ml_cycle[ml_hour]);
	}
	//check to see if time to save accounts
	if(saveClock.tick(10000))
	{
		saveServerState();
		//write out successful saves file
		FILE *f = fopen("ns","w");
		if(f)
		{
			fprintf(f,"%d",++numSaves);
			fclose(f);
		}
	}
	//run timed scripts
	eHandler.handle(&mlscript);

	//time to repost to the metaserver <---(more like time to stop being so lame)
	//if(rePostClock.tick(60000))
	//	postServer();

	//check for ground item timeout
	if(itemTimer.tick(120000))
	{	
		for(int count=0;count<ml_items.item.size();count++)if(ml_items.item[count].qty!=0 && ml_items.item[count].map!=-1)
		{
			if(ml_items.item[count].life==0)
			{
				sendRemoveMapItem(ml_items.item[count].map,ml_items.item[count].x,ml_items.item[count].y);
				removeItem(count);
			}
			else if(ml_items.item[count].stack!=PERMANENT&&world[ml_items.item[count].map].map[ml_items.item[count].y][ml_items.item[count].x].type!=KEEP)
			{
				ml_items.item[count].life--;
			}
		}
	}
}

void cGameServer::checkPlayers()
{
	CHARLOG('b');
	//benchmarking
	if(benchmark_flag)
	{
		benchmark_loop++;
		if(SDL_GetTicks()-benchmark_time>5000)
		{
			benchmark_iterations=benchmark_loop;
			printf("Loop:%d\n",benchmark_iterations);
			benchmark_loop=0;
			benchmark_time=SDL_GetTicks();
		}
	}
	for(int count=0;count<player.size();count++)
		if(player[count].access>0)
	{
			
		//update maplists
		if(player[count].map!=player[count].current_map)
		{
			removeFromMap(count,player[count].current_map);
			player[count].current_map=player[count].map;
			addToMap(count,player[count].current_map);
		}
		
		//do constant check script
		if(check)
			mlscript.run(1001,count);
		
		//check for death
		if(player[count].hp<=0)
			doDeath(count);
		//leveling
		if(player[count].type==PLAYER&&player[count].lvl<255&&player[count].exp>=nextExp(player[count].lvl))
			doLevel(count);
		//send updates to players
		if( updt && player[count].type == PLAYER)
		{
			sendUpdtMsg(itod(count),count);
			//also do
			
			if(player[count].serenity!=0)
			{
				player[count].serenity--;
				if(player[count].serenity==0)
					sendPlyrMsg(count);
			}
			player[count].stationary++;
			player[count].time_safe++;
			
		}
		//Checks Limits here

		//NPC Movement
		if(player[count].type==NPC && ai)
		{
			int spawn = player[count].total_time;
			if(spawn>0)//respawn check
			{
				int ppl_present = 0;
				int k;
				for(k=0;k<map_bucket[player[count].map].size();k++)
					if(player[map_bucket[player[count].map][k]].type==PLAYER)
						ppl_present = 1;

				if(ppl_present)
					spawn-=1;
				else
					spawn-=3;

				//printf("%d\n",spawn);

				if(spawn<0)
					spawn=0;

				player[count].total_time = spawn;
			}
			else
			{
				if(player[count].move_script>-1)
					mlscript.run(player[count].move_script,count);
				else 
					doNpcMove(count);
			}
		}
	}
	CHARLOG('c');
}

void cGameServer::compressInto(int mapid)
{
	unsigned long len=sizeof(cMap);
	compress2((unsigned char *)&map_cache[mapid].buf, &len,(unsigned char *)&world[mapid], (unsigned long)len,9);
	map_cache[mapid].size=len;
}

void cGameServer::loadNPC(int k)//load npcs on kth map
{
	int c,n,i;
	for(c=0;c<4;c++)//every npc slot
	{
		if(world[k].npc[c].index>-1)//if npc to load
		{
			if(world[k].npc[c].qty>20)
				world[k].npc[c].qty=20;
			for(i=0;i<world[k].npc[c].qty;i++)//load number of npcs specified
			{
				n=0;
				if(n==player.size())
						player.size(n+100);
				while(player[n].access>-1)
				{
					n++;
					if(n==player.size())
						player.size(n+100);
				}
				if(world[k].npc[c].index>-1&&world[k].npc[c].index<mnl.size())
				{
					player[n]=mnl[world[k].npc[c].index];//load player
					player[n].randomize();//randomize players starting location
					player[n].origin_map=k;
					player[n].map=k;
					player[n].access=1;
					player[n].type=NPC;
					player[n].hp = player[n].mhp;
					player[n].mp = player[n].mmp;
					int x=0;
					while(world[player[n].map].map[player[n].y][player[n].x].type!=OPEN || world[player[n].map].map[player[n].y][player[n].x].space!=VACANT)
					{
						player[n].randomize();
						x++;
						if(x>300)
							break;
					}
					if(x>300)
					{
						int r1,c1;
						for(r1=0;r1<MAP_ROWS;r1++)
							for(c1=0;c1<MAP_COLS;c1++)
								if(world[player[n].map].map[c1][r1].type==OPEN && world[player[n].map].map[c1][r1].space==VACANT)
								{
									player[n].x=c1;
									player[n].y=r1;
									c1=MAP_COLS;
									r1=MAP_ROWS;
									x=0;
								}
						
					}
					if(x>300)
					{
						newLine("map %d too crowded!\n",player[n].map);
						player[n].x=0;
						player[n].y=0;
					}
					else
						world[player[n].map].map[player[n].y][player[n].x].space=n;
					//load inventory items
					doNpcFill(n);
				}
			}
		}
	}
}

void cGameServer::saveServerState()
{
	//save players
	for(int count=0;count<player.size();count++)
		if(player[count].access>0 && player[count].type==PLAYER)
			mydb.updateCorePlayer(&player[count]);
}


PlayerID cGameServer::itod(int ind)
{
	return player[ind].pid;
}

int cGameServer::dtoi(PlayerID did)
{
	for(int i=0;i<player.size();i++)
		if(did==player[i].pid)
			return i;
	return -1;
}

int cGameServer::ntoi(char *name)
{
	int i=0;
	char aname[256];
	char pname[256];
	strcpy(aname,name);
	stringLower(aname);

	strcpy(pname,player[i].name);
	stringLower(pname);
	while(strcmp(pname,aname)!=0)
	{
		if(i==player.size())
			return -1;
		i++;
		if(i!=player.size())
		{
			strcpy(pname,player[i].name);
			stringLower(pname);
		}
		else 
			return -1;
	}
	return i;
}

/*cList <int> cGameServer::getInventory(int id)
{
	cList <int> inv;
	int sz=0;
	inv.size(50);
	for(int i=0;i<ml_items.item.size();i++)
		if(ml_items.item[i].qty!=0 && ml_items.item[i].owner==id)
		{
			if(sz==inv.size())
				inv.size(sz*2);
			inv[sz]=i;
			sz++;
		}
	inv.size(sz);
	return inv;
}*/

int cGameServer::playerFull(int id)
{
	int amt=0;
	for(int i=0;i<ml_items.item.size();i++)
		if(ml_items.item[i].qty!=0 && ml_items.item[i].owner==id)
			amt++;
	if(amt>MAX_INV)
		return 1;
	return 0;
}

int cGameServer::playerFullOf(int id,int item)
{
	int amt=0;
	for(int i=0;i<ml_items.item.size();i++)
		if(ml_items.item[i].qty!=0 && ml_items.item[i].owner==id)
		{
			if(ml_items.item[i].item_template==item && ml_items.item[i].qty>0)
				return 0;
			amt++;
		}
	if(amt>MAX_INV)
		return 1;
	return 0;
}

//returns next available slot in player's(id) inventory
int cGameServer::nextInventorySlot(int id)
{
	/*cAutoList <int> slots;
	for(int i=0;i<ml_items.item.size();i++)
		if(ml_items.item[i].qty!=0 && 
		   ml_items.item[i].owner==id)
			slots[ml_items.item[i].slot]=1;
	for(i=0;i<slots.size();i++)
		if(slots[i]!=1)
			return i;
	return -1;*/
	for(int i=0;i<MAX_INV;i++)
		if(player[id].inventory[i]==-1)
			return i;
	return -1;
}

//returns first item of certain type in players inventory
int cGameServer::firstItem(int id,int item_template)
{
	for(int k=0;k<MAX_INV;k++)
		if(player[id].inventory[k] != -1 &&
		   ml_items.item[player[id].inventory[k]].item_template == item_template)
				return k;
	return -1;
}

void cGameServer::removeItem(int id)
{
	mydb.removeItem(ml_items.item[id].id);
	ml_items.item[id] = cItem();
}

void cGameServer::updateItem(int id)
{
	int old = ml_items.item[id].owner;
	if(old!=-1)
		ml_items.item[id].owner=(short)player[old].id;//save perm id (FUTUREHAZARD) short
	mydb.updateItem(&ml_items.item[id]);
	if(old!=-1)
		ml_items.item[id].owner=old;//restore temp id
}

void cGameServer::addItem(int id)
{
	mydb.insertItem(&ml_items.item[id]);
}

void cGameServer::addToMap(int id,int map)
{
	int i=0;
	if(map >= world.size())
	{
		world.size(map+map);
		map_cache.size(map+map);
		map_bucket.size(map+map);
	}
	if(i==map_bucket[map].size())
	{
		map_bucket[map].size(i+1);
		map_bucket[map][i]=-1;
	}
	while(map_bucket[map][i]>=0)
	{
		i++;
		if(i==map_bucket[map].size())
		{
			map_bucket[map].size(i+1);
			map_bucket[map][i]=-1;
		}
	}
	map_bucket[map][i]=id;
}

void cGameServer::removeFromMap(int id,int map)
{
	if(map<0)
		return;

	if(map>=world.size())
	{
		world.size(map+1);
		map_cache.size(map+1);
		map_bucket.size(map+1);
	}
	
	for(int i=0;i<map_bucket[map].size();i++)
	{
		if(map_bucket[map][i]==id)
		{
			map_bucket[map][i]=map_bucket[map][map_bucket[map].size()-1];
			map_bucket[map].size(map_bucket[map].size()-1);
			return;
		}
	}
}

//returns slot of topmost item at map coordinates
int cGameServer::topmostItemAt(int map,int x,int y)
{
	int i=ml_items.item.size()-1;
	while(i>=0)
	{
		if(ml_items.item[i].qty!=0 &&  //not empty
		   ml_items.item[i].map==map &&//same map
		   ml_items.item[i].x==x &&    //same x
		   ml_items.item[i].y==y)      //same y
			return i;//this is it
		i--;
	}
	return -1;
}

int cGameServer::missBonus(int num)
{
	if(rand()%1024 <= 255-(num*3))
		return 1;
	return 0;
}

int cGameServer::hpBonus(int num)
{
	return num/2;
}

int cGameServer::manaBonus(int num)
{
	return num/2;
}

int cGameServer::expBonus(int num, int lvl)
{
	//return num * (lvl/4);
	UNUSED(lvl);
	return int(float(num) * 1.5f);
}

int cGameServer::strBonus(int num)
{
	return num / 3;
}

int cGameServer::conBonus(int num)
{
	return num / 4;
}

int cGameServer::equippedAttack(int index)
{
	int atk=0;
	if(player[index].eLeft>-1)
		atk+=ml_items.item[player[index].inventory[player[index].eLeft]].atk;
	if(player[index].eRight>-1)
		atk+=ml_items.item[player[index].inventory[player[index].eRight]].atk;
	if(player[index].eHead>-1)
		atk+=ml_items.item[player[index].inventory[player[index].eHead]].atk;
	if(player[index].eBody>-1)
		atk+=ml_items.item[player[index].inventory[player[index].eBody]].atk;
	if(player[index].eSpecial>-1)
		atk+=ml_items.item[player[index].inventory[player[index].eSpecial]].atk;
	return atk;
}

int cGameServer::equippedDefense(int index)
{
	int def=0;
	if(player[index].eLeft>-1)
		def+=ml_items.item[player[index].inventory[player[index].eLeft]].def;
	if(player[index].eRight>-1)
		def+=ml_items.item[player[index].inventory[player[index].eRight]].def;
	if(player[index].eHead>-1)
		def+=ml_items.item[player[index].inventory[player[index].eHead]].def;
	if(player[index].eBody>-1)
		def+=ml_items.item[player[index].inventory[player[index].eBody]].def;
	if(player[index].eSpecial>-1)
		def+=ml_items.item[player[index].inventory[player[index].eSpecial]].def;
	return def;
}

int cGameServer::wouldAttack(int index,int victim)
{
	//calculate damage
	int dmg = (player[index].atk + equippedAttack(index) + strBonus(player[index].str)) - (player[victim].def + equippedDefense(victim) + conBonus(player[victim].con));
	//apply randomness
	dmg+=rand()%5-2;
	if(dmg<0)
		dmg=0;
	return dmg;
}

int cGameServer::nameOnline(char *name)
{
	char thename[256];
	strcpy(thename,name);
	stringLower(thename);
	char aname[256];
	for(int i=0;i<player.size();i++)
	{
		strcpy(aname,player[i].accid);
		stringLower(aname);
		if(player[i].access>=0 && strcmp(thename,aname)==0)
			return 1;
	}
	return 0;
}

int cGameServer::findIP(char *ip)
{
	for(int i=0;i<player.size();i++)
		if(player[i].access>0 && strcmp(ip,player[i].ip)==0)
			return i;
	return -1;
}

void cGameServer::unequipSlot(int id,int slot)
{
	char flag=0;
	if(player[id].eLeft == slot)
	{
		player[id].eLeft=-1;
		flag=1;
	}
	if(player[id].eRight == slot)
	{
		player[id].eRight=-1;
		flag=1;
	}
	if(player[id].eHead == slot)
	{
		player[id].eHead=-1;
		flag=1;
	}
	if(player[id].eBody == slot)
	{
		player[id].eBody=-1;
		flag=1;
	}
	if(player[id].eSpecial == slot)
	{
		player[id].eSpecial=-1;
		flag=1;
	}
	if(flag)
	{
		mydb.updateEquipPlayer(&player[id]);
		sendEquipMsg(id);
	}
}

float cGameServer::getWeight(int id)
{
	float weight = 0;
	for(int i = 0; i < MAX_INV; i++)
	{
		if(player[id].inventory[i] !=-1)
		{
			if(ml_items.item[player[id].inventory[i]].qty > 0)
			{
				weight += ml_items.item[player[id].inventory[i]].weight * ml_items.item[player[id].inventory[i]].qty;
			}
			else
			{
				weight += ml_items.item[player[id].inventory[i]].weight;
			}
		}
	}
	return weight;
}

int cGameServer::maxWeight(int id)
{
	return player[id].str * 50;
}

int cGameServer::nextExp(int lvl)
{
	return int(100*(lvl*lvl));
}

