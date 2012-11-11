#include <unistd.h>
#include "censor.h"
#include "console.h"
#include "gameserver.h"
#include "net.h"

int cGameServer::parse( const char *str,signed short index)
{
	if(str==NULL)
		return 0;
	if(str[0]=='/')
	{
		char com[128],pm1[128],pm2[128],pm3[128],pm4[128];
		sscanf(str,"/%s %s %s %s %s",com,pm1,pm2,pm3,pm4);

		if(strcmp(com,"scout")==0 &&index>-1&& player[index].access>5)
		{
			int i=0;
			while(i<world.size())
			{
				if(strcmp("_EMPTY_",world[i].name)==0)
					break;
				i++;
			}	
			sendChatMsg(itod(index),"^wNext unused map:%d",i);
		}
		else if(strcmp(com,"check")==0 &&index>-1&& player[index].access>7)
		{
			int i=0;
			char sc[128];
			while(i<1000)
			{
				sprintf(sc,"serverdata/scripts/%d.txt",i);
				if(!fileExists(sc))
					break;
				i++;
			}
			sendChatMsg(itod(index),"^wNext script should be:%d",i);
		}
		else if(strcmp(com,"shutdown")==0 && (index==-45||(index>-1&& player[index].access>9)))
		{			
			done=1;
		}
		else if(strcmp(com,"quiet")==0 && (index==-45||(index>-1&& player[index].access>9)))
		{
			
			quietMode = abs(quietMode-1);
			 
		}
		else if(strcmp(com,"reload")==0 &&(index==-45||(index>-1&& player[index].access>7)))
		{
			
			loadITEMfile();
			loadNPCfile();
			int hp,mp,index,target,x,y,map,ox,oy,omap;
			for(int c=0;c<player.size();c++)if(player[c].access>0 && player[c].type==NPC)
			{
				index = player[c].player_template;
				ox=player[c].origin_x;
				oy=player[c].origin_y;
				omap=player[c].origin_map;
				target=player[c].target;
				x=player[c].x;
				y=player[c].y;
				map=player[c].map;
				hp=player[c].hp;
				mp=player[c].mp;

				player[c]=mnl[index];
				
				player[c].x=x;
				player[c].y=y;
				player[c].map=map;

				player[c].hp=hp;
				player[c].mp=mp;
				player[c].origin_x=ox;
				player[c].origin_y=oy;
				player[c].origin_map=omap;
				player[c].type=NPC;
				player[c].access=1;
				player[c].target=target;
				player[c].player_template=index;

				
				doNpcFill(c);
				
			}
			
			for(int c=0;c<player.size();c++)if(player[c].access>0 && player[c].type==PLAYER)
				sendPlayerVMsg(c);
		}
		else if(strcmp(com,"delete")==0 &&(index==-45||(index>-1&& player[index].access>=10)))
		{
			
			if(doDelete(pm1))
				sendChatMsg(itod(index),"^wCharacter deleted.");
			
		}
		else if(strcmp(com,"download")==0 &&index>-1&& player[index].access>7)
		{
			char temp[64];
			if(strstr(pm1,".ml")!=NULL)//check for ml file
				sprintf(temp,"serverdata/%s",pm1);
			else
				sprintf(temp,"serverdata/scripts/%s",pm1);
			sendFile(itod(index),temp);
		}
		else if(strcmp(com,"access")==0 &&(index==-45||(index>-1&& player[index].access>8)))//TOSCRIPT
		{
			int id=atoi(pm1);
			int ac=atoi(pm2);
			if(id>=0 && id<player.size() && player[id].access>0 && ac>0 && ac<10)
			{
				
				player[id].access = ac;
				
				sendPlyrMsg(id);
				newLine("%s's permissions have been changed.",player[id].name);
				if(index!=-45)
					sendChatMsg(itod(index),"^w%s's permissions have been changed.",player[id].name);
				sendAcssMsg(itod(id),id);
			}
		}
		else if(strcmp(com,"train")==0 &&index>-1&& player[index].access>0)
		{
			strcpy(last_command,pm1);
			mlscript.run(1011,index);
		}
		else if(strcmp(com,"setname")==0 &&index>-1&& player[index].access==10)
		{
			int id=atoi(pm1);
			if(id>=0 && id<player.size() && player[id].access>0&&strlen(pm2)>2&&strlen(pm2)<17)
			{
				CENSOR.star(pm2);
				for(unsigned int c=0;c<strlen(pm2);c++)
					if(pm2[c]<'A' || (pm2[c]>'Z' && pm2[c]<'a') || pm2[c]>'z')
					{
						sendChatMsg(itod(index),"^BInvalid character name. Try again.");
						return 1;
					}
				if(mydb.nameExists(pm2))
				{
					sendChatMsg(itod(index),"^BName already exists, choose another");
					return 1;
				}
				sendChatMsg(itod(index),"^wName changed.");
				
				strcpy(player[id].name,pm2);
				mydb.updatePlayer(&player[id]);
				
				sendPlyrMsg(id);
			}
		}
		else if(strcmp(com,"drop")==0 &&index>-1)//drop a portion
		{
			int slot=atoi(pm1) - 1;
			if(slot < 0 || slot >= MAX_INV)
				return 1;
			int qty=atoi(pm2);
			sprintf(last_command, "drop %d %d", slot, qty);
			mlscript.run(1008,index);
			doDrop(index,slot,qty);
		}
		else if(strcmp(com,"boot")==0 &&(index==-45||(index>-1&& player[index].access>7)))
		{
			char reason[64];
			strcpy(reason,"...");
			int id;
			sscanf(str,"/%s %d %[^\n]",com,&id,reason);
			if(id>=0 && id<player.size() && player[id].access>0)
			{
				sendChatMsg(ALL_CLIENTS,"^R%s gets booted! \"%s\"",player[id].name,reason);
				newLine("%s gets booted! \"%s\"",player[id].name,reason);
				nh.disconnect(itod(id));
			}
		}
		else if(strcmp(com,"tboot")==0 &&(index==-45||(index>-1&& player[index].access>7)))
		{
			char reason[64];
			strcpy(reason,"...");
			int id,mins;
			sscanf(str,"/%s %d %d %[^\n]",com,&id,&mins,reason);
			if(id>=0 && id<player.size() && player[id].access>0)
			{
				
				player[id].boot_time = time(0) + (mins*60);
				
				sendChatMsg(ALL_CLIENTS,"^R%s gets booted! \"%s\"",player[id].name,reason);
				newLine("%s gets booted! \"%s\"",player[id].name,reason);
				nh.disconnect(itod(id));
			}
		}
		else if(strcmp(com,"run")==0 &&index>-1&& player[index].access>7)
		{
			int id;
			sscanf(pm1,"%d",&id);
			
			mlscript.run(id,index);
			
		}
		else if(strcmp(com,"globals")==0 && index==-45)
		{
			for(int i=0;i<gHandler.g.size();i++)
			{
				if(gHandler.g[i].type==0)
					newLine("i %s %d",gHandler.g[i].name,gHandler.g[i].num);
				else if(gHandler.g[i].type==1)
					newLine("s %s %s",gHandler.g[i].name,gHandler.g[i].str);
			}
		}
		else if(strcmp(com,"chatlog")==0 &&index==-45)
		{
			unlink("serverdata/backups/chat.txt");
			
			fclose(chatLog);
			copyFile("serverdata/server.log","serverdata/backups/chat.txt");
			chatLog = fopen("serverdata/server.log","a");
		}
		else if(strcmp(com,"repost")==0 &&(index==-45||(index>-1&& player[index].access>=8)))
		{
			//postServer();
		}
		else if(strcmp(com,"compileall")==0 &&(index==-45||(index>-1&& player[index].access>=8)))
		{
			mlscript.compileAll();
		}
		else if(strcmp(com,"compile")==0 &&(index==-45||(index>-1&& player[index].access>=8)))
		{
			int id;
			sscanf(pm1,"%d",&id);
			mlscript.compile(id);
		}
		else if(strcmp(com,"benchmark")==0 &&(index==-45||(index>-1&& player[index].access>=4)))
		{
			benchmark_flag=abs(benchmark_flag-1);
			if(index==-45)
				newLine("Benchmarking=%d",benchmark_flag);
			else
				sendChatMsg(itod(index),"^wBenchmarking=%d",benchmark_flag);
		}
		else if(strcmp(com,"score")==0 &&(index==-45||(index>-1&& player[index].access>=4)))
		{
			if(benchmark_flag)
			{
				if(index==-45)
					newLine("Server state running at %d iterations every 5 seconds.",benchmark_iterations);
				else
					sendChatMsg(itod(index),"^wServer state running at %d iterations every 5 seconds.",benchmark_iterations);
			}
		}
		else
		{
			if(index!=-45)
			{
				if(strcmp(com,"use")==0 &&index>-1&& player[index].access>0)
				{
					double dex_factor = (1.0 - ((float)player[index].dex/100.0));

					if(dex_factor < 0.1)
					{
						dex_factor = 0.1;
					}

					if(!ml_items.item[player[index].inventory[atoi(pm1)]].cooldown.tick((int)(ml_items.item[player[index].inventory[atoi(pm1)]].total_cooldown * dex_factor)) || !(atoi(pm1) < MAX_INV))
					{
						return 0;
					}
				}
				strcpy(last_command,str+1);
				mlscript.run(1007,index);
			}
			else
				newLine("Command not available");
			return 0;
		}
	}
	return 1;
}
