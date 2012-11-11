//get input
void doGameInput()
{
	//admin options
	if(MYGUY.access>5)
	{
		if(keyDown[SDLK_MLEFT])
		{
			if(mode==1)//map buttons
			{
			}
		}
		if(keyPress[SDLK_MLEFT])//buttons
		{
			if(mode==1)//map buttons
			{
			}
		}
		if(keyDown[SDLK_MRIGHT])
		{
			if(mode==1)
			{
				if(mX < 640 && mY < 480)//tile grabber
				{
					
					curTile=world[MYGUY.p.map].map[mY/32][mX/32].tile[layer];
					
				}
				if(mX >= 660 && mY >= 20 && mX <= 788 && mY <= 276 && anyTimer.tick(100))//tile scroller
				{
					mscrx+=(mX-(660+64))/2;
					mscry+=(mY-(20+128))/2;
					if(mscrx<0)
						mscrx=0;
					if(mscry<0)
						mscry=0;
					if(mscrx>tiledata.w-128)
						mscrx=tiledata.w-128;
					if(mscry>tiledata.h-256)
						mscry=tiledata.h-256;
				}
			}
		}
		if(keyDown[SDLK_MLEFT])
		{
			if(mode==1)
			{
				if(mX >= 660 && mY >= 20 && mX <= 788 && mY <= 276)//tile select
				{
					
					curTile=((mX-660+mscrx)/32) + (((mY-20+mscry)/32)*(tiledata.w/32));
					
				}
				else if(mX < 640 && mY < 480)//tile draw
				{
					
					if(curTile >= 0)
					{
						world[MYGUY.p.map].map[mY/32][mX/32].tile[layer]=curTile;
					}
					else
					{
						world[MYGUY.p.map].map[mY/32][mX/32].type = curTile+101;
						if(curTile==-98)
							world[MYGUY.p.map].map[mY/32][mX/32].warp=warp;
						else if(curTile==-96 || curTile==-95)
							world[MYGUY.p.map].map[mY/32][mX/32].warp.map=map_script;
					}
					
				}
			}
		}
		if(keyPress['f'])
		{
			if(mode==1)
			{
				
				if(curTile >= 0)
					fillwith(mY/32,mX/32,world[MYGUY.p.map].map[mY/32][mX/32].tile[layer]);
				else
					fillwith(mY/32,mX/32,world[MYGUY.p.map].map[mY/32][mX/32].type);
				
			}
		}
	}
	//everyone options
	/*if(keyPress[SDLK_z])
		sounds.play(4);
	if(keyPress[SDLK_x])
	{
		map_shade+=5;
		if(map_shade>100)
			map_shade=0;
	}
	if(keyPress[SDLK_c])
	{
		cEffect temp;
		temp.p.map = MYGUY.p.map;
		temp.p.x=5;
		temp.p.y=5;
		temp.index=rand()%10;
		sounds.play(fxMap[temp.index][rand()%fxMap[temp.index].size()]);
		
		eff.place(temp);
		
	}*/
	if(keyPress[SDLK_MRIGHT])
	{
		if(mode==0)
		{
			if(mX<640&&mY<480)
			{
				target++;
				if(target>1)
					target=-1;
			}
			if(mX > 645 && mX < 677 && mY > 20 && mY < 468 && MYGUY.item[((mY-20)/32)+inv_slot*14].qty!=0)//item drop
			{
				chatting=0;
				MAKE_MSG(drop_msg,msg,DROP_MSG);
				msg.index=((mY-20)/32)+(inv_slot*14);
				if(MYGUY.item[msg.index].qty>1)
				{
					//init drop dialog on stackable items
					dropSlot=msg.index;
					sprintf(vDialog[5].w[2].label,"%d",MYGUY.item[dropSlot].qty);
					sprintf(inputStr,"%d",MYGUY.item[dropSlot].qty);
					curPos=strlen(inputStr);
					vDialog[5].w[2].state=UX_ACTIVE;
					dialog=5;
				}
				else
					nc.send((unsigned char *)&msg,sizeof(drop_msg),SEND_GUARANTEED);
			}
		}
	}
	if(keyPress[SDLK_MLEFT])
	{
		if(mode==0)
		{
			if(mX<640&&mY<480)
			{
				if(world[MYGUY.p.map].map[(mY+8)/32][mX/32].space!=VACANT)
				{
					if(target==0 && world[MYGUY.p.map].map[(mY+8)/32][mX/32].space!=me)
					{
						ptarget_id=world[MYGUY.p.map].map[(mY+8)/32][mX/32].space;
						target=-1;
					}
					else if(target==1)
					{
						mtarget_id=world[MYGUY.p.map].map[(mY+8)/32][mX/32].space;
						target=-1;
						MAKE_MSG(trgt_msg,tr,TRGT_MSG);
						tr.index=mtarget_id;
						nc.send((unsigned char *)&tr,sizeof(trgt_msg),SEND_GUARANTEED);
					}
				}
				else
				{
					if(target==0)
						ptarget_id=-1;
					else if(target==1)
					{
						mtarget_id=-1;
						MAKE_MSG(trgt_msg,tr,TRGT_MSG);
						tr.index=mtarget_id;
						nc.send((unsigned char *)&tr,sizeof(trgt_msg),SEND_GUARANTEED);
					}
					target=-1;
				}
			}
			if(mX > 650 && mX < 682 && mY > 20 && mY < 468 && useTimer.tick(400) && MYGUY.item[((mY-20)/32)+inv_slot*14].qty!=0)//item equip
			{
				char temp[256];
				sprintf(temp,"/use %d",((mY-20)/32)+inv_slot*14);
				sendCmndMsg(temp);
			}
		}
	}
	if(term.size>9) //scrolling
	{
		if(keyUp[SDLK_MLEFT] && mX>624 && mX<640 && mY>480 && mY<496)
		{
			chat_scroll++;
			if(chat_scroll>term.size-9)
				chat_scroll=term.size-9;
		}
		else if(keyUp[SDLK_MLEFT] && mX>624 && mX<640 && mY>566 && mY<582)
		{
			chat_scroll--;
			if(chat_scroll<0)
				chat_scroll=0;
		}
		else if(keyDown[SDLK_MLEFT] && mX>624 && mX<640 && mY>496 && mY<566)
		{
			chat_scroll=term.size-9-((mY-8-496)*(term.size-9))/(55);
			if(chat_scroll<0)chat_scroll=0;
			if(chat_scroll>term.size-9)
				chat_scroll=term.size-9;
		}
	}
	if(keyPress[SDLK_SPACE])
	{
		if(MYGUY.front().inBounds() && world[MYGUY.p.map].map[MYGUY.front().y][MYGUY.front().x].type==SWCH)
		{
			MAKE_MSG(parm_msg,hello,PARM_MSG);
			hello.flag = 3;
			nc.send((unsigned char *)&hello,sizeof(parm_msg),SEND_GUARANTEED);
		}
	}
	if((keyDown[SDLK_SPACE] || (ptarget_id!=-1&&MYGUY.front()==player[ptarget_id].p))&& attackTimer.tick(550))
		attack();
	if(keyPress['/'])
	{
		if(chatting==0)
		{
			keyPress['/']=0;
			keyDown['/']=0;
			
			chatting=1;
			
			strcpy(inputStr,"/");
			curPos = strlen(inputStr);
		}
		else keyPress[SDLK_RETURN]=1;
	}
	if(keyPress['\\'])
	{
		if(chatting==0)
		{
			keyPress['\\']=0;
			keyDown['\\']=0;
			
			chatting=1;
			
			strcpy(inputStr,"/b ");
			curPos = strlen(inputStr);
		}
		else keyPress[SDLK_RETURN]=1;
	}
	if(keyPress[']'])
	{
		if(chatting==0)
		{
			
			chatting=1;
			
			keyPress[']']=0;
			keyDown[']']=0;
			if(strlen(last_tell)>0)
				sprintf(inputStr,"/t %s ",last_tell);
			else strcpy(inputStr,"/t ");
			curPos = strlen(inputStr);
		}
		else keyPress[SDLK_RETURN]=1;
	}
	if(keyPress['\''])
	{
		if(chatting==0)
		{

			chatting=1;

			keyPress['\'']=0;
			keyDown['\'']=0;
			strcpy(inputStr,"/g ");
			curPos = strlen(inputStr);
		}
		else keyPress[SDLK_RETURN]=1;
	}
	if(keyPress['['] && MYGUY.access > 1)
	{
		if(chatting==0)
		{

			chatting=1;

			keyPress['[']=0;
			keyDown['[']=0;
			strcpy(inputStr,"/admin ");
			curPos = strlen(inputStr);
		}
		else keyPress[SDLK_RETURN]=1;
	}
	if(keyPress['a'] && useTimer.tick(400) && MYGUY.item[0].qty!=0)
	{
		sendCmndMsg("/use 0");	
	}
	else if(keyPress['s'] && useTimer.tick(400) && MYGUY.item[1].qty!=0)
	{
		sendCmndMsg("/use 1");
	}
	else if(keyPress['d'] && useTimer.tick(400) && MYGUY.item[2].qty!=0)
	{
		sendCmndMsg("/use 2");
	}
	else if(keyPress['f'] && useTimer.tick(400) && MYGUY.item[3].qty!=0 && mode!=1)
	{
		sendCmndMsg("/use 3");
	}
	else if(keyPress['g'] && useTimer.tick(400) && MYGUY.item[4].qty!=0)
	{
		sendCmndMsg("/use 4");
	}
	else if(keyPress['h'] && useTimer.tick(400) && MYGUY.item[5].qty!=0)
	{
		sendCmndMsg("/use 5");
	}
	else if(keyPress['j'] && useTimer.tick(400) && MYGUY.item[6].qty!=0)
	{
		sendCmndMsg("/use 6");
	}
	else if(keyPress['z'] && useTimer.tick(400) && MYGUY.item[7].qty!=0)
	{
		sendCmndMsg("/use 7");
	}
	else if(keyPress['x'] && useTimer.tick(400) && MYGUY.item[8].qty!=0)
	{
		sendCmndMsg("/use 8");
	}
	else if(keyPress['c'] && useTimer.tick(400) && MYGUY.item[9].qty!=0)
	{
		sendCmndMsg("/use 9");
	}
	else if(keyPress['v'] && useTimer.tick(400) && MYGUY.item[10].qty!=0)
	{
		sendCmndMsg("/use 10");
	}
	else if(keyPress['b'] && useTimer.tick(400) && MYGUY.item[11].qty!=0)
	{
		sendCmndMsg("/use 11");
	}
	else if(keyPress['n'] && useTimer.tick(400) && MYGUY.item[12].qty!=0)
	{
		sendCmndMsg("/use 12");
	}
	else if(keyPress['m'] && useTimer.tick(400) && MYGUY.item[13].qty!=0)
	{
		sendCmndMsg("/use 13");
	}
	if(keyPress[SDLK_TAB])
	{
		inv_slot++;
		if(inv_slot>1)
			inv_slot=0;
	}
	if(keyPress[SDLK_RSHIFT] || keyPress[SDLK_LSHIFT])
	{
		MAKE_MSG(pick_msg,p,PICK_MSG);
		nc.send((unsigned char *)&p,sizeof(pick_msg),SEND_GUARANTEED);
	}
	if(ptarget_id!=-1)
	{
		pos vi=player[ptarget_id].p;
		if(vi.x!=MYGUY.front().x || vi.y!=MYGUY.front().y)
		{
			if(MYGUY.p.x+1 == vi.x && MYGUY.p.y == vi.y)
			{
				
				MYGUY.dir=3;
				
				moved=true;
			}
			else if(MYGUY.p.x-1 == vi.x && MYGUY.p.y == vi.y)
			{
				
				MYGUY.dir=2;
				
				moved=true;
			}
			else if(MYGUY.p.x == vi.x && MYGUY.p.y-1 == vi.y)
			{
				
				MYGUY.dir=1;
				
				moved=true;
			}
			else if(MYGUY.p.x == vi.x && MYGUY.p.y+1 == vi.y) 
			{
				
				MYGUY.dir=0;
				
				moved=true;
			}
		}
	}
	if(keyDown[SDLK_RCTRL] || keyDown[SDLK_LCTRL])//move in place
	{
		turning=1;
		smove=0;
		if(holdMove)
		{
			if(keyPress[SDLK_RIGHT])
			{
				MYGUY.dir=3;
				moved=true;
				smove=0;
			}
			if(keyPress[SDLK_LEFT])
			{
				MYGUY.dir=2;
				moved=true;
				smove=0;
			}
			if(keyPress[SDLK_UP])
			{
				MYGUY.dir=1;
				moved=true;
				smove=0;
			}
			if(keyPress[SDLK_DOWN])
			{
				MYGUY.dir=0;
				moved=true;
				smove=0;
			}
		}
	}
	else //movement
	{
		
		if(walkTime.tick(walk_delay))
			holdMove=1;
		if(holdMove&&keyDown[SDLK_RIGHT])
		{
			
			MYGUY.dir=3;
			if(world[MYGUY.p.map].canMove(player[me].right()))
			{
				turning=0;
				world[MYGUY.p.map].map[MYGUY.p.row()][MYGUY.p.col()].space=VACANT;
				MYGUY.move(3);
				MYGUY.setCore(world[MYGUY.p.map].getPos(MYGUY.getCore()));
				if(MYGUY.p.map>=world.size())
					world.size(MYGUY.p.map+100);
				world[MYGUY.p.map].map[MYGUY.p.row()][MYGUY.p.col()].space=me;
				//debugMsg("moved to %d %d %d",MYGUY.p.map,MYGUY.p.x,MYGUY.p.y);
			}
			else turning=1;
			
			moved=true;
			holdMove=0;
			walkTime.reset();
		}
		if(holdMove&&keyDown[SDLK_LEFT])
		{
			MYGUY.dir=2;
			if(world[MYGUY.p.map].canMove(player[me].left()))
			{
				turning=0;
				world[MYGUY.p.map].map[MYGUY.p.row()][MYGUY.p.col()].space=VACANT;
				MYGUY.move(2);
				MYGUY.setCore(world[MYGUY.p.map].getPos(MYGUY.getCore()));
				if(MYGUY.p.map>=world.size())
					world.size(MYGUY.p.map+100);
				world[MYGUY.p.map].map[MYGUY.p.row()][MYGUY.p.col()].space=me;
				//debugMsg("moved to %d %d %d",MYGUY.p.map,MYGUY.p.x,MYGUY.p.y);
			}
			else turning=1;
			moved=true;
			holdMove=0;
			walkTime.reset();
		}
		if(holdMove&&keyDown[SDLK_UP])
		{
			MYGUY.dir=1;
			if(world[MYGUY.p.map].canMove(player[me].up()))
			{
				turning=0;
				world[MYGUY.p.map].map[MYGUY.p.row()][MYGUY.p.col()].space=VACANT;
				MYGUY.move(1);
				MYGUY.setCore(world[MYGUY.p.map].getPos(MYGUY.getCore()));
				if(MYGUY.p.map>=world.size())
					world.size(MYGUY.p.map+100);
				world[MYGUY.p.map].map[MYGUY.p.row()][MYGUY.p.col()].space=me;
				//debugMsg("moved to %d %d %d",MYGUY.p.map,MYGUY.p.x,MYGUY.p.y);
			}
			else turning=1;
			
			moved=true;
			holdMove=0;
			walkTime.reset();
		}
		if(holdMove&&keyDown[SDLK_DOWN])
		{
			MYGUY.dir=0;
			if(world[MYGUY.p.map].canMove(player[me].down()))
			{
				turning=0;
				world[MYGUY.p.map].map[MYGUY.p.row()][MYGUY.p.col()].space=VACANT;
				MYGUY.move(0);
				MYGUY.setCore(world[MYGUY.p.map].getPos(MYGUY.getCore()));
				if(MYGUY.p.map>=world.size())
					world.size(MYGUY.p.map+100);
				world[MYGUY.p.map].map[MYGUY.p.row()][MYGUY.p.col()].space=me;
				//debugMsg("moved to %d %d %d",MYGUY.p.map,MYGUY.p.x,MYGUY.p.y);
			}
			else turning=1;
			
			moved=true;
			holdMove=0;
			walkTime.reset();
		}
	}
	if (moved)
	{
		moved=false;
		int warp=0;
		if(world[MYGUY.p.map].map[MYGUY.p.row()][MYGUY.p.col()].type==WARP)
			warp=1;
		//SEND PLAYER BASE
		MAKE_MSG(mycr_msg,msg,MYCR_MSG);
		msg.dir=MYGUY.dir;
		msg.p=MYGUY.p;
		//if(!turning || walkTime.tick(250))
			nc.send((unsigned char *)&msg,sizeof(mycr_msg),SEND_GUARANTEED);
		if(MYGUY.p.map !=oldmap && !warp)
		{
			//debugMsg("INPUT:Oldmap before %d",oldmap);
			updateMapDialog();
			SDL_WM_SetCaption(world[MYGUY.p.map].name, "ORCB");
			
			for(int i=0;i<item.size();i++)
				item[i].qty=0;
			oldmap=MYGUY.p.map;
			
			//debugMsg("INPUT:Oldmap now %d",oldmap);
			MAKE_MSG(parm_msg,temp,PARM_MSG);
			temp.parm=0;
			temp.flag=world[MYGUY.p.map].version;
			nc.send((unsigned char *)&temp,sizeof(parm_msg),SEND_GUARANTEED);
			//debugMsg("INPUT:version sent %d",world[MYGUY.p.map].version);
			buildMapLayers();
			if(curMidi!=world[MYGUY.p.map].npc[4].index && strcmp(world[MYGUY.p.map].name,"_EMPTY_")!=0)
				playMidi(world[MYGUY.p.map].npc[4].index);
		}
	}
}

