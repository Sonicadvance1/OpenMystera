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

#include "SDL.h"
#include "SDL_Thread.h"

#include <math.h>
#include <time.h>

#ifdef WIN32
#include <windows.h>
#include <mmsystem.h>
#endif

#include <GL/gl.h>
#include <GL/glu.h>
#include <zlib.h>

#include "png.h"

#include "list.h"
#include "signal.h"
#include "DrawText.h"

#include "glpng.h"
#include "glfuncs.h"
#include "sdlgameinput.h"
#include "gamedefs.h"
#include "NetworkStructures.h"
#include "net.h"
#include "metaserv.h"
#include "gui.h"
#include "wave.h"
#include "cglobals.h"
#include "dialog.h"
#include "crecv.h"
#include "console.h"
#include "input.h"
#include "draw.h"

//LIBRARIES
#if defined(_MSC_VER)
#   pragma comment(lib,"sdl.lib")
#   pragma comment(lib,"sdlmain.lib")
#   pragma comment(lib, "opengl32.lib")
#   pragma comment(lib, "glu32.lib")
#   pragma comment(lib, "glaux.lib")
#   pragma comment(lib, "glpng.lib")
#   pragma comment(lib,"SDL_mixer.lib")
#   pragma comment(lib,"wsock32.lib")
#   pragma comment(lib, "winmm.lib")
#   pragma comment(lib,"zlib.lib")
#endif


