#ifndef _GAMEDEFS_H_
#define _GAMEDEFS_H_

#include "Timing.h"

float client_version = 0.985f;
/*TODO

/////////////////////////FEATURES IMPLEMENTED/////////////////////////
*Items
*Combat
*inventory
*Leveling/XP
*NPC Creation
*(better)Way to shutdown server
*meta server
*equip system
*Item Creation
*magic system
*keyboard/use system
*item uses
*npc merchant
*attribute/class system
*complete scripting system
*spells! mp decrease
*windowing system:training,char creation
*game website
*player accounts and saving!
*admin invisibility
*spell timer
*newbie friendly
*client automatic patching system
*npc/item loader scripts
*chat log
*bg2 animation tiles
map caching
Client is thread safe
Action script tiles(map bit)
Keep tiles (map bit)
Inventory slots doubled
Spell targeting system(fight targeting optional)
New character gfx (body/hair/clothes selection)
Say/tell/broadcast chatting
All text(like your chats) can be colored with color codes
Animated tiles
A lot less lag
Numpad keys(for a vocal minority)
and no crash on the fill command for mappers
switch scripts
monster png blitting
Keep tiles
Bounty system
Npc chat scripts
fullscreen mode
script global variable data
Timed scripts for events
auto view on download
Npc movement scripts
//////////////////////FEATURES I AM WORKING ON/////////////////////////
download ml files
playerv compressed array msg
//////////////////////FEATURES TO BE IMPLEMENTED/////////////////////////
attribute modifier equipment
escape dialog
windowing system for:(npc)(item)
new gui skins
backup server at startup
custom bitmaps for server cfg & client notification
admin self on foreign servers
player bank system
Backup system for server
sound fx / music
walk / attack /spell timed verification
/////////////////////////BUGS ORDERED BY RARITY//////////////////////////
!client movement/mycr collision..
!?death freeze? threads?
a^wss
!when players die while moving their client registers the move overuling
	their cc warp so their map stays the same on client but cc on server
!?npcs sometimes drop items under items already on ground
////////////////////////THINKING ABOUT///////////////////////////////////
monster chasing/taming
greed spell
taunt
heal

exp bounty on death...

^w white (^W for brilliant white rather than grey and so on for other colors)
^r red
^g green
^b blue
^y yellow
^m magenta
^c cyan

names:
^w npc
^y newbie
^W average player
^b admin
^B server admin
message colors:
^M broadcast
^G tell
^W say
^c player login/logout
^C player level
^Y server msg
^R player death

*/
//RPG game definitions
unsigned long SERVER_PORT =20005;
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
#define MAX_HPBAR   128
#define MAX_INV		28
//Map
#define MAP_ROWS    15
#define MAP_COLS    20
#define CAST_MSG(x,y);    x *y;y=(x*)(data);
#define MAKE_MSG(x,_y,z);    x _y;_y.type=z;

int walk_delay=350;

//functions
int nextExp(int lvl)
{
    //return 100*pow(lvl,3);
    return int(100*(lvl*lvl));
}

float percExp(int exp,int lvl)
{
    return float(((float)exp / (100*((float)lvl*(float)lvl)))*100);
}
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
    {
        return y;
    }
    unsigned char col()
    {
        return x;
    }
    int inBounds()
    {
        if(x < MAP_COLS && y < MAP_ROWS)
            return 1;
        return 0;
    }
};

struct cEffect
{
    int id;
    char index,frame;
    pos p;
    cEffect()
    {
        index=0;
        frame=-1;
        id=-1;
    }
    int advance()
    {
        frame++;
        if(frame>7)
        {
            frame=0;
            return 1;
        }
        return 0;
    }
};

struct cHPbar
{
    int id;
    unsigned char hp;
    unsigned short map,index;
    cTimer t;
    cHPbar()
    {
    }
    void init(signed short _map,unsigned short _index,unsigned char _hp)
    {
        map=_map;
        index=_index;
        hp=_hp;
    }
    int advance(int len)
    {
        if(t.tick(len))
            return 1;
        return 0;
    }
};

struct cItemRef
{
    unsigned short index;
    unsigned char life;
    signed long qty;
    unsigned short graphic;
    char name[20];
    pos p;
    cItemRef()
    {
        index=0;
        qty=0;
        life=10;
    }
};

struct cItem
{
    char name[20],desc[45];
    unsigned short graphic;
    unsigned char type,option;
    char uses;
    int value;
    signed short script;
    signed short atk;
    signed short def;
    float oz;
    cItem()
    {
        atk=0;
        def=0;
        script=-1;
        strcpy(name,"_EMPTY_");
        type=IT_EMPTY;
        option=SINGLE;
        strcpy(desc,"");
        graphic=0;
        uses=-1;
    }
    void init(char *_name,char *_desc,unsigned char _graphic,unsigned char _type,unsigned char _option,unsigned char _value,float _oz,char _uses,signed short _atk,signed short _def)
    {
        graphic=_graphic;
        type=_type;
        option=_option;
        value=_value;
        oz=_oz;
        uses=_uses;
        strcpy(name,_name);
        strcpy(desc,_desc);
        atk=_atk;
        def=_def;
    }
};

struct cSkill
{
    char name[16];
    int itemType;
};

struct cBasePlayer
{
    pos p;
    unsigned char dir;
    cBasePlayer()
    {
        p.x=0;
        p.y=0;
        p.map=0;
        dir=0;
    }
};

struct cPlayer : public cBasePlayer
{
    unsigned char frm,rank,type,time,age,state,range,index,str,dex,con,itl,wis;
    signed char access,eLeft,eRight,eHead,eBody,eSpecial,affect;
    unsigned short lvl,worth,atk,def,train;
    unsigned int fire,ice,elec,magic,physical,poison,guildID,guildrank,PKs,kills,deaths;
    signed short sprite,body,hair,clothes,target,target_at,chat_script,move_script;
    signed long hp,mhp,mp,mmp,dpnid;
    unsigned long exp;
    pos origin;
    signed short data[32];
    char name[20];
    char guild[64];
    char privProfile[4];
    cItemRef item[84];
    cTimer walk;
    int delay,path;
    cPlayer()
    {
        delay=walk_delay;
        path=0;
        walk.reset();
        sprite=0;
        target_at=-1;
        chat_script=-1;
        move_script=-1;
        affect=-1;
        body=0;
        hair=0;
        clothes=0;
        str=1;
        dex=1;
        con=1;
        itl=1;
        wis=1;
        train=0;
        eLeft=-1;
        eRight=-1;
        eHead=-1;
        eBody=-1;
        eSpecial=-1;
        index=0;//FIXME:Unsigned but was defaulted to -1
        atk=1;
        def=1;
        worth=0;
        origin.map=0;
        origin.x=5;
        origin.y=5;
        strcpy(name,"_EMPTY_");
        lvl=1;
        hp=100;
        mhp=100;
        mp=80;
        mmp=80;
        exp=0;
        dir=0;
        dpnid=0;
        sprite=1;
        p.map=0;
        access=-1;
        target=-1;
        p.x=5;
        p.y=5;
        type=PLAYER;
        state=PASSIVE;
        range=5;
        fire=0;
        ice=0;
        elec=0;
        magic=0;
        poison=0;
        physical=0;
        strcpy(privProfile,"No");
        guildID=0;
        guildrank=0;
        PKs=0;
        kills=0;
        deaths=0;
    }
    void initLoot(int i1,int q1,int i2,int q2,int i3,int q3,int i4,int q4,int i5,int q5)
    {
        item[0].index=i1;
        item[0].qty  =q1;
        item[1].index=i2;
        item[1].qty  =q2;
        item[2].index=i3;
        item[2].qty  =q3;
        item[3].index=i4;
        item[3].qty  =q4;
        item[4].index=i5;
        item[4].qty  =q5;
    }
    int full(unsigned short index)
    {
        int i=0;
        while(i<MAX_INV)
        {
            if(item[i].qty==0)
                return 0;
            if(index==item[i].index && item[i].qty>0)
                return 0;
            i++;
        }
        return 1;
    }
    int addItem(signed long qty,unsigned short index)
    {
        int i=0;
        if(qty>0)//check for stacking on existing type
        {
            while(i<MAX_INV)
            {
                if(index==item[i].index && item[i].qty!=0)
                {
                    item[i].index=index;
                    item[i].qty+=qty;
                    return i;
                }
                i++;
            }
        }
        i=0;
        while(i<MAX_INV)//check for emtpy slot
        {
            if(item[i].qty==0)
            {
                item[i].qty=qty;
                item[i].index=index;
                return i;
            }
            i++;
        }
        return -1;
    }
    void setCore(cBasePlayer core)
    {
        p=core.p;
        dir=core.dir;
    }
    cBasePlayer getCore()
    {
        cBasePlayer core;
        core.p=p;
        core.dir=dir;
        return core;
    }
    pos front()
    {
        pos temp=p;
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
        pos temp=p;
        temp.y--;
        return temp;
    }
    pos down()
    {
        pos temp=p;
        temp.y++;
        return temp;
    }
    pos left()
    {
        pos temp=p;
        temp.x--;
        return temp;
    }
    pos right()
    {
        pos temp=p;
        temp.x++;
        return temp;
    }
    void move(int _dir)
    {
        dir=_dir;
        if(dir==3)
            p.x++;
        else if(dir==2)
            p.x--;
        else if(dir==1)
            p.y--;
        else if(dir==0)
            p.y++;
        frm+=1;
        if(frm>1)
            frm=0;
    }
    /*int addItem(unsigned char ind,unsigned char qty)
    {
    	if(ind==0)
    		return 0;
    	int c=0;
    	while(item[c].index!=0)
    	{
    		c++;
    		if(c==14)
    			return 0;
    	}
    	item[c].index=ind;
    	item[c].qty=qty;
    	return 1;
    }*/
    int hasItem(int index)
    {
        for(int c=0; c<MAX_INV; c++)
            if(item[c].index==index)
                return c;
        return -1;
    }
    cItemRef getItem()
    {
        int c=13;
        while(item[c].index==0)
        {
            c--;
            if(c<0)
                return item[0];
        }
        return item[c];
    }
    cItemRef getItem(int index,bool pop=true)
    {
        cItemRef temp=item[index];
        if(pop)
            item[index].index=0;
        return temp;
    }
    bool full()
    {
        for(int c=0; c<MAX_INV; c++)
            if(item[c].index==0)
                return false;
        return true;
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
        version=255;
        strcpy(name,"_EMPTY_");
        n=0;
        e=0;
        s=0;
        w=0;
        int r,c;
        for(r=0; r<MAP_ROWS; r++)
        {
            for(c=0; c<MAP_COLS; c++)
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
        for(r=0; r<MAP_ROWS; r++)
        {
            for(c=0; c<MAP_COLS; c++)
            {
                map[r][c].space=VACANT;
            }
        }
    }
    cBasePlayer getPos(cBasePlayer p)
    {
        if(p.p.x==MAP_COLS)
        {
            p.p.x=0;
            p.p.map=e;
        }
        if(p.p.y==MAP_ROWS)
        {
            p.p.y=0;
            p.p.map=s;
        }
        if(p.p.x==255)
        {
            p.p.x=MAP_COLS-1;
            p.p.map=w;
        }
        if(p.p.y==255)
        {
            p.p.y=MAP_ROWS-1;
            p.p.map=n;
        }
        return p;
    }
};

struct cAccount
{
    cPlayer player;
    char ip[16];
    int state;
    int amt;
    int x,y,z;
    char cdate[64];
    char ldate[64];
    char tdate[64];
    char email[64];
    char realn[64];
    char pass[16];
    char sex;
};

struct cTrade
{
    char name[32];
    signed short graphic;
    signed short item_template;
    signed long qty;
    unsigned short count;
    signed short merchID;
    signed short npcType;
    bool isMerch;
    cTrade()
    {
        strcpy(name,"EMPTY");
        graphic = -1;
        item_template = -1;
        qty = -1;
        count = 0;
        merchID = -1;
        npcType = -1;
        isMerch = false;
    }
};
#endif
