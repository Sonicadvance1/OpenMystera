#ifndef _CGLOBALS_H_
#define _CGLOBALS_H_

#include "glfuncs.h"
#include "Timing.h"

//DEFINES
#define MYGUY player[me]
#define STDH 35
#define UNUSED(x) (void)(x)
//PROTOTYPES
void doFrame();
void setupDialogs();



//STRUCTS/CLASSES

struct RPGserver
{
    char ip[32];
    char name[64];
    char players[8];
    RPGserver()
    {
        ip[0]='x';
    }
};

struct cBottleneck
{
    long start;
    long times[4];
    int toggle;
    cTimer check;
    cBottleneck()
    {
        toggle=0;
    }
    void set(int num)
    {
        if(num==0&& check.tick(1000))
            toggle=1;
        if(1||toggle)
        {
            if(num==0)
            {
                times[num]=0;
                start=GetTicks();
            }
            else
            {
                times[num]+=GetTicks()-start;
                start=GetTicks();
            }
        }
        if(num==3)
            toggle=0;
    }
};
cBottleneck bottle;

/*
class CriticalSection
{
public:
    CriticalSection()
    {
        ::InitializeCriticalSection(&cs);
    }
    ~CriticalSection()
    {
        ::DeleteCriticalSection(&cs);
    }
    void Enter()
    {
        ::EnterCriticalSection(&cs);
    }
    void Leave()
    {
        ::LeaveCriticalSection(&cs);
    }
private:
    CRITICAL_SECTION cs;
}; CriticalSection cs;
*/

template <class itemType>
struct shelf
{
    int length;
    int next;
    itemType *list;
    shelf()
    {
        list=0;
        length=0;
        next=0;
    }
    ~shelf()
    {
        if(list!=0)
        {
            delete [] list;
            list=0;
        }
    }
    void create(int m)
    {
        length=m;
        list = new itemType[length];
        clear();
    }
    void clear()
    {
        for(int i=0; i<length; i++)
            list[i].id=-1;
    }
    const itemType & operator [] (int k) const
    {
        return list[k];
    }
    itemType & operator [] (int k)
    {
        return list[k];
    }
    int place(const itemType &i)
    {
        if(next==length)
            return -1;
        int id=next;
        list[next]=i;
        list[next].id=id;
        next++;
        if(next==length)
            return -1;
        while(list[next].id != -1)
        {
            next++;
            if(next==length)
                return -1;
        }
        return id;
    }
    void remove(int i)
    {
        list[i].id=-1;
        if(i<next)
            next=i;
    }
};

int pWidth(char *len);

int isColor(char c)
{
    if(c=='r'||
            c=='R'||
            c=='g'||
            c=='G'||
            c=='b'||
            c=='B'||
            c=='w'||
            c=='W'||
            c=='y'||
            c=='Y'||
            c=='m'||
            c=='M'||
            c=='c'||
            c=='C'||
            c=='N'||
            c=='O'||
            c=='o')
        return 1;
    return 0;
}

struct cMultiLine
{
    char len[16][512];
    int num;
    int multiLine(char *text,int wid)
    {
        num=0;
        int off=0,total=0,temp;
        unsigned int i;
        for(i=0; i<16; i++)
            strcpy(len[i],"");
        char c=0;
        while(1)
        {
            if(c!=0)
                sprintf(len[num],"^%c%s",c,text+total);
            else
                strcpy(len[num],text+total);
            off=0;
            while(pWidth(len[num])>wid)
            {
                len[num][strlen(len[num])-1]='\0';
                off++;
            }
            if(!off)
            {
                num++;
                break;
            }
            //backtrack to a space
            temp=strlen(len[num])-1;
            while(len[num][temp]!=' ')
            {
                temp--;
                if(temp<0)break;
            }
            if(temp>=0)
            {
                off+=(strlen(len[num])-temp-1);
                len[num][temp]='\0';
            }
            for(i=0; i<strlen(len[num])-1; i++)
                if(len[num][i]=='^'&&isColor(len[num][i+1]))
                    c=len[num][i+1];
            num++;
            total+=strlen(text+total)-off;
        }
        return num;
    }
};
cMultiLine mline;

#define CONSOLE_LENGTH 256
class console
{
public:
    char line[CONSOLE_LENGTH][256];
    int t[CONSOLE_LENGTH];
    int len;
    int size;
    int gap;
    void create(int length=CONSOLE_LENGTH,int _gap=20)
    {
        len=length;
        gap=_gap;
        for(int c=0; c<len; c++)
        {
            t[c]=0;
            strcpy(line[c],"");
        }
        size=0;
    }
    void newLine(const char *fmt,...)
    {
        char		text[256];							// Holds Our String
        va_list		ap;									// Pointer To List Of Arguments
        if (fmt == NULL)
            return;
        // Parse The String For Variables
        va_start(ap, fmt);
        vsprintf(text, fmt, ap);
        va_end(ap);
        int n=mline.multiLine(text,616),count;
        for(int c=0; c<n; c++)
        {
            count=0;
            if(line[len-1]!=NULL)
            {   //full list
                for(count=0; count<len-1; count++)
                    strcpy(line[count],line[count+1]);
                strcpy(line[len-1],mline.len[c]);
            }
            else
            {   //partial list
                count=0;
                while(line[count]!=NULL) count++;
                strcpy(line[count],mline.len[c]);
            }
            size++;
            if(size>len)
                size=len;
        }
    }
    void render(int x=0,int y=0,int offset=0,int max=CONSOLE_LENGTH)
    {
        int n=0;
        for(int count=0+offset; count<len && n<max; count++)
        {
            TEXTDRAWER.setColor(1,1,1,1);
            TEXTDRAWER.PrintText(x, y+(count-offset)*gap, line[count]);
            TEXTDRAWER.defaultColor();
            n++;
        }
    }
    void renderAll(int x=0,int y=0)
    {
        for(int count=len; count>=0; count--)
            TEXTDRAWER.PrintText(x, y+count*gap, line[count]);
    }
};

//INSTANCES

int done=0,
    numFrames=0,
    dialog=-1,
    guiskin=0,
    Selection=-1,
    connected=0,
    access_check=0,
    anim=0,
    x=0,
    y=0,
    turning=0,
    oldmap=0,
    chatting=0,
    cstate=0,
    restart=0,
    mscrx=0,
    mscry=0,
    chat_scroll=0,
    me = -1,
    target=-1,
    smove,
    inv_slot=0,
    ptarget_id=-1,
    mtarget_id=-1,
    bodySel=0,
    hairSel=0,
    clothesSel=0,
    animSel=0,
    bodyMax=-1,
    soundMax=-1,
    hairMax=-1,
    clothesMax=-1,
    monsterMax=-1,
    mexp=100,
    gamewidth=800,
    gameheight=600,
    gamebpp=16,
    fullscreen=0,
    map_script=0,
    map_shade=50,
    moved,
    holdMove,
    debug,
    layer,
    scx,
    scy,
    slayer,
    curTile,
    mode,
    newSlot=0,
    curMidi=-1,
    dropSlot;

cPlayer slot[4];

float FPS=0,
      startTime=0;

char myIp[32],
     login_name[32],
     last_tell[256];


console term;

cList <RPGserver> sips;

uxDialog vDialog[11]; //Number of Dialogs/Windows

uxDialog mapDialog;

glSurface tiledata,
          itemdata,
          effdata,
          font,
          loading,
          skin,
          guiback,
          maplayer0,
          maplayer3;

glSurface pBody[256],
          pClothes[256],
          pHair[256],
          pMonster[256],
          pItem[768];

cTimer animTimer,
       anyTimer,
       drawTimer,
       msgTimer,
       walkTime,
       servTimer,
       effectTimer,
       attackTimer,
       spellTimer,
       packetTimer,
       udpTimer,
       useTimer,
       midLength;

cList <cMap> world;

cMap saveWorld,
     copyMap;

cList <cPlayer> player;

cList <cItemRef> item;

pos warp;

shelf <cEffect> eff;
shelf <cHPbar> bar;

cList <cList <int> > fxMap;

cTrade tradeWin[20];

Mix_Music* pMusic=0;

FILE *chatLog=0;

netClient nc;
char autoip[256];

void buildMapLayers();

//FUNCTIONS
// We need to break these off in to a "Common" library later
void debugMsg(const char *fmt,...)
{
#ifdef _DEBUG_
    char		text[256];							// Holds Our String
    va_list		ap;									// Pointer To List Of Arguments
    if (fmt == NULL)
        return;
    // Parse The String For Variables
    va_start(ap, fmt);
    vsprintf(text, fmt, ap);
    va_end(ap);

    FILE *f = fopen("debug.txt","a");
    if (!f)
    {
        printf("Couldn't open Debug log\n");
        return;
    }
    fprintf(f,"%s\n",text);
    fclose(f);
#else
	UNUSED(fmt);
#endif
}

int getPath(int id)
{
    int amt=player[id].path;
    if(amt<0)
        amt=0;
    return amt;
}

void getTradeValues()
{

    MAKE_MSG(twin_msg,trade,TWIN_MSG);

    for(int count=0; count<20; count++)
    {
        trade.item[count].plrID = me;
        strcpy(trade.item[count].name,"");
        trade.item[count].qty = -1;
        trade.item[count].item_template = -1;
        trade.item[count].graphic = -1;
        trade.item[count].merchID = mtarget_id;
        trade.item[count].state = -1;
    }

    nc.send((unsigned char *)&trade,sizeof(twin_msg),SEND_GUARANTEED);
}

void getCharWin()
{
    MAKE_MSG(cwin_msg,plr,CWIN_MSG);

    plr.fire=0;
    plr.ice=0;
    plr.elec=0;
    plr.poison=0;
    plr.magic=0;
    plr.physical=0;
    plr.exp=0;
    plr.tnl=0;
    plr.seren=0;
    plr.honor=0;
    plr.PKs=0;
    plr.str=0;
    plr.itl=0;
    plr.dex=0;
    plr.con=0;
    plr.wis=0;
    strcpy(plr.name,"EMPTY");
    plr.level=0;
    plr.state=-1;
    plr.plrID = me;
    plr.id = -1;
    plr.kills=0;
    plr.deaths=0;
    plr.sprite=-1;
    plr.body=-1;
    plr.hair=-1;
    plr.clothes=-1;
    plr.atk=0;
    plr.def=0;
    strcpy(plr.privProfile,"No");
    nc.send((unsigned char *)&plr,sizeof(cwin_msg),SEND_GUARANTEED);
}

void getRCharWin()
{
    MAKE_MSG(cwin_msg,plr,CWIN_MSG);

    if(mtarget_id >-1)
    {
        plr.fire=0;
        plr.ice=0;
        plr.elec=0;
        plr.poison=0;
        plr.magic=0;
        plr.physical=0;
        plr.exp=0;
        plr.tnl=0;
        plr.seren=0;
        plr.honor=0;
        plr.PKs=0;
        plr.str=0;
        plr.itl=0;
        plr.dex=0;
        plr.con=0;
        plr.wis=0;
        strcpy(plr.name,"EMPTY");
        plr.level=0;
        plr.state=-1;
        plr.id = mtarget_id;
        plr.plrID = me;
        plr.kills=0;
        plr.deaths=0;
        plr.sprite=-1;
        plr.body=-1;
        plr.hair=-1;
        plr.clothes=-1;
        plr.atk=0;
        plr.def=0;
        strcpy(plr.privProfile,"No");
        nc.send((unsigned char *)&plr,sizeof(cwin_msg),SEND_GUARANTEED);
    }
    else
    {
        char message[32];
        strcpy(message,"^RTarget something first!");
        term.newLine(message);
    }
}

void updateFPS()
{
    numFrames++;
    if(numFrames==20)
    {
        float curTime=float(GetTicks());
        FPS=20.0f/((curTime-startTime)/1000.0f);
        startTime=curTime;
        numFrames=0;
    }
}

long itod(int ind)
{
    return player[ind].dpnid;
}

int dtoi(long did)
{
    for(int i=0; i<player.size(); i++)
        if(did==player[i].dpnid)
            return i;
    return -1;
}

int pWidth(char *len)
{
    int width=0,temp;
    for(unsigned int i=0; i<strlen(len); i++)
    {
        if(!(len[i]=='^' && i+1<strlen(len) && isColor(len[i+1])))
        {
            temp=TEXTDRAWER.metrics[((signed char)(len[i]))-32];
            width+=((temp+1)/2)*2;
        }
        else i++;
    }
    return width;
}

int cntr(int x,int twid,char *len)
{
    return (x+(twid/2))-pWidth(len)/2;
}

void fillwith(int x,int y,int tile)
{
    if(x<0||x>=MAP_ROWS||y<0||y>=MAP_COLS)
        return;
    if(curTile>=0)
    {
        if(world[MYGUY.p.map].map[x][y].tile[layer]==curTile||world[MYGUY.p.map].map[x][y].tile[layer]!=tile)
            return;
    }
    else
    {
        if(world[MYGUY.p.map].map[x][y].type==curTile+101||world[MYGUY.p.map].map[x][y].type!=tile)
            return;
    }
    if(curTile>=0)
        world[MYGUY.p.map].map[x][y].tile[layer]=curTile;
    else
        world[MYGUY.p.map].map[x][y].type=curTile+101;
    fillwith(x-1,y,tile);
    fillwith(x+1,y,tile);
    fillwith(x,y-1,tile);
    fillwith(x,y+1,tile);
}

struct cWaves
{
    cList <WaveFile> s;
    cWaves()
    {
        Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024);
        Mix_AllocateChannels(8);
        s.size(256);
    }
    ~cWaves()
    {

    }
    int load(int id,char *file)
    {
        if(id>=s.size())
            s.size(id+1);
        return s[id].Load(file);
    }
    void play(int id)
    {
        s[id].Play();
    }
};
cWaves sounds;

struct cChatBalloon
{
    int id;
    unsigned int start,len,wid,lines;
    cMultiLine text;
    cChatBalloon()
    {
        id=-1;
    }
    void set(char *chat,int index)
    {
        id=index;
        wid=pWidth(chat);
        if(wid>500)wid=500;
        lines=text.multiLine(chat,wid);
        start=GetTicks();
        len=(75*strlen(chat))+1000;
    }
    void draw()
    {
        if(id<0)return;
        int i=0;
        int wx=wid+8;
        int wy=lines*16+16;
        int x=((player[id].p.x*32)-(wid/2))+8;
        int y=player[id].p.y*32-wy-24;
        int cx=player[id].p.x*32+8;
        if(x<0)x=0;
        if(x>640-(wx+10))x=640-(wx+10);
        if(y<0)y=player[id].p.y*32+32;
        if(id==me)
        {
            if(player[me].dir==0)y-=smove;
            else if(player[me].dir==1)y+=smove;
            else if(player[me].dir==2) {
                x+=smove;
                cx+=smove;
            }
            else if(player[me].dir==3) {
                x-=smove;
                cx-=smove;
            }
        }
        else
        {
            int path=getPath(id);
            if(player[id].dir==0)y-=path;
            else if(player[id].dir==1)y+=path;
            else if(player[id].dir==2) {
                x+=path;
                cx+=path;
            }
            else if(player[id].dir==3) {
                x-=path;
                cx-=path;
            }
        }
        skin.setColor(1,1,1,0.5f);
        skin.blit(x,y,16,32,8,8,1,1);//ul corner
        skin.blit(x+wx+8,y,16,32,8,8,-1,1);//ur corner
        skin.blit(x,y+wy,16,32,8,8,1,-1);//ll corner
        skin.blit(x+wx+8,y+wy,16,32,8,8,-1,-1);//lr corner
        skin.blit(x+8,y,24,32,8,8,float(wx)/8.0f-1,1);//north window
        skin.blit(x,y+8,16,40,8,8,1,float(wy)/8.0f-2);//west window
        skin.blit(x+wx+8,y+8,16,40,8,8,-1,float(wy)/8.0f-2);//east window
        skin.blit(x+8,y+wy,24,32,8,8,float(wx)/8.0f-1,-1);//south window
        skin.blit(x+8,y+8,24,40,8,8,float(wx)/8.0f-1,float(wy)/8.0f-2);//inner window
        if(y>player[id].p.y*32)
            skin.blit(cx,y+2,32,32,16,8,1,-1);//chat arrow
        else
            skin.blit(cx,y+wy-2,32,32,16,8,1,1);//chat arrow
        skin.defaultColor();
        while(strlen(text.len[i])>0 && i<16)
        {
            TEXTDRAWER.setColor(1,1,1,1);
            TEXTDRAWER.PrintText(x,y+i*16+8,text.len[i]);
            TEXTDRAWER.defaultColor();
            i++;
        }
        if(GetTicks()-start>len || player[id].p.map!=MYGUY.p.map)
            id=-1;
    }
};
struct cChatBalloonHandler
{
    cList <cChatBalloon> b;
    cChatBalloonHandler()
    {
        b.size(1);
    }
    void add(char *chat,int index)
    {
        int i=0;
        while(b[i].id!=-1)
        {
            i++;
            if(i==b.size())
                b.size(i+1);
        }
        b[i].set(chat,index);
    }
    void draw()
    {
        for(int i=0; i<b.size(); i++)
            b[i].draw();
    }
};
cChatBalloonHandler balloon;

void uxWidget::draw(int px,int py)
{
    if(type==UX_TYPE_BUTTON)
    {
        if(state!=UX_LOCKED)
        {
            if(Input::IsKeyDown(SDLK_MLEFT) && Input::MouseX() > px+x && Input::MouseX() < px+x+width \
                    && Input::MouseY() > py+y-4 && Input::MouseY() < py+y+height)
            {
                skin.setColor(0.90f,0.90f,0.90f,1);
                skin.blit(px+x,py+y,0,48,16,16,1,1);//left side
                int i;
                for(i=16; i<width-16; i+=16)
                    skin.blit(px+x+i,py+y,16,48,16,16,1,1);//middle
                skin.blit(px+x+i,py+y,32,48,16,16,1,1);//right side
                skin.defaultColor();
                TEXTDRAWER.PrintText(cntr(px+x,width-16,label), py+y, label);//label
            }
            else
            {
                skin.blit(px+x,py+y,0,48,16,16,1,1);//left side
                int i;
                for(i=16; i<width-16; i+=16)
                    skin.blit(px+x+i,py+y,16,48,16,16,1,1);//middle
                skin.blit(px+x+i,py+y,32,48,16,16,1,1);//right side
                TEXTDRAWER.PrintText(cntr(px+x,width-16,label), py+y, label);//label
            }
        }
        else Renderer::ColorFill(px+x,py+y,width,height,0,0,0.05f,1);
    }
    if(type==UX_TYPE_LABEL)
    {
        TEXTDRAWER.PrintText(px+x-2, py+y-2, label);
    }
    if(type==UX_TYPE_SLABEL)
    {
        TEXTDRAWER.setColor(0.0,0.0,0.0,1);
        TEXTDRAWER.PrintPlain(px+x-2, py+y-1, label);
        TEXTDRAWER.defaultColor();
        TEXTDRAWER.PrintText(px+x-2,py+y-2, label);
    }
    if(type==UX_TYPE_IMAGE)
    {
        pic->blit(px+x,py+y);
    }
    if(type==UX_TYPE_ITEM)
    {
        if(graphic == -1)
            state=1;
        else
            itemdata.blit(px+x,py+y,(graphic%16)*32,(graphic/16)*32,32,32,scale,scale);
    }
    if(type==UX_TYPE_IBOX)
    {
        skin.blit(px+x,py+y,0,16,16,16,1,1);//nw corner
        skin.blit(px+x,py+y+16,0,32,16,16,1,(height/16)-2);//west
        skin.blit(px+x,py+y+height,0,16,16,16,1,-1);//sw corner
        skin.blit(px+x,py+y,16,16,16,16,(width/16)-1,1);//north
        skin.blit(px+x,py+y+height,16,16,16,16,(width/16)-1,-1);//south
        skin.blit(px+x+width,py+y+16,0,32,16,16,-1,(height/16)-2);//east
        skin.blit(px+x+width,py+y+height,0,16,16,16,-1,-1);//se corner
        skin.blit(px+x+width,py+y,0,16,16,16,-1,1);//ne corner
        //	Renderer::ColorFill(px+x+2,py+y+2,width-4,height-4,0,0,0,1);
    }
    if(type==UX_TYPE_PLYR)
    {
        if(sprite>0)
        {
            pMonster[sprite].blit(px+x,py+y,24,2*32,24,32,1.333f,1.333f);
        }
        else
        {
            pBody[body].blit(px+x,py+y,24,2*32,24,32,1.333f,1.333f);
            pClothes[clothes].blit(px+x,py+y,24,2*32,24,32,1.333f,1.333f);
            pHair[hair].blit(px+x,py+y,24,2*32,24,32,1.333f,1.333f);
        }
    }
    if(type==UX_TYPE_LISTBOX)
    {
        if(state!=UX_LOCKED)
        {
            int c;
            //for(r=0;r<width;r+=16)
            //	for(c=0;c<height;c+=16)
            //		skin.blit(px+x+r,py+y+c,32,16,16,16,1,1);//background
            Renderer::ColorFill(px+x,py+y,width,height,0,0,0,1);
            c=-scroll;
            int i=0;
            while(i<list.size() && c<height/16)
            {
                if(c+scroll==selected&&c>=0)
                    Renderer::ColorFill(px+x,py+y+c*16,width-15,15,1,1,1,0.20f);
                if(c>=0)
                    TEXTDRAWER.PrintText(px+x+1, py+y+1+c*16,list[i].str);
                c++;
                i++;
            }
            //scroll bar
            skin.blit(px+x+width-16,py+y,48,48,16,16,1,1);//scroll up
            skin.blit(px+x+width-16,py+y+16,0,32,16,16,1,(height/16)-2);//frame
            skin.blit(px+x+width-16,py+y+height,48,48,16,16,1,-1);//scroll down
            //window frame
            skin.blit(px+x,py+y,0,16,16,16,1,1);//nw corner
            skin.blit(px+x,py+y+16,0,32,16,16,1,(height/16)-2);//west
            skin.blit(px+x,py+y+height,0,16,16,16,1,-1);//sw corner
            skin.blit(px+x,py+y,16,16,16,16,(width/16)-1,1);//north
            skin.blit(px+x,py+y+height,16,16,16,16,(width/16)-1,-1);//south
            skin.blit(px+x+width,py+y+16,0,32,16,16,-1,(height/16)-2);//east
            skin.blit(px+x+width,py+y+height,0,16,16,16,-1,-1);//se corner
            skin.blit(px+x+width,py+y,0,16,16,16,-1,1);//ne corner
            if(list.size()>height/16)
            {
                int ch = list.size()-height/16-1;
                if(ch==0)
                    ch=1;
                //Renderer::ColorFill(px+x+width-11,py+y+18+(scroll*(height-45)/(list.size()-height/12)),8,8,0,0,1,1);
                skin.blit(px+x+width-16,py+y+16+(scroll*(height-48)/ch),48,32,16,16,1,1);//scroll up
                //if(scroll!=0)
                //if(scroll!=list.size()-height/12)
            }

        }
    }
    if(type==UX_TYPE_FIELD || type==UX_TYPE_PASS)
    {
        for(int c=0; c<width; c+=16)
            skin.blit(px+x+c,py+y,32,16,16,16,1,1);//background
        if(state!=UX_LOCKED)
        {
            //window frame
            skin.blit(px+x,py+y,0,16,16,16,1,1);//nw corner
            skin.blit(px+x,py+y+16,0,32,16,16,1,(height/16)-2);//west
            skin.blit(px+x,py+y+height,0,16,16,16,1,-1);//sw corner
            skin.blit(px+x,py+y,16,16,16,16,(width/16)-1,1);//north
            skin.blit(px+x,py+y+height,16,16,16,16,(width/16)-1,-1);//south
            skin.blit(px+x+width,py+y+16,0,32,16,16,-1,(height/16)-2);//east
            skin.blit(px+x+width,py+y+height,0,16,16,16,-1,-1);//se corner
            skin.blit(px+x+width,py+y,0,16,16,16,-1,1);//ne corner
        }
        //else
        //	Renderer::ColorFill(px+x,py+y,width,height,0,0,0.05f,1);
        if(type==UX_TYPE_PASS)
        {
            char temp[128];
            unsigned int i;
            for(i=0; i<strlen(label); i++)
                temp[i]='*';
            temp[i]='\0';
            if(state==UX_ACTIVE)
            {
                sprintf(temp,"%s|",temp);
                TEXTDRAWER.PrintText(px+x+2,py+y+2,temp);
            }
            else
                TEXTDRAWER.PrintText(px+x+2,py+y+2,temp);
        }
        else
        {
            if(state==UX_ACTIVE)
            {
                char temp[128];
                sprintf(temp,"%s|", Input::GetString());
                TEXTDRAWER.PrintText(px+x+2,py+y+2,temp);
            }
            else
                TEXTDRAWER.PrintText(px+x+2,py+y+2,label);
        }
    }
}
void uxDialog::draw()
{
    if(view==UX_VISIBLE)
    {
        //window fill
        int r,c;
        for(r=0; r<width; r+=16)
            for(c=0; c<height; c+=16)
                skin.blit(x+r,y+16+c,48,16,16,16,1,1);//background
        //title bar
        skin.blit(x,y,0,0,16,16,1,1);//left corner
        skin.blit(x+16,y,16,0,16,16,(width/16)-2,1);//middle section
        skin.blit(x+width,y,0,0,16,16,-1,1);//right corner
        //window frame
        skin.blit(x,y+16,0,16,16,16,1,1);//nw corner
        skin.blit(x,y+32,0,32,16,16,1,(height/16)-2);//west
        skin.blit(x,y+height+16,0,16,16,16,1,-1);//sw corner
        skin.blit(x,y+16,16,16,16,16,(width/16)-1,1);//north
        skin.blit(x,y+height+16,16,16,16,16,(width/16)-1,-1);//south
        skin.blit(x+width,y+32,0,32,16,16,-1,(height/16)-2);//east
        skin.blit(x+width,y+height+16,0,16,16,16,-1,-1);//se corner
        skin.blit(x+width,y+16,0,16,16,16,-1,1);//ne corner
        //char title[64];
        //strcpy(title,"^b");
        //strcpy(title+2,label);
        TEXTDRAWER.setColor(0,0,0,1);
        TEXTDRAWER.PrintText(cntr(x,width-16,label),y,label);
    }
    for(int i=0; i<w.size(); i++)
        w[i].draw(x,y);
}

void addItem(cItemRef theItem)
{
    int i=0;
    if(i==item.size())
        item.size(item.size()+100);
    while(item[i].qty!=0)
    {
        i++;
        if(i==item.size())
            item.size(item.size()+100);
    }
    item[i]=theItem;
}

void addInvItem(cItemRef theItem)
{
    int i=0;
    while(MYGUY.item[i].qty!=0)
    {
        i++;
        if(i==MAX_INV)
            return;
    }
    MYGUY.item[i]=theItem;
}

void drawChar(int x,int y,int sprite,int body,int clothes,int hair,int dir,int frm,float scale=1.3333f)
{
    glLoadIdentity();
    if(dir==0)dir=2;
    else if(dir==1)dir=0;
    else if(dir==2)dir=3;
    else if(dir==3)dir=1;
    if(frm>0)frm++;
    if(sprite>0)
    {
        pMonster[sprite].blit(x,y,frm*24,dir*32,24,32,scale,scale);
    }
    else
    {
        pBody[body].blit(x,y,frm*24,dir*32,24,32,scale,scale);
        pClothes[clothes].blit(x,y,frm*24,dir*32,24,32,scale,scale);
        pHair[hair].blit(x,y,frm*24,dir*32,24,32,scale,scale);
    }
}

/*void drawItem(int x,int y, int graphic, float scale=1.3333f) //Test function
{
	glLoadIdentity();
	pItem[graphic].blit(x,y,
*/
void loadEffectsMap()
{
    FILE *f=fopen("data/misc/sndfx.txt","r");
    if(f==NULL)return;
    char line[128];
    char num[8];
    unsigned int i,l=0,c;
    while(!feof(f))
    {
        fgets(line,128,f);
        if(feof(f))
            break;
        for(i=0,c=0; i<strlen(line); i++,c++)
        {
            if(line[i]==',' || line[i]=='\n')
            {
                num[c]='\0';
                c=0-1;
                if(l>=(unsigned int)fxMap.size())
                    fxMap.size(l+1);
                fxMap[l].size(fxMap[l].size()+1);
                fxMap[l][fxMap[l].size()-1]=atoi(num);
            }
            else
                num[c]=line[i];
        }
        l++;
    }
    fclose(f);
}

void sendCmndMsg(const char *cmd)
{
    char str[256];
    strcpy(str,cmd);
    MAKE_MSG(cmnd_msg,reply,CMND_MSG);
    reply.size=strlen(str)+1;//+1 for null
    char buf[256];
    memcpy(buf,(void *)&reply,sizeof(cmnd_msg));//store header
    memcpy(buf+sizeof(cmnd_msg),(void *)&str,strlen(str)+1);//store string
    nc.send((unsigned char *)&buf,sizeof(cmnd_msg)+strlen(str)+1,SEND_GUARANTEED);
}

void showServers()
{
    term.newLine("^wRequesting worlds...");
    doFrame();
    strcpy(PageBuffer,"");

    ReadPage("www.zircongaming.com", "http://www.zircongaming.com/neometa/neometasrv.php");

    int i=0,len=strlen(PageBuffer);
    while(1)
    {
        if(PageBuffer[i]=='\n' && PageBuffer[i+1]=='\r' && PageBuffer[i+2]=='\n')
        {
            i+=2;
            break;
        }
        i++;
        if(i>=len)
        {
            dialog=0;
            term.newLine("^RNo servers could be found...");
            return;
        }
    }
    char servs[2048];
    strcpy(servs,PageBuffer+i);
    //term.newLine(PageBuffer+194);
    //extract servers
    char stuff[256];
    char str[256];
    int serv_done=0,s=0,p=0;
    i=0;
    char tmp[256];

    while(!serv_done)
    {
        stuff[s]=servs[p];
        p++;
        s++;
        if(servs[p] == 0)
            serv_done = 1;
        else if(servs[p] == ',')
        {
            stuff[s]='\0';
            if(i>=sips.size())
                sips.size(i+1);
            sscanf(stuff,"%[^:]:%[^:]:%[^:]", sips[i].ip, sips[i].name, sips[i].players);
            sprintf(tmp,"%s %s",sips[i].name,sips[i].players);
            i++;
            vDialog[0].w[2].addList(tmp);
            strcpy(stuff,"");
            strcpy(str,"");
            p+=1;
            s=0;
        }
    }
    sprintf(tmp,"^y%d ^wworld(s) found.",i);
    servTimer.reset();
    term.newLine(tmp);
    if(i==0)
        term.newLine("^RNo servers could be found...");
    dialog=0;
}

void downloadUpdate()
{
    term.newLine("^YNewer client available, downloading...");
    doFrame();
    ReadPage("www.mysteralegends.com", "http://www.mysteralegends.com/rpgbeta/RPGBeta.zip");
    char header[512];
    //char header2[512];
    //char servs[1024*512];
    int len;
    sscanf(PageBuffer,"%264[^*] %d", header, &len);
    sprintf(header,"%d",len);
    term.newLine(header);
    FILE *thezip = fopen("client.zip","wb");
    fwrite((unsigned char *)(PageBuffer+324),1,len,thezip);
    fclose(thezip);
    term.newLine("Downloaded, Unzipping...");
    doFrame();
    restart=1;
    done=1;
}

int checkVer()
{
    /*term.newLine("Checking for updates...");
    doFrame();
    ReadPage("www.mysteralegends.com", "http://www.mysteralegends.com/rpgbeta/version.cgi");
    char header[512];
    char servs[128];
    sscanf(PageBuffer,"%190[^*] %[^\n]",&header,&servs);
    float ver;
    sscanf(servs,"%f",&ver);
    if(ver==client_version)
    {
    	term.newLine("Client is up to date.");
    	return 0;
    }
    if(IDYES == MessageBox(NULL,"Newer version is available. Download?","Client Update",MB_YESNO))
    	downloadUpdate();
    else
    	return 0;*/
    return 1;
}

void doRestart()
{
    /*PROCESS_INFORMATION pi;
    STARTUPINFO         si;
    DWORD               dwCode  =   0;
    ZeroMemory(&si,sizeof(STARTUPINFO));
    si.cb           =   sizeof(STARTUPINFO);
    si.dwFlags      =   STARTF_USESHOWWINDOW;
    si.wShowWindow  =   SW_SHOWNORMAL;
    CreateProcess(NULL,"patcher.exe",NULL,NULL,0,NORMAL_PRIORITY_CLASS,NULL,NULL,&si,&pi);*/
}

void initializeSystem()
{

    // (Sonic) These signals being ignored is suck a ugly hack
    // These REALLY need to be removed in the future.
    signal(SIGINT, SIG_IGN);
    signal(SIGILL, SIG_IGN);
    signal(SIGFPE, SIG_IGN);
    signal(SIGSEGV, SIG_IGN);
    signal(SIGTERM, SIG_IGN);
    //signal(SIGBREAK, SIG_IGN);
    signal(SIGABRT, SIG_IGN);

    Renderer::Init( gamewidth, gameheight );
    Renderer::SetTitle("Mystera Legends");

    if(!fullscreen)
        Renderer::SetFullscreen(fullscreen);
    else
    {
#ifdef WIN32
        ShowCursor(0);
#endif
        Renderer::SetFullscreen(fullscreen);
    }
    //misc setup
#ifdef WIN32
    ShowCursor(0);
#endif
    srand(time(NULL));
}

void loadMidi(int num)
{
    char filename[256];
    sprintf(filename,"data/music/%d.ogg",num);
    pMusic = Mix_LoadMUS(filename);
}

void playMidi(int num)
{
    if(num==-1 || !music)
    {
        curMidi=-1;
        Mix_HaltMusic();
        return;
    }

    if(curMidi!=num)
    {
        loadMidi(num);
        Mix_PlayMusic(pMusic, -1);
    }
    else if(! Mix_PlayingMusic() )
        Mix_PlayMusic(pMusic, -1);

    curMidi=num;

}

void setupClient()
{
    //load images and sounds
    char pnum[32];
    int i;
    for(i=0; i<255; i++)
    {
        if(soundMax==-1)
        {
            sprintf(pnum,"data/sounds/%d.wav",i);
            if(!sounds.load(i,pnum))
                soundMax=i;
        }
        if(bodyMax==-1)
        {
            sprintf(pnum,"data/body/%d.png",i);
            if(!pBody[i].Load(pnum))
                bodyMax=i;
        }
        if(hairMax==-1)
        {
            sprintf(pnum,"data/hair/%d.png",i);
            if(!pHair[i].Load(pnum))
                hairMax=i;
        }
        if(clothesMax==-1)
        {
            sprintf(pnum,"data/clothes/%d.png",i);
            if(!pClothes[i].Load(pnum))
                clothesMax=i;
        }
        if(monsterMax==-1 && i>0)
        {
            sprintf(pnum,"data/monsters/%d.png",i);
            if(!pMonster[i].Load(pnum))
                monsterMax=i;
        }
    }
    tiledata.Load("data/misc/tiledata.png");
    effdata.Load("data/misc/effects.png");
    itemdata.Load("data/misc/items.png");
    loading.Load("data/misc/loading.png");
    skin.Load("data/misc/skin0.png");

    //load fonts
    font.Load("data/misc/font.png");
    TEXTDRAWER.Initialize(font.img);
    TEXTDRAWER.setColor(0,0,0,1);
    //create effects,terminal,dialog boxes
    eff.create(MAX_EFFECTS);
    bar.create(MAX_HPBAR);
    term.create(255,11);

    setupDialogs();
    loadEffectsMap();
    //initial size for testing
    world.size(10);
    player.size(10);

    slot[0].lvl=0;
    slot[1].lvl=0;
    slot[2].lvl=0;
    slot[3].lvl=0;

    Input::Init();

    strcpy(last_tell,"");
    strcpy(login_name,"");

    attackTimer.go();
    spellTimer.go();
    effectTimer.go();
    useTimer.go();

    chatLog = fopen("chatlog.txt","a");
}

char *commonStr;
char *concat(char *s1,char *s2)
{
    char temp[256],temp2[256];
    strcpy(temp,s1);
    strcpy(temp2,s2);
    strcpy(commonStr,strcat(temp,temp2));
    return commonStr;
}
char *itos(int num)
{
    char temp[32];
    sprintf(temp,"%d",num);
    commonStr = new char[strlen(temp)+1];
    strcpy(commonStr,temp);
    return commonStr;
}
char *ftos(float num,char *s = "%f")
{
    char temp[32];
    sprintf(temp,s,num);
    commonStr = new char[strlen(temp)+1];
    strcpy(commonStr,temp);
    return commonStr;
}
int stoi(char *str)
{
    return atoi(str);
}
float stof(char *str)
{
    float num;
    sscanf(str,"%f",&num);
    return num;
}

bool saveData(void *data,int size,char *filename,bool append=false)
{
    FILE *f;
    if(!append||(f=fopen(filename,"ab"))==NULL)
        if((f=fopen(filename,"wb"))==NULL)
            return false;
    fwrite (data,size,1,f);
    fclose(f);
    return true;
}
bool loadData(void *data,int size,char *filename)
{
    FILE *f;
    if((f=fopen(filename,"rb"))==NULL)
        return false;
    fread (data,size,1,f);
    fclose(f);
    return true;
}

void attack()
{
    cEffect temp;
    temp.p = MYGUY.front();
    if(temp.p.inBounds())
    {
        for(int i=0; i<player.size(); i++)if(player[i].access>0&&player[i].p.map==temp.p.map&&player[i].p.x==temp.p.x&&player[i].p.y==temp.p.y)
            {
                //temp.index=0;
                //eff.place(temp);
                MAKE_MSG(atck_msg,atk,ATCK_MSG);
                atk.index=i;
                nc.send((unsigned char *)&atk,sizeof(atck_msg),SEND_GUARANTEED);
            }
    }
}

void updateMapDialog()
{
    sprintf(mapDialog.label,"Map %d",MYGUY.p.map);
    sprintf(mapDialog.w[4].label,"N:%d",world[MYGUY.p.map].n);
    sprintf(mapDialog.w[5].label,"S:%d",world[MYGUY.p.map].s);
    sprintf(mapDialog.w[6].label,"W:%d",world[MYGUY.p.map].w);
    sprintf(mapDialog.w[7].label,"E:%d",world[MYGUY.p.map].e);
    sprintf(mapDialog.w[17].label,"N%d",world[MYGUY.p.map].npc[0].index);
    sprintf(mapDialog.w[18].label,"N%d",world[MYGUY.p.map].npc[1].index);
    sprintf(mapDialog.w[19].label,"N%d",world[MYGUY.p.map].npc[2].index);
    sprintf(mapDialog.w[20].label,"N%d",world[MYGUY.p.map].npc[3].index);
    sprintf(mapDialog.w[21].label,"Q%d",world[MYGUY.p.map].npc[0].qty);
    sprintf(mapDialog.w[22].label,"Q%d",world[MYGUY.p.map].npc[1].qty);
    sprintf(mapDialog.w[23].label,"Q%d",world[MYGUY.p.map].npc[2].qty);
    sprintf(mapDialog.w[24].label,"Q%d",world[MYGUY.p.map].npc[3].qty);
    sprintf(mapDialog.w[25].label,"Music:%d",world[MYGUY.p.map].npc[4].index);
    sprintf(mapDialog.w[26].label,"Light:%d",world[MYGUY.p.map].npc[4].qty);
}

void initTestingMode()
{
    me=0;
    player[0].access=10;
    chatting=0;
    strcpy(world[MYGUY.p.map].name,"test");
    strcpy(MYGUY.name,"^BJames");
    mode=1;
    MYGUY.hp=50;
    MYGUY.mp=60;
    //dialog=6;
    //connected=1;
    //Connected=1;
    debug=true;
    player[0].exp=100;
    player[0].item[0].qty=20;
    player[0].item[0].graphic=1;
    strcpy(player[0].item[0].name,"Gold");
}

#endif
