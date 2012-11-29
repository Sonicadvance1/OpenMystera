#include <GL/gl.h>
#include <SDL/SDL.h>

namespace Renderer
{
	void Init( int width, int height )
	{
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
				glColor4f(1,0,0,0.75f);glVertex2d( -16,-6 );
				glColor4f(1,1,0,0.75f);glVertex2d( -10, 0 );
				glColor4f(1,0,0,0.75f);glVertex2d( -16, 6 );
				glColor4f(1,0,0,0.75f);glVertex2d(  16,-6 );
				glColor4f(1,1,0,0.75f);glVertex2d(  10, 0 );
				glColor4f(1,0,0,0.75f);glVertex2d(  16, 6 );
			}
			else if(ttype==1)
			{
				glColor4f(0,1,0,0.75f);glVertex2d( -16, -6 );
				glColor4f(0,0,1,0.75f);glVertex2d( -10, 0 );
				glColor4f(0,1,0,0.75f);glVertex2d( -16, 6 );
				glColor4f(0,1,0,0.75f);glVertex2d( 16,  -6 );
				glColor4f(0,0,1,0.75f);glVertex2d( 10,  0 );
				glColor4f(0,1,0,0.75f);glVertex2d( 16,  6 );
			}
		glEnd();
	}

	void DrawCursor(int _x,int _y)
	{
		glLoadIdentity();
		glBindTexture(GL_TEXTURE_2D, 0);
		glTranslated(_x,_y,0);
		glBegin( GL_TRIANGLES );
			glColor4f(1,1,1,0.75f);glVertex2d( 0, 0 );
			glColor4f(0,0,1,0.75f);glVertex2d( 24, 8 );
			glColor4f(0,0,1,0.75f);glVertex2d( 8, 24 );
		glEnd();
	}

	void ColorFill(int x,int y,int w, int h,float r=1.0f,float g=1.0f,float b=1.0f,float a=1.0f)
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
}

