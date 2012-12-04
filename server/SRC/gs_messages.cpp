
#include "netstructs.h"
#include "gameserver.h"
#include "net.h"
#include "zlib.h"


#define MAKE_MSG(x,_y,z);    x _y;_y.type=z;
#define MAP_PLAYERS(_map_,_count_)  for(_count_=0;_count_<map_bucket[_map_].size();_count_++)if(player[map_bucket[_map_][_count_]].type==PLAYER)


void cGameServer::sendChatMsg(PlayerID pid, const char *fmt,...)
{
    char text[256];							// Holds Our String
    va_list ap;									// Pointer To List Of Arguments
    if (fmt == NULL)
        return;
    // Parse The String For Variables
    va_start(ap, fmt);
    vsprintf(text, fmt, ap);
    va_end(ap);
    MAKE_MSG(chat_msg,reply,CHAT_MSG);
    reply.size=strlen(text)+1;//+1 for null
    char buf[256];
    memcpy(buf,(void *)&reply,sizeof(chat_msg));//store header
    memcpy(buf+sizeof(chat_msg),(void *)&text,reply.size);//store string
    nh.send((unsigned char*)buf,sizeof(chat_msg)+reply.size,SEND_GUARANTEED,pid);
}

void cGameServer::sendPlyrMsg(int id)
{
    MAKE_MSG(plyr_msg,pmsg,PLYR_MSG);
    pmsg.index=id;
    pmsg.sprite=player[id].sprite;
    pmsg.body=player[id].body;
    pmsg.hair=player[id].hair;
    pmsg.clothes=player[id].clothes;
    if(player[id].type==NPC)
        strcpy(pmsg.name,"^w");
    else if(player[id].access>9)
        strcpy(pmsg.name,"^B");
    else if(player[id].access>1)
        strcpy(pmsg.name,"^b");
    else if(player[id].worth>0)
        strcpy(pmsg.name,"^R");
    else if(player[id].serenity>0)
        strcpy(pmsg.name,"^G");
    else
        strcpy(pmsg.name,"^W");
    strcpy(pmsg.name+2,player[id].name);
    nh.send((unsigned char *)&pmsg,sizeof(plyr_msg),SEND_GUARANTEED,ALL_CLIENTS);
}

void cGameServer::sendAttrMsg(PlayerID pid,int id)
{
    if(player[id].access < 0 || player[id].type!=PLAYER)
        return;
    MAKE_MSG(attr_msg,pmsg,ATTR_MSG);
    pmsg.train=player[id].train;
    pmsg.str=player[id].str;
    pmsg.dex=player[id].dex;
    pmsg.con=player[id].con;
    pmsg.itl=player[id].itl;
    pmsg.wis=player[id].wis;
    nh.send((unsigned char *)&pmsg,sizeof(attr_msg),SEND_GUARANTEED,pid);
}

void cGameServer::sendLevlMsg(PlayerID pid,int id)
{
    if(player[id].access < 0 || player[id].type!=PLAYER)
        return;
    MAKE_MSG(levl_msg,pmsg,LEVL_MSG);
    pmsg.lvl=player[id].lvl;
    pmsg.exp=player[id].exp;
    pmsg.hp=player[id].hp;
    pmsg.mhp=player[id].mhp;
    pmsg.mp=player[id].mp;
    pmsg.mmp=player[id].mmp;
    nh.send((unsigned char *)&pmsg,sizeof(levl_msg),SEND_GUARANTEED,pid);
}

void cGameServer::sendMycrMsg(PlayerID pid,int id)
{
    if(player[id].access < 0 || player[id].type!=PLAYER)
        return;
    MAKE_MSG(mycr_msg,msg,MYCR_MSG);
    msg.p.x = player[id].x;
    msg.p.y = player[id].y;
    msg.p.map = player[id].map;
    msg.dir = player[id].dir;
    nh.send((unsigned char *)&msg,sizeof(mycr_msg),SEND_GUARANTEED,pid);
}

void cGameServer::sendAcssMsg(PlayerID pid,int id)
{
    if(player[id].access < 0 || player[id].type!=PLAYER)
        return;
    MAKE_MSG(acss_msg,msg,ACSS_MSG);
    msg.access = player[id].access;
    nh.send((unsigned char *)&msg,sizeof(acss_msg),SEND_GUARANTEED,pid);
}

void cGameServer::sendUpdtMsg(PlayerID pid,int id)
{
    int p=0,map=player[id].map;
    MAKE_MSG(updt_msg,update,UPDT_MSG);
    xyps_msg ps;
    char buf[5000];
    for(int k=0; k<map_bucket[map].size(); k++)if((player[map_bucket[map][k]].state!=1 || player[map_bucket[map][k]].type==NPC ) && (player[map_bucket[map][k]].type!=NPC || player[map_bucket[map][k]].total_time==0) && map_bucket[map][k]!=id)
        {
            ps.index=map_bucket[map][k];
            ps.x=player[map_bucket[map][k]].x;
            ps.y=player[map_bucket[map][k]].y+(50*player[map_bucket[map][k]].dir);//packed with dir
            memcpy(buf+sizeof(updt_msg)+(p*sizeof(xyps_msg)),(void *)&ps,sizeof(xyps_msg));
            p++;
        }
    update.qty=p;
    memcpy(buf,(void *)&update,sizeof(updt_msg));//store header

    int len = sizeof(updt_msg)+(p*sizeof(xyps_msg));
    //send only if update differs from last
    //if( memcmp((void *)&buf,(void *)&player_update[id],len) != 0)
    //{
    nh.send((unsigned char *)&buf,len,SEND_NON_GUARANTEED,pid);
    //	memcpy((void *)&player_update[id],(void *)&buf,len);
    //}
}

//send map
void cGameServer::sendUpldMsg(PlayerID pid, int mapid)
{
    if(mapid < world.size())
    {
        MAKE_MSG(upld_msg,reply,UPLD_MSG);
        char buf[5000];
        reply.size=map_cache[mapid].size;
        memcpy(buf,(void *)&reply,sizeof(upld_msg));//store header
        memcpy ((unsigned char *)&buf+sizeof(upld_msg),(unsigned char *)&map_cache[mapid],reply.size);
        nh.send((unsigned char *)&buf,sizeof(upld_msg)+reply.size,SEND_GUARANTEED,pid);
    }
}

void cGameServer::sendPlayerVMsg(int index)
{
    MAKE_MSG(plyv_msg,msg,PLYV_MSG);
    pvms_msg pl;
    char pls[200000];
    char buf[200000];
    int p=0;
    for(int k=0; k<player.size(); k++)if(player[k].access>0 && k!=index)
        {
            pl.index=k;
            pl.body=player[k].body;
            pl.hair=player[k].hair;
            pl.clothes=player[k].clothes;
            pl.sprite=player[k].sprite;
            if(player[k].type==NPC)
                strcpy(pl.name,"^w");
            else if(player[k].access>9)
                strcpy(pl.name,"^B");
            else if(player[k].access>1)
                strcpy(pl.name,"^b");
            else if(player[k].worth>0)
                strcpy(pl.name,"^R");
            else if(player[k].serenity>0)
                strcpy(pl.name,"^G");
            else
                strcpy(pl.name,"^W");
            strcpy(pl.name+2,player[k].name);
            memcpy(pls+(p*sizeof(pvms_msg)),(void *)&pl,sizeof(pvms_msg));
            p++;
        }
    unsigned long len=200000;
    compress2 ((unsigned char *)&buf+sizeof(plyv_msg), &len,(unsigned char *)&pls, (unsigned long)p*sizeof(pvms_msg),9);
    msg.size=(unsigned short)len;
    memcpy(buf,(void *)&msg,sizeof(plyv_msg));//store header
    nh.send((unsigned char *)&buf,sizeof(plyv_msg)+len,SEND_GUARANTEED,itod(index));
}

void cGameServer::sendItemVMsg(int index)
{
    MAKE_MSG(itmv_msg,msg,ITMV_MSG);
    ivms_msg pl;
    char pls[50000];
    char buf[50000];
    int p=0;
    for(int k=0; k<ml_items.item.size(); k++)
        if(ml_items.item[k].qty != 0 &&
                ml_items.item[k].map == player[index].map)
        {
            pl.graphic=ml_items.item[k].graphic;
            pl.x=ml_items.item[k].x;
            pl.y=ml_items.item[k].y;
            memcpy(pls+(p*sizeof(ivms_msg)),(void *)&pl,sizeof(ivms_msg));
            p++;
        }
    if(p>0)
    {
        unsigned long len=50000;
        compress2 ((unsigned char *)&buf+sizeof(itmv_msg), &len,(unsigned char *)&pls, (unsigned long)p*sizeof(ivms_msg),9);
        msg.size=(unsigned short)len;
        memcpy(buf,(void *)&msg,sizeof(itmv_msg));//store header
        nh.send((unsigned char *)&buf,sizeof(itmv_msg)+len,SEND_GUARANTEED,itod(index));
    }
}

void cGameServer::sendEquipMsg(int id)
{
    if(player[id].access < 0 || player[id].type!=PLAYER)
        return;
    MAKE_MSG(equi_msg,reply,EQUI_MSG);
    reply.eLeft = player[id].eLeft;
    reply.eRight = player[id].eRight;
    reply.eBody = player[id].eBody;
    reply.eHead = player[id].eHead;
    reply.eSpecial = player[id].eSpecial;
    nh.send((unsigned char *)&reply,sizeof(equi_msg),SEND_GUARANTEED,itod(id));
}

void cGameServer::sendHPMsg(int id)
{
    if(player[id].access < 0 || player[id].type!=PLAYER)
        return;
    MAKE_MSG(hitp_msg,hit,HITP_MSG);
    hit.hp=player[id].hp;
    nh.send((unsigned char *)&hit,sizeof(hitp_msg),SEND_GUARANTEED,itod(id));
}

void cGameServer::sendMPMsg(int id)
{
    if(player[id].access < 0 || player[id].type!=PLAYER)
        return;
    MAKE_MSG(manp_msg,man,MANP_MSG);
    man.mp=player[id].mp;
    nh.send((unsigned char *)&man,sizeof(manp_msg),SEND_GUARANTEED,itod(id));
}

void cGameServer::sendEXPMsg(int id)
{
    if(player[id].access < 0 || player[id].type!=PLAYER)
        return;
    MAKE_MSG(expr_msg,exp,EXPR_MSG);
    exp.exp=player[id].exp;
    nh.send((unsigned char *)&exp,sizeof(expr_msg),SEND_GUARANTEED,itod(id));
}

void cGameServer::sendAddMapItem(int graphic,int map,int x,int y)
{
    MAKE_MSG(item_msg,loot,ITEM_MSG);
    loot.graphic=graphic;
    loot.x=x;
    loot.y=y;
    for(int k=0; k<map_bucket[map].size(); k++)if(player[map_bucket[map][k]].type==PLAYER)
            nh.send((unsigned char *)&loot,sizeof(item_msg),SEND_GUARANTEED,itod(map_bucket[map][k]));
}
void cGameServer::sendRemoveMapItem(int map,int x,int y)
{
    MAKE_MSG(itmr_msg,loot,ITMR_MSG);
    loot.x=x;
    loot.y=y;
    for(int k=0; k<map_bucket[map].size(); k++)if(player[map_bucket[map][k]].type==PLAYER)
            nh.send((unsigned char *)&loot,sizeof(itmr_msg),SEND_GUARANTEED,itod(map_bucket[map][k]));
}

void cGameServer::sendEffect(int map,int x,int y,int effect)
{
    //add effect to send batch
    cEffect temp;
    temp.index=effect;
    temp.x=x;
    temp.y=y;
    temp.map=map;

    int i=0;
    if(i==effect_batch.size())
        effect_batch.size(i+100);
    while(effect_batch[i].index>-1)
    {
        i++;
        if(i==effect_batch.size())
            effect_batch.size(i+100);
    }
    effect_batch[i]=temp;
}

void cGameServer::sendSound(int map,int effect)
{
    MAKE_MSG(sndf_msg,snd,SNDF_MSG);
    snd.effect=effect;
    int count;
    MAP_PLAYERS(map,count)
    nh.send((unsigned char *)&snd,sizeof(sndf_msg),SEND_NON_GUARANTEED,itod(map_bucket[map][count]));
}

void cGameServer::sendShade(PlayerID pid,unsigned char shade_amt)
{
    MAKE_MSG(shad_msg,shade,SHAD_MSG);
    shade.shade=shade_amt;
    nh.send((unsigned char *)&shade,sizeof(shad_msg),SEND_GUARANTEED,pid);
}

void cGameServer::sendFile(PlayerID pid,char *filename)
{
    MAKE_MSG(file_msg,scr,FILE_MSG);

    FILE *thefile = fopen(filename,"rb");
    if(thefile==NULL)
        sendChatMsg(pid,"^wFile does not exist, use the full filename");
    else
    {
        fseek(thefile,0,SEEK_END);
        scr.size = ftell(thefile);
        rewind(thefile);

        strcpy(scr.name,strrchr(filename,'/'));//only filename please
        if(scr.name[0]=='/')strcpy(scr.name,strchr(scr.name,'/')+1);

        unsigned char tbuf[100000];//file download buffer
        unsigned char cbuf[100000];//compressed
        fread(&tbuf,scr.size,1,thefile);
        unsigned long len=100000;
        compress2(cbuf+sizeof(file_msg), &len,(unsigned char *)&tbuf, (unsigned long)scr.size,9);
        scr.size=len;
        memcpy(cbuf,(void *)&scr,sizeof(file_msg));
        nh.send((unsigned char *)&cbuf,sizeof(file_msg) + scr.size,SEND_GUARANTEED,pid);
        fclose(thefile);
    }
}

void cGameServer::sendInventoryRemove(PlayerID pid,signed short index,signed long quantity)
{
    MAKE_MSG(invr_msg,rem,INVR_MSG);
    rem.index=index;
    rem.qty=quantity;
    nh.send((unsigned char *)&rem,sizeof(invr_msg),SEND_GUARANTEED,pid);
}

void cGameServer::sendInventoryQty(PlayerID pid,signed short index,signed long quantity)
{
    MAKE_MSG(iqty_msg,rem,IQTY_MSG);
    rem.index=index;
    rem.qty=quantity;
    nh.send((unsigned char *)&rem,sizeof(iqty_msg),SEND_GUARANTEED,pid);
}

void cGameServer::sendHPbar(int map,unsigned short target)
{
    MAKE_MSG(hbar_msg,hb,HBAR_MSG);
    hb.index=target;
    hb.hp=(unsigned char)((player[target].hp*255)/player[target].mhp);
    int count;
    MAP_PLAYERS(map,count)
    nh.send((unsigned char *)&hb,sizeof(hbar_msg),SEND_NON_GUARANTEED,itod(map_bucket[map][count]));
}

void cGameServer::sendSessionInfo(PlayerID pid)
{
    MAKE_MSG(snfo_msg,chat,SNFO_MSG);
    strcpy(chat.tilebmp,"..");
    strcpy(chat.charbmp,"..");
    nh.send((unsigned char *)&chat,sizeof(snfo_msg),SEND_GUARANTEED,pid);
}

void cGameServer::sendLeftMessage(unsigned short index)
{
    MAKE_MSG(left_msg,msg,LEFT_MSG);
    msg.index=index;
    for(int i=0; i<player.size(); i++)if(player[i].access>0&&player[i].type==PLAYER && i!=index)
            nh.send((unsigned char *)&msg,sizeof(left_msg),SEND_GUARANTEED,player[i].pid);
}

void cGameServer::sendInventory(PlayerID pid,unsigned short index)
{
    MAKE_MSG(invt_msg,inv,INVT_MSG);
    for(int i=0; i<MAX_INV; i++)
        if(player[index].inventory[i]>-1)
        {
            inv.graphic=ml_items.item[player[index].inventory[i]].graphic;
            inv.index=i;
            strcpy(inv.name,ml_items.item[player[index].inventory[i]].name);
            inv.qty=ml_items.item[player[index].inventory[i]].qty;
            nh.send((unsigned char *)&inv,sizeof(invt_msg),SEND_GUARANTEED,pid);
        }
}

void cGameServer::sendParmMsg(PlayerID pid,unsigned char parm,unsigned char flag)
{
    UNUSED(parm);
    UNUSED(flag);
    MAKE_MSG(parm_msg,hello,PARM_MSG);
    hello.parm=0;
    hello.flag=50;
    nh.send((unsigned char *)&hello,sizeof(parm_msg),SEND_GUARANTEED,pid);
}

void cGameServer::sendInventoryAdd(PlayerID pid,unsigned short graphic,char *name,unsigned char index,unsigned long quantity)
{
    MAKE_MSG(invt_msg,inv,INVT_MSG);
    inv.graphic=graphic;
    inv.index=index;
    strcpy(inv.name,name);
    inv.qty=quantity;
    nh.send((unsigned char *)&inv,sizeof(invt_msg),SEND_GUARANTEED,pid);
}
