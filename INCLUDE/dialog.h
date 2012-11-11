void setupDialogs()
{
	uxWidget wtemp;
	//mapping dialog
	mapDialog.init(640,0,160,464,"Map 0");
	mapDialog.hotkey=0;
	wtemp.set(UX_TYPE_BUTTON,16,424,64,16,"Layer:0");//0
	mapDialog.add(wtemp);
	wtemp.set(UX_TYPE_BUTTON,80,424,64,16,"Single:0");//1
	mapDialog.add(wtemp);
	wtemp.set(UX_TYPE_BUTTON,16,440,64,16,"Upload");//2
	mapDialog.add(wtemp);
	wtemp.set(UX_TYPE_BUTTON,80,440,64,16,"Title");//3
	mapDialog.add(wtemp);
	wtemp.set(UX_TYPE_BUTTON,56,376,48,16,"N:0");//4
	mapDialog.add(wtemp);
	wtemp.set(UX_TYPE_BUTTON,56,408,48,16,"S:0");//5
	mapDialog.add(wtemp);
	wtemp.set(UX_TYPE_BUTTON,16,392,48,16,"W:0");//6
	mapDialog.add(wtemp);
	wtemp.set(UX_TYPE_BUTTON,96,392,48,16,"E:0");//7
	mapDialog.add(wtemp);
	wtemp.set(UX_TYPE_BUTTON,112,312,32,16,"Copy");//8
	mapDialog.add(wtemp);
	wtemp.set(UX_TYPE_BUTTON,112,328,32,16,"Paste");//9
	mapDialog.add(wtemp);
	wtemp.set(UX_TYPE_BUTTON,16,360,32,16,"Wall");//10
	mapDialog.add(wtemp);
	wtemp.set(UX_TYPE_BUTTON,48,360,32,16,"Keep");//11
	mapDialog.add(wtemp);
	wtemp.set(UX_TYPE_BUTTON,80,360,32,16,"Npc");//12
	mapDialog.add(wtemp);
	wtemp.set(UX_TYPE_BUTTON,112,360,32,16,"Swch");//13
	mapDialog.add(wtemp);
	wtemp.set(UX_TYPE_BUTTON,80,344,32,16,"Warp");//14
	mapDialog.add(wtemp);
	wtemp.set(UX_TYPE_BUTTON,112,344,32,16,"Scpt");//15
	mapDialog.add(wtemp);
	wtemp.set(UX_TYPE_BUTTON,16,344,64,16,"None");//16
	mapDialog.add(wtemp);
	wtemp.set(UX_TYPE_BUTTON,16,280,48,16,"N-1");//17
	mapDialog.add(wtemp);
	wtemp.set(UX_TYPE_BUTTON,16,296,48,16,"N-1");//18
	mapDialog.add(wtemp);
	wtemp.set(UX_TYPE_BUTTON,16,312,48,16,"N-1");//19
	mapDialog.add(wtemp);
	wtemp.set(UX_TYPE_BUTTON,16,328,48,16,"N-1");//20
	mapDialog.add(wtemp);
	wtemp.set(UX_TYPE_BUTTON,64,280,48,16,"Q0");//21
	mapDialog.add(wtemp);
	wtemp.set(UX_TYPE_BUTTON,64,296,48,16,"Q0");//22
	mapDialog.add(wtemp);
	wtemp.set(UX_TYPE_BUTTON,64,312,48,16,"Q0");//23
	mapDialog.add(wtemp);
	wtemp.set(UX_TYPE_BUTTON,64,328,48,16,"Q0");//24
	mapDialog.add(wtemp);
	wtemp.set(UX_TYPE_BUTTON,16,456,64,16,"Music:0");//25
	mapDialog.add(wtemp);
	wtemp.set(UX_TYPE_BUTTON,80,456,64,16,"Light:0");//26
	mapDialog.add(wtemp);
	//server selection
	vDialog[0].init(48,112,544,176,"Select a world to join");
	wtemp.set(UX_TYPE_BUTTON,192,150,64,16,"Join");
	vDialog[0].add(wtemp);
	wtemp.set(UX_TYPE_BUTTON,272,150,64,16,"Exit");
	vDialog[0].add(wtemp);
	wtemp.set(UX_TYPE_LISTBOX,48,48,448,96,"");
	vDialog[0].add(wtemp);
	//login screen
	vDialog[1].init(160,112,320,144,"Login");
	wtemp.set(UX_TYPE_BUTTON,48,112,64,16,"Login");
	vDialog[1].add(wtemp);
	wtemp.set(UX_TYPE_BUTTON,128,112,64,16,"Create");
	vDialog[1].add(wtemp);
	wtemp.set(UX_TYPE_BUTTON,208,112,64,16,"Cancel");
	vDialog[1].add(wtemp);
	wtemp.set(UX_TYPE_LABEL,48,42,128,20,"Account ID");
	vDialog[1].add(wtemp);
	wtemp.set(UX_TYPE_LABEL,48,77,128,20,"Password");
	vDialog[1].add(wtemp);
	wtemp.set(UX_TYPE_FIELD,128,40,128,20,"");
	vDialog[1].add(wtemp);
	wtemp.set(UX_TYPE_PASS,128,75,128,20,"");
	vDialog[1].add(wtemp);
	//training
	vDialog[2].init(500,0,144,256,"Train");
	wtemp.set(UX_TYPE_LABEL,16,25,100,20,"Points Left:#");
	vDialog[2].add(wtemp);
	wtemp.set(UX_TYPE_LABEL,16,50,50,20,"STR #");
	vDialog[2].add(wtemp);
	wtemp.set(UX_TYPE_LABEL,16,85,50,20,"DEX #");
	vDialog[2].add(wtemp);
	wtemp.set(UX_TYPE_LABEL,16,120,50,20,"CON #");
	vDialog[2].add(wtemp);
	wtemp.set(UX_TYPE_LABEL,16,155,50,20,"INT #");
	vDialog[2].add(wtemp);
	wtemp.set(UX_TYPE_LABEL,16,190,50,20,"WIS #");
	vDialog[2].add(wtemp);
	wtemp.set(UX_TYPE_BUTTON,48,225,64,20,"OK");
	vDialog[2].add(wtemp);
	wtemp.set(UX_TYPE_BUTTON,80,50,32,20,"+1");
	vDialog[2].add(wtemp);
	wtemp.set(UX_TYPE_BUTTON,80,85,32,20,"+1");
	vDialog[2].add(wtemp);
	wtemp.set(UX_TYPE_BUTTON,80,120,32,20,"+1");
	vDialog[2].add(wtemp);
	wtemp.set(UX_TYPE_BUTTON,80,155,32,20,"+1");
	vDialog[2].add(wtemp);
	wtemp.set(UX_TYPE_BUTTON,80,190,32,20,"+1");
	vDialog[2].add(wtemp);
	//account creation
	vDialog[3].init(64,128,512,144,"Account Creation");
	wtemp.set(UX_TYPE_BUTTON,256,STDH*3+10,80,20,"Create");
	vDialog[3].add(wtemp);
	wtemp.set(UX_TYPE_BUTTON,360,STDH*3+10,80,20,"Cancel");
	vDialog[3].add(wtemp);
	wtemp.set(UX_TYPE_LABEL,40,42,220,20,"Email");
	vDialog[3].add(wtemp);
	wtemp.set(UX_TYPE_LABEL,40,77,120,20,"Password");
	vDialog[3].add(wtemp);
	wtemp.set(UX_TYPE_LABEL,256,77,120,20,"Confirm");
	vDialog[3].add(wtemp);
	wtemp.set(UX_TYPE_FIELD,120,40,320,20,"");
	vDialog[3].add(wtemp);
	wtemp.set(UX_TYPE_PASS,120,75,112,20,"");
	vDialog[3].add(wtemp);
	wtemp.set(UX_TYPE_PASS,328,75,112,20,"");
	vDialog[3].add(wtemp);
	//character creation
	vDialog[4].init(170,100,352,320,"Character Creation");
	wtemp.set(UX_TYPE_LABEL,40,162,120,20,"Body");
	vDialog[4].add(wtemp);
	wtemp.set(UX_TYPE_LABEL,40,162+35,120,20,"Clothes");
	vDialog[4].add(wtemp);
	wtemp.set(UX_TYPE_LABEL,40,162+70,120,20,"Hair");
	vDialog[4].add(wtemp);
	wtemp.set(UX_TYPE_BUTTON,192,297,64,20,"Create");
	vDialog[4].add(wtemp);
	wtemp.set(UX_TYPE_BUTTON,272,297,64,20,"Cancel");
	vDialog[4].add(wtemp);
	wtemp.set(UX_TYPE_BUTTON,120,162,32,20,"<");
	vDialog[4].add(wtemp);
	wtemp.set(UX_TYPE_BUTTON,192,162,32,20,">");
	vDialog[4].add(wtemp);
	wtemp.set(UX_TYPE_BUTTON,120,162+35,32,20,"<");
	vDialog[4].add(wtemp);
	wtemp.set(UX_TYPE_BUTTON,192,162+35,32,20,">");
	vDialog[4].add(wtemp);
	wtemp.set(UX_TYPE_BUTTON,120,162+70,32,20,"<");
	vDialog[4].add(wtemp);
	wtemp.set(UX_TYPE_BUTTON,192,162+70,32,20,">");
	vDialog[4].add(wtemp);
	wtemp.set(UX_TYPE_LABEL,40,162+105,120,20,"Name");
	vDialog[4].add(wtemp);
	wtemp.set(UX_TYPE_FIELD,120,162+105,160,20,"");
	vDialog[4].add(wtemp);
	//drop amount
	vDialog[5].init(320,112,256,80,"Drop How Much?");
	wtemp.set(UX_TYPE_BUTTON,112,64,48,16,"Drop");
	vDialog[5].add(wtemp);
	wtemp.set(UX_TYPE_BUTTON,176,64,48,16,"Cancel");
	vDialog[5].add(wtemp);
	wtemp.set(UX_TYPE_FIELD,32,32,192,20,"");
	vDialog[5].add(wtemp);
	//character selection
	vDialog[6].init(48,100,528,224,"Character Selection");
	wtemp.set(UX_TYPE_BUTTON,24,196,48,16,"");
	vDialog[6].add(wtemp);
	wtemp.set(UX_TYPE_BUTTON,152,196,48,16,"");
	vDialog[6].add(wtemp);
	wtemp.set(UX_TYPE_BUTTON,280,196,48,16,"");
	vDialog[6].add(wtemp);
	wtemp.set(UX_TYPE_BUTTON,408,196,48,16,"");
	vDialog[6].add(wtemp);
	wtemp.set(UX_TYPE_LABEL,24,24,48,16,"Character 1");
	vDialog[6].add(wtemp);
	wtemp.set(UX_TYPE_LABEL,152,24,48,16,"Character 2");
	vDialog[6].add(wtemp);
	wtemp.set(UX_TYPE_LABEL,280,24,48,16,"Character 3");
	vDialog[6].add(wtemp);
	wtemp.set(UX_TYPE_LABEL,408,24,48,16,"Character 4");
	vDialog[6].add(wtemp);
	//jukebox dialog
	vDialog[7].init(230,100,160,128,"Music Options");
	wtemp.set(UX_TYPE_LABEL,25,25,16,20,"Music Power: #");
	vDialog[7].add(wtemp);
	wtemp.set(UX_TYPE_BUTTON,30,43,32,20,"On");
	vDialog[7].add(wtemp);
	wtemp.set(UX_TYPE_BUTTON,98,43,32,20,"Off");
	vDialog[7].add(wtemp);
	wtemp.set(UX_TYPE_BUTTON,48,116,64,20,"Ok");
	vDialog[7].add(wtemp);
	wtemp.set(UX_TYPE_LABEL,25,68,16,20,"Sound Power: #");
	vDialog[7].add(wtemp);
	wtemp.set(UX_TYPE_BUTTON,30,86,32,20,"On");
	vDialog[7].add(wtemp);
	wtemp.set(UX_TYPE_BUTTON,98,86,32,20,"Off");
	vDialog[7].add(wtemp);
	//Trade Window
	vDialog[8].init(30,20,320,400,"Trade Menu");
	wtemp.set(UX_TYPE_BUTTON,128,385,64,20,"OK");
	vDialog[8].add(wtemp);

	wtemp.set(UX_TYPE_IBOX,5,32,32,32,"");
	vDialog[8].add(wtemp);
	wtemp.set(UX_TYPE_IBOX,5,64,32,32,"");
	vDialog[8].add(wtemp);
	wtemp.set(UX_TYPE_IBOX,5,96,32,32,"");
	vDialog[8].add(wtemp);
	wtemp.set(UX_TYPE_IBOX,5,128,32,32,"");
	vDialog[8].add(wtemp);
	wtemp.set(UX_TYPE_IBOX,5,160,32,32,"");
	vDialog[8].add(wtemp);
	wtemp.set(UX_TYPE_IBOX,5,192,32,32,"");
	vDialog[8].add(wtemp);
	wtemp.set(UX_TYPE_IBOX,5,224,32,32,"");
	vDialog[8].add(wtemp);
	wtemp.set(UX_TYPE_IBOX,5,256,32,32,"");
	vDialog[8].add(wtemp);
	wtemp.set(UX_TYPE_IBOX,5,288,32,32,"");
	vDialog[8].add(wtemp);
	wtemp.set(UX_TYPE_IBOX,5,320,32,32,"");
	vDialog[8].add(wtemp);

	wtemp.set(UX_TYPE_SLABEL,37,40,300,32,"");
	vDialog[8].add(wtemp);
	wtemp.set(UX_TYPE_SLABEL,37,72,300,32,"");
	vDialog[8].add(wtemp);
	wtemp.set(UX_TYPE_SLABEL,37,104,300,32,"");
	vDialog[8].add(wtemp);
	wtemp.set(UX_TYPE_SLABEL,37,136,300,32,"");
	vDialog[8].add(wtemp);
	wtemp.set(UX_TYPE_SLABEL,37,168,300,32,"");
	vDialog[8].add(wtemp);
	wtemp.set(UX_TYPE_SLABEL,37,200,300,32,"");
	vDialog[8].add(wtemp);
	wtemp.set(UX_TYPE_SLABEL,37,232,300,32,"");
	vDialog[8].add(wtemp);
	wtemp.set(UX_TYPE_SLABEL,37,264,300,32,"");
	vDialog[8].add(wtemp);
	wtemp.set(UX_TYPE_SLABEL,37,296,300,32,"");
	vDialog[8].add(wtemp);
	wtemp.set(UX_TYPE_SLABEL,37,328,300,32,"");
	vDialog[8].add(wtemp);

	wtemp.set(UX_TYPE_ITEM,5,32,32,32,"");
	vDialog[8].add(wtemp);
	wtemp.set(UX_TYPE_ITEM,5,64,32,32,"");
	vDialog[8].add(wtemp);
	wtemp.set(UX_TYPE_ITEM,5,96,32,32,"");
	vDialog[8].add(wtemp);
	wtemp.set(UX_TYPE_ITEM,5,128,32,32,"");
	vDialog[8].add(wtemp);
	wtemp.set(UX_TYPE_ITEM,5,160,32,32,"");
	vDialog[8].add(wtemp);
	wtemp.set(UX_TYPE_ITEM,5,192,32,32,"");
	vDialog[8].add(wtemp);
	wtemp.set(UX_TYPE_ITEM,5,224,32,32,"");
	vDialog[8].add(wtemp);
	wtemp.set(UX_TYPE_ITEM,5,256,32,32,"");
	vDialog[8].add(wtemp);
	wtemp.set(UX_TYPE_ITEM,5,288,32,32,"");
	vDialog[8].add(wtemp);
	wtemp.set(UX_TYPE_ITEM,5,320,32,32,"");
	vDialog[8].add(wtemp);

	wtemp.set(UX_TYPE_LABEL,220,390,10,5,"Qty:");
	vDialog[8].add(wtemp);
	wtemp.set(UX_TYPE_FIELD,260,385,48,20,"1");
	vDialog[8].add(wtemp);

	//Character Pane
	vDialog[9].init(105,45,272,400,"Character Info");
	wtemp.set(UX_TYPE_BUTTON,168,385,64,20,"OK");//0
	vDialog[9].add(wtemp);

	wtemp.set(UX_TYPE_LABEL,80,25,20,5,"Name:");//1
	vDialog[9].add(wtemp);
	wtemp.set(UX_TYPE_LABEL,80,45,10,5,"Level:");//2
	vDialog[9].add(wtemp);
	wtemp.set(UX_TYPE_LABEL,120,25,50,5,"EMPTY");//3
	vDialog[9].add(wtemp);
	wtemp.set(UX_TYPE_LABEL,120,45,10,5,"0");//4
	vDialog[9].add(wtemp);

	wtemp.set(UX_TYPE_LABEL,15,80,18,5,"Base Stats");//5
	vDialog[9].add(wtemp);
	wtemp.set(UX_TYPE_IBOX,10,95,80,112,"");//6
	vDialog[9].add(wtemp);
	wtemp.set(UX_TYPE_LABEL,12,105,10,5,"STR:");//7
	vDialog[9].add(wtemp);
	wtemp.set(UX_TYPE_LABEL,12,125,10,5,"DEX:");//8
	vDialog[9].add(wtemp);
	wtemp.set(UX_TYPE_LABEL,12,145,10,5,"CON:");//9
	vDialog[9].add(wtemp);
	wtemp.set(UX_TYPE_LABEL,12,165,10,5,"INT:");//10
	vDialog[9].add(wtemp);
	wtemp.set(UX_TYPE_LABEL,12,185,10,5,"WIS:");//11
	vDialog[9].add(wtemp);
	wtemp.set(UX_TYPE_LABEL,52,105,10,5,"0");//12
	vDialog[9].add(wtemp);
	wtemp.set(UX_TYPE_LABEL,52,125,10,5,"0");//13
	vDialog[9].add(wtemp);
	wtemp.set(UX_TYPE_LABEL,52,145,10,5,"0");//14
	vDialog[9].add(wtemp);
	wtemp.set(UX_TYPE_LABEL,52,165,10,5,"0");//15
	vDialog[9].add(wtemp);
	wtemp.set(UX_TYPE_LABEL,52,185,10,5,"0");//16
	vDialog[9].add(wtemp);

	wtemp.set(UX_TYPE_LABEL,157,80,18,5,"Resistances");//17
	vDialog[9].add(wtemp);
	wtemp.set(UX_TYPE_IBOX,152,95,112,128,"");//18
	vDialog[9].add(wtemp);
	wtemp.set(UX_TYPE_LABEL,154,105,10,5,"FIRE:");//19
	vDialog[9].add(wtemp);
	wtemp.set(UX_TYPE_LABEL,154,125,10,5,"ICE:");//20
	vDialog[9].add(wtemp);
	wtemp.set(UX_TYPE_LABEL,154,145,10,5,"ELECRIC:");//21
	vDialog[9].add(wtemp);
	wtemp.set(UX_TYPE_LABEL,154,165,10,5,"PHYSICAL:");//22
	vDialog[9].add(wtemp);
	wtemp.set(UX_TYPE_LABEL,154,185,10,5,"POISON:");//23
	vDialog[9].add(wtemp);
	wtemp.set(UX_TYPE_LABEL,154,205,10,5,"MAGIC:");//24
	vDialog[9].add(wtemp);
	wtemp.set(UX_TYPE_LABEL,224,105,10,5,"0");//25
	vDialog[9].add(wtemp);
	wtemp.set(UX_TYPE_LABEL,224,125,10,5,"0");//26
	vDialog[9].add(wtemp);
	wtemp.set(UX_TYPE_LABEL,224,145,10,5,"0");//27
	vDialog[9].add(wtemp);
	wtemp.set(UX_TYPE_LABEL,224,165,10,5,"0");//28
	vDialog[9].add(wtemp);
	wtemp.set(UX_TYPE_LABEL,224,185,10,5,"0");//29
	vDialog[9].add(wtemp);
	wtemp.set(UX_TYPE_LABEL,224,205,10,5,"0");//30
	vDialog[9].add(wtemp);

	wtemp.set(UX_TYPE_LABEL,15,235,18,5,"Experience");//31
	vDialog[9].add(wtemp);
	wtemp.set(UX_TYPE_IBOX,10,250,128,96,"");//32
	vDialog[9].add(wtemp);
	wtemp.set(UX_TYPE_LABEL,12,260,10,5,"EXP:");//33
	vDialog[9].add(wtemp);
	wtemp.set(UX_TYPE_LABEL,12,280,10,5,"TNL:");//34
	vDialog[9].add(wtemp);
	wtemp.set(UX_TYPE_LABEL,42,260,10,5,"0");//35
	vDialog[9].add(wtemp);
	wtemp.set(UX_TYPE_LABEL,42,280,10,5,"0");//36
	vDialog[9].add(wtemp);

	wtemp.set(UX_TYPE_LABEL,152,235,18,5,"Player Combat");//37
	vDialog[9].add(wtemp);
	wtemp.set(UX_TYPE_IBOX,150,250,96,64,"");//38
	vDialog[9].add(wtemp);
	wtemp.set(UX_TYPE_LABEL,152,257,10,5,"Flag");//39
	vDialog[9].add(wtemp);
	wtemp.set(UX_TYPE_LABEL,152,277,10,5,"Kills:");//40
	vDialog[9].add(wtemp);
	wtemp.set(UX_TYPE_LABEL,152,297,10,5,"Honor:");//41
	vDialog[9].add(wtemp);
	wtemp.set(UX_TYPE_LABEL,182,277,10,5,"0");//42
	vDialog[9].add(wtemp);
	wtemp.set(UX_TYPE_LABEL,192,297,10,5,"0");//43
	vDialog[9].add(wtemp);

	wtemp.set(UX_TYPE_LABEL,12,300,10,5,"Kills:");//44
	vDialog[9].add(wtemp);
	wtemp.set(UX_TYPE_LABEL,45,300,10,5,"0");//45
	vDialog[9].add(wtemp);
	wtemp.set(UX_TYPE_LABEL,12,320,10,5,"Deaths:");//46
	vDialog[9].add(wtemp);
	wtemp.set(UX_TYPE_LABEL,58,320,10,5,"0");//47
	vDialog[9].add(wtemp);
	wtemp.set(UX_TYPE_PLYR,20,20,32,128,"");//48
	vDialog[9].add(wtemp);
	wtemp.set(UX_TYPE_ITEM,203,23,16,16,"");//49
	vDialog[9].add(wtemp);
	wtemp.set(UX_TYPE_LABEL,215,25,10,5,":0");//50
	vDialog[9].add(wtemp);
	wtemp.set(UX_TYPE_ITEM,205,43,16,16,"");//51
	vDialog[9].add(wtemp);
	wtemp.set(UX_TYPE_LABEL,215,45,10,5,":0");//52
	vDialog[9].add(wtemp);

	//NPC Window
	vDialog[10].init(105,45,272,272,"NPC Info");
	wtemp.set(UX_TYPE_BUTTON,168,257,64,20,"OK");//0
	vDialog[10].add(wtemp);

	wtemp.set(UX_TYPE_LABEL,80,25,20,5,"Name:");//1
	vDialog[10].add(wtemp);
	wtemp.set(UX_TYPE_LABEL,120,25,50,5,"EMPTY");//2
	vDialog[10].add(wtemp);
	wtemp.set(UX_TYPE_LABEL,80,45,20,5,"HP:");//3
	vDialog[10].add(wtemp);
	wtemp.set(UX_TYPE_LABEL,120,45,50,5,"0/0");//4
	vDialog[10].add(wtemp);

	wtemp.set(UX_TYPE_LABEL,15,80,18,5,"Stats");//5
	vDialog[10].add(wtemp);
	wtemp.set(UX_TYPE_IBOX,10,95,96,96,"");//6
	vDialog[10].add(wtemp);
	wtemp.set(UX_TYPE_LABEL,12,110,10,5,"ATK:");//7
	vDialog[10].add(wtemp);
	wtemp.set(UX_TYPE_LABEL,12,130,10,5,"DEF:");//8
	vDialog[10].add(wtemp);
	wtemp.set(UX_TYPE_LABEL,12,150,10,5,"AGG:");//9
	vDialog[10].add(wtemp);
	wtemp.set(UX_TYPE_LABEL,12,170,10,5,"EXP:");//10
	vDialog[10].add(wtemp);
	wtemp.set(UX_TYPE_LABEL,52,110,10,5,"0");//11
	vDialog[10].add(wtemp);
	wtemp.set(UX_TYPE_LABEL,52,130,10,5,"0");//12
	vDialog[10].add(wtemp);
	wtemp.set(UX_TYPE_LABEL,52,150,10,5,"No");//13
	vDialog[10].add(wtemp);
	wtemp.set(UX_TYPE_LABEL,52,170,10,5,"0");//14
	vDialog[10].add(wtemp);

	wtemp.set(UX_TYPE_LABEL,157,80,18,5,"Resistances");//15
	vDialog[10].add(wtemp);
	wtemp.set(UX_TYPE_IBOX,152,95,112,128,"");//16
	vDialog[10].add(wtemp);
	wtemp.set(UX_TYPE_LABEL,154,105,10,5,"FIRE:");//17
	vDialog[10].add(wtemp);
	wtemp.set(UX_TYPE_LABEL,154,125,10,5,"ICE:");//18
	vDialog[10].add(wtemp);
	wtemp.set(UX_TYPE_LABEL,154,145,10,5,"ELECTRIC:");//19
	vDialog[10].add(wtemp);
	wtemp.set(UX_TYPE_LABEL,154,165,10,5,"PHYSICAL:");//20
	vDialog[10].add(wtemp);
	wtemp.set(UX_TYPE_LABEL,154,185,10,5,"POISON:");//21
	vDialog[10].add(wtemp);
	wtemp.set(UX_TYPE_LABEL,154,205,10,5,"MAGIC:");//22
	vDialog[10].add(wtemp);
	wtemp.set(UX_TYPE_LABEL,224,105,10,5,"0");//23
	vDialog[10].add(wtemp);
	wtemp.set(UX_TYPE_LABEL,224,125,10,5,"0");//24
	vDialog[10].add(wtemp);
	wtemp.set(UX_TYPE_LABEL,224,145,10,5,"0");//25
	vDialog[10].add(wtemp);
	wtemp.set(UX_TYPE_LABEL,224,165,10,5,"0");//26
	vDialog[10].add(wtemp);
	wtemp.set(UX_TYPE_LABEL,224,185,10,5,"0");//27
	vDialog[10].add(wtemp);
	wtemp.set(UX_TYPE_LABEL,224,205,10,5,"0");//28
	vDialog[10].add(wtemp);
	wtemp.set(UX_TYPE_PLYR,20,20,32,128,"");//29
	vDialog[10].add(wtemp);



	//set default text fields
	for(int i=0,c=0;i<8;i++)
		for(c=0;c<vDialog[i].w.size();c++)
		{
			if(vDialog[i].w[c].type==UX_TYPE_FIELD||vDialog[i].w[c].type==UX_TYPE_PASS)
			{
				vDialog[i].w[c].state=UX_ACTIVE;
				c=vDialog[i].w.size();
			}
		}

}

void mapEvent(int item)
{
	if(item==0)
	{
		layer++;
		if(layer>3)
			layer=0;
		sprintf(mapDialog.w[0].label,"Layer:%d",layer);
	}
	else if(item==1)
	{
		if(slayer==1)
			slayer=0;
		else slayer=1;
		sprintf(mapDialog.w[1].label,"Single:%d",slayer);
	}
	else if(item==2)
	{
		world[MYGUY.p.map].setAllVacant();
		world[MYGUY.p.map].version++;
		MAKE_MSG(upld_msg,reply,UPLD_MSG);
		char buf[5000];
		unsigned long len=sizeof(cMap);
		compress ((unsigned char *)&buf+sizeof(upld_msg), &len, (unsigned char *)&world[MYGUY.p.map], (unsigned long)len);
		reply.size=(unsigned short)len;
		memcpy(buf,(void *)&reply,sizeof(upld_msg));//store header
		nc.send((unsigned char *)&buf,sizeof(upld_msg)+len,SEND_GUARANTEED);
		term.newLine("Map uploaded.");
		SDL_WM_SetCaption(world[MYGUY.p.map].name, "ORCB");
		if(curMidi!=world[MYGUY.p.map].npc[4].index)
			playMidi(world[MYGUY.p.map].npc[4].index);
	}
	else if(item==3)
	{
		chatting=1;
		strcpy(inputStr,"/map_title ");
		curPos = strlen(inputStr);
	}
	else if(item==4)
	{
		chatting=1;
		strcpy(inputStr,"/map_north ");
		curPos = strlen(inputStr);
	}
	else if(item==5)
	{
		chatting=1;
		strcpy(inputStr,"/map_south ");
		curPos = strlen(inputStr);
	}
	else if(item==6)
	{
		chatting=1;
		strcpy(inputStr,"/map_west ");
		curPos = strlen(inputStr);
	}
	else if(item==7)
	{
		chatting=1;
		strcpy(inputStr,"/map_east ");
		curPos = strlen(inputStr);
	}
	else if(item==8)
	{
		copyMap=world[MYGUY.p.map];
		term.newLine("Map copied.");
	}
	else if(item==9)
	{
		world[MYGUY.p.map]=copyMap;
		term.newLine("Map pasted.");
	}
	else if(item==10)
	{
		curTile = -99;//wall
	}
	else if(item==11)
	{
		curTile = -94;//keep
	}
	else if(item==12)
	{
		curTile = -97;//npc
	}
	else if(item==13)
	{
		curTile = -95;//switch
		chatting=1;
		strcpy(inputStr,"/map_switch ");
		curPos = strlen(inputStr);
	}
	else if(item==14)
	{
		curTile = -98;//warp
		chatting=1;
		strcpy(inputStr,"/map_warp ");
		curPos = strlen(inputStr);
	}
	else if(item==15)
	{
		curTile = -96;//script
		chatting=1;
		strcpy(inputStr,"/map_script ");
		curPos = strlen(inputStr);
	}
	else if(item==16)
	{
		curTile = -100;//none
	}
	else if(item==17)
	{
		chatting=1;
		strcpy(inputStr,"/map_npc1 ");
		curPos = strlen(inputStr);
	}
	else if(item==18)
	{
		chatting=1;
		strcpy(inputStr,"/map_npc2 ");
		curPos = strlen(inputStr);
	}
	else if(item==19)
	{
		
		chatting=1;
		strcpy(inputStr,"/map_npc3 ");
		curPos = strlen(inputStr);
		
	}
	else if(item==20)
	{
		
		chatting=1;
		strcpy(inputStr,"/map_npc4 ");
		curPos = strlen(inputStr);
		
	}
	else if(item==21)
	{
		
		chatting=1;
		strcpy(inputStr,"/map_qty1 ");
		curPos = strlen(inputStr);
		
	}
	else if(item==22)
	{
		
		chatting=1;
		strcpy(inputStr,"/map_qty2 ");
		curPos = strlen(inputStr);
		
	}
	else if(item==23)
	{
		
		chatting=1;
		strcpy(inputStr,"/map_qty3 ");
		curPos = strlen(inputStr);
		
	}
	else if(item==24)
	{
		
		chatting=1;
		strcpy(inputStr,"/map_qty4 ");
		curPos = strlen(inputStr);
		
	}
	else if(item==25)
	{
		
		chatting=1;
		strcpy(inputStr,"/map_music ");
		curPos = strlen(inputStr);
		
	}
	else if(item==26)
	{
		
		chatting=1;
		strcpy(inputStr,"/map_light ");
		curPos = strlen(inputStr);
		
	}
}

void dialogEvent(int item)
{
	if(dialog==0)
	{
		if(item==0)
		{
			//dialog=-1;
			//char show[128];
			cstate=1;
			char _ip[32];
			sscanf(sips[vDialog[0].w[2].selected].ip,"%s",&_ip);
			//strcpy(_ip,sips[vDialog[0].w[2].selected].ip);
			//.term.newLine("connecting to %s %d",_ip,SERVER_PORT);
			//sprintf(show,"--- Attempting to connect to %s...",_ip);
			/*strcpy(show,"--- Attempting to connect...");
			term.newLine(show);
			term.render(0,480,246);
			SDL_GL_SwapBuffers();*/
			if(!nc.connect(_ip,SERVER_PORT))
				term.newLine("--- Error connecting.");
			else
			{
				term.newLine("--- Connected [%s]",_ip);
				connected=1;
				packetTimer.reset();
			}
		}
		if(item==1)
			done=1;
	}
	else if(dialog==1)
	{
		if(item==0)
		{
			MAKE_MSG(algn_msg,msg,ALGN_MSG);
			memcpy(msg.id,vDialog[1].w[5].label,7);
			msg.id[7]='\0';
			strcpy(msg.pass,vDialog[1].w[6].label);
			nc.send((unsigned char *)&msg,sizeof(algn_msg),SEND_GUARANTEED);
			resetStringInput();
		}
		else if(item==1)
		{
			dialog=3;
		}
		else if(item==2)
		{
			nc.shutdown();
			dialog=0;
		}
	}
	else if(dialog==2)
	{
		if(item==6)
			dialog=-1;
		else if(item==7)
		{
			if(MYGUY.train>0)
			{
				sprintf(vDialog[2].w[0].label,"Points Left:%d",MYGUY.train-1);
				sprintf(vDialog[2].w[1].label,"STR %d",MYGUY.str+1);
			}
			char temp[256];
			sprintf(temp,"/train str");
			sendCmndMsg(temp);
		}
		else if(item==8)
		{
			if(MYGUY.train>0)
			{
				sprintf(vDialog[2].w[0].label,"Points Left:%d",MYGUY.train-1);
				sprintf(vDialog[2].w[2].label,"DEX %d",MYGUY.dex+1);
			}
			char temp[256];
			sprintf(temp,"/train dex");
			sendCmndMsg(temp);
		}
		else if(item==9)
		{
			if(MYGUY.train>0)
			{
				sprintf(vDialog[2].w[0].label,"Points Left:%d",MYGUY.train-1);
				sprintf(vDialog[2].w[3].label,"CON %d",MYGUY.con+1);
			}
			char temp[256];
			sprintf(temp,"/train con");
			sendCmndMsg(temp);
		}
		else if(item==10)
		{
			if(MYGUY.train>0)
			{
				sprintf(vDialog[2].w[0].label,"Points Left:%d",MYGUY.train-1);
				sprintf(vDialog[2].w[4].label,"INT %d",MYGUY.itl+1);
			}
			char temp[256];
			sprintf(temp,"/train int");
			sendCmndMsg(temp);
		}
		else if(item==11)
		{
			if(MYGUY.train>0)
			{
				sprintf(vDialog[2].w[0].label,"Points Left:%d",MYGUY.train-1);
				sprintf(vDialog[2].w[5].label,"WIS %d",MYGUY.wis+1);
			}
			char temp[256];
			sprintf(temp,"/train wis");
			sendCmndMsg(temp);
		}
	}
	else if(dialog==3)//new account
	{
		if(item==1)
		{
			dialog=1;
			resetStringInput();
		}
		else if(item==0)
		{
			//send new account information
			MAKE_MSG(nwac_msg,temp,NWAC_MSG);
			strcpy(temp.email,vDialog[3].w[5].label);
			strcpy(temp.pass,vDialog[3].w[6].label);
			strcpy(temp.conf,vDialog[3].w[7].label);
			nc.send((unsigned char *)&temp,sizeof(nwac_msg),SEND_GUARANTEED);
			resetStringInput();
		}
	}
	else if(dialog==4)//new character
	{
		if(item==3)
		{
			MAKE_MSG(nchr_msg,temp,NCHR_MSG);
			strcpy(temp.name,vDialog[4].w[12].label);
			temp.slot=newSlot;
			temp.body=bodySel;
			temp.hair=hairSel;
			temp.clothes=clothesSel;
			nc.send((unsigned char *)&temp,sizeof(nchr_msg),SEND_GUARANTEED);
			resetStringInput();
		}
		else if(item==4)
		{
			dialog=6;
			resetStringInput();
		}
		else if(item==5)
		{
			bodySel--;
			if(bodySel<0)
				bodySel=bodyMax-1;
		}
		else if(item==6)
		{
			bodySel++;
			if(bodySel==bodyMax)
				bodySel=0;
		}
		else if(item==7)
		{
			clothesSel--;
			if(clothesSel<0)
				clothesSel=clothesMax-1;
		}
		else if(item==8)
		{
			clothesSel++;
			if(clothesSel==clothesMax)
				clothesSel=0;
		}
		else if(item==9)
		{
			hairSel--;
			if(hairSel<0)
				hairSel=hairMax-1;
		}
		else if(item==10)
		{
			hairSel++;
			if(hairSel==hairMax)
				hairSel=0;
		}
	}
	else if(dialog==5)
	{
		if(item==0)
		{
			char dropn[256];
			int dropqty = atoi(vDialog[5].w[2].label);
			if(dropqty>=MYGUY.item[dropSlot].qty)
			{
				MAKE_MSG(drop_msg,msg,DROP_MSG);
				msg.index=dropSlot;
				nc.send((unsigned char *)&msg,sizeof(drop_msg),SEND_GUARANTEED);
			}
			else
			{
				sprintf(dropn,"/drop %d %d",dropSlot+1,dropqty);
				sendCmndMsg(dropn);
			}
			resetStringInput();
			dialog=-1;
		}
		else if(item==1)
		{
			dialog=-1;
			resetStringInput();
		}
	}
	else if(dialog==6)
	{

		if(item==0)
		{
			if(slot[0].lvl==0)
			{
				newSlot=0;
				dialog=4;
			}
			else
			{
				strcpy(login_name,slot[0].name);
				MAKE_MSG(logn_msg,msg,LOGN_MSG);
				msg.slot=0;
				nc.send((unsigned char *)&msg,sizeof(logn_msg),SEND_GUARANTEED);
				dialog=-1;
			}
		}
		else if(item==1)
		{
			if(slot[1].lvl==0)
			{
				newSlot=1;
				dialog=4;
			}
			else
			{
				strcpy(login_name,slot[1].name);
				MAKE_MSG(logn_msg,msg,LOGN_MSG);
				msg.slot=1;
				nc.send((unsigned char *)&msg,sizeof(logn_msg),SEND_GUARANTEED);
				dialog=-1;
			}
		}
		else if(item==2)
		{
			if(slot[2].lvl==0)
			{
				newSlot=2;
				dialog=4;
			}
			else
			{
				strcpy(login_name,slot[2].name);
				MAKE_MSG(logn_msg,msg,LOGN_MSG);
				msg.slot=2;
				nc.send((unsigned char *)&msg,sizeof(logn_msg),SEND_GUARANTEED);
				dialog=-1;
			}
		}
		else if(item==3)
		{
			if(slot[3].lvl==0)
			{
				newSlot=3;
				dialog=4;
			}
			else
			{
				strcpy(login_name,slot[3].name);
				MAKE_MSG(logn_msg,msg,LOGN_MSG);
				msg.slot=3;
				nc.send((unsigned char *)&msg,sizeof(logn_msg),SEND_GUARANTEED);
				dialog=-1;
			}
		}
	}
	else if(dialog==7)
	{
		//char message[64];
		//sprintf(message,"Music is set to %d",music);
		//term.newLine(message);
		
		if(item == 1 && music == 0)
		{
			music = 1;
			playMidi(world[MYGUY.p.map].npc[4].index);
			sprintf(vDialog[7].w[0].label,"Music Power: On");
		}
		else if(item == 2 && music == 1)
		{
			music = 0;
			Mix_HaltMusic();
			curMidi = -1;
			sprintf(vDialog[7].w[0].label,"Music Power: Off");
		}
		else if(item == 5 && sound == 0)
		{
			sound = 1;
			sprintf(vDialog[7].w[4].label,"Sound Power: On");
		}
		else if(item == 6 && sound == 1)
		{
			sound = 0;
			sprintf(vDialog[7].w[4].label,"Sound Power: Off");
		}
		else if(item == 3)
			dialog = -1;
	}
	else if(dialog==8)//Trade Window
	{
		int qty = atoi(vDialog[8].w[32].label);
		if(qty < 1)
		{
			char temp[256];
			strcpy(temp,"^RInvalid quantity.");
			term.newLine(temp);
		}
		else
		{
			if(item == 0)
			{
				strcpy(vDialog[8].w[32].label,"1");
				dialog = -1;
			}
			else if(item == 1 || item == 21)
			{
				if(vDialog[8].w[21].graphic != -1)
				{
					char temp[256];
					sprintf(temp,"/trade 1 %d",qty);
					sendCmndMsg(temp);
				}
			}
			else if(item == 2 || item == 22)
			{
				if(vDialog[8].w[22].graphic != -1)
				{
					char temp[256];
					sprintf(temp,"/trade 2 %d",qty);
					sendCmndMsg(temp);
				}
			}
			else if(item == 3 || item == 23)
			{
				if(vDialog[8].w[23].graphic != -1)
				{
					char temp[256];
					sprintf(temp,"/trade 3 %d",qty);
					sendCmndMsg(temp);
				}
			}
			else if(item == 4 || item == 24)
			{
				if(vDialog[8].w[24].graphic != -1)
				{
					char temp[256];
					sprintf(temp,"/trade 4 %d",qty);
					sendCmndMsg(temp);
				}
			}
			else if(item == 5 || item == 25)
			{
				if(vDialog[8].w[25].graphic != -1)
				{
					char temp[256];
					sprintf(temp,"/trade 5 %d",qty);
					sendCmndMsg(temp);
				}
			}
			else if(item == 6 || item == 26)
			{
				if(vDialog[8].w[26].graphic != -1)
				{
					char temp[256];
					sprintf(temp,"/trade 6 %d",qty);
					sendCmndMsg(temp);
				}
			}
			else if(item == 7 || item == 27)
			{
				if(vDialog[8].w[27].graphic != -1)
				{
					char temp[256];
					sprintf(temp,"/trade 7 %d",qty);
					sendCmndMsg(temp);
				}
			}
			else if(item == 8 || item == 28)
			{
				if(vDialog[8].w[28].graphic != -1)
				{
					char temp[256];
					sprintf(temp,"/trade 8 %d",qty);
					sendCmndMsg(temp);
				}
			}
			else if(item == 9 || item == 29)
			{
				if(vDialog[8].w[29].graphic != -1)
				{
					char temp[256];
					sprintf(temp,"/trade 9 %d",qty);
					sendCmndMsg(temp);
				}
			}
			else if(item == 10 || item == 30)
			{
				if(vDialog[8].w[30].graphic != -1)
				{
					char temp[256];
					sprintf(temp,"/trade 10 %d",qty);
					sendCmndMsg(temp);
				}
			}
		}
	}
	else if(dialog==9) //Character Window
	{
		if(item==0)
			dialog=-1;
	}
	else if(dialog==10) //NPC Window
	{
		if(item==0)
			dialog=-1;
	}
}

