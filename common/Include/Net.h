/* net.h 1.0 James Hamer 04
This is a portable network library which is a layer over SDL_Net.
This layer adds a simpler mechanism for client/server programs to
interact and handle connections. It was designed to work inside an
existing thread on purpose to avoid managing shared data nightmares.
TCP Streams behave more like udp packets so you dont have to manage
partial send/reads or check message lengths.

Note:UDP sockets will open on whichever port you host on plus one.
server.host(12000) //udp now claiming 12001
*/
#ifndef __NET_H__
#define __NET_H__

#include <SDL/SDL_net.h>
#define MAX_PACKET 200000
#define MAX_CLIENT 100

#define SEND_NON_GUARANTEED 0
#define SEND_GUARANTEED 1
#define SEND_RAW_GUARANTEED 2 //not implemented

#define ALL_CLIENTS -1

typedef signed long PlayerID;
/* Dont forget to implement these functions:

//for server
void netServer::onConnect(unsigned long cid,char *ip_address){}
void netServer::onDisconnect(unsigned long cid){}
void netServer::onReceive(unsigned char *data,int size,unsigned long cid){}

//for client
void netClient::onReceive(unsigned char *data,int size){}

*/

class netServer
{
    char myip[16];//text holding local ip address
    char clip[16];//holds a client address temporarily
    unsigned char buffer[MAX_PACKET];//buffer for receiving packets
    unsigned char send_buffer[MAX_PACKET];//buffer for sending packets
    IPaddress ip;
    TCPsocket server;
    TCPsocket client[MAX_CLIENT];
    IPaddress clientip[MAX_CLIENT];
    unsigned char num[MAX_CLIENT];
    unsigned short key[MAX_CLIENT];
    unsigned long count[MAX_CLIENT];
    UDPsocket udpsock;
    UDPpacket *packet;
    UDPpacket *sendpacket;
    SDLNet_SocketSet set;

public:
    int numClients,port;

    netServer();
    ~netServer();
    int host(int thePort);
    void shutdown();
    int update();
    void disconnect(signed long cid);
    int send(unsigned char *data,int size,int guaranteed, signed long cid);
    char *getip();
    char *getip(signed long cid);

    virtual void onConnect(signed long cid,char *ip_address);
    virtual void onDisconnect(signed long cid);
    virtual void onReceive(unsigned char *data,int size, signed long cid);
};

class netClient
{
    unsigned char buffer[MAX_PACKET];//buffer for receiving packets
    unsigned char send_buffer[MAX_PACKET];//buffer for sending packets
    unsigned long marker,pheader;
    unsigned char seed,num;
    unsigned short key;
    unsigned long count;
    IPaddress ip;//server's ip/port data
    TCPsocket sock;
    UDPsocket udpsock;
    UDPpacket *sendpacket;
    UDPpacket *packet;
    SDLNet_SocketSet set;

public:
    int port;

    netClient();
    ~netClient();

    int connect(char *serverip,int thePort);
    int update();
    int send(unsigned char *data,int size,int guaranteed);
    void shutdown();

    virtual void onReceive(unsigned char *data,int size);
};

#endif
