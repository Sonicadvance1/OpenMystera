#ifndef _MLUTILS_
#define _MLUTILS_

#include <time.h>
#include <string.h>

#include <SDL/SDL.h>
#include <SDL/SDL_net.h>
#include <SDL/SDL_thread.h>
#define UNUSED(x) (void)(x)
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

int transact(TCPsocket *sock,char *message,char *expect);

/*static void sendEmail(char *host,char *login,char *pass,char *from,char *to,char *subject,char *body)
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
*/

//file commands
int copyFile(const char *name,const char *newname);
void backupFile(char *filePath,char *backupPath);
bool saveData(void *data,int size,char *filename,bool append=false);
bool loadData(void *data,int size,char *filename);
bool fileExists(const char *filename);

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

#endif
