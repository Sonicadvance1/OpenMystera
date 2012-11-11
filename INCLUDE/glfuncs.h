struct glSurface
{
	GLuint img;
	int w,h,d,a;
	float cr,cg,cb,ca;
	glSurface()
	{
		w=1,h=1;
		img=0,d=0,a=0;
		defaultColor();
	}
	~glSurface()
	{
		if(img!=0)
		{
			glDeleteTextures (1,&img);
			img=0;
		}
	}
	void defaultColor()
	{
		cr=1;cg=1;cb=1;ca=1;
	}
	int load(char *filename, int minfilter, int magfilter)
	{
		if(img!=0)
		{
			glDeleteTextures (1,&img);
			img=0;
		}
		pngInfo info;
		img = pngBind(filename, PNG_NOMIPMAP, PNG_STENCIL,&info, GL_REPEAT, minfilter,magfilter);
		w=info.Width;
		h=info.Height;
		d=info.Depth;
		a=info.Alpha;
		if(img!=0)
			return 1;
		return 0;
	}
	void blitFast(int x,int y,float scalex=1.0f,float scaley=1.0f)
	{
		glLoadIdentity();
		glColor4f(cr,cg,cb,ca);
		glBindTexture(GL_TEXTURE_2D, img);
		glBegin( GL_QUADS );
			glTexCoord2f(0,0); glVertex2d( x, y );
			glTexCoord2f(1,0); glVertex2d( x+w*scalex, y );
			glTexCoord2f(1,1); glVertex2d( x+w*scalex, y+h*scaley );
			glTexCoord2f(0,1); glVertex2d( x, y+h*scaley );
		glEnd();
	}
	void setColor(float r,float g,float b,float a)
	{
		cr=r;cg=g;cb=b;ca=a;
	}
	void blit(int x,int y,int sx=0,int sy=0,int cw=0,int ch=0,double scalex=1.0f,double scaley=1.0f)
	{
		glLoadIdentity();
		if(cw==0||ch==0)
		{
			cw=w;
			ch=h;
		}
		float fx=float(sx)/float(w);
		float fy=float(sy)/float(h);
		float gx=float(sx+cw)/float(w);
		float gy=float(sy+ch)/float(h);
		glColor4f(cr,cg,cb,ca);
		glBindTexture(GL_TEXTURE_2D, img);
		glBegin( GL_QUADS );
			glTexCoord2f(fx,fy); glVertex2d( x, y );
			glTexCoord2f(gx,fy); glVertex2d( x+int(float(cw)*scalex), y );
			glTexCoord2f(gx,gy); glVertex2d( x+int(float(cw)*scalex), y+int(float(ch)*scaley) );
			glTexCoord2f(fx,gy); glVertex2d( x, y+int(float(ch)*scaley) );
		glEnd();
	}
	void create(int sx,int sy)
	{
		if(img!=0)
		{
			glDeleteTextures (1,&img);
			img=0;
		}
		w=sx; h=sy;
		unsigned int *data=0;// Stored Data
		data = new unsigned int[sx * sy * 4];
		memset(data,0,(sx * sy * 4 * sizeof(unsigned int)));// Clear Storage Memory
		
		glGenTextures(1, &img);// Create 1 Texture
		glBindTexture(GL_TEXTURE_2D, img);// Bind The Texture
		
		glTexImage2D(GL_TEXTURE_2D, 0, 4, sx, sy, 0,GL_RGBA, GL_UNSIGNED_INT, data);// Build Texture Using Information In data
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
		
		delete [] data;// Release data
	}
	void loadFromScreen(int sx,int sy)//(from bottom left corner)
	{
		if(img==0)
			create(sx,sy);
		
		glBindTexture(GL_TEXTURE_2D,img);// Bind To Texture
		glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 0, 0, sx, sy, 0);
	}
};

void setup_opengl( int width, int height )
{
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);// Enable Alpha Blending (disable alpha testing)
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

void drawTarget(int _x,int _y,int ttype)
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

void drawCursor(int _x,int _y)
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

void colorFill(int x,int y,int w, int h,float r=1.0f,float g=1.0f,float b=1.0f,float a=1.0f)
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

