const int OFFSET = 605;
const int STONE_SHOVEL=0 + OFFSET;
const int COPPER_SHOVEL=1 + OFFSET;
const int IRON_SHOVEL=2 + OFFSET;
const int STONE_AXE=3 + OFFSET;
const int COPPER_AXE=4 + OFFSET;
const int IRON_AXE=5 + OFFSET;
const int WOOD=6 + OFFSET;
const int DIRT=7 + OFFSET;
const int STONE_PICKAXE=8 + OFFSET;
const int COPPER_PICKAXE=9 + OFFSET;
const int IRON_PICKAXE=10 + OFFSET;
const int STONE=14 + OFFSET;
const int GOLD=11 + OFFSET;
const int COPPER=13 + OFFSET;
const int IRON=12 + OFFSET;

struct builditem
{
	char name[32];
	int reqitems[10];
	int reqqty[10];
	int giveitem;
	int giveqty;
	int tilemake;
	int tilelayer;
	int tiletype;
};

builditem items[]=
{
//Stone Shovel
{"Stone Shovel",{WOOD,STONE,-1,-1,-1,-1,-1,-1,-1,-1},{30,40,0,0,0,0,0,0,0,0},STONE_SHOVEL,1,-1,-1,-1},
{"Stone Axe",{WOOD,STONE,-1,-1,-1,-1,-1,-1,-1,-1},{30,40,0,0,0,0,0,0,0,0},STONE_AXE,1,-1,-1,-1},
{"Copper Shovel",{WOOD,COPPER,-1,-1,-1,-1,-1,-1,-1,-1},{60,40,0,0,0,0,0,0,0,0},COPPER_SHOVEL,1,-1,-1,-1},
{"Copper Axe",{WOOD,COPPER,-1,-1,-1,-1,-1,-1,-1,-1},{60,40,0,0,0,0,0,0,0,0},COPPER_AXE,1,-1,-1,-1},
{"Iron Shovel",{WOOD,IRON,-1,-1,-1,-1,-1,-1,-1,-1},{90,100,0,0,0,0,0,0,0,0},IRON_SHOVEL,1,-1,-1,-1},
{"Iron Axe",{WOOD,IRON,-1,-1,-1,-1,-1,-1,-1,-1},{90,100,0,0,0,0,0,0,0,0},IRON_AXE,1,-1,-1,-1},
};

int numitems=sizeof(items)/sizeof(builditem);

int takeItems(int id,int amount,int itemid)
{
	int ItemID,Quantity;
	for (int i = 0; i < inventoryLen(); i++)
	{
		ItemID = itemAt(id, i);
		Quantity = qtyAt(id, i);

		if (Quantity == 0)
			continue;

		if(ItemID == itemid && Quantity >= amount)
		{
			setQty(id,i,Quantity-amount);
			return 1;
		}
	}
	return 0;
}

bool canbuild(int id,int build)
{
	for(int i=0;i<10;i++)
	{
		if(items[build].reqitems[i]>-1)
		{
			if(hasItem(id,items[build].reqitems[i]) && qtyAt(id,itemSlot(id,items[build].reqitems[i]))>items[build].reqqty[i])
			{
				continue;
			}
			else
				return 0;
		}
		else
			break;
	}
	return 1;
}

void sendcanbuild(int id)
{
	sendChat("^GYou can build:",id);
	for(int i=0;i<numitems;i++)
	{
		if(canbuild(id,i))
		{
			sendChatf(id,"%s ",items[i].name);
		}
	}
}

void builditem(int id,char item[])
{
	int buildid=-1;

	for(int i=0;i<numitems;i++)
	{

		if(strcmp(items[i].name,item)==0)
		{
			if(canbuild(id,i))
			{
				buildid=i;
				break;
			}
		}
	}
	if(buildid>-1)
	{
		for(int i=0;i<10;i++)
		{
			if(items[buildid].reqitems[i]>-1)
			{
				takeItems(id,items[buildid].reqqty[i],items[buildid].reqitems[i]);
			}
			else
				break;
		}
		makeItem(items[buildid].giveitem,items[buildid].giveqty,getMap(id),getX(id),getY(id));
	}
}


