//DirectPlay 8.0 Wrapper
#ifndef _DPLAY8WRAP_
#define _DPLAY8WRAP_

#include "dplay8.h"
#include "dpaddr.h"

#define ReleaseCOM(x) if(x) { x->Release(); x = NULL; }
struct genMsg{char type; void *data;};

static void (*mhandler)(void *,unsigned long,unsigned long,unsigned long);

class netHandler
{
public:
	IDirectPlay8Server		*DPServer;
	IDirectPlay8Client		*DPClient;

	DPNMSG_RECEIVE			*DPNnewMsg;
	DPNMSG_CREATE_PLAYER	*DPNnewPlayer;
	int						networkState;
	BOOL					Connected;
	bool					Hosting;
	long					Port;
	char					IPAddress[MAX_PATH];
	char					PlayerName[MAX_PATH];
	char					SessionName[MAX_PATH];
	char					SessionPassword[MAX_PATH];
	long					MaxPlayers;
	long					NumPlayers;

	netHandler();
	~netHandler();

	void setMessageHandler(void (*mh)(void *,unsigned long,unsigned long,unsigned long));

	bool disconnect();
	bool getIP(char *IPAddress, unsigned long PlayerNum=0);
	bool host(long PortNum, char *Session, char *Password, long _MaxPlayers,GUID *guidAdapter=NULL);
	bool connect(char *IP, long PortNum, char *PlayerName, char *Session, char *Password,GUID *guidAdapter=NULL);
	bool disconnectPlayer(long PlayerId);
	bool serverSend(void *Data, unsigned long Size,unsigned long Flags=DPNSEND_NOLOOPBACK,DPNID dpnidPlayer=0);
	bool clientSend(void *Data, unsigned long Size, unsigned long Flags);
	static HRESULT WINAPI messageHandler(PVOID pvUserContext, DWORD dwMessageId, PVOID pMsgBuffer);
};

#endif