
int parse(char *str)
{
	if(str==NULL)
		return 0;
	if(str[0]=='/')
	{
		char com[16],pm1[64],pm2[64],pm3[64],pm4[64];
		sscanf(str,"/%s %s %s %s %s",&com,&pm1,&pm2,&pm3,&pm4);
		if(strcmp(com,"quit")==0)
		{
			MAKE_MSG(quit_msg,msg,QUIT_MSG);
			nc.send((unsigned char *)&msg,sizeof(quit_msg),SEND_GUARANTEED);
			return 0;
		}
		else if(strcmp(com,"logout")==0)
		{
			//dplayshutdown();
			//dplayinit();
			//dialog=0;
		}
		else if(strcmp(com,"music")==0)
		{
			if(music)
			{
				music=0;
				Mix_HaltMusic();
				curMidi=-1;
			}
			else
			{
				music=1;
				playMidi(world[MYGUY.p.map].npc[4].index);
			}
			return 0;
		}
		else if(strcmp(com,"sound")==0)
		{
			sound=abs(sound-1);
			return 0;
		}
		else if(me == -1)
		{
			term.newLine("--- Unknown command or not authorized, try /help");
			return 0;
		}
		else if(strcmp(com,"where")==0 && MYGUY.access>2)
		{
			char temp[64];
			sprintf(temp,"You are on map %d at %d %d.",MYGUY.p.map,MYGUY.p.x,MYGUY.p.y);
			term.newLine(temp);
			return 0;
		}
		else if(strcmp(com,"t")==0)
		{
			char temp[256];
			sscanf(str,"/t %s %[^\n]",&last_tell,&temp);
			sendCmndMsg(str);
			return 0;
		}
		else if(strcmp(com,"train")==0)
		{
			dialog=2;
			sprintf(vDialog[2].w[0].label,"Points Left:%d",MYGUY.train);
			sprintf(vDialog[2].w[1].label,"STR %d",MYGUY.str);
			sprintf(vDialog[2].w[2].label,"DEX %d",MYGUY.dex);
			sprintf(vDialog[2].w[3].label,"CON %d",MYGUY.con);
			sprintf(vDialog[2].w[4].label,"INT %d",MYGUY.itl);
			sprintf(vDialog[2].w[5].label,"WIS %d",MYGUY.wis);
			return 0;
		}
		else if(strcmp(com,"music_box")==0)
		{
			char musicText[4];
			char soundText[4];
			dialog=7;

			if(music == 0)
				strcpy(musicText,"Off");
			else
				strcpy(musicText,"On");

			if(sound == 0)
				strcpy(soundText,"Off");
			else
				strcpy(soundText,"On");

			sprintf(vDialog[7].w[0].label,"Music Power: %s",musicText);
			sprintf(vDialog[7].w[4].label,"Sound Power: %s",soundText);
			return 0;
		}
		else if(strcmp(com,"trade")==0)
		{
			getTradeValues();
			return 0;
		}
		else if(strcmp(com,"stats")==0)
		{
			getCharWin();
			return 0;
		}
		else if(strcmp(com,"rstats")==0)
		{
			getRCharWin();
			return 0;
		}
		else if(strcmp(com,"map_north")==0 && MYGUY.access>5)
		{
			world[MYGUY.p.map].n=atoi(pm1);
			sprintf(mapDialog.w[4].label,"N:%d",world[MYGUY.p.map].n);
			return 0;
		}
		else if(strcmp(com,"map_south")==0 && MYGUY.access>5)
		{
			world[MYGUY.p.map].s=atoi(pm1);
			sprintf(mapDialog.w[5].label,"S:%d",world[MYGUY.p.map].s);
			return 0;
		}
		else if(strcmp(com,"map_west")==0 && MYGUY.access>5)
		{
			world[MYGUY.p.map].w=atoi(pm1);
			sprintf(mapDialog.w[6].label,"W:%d",world[MYGUY.p.map].w);
			return 0;
		}
		else if(strcmp(com,"map_east")==0 && MYGUY.access>5)
		{
			world[MYGUY.p.map].e=atoi(pm1);
			sprintf(mapDialog.w[7].label,"E:%d",world[MYGUY.p.map].e);
			return 0;
		}
		else if(strcmp(com,"map_npc1")==0 && MYGUY.access>5)
		{
			world[MYGUY.p.map].npc[0].index=atoi(pm1);
			sprintf(mapDialog.w[17].label,"N%d",world[MYGUY.p.map].npc[0].index);
			return 0;
		}
		else if(strcmp(com,"map_npc2")==0 && MYGUY.access>5)
		{
			world[MYGUY.p.map].npc[1].index=atoi(pm1);
			sprintf(mapDialog.w[18].label,"N%d",world[MYGUY.p.map].npc[1].index);
			return 0;
		}
		else if(strcmp(com,"map_npc3")==0 && MYGUY.access>5)
		{
			world[MYGUY.p.map].npc[2].index=atoi(pm1);
			sprintf(mapDialog.w[19].label,"N%d",world[MYGUY.p.map].npc[2].index);
			return 0;
		}
		else if(strcmp(com,"map_npc4")==0 && MYGUY.access>5)
		{
			world[MYGUY.p.map].npc[3].index=atoi(pm1);
			sprintf(mapDialog.w[20].label,"N%d",world[MYGUY.p.map].npc[3].index);
			return 0;
		}
		else if(strcmp(com,"map_qty1")==0 && MYGUY.access>5)
		{
			world[MYGUY.p.map].npc[0].qty=atoi(pm1);
			sprintf(mapDialog.w[21].label,"Q%d",world[MYGUY.p.map].npc[0].qty);
			return 0;
		}
		else if(strcmp(com,"map_qty2")==0 && MYGUY.access>5)
		{
			world[MYGUY.p.map].npc[1].qty=atoi(pm1);
			sprintf(mapDialog.w[22].label,"Q%d",world[MYGUY.p.map].npc[1].qty);
			return 0;
		}
		else if(strcmp(com,"map_qty3")==0 && MYGUY.access>5)
		{
			world[MYGUY.p.map].npc[2].qty=atoi(pm1);
			sprintf(mapDialog.w[23].label,"Q%d",world[MYGUY.p.map].npc[2].qty);
			return 0;
		}
		else if(strcmp(com,"map_qty4")==0 && MYGUY.access>5)
		{
			world[MYGUY.p.map].npc[3].qty=atoi(pm1);
			sprintf(mapDialog.w[24].label,"Q%d",world[MYGUY.p.map].npc[3].qty);
			return 0;
		}
		else if(strcmp(com,"map_music")==0 && MYGUY.access>5)
		{
			world[MYGUY.p.map].npc[4].index=atoi(pm1);
			sprintf(mapDialog.w[25].label,"Music:%d",world[MYGUY.p.map].npc[4].index);
			return 0;
		}
		else if(strcmp(com,"map_light")==0 && MYGUY.access>5)
		{
			world[MYGUY.p.map].npc[4].qty=atoi(pm1);
			sprintf(mapDialog.w[26].label,"Light:%d",world[MYGUY.p.map].npc[4].qty);
			return 0;
		}
		else if(strcmp(com,"map_title")==0 && MYGUY.access>5)
		{
			sscanf(str,"/%s %[^\n]",com,world[MYGUY.p.map].name);
			return 0;
		}
		else if(strcmp(com,"map_warp")==0 && MYGUY.access>5)
		{
			warp.map=atoi(pm1);
			warp.x=atoi(pm2);
			warp.y=atoi(pm3);
			curTile = -98;
			return 0;
		}
		else if(strcmp(com,"map_script")==0 && MYGUY.access>5)
		{
			map_script=atoi(pm1);
			curTile = -96;
			return 0;
		}
		else if(strcmp(com,"map_switch")==0 && MYGUY.access>5)
		{
			map_script=atoi(pm1);
			curTile = -95;
			return 0;
		}
		else if(strcmp(com,"view")==0 && MYGUY.access>7)
		{
			char temp[64];
			char temp2[64];
			sprintf(temp,"%d.txt",atoi(pm1));
			FILE *thefile = fopen(temp,"rb");
			if(thefile==NULL)
				term.newLine("You have no such script! Try downloading it first.");
			else
			{
				fclose(thefile);
				sprintf(temp2,"notepad %s",temp);
				#ifdef WIN32
				WinExec(temp2,SW_MAXIMIZE);
				#endif
			}
			return 0;
		}
		else if(strcmp(com,"start")==0 && MYGUY.access>7)
		{
			char temp[64];
			char temp2[64];
			sprintf(temp,"%d.txt",atoi(pm1));
			FILE *thefile = fopen(temp,"w");
			fputs("//game script\nvoid main()\n{\n}",thefile);
			fclose(thefile);
			sprintf(temp2,"notepad %s",temp);
			#ifdef WIN32
			WinExec(temp2,SW_MAXIMIZE);
			#endif
			return 0;
		}
		else if(strcmp(com,"upload")==0 && MYGUY.access>7)
		{
			MAKE_MSG(file_msg,scr,FILE_MSG);
			strcpy(scr.name,pm1);
			char filename[256];
			sprintf(filename, "scripts\\%s",scr.name);
			FILE *thefile = fopen(filename,"rb");
			if(thefile==NULL)
				term.newLine("Error opening file, please specify full filename");
			else
			{
				fseek(thefile,0,SEEK_END);
				scr.size = ftell(thefile);
				rewind(thefile);
				unsigned char tbuf[100000];
				unsigned char cbuf[100000];//compressed
				fread(&tbuf,scr.size,1,thefile);
				unsigned long len=100000;
				compress2(cbuf+sizeof(file_msg), &len,(unsigned char *)&tbuf, (unsigned long)scr.size,9);
				scr.size=len;
				memcpy(cbuf,(void *)&scr,sizeof(file_msg));
				nc.send((unsigned char *)&cbuf,sizeof(file_msg) + scr.size,SEND_GUARANTEED);
				fclose(thefile);
				term.newLine("File uploaded.");
			}
			return 0;
		}
		else
		{
			sendCmndMsg(str);
			return 0;
		}
	}
	return 1;
}



