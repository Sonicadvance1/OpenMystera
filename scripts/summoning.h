struct creature
{
	int id;
	int lvl;
	int useables[10];
	char chant[128];
};

creature summons[]=
{
	{21,255,{358,1,285,-1,-1,-1,-1,-1,-1},"^rargos"},
	{129,1,{358,1,285,-1,-1,-1,-1,-1,-1},"stupid sheep"},
	{131,90,{358,1,285,-1,-1,-1,-1,-1,-1},"dan"},
	{130,30,{358,1,285,-1,-1,-1,-1,-1,-1},"protect me!"},
	{134,10,{358,1,285,-1,-1,-1,-1,-1,-1},"i choose you farfetched!"}
	

};
const int summonsize=sizeof(summons)/sizeof(creature);

bool canuse(int id,int npc,int spell)
{
	if(id!=-1)
	{
		cPlayer *player=playerStruct(id);
		for(int i=0;i<summonsize;i++)
		{
			if(player->player_template==summons[i].id)
			{
				for(int s=0;s<10;s++)
				{
					if(summons[i].useables[s]==spell)
					{
						return true;
					}
				}
				break;
			}
		}
	}
	return false;
}

int findnpc(int map,int x,int y)
{
	for(int i=0;i<playerLen();i++)
	{
		cPlayer *current=playerStruct(i);
		if(current->map==map&&current->x==x&&current->y==y)
		{
			return i;
		}
	}
	return -1;
}

int makeNext(int map,int x,int y,int id)
{
	if(getID(map,x,y)==-1)
	{
		makeNPC(id,map,x,y);
		return findnpc(map,x,y);
	}
	return -1;
}

void summon(int id,int npc,int map,int x,int y)
{
	cPlayer *self=playerStruct(id);
	char global[256];
	sprintf(global,"%s summon",self->name);
	if(!isGlobal(global))
	{
		creature summoned=summons[npc];
		int summonid=makeNext(map,x,y,summoned.id);
		if(summonid>-1&&id!=-1)
		{
			cPlayer *mob=playerStruct(summonid);

			if(mob->type==PLAYER_TYPE_NPC)
			{
				makeEffect(mob->map,mob->x,mob->y,10);
		
				mob->move_script=139;
				mob->target_at=id;
				mob->target=-1;
				setGlobalInt(global,summonid);
			}
		}
	}
	else
	{
		sendChat("^RYou cannot summon more than one monster!",id);
	}
}

void chant(int id,char incantation[])
{	
	for(int i=0;i<summonsize;i++)
	{
		if(strcmp(incantation,summons[i].chant)==0)
		{
			int map=getMap(id);
			int x=getX(id);
			int y=getY(id);
			int dir=getDir(id);
			switch(dir)
			{
				case DIR_UP:
					y--;
					break;
				case DIR_DOWN:
					y++;
					break;
				case DIR_LEFT:
					x--;
					break;
				case DIR_RIGHT:
					x++;
					break;
			}
			int tile=getTileType(map,x,y);
			if(tile==TILE_TYPE_NONE||tile==TILE_TYPE_NPC||tile==TILE_TYPE_KEEP)
				summon(id,i,map,x,y);
			break;
		}
	}
}

void npccommand(int id,int cmd)
{
	if(id!=-1)
	{
		cPlayer *player=playerStruct(id);
		char global[256];
		sprintf(global,"summoncmd %s %d",player->name,id);
		setGlobalInt(global,cmd);
	}
}

void npcattack(int id,int atk)
{
	if(id!=-1)
	{
		cPlayer *player=playerStruct(id);
		char global[256];
		sprintf(global,"summonatk %s %d",player->name,id);
		setGlobalInt(global,atk);
	}
}

void npcNoAtk(int id)
{
	if(id>-1)
	{
		cPlayer *player=playerStruct(id);
		char global[256];
		sprintf(global,"summonatk %s %d",player->name,id);
		freeGlobal(global);
	}
}
void npcNoCmd(int id)
{
	if(id>-1)
	{
		cPlayer *player=playerStruct(id);
		char global[256];
		sprintf(global,"summoncmd %s %d",player->name,id);
		freeGlobal(global);
	}
}

void unSummon(int id)
{
	if(id!=-1)
	{
		cPlayer *player=playerStruct(id);
		sendMapChatf(player->map,"%s:Oh woe is me that I must depart this world.. what a world..",player->name);
		sendMapChatf(player->map,"%s melts",player->name);
		if(player->type==PLAYER_TYPE_NPC)
		{
			int summoner=player->target_at;
			char global[256];
			if(summoner!=-1)
			{
				cPlayer *master=playerStruct(summoner);
				sprintf(global,"%s summon",master->name);
				freeGlobal(global);
			}
			npcNoAtk(id);
			npcNoCmd(id);
			player->target=id;
			player->hp=0;	
		}
	}
}

void removeSummon(int id)
{
	if(id!=-1)
	{
		cPlayer *player=playerStruct(id);
		char global[256];
		sprintf(global,"%s summon",player->name);
		freeGlobal(global);
	}
}

void assignSummon(int id,int summon)
{
	if(id!=-1&&summon!=-1)
	{
		cPlayer *master=playerStruct(id);
		cPlayer *mob=playerStruct(summon);
		mob->target_at=id;
		char global[256];
		sprintf(global,"%s summon",master->name);
		setGlobalInt(global,summon);
	}
}

int getSummon(int id)
{
	if(id!=-1)
	{
		cPlayer *master=playerStruct(id);
		char global[256];
		sprintf(global,"%s summon",master->name);
		if(isGlobal(global))
		{
			return globalInt(global);
		}
		else
		{
			return -1;
		}
	}
}

int getMaster(int id)
{
	if(id!=-1)
	{
		cPlayer *player=playerStruct(id);
		if(getSummon(player->target_at)==id)
			return player->target_at;
	}
	return -1;
}

void chargeTo(int id,int target,int len=10)
{
	while(len>0&&distance(id,target)>1)
	{
		npc_follow(id,target,true);
		makeEffect(getMap(id),getX(id),getY(id),17);
		len--;
	}
}