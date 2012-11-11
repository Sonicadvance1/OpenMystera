#define MAX_PAGE    (1024*512)

char    PageBuffer[MAX_PAGE];
void showServers();

void ReadPage(const char* Host, const char* Page)
{
	IPaddress SockAddr;
	TCPsocket Socket;
	int Port        = 80; /* HTTP */

	if(SDLNet_ResolveHost(&SockAddr,Host,Port)==-1)
	{
		printf("SDLNet_ResolveHost: %s\n", SDLNet_GetError());
		return;
	}

	Socket=SDLNet_TCP_Open(&SockAddr);

	if(!Socket)
	{
		printf("SDLNet_TCP_Open: %s\n", SDLNet_GetError());
		return;
	}

	unsigned long   StartTime, EndTime;
	char    Request[512];
	char*   Rover   = PageBuffer;
	int     Read;

	sprintf(Request, "GET %s HTTP/1.0\n\n", Page);
	SDLNet_TCP_Send(Socket, Request, strlen(Request));

	StartTime = SDL_GetTicks();
	for(Read=0;Read < MAX_PAGE;)
	{
		int ThisRead;
		ThisRead = SDLNet_TCP_Recv(Socket, Rover, MAX_PAGE-Read);
		if(ThisRead <= 0)
			break;
		else
		{
					Read    += ThisRead;
					Rover   += ThisRead;
		}
	}
	EndTime = SDL_GetTicks();
	printf("%d milliseconds to read %d-byte page\n",EndTime-StartTime, Read);
	SDLNet_TCP_Close(Socket);
}

