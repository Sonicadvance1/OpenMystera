#include "glfuncs.h"

#include <GL/gl.h>
#include <SDL/SDL.h>

namespace Renderer
{
unsigned int width, height;
SDL_Surface *screen=0;

void Init( int _width, int _height )
{
    // The audio initialization should be moved to its own audio library file
    // Haven't got that far yet.
    SDL_Init( 0 );
    SDL_InitSubSystem( SDL_INIT_TIMER );
    SDL_InitSubSystem( SDL_INIT_AUDIO );
    SDL_InitSubSystem( SDL_INIT_VIDEO );

    SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 8 );
    SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 8 );
    SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 8 );
    SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 32 );
    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);// Enable Alpha Blending (disable alpha testing)
    glEnable(GL_BLEND);
    glEnable(GL_TEXTURE_2D);
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    glClearColor( 0, 0, 0, 0 );
    glViewport( 0, 0, width, height );

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity( );

    glOrtho(0.0f,width,height,0.0f,-1.0f,1.0f);
    glMatrixMode(GL_MODELVIEW);// Select The Modelview Matrix
    glLoadIdentity();// Reset The Modelview Matrix
    width = _width;
    height = _height;
}
void Shutdown()
{
    SDL_Quit();
}
void DrawTarget(int _x,int _y,int ttype)
{
    glLoadIdentity();
    glBindTexture(GL_TEXTURE_2D, 0);
    glTranslated(_x+16,_y+16,0);
    if(ttype==0)
        glRotatef(float(SDL_GetTicks())/4.0f,0,0,1);
    else if(ttype==1)
        glRotatef((float(SDL_GetTicks()+360)/4.0f),0,0,1);
    glBegin( GL_TRIANGLES );
    if(ttype==0)
    {
        glColor4f(1,0,0,0.75f);
        glVertex2d( -16,-6 );
        glColor4f(1,1,0,0.75f);
        glVertex2d( -10, 0 );
        glColor4f(1,0,0,0.75f);
        glVertex2d( -16, 6 );
        glColor4f(1,0,0,0.75f);
        glVertex2d(  16,-6 );
        glColor4f(1,1,0,0.75f);
        glVertex2d(  10, 0 );
        glColor4f(1,0,0,0.75f);
        glVertex2d(  16, 6 );
    }
    else if(ttype==1)
    {
        glColor4f(0,1,0,0.75f);
        glVertex2d( -16, -6 );
        glColor4f(0,0,1,0.75f);
        glVertex2d( -10, 0 );
        glColor4f(0,1,0,0.75f);
        glVertex2d( -16, 6 );
        glColor4f(0,1,0,0.75f);
        glVertex2d( 16,  -6 );
        glColor4f(0,0,1,0.75f);
        glVertex2d( 10,  0 );
        glColor4f(0,1,0,0.75f);
        glVertex2d( 16,  6 );
    }
    glEnd();
}

void DrawCursor(int _x,int _y)
{
    glLoadIdentity();
    glBindTexture(GL_TEXTURE_2D, 0);
    glTranslated(_x,_y,0);
    glBegin( GL_TRIANGLES );
    glColor4f(1,1,1,0.75f);
    glVertex2d( 0, 0 );
    glColor4f(0,0,1,0.75f);
    glVertex2d( 24, 8 );
    glColor4f(0,0,1,0.75f);
    glVertex2d( 8, 24 );
    glEnd();
}

void ColorFill(int x,int y,int w, int h,float r,float g,float b,float a)
{
    glLoadIdentity();
    glBindTexture(GL_TEXTURE_2D, 0);
    glColor4f(r,g,b,a);
    glBegin( GL_QUADS );
    glVertex2d( x, y );
    glVertex2d( x+w, y );
    glVertex2d( x+w, y+h );
    glVertex2d( x, y+h );
    glEnd();
}
void Clear()
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}
void SetFullscreen(bool fs)
{
    screen = SDL_SetVideoMode(width, height, 32, SDL_SWSURFACE | SDL_OPENGL | (fs ? SDL_FULLSCREEN : 0));
}
void SetTitle(const char* Title)
{
    SDL_WM_SetCaption(Title, Title);
}
void Swap()
{
    SDL_GL_SwapBuffers();
}

// Deprecated Functions below
void LoadIdentity()
{
    glLoadIdentity();
}
}

