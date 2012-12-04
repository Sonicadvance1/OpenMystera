//Tool for censoring strings - James Hamer 2003
/* Usage
CENSOR.star(str);
*/
#ifndef _CENSOR_H
#define _CENSOR_H

#include <string.h>
#include "script_commands.h"
#define BADWORDLEN 101

class cCensor
{
public: //INTERFACE
    void star(char *str)
    {
        if(!str)
            return;
        char temp[256];
        strcpy(temp,str);
        stringLower(temp);
        for(int i=0; i<BADWORDLEN; i++)
        {
            if(str[i]==12)
                str[i]=32;
            while(starOut(temp,badWords[i])!=-1);
        }
        for(unsigned int i=0; i<strlen(str); i++)
            if(temp[i]=='*')
                str[i]='*';
    }
    cCensor()
    {
        strcpy(badWords[0],"fuck");
        strcpy(badWords[1],"shit");
        strcpy(badWords[2],"bitch");
        strcpy(badWords[3],"a$$");
        strcpy(badWords[4],"piss");
        strcpy(badWords[5],"f uck");
        strcpy(badWords[6],"cunt");
        strcpy(badWords[7],"whore");
        strcpy(badWords[8],"bastard");
        strcpy(badWords[9],"dick");
        strcpy(badWords[10],"cock");
        strcpy(badWords[11],"pussy");
        strcpy(badWords[12],"damn");
        strcpy(badWords[13],"dyke");
        strcpy(badWords[14],"@$$");
        strcpy(badWords[15],"asshole");
        strcpy(badWords[16],"assramer");
        strcpy(badWords[17],"b!+ch");
        strcpy(badWords[18],"b!tch");
        strcpy(badWords[19],"b17ch");
        strcpy(badWords[20],"b1tch");
        strcpy(badWords[21],"bi+ch");
        strcpy(badWords[22],"bi7ch");
        strcpy(badWords[23],"bitch");
        strcpy(badWords[24],"c0ck");
        strcpy(badWords[25],"cabron");
        strcpy(badWords[26],"cawk");
        strcpy(badWords[27],"chink");
        strcpy(badWords[28],"clits");
        strcpy(badWords[29],"d4mn");
        strcpy(badWords[30],"dike");
        strcpy(badWords[31],"dildo");
        strcpy(badWords[32],"ejackulate");
        strcpy(badWords[33],"ejaculate");
        strcpy(badWords[34],"faggot");
        strcpy(badWords[35],"fag");
        strcpy(badWords[36],"fcuk");
        strcpy(badWords[37],"foreskin");
        strcpy(badWords[38],"fu(*");
        strcpy(badWords[39],"fuk");
        strcpy(badWords[40],"fux0r");
        strcpy(badWords[41],"h0r");
        strcpy(badWords[42],"fux");
        strcpy(badWords[43],"hoer");
        strcpy(badWords[44],"fu ck");
        strcpy(badWords[45],"huevon");
        strcpy(badWords[46],"jizz");
        strcpy(badWords[47],"kawk");
        strcpy(badWords[48],"s h i t");
        strcpy(badWords[49],"kuksuger");
        strcpy(badWords[50],"l3i+ch");
        strcpy(badWords[51],"l3itch");
        strcpy(badWords[52],"lesbian");
        strcpy(badWords[53],"lesbo");
        strcpy(badWords[54],"masturbat");
        strcpy(badWords[55],"motherfucker");
        strcpy(badWords[56],"nigga");
        strcpy(badWords[57],"nigger");
        strcpy(badWords[58],"nutsack");
        strcpy(badWords[59],"pendejo");
        strcpy(badWords[60],"penis");
        strcpy(badWords[61],"phuck");
        strcpy(badWords[62],"whoar");
        strcpy(badWords[63],"pizda");
        strcpy(badWords[64],"preteen");
        strcpy(badWords[65],"pussy");
        strcpy(badWords[66],"pusse");
        strcpy(badWords[67],"@ss");
        strcpy(badWords[68],"fu(k");
        strcpy(badWords[69],"pussy");
        strcpy(badWords[70],"queef");
        strcpy(badWords[71],"queer");
        strcpy(badWords[72],"qweef");
        strcpy(badWords[73],"scrotum");
        strcpy(badWords[74],"sh!t");
        strcpy(badWords[75],"shiz");
        strcpy(badWords[76],"slut");
        strcpy(badWords[77],"smut");
        strcpy(badWords[78],"testicles");
        strcpy(badWords[79],"tits");
        strcpy(badWords[80],"titties");
        strcpy(badWords[81],"titty");
        strcpy(badWords[82],"twat");
        strcpy(badWords[83],"twaty");
        strcpy(badWords[84],"sh*t");
        strcpy(badWords[85],"f*ck");
        strcpy(badWords[86],"f!ck");
        strcpy(badWords[87],"fu*k");
        strcpy(badWords[88],"f*c");
        strcpy(badWords[89],"f*k");
        strcpy(badWords[90],"f*uck");
        strcpy(badWords[91],"fu*ck");
        strcpy(badWords[92],"fuc k");
        strcpy(badWords[93],"sh*it");
        strcpy(badWords[94],"shi*t");
        strcpy(badWords[95],"nuttsack");
        strcpy(badWords[96],"vagina");
        strcpy(badWords[97],"shi t");
        strcpy(badWords[98],"f u c k");
        strcpy(badWords[99],"fu ck");
        strcpy(badWords[100],"f uc k");
    }
    int starOut(char *str,char *sub)
    {
        unsigned int i=0,n=0,a=0;
        while(i<strlen(str))
        {
            while(str[i+n+a]==sub[n])
            {
                n++;
                if(n==strlen(sub))
                {
                    for(unsigned int t=1; t<strlen(sub); t++)
                        str[i+t]='*';
                    return i;
                }
                /*if(str[i+n]=='^')//for color codes
                {
                	if(i+n+1!=strlen(str)&&(str[i+n+1]==''))
                		a++;
                }*/
            }
            a=0;
            n=0;
            i++;
        }
        return -1;
    }
private: //DATA
    char badWords[BADWORDLEN][16];
};
static cCensor CENSOR;

#endif
