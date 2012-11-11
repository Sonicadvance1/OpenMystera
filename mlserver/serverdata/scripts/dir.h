void dirapply(int &x,int &y,int dir,bool reverse=false)
{
	switch(dir)
	{
		case DIR_DOWN:
			if(!reverse)
				y++;
			else
				y--;
			break;
		case DIR_UP:
			if(!reverse)
				y--;
			else
				y++;
			break;
		case DIR_LEFT:
			if(!reverse)
				x--;
			else
				x++;
			break;
		case DIR_RIGHT:
			if(!reverse)
				x++;
			else
				x--;
			break;
	}
}
int opposite(int dir)
{
	switch(dir)
	{
		case DIR_DOWN:
			return DIR_UP;
		case DIR_UP:
			return DIR_DOWN;
		case DIR_LEFT:
			return DIR_RIGHT;
		case DIR_RIGHT:
			return DIR_LEFT;
	}
}
int arrow(int dir)
{
	return 5+dir;
}
int fire(int dir)
{
	switch(dir)
	{
		case DIR_DOWN:
			return 21;
		case DIR_UP:
			return 23;
		case DIR_LEFT:
			return 22;
		case DIR_RIGHT:
			return 20;
	}
	return -1;
}
bool pass(int tile)
{
	return (tile==TILE_TYPE_NONE||tile==TILE_TYPE_NPC||tile==TILE_TYPE_SCRIPT||tile==TILE_TYPE_KEEP);
}