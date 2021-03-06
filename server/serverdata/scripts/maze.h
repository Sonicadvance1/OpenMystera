//Maze Generation functions - James Hamer 1/13/05

#include <time.h>

void fill_map(cMap *map,int map_id,int rx,int ry)
{
	int r,c;
	for(r=0;r<15;r++)
		for(c=0;c<20;c++)
			if(map->map[r][c].type == 1)
			{
				map->map[r][c].type = 3;
				map->map[r][c].warp.map = map_id;
				map->map[r][c].warp.x = rx;
				map->map[r][c].warp.y = ry;
			}
}

int tile_type(cMap *map,int x,int y)
{
	if( x < 0 || x > 19 || y < 0 || y > 14)
		return 0;
	if( map->map[y][x].type == 2 || map->map[y][x].type == 3)
		return 1;
	return 0;

}

int neighbor_count(cMap *map,int x,int y)
{
	if(map->map[y][x].type != 3)//cant eat through anything but warps
		return 0;

	int neighbors = 0;
	neighbors += tile_type(map,x+1,y);
	neighbors += tile_type(map,x-1,y);
	neighbors += tile_type(map,x,y+1);
	neighbors += tile_type(map,x,y-1);
	return neighbors;
}

void find_open(cMap *map,int x,int y)
{
	map->map[y][x].type = 1;

	if(map->map[y][x+1].type == 3)
		map->map[y][x+1].type = 1;
	else if(map->map[y+1][x].type == 3)
		map->map[y+1][x].type = 1;
	else if(map->map[y][x-1].type == 3)
		map->map[y][x-1].type = 1;
	else if(map->map[y-1][x].type == 3)
		map->map[y-1][x].type = 1;
}

void go_through(cMap *map,int x,int y,int dir,int difficulty)
{
	map->map[y][x].type = 1;
	
	if(rand()%difficulty != 0)
		dir = rand()%4;

	if(dir == 0 && neighbor_count(map,x+1,y) == 3)
		go_through(map,x+1,y,dir,difficulty);
	else if(dir == 1 && neighbor_count(map,x,y+1) == 3)
		go_through(map,x,y+1,dir,difficulty);
	else if(dir == 2 && neighbor_count(map,x-1,y) == 3)
		go_through(map,x-1,y,dir,difficulty);
	else if(dir == 3 && neighbor_count(map,x,y-1) == 3)
		go_through(map,x,y-1,dir,difficulty);

	if(neighbor_count(map,x+1,y) == 3)
		go_through(map,x+1,y,0,difficulty);
	if(neighbor_count(map,x,y+1) == 3)
		go_through(map,x,y+1,1,difficulty);
	if(neighbor_count(map,x-1,y) == 3)
		go_through(map,x-1,y,2,difficulty);
	if(neighbor_count(map,x,y-1) == 3)
		go_through(map,x,y-1,3,difficulty);
}

void make_maze(int map_id,int sx,int sy,int fx,int fy,int rmap,int rx,int ry,int difficulty)
{
	if(difficulty < 1)
		difficulty = 1;
	difficulty++;

	cMap *map = mapStruct(map_id);
	
	fill_map(map,rmap,rx,ry);	
	
	go_through(map,fx,fy,rand()%4,difficulty);

	find_open(map,sx,sy);

	mapSave(map_id);

	sendMapUpdate(map_id);

}
