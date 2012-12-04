#ifndef _DRAWTEXT_H
#define _DRAWTEXT_H

#include <GL/gl.h>

// The number of chars in our font texture.
// We are assuming two sets of 128 chars (e.g. as created by Bitmap Font Creator).
#define NUMCHARS    256

struct cTextDrawer
{
    GLuint mBaseListId;		// Start list id
    GLuint mFontTexId;		// GL font texture id.
    float mR,mG,mB,mA;
    char metrics[256];
    int font;
    cTextDrawer()
    {
        font=0;
        mBaseListId = 0;
        mFontTexId=0;
        mR = mG = mB = mA = 1.0f;
        metrics[0]=3;
        metrics[1]=3;
        metrics[2]=4;
        metrics[3]=7;
        metrics[4]=7;
        metrics[5]=7;
        metrics[6]=8;
        metrics[7]=3;
        metrics[8]=4;
        metrics[9]=4;
        metrics[10]=5;
        metrics[11]=9;
        metrics[12]=3;
        metrics[13]=6;
        metrics[14]=3;
        metrics[15]=6;
        metrics[16]=7;
        metrics[17]=7;
        metrics[18]=7;
        metrics[19]=7;
        metrics[20]=7;
        metrics[21]=7;
        metrics[22]=7;
        metrics[23]=7;
        metrics[24]=7;
        metrics[25]=7;
        metrics[26]=3;
        metrics[27]=3;
        metrics[28]=9;
        metrics[29]=9;
        metrics[30]=9;
        metrics[31]=5;
        metrics[32]=9;
        metrics[33]=8;
        metrics[34]=6;
        metrics[35]=8;
        metrics[36]=8;
        metrics[37]=6;
        metrics[38]=6;
        metrics[39]=8;
        metrics[40]=8;
        metrics[41]=3;
        metrics[42]=3;
        metrics[43]=7;
        metrics[44]=6;
        metrics[45]=9;
        metrics[46]=8;
        metrics[47]=9;
        metrics[48]=6;
        metrics[49]=9;
        metrics[50]=7;
        metrics[51]=6;
        metrics[52]=7;
        metrics[53]=8;
        metrics[54]=7;
        metrics[55]=9;
        metrics[56]=7;
        metrics[57]=7;
        metrics[58]=7;
        metrics[59]=4;
        metrics[60]=6;
        metrics[61]=4;
        metrics[62]=7;
        metrics[63]=6;
        metrics[64]=7;
        metrics[65]=6;
        metrics[66]=6;
        metrics[67]=6;
        metrics[68]=6;
        metrics[69]=6;
        metrics[70]=4;
        metrics[71]=7;
        metrics[72]=7;
        metrics[73]=3;
        metrics[74]=3;
        metrics[75]=6;
        metrics[76]=3;
        metrics[77]=11;
        metrics[78]=7;
        metrics[79]=5;
        metrics[80]=7;
        metrics[81]=6;
        metrics[82]=5;
        metrics[83]=6;
        metrics[84]=4;
        metrics[85]=7;
        metrics[86]=6;
        metrics[87]=8;
        metrics[88]=7;
        metrics[89]=6;
        metrics[90]=6;
        metrics[91]=4;
        metrics[92]=4;
        metrics[93]=4;
        metrics[94]=7;
        metrics[95]=8;
        metrics[96]=7;
        metrics[97]=8;
        metrics[98]=3;
        metrics[99]=4;
        metrics[100]=4;
        metrics[101]=11;
        metrics[102]=7;
        metrics[103]=7;
        metrics[104]=7;
        metrics[105]=11;
        metrics[106]=6;
        metrics[107]=4;
        metrics[108]=11;
        metrics[109]=8;
        metrics[110]=7;
        metrics[111]=8;
        metrics[112]=8;
        metrics[113]=3;
        metrics[114]=3;
        metrics[115]=4;
        metrics[116]=4;
        metrics[117]=7;
        metrics[118]=6;
        metrics[119]=11;
        metrics[120]=7;
        metrics[121]=9;
        metrics[122]=6;
        metrics[123]=4;
        metrics[124]=10;
        metrics[125]=8;
        metrics[126]=6;
        metrics[127]=7;
        metrics[128]=4;
        metrics[129]=4;
        metrics[130]=5;
        metrics[131]=8;
        metrics[132]=8;
        metrics[133]=8;
        metrics[134]=9;
        metrics[135]=4;
        metrics[136]=5;
        metrics[137]=5;
        metrics[138]=6;
        metrics[139]=10;
        metrics[140]=4;
        metrics[141]=7;
        metrics[142]=4;
        metrics[143]=7;
        metrics[144]=8;
        metrics[145]=8;
        metrics[146]=8;
        metrics[147]=8;
        metrics[148]=8;
        metrics[149]=8;
        metrics[150]=8;
        metrics[151]=8;
        metrics[152]=8;
        metrics[153]=8;
        metrics[154]=4;
        metrics[155]=4;
        metrics[156]=10;
        metrics[157]=10;
        metrics[158]=10;
        metrics[159]=6;
        metrics[160]=10;
        metrics[161]=9;
        metrics[162]=7;
        metrics[163]=9;
        metrics[164]=9;
        metrics[165]=7;
        metrics[166]=7;
        metrics[167]=9;
        metrics[168]=9;
        metrics[169]=4;
        metrics[170]=4;
        metrics[171]=8;
        metrics[172]=7;
        metrics[173]=10;
        metrics[174]=9;
        metrics[175]=10;
        metrics[176]=7;
        metrics[177]=10;
        metrics[178]=8;
        metrics[179]=7;
        metrics[180]=8;
        metrics[181]=9;
        metrics[182]=8;
        metrics[183]=10;
        metrics[184]=8;
        metrics[185]=8;
        metrics[186]=8;
        metrics[187]=5;
        metrics[188]=7;
        metrics[189]=5;
        metrics[190]=8;
        metrics[191]=7;
        metrics[192]=8;
        metrics[193]=7;
        metrics[194]=8;
        metrics[195]=7;
        metrics[196]=8;
        metrics[197]=7;
        metrics[198]=5;
        metrics[199]=8;
        metrics[200]=8;
        metrics[201]=4;
        metrics[202]=4;
        metrics[203]=7;
        metrics[204]=4;
        metrics[205]=12;
        metrics[206]=8;
        metrics[207]=8;
        metrics[208]=8;
        metrics[209]=8;
        metrics[210]=6;
        metrics[211]=7;
        metrics[212]=5;
        metrics[213]=8;
        metrics[214]=7;
        metrics[215]=9;
        metrics[216]=8;
        metrics[217]=7;
        metrics[218]=7;
        metrics[219]=5;
        metrics[220]=5;
        metrics[221]=5;
        metrics[222]=8;
        metrics[223]=9;
        metrics[224]=8;
        metrics[225]=9;
        metrics[226]=4;
        metrics[227]=5;
        metrics[228]=5;
        metrics[229]=12;
        metrics[230]=8;
        metrics[231]=8;
        metrics[232]=8;
        metrics[233]=12;
        metrics[234]=7;
        metrics[235]=5;
        metrics[236]=12;
        metrics[237]=9;
        metrics[238]=8;
        metrics[239]=9;
        metrics[240]=9;
        metrics[241]=4;
        metrics[242]=4;
        metrics[243]=5;
        metrics[244]=5;
        metrics[245]=8;
        metrics[246]=7;
        metrics[247]=12;
        metrics[248]=8;
        metrics[249]=10;
        metrics[250]=7;
        metrics[251]=5;
        metrics[252]=11;
        metrics[253]=9;
        metrics[254]=7;
        metrics[255]=8;
    }
    ~cTextDrawer()
    {
        if (mFontTexId)
        {
            // Delete the gl display lists for each letter.
            glDeleteLists(mBaseListId, NUMCHARS);			// Delete All Display Lists

            //delete mSingleton;
        }
    }
    void setFont(int f)
    {
        font=f;
    }
    void defaultColor()
    {
        mR = mG = mB = 0.0f;
        mA=1.0f;
    }
    void setColor(float r,float g,float b,float a)
    {
        mR=r;
        mG=g;
        mB=b;
        mA=a;
    }
    void Initialize(GLuint aFontTextureId)		// Build Our Font Display List
    {
        mFontTexId = aFontTextureId;
        //assert(mSingleton->mFontTexId);		// No font texture id set: Use TEXTDRAWER.SetFontTextureId(aFontTextureId);

        float	cx;										// Holds Our X Character Coord
        float	cy;										// Holds Our Y Character Coord
        int		loop;
        float size=0.0625f;
        mBaseListId = glGenLists(NUMCHARS);				// Creating NUMCHARS Display Lists
        glBindTexture(GL_TEXTURE_2D, mFontTexId);
        for (loop=0; loop<NUMCHARS; loop++)
        {
            cx=((float)(loop%16))/16.0f;				// X Position Of Current Character
            cy=((float)((NUMCHARS-loop-1)/16))/16.0f;				// Y Position Of Current Character
            glNewList(mBaseListId+loop, GL_COMPILE);	// Start Building A List
            glTranslatef(float((metrics[loop]+1)/2),0,0);
            glBegin(GL_QUADS);						// Use A Quad For Each Character
            glTexCoord2f(cx,1-cy-size);		// Texture Coord (Bottom Left)
            glVertex2f(0,0);					// Vertex Coord (Bottom Left)
            glTexCoord2f(cx+size,1-cy-size);// Texture Coord (Bottom Right)
            glVertex2f(16,0);					// Vertex Coord (Bottom Right)
            glTexCoord2f(cx+size,1-cy);		// Texture Coord (Top Right)
            glVertex2f(16,16);					// Vertex Coord (Top Right)
            glTexCoord2f(cx,1-cy);				// Texture Coord (Top Left)
            glVertex2f(0,16);					// Vertex Coord (Top Left)
            glEnd();								// Done Building Our Quad (Character)
            glTranslatef(float((metrics[loop]+1)/2),0,0);				// Move To The Right Of The Character
            glEndList();								// Done Building The Display List
        }
    }

    bool PrintTextf(int x, int y, const char *fmt, ...)
    {
        //assert(mBaseListId != 0);
        char		text[1024];							// Holds Our String
        va_list		ap;									// Pointer To List Of Arguments

        if (fmt == NULL)
            return true;

        // Parse The String For Variables
        va_start(ap, fmt);
        vsprintf(text, fmt, ap);
        va_end(ap);

        glLoadIdentity();
        glBindTexture(GL_TEXTURE_2D, mFontTexId);

        glTranslated(x, y-2, 0);
        //glScaled(0.5f,0.5f,0);
        // Note: the 128 below refers to the font texture containing 2 font sets.
        // Use 0 for the first set, or 128 for the second set.
        glListBase(mBaseListId-32);			// Font bitmaps starts at ' ' (space/32).

        glColor4f(mR,mG,mB,mA);			// Set text colour.
        for(unsigned int i=0; i<strlen(text); i++)
        {
            if(text[i]=='^' && i+1<strlen(text))//parse color codes
            {
                if(text[i+1]=='w')glColor4f(0.6f, 0.6f, 0.6f, 1.0f);
                else if(text[i+1]=='r')glColor4f(0.6f, 0.0f, 0.0f, 1.0f);
                else if(text[i+1]=='g')glColor4f(0.0f, 0.6f, 0.0f, 1.0f);
                else if(text[i+1]=='b')glColor4f(0.0f, 0.0f, 0.6f, 1.0f);
                else if(text[i+1]=='y')glColor4f(0.6f, 0.6f, 0.0f, 1.0f);
                else if(text[i+1]=='m')glColor4f(0.6f, 0.0f, 0.6f, 1.0f);
                else if(text[i+1]=='c')glColor4f(0.0f, 0.6f, 0.6f, 1.0f);
                else if(text[i+1]=='W')glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
                else if(text[i+1]=='R')glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
                else if(text[i+1]=='G')glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
                else if(text[i+1]=='B')glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
                else if(text[i+1]=='Y')glColor4f(1.0f, 1.0f, 0.0f, 1.0f);
                else if(text[i+1]=='M')glColor4f(1.0f, 0.0f, 1.0f, 1.0f);
                else if(text[i+1]=='C')glColor4f(0.0f, 1.0f, 1.0f, 1.0f);
                else if(text[i+1]=='N')glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
                else if(text[i+1]=='O')glColor4f(1.0f, 0.5f, 0.0f, 1.0f);
                else if(text[i+1]=='o')glColor4f(0.75f, 0.4f, 0.0f, 1.0f);
                else
                {
                    glCallList(((signed char)(text[i]))-31+(128*font));
                    i-=1;
                }
                i+=1;
            }
            else glCallList(((signed char)(text[i]))-31+(128*font));
        }
        //glCallLists(strlen(text), GL_BYTE, text);		// Write The Text To The Screen

        return true;
    }
    bool PrintText(int x, int y, const char *text)
    {
        glLoadIdentity();
        glBindTexture(GL_TEXTURE_2D, mFontTexId);

        glTranslated(x, y-2, 0);
        //glScaled(0.5f,0.5f,0);
        // Note: the 128 below refers to the font texture containing 2 font sets.
        // Use 0 for the first set, or 128 for the second set.
        glListBase(mBaseListId-32);			// Font bitmaps starts at ' ' (space/32).

        glColor4f(mR,mG,mB,mA);			// Set text colour.
        for(unsigned int i=0; i<strlen(text); i++)
        {
            if(text[i]=='^' && i+1<strlen(text))//parse color codes
            {
                if(text[i+1]=='w')glColor4f(0.6f, 0.6f, 0.6f, 1.0f);
                else if(text[i+1]=='r')glColor4f(0.6f, 0.0f, 0.0f, 1.0f);
                else if(text[i+1]=='g')glColor4f(0.0f, 0.6f, 0.0f, 1.0f);
                else if(text[i+1]=='b')glColor4f(0.0f, 0.0f, 0.6f, 1.0f);
                else if(text[i+1]=='y')glColor4f(0.6f, 0.6f, 0.0f, 1.0f);
                else if(text[i+1]=='m')glColor4f(0.6f, 0.0f, 0.6f, 1.0f);
                else if(text[i+1]=='c')glColor4f(0.0f, 0.6f, 0.6f, 1.0f);
                else if(text[i+1]=='W')glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
                else if(text[i+1]=='R')glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
                else if(text[i+1]=='G')glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
                else if(text[i+1]=='B')glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
                else if(text[i+1]=='Y')glColor4f(1.0f, 1.0f, 0.0f, 1.0f);
                else if(text[i+1]=='M')glColor4f(1.0f, 0.0f, 1.0f, 1.0f);
                else if(text[i+1]=='C')glColor4f(0.0f, 1.0f, 1.0f, 1.0f);
                else if(text[i+1]=='N')glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
                else if(text[i+1]=='O')glColor4f(1.0f, 0.5f, 0.0f, 1.0f);
                else if(text[i+1]=='o')glColor4f(0.75f, 0.4f, 0.0f, 1.0f);
                else
                {
                    glCallList(((signed char)(text[i]))-31+(128*font));
                    i-=1;
                }
                i+=1;
            }
            else glCallList(((signed char)(text[i]))-31+(128*font));
        }
        //glCallLists(strlen(text), GL_BYTE, text);		// Write The Text To The Screen

        return true;
    }
    bool PrintPlain(int x, int y, const char *fmt, ...)
    {
        //assert(mBaseListId != 0);
        char		text[1024];							// Holds Our String
        va_list		ap;									// Pointer To List Of Arguments

        if (fmt == NULL)
            return true;

        // Parse The String For Variables
        va_start(ap, fmt);
        vsprintf(text, fmt, ap);
        va_end(ap);

        glLoadIdentity();
        glBindTexture(GL_TEXTURE_2D, mFontTexId);

        glTranslated(x, y-2, 0);
        //glScaled(0.5f,0.5f,0);
        // Note: the 128 below refers to the font texture containing 2 font sets.
        // Use 0 for the first set, or 128 for the second set.
        glListBase(mBaseListId-32);			// Font bitmaps starts at ' ' (space/32).

        glColor4f(mR,mG,mB,mA);			// Set text colour.
        for(unsigned int i=0; i<strlen(text); i++)
        {
            if(text[i]=='^' && i+1<strlen(text))//parse color codes
            {

                if(text[i+1]=='w')glColor4f(mR,mG,mB,mA);
                else if(text[i+1]=='r')glColor4f(mR,mG,mB,mA);
                else if(text[i+1]=='g')glColor4f(mR,mG,mB,mA);
                else if(text[i+1]=='b')glColor4f(mR,mG,mB,mA);
                else if(text[i+1]=='y')glColor4f(mR,mG,mB,mA);
                else if(text[i+1]=='m')glColor4f(mR,mG,mB,mA);
                else if(text[i+1]=='c')glColor4f(mR,mG,mB,mA);
                else if(text[i+1]=='W')glColor4f(mR,mG,mB,mA);
                else if(text[i+1]=='R')glColor4f(mR,mG,mB,mA);
                else if(text[i+1]=='G')glColor4f(mR,mG,mB,mA);
                else if(text[i+1]=='B')glColor4f(mR,mG,mB,mA);
                else if(text[i+1]=='Y')glColor4f(mR,mG,mB,mA);
                else if(text[i+1]=='M')glColor4f(mR,mG,mB,mA);
                else if(text[i+1]=='C')glColor4f(mR,mG,mB,mA);
                else if(text[i+1]=='N')glColor4f(mR,mG,mB,mA);
                else if(text[i+1]=='O')glColor4f(mR,mG,mB,mA);
                else if(text[i+1]=='o')glColor4f(mR,mG,mB,mA);
                else
                {
                    glCallList(((signed char)(text[i]))-31+(128*font));
                    i-=1;
                }
                i+=1;
            }
            else glCallList(((signed char)(text[i]))-31+(128*font));
        }
        //glCallLists(strlen(text), GL_BYTE, text);		// Write The Text To The Screen

        return true;
    }
};
cTextDrawer TEXTDRAWER;


#endif
