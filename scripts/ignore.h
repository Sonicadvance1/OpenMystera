

void ignore(int id, char name[256])
{
	cPlayer *player = playerStruct(id);
	char global_name[256];
	char lower_name[256];
	strcpy(lower_name,stringLower(name));
	int last_index = 0;
	do
	{
		sprintf(global_name, "ignore%s%d", player->name,last_index);
		last_index++;
		if(DBisGlobal(global_name))
		{
			if(strcmp(stringLower(DBselectGlobal(global_name)),lower_name) == 0)
			{
				sendChatf(id, "^RYou are already ignoring the chats of %s", name);
				return;
			}
		}
		else
		{
			sendChatf(id, "^GYou are now ignoring the chats of %s", name);
			DBinsertGlobal(global_name,name);
			break;
		}
	}
	while(DBisGlobal(global_name));
}

void unIgnore(int id, char name[256])
{
	cPlayer *player = playerStruct(id);
	char global_name[256];
	char global_value[256];
	char delete_global_name[256];
	char lower_name[256];
	strcpy(lower_name,stringLower(name));
	int delete_index = -1;
	int last_index   = 0;
	do
	{
		sprintf(global_name, "ignore%s%d", player->name,last_index);
		if(DBisGlobal(global_name))
		{
			strcpy(global_value, DBselectGlobal(global_name));
			if(strcmp(stringLower(global_value),lower_name) == 0)
			{
				delete_index = last_index;
				strcpy(delete_global_name,global_name);
			}
			last_index++;
		}
	}
	while(DBisGlobal(global_name));
	if(delete_index > -1)
	{
		sprintf(global_name, "ignore%s%d", player->name,last_index-1);
		DBupdateGlobal(delete_global_name,global_value);
		DBdeleteGlobal(global_name);
		sendChatf(id, "^gYou are no longer ignoring the chats of %s", name);
	}
	else
	{
		sendChatf(id, "^RYou are not ignoring the chats of %s!", name);
	}
}

void unIgnoreAll(int id)
{
	cPlayer *player = playerStruct(id);
	char global_name[256];
	int last_index   = 0;
	do
	{
		sprintf(global_name, "ignore%s%d", player->name,last_index);
		if(DBisGlobal(global_name))
		{
			DBdeleteGlobal(global_name);
			last_index++;
		}
	}
	while(DBisGlobal(global_name));
}
/*void unIgnore(int id, int index)
{
	cPlayer *player = playerStruct(id);
	char global_name[256];
	char global_value[256];
	char delete_global[256];
	char name[256];
	char lower_name[256];
	int delete_index = -1;
	int last_index   = 0;
	do
	{
		sprintf(global_name, "ignore%s%d", player->name,last_index);
		if(DBisGlobal(global_name))
		{
			strcpy(global_value, DBselectGlobal(global_name));
			if(last_index == index - 1)
			{
				delete_index = last_index;
				strcpy(name,global_value);
				strcpy(lower_name,stringLower(name));
				strcpy(delete_global,global_name);
			}
			last_index++;
		}
	}
	while(DBisGlobal(global_name));
	if(delete_index > -1)
	{
		sprintf(global_name, "ignore%s%d", player->name,last_index-1);
		DBupdateGlobal(delete_global,global_value);
		DBdeleteGlobal(global_name);
		sendChatf(id, "^gYou are no longer ignoring the chats of %s", name);
	}
	else
	{
		sendChatf(id, "^RYou are not ignoring that index!");
	}
}*/

bool isIgnored(int id, char name[256])
{
	cPlayer *player = playerStruct(id);
	char global_name[256];
	char lower_name[256];
	strcpy(lower_name,stringLower(name));
	int i = 0;
	do
	{
		sprintf(global_name,"ignore%s%d",player->name,i);
		if(DBisGlobal(global_name))
		{
			if(strcmp(stringLower(DBselectGlobal(global_name)),lower_name) == 0)
			{
				return true;
			}
			i++;
		}
	}
	while(DBisGlobal(global_name));
	return false;
}

void sendIgnoreList(int id)
{
	cPlayer *player = playerStruct(id);
	char global_name[256];
	int last_index = 0;
	do
	{
		sprintf(global_name, "ignore%s%d", player->name,last_index);
		last_index++;
		if(DBisGlobal(global_name))
		{
			sendChatf(id, "^G%d.)^R %s",last_index, DBselectGlobal(global_name));
		}
	}
	while(DBisGlobal(global_name));
	if(last_index == 1)
	{
		sendChatf(id, "^rYou are not ignoring anyone");
	}
}