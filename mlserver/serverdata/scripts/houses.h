
struct cHouse
{
	int map;
	int x;
	int y;
	int dmap;
	int dx;
	int dy;
	int price;
};

// ADD NEW HOUSES TO THE LIST BELOW!
cHouse house[] = {

// Houses


	{ 4 , 4,  4, 183,9,10, 60000 },
	{ 180 , 13,  5, 182,8,11, 60000 },
	{ 30 , 13,  2, 77,9,13, 40000 },
	{ 785 , 7,  5, 789,9,13, 90000 },
	{ 1 , 16, 11, 185,10,9, 30000 }, // Tiny North GB House
	{ 428 , 3, 5, 459,10,11, 60000 },
	{ 387, 9, 8, 1244, 10, 9, 5000 },
	{ 87, 11, 11, 123, 10, 11, 20000 },
	{ 120, 3, 10, 1253, 12, 5, 5000 },
	{ 79, 6, 9, 1254, 12, 9, 10000 },
	{ 3, 6, 12, 1245, 9, 11, 80000 }, // West GB House
	{ 1255, 13, 9, 1257, 11, 9, 20000}, // Beach Shanty
	{ 1250, 12, 8, 1258, 10, 8, 20000}, // Beach Shanty
	{ 1256, 3, 7, 1259, 10, 10, 40000}, // Ocean Shack
	{ 1261, 11, 8, 1262, 9, 10, 40000 }, // Beach House (off of fishing dock)
	{ 1269, 12, 9, 1270, 9, 10, 40000 }, // Beach House (off of fishing dock)
	{ 1126, 11, 7, 1091, 10, 10, 10000 }, // Long Road House
	{ 449, 6, 1, 450, 6, 13, 5000 }, // Ned and Janelle's Storage	
	{ 243, 13, 10, 244, 10, 13, 150000 }, // Ned and Janelle's House (haha, house, what a puny word for this...)
	{ 585, 17, 10, 586, 9, 11, 10000 }, // Sheeptown Slums House
	{ 585, 2, 4, 593, 9, 11, 10000 }, // Sheeptown Slums House
	{ 585, 12, 10, 587, 9, 11, 10000 }, // Sheeptown Slums House
	{ 49, 10, 5, 566, 9, 12, 50000 }, // Beach House (Fishing Docks Area)	
	{ 6, 3, 6, 877, 9, 12, 60000 }, // South East GB House
	{ 1197, 16, 6, 1197, 16, 4, 5000 }, // Monestary Dorm (Fancy)
	{ 1197, 3, 6, 1197, 3, 4, 5000 }, // Monestary Dorm (Fancy)
	{ 1197, 16, 9, 1197, 16, 11, 5000 }, // Monestary Dorm (Fancy)	
	{ 1201, 9, 6, 1201, 9, 4, 5000 }, // Monestary Dorm (Large)
	{ 1211, 9, 6, 1211, 9, 4, 5000 }, // Monestary Dorm (Large) 
	{ 1201, 16, 6, 1201, 16, 4, 5000 }, // Monestary Dorm (Medium)
	{ 1201, 3, 6, 1201, 3, 4, 5000 }, // Monestary Dorm (Medium)
	{ 1211, 16, 6, 1211, 16, 4, 5000 }, // Monestary Dorm (Medium)
	{ 1211, 3, 6, 1211, 3, 4, 5000 }, // Monestary Dorm (Medium)
	{ 1334, 5, 11, 1334, 5, 9, 3000 }, // Armory
	{ 484, 10, 13, 484, 10, 11, 75000 }, // Treehouse
	{ 1275, 10, 8, 1276, 10, 9, 45000 }, // Long Road House (Near Imp Cave)
	{ 131, 10, 1, 132, 10, 13, 100000 }, // Mansion
	{ 241, 2, 3, 461, 10, 12, 35000 }, // Sheeptown House
	{ 749, 5, 7, 749, 5, 6, 115000 }, // Mine Hideout
	{ 1115, 5, 9, 1115, 5, 7, 5000 }, // Mine Hideout Storage
	{ 488, 14,5, 800, 10, 9, 20000 }, // Wellington House
	{ 488, 4,8, 801, 10, 10, 35000 }, // Wellington House
	{ 498, 8,12,1385, 10, 10, 50000 }, // Nice Wellington House
	{ 493, 7,8,1386, 10, 10, 50000 }, // Nice Wellington House
	{ 499, 14,5, 796, 10, 9, 20000 }, // Wellington House
	{ 499, 10,11,499, 9, 11, 80000 }, // Nice Wellington House
	{ 490, 15, 6, 797, 10, 9, 20000 }, // Wellington House
	{ 493, 12, 8, 1391, 10, 10, 50000 }, // Nice Wellington House
	{ 498, 2,12,1388, 10, 10, 50000 }, // Nice Wellington House
	{ 928, 5,3,929, 10, 10, 80000 }, // Ken Tucky's Farm House
	{ 3, 2,6,3, 2, 5, 3000 }, // Galebrook Locker
	{ 3, 4,6,3, 4, 5, 3000 }, // Galebrook Locker
	{ 3, 6,6,3, 6, 5, 3000 }, // Galebrook Locker
	{ 3, 13,11,3, 13, 10,3000 }, // Galebrook Locker
	{ 3, 15,11,3, 15, 10,3000 }, // Galebrook Locker
	{ 3, 17,11,3, 17, 10,3000 }, // Galebrook Locker
	{ 221, 10,6,223, 10, 13,65000 }, // Forest House
// Guilds


	{ 72, 16, 8, 545, 7, 10, 200000 }, // Healers Guild Hall
	{ 1218, 10, 5, 1219, 10, 13, 200000 }, // Brotherhood Guild Hall
	{ 23, 19, 8, 1136, 1, 6, 210000 }, // Destiny's Soldiers Guild Hall
	{ 6, 17, 3, 1146, 11, 6, 90000 }, // KFC Guild Hall
	{ 41, 4, 4, 216, 10, 13, 45000 }, // Peacekeepers Guild Hall
	{ 619, 8, 2, 1050, 9, 11, 190000 }, // Divine Knights Guild Hall
	{ 325, 6, 7, 758, 10, 13, 35000 }, // Turtle Guild Hall	
	{ 30, 7, 0, 549, 7, 13, 210000 }, // Bounty Hunters Guild Hall


// Businesses


	{ 1065, 9, 2, 1227, 9, 13, 95000 }, // First Bank of ML
	{ 1064, 10, 7, 1064, 10, 5, 100000 }, // BBQ Hut 
	{ 1239, 9, 10, 1239, 9, 8, 95000 }, // Pawn-O-Rama

	{ 181, 5, 12, 181, 5, 10, 25 }, // Galebrook Market Booth
	{ 181, 10, 12, 181, 10, 10, 25 }, // Galebrook Market Booth	
	{ 181, 15, 12, 181, 15, 10, 25 }, // Galebrook Market Booth
	{ 1335, 5, 12, 1335, 5, 10, 25 }, // Galebrook Market Booth	
	{ 1335, 10, 12, 1335, 10, 10, 25 }, // Galebrook Market Booth	
	{ 1335, 15, 12, 1335, 15, 10, 25 }, // Galebrook Market Booth	


// Guild Lockers and Rooms


	{ 547, 9, 8, 547, 9, 10, 5000 }, // Healers Guild Locker
	{ 547, 15, 8, 547, 15, 10, 5000 }, // Healers Guild Locker  
	{ 548, 3, 5, 548, 3, 3, 5000 }, // Healers Guild Locker
	{ 548, 6, 8, 548, 6, 10, 5000 }, // Healers Guild Locker
	{ 548, 9, 5, 548, 9, 3, 5000 }, // Healers Guild Locker
	{ 548, 12, 8, 548, 12, 10, 5000 }, // Healers Guild Locker 
	{ 548, 15, 5, 548, 15, 3, 5000 }, // Healers Guild Locker 
	{ 634, 3, 5, 634, 3, 3, 5000 }, // Healers Guild Locker
	{ 634, 6, 8, 634, 6, 10, 5000 }, // Healers Guild Locker
	{ 634, 9, 5, 634, 9, 3, 5000 }, // Healers Guild Locker
	{ 634, 12, 8, 634, 12, 10, 5000 }, // Healers Guild Locker
	{ 634, 15, 5, 634, 15, 3, 5000 }, // Healers Guild Locker
	{ 636, 0, 9, 638, 18, 9, 20000 }, // Guild Leader Room (HF)
	{ 637, 3, 8, 637, 3, 6, 5000 }, // Guild Room (DS)
	{ 637, 9, 8, 637, 9, 6, 5000 }, // Guild Room (DS)
	{ 637, 16, 8, 637, 16, 6, 5000 }, // Guild Room (DS)
	{ 644, 3, 8, 644, 3, 6, 5000 }, // Guild Room (DS)
	{ 644, 10, 8, 644, 10, 6, 5000 }, // Guild Room (DS)
	{ 644, 16, 8, 644, 16, 6, 5000 }, // Guild Room (DS)
	{ 1051, 9, 6, 1051, 9, 4, 5000 }, // DK Room
	{ 1051, 10, 9, 1051, 10, 11, 5000 }, // DK Room
	{ 1053, 9, 6, 1053, 9, 4, 5000 }, // DK Room
	{ 1053, 10, 9, 1053, 10, 11, 5000 }, // DK Room	
	{ 547, 9, 8, 547, 9, 10, 5000 }, // Guild Room (Healers)
	{ 547, 15, 8, 547, 15, 10, 5000 }, // Guild Room (Healers)
	{ 554, 3, 6, 554, 3, 4, 5000 }, // Guild Room (Bounty Hunters)
	{ 554, 3, 9, 554, 3, 11, 5000}, // Guild Room (Bounty Hunters)
	{ 554, 12, 7, 554, 14, 7, 5000 }, // Guild Leader Room (Bounty Hunters)
	{ 555, 16, 6, 555, 16, 4, 5000 }, // Guild Room (Bounty Hunters)	
	{ 555, 16, 9, 555, 16, 11, 5000 }, // Guild Room (Bounty Hunters)
	{ 555, 3, 9, 555, 3, 11, 5000 }, // Guild Room (Bounty Hunters)
	{ 555, 3, 6, 555, 3, 4, 5000 }, // Guild Room (Bounty Hunters)
	{ 1073, 16, 8, 1073, 16, 10, 5000 }, // Guild Room (Guardians)
	{ 1073, 16, 5, 1073, 16, 3, 5000 }, // Guild Room (Guardians)	
	{ 1073, 8, 4, 1073, 8, 2, 5000 }, // Guild Room (Guardians)	
	{ 1073, 8, 9, 1073, 8, 11, 5000 }, // Guild Room (Guardians)		
	{ 1073, 5, 6, 1073, 3, 6, 5000 }, // Guild Room (Guardians)		
	{ 1074, 16, 8, 1074, 16, 10, 5000 }, // Guild Room (Guardians)
	{ 1074, 16, 5, 1074, 16, 3, 5000 }, // Guild Room (Guardians)	
	{ 1074, 8, 4, 1074, 8, 2, 5000 }, // Guild Room (Guardians)	
	{ 1074, 8, 9, 1074, 8, 11, 5000 }, // Guild Room (Guardians)		
	{ 1074, 5, 6, 1074, 3, 6, 5000 }, // Guild Room (Guardians)	
	{ 1072, 5, 0, 1075, 5, 13, 5000 }, // Guild Leader Room (Guardians)	
	{ 1072, 14, 0, 1075, 14, 13, 5000 }, // Guild Leader Room (Guardians)	

	};

int NUM_HOUSES = 101;

//Note to self:change amount of houses and reupload 468.txt and 1007.txt each time a new house is added