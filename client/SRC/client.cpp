//MAIN.CPP - ONLINE RPG CLIENT - JAMES HAMER 2003

#include "mlheader.h"

//for server
void netServer::onConnect(unsigned long cid,char *ip_address){}
void netServer::onDisconnect(unsigned long cid){}
void netServer::onReceive(unsigned char *data,int size,unsigned long cid){}

//for client
void netClient::onReceive(unsigned char *data,int size)
{
	::onReceive(data,size,data[0]);
}

void doFrame()
{
	if(keyDown[SDLK_LCTRL] && keyPress[SDLK_q])
	{
			if(connected)
			{
				MAKE_MSG(quit_msg,msg,QUIT_MSG);
				nc.send((unsigned char *)&msg,sizeof(quit_msg),SEND_GUARANTEED);
			}
			else
				done=1;
	}
	if ((keyDown[SDLK_LALT] || keyDown[SDLK_RALT]) && keyPress[SDLK_RETURN])
	{
		fullscreen = !fullscreen;
		Renderer::SetFullscreen(fullscreen);
		// The next block of code is stupid nonsense crap because it is already setup.
		// There is no reason to reload EVERYTHING just because we are going to fullscreen.
		/*initializeSystem();
		Renderer::Clear();
		Renderer::LoadIdentity();
		//load images and sounds
		char pnum[32];
		int i;
		soundMax=-1;
		bodyMax=-1;
		hairMax=-1;
		clothesMax=-1;
		monsterMax=-1;
		for(i=0;i<255;i++)
		{
			if(soundMax==-1)
			{
				sprintf(pnum,"data/sounds/%d.wav",i);
				if(!sounds.Load(i,pnum))
					soundMax=i;
			}
			if(bodyMax==-1)
			{
				sprintf(pnum,"data/body/%d.png",i);
				if(!pBody[i].Load(pnum))
					bodyMax=i;
			}
			if(hairMax==-1)
			{
				sprintf(pnum,"data/hair/%d.png",i);
				if(!pHair[i].Load(pnum))
					hairMax=i;
			}
			if(clothesMax==-1)
			{
				sprintf(pnum,"data/clothes/%d.png",i);
				if(!pClothes[i].Load(pnum))
					clothesMax=i;
			}
			if(monsterMax==-1 && i>0)
			{
				sprintf(pnum,"data/monsters/%d.png",i);
				if(!pMonster[i].Load(pnum))
					monsterMax=i;
			}
		}
		tiledata.Load("data/misc/tiledata.png");
		effdata.Load("data/misc/effects.png");
		itemdata.Load("data/misc/items.png");
		loading.Load("data/misc/loading.png");
		skin.Load("data/misc/skin0.png");
	
		//load fonts
		font.Load("data/misc/font.png");
		TEXTDRAWER.Initialize(font.img);
		TEXTDRAWER.setColor(0,0,0,1);
		//create effects,terminal,dialog boxes
		eff.create(MAX_EFFECTS);
		bar.create(MAX_HPBAR);
		term.create(255,11);
	
	//	setupDialogs();
		loadEffectsMap();
		updateFPS();*/
		
		//render images	 
		doGameGraphics();
	}
	if(keyPress[SDLK_F5])//change skins
	{
		guiskin++;
		char name[256];
		sprintf(name,"data/misc/skin%d.png",guiskin);
		FILE *f=fopen(name,"r");
		if(f==NULL)
		{
			guiskin=0;
			sprintf(name,"data/misc/skin%d.png",guiskin);
			skin.Load(name);
		}
		else
		{
			fclose(f);
			f=0;
			skin.Load(name);
		}
	}
	if(keyPress[SDLK_ESCAPE])
	{
		target=-1;
		mtarget_id=-1;
		MAKE_MSG(trgt_msg,tr,TRGT_MSG);
		tr.index=mtarget_id;
		nc.send((unsigned char *)&tr,sizeof(trgt_msg),SEND_GUARANTEED);
		ptarget_id=-1;
		chatting=0;
		strcpy(inputStr,"");
		curPos=0;
	}
	if(connected && dialog==-1 && keyPress[SDLK_RETURN] && !keyDown[SDLK_LALT] && !keyDown[SDLK_RALT])
	{
		if(chatting)
		{
			if(strlen(inputStr)==0)
				chatting=0;
		}
		else
			chatting=1;
	}
	if(connected && me > -1 && MYGUY.access > 5)
	{
		if(keyPress[SDLK_F1])
		{
			target=-1;
			if(mode==1) mode=0;
			else mode=1;
		}
		if(keyPress[SDLK_F11]) //debug
		{
			
			if(debug==1) debug=0;
			else debug=1;
		}
	}
	if(me > -1 && !chatting && dialog==-1 && MYGUY.hp>0 && (strcmp(world[MYGUY.p.map].name,"_EMPTY_")!=0 || mode==1))
		doGameInput();
	else if((ptarget_id!=-1&&MYGUY.front()==player[ptarget_id].p)&& attackTimer.tick(50))
		attack();
	if(dialog==-1 && chatting && stringInput(240))
	{
		if(parse(inputStr))
		{
			if(me > -1)
			{
				//sprintf(temp,"%s:%s",MYGUY.name,inputStr);
				//term.newLine("Here is a very long sentence i am using to test with will you please split it up correctly at the spaces so it will wrap around, thank you very much sir...");
				//term.newLine(inputStr);
				//balloon.add(inputStr,me);
				MAKE_MSG(chat_msg,reply,CHAT_MSG);
				reply.size=strlen(inputStr)+1;//+1 for null
				char buf[256];
				memcpy(&buf,(void *)&reply,sizeof(chat_msg));//store header
				memcpy(buf+sizeof(chat_msg),(void *)&inputStr,reply.size);//store string
				nc.send((unsigned char *)&buf,sizeof(chat_msg)+reply.size,SEND_GUARANTEED);
				chatting=0;
			}
		}
		else if(me > -1)
		{
			chatting=0;
		}
		resetStringInput();
	}
	updateFPS();
	//render images
	Renderer::Clear();
	Renderer::LoadIdentity();
	doGameGraphics();

	/*TEXTDRAWER.setColor(1,1,1,1);//draw bottleneck stats
	for(int i=0;i<4;i++)
		TEXTDRAWER.PrintText(10,50+i*20,"%d) %d",i,bottle.times[i]);
	TEXTDRAWER.defaultColor();*/
	
	if(mode==1)
	{
		doMapDialog();
		int r=mapDialog.modified();
		if(r>-1)
			mapEvent(r);
	}
	//if(keyDown[SDLK_HOME])
	//	term.renderAll(0,200);
	//else
	term.render(0,480,246-chat_scroll,9);
	if(dialog!=-1)
	{
		vDialog[dialog].draw();
		if(dialog==4)//draw sprites
		{
			if(animTimer.tick(400))
				animSel=abs(animSel-1);
			TEXTDRAWER.PrintTextf(vDialog[4].x+160,vDialog[4].y+162,"%d",bodySel);
			TEXTDRAWER.PrintTextf(vDialog[4].x+160,vDialog[4].y+162+35,"%d",clothesSel);
			TEXTDRAWER.PrintTextf(vDialog[4].x+160,vDialog[4].y+162+70,"%d",hairSel);
			drawChar(vDialog[4].x+10,vDialog[4].y+10,-1,bodySel,clothesSel,hairSel,0,animSel,4);
			drawChar(vDialog[4].x+90,vDialog[4].y+10,-1,bodySel,clothesSel,hairSel,1,animSel,4);
			drawChar(vDialog[4].x+170,vDialog[4].y+10,-1,bodySel,clothesSel,hairSel,2,animSel,4);
			drawChar(vDialog[4].x+250,vDialog[4].y+10,-1,bodySel,clothesSel,hairSel,3,animSel,4);
		}
		else if(dialog==6)
		{
			if(animTimer.tick(400))
				animSel=abs(animSel-1);
			for(int i=0;i<4;i++)if(slot[i].lvl>0)
			{
				TEXTDRAWER.PrintTextf(vDialog[6].x+16+128*i,vDialog[6].y+162,"%s",slot[i].name);
				TEXTDRAWER.PrintTextf(vDialog[6].x+16+128*i,vDialog[6].y+162+16,"Level %d",slot[i].lvl);
				drawChar(vDialog[6].x+10+128*i,vDialog[6].y+10,slot[i].sprite,slot[i].body,slot[i].clothes,slot[i].hair,0,animSel,4);
				TEXTDRAWER.PrintTextf(vDialog[6].x+28+128*i,vDialog[6].y+196,"Use");
			}
			else TEXTDRAWER.PrintTextf(vDialog[6].x+28+128*i,vDialog[6].y+196,"New");
		}
		int r=vDialog[dialog].modified();
		if(r!=-1)
			dialogEvent(r);
	}
	else
	{
		if(me>-1 && strcmp(world[MYGUY.p.map].name,"_EMPTY_")==0)
		{
			loading.blitFast(150,150,float(mX)/640.0f,float(mY)/480.0f);
		}
		if(chatting)
		{
			char temp[256];
			int x=0,len;
			sprintf(temp,"Send:%s_",inputStr);
			len=pWidth(temp);
			if(len>636)
				x=636-len;
			TEXTDRAWER.setColor(1,1,1,1);
			TEXTDRAWER.PrintText(x,585,temp);
			TEXTDRAWER.defaultColor();
		}
	}
	//cursor
	skin.blit(mX,mY,64,0,32,32,1,1);
	SDL_GL_SwapBuffers();
}
void callback()
{
	term.newLine("done");
}

#ifndef _WIN32
void Sleep(unsigned int MS)
{
	usleep(MS * 1000);
}
#endif

int main(int argc, char **argv)
{
	//parse command line
	strcpy(autoip,"");
	for(int j=0;j<argc;j++)
	{
		if(strcmp(argv[j],"-full")==0)
			fullscreen=1;
		else if(strstr(argv[j],"-join")!=0)
			sscanf(argv[j],"-join:%s",&autoip);
		else if(strstr(argv[j],"-port")!=0)
			sscanf(argv[j],"-port:%d",&SERVER_PORT);
	}
	//strcpy(autoip,"127.0.0.1");//testing
	
	//init graphics
	initializeSystem();
	
	//setup
	setupClient();
	
	//startup
	term.newLine("^cMystera Legends Beta %.3f ^b- ^OZircon Release",client_version);
	//only for testing
	//initTestingMode();

	//checking for newer version or showing servers
	//if(!checkVer())showServers();
	//get available servers
	//initialize socket library
	if(!debug)
	{
		if(strlen(autoip)>2)
		{
			/*dialog=-1;
			//char show[128];
			cstate=1;
			 //sprintf(show,"--- Attempting to connect to %s",autoip);
			 //term.newLine(show);
			 //term.render(0,480,246);
			 //SDL_GL_SwapBuffers();
			if(!nc.connect(autoip,SERVER_PORT))
				term.newLine("--- Error connecting. CTRL-Q to quit.");
			else
			{
				term.newLine("--- Connected to %s.",autoip);
				connected=1;
			}*/
			sips.size(1);
			strcpy(sips[0].ip,autoip);
			sprintf(sips[0].name,"^W%s",autoip);
			strcpy(sips[0].players," ");
			vDialog[0].w[2].addList(sips[0].name);
			dialog=0;
		}
		else
			showServers();
	}

	unsigned long loopnum   = 0;
	unsigned long lastsec   = 0;
	unsigned long loopdif   = 0;
	unsigned long second    = time(0);
	unsigned long sleeptime = 0;
	const long FPS = 50;

	//buildMapLayers();
	//application loop
	while(!done) 
	{
		
		updateKeyboard();
		doFrame();
		
		if(time(0) == second + 1)
		{
			loopdif = loopnum - lastsec;
			lastsec = loopnum;
			sleeptime = float(1000/FPS);
			sleeptime -= loopdif/1000;
			second++;
		}

		loopnum++;
		Sleep(sleeptime);

		if(connected)
		{
			//term.newLine("I really am connected you know.");
			if(udpTimer.tick(1500))
			{
				//send udp packet
				char u=NULL_MSG;
				nc.send((unsigned char *)&u,1,SEND_NON_GUARANTEED);
			}

			int res = nc.update();
			if(res==-1 || servTimer.tick(1000000))
			{
				me=-1;
				player.size(0);player.size(10);
				world.size(0);world.size(10);
				item.size(0);
				term.newLine("--- Connection closed.");
				connected=0;
				servTimer.reset();
				dialog=0;
				
				SDL_WM_SetCaption("Mystera Legends Beta", "ML");
				nc.shutdown();
			}
		}
	}
	//shutdown
	fclose(chatLog);
	
	nc.shutdown();
	Mix_CloseAudio();

	SDL_Quit();
	
	//if(restart)
	//	doRestart();

	return 0;
}
/*

-check CTRL-Q stuff
check use bug
check packet halting
check player password changing or deleting


*/

