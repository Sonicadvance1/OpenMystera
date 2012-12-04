//net.cpp James Hamer 04
#include "net.h"
#include <string.h>
#include <time.h>

#ifdef WIN32
#include "winsock.h"
#else
#include <unistd.h>
#endif

static int net_state_watch=0;

//server functions
netServer::netServer()
{
    if(!net_state_watch)
        SDLNet_Init();
    net_state_watch++;
    server=0;
    udpsock=0;
    packet=0;
    sendpacket=0;
    for(int i=0; i<MAX_CLIENT; i++)
    {
        client[i]=0;
        memset(&clientip[i],0,sizeof(IPaddress));
    }
    set=0;
    strcpy(myip,"");
    strcpy(clip,"");
    packet=SDLNet_AllocPacket(MAX_PACKET);
    sendpacket=SDLNet_AllocPacket(MAX_PACKET);
}
netServer::~netServer()
{
    if(sendpacket)
    {
        sendpacket->data=0;
        SDLNet_FreePacket(sendpacket);
        sendpacket=0;
    }
    if(packet)
    {
        packet->data=0;
        SDLNet_FreePacket(packet);
        packet=0;
    }
    shutdown();
    net_state_watch--;
    if(!net_state_watch)
        SDLNet_Quit();
}
int netServer::host(int thePort)
{
    if(SDLNet_ResolveHost(&ip,0,thePort)==-1)
        return 0;
    server=SDLNet_TCP_Open(&ip);
    udpsock=SDLNet_UDP_Open(thePort);
    if(!server || !udpsock)
        return 0;
    numClients=0;
    port=thePort;
    set=SDLNet_AllocSocketSet(MAX_CLIENT+2);
    numClients=SDLNet_TCP_AddSocket(set,server)-2;
    numClients=SDLNet_UDP_AddSocket(set,udpsock)-2;
    return 1;
}

void netServer::shutdown()
{
    /*for(int i=0;i<MAX_CLIENT;i++)
    {
    	if(client[i])
    	{
    		//printf("would be shutting down client %d here %d\n",i,time(0));
    		//disconnect(i);
    		//onDisconnect(i);
    	}
    }*/
    if(server)
    {
        //printf("closing server socket %d\n",time(0));
        SDLNet_TCP_Close(server);
        server=0;
    }
    if(udpsock)
    {
        //printf("closing udp socket %d\n",time(0));
        SDLNet_UDP_Close(udpsock);
        udpsock=0;
    }
    if(set)
    {
        //printf("freeing socket set %d\n",time(0));
        SDLNet_FreeSocketSet(set);
        set=0;
    }
}

int netServer::update()
{
    if(!set)return -1;
    int numchecked=0,numready=SDLNet_CheckSockets(set,0);
    int msg_size;
    if(numready>0)
    {
        signed long cid=0;
        //check for udp packets
        if(SDLNet_SocketReady(udpsock))
        {
            numchecked++;
            SDLNet_UDP_Recv(udpsock, packet);
            while(cid!=MAX_CLIENT && packet->address.host!=clientip[cid].host)
                cid++;
            if(cid!=MAX_CLIENT && packet->data[0]==0)//FUTUREHAZARD ONLY NULL UDP PACKETS ALLOWED
                onReceive(packet->data,packet->len,cid);
        }
        cid=0;
        // check all sockets with SDLNet_SocketReady and handle the active ones.
        if(SDLNet_SocketReady(server))
        {
            numchecked++;
            while(client[cid])
                cid++;
            //add client
            client[cid]=SDLNet_TCP_Accept(server);
            if(client[cid])
            {
                //SDLNet_TCP_SetNonBlocking(client[cid],1);
                numClients=SDLNet_TCP_AddSocket(set,client[cid])-2;
                clientip[cid].host=SDLNet_TCP_GetPeerAddress(client[cid])->host;
                SDLNet_Write16((Uint16)(port+1),&clientip[cid].port);

                //send security seed
                unsigned char seed = rand()%200+50;
                num[cid]=0;
                key[cid]=3^seed;
                count[cid]=0;
                signed long result;
                while(!(result=SDLNet_TCP_Send(client[cid],(unsigned char *)&seed,1)))
                    SDL_Delay(1);
                onConnect(cid,getip(cid));
                if(result<1)
                {
                    disconnect(cid);
                    onDisconnect(cid);
                }
            }
        }
        cid=0;
        //loop through players
        while(numchecked<numready)
        {
            if(client[cid] && SDLNet_SocketReady(client[cid]))
            {
                numchecked++;

                unsigned short header;
                unsigned char sec;
                int result,pheader;

                //check security byte
                num[cid]+=key[cid];
                num[cid]^=(unsigned char)num[cid]*4;
                count[cid]++;
                if(count[cid]%32==0)
                    key[cid]*=3;

                while(!(result=SDLNet_TCP_Recv(client[cid],&sec,1)))
                    SDL_Delay(1);

                if(result>-1 && sec == num[cid])
                {
                    while(!(result=SDLNet_TCP_Recv(client[cid],(unsigned char *)&header,2)))
                        SDL_Delay(1);
                }
                else //security byte mismatch
                    result=-1;

                //printf("header:%d\n",header);
                if(result>-1)
                {
                    if(header==0)
                    {
                        unsigned long exheader;
                        while(!(result=SDLNet_TCP_Recv(client[cid],&exheader,4)))
                            SDL_Delay(1);
                        if(result>-1)
                        {
                            msg_size = exheader;
                            //printf("exheader:%d\n",exheader);

                            while(!(result=SDLNet_TCP_Recv(client[cid],buffer,exheader)))
                                SDL_Delay(1);
                            pheader=exheader-result;
                            //printf("result:%d\n",result);
                        }
                    }
                    else
                    {
                        msg_size = header;
                        while(!(result=SDLNet_TCP_Recv(client[cid],buffer,header)))
                            SDL_Delay(1);
                        pheader=header-result;
                        //printf("result:%d\n",result);
                    }
                }

                if(result<0)
                {
                    //client disconnected
                    disconnect(cid);
                    onDisconnect(cid);
                }
                else
                {
                    if(pheader!=0)
                    {
                        int marker=result;
                        while(pheader!=0)
                        {
                            //printf("result:%d pheader:%d\n",result,pheader);
                            while(!(result=SDLNet_TCP_Recv(client[cid],buffer+marker,pheader)))
                                SDL_Delay(1);
                            if(result<0)
                            {
                                //client disconnected
                                disconnect(cid);
                                onDisconnect(cid);
                                pheader=0;
                                result=0;
                            }
                            else
                            {
                                //printf("next result:%d\n",result);
                                marker+=result;
                                pheader-=result;
                            }
                        }
                    }
                    if(result)
                        onReceive(buffer,msg_size,cid);
                }
            }
            cid++;
        }
        return 1;
    }
    return 0;
}
void netServer::disconnect(signed long cid)
{
    numClients=SDLNet_TCP_DelSocket(set,client[cid])-2;
    SDLNet_TCP_Close(client[cid]);
    client[cid]=0;
    memset(&clientip[cid],0,sizeof(IPaddress));
}
int netServer::send(unsigned char *data,int size,int guaranteed, signed long cid)
{
    if(!guaranteed)
    {
        sendpacket->len=size;
        sendpacket->data=data;

        if(cid==ALL_CLIENTS)
        {
            int numSent=0;
            cid=0;

            while(numSent<numClients)
            {
                if(client[cid])
                {
                    sendpacket->address=clientip[cid];
                    //printf("%s %d\n",getip(cid),sendpacket->address.port);
                    SDLNet_UDP_Send(udpsock,-1, sendpacket);
                    numSent++;
                }
                cid++;
            }
            return 1;
        }
        if(client[cid])
        {
            sendpacket->address=clientip[cid];
            SDLNet_UDP_Send(udpsock,-1, sendpacket);
        }
        return 1;
    }
    if(cid==ALL_CLIENTS)
    {
        int numSent=0;
        cid++;
        while(numSent<numClients)
        {
            if(client[cid])
            {
                send(data,size,guaranteed,cid);
                numSent++;
            }
            cid++;
        }
        return 1;
    }
    if(!client[cid])
        return 0;

    unsigned short header;
    if(size>65535)
    {
        header=0;
        unsigned long exheader=size;
        memcpy(send_buffer,&header,2);
        memcpy(send_buffer+2,&exheader,4);
        memcpy(send_buffer+6,data,size);
        signed long result;
        while(!(result=SDLNet_TCP_Send(client[cid],send_buffer,size+6)))
            SDL_Delay(1);
        if(result<size+6)
        {
            disconnect(cid);
            onDisconnect(cid);
            return 0;
        }
    }
    else
    {
        header=size;
        //printf("size:%d\n",size);
        memcpy(send_buffer,&header,2);
        memcpy(send_buffer+2,data,size);
        signed long result;
        while(!(result=SDLNet_TCP_Send(client[cid],send_buffer,size+2)))
            SDL_Delay(1);
        //printf("result:%d\n",result);
        if(result<size+2)
        {
            disconnect(cid);
            onDisconnect(cid);
            return 0;
        }
    }
    return 1;
}
char *netServer::getip()
{
    if(strcmp(myip,"")!=0)
        return myip;
    IPaddress ip;
    Uint8 *ipaddr;
    char localhostname[256];
    if((gethostname(localhostname, 256)>=0))
    {
        SDLNet_ResolveHost(&ip,localhostname,0);
        ipaddr=(Uint8*)&ip.host;
        sprintf(myip,"%d.%d.%d.%d",ipaddr[0], ipaddr[1], ipaddr[2], ipaddr[3]);
    }
    return myip;
}

char *netServer::getip(signed long cid)
{
    sprintf(clip,"%d.%d.%d.%d",
            ((unsigned char *)&clientip[cid].host)[0],
            ((unsigned char *)&clientip[cid].host)[1],
            ((unsigned char *)&clientip[cid].host)[2],
            ((unsigned char *)&clientip[cid].host)[3]);
    return clip;
}

//client functions
netClient::netClient()
{
    if(!net_state_watch)
        SDLNet_Init();
    net_state_watch++;
    sock=0;
    udpsock=0;
    set=0;
    packet=0;
    sendpacket=0;
}

netClient::~netClient()
{
    shutdown();
    net_state_watch--;
    if(!net_state_watch)
        SDLNet_Quit();
}

int netClient::connect(char *serverip,int thePort)
{
    marker=0;
    packet=SDLNet_AllocPacket(MAX_PACKET);
    sendpacket=SDLNet_AllocPacket(MAX_PACKET);

    if(SDLNet_ResolveHost(&ip,serverip,thePort)==-1)
    {
        shutdown();
        return 0;
    }
    udpsock=SDLNet_UDP_Open(thePort+1);
    sock=SDLNet_TCP_Open(&ip);
    if(!sock || !udpsock)
    {
        shutdown();
        return 0;
    }
    SDLNet_ResolveHost(&sendpacket->address,serverip,thePort);
    port=thePort;
    set=SDLNet_AllocSocketSet(2);
    SDLNet_TCP_AddSocket(set,sock);
    SDLNet_UDP_AddSocket(set,udpsock);
    //SDLNet_TCP_SetNonBlocking(sock,1);

    //recieve security seed
    int result;
    while(!(result=SDLNet_TCP_Recv(sock,&seed,1)))
        SDL_Delay(1);
    if(result<0)
    {
        shutdown();
        return -1;
    }
    num=0;
    key=3^seed;
    count=0;

    return 1;
}
int netClient::update()
{
    if(!set)return -1;
    int msg_size;
    if(SDLNet_CheckSockets(set,0)>0)
    {
        if(SDLNet_SocketReady(udpsock))
        {
            SDLNet_UDP_Recv(udpsock, packet);
            if(packet->address.host==ip.host)
                onReceive(packet->data,packet->len);
        }
        if(SDLNet_SocketReady(sock))
        {
            int result;
            if(marker==0)
            {
                unsigned short header;
                while(!(result=SDLNet_TCP_Recv(sock,&header,2)))
                    SDL_Delay(1);
                if(result<0)
                {
                    shutdown();
                    return -1;
                }
                if(header==0)
                {
                    unsigned long exheader;
                    while(!(result=SDLNet_TCP_Recv(sock,&exheader,4)))
                        SDL_Delay(1);
                    if(result<0)
                    {
                        shutdown();
                        return -1;
                    }
                    msg_size = exheader;
                    while(!(result=SDLNet_TCP_Recv(sock,buffer,exheader)))
                        SDL_Delay(1);
                    if(result<0)
                    {
                        shutdown();
                        return -1;
                    }
                    if(result<(signed long)exheader)
                    {
                        marker=result;
                        pheader=exheader-result;
                    }
                }
                else
                {
                    msg_size = header;
                    while(!(result=SDLNet_TCP_Recv(sock,buffer,header)))
                        SDL_Delay(1);
                    if(result<0)
                    {
                        shutdown();
                        return -1;
                    }
                    if(result<header)
                    {
                        marker=result;
                        pheader=header-result;
                    }
                }
            }
            else
            {
                while(!(result=SDLNet_TCP_Recv(sock,buffer+marker,pheader)))
                    SDL_Delay(1);
                if(result<0)
                {
                    shutdown();
                    return -1;
                }
                if(result<(signed long)pheader)
                {
                    marker+=result;
                    pheader-=result;
                }
                else
                    marker=0;
            }
            if(result<0)
            {
                //disconnected
                shutdown();
                return -1;
            }
            else if(marker==0)
                onReceive(buffer,msg_size);
        }
        return 1;
    }
    return 0;
}

int netClient::send(unsigned char *data,int size,int guaranteed)
{
    if(!set)return 0;
    if(!guaranteed)
    {
        sendpacket->len=size;
        sendpacket->data=data;
        SDLNet_UDP_Send(udpsock,-1, sendpacket);
        return 1;
    }
    //add security byte
    num+=key;
    num^=(unsigned char)num*4;
    count++;
    if(count%32==0)
        key*=3;
    memcpy(send_buffer,&num,1);

    unsigned short header;
    if(size>65535)
    {
        header=0;
        unsigned long exheader=size;
        memcpy(send_buffer+1,&header,2);
        memcpy(send_buffer+3,&exheader,4);
        memcpy(send_buffer+7,data,size);
        signed long result;
        //printf("exheader:%d\n",exheader);
        while(!(result=SDLNet_TCP_Send(sock,send_buffer,size+7)))
            SDL_Delay(1);
        if(result<size+7)
        {
            shutdown();
            return 0;
        }
    }
    else
    {
        header=size;
        memcpy(send_buffer+1,&header,2);
        memcpy(send_buffer+3,data,size);
        signed long result;
        //printf("header:%d\n",header);
        while(!(result=SDLNet_TCP_Send(sock,send_buffer,size+3)))
            SDL_Delay(1);
        //printf("result:%d\n",result);
        if(result<size+3)
        {
            shutdown();
            return 0;
        }
    }
    return 1;
}

void netClient::shutdown()
{
    //printf("shutting down\n");
    if(set && udpsock && sock)
    {
        SDLNet_UDP_DelSocket(set,udpsock);
        SDLNet_TCP_DelSocket(set,sock);
    }

    if(udpsock)
    {
        SDLNet_UDP_Close(udpsock);
        udpsock=0;
    }
    if(sock)
    {
        SDLNet_TCP_Close(sock);
        sock=0;
    }
    if(set)
    {
        SDLNet_FreeSocketSet(set);
        set=0;
    }
    if(sendpacket)
    {
        sendpacket->data=0;
        SDLNet_FreePacket(sendpacket);
        sendpacket=0;
    }
    if(packet)
    {
        packet->data=0;
        SDLNet_FreePacket(packet);
        packet=0;
    }
}

