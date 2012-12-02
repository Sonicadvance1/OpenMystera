//int totaldata=0;
char message[256];
void onReceive(unsigned char *data,unsigned long dataSize,unsigned char type)
{
	UNUSED(dataSize);
	//char temp[64];
	//totaldata+=dataSize;
	//sprintf(temp,"type:%d size:%d totalsize:%d",type,dataSize,totaldata);
	//term.newLine(temp);

	//int index = dtoi(dpnid);
	
	//char temp[32];
	//sprintf(temp,"type:%d size:%d",type,dataSize);
	//term.newLine(temp);
	
	/*if(type==ID_DISCONNECTION_NOTIFICATION || type==ID_CONNECTION_LOST)
	{
		if(me>-1)
		{
			MYGUY.access=-1;
			me=-1;
		}
		term.newLine("--- Connection closed.");
		connected=0;
		servTimer.reset();
		dialog=0;
		
		SDL_WM_SetCaption("Mystera Legends Beta", "ML");
		nc.shutdown();
	}*/

	if(type==NULL_MSG)
	{
		servTimer.reset();
		return;
	}
	else if(type==CHAT_MSG)//chat message
	{
		chat_msg msg;
		char theChat[256];
		memcpy((unsigned char *)&msg,data,sizeof(chat_msg));
		memcpy(&theChat,data+sizeof(chat_msg),msg.size);
		
		term.newLine(theChat);
		fprintf(chatLog,"%s\n",theChat);
		if(chat_scroll>0)chat_scroll++;


		//do chat balloon
		char chatb[256];
		char name[256];
		int id=-1;
		unsigned int i=0;
		while(i<strlen(theChat) && i<20)//seperate name and chat
		{
			if(theChat[i]==':')
			{
				strcpy(chatb,theChat+i+1);
				name[i]='\0';
				break;
			}
			name[i]=theChat[i];
			i++;
		}
		if(strlen(name)>= 3 && (name[1]=='W' || name[0]!='^'))//find speaker
		{
			for(i=0;i<(unsigned int)player.size();i++)
				if(player[i].access>0 && player[i].p.map==MYGUY.p.map)
				{  				
					if(strcmp(name,player[i].name+2)==0)
						id=i;
				}
			//sprintf(chatb,"%d",id);
			//term.newLine(chatb);
			if(id>-1)
				balloon.add(chatb,id);
		}
	}
	else if(type==TWIN_MSG)//Trade Window
	{
		CAST_MSG(twin_msg,msg);

		char message[256];
		if(msg->item[0].state != 3)
		{
			strcpy(message,"^RTarget a merchant first!");
			term.newLine(message);
		}
		else
		{
			for(int c=0;c<20;c++)
			{
				tradeWin[c].qty = msg->item[c].qty;
				strcpy(tradeWin[c].name,msg->item[c].name);
				tradeWin[c].item_template = msg->item[c].item_template;
				tradeWin[c].graphic = msg->item[c].graphic;
				tradeWin[c].merchID = msg->item[c].merchID;
				tradeWin[c].npcType = msg->item[c].state;
			}
			int wCount = 11, iCount = 21;
			char nameCheck[32];
			char tradeString[64];
			char costString[64];
			for(int winClear = 0;winClear<10;winClear++)
			{
				strcpy(vDialog[8].w[wCount].label,"");
				vDialog[8].w[iCount].setGraphic(-1);
				wCount++;
				iCount++;
			}
			wCount = 11;
			iCount = 21;
			for(int winFill=0;winFill<20;winFill++)
			{
				if(winFill != 0)
					winFill++;
				if(tradeWin[winFill].qty == -1)
					tradeWin[winFill].qty = 1;
				if(tradeWin[winFill+1].qty == -1)
					tradeWin[winFill+1].qty = 1;
				strcpy(nameCheck,tradeWin[winFill+1].name);
				if(strlen(tradeWin[winFill+1].name)>0 && nameCheck[0] == '^')
				{
					sprintf(tradeString,"%ld %s",tradeWin[winFill].qty,tradeWin[winFill].name);
					sprintf(costString,"%ld %s",tradeWin[winFill+1].qty,tradeWin[winFill+1].name);
					sprintf(vDialog[8].w[wCount].label,"%ld %s^N for %ld %s^N.",tradeWin[winFill].qty,tradeWin[winFill].name,tradeWin[winFill+1].qty,tradeWin[winFill+1].name);
					if(tradeWin[winFill].graphic != -1)
					{
						vDialog[8].w[iCount].setGraphic(tradeWin[winFill].graphic);
					}
					wCount++;
					iCount++;
				}
			}
			dialog=8;
		}
		return;
	}
	else if(type==CWIN_MSG)
	{
		CAST_MSG(cwin_msg,msg);

		if(strcmp(msg->privProfile,"No")==0 || MYGUY.access > 6 || msg->id == -1)
		{
			if(strcmp(msg->privProfile,"No") != 0 && msg->id != -1 && MYGUY.access > 6)
			{
				char message[40];
				strcpy(message,"^YADMIN:Private flag override.");
				term.newLine(message);
			}
			strcpy(vDialog[9].w[3].label,msg->name);
			strcpy(vDialog[9].w[4].label,itos(msg->level));
			strcpy(vDialog[9].w[12].label,itos(msg->str));
			strcpy(vDialog[9].w[13].label,itos(msg->dex));
			strcpy(vDialog[9].w[14].label,itos(msg->con));
			strcpy(vDialog[9].w[15].label,itos(msg->itl));
			strcpy(vDialog[9].w[16].label,itos(msg->wis));
			strcpy(vDialog[9].w[25].label,itos(msg->fire));
			strcpy(vDialog[9].w[26].label,itos(msg->ice));
			strcpy(vDialog[9].w[27].label,itos(msg->elec));
			strcpy(vDialog[9].w[28].label,itos(msg->physical));
			strcpy(vDialog[9].w[29].label,itos(msg->poison));
			strcpy(vDialog[9].w[30].label,itos(msg->magic));
			sprintf(vDialog[9].w[35].label,"%lu",msg->exp);
			if(msg->level != 255)
				sprintf(vDialog[9].w[36].label,"%lu",msg->tnl);
			else
				strcpy(vDialog[9].w[36].label,"N/A");
			if(msg->seren > 0)
				strcpy(vDialog[9].w[39].label,"Disabled");
			else
				strcpy(vDialog[9].w[39].label,"Enabled");
			strcpy(vDialog[9].w[42].label,itos(msg->PKs));
			strcpy(vDialog[9].w[43].label,itos(msg->honor));
			strcpy(vDialog[9].w[45].label,itos(msg->kills));
			strcpy(vDialog[9].w[47].label,itos(msg->deaths));
			sprintf(vDialog[9].w[50].label,":%s",itos(msg->atk));
			sprintf(vDialog[9].w[52].label,":%s",itos(msg->def));
			vDialog[9].w[48].setAppr(msg->sprite,msg->body,msg->clothes,msg->hair);
			vDialog[9].w[49].setGraphic(81);
			vDialog[9].w[51].setGraphic(186);
			vDialog[9].w[49].setScale(0.500f);
			vDialog[9].w[51].setScale(0.500f);
			dialog=9;
		}
		else
		{
			char message[40];
			strcpy(message,"^RPlayer info marked as private.");
			term.newLine(message);
		}

	}
	else if(type==NWIN_MSG)
	{
		CAST_MSG(nwin_msg,msg);

		strcpy(vDialog[10].w[2].label,msg->name);
		sprintf(vDialog[10].w[4].label,"%s/%s",itos(msg->hp),itos(msg->mhp));
		strcpy(vDialog[10].w[11].label,itos(msg->atk));
		strcpy(vDialog[10].w[12].label,itos(msg->def));
		if(msg->state == ATTACK)
			strcpy(vDialog[10].w[13].label,"Yes");
		else if(msg->state == MERCHANT)
		{
			if(msg->target != -1)
				strcpy(vDialog[10].w[13].label,"Yes");
			else
				strcpy(vDialog[10].w[13].label,"No");
		}
		else
			strcpy(vDialog[10].w[13].label,"No");
		strcpy(vDialog[10].w[14].label,itos(msg->exp));
		strcpy(vDialog[10].w[23].label,itos(msg->fire));
		strcpy(vDialog[10].w[24].label,itos(msg->ice));
		strcpy(vDialog[10].w[25].label,itos(msg->elec));
		strcpy(vDialog[10].w[26].label,itos(msg->physical));
		strcpy(vDialog[10].w[27].label,itos(msg->poison));
		strcpy(vDialog[10].w[28].label,itos(msg->magic));
		vDialog[10].w[29].setAppr(msg->sprite,msg->body,msg->clothes,msg->hair);
		dialog=10;

	}
	else if(type==HITP_MSG)//new hp message
	{
		CAST_MSG(hitp_msg,msg);
		
		MYGUY.hp = msg->hp;
		
	}
	else if(type==MANP_MSG)//new mp message
	{
		CAST_MSG(manp_msg,msg);
		
		MYGUY.mp = msg->mp;
		
	}
	else if(type==PARM_MSG)//
	{
		CAST_MSG(parm_msg,msg);
		if(msg->flag > 20 && msg->flag < 40)
		{
			MAKE_MSG(parm_msg,hello,PARM_MSG);
			hello.flag = msg->flag;
			nc.send((unsigned char *)&hello,sizeof(parm_msg),SEND_GUARANTEED);
		}
	}
	else if(type==EXPR_MSG)//experience message
	{
		CAST_MSG(expr_msg,msg);
		
		MYGUY.exp = msg->exp;
		
	}
	else if(type==LEVL_MSG)//leveling message
	{
		CAST_MSG(levl_msg,msg);
		
		MYGUY.exp = msg->exp;
		MYGUY.lvl = msg->lvl;
		MYGUY.hp  = msg->hp;
		MYGUY.mhp = msg->mhp;
		MYGUY.mp  = msg->mp;
		MYGUY.mmp = msg->mmp;
		mexp = nextExp(MYGUY.lvl);
		
	}
	else if(type==EFCT_MSG)//effect message
	{
		efpk_msg pack;
		efct_msg msg;
		cEffect temp;
		memcpy((unsigned char *)&pack,data,sizeof(efpk_msg));
		for(int i=0;i<pack.qty;i++)
		{
			memcpy(&msg,data+sizeof(efpk_msg)+(i*sizeof(efct_msg)),sizeof(efct_msg));
			temp.p.map = MYGUY.p.map;
			temp.p.x=msg.x;
			temp.p.y=msg.y;
			temp.index=msg.index;
			if(temp.index < fxMap.size())
			{
				sounds.play(fxMap[temp.index][rand()%fxMap[temp.index].size()]);
			}
			eff.place(temp);
		}
	}
	else if(type==EQUI_MSG)//equip message
	{
		CAST_MSG(equi_msg,msg);
		
		MYGUY.eLeft=msg->eLeft;
		MYGUY.eRight=msg->eRight;
		MYGUY.eBody=msg->eBody;
		MYGUY.eHead=msg->eHead;
		MYGUY.eSpecial=msg->eSpecial;
		
	}
	else if(type==ACSS_MSG)//access message
	{
		CAST_MSG(acss_msg,msg);	
		MYGUY.access=msg->access;
		if(MYGUY.access > 5)
			access_check = int(MYGUY.name[0]);
		else
			access_check = 0;
		mode=0;
	}
	else if(type==PLYR_MSG)//set current or other player info
	{
		CAST_MSG(plyr_msg,msg);
		char t1[64];
		char t2[64];
		strcpy(t1,msg->name+2);
		strcpy(t2,login_name);
		strlwr(t1);
		strlwr(t2);
		if(me==-1 && strcmp(t1,t2)==0)
		{
			dialog=-1;
			me=msg->index;
			if(me>=player.size())
				player.size(me+100);
			player[me].sprite=msg->sprite;
			player[me].body=msg->body;
			player[me].hair=msg->hair;
			player[me].clothes=msg->clothes;
			strcpy(player[me].name,msg->name);
			oldmap=player[me].p.map;
			chatting=0;
		}
		else if(me!=-1)
		{
			if(msg->index>=player.size())
				player.size(msg->index+100);
			player[msg->index].sprite=msg->sprite;
			player[msg->index].body=msg->body;
			player[msg->index].hair=msg->hair;
			player[msg->index].clothes=msg->clothes;
			strcpy(player[msg->index].name,msg->name);
		}
	}
	else if(type==ATTR_MSG)
	{
		CAST_MSG(attr_msg,msg);
		
		MYGUY.train=msg->train;
		MYGUY.str=msg->str;
		MYGUY.dex=msg->dex;
		MYGUY.con=msg->con;
		MYGUY.itl=msg->itl;
		MYGUY.wis=msg->wis;    
		sprintf(vDialog[2].w[0].label,"Points Left:%d",MYGUY.train);
		
	}
	else if(type==UPDT_MSG)//receive players states
	{
		updt_msg msg;
		xyps_msg ps;
		int ox,oy,od;
		int qty = 0;;
		memcpy((unsigned char *)&msg,data,sizeof(updt_msg));
		int i;
		if(msg.isLogin == true)
			qty = 0;
		else
			qty = msg.qty;
		for(i=0;i<qty;i++)
		{
			memcpy(&ps,data+sizeof(updt_msg)+(i*sizeof(xyps_msg)),sizeof(xyps_msg)); //Causes MSG 5 Login bug
			world[player[ps.index].p.map].map[player[ps.index].p.row()][player[ps.index].p.col()].space=VACANT;
			ox=player[ps.index].p.x;
			oy=player[ps.index].p.y;
			od=player[ps.index].dir;
			player[ps.index].p.x=ps.x;//msg.y=y+(50*dir) y packed w dir
			player[ps.index].p.y=ps.y%50;
			player[ps.index].dir=ps.y/50;
			
			if(ox!=player[ps.index].p.x||oy!=player[ps.index].p.y)
			{
				player[ps.index].frm++;
				if(player[ps.index].frm>1)
					player[ps.index].frm=0;
				//if theyve moved one space
				if(abs(ox-player[ps.index].p.x)+abs(oy-player[ps.index].p.y)==1)
				{
					
					if(player[ps.index].delay<0)
						player[ps.index].delay = -player[ps.index].delay;

				
					player[ps.index].delay -=int( float(player[ps.index].path*abs(player[ps.index].path)));//average speed
					//player_delay[ps.index] -= player_path[ps.index]*8;//average speed
					player[ps.index].path=32;

					player[ps.index].walk.reset();
					
				}
				else
				{
					//catch up to fast moving player
					
					player[ps.index].delay = -player[ps.index].delay;
					player[ps.index].path=0;
					//player_timer[ps.index].reset();
					
				}
			}
			else
			{
				
				if(od!=player[ps.index].dir)
					player[ps.index].path=0;
				if(player[ps.index].path<=0 && player[ps.index].delay>0)//if path is traveled and not moving
				{
					//stand still
					player[ps.index].delay=-player[ps.index].delay;
					//player_timer[ps.index].reset();
				}
				
			}
			player[ps.index].p.map=MYGUY.p.map;
			world[player[ps.index].p.map].map[player[ps.index].p.row()][player[ps.index].p.col()].space=ps.index;
			player[ps.index].access = -100;
		}
		for(i=0;i<player.size();i++)
			if(player[i].p.map==MYGUY.p.map && i!=me)
			{
				if(player[i].access==-100)
					player[i].access=1;
				else
				{
					if(world[player[i].p.map].map[player[i].p.row()][player[i].p.col()].space==i)
						world[player[i].p.map].map[player[i].p.row()][player[i].p.col()].space=VACANT;
					player[i].p.map++;
				}
			}
		
	}
	else if(type==PLYV_MSG)
	{
		plyv_msg msg;
		char tempbuf[200000];
		char buf[200000];
		pvms_msg pl;
		memcpy((unsigned char *)&msg,data,sizeof(plyv_msg));
		memcpy(&tempbuf,data+sizeof(plyv_msg),msg.size);
		unsigned long newlen = 200000;
		uncompress ((unsigned char *)&buf, &newlen, (unsigned char *)&tempbuf, (unsigned long)msg.size);
		int qty=newlen/sizeof(pvms_msg);
		
		for(int i=0;i<qty;i++)
		{
			memcpy((unsigned char *)&pl,&buf[i*sizeof(pvms_msg)],sizeof(pvms_msg));
			if(pl.index>=player.size())
				player.size(pl.index+100);
			player[pl.index].sprite=pl.sprite;
			player[pl.index].body=pl.body;
			player[pl.index].hair=pl.hair;
			player[pl.index].clothes=pl.clothes;
			strcpy(player[pl.index].name,pl.name);
		}
		
	}
	else if(type==ITMV_MSG)
	{
		itmv_msg msg;
		unsigned char tempbuf[50000];
		unsigned char buf[50000];
		ivms_msg pl;
		memcpy((unsigned char *)&msg,data,sizeof(itmv_msg));
		memcpy(&tempbuf,data+sizeof(itmv_msg),msg.size);
		unsigned long newlen = 50000;
		int res = uncompress((unsigned char *)&buf, &newlen, (unsigned char *)&tempbuf, (unsigned long)msg.size);
		if (!res)
		{
			debugMsg("Couldn't decompress ITMV_MSG\n");
			return;
		}
		int qty = newlen/sizeof(ivms_msg);
		cItemRef theItem;
		theItem.qty=1;
		theItem.p.map=MYGUY.p.map;
		
		for(int i=0;i<qty;i++)
		{
			memcpy((unsigned char *)&pl,&buf[i*sizeof(ivms_msg)],sizeof(ivms_msg));
			theItem.graphic=pl.graphic;
			theItem.p.x=pl.x;
			theItem.p.y=pl.y;
			
			addItem(theItem);
		}
		
	}
	else if(type==MYCR_MSG)//set current player position
	{
		CAST_MSG(mycr_msg,msg);
		debugMsg("MYCR: CUR POS AT DEATH:%d %d %d",MYGUY.p.map,MYGUY.p.x,MYGUY.p.y);
		if(msg->isLogin == false)
			world[player[me].p.map].map[player[me].p.row()][player[me].p.col()].space=VACANT; // Causes MSG 12 Login Bug
		MYGUY.p=msg->p;
		if(MYGUY.p.map>=world.size())
			world.size(MYGUY.p.map+100);
		world[player[me].p.map].map[player[me].p.row()][player[me].p.col()].space=me;
		MYGUY.dir = msg->dir;
		
		debugMsg("POS AFTER WARP:%d %d %d",MYGUY.p.map,MYGUY.p.x,MYGUY.p.y);
		if(MYGUY.p.map !=oldmap)
		{
			debugMsg("Oldmap before %d",oldmap);
			updateMapDialog();
			SDL_WM_SetCaption(world[MYGUY.p.map].name, "ORCB");
			
			for(int i=0;i<item.size();i++)
				item[i].qty=0;
			oldmap=MYGUY.p.map;;
			
			debugMsg("Oldmap now %d",oldmap);
			MAKE_MSG(parm_msg,temp,PARM_MSG);
			temp.parm=0;
			temp.flag=world[MYGUY.p.map].version;
			nc.send((unsigned char *)&temp,sizeof(parm_msg),SEND_GUARANTEED);
			debugMsg("version sent %d",world[MYGUY.p.map].version);
			buildMapLayers();
			if(curMidi!=world[MYGUY.p.map].npc[4].index)
				playMidi(world[MYGUY.p.map].npc[4].index);
		}	
	}
	else if(type==UPLD_MSG)//set current map
	{
		upld_msg msg;
		char buf[5000];
		memcpy((unsigned char *)&msg,data,sizeof(upld_msg));
		memcpy(&buf,data+sizeof(upld_msg),msg.size);
		unsigned long newlen = sizeof(cMap);
		
		if(MYGUY.p.map>=world.size())
			world.size(MYGUY.p.map+100);
		uncompress ((unsigned char *)&world[MYGUY.p.map], &newlen, (unsigned char *)&buf, (unsigned long)newlen);
		world[MYGUY.p.map].setAllVacant();
		
		updateMapDialog();
		buildMapLayers();
		if(curMidi!=world[MYGUY.p.map].npc[4].index)
			playMidi(world[MYGUY.p.map].npc[4].index);
		SDL_WM_SetCaption(world[MYGUY.p.map].name, "ORCB");
		debugMsg("UPLD MSG- map received(MYGUY at %d %d %d)",MYGUY.p.map,MYGUY.p.x,MYGUY.p.y);
	}
	else if(type==ITEM_MSG)//add new item on ground
	{
		CAST_MSG(item_msg,msg);
		cItemRef theItem;
		theItem.graphic=msg->graphic;
		theItem.p.x=msg->x;
		theItem.p.y=msg->y;
		theItem.qty=1;
		
		addItem(theItem);
		
	}
	else if(type==ITMR_MSG)//remove item on ground
	{
		CAST_MSG(itmr_msg,msg);
		int i=item.size()-1;
		while(i>=0)
		{
			if(item[i].qty!=0&&item[i].p.x==msg->x&&item[i].p.y==msg->y)
			{
				item[i].qty=0;
				break;
			}
			i--;
		}
	}
	else if(type==INVT_MSG)//add item to inventory
	{
		CAST_MSG(invt_msg,msg);	
		MYGUY.item[msg->index].qty+=msg->qty;
		MYGUY.item[msg->index].graphic=msg->graphic;
		strcpy(MYGUY.item[msg->index].name,msg->name);
		
	}
	else if(type==IQTY_MSG)//inventory item absolute set
	{
		CAST_MSG(iqty_msg,msg);	
		
		MYGUY.item[msg->index].qty=msg->qty;
		
	}
	else if(type==INVR_MSG)//remove item from inventory
	{
		CAST_MSG(invr_msg,msg);
		
		if(msg->qty>0)
			MYGUY.item[msg->index].qty-=msg->qty;
		else 
			MYGUY.item[msg->index].qty=0;
		
	}
	else if(type==LEFT_MSG)
	{
		CAST_MSG(left_msg,msg);
		if(me==-1)
			return;
		player[msg->index].access=-1;
		world[player[msg->index].p.map].map[player[msg->index].p.row()][player[msg->index].p.col()].space=VACANT;
		char temp[128];
		sprintf(temp,"%s has left the realm.",player[msg->index].name);
		temp[1]='w';
		term.newLine(temp);
		
	}
	else if(type==SNFO_MSG)
	{
		connected=1;
		//term.newLine("--- Connected");
		
		dialog=1;
		MAKE_MSG(vrsn_msg,msg,VRSN_MSG);
		msg.version=client_version;
		nc.send((unsigned char *)&msg,sizeof(vrsn_msg),SEND_GUARANTEED);
		servTimer.reset();
	}
	else if(type==HBAR_MSG)
	{
		CAST_MSG(hbar_msg,msg);
		cHPbar temp;
		
		//if(msg->hp<0)
		//	msg->hp=0;
		temp.init(MYGUY.p.map,msg->index,msg->hp);
		bar.place(temp);

	}
	else if(type==SNDF_MSG)
	{
		CAST_MSG(sndf_msg,msg);
		sounds.play(msg->effect);
	}
	else if(type==SHAD_MSG)
	{
		CAST_MSG(shad_msg,msg);
		map_shade = msg->shade;
	}
	else if(type==SLOT_MSG)
	{
		CAST_MSG(slot_msg,msg);
		for(int i=0;i<4;i++)
		{
			strcpy(slot[i].name,msg->name[i]);
			slot[i].lvl=msg->lvl[i];
			slot[i].sprite=msg->sprite[i];
			slot[i].body=msg->body[i];
			slot[i].hair=msg->hair[i];
			slot[i].clothes=msg->clothes[i];
		}
		dialog=6;
	}
	else if(type==DLOG_MSG)
	{
		CAST_MSG(dlog_msg,msg);
		dialog = msg->dialog;
	}
	else if(type==QUIT_MSG)
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
	else if(type==FILE_MSG)
	{
		file_msg msg;
		memcpy((unsigned char *)&msg,data,sizeof(file_msg));
		char buf[100000];
		char filename[256];
		unsigned long newlen = 100000;
		uncompress ((unsigned char *)&buf, &newlen, data+sizeof(file_msg), (unsigned long)msg.size);
		char temp[128];
		sprintf(temp,"File %s downloaded: %d(%ld) bytes.",msg.name,msg.size,newlen);
		
		term.newLine(temp);
		
		sprintf(filename, "scripts\\%s",msg.name);

		FILE *thefile = fopen(filename,"wb");
		if(thefile != NULL)
		{
			fwrite(&buf,newlen,1,thefile);
			fclose(thefile);
			sprintf(temp,"notepad %s",filename);
			#ifdef WIN32
				WinExec(temp,SW_MAXIMIZE);
			#endif
		}
		else 
			term.newLine("Error creating file");
	}
	else
	{
		char temp[64];
		sprintf(temp,"unknown message:%d",type);
		term.newLine(temp);
	}
}
