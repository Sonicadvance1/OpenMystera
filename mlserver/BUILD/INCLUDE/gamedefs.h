#ifndef _MLGAMEDEFS_
#define _MLGAMEDEFS_

#include "utils.h"
#include "list.h"
#include "script_system.h"
#include "net.h"

//RPG game definitions

//Graphical
#define BSIZE     32
//Item Type
#define IT_EMPTY     0
#define IT_HAND      1
#define IT_ITEM      2
#define IT_CURRENCY  3
#define IT_ARMOR     4
#define IT_HELMET    5
#define IT_2HAND     6
#define IT_SPECIAL   7
//Item Option
#define	SINGLE    0
#define STACKABLE 1
#define PERMANENT 2
//player type
#define PLAYER    0
#define NPC       1
//NPC states
#define PASSIVE   0
#define ATTACK    1
#define STANDING  2
#define MERCHANT  3
//Tile space
#define VACANT    -1
//Tile type
#define OPEN      1
#define WALL      2
#define WARP      3
#define XNPC      4
#define SCPT      5
#define SWCH      6
#define KEEP      7
//Game
#define MAX_EFFECTS 128
#define MAX_HPBAR   256
#define MAX_INV		28

//Map
#define MAP_ROWS    15
#define MAP_COLS    20
#define CAST_MSG(x,y);    x *y;y=(x*)(data);

//Structures
struct pos
{
	unsigned char x,y;
	signed short map;
	pos()
	{}
	pos(unsigned char r,unsigned char c)
	{
		x=c;
		y=r;
	}
	void randomize()
	{
		x=rand()%MAP_COLS;
		y=rand()%MAP_ROWS;
	}
	int operator ==(const pos& p)
	{
		if(x==p.x&&y==p.y&&map==p.map)
			return 1;
		return 0;
	}
	unsigned char row()
	{return y;}
	unsigned char col()
	{return x;}
	int inBounds()
	{
		if(x < MAP_COLS && y < MAP_ROWS)
			return 1;
		return 0;
	}
};

struct cItem
{
	signed long		id;
	unsigned char	life;
	signed long		qty;
	unsigned short	graphic;
	char			name[32];
	signed short	map;
	unsigned char	x;
	unsigned char	y;
	signed short	owner;
	signed short	slot;
	unsigned char	type;
	unsigned char	stack;
	unsigned int	flags;
	signed char		uses;
	signed short	use_script;
	signed short	equip_script;
	signed short	unequip_script;
	signed short	pickup_script;
	signed short	drop_script;
	signed short	lose_script;
	signed short	atk;
	signed short	def;
	signed short	item_template;
	signed short	bonus;
	signed short	bonus2;
	signed short	userdata;
	signed short	userdata2;
	timer           cooldown;
	unsigned short  total_cooldown;
	float           weight;

	/*
	signed char		pierce_atk;
	signed char		slash_atk;
	signed char		bash_atk;
	signed char		holy_atk;
	signed char		dark_atk;
	signed char		fire_atk;
	signed char		ice_atk;
	signed char		shock_atk;
	signed char		pierce_def;
	signed char		slash_def;
	signed char		bash_def;
	signed char		holy_def;
	signed char		dark_def;
	signed char		fire_def;
	signed char		ice_def;
	signed char		shock_def;
	*/

	cItem()
	{
		id=-1;
		life=10;
		qty=0;
		graphic=0;
		strcpy(name,"_EMPTY_");
		map=-1;
		x=0;
		y=0;
		owner=-1;
		slot=-1;
		type=0;
		stack=0;
		flags=0;
		uses=-1;
		use_script=-1;
		equip_script=-1;
		unequip_script=-1;
		pickup_script=-1;
		drop_script=-1;
		lose_script=-1;
		atk=0;
		def=0;
		item_template=-1;
		bonus=0;
		bonus2=0;
		userdata=0;
		userdata2=0;
		total_cooldown = 750;
		cooldown.go();
		weight = 1;
	}
};

struct cItemList
{
	cList <cItem> item;
	int inventoryMax;
	cItemList()
	{
		inventoryMax=28;
	}
	int addItem(cItem &theItem)
	{
		int i=0;
		if(i==item.size())
			item.size((item.size()+1)*2);
		while(item[i].qty!=0)
		{
			i++;
			if(i==item.size())
				item.size((item.size()+1)*2);
		}
		item[i]=theItem;
		return i;
	}
	int addMapItem(int map,int x,int y,cItem &theItem)
	{
		theItem.owner=-1;
		theItem.map=map;
		theItem.x=x;
		theItem.y=y;
		return addItem(theItem);
	}
	int addInventoryItem(int id,int slot,cItem &theItem)
	{
		theItem.map=-1;
		theItem.owner=id;
		theItem.slot=slot;
		return addItem(theItem);
	}
};

struct npcItemTemplate
{
	int index,qty,chance;
	npcItemTemplate()
	{
		chance=200;
		index=0;
		qty=0;
	}
};

struct npcLoot
{
	npcItemTemplate loot[MAX_INV];
	void reset()
	{
		for(int i=0;i<MAX_INV;i++)
			loot[i].qty=0;
	}
	void addLoot(int index,int qty,int chance)
	{
		for(int i=0;i<MAX_INV;i++)
			if(loot[i].qty==0)
			{
				loot[i].index=index;
				loot[i].qty=qty;
				loot[i].chance=chance;
				break;
			}
	}
};

struct serverLoot
{
	cList <npcLoot> loot;
	void addLoot(int npc,int index,int qty,int chance)
	{
		if(npc>=loot.size())
			loot.size(npc+1);
		loot[npc].addLoot(index,qty,chance);
	}
};

struct cPlayer
{
	signed long		id;
	unsigned char	x;
	unsigned char	y;
	signed short	map;
	unsigned char	dir;
	unsigned char	type;
	unsigned char	state;
	unsigned char	range;
	unsigned char	str;
	unsigned char	dex;
	unsigned char	con;
	unsigned char	itl;
	unsigned char	wis;
	signed char		access;
	signed char		eLeft;
	signed char		eRight;
	signed char		eHead;
	signed char		eBody;
	signed char		eSpecial;
	unsigned short	lvl;
	signed short	player_template;
	signed short	sprite;
	signed short	body;
	signed short	hair;
	signed short	clothes;
	signed long		worth;
	signed short	atk;
	signed short	def;
	unsigned short	train;
	signed long		hp;
	signed long		mhp;
	signed long		mp;
	signed long		mmp;
	signed short	target;
	signed short	target_at;
	signed short	chat_script;
	signed short	move_script;
	signed long		exp;
	unsigned long	flags;
	unsigned char	origin_x;
	unsigned char	origin_y;
	signed	short	origin_map;
	char			name[32];
	char			title[64];
	char			create_date[64];
	char			login_date[64];
	char			logout_date[64];
	unsigned long	total_time;
	unsigned long	boot_time;
	unsigned long	serenity;
	unsigned long	unknown;

	//not stored
	char ip[16];
	int time_safe;
	int stationary;
	int premium;
	char accid[7];
	PlayerID pid;
	int inventory[MAX_INV];
	int current_map;
	timer mstl;
	timer move_timer;
	unsigned long packet_time;
	signed char npacket;
	char ignore[32];

	cPlayer()
	{
		id=-1;
		x=5;
		y=5;
		map=0;
		dir=0;
		type=0;
		state=0;
		range=5;
		str=1;
		dex=1;
		con=1;
		itl=1;
		wis=1;
		access=-1;
		eLeft=-1;
		eRight=-1;
		eHead=-1;
		eBody=-1;
		eSpecial=-1;
		lvl=1;
		player_template=-1;
		sprite=0;
		body=0;
		hair=0;
		clothes=0;
		worth=0;
		atk=1;
		def=1;
		train=0;
		hp=100;
		mhp=100;
		mp=80;
		mmp=80;
		target=-1;
		target_at=-1;
		chat_script=-1;
		move_script=-1;
		exp=0;
		flags=0;
		origin_x=5;
		origin_y=5;
		origin_map=0;
		strcpy(name,"_EMPTY_");
		strcpy(title,"the weak.");
		serenity=216000;
		unknown=0;
		boot_time=0;
		total_time=0;
		time_safe=120;
		stationary=0;
		mstl.reset();
		move_timer.reset();
		current_map=-1;
		premium=0;
		packet_time=SDL_GetTicks();
		npacket=0;
		pid=1000000;
		strcpy(accid,"");
		strcpy(ip,"");
		strcpy(ignore,"");
		for(int i=0;i<MAX_INV;i++)
			inventory[i]=-1;
		mstl.go();
		move_timer.go();
	}
	void randomize()
	{
		x=rand()%MAP_COLS;
		y=rand()%MAP_ROWS;
	}
	pos front()
	{
		pos temp;
		temp.x=x;
		temp.y=y;
		temp.map=map;
		if(dir==0)//down
			temp.y++;
		else if(dir==1)//up
			temp.y--;
		else if(dir==2)//left
			temp.x--;
		else if(dir==3)//right
			temp.x++;
		return temp;
	}
	pos up()
	{
		pos temp;
		temp.x=x;
		temp.y=y;
		temp.map=map;
		temp.y--;
		return temp;
	}
	pos down()
	{
		pos temp;
		temp.x=x;
		temp.y=y;
		temp.map=map;
		temp.y++;
		return temp;
	}
	pos left()
	{
		pos temp;
		temp.x=x;
		temp.y=y;
		temp.map=map;
		temp.x--;
		return temp;
	}
	pos right()
	{
		pos temp;
		temp.x=x;
		temp.y=y;
		temp.map=map;
		temp.x++;
		return temp;
	}
	void move(int _dir)
	{
		dir=_dir;
		if(dir==3)
			x++;
		else if(dir==2)
			x--;
		else if(dir==1)
			y--;
		else if(dir==0)
			y++;
	}
};

struct cTile
{
	unsigned short tile[4];
	unsigned char type;
	pos warp;
	signed short space;
	cTile()
	{
		warp.map=-1;
		tile[0]=0;
		tile[1]=0;
		tile[2]=0;
		tile[3]=0;
		type=OPEN;
		space=VACANT;
	}
};

struct cNPCRef
{
	int index,qty;
	cNPCRef()
	{
		index=-1;
		qty=1;
	}
};

struct cMap
{
	cTile map[MAP_ROWS][MAP_COLS];
	char name[32];
	int n,e,s,w;
	unsigned char version;
	cNPCRef npc[5];
	cMap()
	{
		version=0;
		strcpy(name,"_EMPTY_");
		n=0;e=0;s=0;w=0;
		int r,c;
		for(r=0;r<MAP_ROWS;r++)
		{
			for(c=0;c<MAP_COLS;c++)
			{
				if(rand()%30==0)
					map[r][c].tile[1]=23;//rocks
				if(rand()%5==0)
					map[r][c].tile[0]=21;//set all to grass
				else
					map[r][c].tile[0]=36;//set all to grass
			}
		}
	}
	bool canMove(pos p,unsigned char npc=0)
	{
		if(p.row()==255||p.row()==MAP_ROWS||p.col()==255||p.col()==MAP_COLS)
		{
			if(npc)
				return false;
			return true;
		}
		if(npc && (map[p.row()][p.col()].type == XNPC || map[p.row()][p.col()].type == WARP))
			return false;
		if(map[p.row()][p.col()].space==VACANT && map[p.row()][p.col()].type!=WALL && map[p.row()][p.col()].type!=SWCH)
			return true;
		return false;
	}
	void setAllVacant()
	{
		int r,c;
		for(r=0;r<MAP_ROWS;r++)
		{
			for(c=0;c<MAP_COLS;c++)
			{
				map[r][c].space=VACANT;
			}
		}
	}
};

struct cEvent
{
	timer t;
	long s;
	int script;
	int id; 
	cEvent()
	{
		script=-1;
	}
	void set(int _script,int _id,int _s)
	{
		t.reset();
		script=_script;
		id=_id;
		s=_s;
	}
	int check(cScriptSystem *mlscript)
	{
		if(script==-1)
			return -1;
		if(t.tick(s))
		{
			mlscript->run(script,id);
			return 1;
		}
		return 0;
	}
};

struct cEventHandler
{
	cList <cEvent> e;
	int add(int _script,int _id,int _s)
	{
		int i=0;
		while(1)
		{
			if(e.size()<=i)
				e.size(i+1);
			if(e[i].script==-1)
			{
				e[i].set(_script,_id,_s);
				return i;
			}
			i++;
		}
		return -1;
	}
	void halt(int id)
	{
		if(id<e.size()&&id>=0)
			e[id].script=-1;
	}
	int handle(cScriptSystem *mlscript)
	{
		int n=0;
		for(int i=0;i<e.size();i++)
			if(e[i].check(mlscript)==1)
			{
				e[i].script=-1;
				n++;
			}
		return n;
	}
};

struct cScriptGlobal
{
	signed char type;//0 int, 1 string
	char name[128];
	char str[512];//data
	int num;
	cScriptGlobal()
	{
		free();
	}
	void setName(char *s)
	{
		strcpy(name,s);
	}
	int isName(char *s)
	{
		if(!s || strcmp(name,s) != 0)
			return 0;
		return 1;
	}
	void setString(char *s)
	{
		strcpy(str,s);
		type=1;
	}
	void setInt(int n)
	{
		num=n;
		type=0;
	}
	void free()
	{
		strcpy(name,"");
		strcpy(str,"");
		num=0;
		type=-1;
	}
};

struct cGlobalHandler
{
	cList <cScriptGlobal> g;
	void addInt(char *name,int num)
	{
		int i=0;
		while(1)
		{
			if(g.size()<=i)
				g.size(i+1);
			if(g[i].type==-1)
			{
				g[i].setName(name);
				g[i].setInt(num);
				break;
			}
			i++;
		}
	}
	void addString(char *name,char *str)
	{
		int i=0;
		while(1)
		{
			if(g.size()<=i)
				g.size(i+1);
			if(g[i].type==-1)
			{
				g[i].setName(name);
				g[i].setString(str);
				break;
			}
			i++;
		}
	}
	void setInt(char *name,int num)
	{
		int i=0;
		while(i<g.size())
		{
			if(g[i].isName(name))
			{
				g[i].setInt(num);
				return;
			}
			i++;
		}
		addInt(name,num);
	}
	void setString(char *name,char *str)
	{
		int i=0;
		while(i<g.size())
		{
			if(g[i].isName(name))
			{
				g[i].setString(str);
				return;
			}
			i++;
		}
		addString(name,str);
	}
	int getInt(char *name)
	{
		int i=0;
		while(i<g.size())
		{
			if(g[i].isName(name))
				return g[i].num;
			i++;
		}
		return 0;
	}
	char *getString(char *name)
	{
		int i=0;
		while(i<g.size())
		{
			if(g[i].isName(name))
				return g[i].str;
			i++;
		}
		return "";
	}
	int isGlobal(char *name)
	{
		int i=0;
		while(i<g.size())
		{
			if(g[i].type>-1 && g[i].isName(name))
				return 1;
			i++;
		}
		return 0;
	}
	void free(char *name)
	{
		int i=0;
		while(i<g.size())
		{
			if(g[i].isName(name))
			{
				g[i].free();
				break;
			}
			i++;
		}
	}
}; 

#endif
