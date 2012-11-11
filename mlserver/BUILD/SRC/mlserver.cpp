
//libraries
#if defined(_MSC_VER)
#   pragma comment(lib,"zlib.lib")
#   pragma comment(lib,"sdlmain.lib")
#   pragma comment(lib,"sdl.lib")
#   pragma comment(lib,"WSOCK32.lib")
#endif

#include <SDL/SDL_thread.h>

#include "script_commands.h"
#include "net.h"

#include "console.h"
#include "gameserver.h"
#include "consoleport.h"

cGameServer mlserver;
unsigned long live_counter=1;

void netServer::onConnect(PlayerID cid,char *ip_address)
{
	mlserver.onConnect(cid,ip_address);
}
void netServer::onDisconnect(PlayerID cid)
{
	mlserver.onDisconnect(cid);
}
void netServer::onReceive(unsigned char *data,int size,PlayerID cid)
{
	mlserver.onMessage(data,size,cid,data[0]);
}
void netClient::onReceive(unsigned char *data,int size){}

int checkAlive(void *unused)//rough way to see if the server has stalled (blocking send)
{
	int *done=(int *)unused;
	unsigned long check_counter,num=0;
	while(1)
	{
		check_counter=live_counter;
		SDL_Delay(1000);
		if(check_counter==live_counter)
			num++;
		else
			num=0;
		if(num>10)
			break;
	} 
	cs.Enter();
	*done=1;
	cs.Leave();
	return 0;
}

int keyPress(void *unused)
{
	char c;
	int curpos=0;
	char input[256];
	strcpy(input,"");
	int *done=(int *)unused;
	while(!*done)
	{
		c=getch();
		if(c=='Q')//quit
		{
			cs.Enter();
			*done=1;
			cs.Leave();
		}
		else if(c=='P')
		{
			newLine("Reposting.");
			mlserver.postServer();
		}
		else if(c==13)
		{
			while(!*done)
			{
				gotoxy(0,23);
				setrgb(4);
				printf("Send:%s",input);
				for(int i=75-c;i>=0;i--)
					putc(' ',stdout);
				putc('\r',stdout);
				setrgb(0);
				c=getch();
				if(c==13)
				{
					mlserver.consoleInput(input);
					strcpy(input,"");
					curpos=0;
					break;
				}
				else if(c==10 && curpos>0)
				{
					input[curpos]='\0';
					curpos--;
					input[curpos]='\0';
				}
				else
				{
					input[curpos]=c;
					curpos++;
					input[curpos]='\0';
				}
			}
		}
		else if(c=='I')
		{
			//newLine("%d items.",mlserver.ml_items.item.size());
			//for(int i=0;i<mlserver.ml_items.item.size();i++)
			//	if(mlserver.ml_items.item[i].qty!=0)
			//		newLine("(%d) %s : %d at %d %d %d",i,mlserver.ml_items.item[i].name,mlserver.ml_items.item[i].qty,mlserver.ml_items.item[i].map,mlserver.ml_items.item[i].x,mlserver.ml_items.item[i].y);
		}
		else //list players
		{
			int count=0;
			for(int i=0;i<mlserver.player.size();i++)
				if(mlserver.player[i].access>0&&mlserver.player[i].type==PLAYER)
				{
					newLine("%s at %d,%d,%d  Access %d  Level %d  slot id %d  database id %d",mlserver.player[i].name,mlserver.player[i].map,mlserver.player[i].x,mlserver.player[i].y,mlserver.player[i].access,mlserver.player[i].lvl,i,mlserver.player[i].id);
					count++;
				}
			newLine("%d players online.",count);
		}
	}
	return 0;
}

int serverLoop(void *unused)
{
	int *done=(int *)unused;
	int checkSpeed,oldSpeed=SDL_GetTicks();
	while(!*done)
	{
		//Get server speed
		checkSpeed = SDL_GetTicks()-oldSpeed;
		//Delay
		if(checkSpeed<40)
			SDL_Delay(40-checkSpeed);
		//Reset speed check
		oldSpeed = SDL_GetTicks();
		//if(rand()%50==0)
		//	printf("chat:%d\n",rand()%100);
		//Do server checks
		int res=mlserver.nh.update();
		if(res==-1)
		{
			FILE *f = fopen("error.txt","w");
			fprintf(f,"Socket set invalid.\n");
			fclose(f);
			mlserver.done=1;
		}
		if(mlserver.packetTimer.tick(1000))
		{
			//send udp packet
			char u=0;
			mlserver.nh.send((unsigned char *)&u,1,SEND_NON_GUARANTEED,ALL_CLIENTS);
		}
		mlserver.scheduler();
		mlserver.checkPlayers();
		live_counter++;
	}
	return 0;
}

void ScriptSignalHandler(int Signal)
{
	newLine("@@@@@@@@ Fatal Signal %d in Script %d @@@@@@@@",Signal,mlserver.mlscript.getScript());
	FILE *er = fopen("FatalErrorLog.txt","a");
	fprintf(er,"@@@@@@@@ Fatal Signal %d in Script %d @@@@@@@@\n",Signal,mlserver.mlscript.getScript());
	fclose(er);
	mlserver.shutdownServer();
}

int main(int argc,char *argv[])
{
	LoadLibrary("exchndl.dll");

	srand(time(0));

	//Create key command thread
	SDL_Thread *thread = SDL_CreateThread(keyPress,(void *)&mlserver.done);

	//Set callbacks and pointers
	setScriptCommandGameServer(&mlserver);

	//Startup sockets for cgi posting
	startupWinsock();

	//print header
	newLine("Mystera Legends Beta Server %.2f - James Hamer 2004",mlserver.version);
	
	//load server configuration file
	if(!mlserver.loadConfig())
	{
		newLine("No serv.cfg file!\n");
		return 1;
	}

	//print title/ip/port
	newLine("%s\n",mlserver.server_title);
	if(mlserver.myIP[0]=='0')
		strcpy(mlserver.myIP,mlserver.nh.getip());
	newLine("IP Address:%s\n",mlserver.myIP);
	newLine("Port:%d\n",mlserver.serverPort);

	//Initialize Server
	newLine("Loading World...\n");
	if(!mlserver.initialize())
	{
		newLine("Error initializing...will shut down.\n");
		cs.Enter();
		mlserver.done=1;
		cs.Leave();
	}
	//print players
	newLine("%d players found in %d accounts.\n",mlserver.mydb.numPlayerAccounts(),mlserver.mydb.numAccounts());

	//Host server on port
 	newLine("Hosting Server...\n");
	mlserver.serverPort = 20005;
	if(!mlserver.nh.host(mlserver.serverPort))
	{
		newLine("Error hosting...will shut down.\n");
		cs.Enter();
		mlserver.done=1;
		cs.Leave();
	}

	//Post on metaserver
	mlserver.postServer();

	//Create main loop thread
	newLine("*Running*\n");

	fprintf(mlserver.chatLog,"*Running*\n");
	mlserver.mlscript.run(1000,-1);//run startup script

	SDL_Thread *sthread = SDL_CreateThread(serverLoop,(void *)&mlserver.done);

	//serverLoop((void *)&mlserver.done);
	//SDL_Thread *cthread = SDL_CreateThread(checkAlive,(void *)&mlserver.done);

	while(!mlserver.done)
		SDL_Delay(100);
	//Shutdown
	//SDL_KillThread(cthread);
	SDL_KillThread(sthread);
	SDL_KillThread(thread);
	mlserver.shutdownServer();
	DEBUGLOG("exit program - return 0");
	return 0;
}

/*
--main components
[NETWORK] (nethandler.h)
[CONSOLE] (console.h)
[DATABASE] (mysqldb.h)
[SCRIPTING] (script_commands.h,script_system.h)
[PLAYER] (gamedefs.h)
[MAPS] (gamedefs.h)
[ITEMS] (gamedefs.h)
[CHECKS] (gameserver.h)
[SAVING] (gameserver.h)

--utils
[LIST]
[AUTOLIST]
[CENSOR]

*/
