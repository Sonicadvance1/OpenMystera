long safeMaps[] = 
{
69
};

long sizeOfSafe = sizeof(safeMaps)/sizeof(long);

bool isSafe(long map)
{
	for(long i = 0;i < sizeOfSafe; i++)
	{
		if(map == safeMaps[i])
			return true;
	}
	return false;
}