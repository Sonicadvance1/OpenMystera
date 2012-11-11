struct sprite
{
	int costume;
	int body;
	int hair;
	int clothes;
};

struct card
{
	char   	name[64];
	sprite 	graphic;
	int    	type;
	int	   	min_lvl;
	int		max_lvl;
};

#define M_ATK 0
#define P_ATK 1

card cards = 
{    
	{"Toad"			, {63 ,-1,-1,-1}	,  M_ATK,  0,  1}, 
    {"Areneid" 		, {119,-1,-1,-1}	,  P_ATK,  0,  1},
    {"Bomb" 		, {58 ,-1,-1,-1}	,  M_ATK,  0,  1},
    {"Earthguard" 	, {20 ,-1,-1,-1}	,  P_ATK,  0,  1},
    {"Flan" 		, {12 ,-1,-1,-1}	,  M_ATK,  0,  1}, 
    {"Bloompire"	, {69 ,-1,-1,-1}	,  P_ATK,  0,  1},
    {"Vulkite" 		, {43 ,-1,-1,-1}	,  M_ATK,  0,  1}, 
    {"Skull Eater" 	, {116,-1,-1,-1}	,  P_ATK,  0,  1},
    {"Canine" 		, {44 ,-1,-1,-1}	,  P_ATK,  0,  2}, 
    {"Siren" 		, {-1 ,11,74,60}	,  M_ATK,  0,  2}, 
    {"Grease Monk" 	, {11 ,-1,-1,-1}	,  P_ATK,  0,  2},
    {"Cephaler" 	, {122,-1,-1,-1}	,  P_ATK,  0,  2},
    {"Goblin" 		, {42 ,-1,-1,-1}	,  P_ATK,  0,  2},
    {"Critic" 		, {124,-1,-1,-1}	,  P_ATK,  0,  2},
    {"Suriander" 	, {78 ,-1,-1,-1}	,  P_ATK,  1,  2},
    {"Veteran" 		, {49 ,-1,-1,-1}	,  M_ATK,  1,  2},
    {"Ultros" 		, {109,-1,-1,-1}	,  P_ATK,  1,  2},
    {"Alcumia" 		, {-1 ,11,78,55}	,  M_ATK,  1,  2},
    {"Kirin" 		, {51 ,-1,-1,-1}	,  P_ATK,  1,  2},
    {"Guard" 		, {10 ,-1,-1,-1}	,  P_ATK,  0,  3},
    {"Crystal Fairy", {35 ,-1,-1,-1}	,  M_ATK,  0,  3},
    {"Apparite" 	, {53 ,-1,-1,-1}	,  M_ATK,  0,  3},
    {"Exoray" 		, {66 ,-1,-1,-1}	,  P_ATK,  0,  3}, 
    {"Magic Urn" 	, {71 ,-1,-1,-1}	,  M_ATK,  0,  3},
    {"Dancer" 		, "l-30_magic",  M_ATK,  0,  3},
    {"Katanasoul" 	, {7  ,-1,-1,-1}	,  P_ATK,  0,  3},
    {"Bismark" 		, {126,-1,-1,-1}	,  P_ATK,  0,  3},
    {"Whelk" 		, {106,-1,-1,-1}	,  P_ATK,  0,  3},
    {"Umaro" 		, {85 ,-1,-1,-1}	,  P_ATK,  0,  3},
    {"Mage Master" 	, {87 ,-1,-1,-1}	,  M_ATK,  1,  3},
    {"Cherie" 		, "Cherie",  M_ATK,  1,  3},
    {"Spook" 		, {55 ,-1,-1,-1}	,  M_ATK,  1,  3},
    {"Esper" 		, {56 ,-1,-1,-1}	,  P_ATK,  1,  3},
    {"Ceritops" 	, {27 ,-1,-1,-1}	,  P_ATK,  0,  4},
    {"Mukare" 		, {22 ,-1,-1,-1}	,  M_ATK,  0,  4},
    {"Misfit" 		, "Misfit",  M_ATK,  0,  4},
    {"Magroadera" 	, "mag_roadera",  P_ATK,  0,  4},
    {"Lamia" 		, "Lamia",  M_ATK,  0,  4},
    {"Rhinox" 		, "rhinox",  P_ATK,  1,  4},
    {"Ifrit" 		, "ifritb",  M_ATK,  1,  4},
    {"Gloom Shell" 	, "gloomshell",  M_ATK,  1,  4}, 
    {"Fire Demon" 	, "firedemon",  M_ATK,  1,  4},
    {"Osprey" 		, "osprey",  P_ATK,  1,  4},
    {"Brawler" 		, "brawler",  P_ATK,  1,  4},
    {"Wolf" 		, "lobo",  P_ATK,  1,  4},
    {"Golem" 		, "golem",  P_ATK,  1,  4},
    {"Brachosaur" 	, "brachosaur",  P_ATK,  1,  4},
    {"Jester" 		, "l-90_magic",  M_ATK,  1,  4},
    {"Dark Force" 	, "l-70_magic",  M_ATK,  1,  4},
    {"Ghost" 		, "ghost",  M_ATK,  1,  4},
    {"Shiva" 		, "shiva",  M_ATK,  1,  4},
    {"Bear" 		, "gold_bear",  P_ATK,  1,  4}, 
    {"Fidor" 		, "fidor",  P_ATK,  1,  4},
    {"Sorceress" 	, "ff52",  M_ATK,  1,  4},
    {"Starlet" 		, "starlet",  M_ATK,  1,  4},
    {"Temptress" 	, "l-80_magic",  M_ATK,  1,  4},
    {"Merchant" 	, "merchant",  M_ATK,  1,  4},
    {"Commando" 	, "commando",  P_ATK,  1,  4},
    {"Tritoch" 		, "tritochb",  M_ATK,  1,  4},
    {"Ramuh" 		, "ramuh",  M_ATK,  1,  4},
    {"Chupon" 		, "chupon",  M_ATK,  2,  4},
    {"Opinicus" 	, "opinicus",  P_ATK,  2,  4},
    {"Rikald Mage" 	, "RikaldMage",  M_ATK,  2,  4},
    {"Magissa" 		, "Magissa",  M_ATK,  1,  5},
    {"Nastidon" 	, "nastidon",  P_ATK,  1,  5},
    {"Mantis" 		, "gilomantis",  M_ATK,  1,  5}, 
    {"Allosaurus" 	, "allosaurus",  P_ATK,  2,  5},
    {"Outsider" 	, "outsider",  P_ATK,  2,  5},
    {"Pterodon" 	, "pterodon",  P_ATK,  2,  5},
    {"Maduin" 		, "maduin",  M_ATK,  3,  5},
    {"Poison Breath", "mad_oscar",  P_ATK,  3,  5},
    {"Wood Sprite" 	, "WoodSprite",  M_ATK,  3,  5},
    {"Doom" 		, "doom_gaze",  M_ATK,  2,  6},
    {"Blue Dragon" 	, "blue_drgn",  P_ATK,  2,  6},
    {"Dark Wizard" 	, "DarkWizard",  M_ATK,  2,  6},
    {"Minotaur" 	, "Minotaur",  P_ATK,  2,  6},
    {"Nerapa" 		, "nerapa",  M_ATK,  2,  6},
    {"Chimera" 		, "chimera",  P_ATK,  3,  7},
    {"Azulmagia" 	, "Azulmagia",  M_ATK,  3,  7},
    {"Halycanos" 	, "Halycanos",  M_ATK,  3,  7},
    {"Aquila" 		, "aquila",  P_ATK,  3,  7},
    {"Atma" 		, "atmaweapon",  P_ATK,  3,  7},
    {"Kefka A" 		, "kefkaa",  M_ATK,  4,  8},
    {"General" 		, "general",  P_ATK,  4,  8},
    {"Necrofobia" 	, "Necrofobia",  M_ATK,  4,  8},
    {"Lich" 		, "l-50_magic",  M_ATK,  4,  9}, 
    {"Seraphim" 	, "sraphim",  M_ATK,  4,  9},
    {"Terrato" 		, "terrato",  M_ATK,  4,  9},
    {"Dragoblin" 	, "goblin",  M_ATK,  5,  10},
    {"Unicorn" 		, "unicorn",  P_ATK,  5,  10},
    {"Palidor" 		, "palidor",  M_ATK,  5,  11},
    {"Black Dragon"	, "dragon",  P_ATK,  6,  11},
    {"Gigantos" 	, "gigantos",  P_ATK,  6,  12},
    {"Bahamut" 		, "bahamut",  P_ATK,  6,  12},
    {"Kefka B" 		, "kefkab",  M_ATK,  7,  13}, 
    {"Odin" 		, "odin",  P_ATK,  7,  13},
    {"Nether Demon"	, "phunbaba",  P_ATK,  8,  14},
    {"Dante" 		, "dante",  P_ATK,  8,  14},
    {"Behemoth" 	, "gtbehemoth",  P_ATK,  9,  15},
    {"Phoenix" 		, "phoenix",  M_ATK,  9,  15}
};