//HEADER FILES
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#ifndef WIN32

void strlwr(char *t)
{
    if(t==0)
        return;
    int i=0;
    while(t[i]!='\0')
        if(t[i]>=65 && t[i]<=91)
            t[i]+=32;
}
#endif

//#include "mleaks.h"

#include <math.h>
#include <time.h>

#ifdef _WIN32
#include <windows.h>
#include <mmsystem.h>
#else
#include <unistd.h>
#endif

#include <zlib.h>

#include "List.h"
#include "signal.h"
#include "DrawText.h"

#include "glfuncs.h"
#include "sdlgameinput.h"
#include "gamedefs.h"
#include "NetworkStructures.h"
#include "Net.h"
#include "metaserv.h"
#include "gui.h"
#include "wave.h"
#include "cglobals.h"
#include "dialog.h"
#include "crecv.h"
#include "console.h"
#include "input.h"
#include "draw.h"

