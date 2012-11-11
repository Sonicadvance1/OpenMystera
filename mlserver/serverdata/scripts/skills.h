char WOOD_CHOP[]="WoodChopping";
char WOOD_CHOPEXP[]="WoodChopexp";
char SHOVEL[]="Shovel";
char SHOVEL_EXP[]="Shovelexp";
char MINING[]="Mining";
char MINING_EXP[]="Miningexp";

int getSkill(int id,char skill[])
{
	cPlayer *player=playerStruct(id);
	char dbname[256];
	sprintf(dbname,"%s:%s",player->name,skill);
	if(DBisGlobal(dbname))
	{
		return atoi(DBselectGlobal(dbname));
	}
	return -1;
}
void setSkill(int id,char skill[],int level)
{
	cPlayer *player=playerStruct(id);
	char dbname[256];
	char dbvalue[10];
	sprintf(dbname,"%s:%s",player->name,skill);
	sprintf(dbvalue,"%d",level);
	if(DBisGlobal(dbname))
	{
		DBupdateGlobal(dbname,dbvalue);
	}
	else
	{
		DBinsertGlobal(dbname,dbvalue);
	}
}