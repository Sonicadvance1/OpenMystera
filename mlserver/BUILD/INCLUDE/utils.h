#ifndef _MLUTILS_
#define _MLUTILS_

#include <time.h>
#include <string.h>

#include <SDL/SDL.h>
#include <SDL/SDL_net.h>
#include <SDL/SDL_thread.h>
//sdl timer
struct timer
{
    long start;
    bool started;
    timer()
    {
		started=0;
    }
	void go()
	{
		started=1;
		start=0;
	}
    bool tick(int len)
    {
		if(!started)
        {
            reset();
            started=1;
        }
        if(int(SDL_GetTicks()-start)>=len)
        {
            reset();
            return 1;
        }
        return 0;
    }
    void reset()
    {
	    start=SDL_GetTicks();
    }
	long ticks()
	{
		return SDL_GetTicks()-start;
	}
};

static int transact(TCPsocket *sock,char *message,char *expect)
{
	int res;
	//printf(message);
	SDLNet_TCP_Send(*sock,message,strlen(message));
	res=SDLNet_TCP_Recv(*sock,message,256);
	if(res<=0)
		return 0;
	message[res]='\0';
	//printf(message);
	if(strstr(message,expect)!=0)
		return 1;
	return 0;
}

static void sendEmail(char *host,char *login,char *pass,char *from,char *to,char *subject,char *body)
{
	IPaddress ip;
	if(SDLNet_ResolveHost(&ip,host,25)==-1)
		return;

	// open the server socket
	TCPsocket sock=SDLNet_TCP_Open(&ip);
	if(!sock)
	{
		if(SDLNet_ResolveHost(&ip,host,24)==-1)
			return;
		TCPsocket sock=SDLNet_TCP_Open(&ip);
		if(!sock)
			return;
	}
	char message[1024];
	
	sprintf(message,"EHLO %s\r\n",host);
	if(!transact(&sock,message,"220"))return;

	if(strlen(login)>1)
	{
		sprintf(message,"AUTH LOGIN\r\n");
		if(!transact(&sock,message,"250"))return;

		sprintf(message,"%s\r\n",login);
		if(!transact(&sock,message,"334"))return;

		sprintf(message,"%s\r\n",pass);
		if(!transact(&sock,message,"334"))return;
	}

	sprintf(message,"MAIL FROM:<%s>\r\n",from);
	if(!transact(&sock,message,"2"))return;//235

	sprintf(message,"RCPT TO:<%s>\r\n",to);
	if(!transact(&sock,message,"250"))return;

	sprintf(message,"DATA\r\n");
	if(!transact(&sock,message,"250"))return;

	sprintf(message,"To: %s\nFrom: %s\nSubject: %s\n%s\n.\r\n",to,from,subject,body);
	if(!transact(&sock,message,"354"))return;

	sprintf(message,"QUIT\r\n");
	SDLNet_TCP_Send(sock,message,strlen(message));
	SDLNet_TCP_Close(sock);
}

//file commands
static int copyFile(char *name,char *newname)
{
	FILE *f;
	FILE *f2;
	f=fopen(name,"rb");
	if(f==NULL)
	{
		return 0;
	}
	f2=fopen(newname,"wb");
	if(f2==NULL)
	{
		return 0;
	}
	fseek(f,0,SEEK_END);
	int len = ftell(f);
	rewind(f);
	void *buffer = new unsigned char[len];
	fread(buffer,len,1,f);
	fwrite(buffer,len,1,f2);
	delete buffer;
	fclose(f);
	fclose(f2);
	return 1;
}

static void backupFile(char *filePath,char *backupPath)
{
	char temp[64];
	sprintf(temp,"%s.%d",backupPath,time(NULL));
	copyFile(filePath,temp);
}

static bool saveData(void *data,int size,char *filename,bool append=false)
{
	FILE *f;
	if(!append||(f=fopen(filename,"ab"))==NULL)
		if((f=fopen(filename,"wb"))==NULL)
			return false;
	fwrite (data,size,1,f);
	fclose(f);
	return true;
}
static bool loadData(void *data,int size,char *filename)
{
	FILE *f;
	if((f=fopen(filename,"rb"))==NULL)
		return false;
	fread (data,size,1,f);
	fclose(f);
	return true;
}
static bool fileExists(char *filename)
{
	FILE *f;
	if((f=fopen(filename,"rb"))==NULL)
		return false;
	fclose(f);
	return true;
}

//flat file database
struct gameDB
{
	FILE *f;
	int size,nextRec;
	char file[64];
	gameDB()
	{
		size=0;
	}
	int connect(char *filename,int s)
	{
		strcpy(file,filename);
		size=s;
		if((f=fopen(filename,"r+b"))==NULL)
		{
			//make new db
			f=fopen(filename,"wb");
			unsigned long sz = 0;
			fwrite(&sz,4,1,f);
			int nr = 0;
			fwrite(&nr,4,1,f);
			fclose(f);
			f=fopen(filename,"r+b");
			return 2;
		}
		return 1;
	}
	void seek(long to)
	{
		fseek(f,to,SEEK_SET);
	}
	void close()
	{
		fclose(f);
	}
	int add(void *data)
	{
		int cursor=8+nextRecord()*size;
		seek(cursor);
		fwrite(data,size,1,f);
		cursor+=size;
		writeNumRecords(numRecords()+1);
		seek(cursor);
		while(1)//search for next available record
		{
			if(fgetc(f)==EOF)
			{
				writeNextAvailableRecord((cursor-8)/size);
				return 1;
			}
			seek(cursor);
			if(fgetc(f)=='!' && fgetc(f)=='M' && fgetc(f)=='T' && fgetc(f)=='!')
			{
				writeNextAvailableRecord((cursor-8)/size);
				return 1;
			}
			seek(cursor);
			fseek(f,size,SEEK_CUR);
			cursor+=size;
		}
		return 1;
	}
	int get(int id,void *data)
	{
		seek(8+id*size);
		if(fgetc(f)==EOF)
			return -1;
		seek(8+id*size);
		if(fgetc(f)=='!' && fgetc(f)=='M' && fgetc(f)=='T' && fgetc(f)=='!')
			return 0;
		seek(8+id*size);
		fread (data,size,1,f);
		return 1;
	}
	int update(int id,void *data)
	{
		seek(8+id*size);
		if(fgetc(f)=='!' && fgetc(f)=='M' && fgetc(f)=='T' && fgetc(f)=='!')
			return 0;
		seek(8+id*size);
		fwrite(data,size,1,f);
		return 1;
	}
	int remove(int id)
	{
		seek(8+id*size);
		if(fgetc(f)==EOF)
			return 0;
		seek(8+id*size);
		fputs("!MT!",f);
		writeNumRecords(numRecords()-1);
		if(nextRecord()>id)
			writeNextAvailableRecord(id);
		return 1;
	}
	void writeNextAvailableRecord(int id)
	{	
		seek(4);
		int sz = id;
		fwrite(&sz,4,1,f);
	}
	unsigned long numRecords()
	{
		if(size==0)
			return 0;
		fseek(f,0,SEEK_SET);
		unsigned long sz;
		fread (&sz,4,1,f);
		return sz;
	}
	void writeNumRecords(unsigned long num)
	{
		seek(0);
		unsigned long sz = num;
		fwrite(&sz,4,1,f);
	}
	int nextRecord()
	{
		seek(4);
		int sz;
		fread (&sz,4,1,f);
		return sz;
	}
};

//critical sections
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
}; 
static CriticalSection cs;

//http get
#define MAX_PAGE    (1024*64)
static char    PageBuffer[MAX_PAGE];

static void startupWinsock()
{
	WSADATA         WsaData;
    WSAStartup(0x0001, &WsaData);
}

static int GetAddr(const char* HostName, int Port, struct sockaddr* Result)
{
    struct hostent*     Host;
    SOCKADDR_IN         Address;

    memset(Result, 0, sizeof(*Result));
    memset(&Address, 0, sizeof(Address));

    Host                = gethostbyname(HostName);
    if(Host != NULL)
    {
        Address.sin_family  = AF_INET;
        Address.sin_port    = htons((short)Port);
        memcpy(&Address.sin_addr, Host->h_addr_list[0], Host->h_length);
        memcpy(Result, &Address, sizeof(Address));
    }
    return Host != NULL;
}

static int ReadPage(char *Page)
{
	int waitRead = 0;
	char Host[256];

	sprintf(Host,"www.mysteralegends.com");

    struct sockaddr     SockAddr;
    SOCKET              Socket;
    int                 Port        = 80; /* HTTP */

    if(GetAddr(Host, Port, &SockAddr))
    {
        int     Status;

        Socket = socket(AF_INET, SOCK_STREAM, 0);
        Status = connect(Socket, &SockAddr, sizeof(SockAddr));
        if(Status >= 0)
        {
            DWORD   StartTime, EndTime;
            char    Request[512];
            char*   Rover   = PageBuffer;
            int     Read;
            sprintf(Request, "GET %s HTTP/1.0\n\n", Page);
            send(Socket, Request, strlen(Request), 0);
			if(!waitRead)
				return 0;
            StartTime = GetTickCount();
            for(Read=0;Read < MAX_PAGE;)
            {
                int ThisRead;
                ThisRead = recv(Socket, Rover, MAX_PAGE-Read, 0);
                if(ThisRead == SOCKET_ERROR || ThisRead == 0)
                    break;
                else
                {
					Read    += ThisRead;
					Rover   += ThisRead;
                }
            }
            EndTime = GetTickCount();
            //newLine("%d milliseconds to read %d-byte page\n",
            //    EndTime-StartTime, Read);
            closesocket(Socket);
        }
        else
            printf( "connect failed (%d)\n",
                WSAGetLastError());
    }
    else
        printf( "Can't map hostname '%s'\n", Host);
	return 0;
}

#endif
