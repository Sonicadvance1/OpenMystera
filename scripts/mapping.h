const int GRASS_TILE=36;
const int GRASS_TILE2=21;
const int WATER_TILE=247;
const int DIRT_TILE=22;
const int WATER_BORDER=7;
const int SHADOW_TILE=20;
const int WATER_ANIM=325;
const int WATER_ANIM2=326;
const int BEACH_TILE=209;
const int BEACH_TILE2=161;
const int BEACH_BORDER=5;
const int BEACH_RIGHT=247;
const int BEACH_LEFT=948;
const int BEACH_DOWN=946;
const int BEACH_UP=947;
const int GRASSEND_UP=862;
const int GRASSEND_DOWN=846;
const int GRASSEND_LEFT=861;
const int GRASSEND_RIGHT=860;
const int GRASS_LEFT=924;
const int GRASS_RIGHT=925;
const int GRASS_UP=703;
const int GRASS_DOWN=687;
const int GRASSCORNER_UR=671;
const int GRASSCORNER_UL=655;
const int GRASSCORNER_DR=639;
const int GRASSCORNER_DL=623;
const int GRASSNARROW_LR=542;
const int GRASSNARROW_UD=543;
const int GRASSSINGLE_TILE=719;
const int ROCK_TILE=23;
const int SMALL_PLANT=444;
const int SMALL_TREE=300;
const int LARGETREE_BR=333;
const int LARGETREE_BL=332;
const int LARGETREE_TR=317;
const int LARGETREE_TL=316;
const int STAIR_UP=318;
const int STAIR_DOWN=334;
const int DUG_DIRT=32;
const int LARGE_ROCK=261;

#define STARTMAP 1600
#define NUMMAPS 35
#define TOTALMAPS NUMMAPS * NUMMAPS
#define ENDMAP (STARTMAP +  (TOTALMAPS * 2))
#define UNDERSTART (ENDMAP - (TOTALMAPS))
#define TREESCRIPT 536
#define ROCKSCRIPT 537
#define STAIRSCRIPT 540
#define WATERSCRIPT -1


void savemap(int map)
{
	mapSave(map); 
	mapCompleteSave(map); 
	updateMap(map); 
	sendMapUpdate(map);
}
bool tilearound(cMap *map,int x,int y,int tile)
{
	if(map->map[y+1][x].tile[0]==tile||map->map[y-1][x].tile[0]==tile||map->map[y][x+1].tile[0]==tile||map->map[y][x-1].tile[0]==tile)
		return 1;
	return 0;
}
bool maketree(cMap *map,int x,int y)
{
	//cMap *map=mapStruct(mapid);
	if(x<18&&x>1&&y<14&&y>0&&(map->map[y][x].tile[0]==GRASS_TILE||map->map[y][x].tile[0]==GRASS_TILE2) && (map->map[y][x+1].tile[0]==GRASS_TILE || map->map[y][x+1].tile[0]==GRASS_TILE2)
	&&	map->map[y][x].tile[1]==0 && map->map[y][x+1].tile[1]==0 && map->map[y][x].type==TILE_TYPE_NONE && map->map[y][x+1].type==TILE_TYPE_NONE)
	{
		map->map[y][x].tile[1]=LARGETREE_BL;
		map->map[y][x].type=TILE_TYPE_SWITCH;
		map->map[y][x].warp.map=TREESCRIPT;
		map->map[y][x+1].tile[1]=LARGETREE_BR;
		map->map[y][x+1].type=TILE_TYPE_SWITCH;
		map->map[y][x+1].warp.map=TREESCRIPT;
		map->map[y-1][x].tile[3]=LARGETREE_TL;
		map->map[y-1][x+1].tile[3]=LARGETREE_TR;
	}
	else
		return 0;
}

void clear(int mapid)
{
	cMap *map=mapStruct(mapid);
	for(int x=0;x<20;x++)
	{
		for(int y=0;y<15;y++)
		{
			for(int l=0;l<4;l++)
			{
				map->map[y][x].tile[l]=0;
				map->map[y][x].type=0;
			}
		}
	}
	strcpy(map->name,"_EMPTY_");
	map->n=map->s=map->w=map->e=0;
	for(int i=0;i<5;i++)
	{
		map->npc[i].index=-1;
		map->npc[i].qty=1;
	}
}
void makewateranim(cMap *map,int x,int y)
{
	if(map->map[y][x].tile[0]==WATER_TILE&&map->map[y][x].tile[1]==0)
		map->map[y][x].tile[2]=WATER_ANIM2;
	if(y>0 && map->map[y-1][x].tile[0]==WATER_TILE && map->map[y-1][x].tile[1]==0)
		map->map[y-1][x].tile[2]=WATER_ANIM;
	if(y<14&& map->map[y+1][x].tile[0]==WATER_TILE&& map->map[y+1][x].tile[1]==0)
		map->map[y+1][x].tile[2]=WATER_ANIM;
	if(x>0&& map->map[y][x-1].tile[0]==WATER_TILE&& map->map[y][x-1].tile[1]==0)
		map->map[y][x-1].tile[2]=WATER_ANIM;
	if(x<19&& map->map[y][x+1].tile[0]==WATER_TILE&& map->map[y][x+1].tile[1]==0)
		map->map[y][x+1].tile[2]=WATER_ANIM;	
}
int watersmooth(int mapid,int x,int y)
{
	cMap *map=mapStruct(mapid);
	int recommend=0;
	int numtiles=0;
	int uptile=0;
	int downtile=0;
	int lefttile=0;
	int righttile=0;
	if(map->map[y][x].tile[0]!=WATER_TILE)
		return 0;
	if(inBounds(x+1,y))
	{
		if(map->map[y][x+1].tile[0]==WATER_TILE)
		{
			numtiles++;
			righttile=1;
		}
	}
	else
	{
		numtiles++;
		righttile=1;
	}
	if(inBounds(x,y+1))
	{
		if(map->map[y+1][x].tile[0]==WATER_TILE||!inBounds(x,y+1))
		{
			numtiles++;
			downtile=1;
		}
	}
	else
	{
		numtiles++;
		downtile=1;
	}
	if(inBounds(x-1,y))
	{
		if(map->map[y][x-1].tile[0]==WATER_TILE||!inBounds(x-1,y))
		{
			numtiles++;
			lefttile=1;
		}
	}
	else
	{
		numtiles++;
		lefttile=1;
	}
	if(inBounds(x,y-1))
	{
		if(map->map[y-1][x].tile[0]==WATER_TILE||!inBounds(x,y-1))
		{
			uptile=1;
			numtiles++;
		}
	}
	else
	{
		uptile=1;
		numtiles++;
	}
	if(numtiles==0)
	{
		recommend=GRASSSINGLE_TILE;
	}
	else if(numtiles==1)
	{
		if(righttile)
			recommend=GRASSEND_LEFT;
		else if(lefttile)
			recommend=GRASSEND_RIGHT;
		else if(uptile)
			recommend=GRASSEND_DOWN;
		else if(downtile)
			recommend=GRASSEND_UP;
	}
	else if(numtiles==2)
	{
		if(righttile&&lefttile)
			recommend=GRASSNARROW_LR;
		else if(uptile&&downtile)
			recommend=GRASSNARROW_UD;
		else if(uptile&&righttile)
			recommend=GRASSCORNER_DL;
		else if(uptile&&lefttile)
			recommend=GRASSCORNER_DR;
		else if(downtile&&lefttile)
			recommend=GRASSCORNER_UR;
		else if(downtile&&righttile)
			recommend=GRASSCORNER_UL;
	}
	else if(numtiles==3)
	{
		if(uptile&&downtile&&righttile)
			recommend=GRASS_LEFT;
		else if(uptile&&downtile&&lefttile)
			recommend=GRASS_RIGHT;
		else if(lefttile&&righttile&&downtile)
			recommend=GRASS_UP;
		else if(lefttile&&righttile&&uptile)
			recommend=GRASS_DOWN;
	}
	else if(numtiles==4)
	{
		recommend=-1;
	}
	
	return recommend;
}
void smootharound(int mapid,cMap *map,int x,int y)
{
	for(int x1=x-1;x1<=x+1;x1++)
	{
		for(int y1=y-1;y1<=y+1;y1++)
		{
			if(inBounds(x1,y1))
			{
				if(map->map[y1][x1].tile[0]==WATER_TILE)
				{
					map->map[y1][x1].tile[1]=0;
					map->map[y1][x1].tile[2]=0;
				}
				int smoothtile=watersmooth(mapid,x1,y1);
				if(smoothtile>0)
				{
					map->map[y1][x1].tile[1]=smoothtile;
				}
			}
		}
	}
}
void extendtonext(cMap *map,int x,int y,int tile,int tile_type,int tile_replace)
{
	cMap *latmap;
	int latmapid;
	int latx=-1;
	cMap *longmap;
	int longmapid;
	int laty=-1;
	if(x==0)
	{
		latmap=mapStruct(map->w);
		latmapid=map->w;
		latx=19;
	}
	else if(x==19)
	{
		latmap=mapStruct(map->e);
		latmapid=map->e;
		latx=0;
	}
	if(y==0)
	{
		longmap=mapStruct(map->n);
		longmapid=map->n;
		laty=14;
	}
	else if(y==14)
	{
		longmap=mapStruct(map->s);
		longmapid=map->s;
		laty=0;
	}
	if(laty!=-1)
	{
		if(longmap->map[laty][x].type==tile_replace)
		{
			longmap->map[laty][x].type=tile_type;
			longmap->map[laty][x].tile[0]=tile;
			smootharound(longmapid,longmap,x,laty);
			savemap(longmapid);
		}
	}
	if(latx!=-1)
	{
		if(latmap->map[y][latx].type==tile_replace)
		{
			latmap->map[y][latx].type=tile_type;
			latmap->map[y][latx].tile[0]=tile;
			smootharound(latmapid,latmap,latx,y);
			savemap(latmapid);
		}
	}
}
void makelaketile(int mapid,int x,int y,int size)
{
	cMap *map=mapStruct(mapid);
	map->map[y][x].tile[0]=WATER_TILE;
	map->map[y][x].type=TILE_TYPE_SWITCH;
	map->map[y][x].warp.map=WATERSCRIPT;
	int randgen=getRand(4)+1;
	if(randgen>0)
	{
		for(int i=0;i<randgen;i++)
		{
			int randir=getRand(4);
			if(randir==DIR_UP)
				y++;
			else if(randir==DIR_DOWN)
				y--;
			else if(randir==DIR_LEFT)
				x--;
			else if(randir==DIR_RIGHT)
				x++;
			if(x<19&&x>0&&y<14&&y>0&&size>0&&map->map[y][x].tile[1]==0)
				makelaketile(mapid,x,y,size-1);
		}
	}
}
void makelake(int mapid,int size)
{
	cMap *map=mapStruct(mapid);
	int randx;
	int randy;
	while(randx>15||randx<6)
		randx=getRand(19);
	while(randy>10||randy<6)
		randy=getRand(14);
	makelaketile(mapid,randx,randy,size);
}
void prettymap(int mapid)
{
	cMap *map=mapStruct(mapid);
	for(int x=0;x<20;x++)
	{
		for(int y=0;y<15;y++)
		{
			if(map->map[y][x].tile[0]==WATER_TILE)
			{
				int smoothtile=watersmooth(mapid,x,y);
				if(smoothtile>0)
				{
					map->map[y][x].tile[1]=smoothtile;
					map->map[y][x].tile[2]=0;
				}
				else if(smoothtile==-1)
				{
					if(getRand(5)==1)
					{
						makewateranim(map,x,y);
					}
					else if(getRand(20)==1)
					{
						if(map->map[y][x].tile[2]==0)
							map->map[y][x].tile[1]=SMALL_PLANT;
					}
				}
			}
			else if(map->map[y][x].tile[0]==GRASS_TILE)
			{
				if(getRand(3)==1)
					map->map[y][x].tile[0]=GRASS_TILE2;
					
				if(getRand(100)==1)
				{
					map->map[y][x].tile[1]=ROCK_TILE;
					map->map[y][x].type=TILE_TYPE_SWITCH;
					map->map[y][x].warp.map=ROCKSCRIPT;
				}
				else if(getRand(100)==1 && y<14 && x<19 && x>0 && y>0)
				{
					map->map[y][x].tile[1]=SMALL_TREE;
					map->map[y][x].type=TILE_TYPE_SWITCH;
					map->map[y][x].warp.map=TREESCRIPT;
				}
				else if(getRand(150)==1)
				{
					maketree(map,x,y);
				}
			}
			else if(map->map[y][x].tile[0]==DIRT_TILE)
			{
				if(getRand(200)==1 && y<14 && x<19 && x>0 && y>0)
				{
					map->map[y][x].tile[1]=LARGE_ROCK;
					map->map[y][x].type=TILE_TYPE_SWITCH;
					map->map[y][x].warp.map=ROCKSCRIPT;
				}
				else if(getRand(100)==1 && y<14 && x<19 && x>0 && y>0)
				{
					map->map[y][x].tile[1]=ROCK_TILE;
					map->map[y][x].type=TILE_TYPE_SWITCH;
					map->map[y][x].warp.map=TREESCRIPT;
				}
			}
		}
	}
}