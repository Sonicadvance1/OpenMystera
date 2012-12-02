//Gui stuff - James Hamer 2003
#include "Input.h"

#define UX_INACTIVE  0
#define UX_ACTIVE    1
#define UX_LOCKED    2

#define UX_VISIBLE      0
#define UX_TRANSPARENT  1

#define UX_TYPE_BUTTON  0
#define UX_TYPE_FIELD   1 
#define UX_TYPE_PASS    2
#define UX_TYPE_LABEL   3
#define UX_TYPE_CHECK   4
#define UX_TYPE_OPTION  5
#define UX_TYPE_LISTBOX 6
#define UX_TYPE_IMAGE   7
#define UX_TYPE_IBOX	8
#define UX_TYPE_SLABEL	9
#define UX_TYPE_ITEM	10
#define UX_TYPE_PLYR	11

int pWidth(char *len);

struct listMember
{
	char str[256];
};

struct uxWidget
{
	int id,x,y,width,height,state,type,selected,scroll,graphic,sprite,body,clothes,hair;
	float scale;
	glSurface *pic;
	char label[128];
	cList <listMember> list;
	uxWidget()
	{
		pic=0;
		id=-1;
		graphic=-1;
	}
	void set(int _type,int _x,int _y,int _w,int _h, const char *_label)
	{
		type = _type;
		x= _x;
		y= _y;
		width= _w;
		height= _h;
		strcpy(label,_label);
		state=0;
		selected=0;
		scroll=0;
		scale=1.000;
	}
	void clear()
	{
		list.size(0);
	}
	void addList(char *nstr)
	{
		list.size(list.size()+1);	
		strcpy(list[list.size()-1].str,nstr);
	}
	void setState(int _state)
	{
		state=_state;
	}
	void setImage(glSurface *tex)
	{
		pic=tex;
	}
	void setGraphic(int iGraphic)
	{
		graphic = iGraphic;
	}
	void setAppr(int mSprite, int mBody, int mClothes, int mHair)
	{
		sprite = mSprite;
		body = mBody;
		clothes = mClothes;
		hair = mHair;
	}
	void setScale(float wScale)
	{
		scale = wScale;
	}
	void draw(int px,int py);
	int check(int px,int py)
	{
		if(type==UX_TYPE_BUTTON)
		{
			if(Input::IsKeyUp(SDLK_MLEFT) && Input::MouseX()>px+x && Input::MouseX()<px+x+width && Input::MouseY()>py+y-4 && Input::MouseY()<py+y+height)
				return 1;
			return 0;
		}
		if(type==UX_TYPE_IBOX)
		{
			if(Input::IsKeyUp(SDLK_MLEFT) && Input::MouseX()>px+x && Input::MouseX()<px+x+width && Input::MouseY()>py+y-4 && Input::MouseY()<py+y+height)
				return 1;
			return 0;
		}
		if(type==UX_TYPE_ITEM)
		{
			if(Input::IsKeyUp(SDLK_MLEFT) && Input::MouseX()>px+x && Input::MouseX()<px+x+width && Input::MouseY()>py+y-4 && Input::MouseY()<py+y+height)
				return 1;
			return 0;
		}
		if(type==UX_TYPE_LISTBOX)
		{
			if(list.size()>height/16) //scrolling
			{
				if(Input::IsKeyUp(SDLK_MLEFT) && Input::MouseX()>px+x+width-16 && Input::MouseX()<px+x+width && Input::MouseY()>py+y && Input::MouseY()<py+y+16)
				{
					scroll--;
					if(scroll<0)
						scroll=0;
				}
				else if(Input::IsKeyUp(SDLK_MLEFT) && Input::MouseX()>px+x+width-16 && Input::MouseX()<px+x+width && Input::MouseY()>py+y+height-16 && Input::MouseY()<py+y+height)
				{
					scroll++;
					if(scroll>list.size()-height/16)
						scroll=list.size()-height/16;
				}
				else if(Input::IsKeyDown(SDLK_MLEFT) && Input::MouseX()>px+x+width-16 && Input::MouseX()<px+x+width && Input::MouseY()>py+y+16 && Input::MouseY()<py+y+height-16)
				{
					scroll=(Input::MouseY()-py-y-24)*(list.size()-height/16)/(height-48);
					if(scroll<0)scroll=0;
					if(scroll>list.size()-height/16)
						scroll=list.size()-height/16;
				}
			}
			if(Input::IsKeyUp(SDLK_MLEFT) && Input::MouseX()>px+x && Input::MouseX()<px+x+width-16 && Input::MouseY()>py+y && Input::MouseY()<py+y+height)
			{
				int s = (Input::MouseY()-(py+y+(-scroll*16)))/16;
				if(s<list.size())
				{
					selected=s;
					return 1;
				}
			}
			return 0;
		}
		if(type==UX_TYPE_FIELD || type==UX_TYPE_PASS)
		{
			if(state==UX_ACTIVE)
			{
				if(!Input::IsPressed(SDLK_MLEFT))
					strcpy(label, Input::GetString());	
				int len=256;
				if(type==UX_TYPE_PASS)
					len=16;
				if(Input::StringInput(len))
				{
					strcpy(label, Input::GetString());
					return 1;
				}
				if(type==UX_TYPE_FIELD && pWidth(Input::GetString())>width-16)
					Input::NullTerm();
			}
			if(Input::IsPressed(SDLK_MLEFT))
			{
				if(Input::MouseX()>px+x && Input::MouseX()<px+x+width && Input::MouseY()>py+y && Input::MouseY()<py+y+height)
				{
					if(state==UX_INACTIVE)
					{
						state=UX_ACTIVE;
						Input::SetString(label);
					}
				}
				else
					state=UX_INACTIVE;
			}
			return 0;
		}
		return 0;
	}
};

struct uxDialog
{
	cList <uxWidget> w;
	int x,y,width,height,hx,hy,view,hotkey;
	char label[256];
	uxDialog()
	{
		view=0;
		hx=-1;
		hotkey=1;
	}
	void init(int _x,int _y, int _w,int _h, const char *_label)
	{
		x= _x;
		y= _y;
		width= _w;
		height= _h;
		strcpy(label,_label);
	}
	void draw();
	void setTransparent(int tr)
	{
		view=tr;
	}
	int add(uxWidget widg)
	{
		w.size(w.size()+1);
		w[w.size()-1]=widg;
		return w.size()-1;
	}
	void remove(int ind)
	{
		w[ind]=w[w.size()-1];
		w.size(w.size()-1);
	}
	int modified()
	{
		int sel=-1;
		for(int i=0;i<w.size();i++)
		{
			if(hotkey)
			{
				if(Input::IsPressed(SDLK_DOWN) && w[i].type==UX_TYPE_LISTBOX && w[i].selected < w[i].list.size()-1)
					w[i].selected++;
				if(Input::IsPressed(SDLK_UP) && w[i].type==UX_TYPE_LISTBOX && w[i].selected >0)
					w[i].selected--;
				if(Input::IsPressed(SDLK_RETURN) && w[i].type==UX_TYPE_BUTTON && !Input::IsKeyDown(SDLK_LALT) && !Input::IsKeyDown(SDLK_RALT))
					return i;
				if(Input::IsPressed(SDLK_TAB) && w[i].state==UX_ACTIVE && (w[i].type==UX_TYPE_FIELD || w[i].type==UX_TYPE_PASS))//tab selection
				{
					int c=i+1;
					if(c>w.size()-1)
						c=0;
					for(;c<w.size();c++)
					{
						if(c!=i&&(w[c].type==UX_TYPE_FIELD || w[c].type==UX_TYPE_PASS))
						{
							if(sel==-1)
							{
								sel=c;
							}
						}
					}
					if(sel!=-1)
					{
						w[i].state=UX_INACTIVE;
						w[sel].state=UX_ACTIVE;
						Input::SetString(w[sel].label);
					}
				}
			}
			if(w[i].check(x,y))
				return i;

		}
		if(hx==-1 && Input::IsKeyDown(SDLK_MLEFT) && Input::MouseX()>x && Input::MouseX()<x+width && Input::MouseY()>y && Input::MouseY()<y+15) //Dialog Drag Stuff - 15 @ y is titlebar offset
		{
			hx=Input::MouseX()-x;
			hy=Input::MouseY()-y;
		}
		else if(hx!=-1)
		{
			if(Input::IsKeyDown(SDLK_MLEFT))
			{
				x=Input::MouseX()-hx;
				y=Input::MouseY()-hy;
			}
			else 
				hx=-1;
		}
		return -1;
	}
};

