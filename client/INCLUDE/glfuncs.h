#ifndef _RENDER_H_
#define _RENDER_H_

#include <stdio.h>
#include <stdlib.h>

#include <png.h>
#include <GL/gl.h>


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
	int LoadPNG(const char *filename)
	{
			FILE         *infile;         /* PNG file pointer */
			png_structp   png_ptr;        /* internally used by libpng */
			png_infop     info_ptr;       /* user requested transforms */
		   
			char         *image_data;      /* raw png image data */
			char         sig[8];           /* PNG signature array */
			/*char         **row_pointers;   */
		   
			int           bit_depth;
			int           color_type;
		   
			png_uint_32 width;            /* PNG image width in pixels */
			png_uint_32 height;           /* PNG image height in pixels */
			unsigned int rowbytes;         /* raw bytes at row n in image */
		   
			image_data = NULL;
			int i;
			png_bytepp row_pointers = NULL;
		   
			/* Open the file. */
			infile = fopen(filename, "rb");
			if (!infile) {
					return 0;
			}
		   
		   
			/*
			 *              13.3 readpng_init()
			 */
		   
			/* Check for the 8-byte signature */
			fread(sig, 1, 8, infile);
		   
			if (!png_check_sig((unsigned char *) sig, 8)) {
					fclose(infile);
					return 0;
			}
		   
			/*
			 * Set up the PNG structs
			 */
			png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
			if (!png_ptr) {
					fclose(infile);
					return 4;    /* out of memory */
			}
		   
			info_ptr = png_create_info_struct(png_ptr);
			if (!info_ptr) {
					png_destroy_read_struct(&png_ptr, (png_infopp) NULL, (png_infopp) NULL);
					fclose(infile);
					return 4;    /* out of memory */
			}
		   
		   
			/*
			 * block to handle libpng errors,
			 * then check whether the PNG file had a bKGD chunk
			 */
			if (setjmp(png_jmpbuf(png_ptr))) {
					png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
					fclose(infile);
					return 0;
			}
		   
			/*
			 * takes our file stream pointer (infile) and
			 * stores it in the png_ptr struct for later use.
			 */
			/* png_ptr->io_ptr = (png_voidp)infile;*/
			png_init_io(png_ptr, infile);
		   
			/*
			 * lets libpng know that we already checked the 8
			 * signature bytes, so it should not expect to find
			 * them at the current file pointer location
			 */
			png_set_sig_bytes(png_ptr, 8);
		   
			/* Read the image */
		   
			/*
			 * reads and processes not only the PNG file's IHDR chunk
			 * but also any other chunks up to the first IDAT
			 * (i.e., everything before the image data).
			 */
		   
			/* read all the info up to the image data  */
			png_read_info(png_ptr, info_ptr);
		   
			png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth,
									 &color_type, NULL, NULL, NULL);
		   
			w = width;
			h = height;
		   
			/* Set up some transforms. */
			if (color_type & PNG_COLOR_MASK_ALPHA) {
					png_set_strip_alpha(png_ptr);
			}
			if (bit_depth > 8) {
					png_set_strip_16(png_ptr);
			}
			if (color_type == PNG_COLOR_TYPE_GRAY ||
					color_type == PNG_COLOR_TYPE_GRAY_ALPHA) {
					png_set_gray_to_rgb(png_ptr);
			}
			if (color_type == PNG_COLOR_TYPE_PALETTE) {
					png_set_palette_to_rgb(png_ptr);
			}
		   
			/* Update the png info struct.*/
			png_read_update_info(png_ptr, info_ptr);
		   
			/* Rowsize in bytes. */
			rowbytes = png_get_rowbytes(png_ptr, info_ptr);
		   
		   
			/* Allocate the image_data buffer. */
			if ((image_data = (char *) malloc(rowbytes * height))==NULL) {
					png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
					return 4;
		}
		   
			if ((row_pointers = (png_bytepp)malloc(height*sizeof(png_bytep))) == NULL) {
			png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
			free(image_data);
			image_data = NULL;
			return 4;
		}
		   
		   
		/* set the individual row_pointers to point at the correct offsets */
		   
		for (i = 0;  i < height;  ++i)
			row_pointers[height - 1 - i] = (png_byte*)(image_data + i*rowbytes);
		   
		   
		/* now we can go ahead and just read the whole image */
		png_read_image(png_ptr, row_pointers);
		   
		/* and we're done!  (png_read_end() can be omitted if no processing of
		 * post-IDAT text/time/etc. is desired) */
		   
			/* Clean up. */
			free(row_pointers);
		   
			/* Clean up. */
			png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
			fclose(infile);
		   
			glGenTextures(1, &img);
		   
			printf("(loadTexture) width: %lu height: %lu\n", width, height);
		   
			/* create a new texture object
			 * and bind it to texname (unsigned integer > 0)
			 */
			glBindTexture(GL_TEXTURE_2D, img);
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,
									 GL_RGB, GL_UNSIGNED_BYTE, image_data);            
		return img;
	}

	int Load(const char *filename)
	{
		if(img!=0)
		{
			glDeleteTextures (1,&img);
			img=0;
		}
		LoadPNG(filename);
		//img = pngBind(filename, PNG_NOMIPMAP, PNG_STENCIL,&info, GL_REPEAT, minfilter,magfilter);
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
namespace Renderer
{
	// This initializes the renderer
	void Init( int width, int height );
	// Shuts everything down
	void Shutdown();
	// This will draw a certain target
	// TODO: Replace arg3 with a enum
	void DrawTarget(int _x,int _y,int ttype);
	// Draws the cursor
	void DrawCursor(int _x,int _y);
	// Draws a coloured quad
	void ColorFill(int x,int y,int w, int h,float r=1.0f,float g=1.0f,float b=1.0f,float a=1.0f);
	// Clear the screen
	void Clear();
	// Change game to fullscreen or back
	void SetFullscreen(bool fs);
	// Sets the title to the window
	void SetTitle(const char* title);
	// Swap buffers
	void Swap();

	// Deprecated backend functions here
	// These need to be removed very soon
	void LoadIdentity();
}
#endif
