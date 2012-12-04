#include "utils.h"

int transact(TCPsocket *sock,char *message,char *expect)
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
int copyFile(const char *name,const char *newname)
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
    unsigned char *buffer = new unsigned char[len];
    fread(buffer,len,1,f);
    fwrite(buffer,len,1,f2);
    delete [] buffer;
    fclose(f);
    fclose(f2);
    return 1;
}

void backupFile(char *filePath,char *backupPath)
{
    char temp[64];
    sprintf(temp,"%s.%ld",backupPath,time(NULL));
    copyFile(filePath,temp);
}

bool saveData(void *data,int size,char *filename,bool append)
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
bool fileExists(const char *filename)
{
    FILE *f;
    if((f=fopen(filename,"rb"))==NULL)
        return false;
    fclose(f);
    return true;
}

