long getItemAtk(long itemid)
{
	cItem *item = itemStruct(itemid);
	return item->atk;
}

long getItemDef(long itemid)
{
	cItem *item = itemStruct(itemid);
	return item->def;
}

long strBonus(long str)
{
	return str / 3;
}

long conBonus(long con)
{
	return con / 4;
}

long missBonus(long dex)
{
	if(rand()%1024 <= 255-(dex*3))
		return 1;
	return 0;
}

long equippedAttack(long index)
{
	long atk=0;
	cPlayer *player = playerStruct(index);
	if(player->eLeft>-1)
		atk+=getItemAtk(player->inventory[player->eLeft]);
	if(player->eRight>-1)
		atk+=getItemAtk(player->inventory[player->eRight]);
	if(player->eHead>-1)
		atk+=getItemAtk(player->inventory[player->eHead]);
	if(player->eBody>-1)
		atk+=getItemAtk(player->inventory[player->eBody]);
	if(player->eSpecial>-1)
		atk+=getItemAtk(player->inventory[player->eSpecial]);
	return atk;
}

long equippedDefense(long index)
{
	long def=0;
	cPlayer *player = playerStruct(index);
	if(player->eLeft>-1)
		def+=getItemDef(player->inventory[player->eLeft]);
	if(player->eRight>-1)
		def+=getItemDef(player->inventory[player->eRight]);
	if(player->eHead>-1)
		def+=getItemDef(player->inventory[player->eHead]);
	if(player->eBody>-1)
		def+=getItemDef(player->inventory[player->eBody]);
	if(player->eSpecial>-1)
		def+=getItemDef(player->inventory[player->eSpecial]);
	return def;
}

long wouldAttack(long index, long victim)
{
	cPlayer *target = playerStruct(victim);
	cPlayer *player = playerStruct(index);
	//calculate damage
	long dmg = (player->atk + equippedAttack(index) + strBonus(player->str)) - (target->def + equippedDefense(victim) + conBonus(target->con));
	//apply randomness
	dmg+=rand()%5-2;
	if(dmg<0)
		dmg=0;
	return dmg;
}