#include "Input.h"
//get input
void doGameInput()
{
    //admin options
    if(MYGUY.access>5)
    {
        if(Input::IsKeyDown(SDLK_MLEFT))
        {
            if(mode==1)//map buttons
            {
            }
        }
        if(Input::IsPressed(SDLK_MLEFT))//buttons
        {
            if(mode==1)//map buttons
            {
            }
        }
        if(Input::IsKeyDown(SDLK_MRIGHT))
        {
            if(mode==1)
            {
                if(Input::MouseX() < 640 && Input::MouseY() < 480)//tile grabber
                {

                    curTile=world[MYGUY.p.map].map[Input::MouseY()/32][Input::MouseX()/32].tile[layer];

                }
                if(Input::MouseX() >= 660 && Input::MouseY() >= 20 && Input::MouseX() <= 788 && Input::MouseY() <= 276 && anyTimer.tick(100))//tile scroller
                {
                    mscrx+=(Input::MouseX()-(660+64))/2;
                    mscry+=(Input::MouseY()-(20+128))/2;
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
        if(Input::IsKeyDown(SDLK_MLEFT))
        {
            if(mode==1)
            {
                if(Input::MouseX() >= 660 && Input::MouseY() >= 20 && Input::MouseX() <= 788 && Input::MouseY() <= 276)//tile select
                {

                    curTile=((Input::MouseX()-660+mscrx)/32) + (((Input::MouseY()-20+mscry)/32)*(tiledata.w/32));

                }
                else if(Input::MouseX() < 640 && Input::MouseY() < 480)//tile draw
                {

                    if(curTile >= 0)
                    {
                        world[MYGUY.p.map].map[Input::MouseY()/32][Input::MouseX()/32].tile[layer]=curTile;
                    }
                    else
                    {
                        world[MYGUY.p.map].map[Input::MouseY()/32][Input::MouseX()/32].type = curTile+101;
                        if(curTile==-98)
                            world[MYGUY.p.map].map[Input::MouseY()/32][Input::MouseX()/32].warp=warp;
                        else if(curTile==-96 || curTile==-95)
                            world[MYGUY.p.map].map[Input::MouseY()/32][Input::MouseX()/32].warp.map=map_script;
                    }

                }
            }
        }
        if(Input::IsPressed('f'))
        {
            if(mode==1)
            {

                if(curTile >= 0)
                    fillwith(Input::MouseY()/32,Input::MouseX()/32,world[MYGUY.p.map].map[Input::MouseY()/32][Input::MouseX()/32].tile[layer]);
                else
                    fillwith(Input::MouseY()/32,Input::MouseX()/32,world[MYGUY.p.map].map[Input::MouseY()/32][Input::MouseX()/32].type);

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
    if(Input::IsPressed(SDLK_MRIGHT))
    {
        if(mode==0)
        {
            if(Input::MouseX()<640&&Input::MouseY()<480)
            {
                target++;
                if(target>1)
                    target=-1;
            }
            if(Input::MouseX() > 645 && Input::MouseX() < 677 && Input::MouseY() > 20 && Input::MouseY() < 468 && MYGUY.item[((Input::MouseY()-20)/32)+inv_slot*14].qty!=0)//item drop
            {
                chatting=0;
                MAKE_MSG(drop_msg,msg,DROP_MSG);
                msg.index=((Input::MouseY()-20)/32)+(inv_slot*14);
                if(MYGUY.item[msg.index].qty>1)
                {
                    //init drop dialog on stackable items
                    dropSlot=msg.index;
                    sprintf(vDialog[5].w[2].label,"%ld",MYGUY.item[dropSlot].qty);
                    Input::SetString(vDialog[5].w[2].label);
                    vDialog[5].w[2].state=UX_ACTIVE;
                    dialog=5;
                }
                else
                    nc.send((unsigned char *)&msg,sizeof(drop_msg),SEND_GUARANTEED);
            }
        }
    }
    if(Input::IsPressed(SDLK_MLEFT))
    {
        if(mode==0)
        {
            if(Input::MouseX()<640&&Input::MouseY()<480)
            {
                if(world[MYGUY.p.map].map[(Input::MouseY()+8)/32][Input::MouseX()/32].space!=VACANT)
                {
                    if(target==0 && world[MYGUY.p.map].map[(Input::MouseY()+8)/32][Input::MouseX()/32].space!=me)
                    {
                        ptarget_id=world[MYGUY.p.map].map[(Input::MouseY()+8)/32][Input::MouseX()/32].space;
                        target=-1;
                    }
                    else if(target==1)
                    {
                        mtarget_id=world[MYGUY.p.map].map[(Input::MouseY()+8)/32][Input::MouseX()/32].space;
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
            if(Input::MouseX() > 650 && Input::MouseX() < 682 && Input::MouseY() > 20 && Input::MouseY() < 468 && useTimer.tick(400) && MYGUY.item[((Input::MouseY()-20)/32)+inv_slot*14].qty!=0)//item equip
            {
                char temp[256];
                sprintf(temp,"/use %d",((Input::MouseY()-20)/32)+inv_slot*14);
                sendCmndMsg(temp);
            }
        }
    }
    if(term.size>9) //scrolling
    {
        if( Input::IsKeyUp(SDLK_MLEFT) && Input::MouseX()>624 && Input::MouseX()<640 && Input::MouseY()>480 && Input::MouseY()<496)
        {
            chat_scroll++;
            if(chat_scroll>term.size-9)
                chat_scroll=term.size-9;
        }
        else if(Input::IsKeyUp(SDLK_MLEFT) && Input::MouseX()>624 && Input::MouseX()<640 && Input::MouseY()>566 && Input::MouseY()<582)
        {
            chat_scroll--;
            if(chat_scroll<0)
                chat_scroll=0;
        }
        else if(Input::IsKeyDown(SDLK_MLEFT) && Input::MouseX()>624 && Input::MouseX()<640 && Input::MouseY()>496 && Input::MouseY()<566)
        {
            chat_scroll=term.size-9-((Input::MouseY()-8-496)*(term.size-9))/(55);
            if(chat_scroll<0)chat_scroll=0;
            if(chat_scroll>term.size-9)
                chat_scroll=term.size-9;
        }
    }
    if(Input::IsPressed(SDLK_SPACE))
    {
        if(MYGUY.front().inBounds() && world[MYGUY.p.map].map[MYGUY.front().y][MYGUY.front().x].type==SWCH)
        {
            MAKE_MSG(parm_msg,hello,PARM_MSG);
            hello.flag = 3;
            nc.send((unsigned char *)&hello,sizeof(parm_msg),SEND_GUARANTEED);
        }
    }
    if((Input::IsKeyDown(SDLK_SPACE) || (ptarget_id!=-1&&MYGUY.front()==player[ptarget_id].p))&& attackTimer.tick(550))
        attack();
    if(Input::IsPressed('/'))
    {
        if(chatting==0)
        {
            chatting=1;
            Input::SetString("/");
        }
    }
    if(Input::IsPressed('\\'))
    {
        if(chatting==0)
        {
            chatting=1;
            Input::SetString("/b ");
        }
    }
    if(Input::IsPressed(']'))
    {
        if(chatting==0)
        {
            chatting=1;

            char tmpStr[128];

            if(strlen(last_tell)>0)
            {
                sprintf(tmpStr,"/t %s ", last_tell);
                Input::SetString(tmpStr);
            }
            else
                Input::SetString("/t ");
        }
    }
    if(Input::IsPressed('\''))
    {
        if(chatting==0)
        {
            chatting=1;
            Input::SetString("/g ");
        }
    }
    if(Input::IsPressed('[') && MYGUY.access > 1)
    {
        if(chatting==0)
        {
            chatting=1;
            Input::SetString("/admin ");
        }
    }
    if(Input::IsPressed('a') && useTimer.tick(400) && MYGUY.item[0].qty!=0)
    {
        sendCmndMsg("/use 0");
    }
    else if(Input::IsPressed('s') && useTimer.tick(400) && MYGUY.item[1].qty!=0)
    {
        sendCmndMsg("/use 1");
    }
    else if(Input::IsPressed('d') && useTimer.tick(400) && MYGUY.item[2].qty!=0)
    {
        sendCmndMsg("/use 2");
    }
    else if(Input::IsPressed('f') && useTimer.tick(400) && MYGUY.item[3].qty!=0 && mode!=1)
    {
        sendCmndMsg("/use 3");
    }
    else if(Input::IsPressed('g') && useTimer.tick(400) && MYGUY.item[4].qty!=0)
    {
        sendCmndMsg("/use 4");
    }
    else if(Input::IsPressed('h') && useTimer.tick(400) && MYGUY.item[5].qty!=0)
    {
        sendCmndMsg("/use 5");
    }
    else if(Input::IsPressed('j') && useTimer.tick(400) && MYGUY.item[6].qty!=0)
    {
        sendCmndMsg("/use 6");
    }
    else if(Input::IsPressed('z') && useTimer.tick(400) && MYGUY.item[7].qty!=0)
    {
        sendCmndMsg("/use 7");
    }
    else if(Input::IsPressed('x') && useTimer.tick(400) && MYGUY.item[8].qty!=0)
    {
        sendCmndMsg("/use 8");
    }
    else if(Input::IsPressed('c') && useTimer.tick(400) && MYGUY.item[9].qty!=0)
    {
        sendCmndMsg("/use 9");
    }
    else if(Input::IsPressed('v') && useTimer.tick(400) && MYGUY.item[10].qty!=0)
    {
        sendCmndMsg("/use 10");
    }
    else if(Input::IsPressed('b') && useTimer.tick(400) && MYGUY.item[11].qty!=0)
    {
        sendCmndMsg("/use 11");
    }
    else if(Input::IsPressed('n') && useTimer.tick(400) && MYGUY.item[12].qty!=0)
    {
        sendCmndMsg("/use 12");
    }
    else if(Input::IsPressed('m') && useTimer.tick(400) && MYGUY.item[13].qty!=0)
    {
        sendCmndMsg("/use 13");
    }
    if(Input::IsPressed(SDLK_TAB))
    {
        inv_slot++;
        if(inv_slot>1)
            inv_slot=0;
    }
    if(Input::IsPressed(SDLK_RSHIFT) || Input::IsPressed(SDLK_LSHIFT))
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
    if(Input::IsKeyDown(SDLK_RCTRL) || Input::IsKeyDown(SDLK_LCTRL))//move in place
    {
        turning=1;
        smove=0;
        if(holdMove)
        {
            if(Input::IsPressed(SDLK_RIGHT))
            {
                MYGUY.dir=3;
                moved=true;
                smove=0;
            }
            if(Input::IsPressed(SDLK_LEFT))
            {
                MYGUY.dir=2;
                moved=true;
                smove=0;
            }
            if(Input::IsPressed(SDLK_UP))
            {
                MYGUY.dir=1;
                moved=true;
                smove=0;
            }
            if(Input::IsPressed(SDLK_DOWN))
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
        if(holdMove && Input::IsKeyDown(SDLK_RIGHT))
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
        if(holdMove && Input::IsKeyDown(SDLK_LEFT))
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
        if(holdMove && Input::IsKeyDown(SDLK_UP))
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
        if(holdMove && Input::IsKeyDown(SDLK_DOWN))
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

            for(int i=0; i<item.size(); i++)
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

