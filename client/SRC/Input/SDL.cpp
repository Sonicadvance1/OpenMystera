
#include "Timing.h"
#include <SDL/SDL.h>

namespace Input
{
//mouse coordinates
int mX,mY;

//key events
SDL_Event event;
int keyDown[323];
int keyPress[323];
int keyFlag[323];
int keyUp[323];

//string input
char inputStr[512];
int curPos=0,repTick=300;

cTimer strTimer;


// Switches keys if you have shift clicked
// (Sonic) This stupid function only works for people that have the standard QWERTY keyboard.
int capSwitch(int ch)
{
    if(ch>96&&ch<123)return ch-32;//caps switches
    if(ch==46)return 62; //>
    if(ch==44)return 60; //<
    if(ch==39)return 34; //"
    if(ch==59)return 58; //:
    if(ch==45)return 95; //_
    if(ch==48)return 41; //)
    if(ch==49)return 33; //!
    if(ch==50)return 64; //@
    if(ch==51)return 35; //#
    if(ch==52)return 36; //$
    if(ch==53)return 37; //%
    if(ch==54)return 94; //^
    if(ch==55)return 38; //&
    if(ch==56)return 42; //*
    if(ch==57)return 40; //(
    if(ch==92)return 124;//|
    if(ch==61)return 43; //+
    if(ch==91)return 123;//{
    if(ch==93)return 125;//}
    if(ch==96)return 126;//~
    if(ch==47)return 63; //?
    return ch;
}

bool keyCheck(int k)
{
    if(keyPress[k] || (keyDown[k] && strTimer.tick(repTick)))
    {
        if(keyPress[k])
        {
            repTick=250;
            strTimer.reset();
        }
        else
            repTick=50;
        if(keyDown[SDLK_LSHIFT] || keyDown[SDLK_RSHIFT])
        {
            if(k>255)k-=208;
            inputStr[curPos]=capSwitch(k);
            /*if(inputStr[curPos]=='%')
            {
            curPos++;
            inputStr[curPos]=inputStr[curPos-1];
            }*/
        }
        else
        {

            if(k==SDLK_KP_PERIOD)k='.';
            else if(k==SDLK_KP_DIVIDE)k='/';
            else if(k==SDLK_KP_MULTIPLY)k='*';
            else if(k==SDLK_KP_MINUS)k='-';
            else if(k==SDLK_KP_PLUS)k='+';
            else if(k>255)k-=208;
            inputStr[curPos]=k;
        }
        inputStr[curPos+1]=0;
        curPos++;
        return false;
    }
    return true;
}


// Public functions below
bool Init()
{
    //reset all input keys
    for(unsigned int i = 0; i < 323; ++i)
    {
        keyDown[i]=0;
        keyPress[i]=0;
        keyFlag[i]=0;
        keyUp[i]=0;
    }
    return true;
}
void Shutdown()
{
}
void Update()
{
    memset(keyPress,0,sizeof(keyPress));
    memset(keyUp,0,sizeof(keyUp));
    while(SDL_PollEvent(&event))
    {
        switch (event.type) {
        case SDL_KEYDOWN:
            keyDown[event.key.keysym.sym] = 1;
            keyUp[event.key.keysym.sym] = 0;
            if(keyFlag[event.key.keysym.sym]==0)
            {
                keyPress[event.key.keysym.sym] = 1;
                keyFlag[event.key.keysym.sym] = 1;
            }
            else keyPress[event.key.keysym.sym] = 0;
            break;
        case SDL_KEYUP:
            keyDown[event.key.keysym.sym] = 0;
            keyPress[event.key.keysym.sym] = 0;
            keyFlag[event.key.keysym.sym] = 0;
            keyUp[event.key.keysym.sym] = 1;
            break;
        case SDL_MOUSEMOTION:
            mX=event.motion.x;
            mY=event.motion.y;
            break;
        case SDL_MOUSEBUTTONDOWN:
            if(event.button.button<1||event.button.button>3)
                break;
            keyDown[event.button.button+319] = 1;
            keyUp[event.button.button+319] = 0;
            if(keyFlag[event.button.button+319]==0)
            {
                keyPress[event.button.button+319] = 1;
                keyFlag[event.button.button+319] = 1;
            }
            break;
        case SDL_MOUSEBUTTONUP:
            if(event.button.button<1||event.button.button>3)
                break;
            keyDown[event.button.button+319] = 0;
            keyPress[event.button.button+319] = 0;
            keyFlag[event.button.button+319] = 0;
            keyUp[event.button.button+319] = 1;
            break;
        }
    }
}
bool IsKeyUp(int k)
{
    return keyUp[k] == 1;
}
bool IsKeyDown(int k)
{
    return keyDown[k] == 1;
}
bool IsPressed(int k)
{
    return keyPress[k] == 1;
}
int MouseX()
{
    return mX;
}
int MouseY()
{
    return mY;
}

// Disgusting string functions
void SetString(const char* Text)
{
    strcpy(inputStr, Text);
    curPos = strlen(inputStr);
}
char *GetString()
{
    return inputStr;
}
void NullTerm()
{
    inputStr[strlen(inputStr)-1]='\0';
    curPos--;

}
bool StringInput(int len)
{
    if(curPos<len)
    {
        int k;
        for(k=SDLK_SPACE; k<=SDLK_AT; k++)
            if(!keyCheck(k))
                return false;
        for(k=SDLK_LEFTBRACKET; k<=SDLK_BACKQUOTE; k++)
            if(!keyCheck(k))
                return false;
        for(k=SDLK_a; k<=SDLK_z; k++)
            if(!keyCheck(k))
                return false;
        for(k=SDLK_KP0; k<=SDLK_KP_PLUS; k++)
            if(!keyCheck(k))
                return false;
    }
    if(keyPress[SDLK_BACKSPACE] ||(keyDown[SDLK_BACKSPACE] && strTimer.tick(repTick)))
    {
        if(keyPress[SDLK_BACKSPACE])
        {
            repTick=250;
            strTimer.reset();
        }
        else
            repTick=50;
        if(curPos>0)
        {
            /*if(curPos>1 && inputStr[curPos-1]=='%')
            {
            inputStr[curPos-1]=0;
            curPos--;
            }*/
            inputStr[curPos-1]=0;
            curPos--;
        }
        return false;
    }
    if(keyPress[SDLK_RETURN]&&inputStr[0]!=0)
    {
        keyPress[SDLK_RETURN]=0;
        keyDown[SDLK_RETURN]=0;
        return true;
    }
    return false;
}

void ResetString()
{
    strcpy(inputStr,"");
    curPos=0;
}


}
