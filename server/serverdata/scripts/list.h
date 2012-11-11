//Tool for using resizable and serializable lists - James Hamer 2003
/* Usage
cList <int> list(20);
int i=0;FORALL(i,list)
{
	...
}
list.size(10); //resize
*/
#ifndef _LIST_H
#define _LIST_H

#define FORALL(x,y)  for(;x<y.size();x++)

template <class itemType>
class cList
{
public:	 //INTERFACE
	int size(int len)
	{
		//if(len<1)
		//	return length;
		if(list==0)//new list
			list=new itemType[len];
		else//resize
		{
			itemType *tempList = new itemType[len];
			if(len<length)
				for(int iList=0;iList<len;iList++)
					tempList[iList] = list[iList];
			else
				for(int iList=0;iList<length;iList++)
					tempList[iList] = list[iList];
			delete [] list;
			list = tempList;
		}
		length=len;
		return length;
	}
	int size()
	{
		return length;
	}
	cList& operator=(const cList& other)
	{
		if(this!=&other)
		{
			size(other.length);
			for(int i=0;i<length;i++)
				memcpy(&list[i],&other[i],sizeof(itemType));
		}
		return *this;
	}
	itemType *getList()
	{
		return list;
	}
	const itemType & operator [] (int k) const
	{
		return list[k];
	}
	itemType & operator [] (int k)
	{
		return list[k];
	}
	cList()
	{ 
		length=0; 
		list=0; 
	}
	cList(int len)
	{ 
		length=0; 
		list=0; 
		size(len);
	}
	~cList()
	{ 
		if(list!=0)
		{
			delete [] list;
			list=0;
		}
	}
private: //IMPLEMENTATION
	
private: //DATA
	int length;
	itemType *list;
};


template <class itemType>
class cAutoList
{
public:	 //INTERFACE
	int size(int len)
	{
		//if(len<1)
		//	return length;
		if(list==0)//new list
			list=new itemType[len];
		else//resize
		{
			itemType *tempList = new itemType[len];
			if(len<length)
				for(int iList=0;iList<len;iList++)
					tempList[iList] = list[iList];
			else
				for(int iList=0;iList<length;iList++)
					tempList[iList] = list[iList];
			delete [] list;
			list = tempList;
		}
		length=len;
		return length;
	}
	int size()
	{
		return length;
	}
	cList& operator=(const cList& other)
	{
		if(this!=&other)
		{
			size(other.length);
			for(int i=0;i<length;i++)
				memcpy(&list[i],&other[i],sizeof(itemType));
		}
		return *this;
	}
	itemType *getList()
	{
		return list;
	}
	const itemType & operator [] (int k) const
	{
		if(k>=size())
			size(k+1);
		return list[k];
	}
	itemType & operator [] (int k)
	{
		if(k>=size())
			size(k+1);
		return list[k];
	}
	cAutoList()
	{ 
		length=0; 
		list=0; 
	}
	cAutoList(int len)
	{ 
		length=0; 
		list=0; 
		size(len);
	}
	~cAutoList()
	{ 
		if(list!=0)
		{
			delete [] list;
			list=0;
		}
	}
private: //IMPLEMENTATION
	
private: //DATA
	int length;
	itemType *list;
};


#endif