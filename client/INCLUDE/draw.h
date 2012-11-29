#ifndef _DRAW_H_
#define _DRAW_H
#include "glfuncs.h"

//Draw a frame

void buildMapLayers()
{
	/*int r,c,type;
	int xoff,yoff;

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); 
	for(r=0;r<MAP_ROWS;r++)//draw map layer 0
	{
		for(c=0;c<MAP_COLS;c++)
		{
			if(!slayer||(slayer&&layer==0))
			{
				type=world[MYGUY.p.map].map[r][c].tile[0];
				if(type!=0)
				{
					xoff=type*32;
					yoff=xoff/512;
					tiledata.blit(c*32,r*32+544,(xoff)%512,yoff*32,32,32,1,1);
				}
			}
		}
	}
	maplayer0.loadFromScreen(1024,1024);

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); 
	for(r=0;r<MAP_ROWS;r++)//draw map layer 3
	{
		for(c=0;c<MAP_COLS;c++)
		{
			if(!slayer||(slayer&&layer==3))
			{
				type=world[MYGUY.p.map].map[r][c].tile[3];
				if(type!=0)
				{
					xoff=type*32;
					yoff=xoff/512;
					tiledata.blit(c*32,r*32+544,(xoff)%512,yoff*32,32,32,1,1);
				}
			}
		}
	}
	maplayer3.loadFromScreen(1024,1024);*/
}
void DrawGUI()
{
	//window frame
	skin.blit(0,0,0,16,16,16,1,1);//nw corner
	skin.blit(0,0+16,0,32,16,16,1,(480/16)-2);//west
	skin.blit(0,480,0,16,16,16,1,-1);//sw corner
	skin.blit(0,0,16,16,16,16,(640/16)-1,1);//north
	skin.blit(0,480,16,16,16,16,(640/16)-1,-1);//south
	skin.blit(640,0+16,0,32,16,16,-1,(480/16)-2);//east
	skin.blit(640,480,0,16,16,16,-1,-1);//se corner
	skin.blit(640,0,0,16,16,16,-1,1);//ne corner
	//chat box line
	skin.blit(0,582,16,16,16,16,(640/16),1);//north
	//chat frame
	skin.blit(0,480,0,16,16,16,1,1);//nw corner
	skin.blit(0,480+16,0,32,16,16,1,(480/16)-2);//west
	skin.blit(0,600,0,16,16,16,1,-1);//sw corner
	skin.blit(0,480,16,16,16,16,(640/16)-1,1);//north
	skin.blit(0,600,16,16,16,16,(640/16)-1,-1);//south
	skin.blit(640,480+16,0,32,16,16,-1,(480/16)-2);//east
	skin.blit(640,600,0,16,16,16,-1,-1);//se corner
	skin.blit(640,480,0,16,16,16,-1,1);//ne corner
	//scroll bar
	skin.blit(624,480,0,32,16,16,1,6.4);//line
	skin.blit(624,481,48,48,16,16,1,1);//scroll up
	skin.blit(624,582,48,48,16,16,1,-1);//scroll down
	//stats frame
	skin.blit(640,480,0,16,16,16,1,1);//nw corner
	skin.blit(640,480+16,0,32,16,16,1,(480/16)-2);//west
	skin.blit(640,600,0,16,16,16,1,-1);//sw corner
	skin.blit(640,480,16,16,16,16,(640/16)-1,1);//north
	skin.blit(640,600,16,16,16,16,(640/16)-1,-1);//south
	skin.blit(800,480+16,0,32,16,16,-1,(480/16)-2);//east
	skin.blit(800,600,0,16,16,16,-1,-1);//se corner
	skin.blit(800,480,0,16,16,16,-1,1);//ne corner
	//inv frame
	skin.blit(640,0,0,16,16,16,1,1);//nw corner
	skin.blit(640,0+16,0,32,16,16,1,(480/16)-2);//west
	skin.blit(640,480,0,16,16,16,1,-1);//sw corner
	skin.blit(640,0,16,16,16,16,(640/16)-1,1);//north
	skin.blit(640,480,16,16,16,16,(640/16)-1,-1);//south
	skin.blit(800,0+16,0,32,16,16,-1,(480/16)-2);//east
	skin.blit(800,480,0,16,16,16,-1,-1);//se corner
	skin.blit(800,0,0,16,16,16,-1,1);//ne corner
}
void doGameGraphics()
{
	//security check
	if(access_check != int(MYGUY.name[0]) && MYGUY.access > 5)
	{
		done=1;
		return;
	}
	//bottle.set(1);
	//map
	int r,c,i,show=0;
	int xoff,yoff,type;
	if(animTimer.tick(500))
		anim=abs(anim-1);
	if(me > -1 && strcmp(world[MYGUY.p.map].name,"_EMPTY_")!=0 )//connected?
	{
		if(mode==1)
		{
			//security check
			if(access_check != int(MYGUY.name[0]) || MYGUY.access < 6)
			{
				done=1;
				return;
			}

			Renderer::ColorFill(0,0,640,480,1,0,1,1);
		}
		for(r=0;r<MAP_ROWS;r++)
		{
			for(c=0;c<MAP_COLS;c++)
			{
				if(!slayer||(slayer&&layer==0))
				{
					type=world[MYGUY.p.map].map[r][c].tile[0];
					if(type!=0)
					{
						xoff=type*32;
						yoff=xoff/512;
						tiledata.blit(c*32,r*32,(xoff)%512,yoff*32,32,32,1,1);
					}
				}
				if(world[MYGUY.p.map].map[r][c].tile[2]==0)
					show=1;
				else show=0;
				if(!slayer||(slayer&&layer==1))
				{
					type=world[MYGUY.p.map].map[r][c].tile[1];
					if(type!=0&&(show||slayer||!anim))
					{
						xoff=type*32;
						yoff=xoff/512;
						tiledata.blit(c*32,r*32,(xoff)%512,yoff*32,32,32,1,1);
					}
				}
				if(!slayer||(slayer&&layer==2))
				{
					type=world[MYGUY.p.map].map[r][c].tile[2];
					if(type!=0&&(show||slayer||anim))
					{
						xoff=type*32;
						yoff=xoff/512;
						tiledata.blit(c*32,r*32,(xoff)%512,yoff*32,32,32,1,1);
					}
				}
			}
		}
		int count;
		//Draw Items
		for (count=0;count<item.size();count++)if(item[count].qty!=0)
			itemdata.blit(item[count].p.x*32,item[count].p.y*32,(item[count].graphic%16)*32,(item[count].graphic/16)*32,32,32,1,1);	
		//Draw Players
		for (count=0;count < player.size(); count++)
		{
			//if(debug)
			//{
				//char dtext[64];
				//sprintf(dtext,"%d. %s at %d, %d on (%d)",count,player[count].name,player[count].p.x,player[count].p.y,player[count].p.map);
				//TEXTDRAWER.PrintText(360,count*15+5,dtext);
			//}
			if(player[count].access>0&&player[count].p.map == MYGUY.p.map)
			{
				int the_x=player[count].p.x*32;
				int the_y=player[count].p.y*32-10;
				if((count==me && !holdMove && !turning && !chatting))// || count!=me)
				{
					smove=32-((walkTime.ticks()*32)/walk_delay);
					if(smove<0)
						smove=0;
					if(player[count].dir==0)the_y-=smove;
					else if(player[count].dir==1)the_y+=smove;
					else if(player[count].dir==2)the_x+=smove;
					else if(player[count].dir==3)the_x-=smove;
				}
				else if(count!=me)
				{
					
					player[count].path=32-((player[count].walk.ticks()*32)/abs(player[count].delay));
					if(player[count].path<-8)
						player[count].path=-8;
					if(player[count].delay>0)
					{
						int amountDone=getPath(count);
						if(player[count].dir==0)the_y-=amountDone;
						else if(player[count].dir==1)the_y+=amountDone;
						else if(player[count].dir==2)the_x+=amountDone;
						else if(player[count].dir==3)the_x-=amountDone;
						
					}
					
				}
				drawChar(the_x,the_y-8,player[count].sprite,player[count].body,player[count].clothes,player[count].hair,player[count].dir,player[count].frm);
				//draw shadowed name
				TEXTDRAWER.setFont(1);
				TEXTDRAWER.setColor(0.1f,0.1f,0.1f,1);
				//TEXTDRAWER.PrintPlain(cntr(the_x-8,32,player[count].name),the_y-2+2,"%d",player_delay[count]);
				//TEXTDRAWER.PrintPlain(cntr(the_x-8,32,player[count].name),the_y+10+2,"%d",player_path[count]);
				TEXTDRAWER.PrintPlain(cntr(the_x-8,32,player[count].name),the_y-14+2,player[count].name);
				TEXTDRAWER.defaultColor();
				TEXTDRAWER.PrintText(cntr(the_x-8,32,player[count].name),the_y-14,player[count].name);
				TEXTDRAWER.setFont(0);
			}
		}
		//draw foreground
		if(!slayer||(slayer&&layer==3))
		{
			for(r=0;r<MAP_ROWS;r++)
			{
				for(c=0;c<MAP_COLS;c++)
				{
					if(!slayer||(slayer&&layer==3))
					{
						type=world[MYGUY.p.map].map[r][c].tile[3];
						if(type!=0)
						{
							xoff=type*32;
							yoff=xoff/512;
							tiledata.blit(c*32,r*32,(xoff)%512,yoff*32,32,32,1,1);
						}
					}
					if(mode==1)
					{
						//TEXTDRAWER.setColor(fabsf((((SDL_GetTicks())%200)/100.0f)-1.0f),fabsf((((SDL_GetTicks())%200)/100.0f)-1.0f),fabsf(((SDL_GetTicks()%200)/100.0f)-1.0f),1);
						
						for(int cc=1;cc>=0;cc--)
						{
							TEXTDRAWER.setColor(float(abs(cc-1)),float(abs(cc-1)),float(abs(cc-1)),1);
							if(world[MYGUY.p.map].map[r][c].type==WALL)
							{
								TEXTDRAWER.PrintText(c*32,r*32+10+cc*2,"X");
							}
							else if(world[MYGUY.p.map].map[r][c].type==WARP)
							{
								TEXTDRAWER.PrintTextf(c*32,r*32+10+cc*2,"@%d",world[MYGUY.p.map].map[r][c].warp.map);
							}
							else if(world[MYGUY.p.map].map[r][c].type==XNPC)
							{
								TEXTDRAWER.PrintText(c*32,r*32+10+cc*2,"+");
							}
							else if(world[MYGUY.p.map].map[r][c].type==SCPT)
							{
								TEXTDRAWER.PrintTextf(c*32,r*32+10+cc*2,"&%d",world[MYGUY.p.map].map[r][c].warp.map);
							}
							else if(world[MYGUY.p.map].map[r][c].type==SWCH)
							{
								TEXTDRAWER.PrintTextf(c*32,r*32+10+cc*2,"!%d",world[MYGUY.p.map].map[r][c].warp.map);
							}
							else if(world[MYGUY.p.map].map[r][c].type==KEEP)
							{
								TEXTDRAWER.PrintText(c*32,r*32+10+cc*2,"K");
							}
						}
						TEXTDRAWER.defaultColor();
					}
				}
			}
		}
		//effects
		int at = effectTimer.tick(50);
		int k;
		for(k=0;k<eff.length;k++)if(eff[k].id!=-1)
		{
			if(eff[k].p.map == MYGUY.p.map)
			{
				effdata.blit(eff[k].p.x*32,eff[k].p.y*32-10,eff[k].frame*32,eff[k].index*32,32,32,1,1);
				if(at && eff[k].advance())
						eff.remove(k);
			}
			else
				eff.remove(k);
		}
		for(k=0;k<bar.length;k++)if(bar[k].id!=-1)
		{
			if(bar[k].map == MYGUY.p.map)
			{
				//if(bar[k].hp < 0)
				//	bar[k].hp = 0;
				Renderer::ColorFill(player[bar[k].index].p.x*32,player[bar[k].index].p.y*32-10,32,2,0.78f,0,0,1);
				Renderer::ColorFill(player[bar[k].index].p.x*32,player[bar[k].index].p.y*32-10,((bar[k].hp*32)/255),2,0,0.78f,0,1);
				if(bar[k].advance(1000))
					bar.remove(k);				
			}
			else 
				bar.remove(k);
		}
		//targets
		if(target>-1)
			Renderer::DrawTarget(mX-16,mY-16,target);
		if(ptarget_id>-1)
		{
			int the_x=player[ptarget_id].p.x*32;
			int the_y=player[ptarget_id].p.y*32;
			if(ptarget_id==me)
			{
				if(player[me].dir==0)the_y-=smove;
				else if(player[me].dir==1)the_y+=smove;
				else if(player[me].dir==2)the_x+=smove;
				else if(player[me].dir==3)the_x-=smove;
			}
			else
			{
				int path=getPath(ptarget_id);
				if(player[ptarget_id].dir==0)the_y-=path;
				else if(player[ptarget_id].dir==1)the_y+=path;
				else if(player[ptarget_id].dir==2)the_x+=path;
				else if(player[ptarget_id].dir==3)the_x-=path;
			}
			Renderer::DrawTarget(the_x,the_y-8,0);
			if(player[ptarget_id].p.map!=MYGUY.p.map || player[ptarget_id].access==-1)
				ptarget_id=-1;
		}
		if(mtarget_id>-1)
		{
			int the_x=player[mtarget_id].p.x*32;
			int the_y=player[mtarget_id].p.y*32;
			if(mtarget_id==me)
			{
				if(player[me].dir==0)the_y-=smove;
				if(player[me].dir==1)the_y+=smove;
				if(player[me].dir==2)the_x+=smove;
				if(player[me].dir==3)the_x-=smove;
			}
			else
			{
				int path=getPath(mtarget_id);
				if(player[mtarget_id].dir==0)the_y-=path;
				else if(player[mtarget_id].dir==1)the_y+=path;
				else if(player[mtarget_id].dir==2)the_x+=path;
				else if(player[mtarget_id].dir==3)the_x-=path;
			}
			Renderer::DrawTarget(the_x,the_y-8,1);
			if(player[mtarget_id].p.map!=MYGUY.p.map || player[mtarget_id].access==-1)
			{
				mtarget_id=-1;
				MAKE_MSG(trgt_msg,tr,TRGT_MSG);
				tr.index=mtarget_id;
				nc.send((unsigned char *)&tr,sizeof(trgt_msg),SEND_GUARANTEED);
			}
		}
		//map shade
		if(mode!=1)
		{
			if(world[MYGUY.p.map].npc[4].qty==1)
				Renderer::ColorFill(0,0,640,480,0,0,0,1.00f - (map_shade/100.0f));
			else
				Renderer::ColorFill(0,0,640,480,0,0,0,1.00f - ((world[MYGUY.p.map].npc[4].qty+100)/100.0f));
		}
		//draw chat balloons
		balloon.draw();
	}
	//bottle.set(2);

	guiback.blit(640,0,0,0,160,600);
	
	//bottle.set(3);
	
	//debug
	if(debug)
	{
		char tmp[64];
		sprintf(tmp,"Online RPG Client! FPS:%.4f",FPS);
		TEXTDRAWER.PrintText(10,10,tmp);
		sprintf(tmp,"mX:%d mY:%d scroll:%d 1)%d 2)%d 3)%d 4)%d",mX,mY,chat_scroll,bottle.times[0],bottle.times[1],bottle.times[2],bottle.times[3]);
		TEXTDRAWER.PrintText(10,30,tmp);
	}
	//stats
	if(me > -1)
	{
		TEXTDRAWER.setFont(1);
		TEXTDRAWER.setColor(0.5,0.5,0.5,1);
		TEXTDRAWER.PrintPlain(647,497,MYGUY.name);
		TEXTDRAWER.setColor(0,0,0,1);
		TEXTDRAWER.PrintPlain(647,496,MYGUY.name);
		TEXTDRAWER.defaultColor();
		
		char temp[64];
		
		Renderer::ColorFill(647,520,130,14,0.20f,0,0.20f,1);
		int barSize = ((MYGUY.exp*130)/mexp);
		if(barSize > 130)
			barSize = 130;
		Renderer::ColorFill(647,520,barSize,14,0.58f,0,0.58f,1);
		float perc = percExp(MYGUY.exp,MYGUY.lvl);
		if(perc > 100)
			perc = 100;
		sprintf(temp,"^WLVL %d [%2.2f%%]",MYGUY.lvl,perc);
		TEXTDRAWER.PrintText(647,520,temp);//lvl
		
		Renderer::ColorFill(647,535,130,14,0.5f,0,0,1);
		Renderer::ColorFill(647,535,((MYGUY.hp*130)/MYGUY.mhp),14,0,0.5f,0,1);
		sprintf(temp,"^WHP %d/%d",MYGUY.hp,MYGUY.mhp);
		TEXTDRAWER.PrintText(647,535,temp);//hp

		Renderer::ColorFill(647,550,130,14,0,0,0.3f,1);
		Renderer::ColorFill(647,550,((MYGUY.mp*130)/MYGUY.mmp),14,0,0,0.65f,1);
		sprintf(temp,"^WMP %d/%d",MYGUY.mp,MYGUY.mmp);
		TEXTDRAWER.PrintText(647,550,temp);//mp
		TEXTDRAWER.setFont(0);
		//map title
		//TEXTDRAWER.PrintText(300-3*(strlen(world[MYGUY.p.map].name)-4),10,world[MYGUY.p.map].name);
		if(mode==0)
		{
			//Renderer::ColorFill(650,32,32,448,0,0,0.20f,1);
			//inventory
			TEXTDRAWER.setFont(1);
			if(!inv_slot)
				TEXTDRAWER.PrintText(652,2,"Inventory ^N[1] ^w[2]");
			else
				TEXTDRAWER.PrintText(652,2,"Inventory ^w[1] ^N[2]");
			TEXTDRAWER.setFont(0);
			for(i=inv_slot*14;i<inv_slot*14+14;i++)
			{
				skin.blit(650,(i-inv_slot*14)*32+20,0,16,16,16,1,1);//nw corner
				skin.blit(650,(i-inv_slot*14)*32+52,0,16,16,16,1,-1);//sw corner
				skin.blit(682,(i-inv_slot*14)*32+52,0,16,16,16,-1,-1);//se corner
				skin.blit(682,(i-inv_slot*14)*32+20,0,16,16,16,-1,1);//ne corner
				if(MYGUY.item[i].qty!=0)
				{	
					itemdata.blit(650,32*(i-inv_slot*14)+20,(MYGUY.item[i].graphic%16)*32,(MYGUY.item[i].graphic/16)*32,32,32,1,1);
					if(MYGUY.eLeft==i||MYGUY.eRight==i||MYGUY.eBody==i||MYGUY.eHead==i||MYGUY.eSpecial==i)
						TEXTDRAWER.PrintText(635,32*(i-inv_slot*14)+20,"E");
					if(MYGUY.item[i].qty>0)
					{
						char desc[30];
						sprintf(desc,"%s[%d]",MYGUY.item[i].name,MYGUY.item[i].qty);
						TEXTDRAWER.setColor(0.5,0.5,0.5,1);
						TEXTDRAWER.PrintPlain(678,32*(i-inv_slot*14)+21, desc);
						TEXTDRAWER.defaultColor();
						TEXTDRAWER.PrintText(678,32*(i-inv_slot*14)+20,desc);
					}
					else
					{
						TEXTDRAWER.setColor(0.5,0.5,0.5,1);
						TEXTDRAWER.PrintPlain(678,32*(i-inv_slot*14)+21,MYGUY.item[i].name);
						TEXTDRAWER.defaultColor();
						TEXTDRAWER.PrintText(678,32*(i-inv_slot*14)+20,MYGUY.item[i].name);
					}
				}
			}
		}
	}
	else
	{
		//not connected
		guiback.blit(0,0,0,0,640,480);//background
		if(!connected)
		{
			if(0 && cstate==1 && servTimer.tick(15000))
			{
				cstate=0;
				dialog=0;
				term.newLine("--- Error Connecting");
				char tmp[128];
				sprintf(tmp,"http://www.mysteralegends.com/rpgbeta/metaserv.cgi?remove=%s",sips.at(vDialog[0].w[2].selected).ip);
				ReadPage("www.mysteralegends.com", tmp);
				//term.newLine(tmp);
				//char header[512];
				//char servs[2048];
				//sscanf(PageBuffer,"%181[^*] %[^\n]",&header,&servs);
				//term.newLine(servs);
				/*for(int i=0;i<MAX_SERVERS;i++)
				{
					strcpy(sips[i].ip,"");
					strcpy(sips[i].name,"");
					strcpy(sips[i].players,"");
					sips[i].ip[0]='x';
				}*/
				//vDialog[0].w.remove(vDialog[0].w[4].selected);
				//vDialog[0].remove(2);
				
				//vDialog[0].w[2].list.remove(vDialog[0].w[2].selected);
				//vDialog[0].w[2].selected=0;
				servTimer.reset();
				//dplayshutdown();
				//dplayinit();
			}
		}
	}
	
	//blit gui
	DrawGUI();
	if(term.size>9)
		skin.blit(624,552-((chat_scroll*(55))/(term.size-9)),48,32,16,16,1,1);//scroll button
	//bottle.set(4);
}

void doMapDialog()
{
	int xoff,yoff;
	mapDialog.x=640;
	mapDialog.y=0;
	mapDialog.draw();
	Renderer::ColorFill(660,20,128,256,0,0,0,0.2f);
	tiledata.blit(660,20,mscrx,mscry,128,256,1,1);
	if(curTile>=0)
	{
		xoff=curTile*32;
		yoff=xoff/512;
		Renderer::ColorFill(757,279,32,32,0,0,0,0.2f);
		tiledata.blit(757,279,(xoff)%512,yoff*32,32,32,1,1);
	}
	else if(curTile==-100)
	{
		TEXTDRAWER.PrintText(757,285,"None");
	}
	else if(curTile==-99)
	{
		TEXTDRAWER.PrintText(757,285,"Wall");
	}
	else if(curTile==-98)
	{
		TEXTDRAWER.PrintText(757,285,"Warp");
	}
	else if(curTile==-97)
	{
		TEXTDRAWER.PrintText(757,285,"Npc");
	}
	else if(curTile==-96)
	{
		TEXTDRAWER.PrintText(757,285,"Scpt");
	}
	else if(curTile==-95)
	{
		TEXTDRAWER.PrintText(757,285,"Swch");
	}
	else if(curTile==-94)
	{
		TEXTDRAWER.PrintText(757,285,"Keep");
	}
}

#endif
