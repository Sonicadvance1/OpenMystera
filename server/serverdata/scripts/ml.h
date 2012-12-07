/*
	Mystera Legends scripting interface
	Written by Steve Northamer
	SteveNorthamer@yahoo.com
	February 2, 2004
*/

// Header inclusion guard
#if !defined(ML_H)
#define ML_H


// Define NULL
#if !defined(NULL)
	#define NULL 0
#endif


// ML data types
typedef void			MLvoid;
typedef unsigned int	MLboolean;
typedef unsigned int	MLbitfield;
typedef unsigned int	MLenum;
typedef unsigned int	MLsize;
typedef char			MLchar;
typedef int				MLint;
typedef unsigned int	MLuint;
typedef float			MLfloat;


// ML boolean states
const MLboolean ML_FALSE	= 0;
const MLboolean ML_TRUE		= 1;


// ML error states
const MLenum ML_NO_ERROR			= 0x0000;
const MLenum ML_INVALID_ENUM		= 0x0001;
const MLenum ML_INVALID_VALUE		= 0x0002;
const MLenum ML_INVALID_OPERATION	= 0x0003;
const MLenum ML_STACK_OVERFLOW		= 0x0004;
const MLenum ML_STACK_UNDERFLOW		= 0x0005;
const MLenum ML_OUT_OF_MEMORY		= 0x0006;


// ML state bits
const MLbitfield ML_HP_BAR	= 0x00000001;


// ML player state constants
const MLenum ML_DATABASE_ID				= 0x0100;
const MLenum ML_X						= 0x0101;
const MLenum ML_Y						= 0x0102;
const MLenum ML_MAP_ID					= 0x0103;
const MLenum ML_DIRECTION				= 0x0104;
const MLenum ML_IS_NPC					= 0x0105;
const MLenum ML_IS_HOSTILE				= 0x0106;
const MLenum ML_IS_MERCHANT				= 0x0107;
const MLenum ML_VISION_RANGE			= 0x0108;
const MLenum ML_STRENGTH				= 0x0109;
const MLenum ML_DEXTERITY				= 0x010A;
const MLenum ML_CONSTITUTION			= 0x010B;
const MLenum ML_INTELLIGENCE			= 0x010C;
const MLenum ML_WISDOM					= 0x010D;
const MLenum ML_EQUIPMENT_LEFT_HAND		= 0x010E;
const MLenum ML_EQUIPMENT_RIGHT_HAND	= 0x010F;
const MLenum ML_EQUIPMENT_HEAD			= 0x0110;
const MLenum ML_EQUIPMENT_BODY			= 0x0111;
const MLenum ML_EQUIPMENT_OTHER			= 0x0112;
const MLenum ML_LEVEL					= 0x0113;
const MLenum ML_SPRITE_ID				= 0x0114;
const MLenum ML_BODY_ID					= 0x0115;
const MLenum ML_HAIR_ID					= 0x0116;
const MLenum ML_CLOTHES_ID				= 0x0117;
const MLenum ML_BOUNTY					= 0x0118;
const MLenum ML_BASE_ATTACK				= 0x0119;
const MLenum ML_BASE_DEFENSE			= 0x011A;
const MLenum ML_TRAINING_POINTS			= 0x011B;
const MLenum ML_CURRENT_HP				= 0x011C;
const MLenum ML_MAXIMUM_HP				= 0x011D;
const MLenum ML_CURRENT_MP				= 0x011E;
const MLenum ML_MAXIMUM_MP				= 0x011F;
const MLenum ML_AGGRESSOR_ID			= 0x0120;
const MLenum ML_MAGIC_TARGET_ID			= 0x0121;
const MLenum ML_CHAT_SCRIPT_ID			= 0x0122;
const MLenum ML_MOVE_SCRIPT_ID			= 0x0123;
const MLenum ML_EXPERIENCE				= 0x0124;
const MLenum ML_ORIGIN_X				= 0x0125;
const MLenum ML_ORIGIN_Y				= 0x0126;
const MLenum ML_ORIGIN_MAP_ID			= 0x0127;
const MLenum ML_NAME					= 0x0128;
const MLenum ML_TITLE					= 0x0129;
const MLenum ML_IP_ADDRESS				= 0x012A;
const MLenum ML_CREATE_DATE				= 0x012B;
const MLenum ML_LOG_IN_DATE				= 0x012C;
const MLenum ML_LOG_OUT_DATE			= 0x012D;
const MLenum ML_LOGGED_IN_TIME			= 0x012E;
const MLenum ML_SERENITY				= 0x012F;
const MLenum ML_STATIONARY_TIME			= 0x0130;
const MLenum ML_IS_PREMIUM_ACCOUNT		= 0x0131;
const MLenum ML_ACCOUNT_NAME			= 0x0132;

/*
const MLenum ML_AGE	// Obsolete
const MLenum ML_PLAYER_TEMPLATE	// Don't understand
const MLenum ML_FLAGS	// Don't understand
const MLenum ML_BOOT_TIME	// Managed by server
const MLenum ML_UNKNOWN // Don't understand
const MLenum ML_TIME_SAFE // Don't understand
const MLenum ML_PLAYER_ID // Not useful in this context
const MLenum ML_CURRENT_MAP // Don't understand
const MLenum ML_MSTL // Don't understand
*/


// ML item state constants
//const MLenum ML_DATABASE_ID
const MLenum ML_QUANTITY			= 0x0200;
const MLenum ML_IMAGE_ID			= 0x0201;
//const MLenum ML_NAME
//const MLenum ML_MAP_ID
//const MLenum ML_X
//const MLenum ML_Y
const MLenum ML_OWNER_ID			= 0x0202;
const MLenum ML_SLOT_ID				= 0x0203;
const MLenum ML_TYPE				= 0x0204;
const MLenum ML_IS_STACKABLE		= 0x0205;
const MLenum ML_IS_DROPABLE			= 0x0206;
const MLenum ML_IS_USABLE			= 0x0207;
const MLenum ML_USE_SCRIPT_ID		= 0x0208;
const MLenum ML_EQUIP_SCRIPT_ID		= 0x0209;
const MLenum ML_UNEQUIP_SCRIPT_ID	= 0x020A;
const MLenum ML_PICK_UP_SCRIPT_ID	= 0x020B;
const MLenum ML_DROP_SCRIPT_ID		= 0x020C;
const MLenum ML_LOSE_SCRIPT_ID		= 0x020D;
const MLenum ML_ATTACK				= 0x020E;
const MLenum ML_DEFENSE				= 0x020F;

/*
const MLenum ML_LIFE // Managed by server
const MLenum ML_FLAGS // Don't understand
const MLenum ML_ITEM_TEMPLATE // Don't understand
const MLenum ML_BONUS // Don't understand
const MLenum ML_BONUS2 // Don't understand
const MLenum ML_USERDATA // Don't understand
const MLenum ML_USERDATA2 // Don't understand
const MLenum ML_DATA // Don't understand
*/


// ML player range constants
const MLint ML_MIN_PLAYER_ID		= -1;
const MLint ML_MAX_PLAYER_ID		= (1 << 30) - 1;
const MLint ML_MIN_X				= 0;
const MLint ML_MAX_X				= 19;
const MLint ML_MIN_Y				= 0;
const MLint ML_MAX_Y				= 14;
const MLint ML_MIN_MAP_ID			= -1;
const MLint ML_MAX_MAP_ID			= (1 << 15) - 1;
const MLenum ML_DOWN				= 0;
const MLenum ML_UP					= 1;
const MLenum ML_LEFT				= 2;
const MLenum ML_RIGHT				= 3;
const MLint ML_MIN_ATTRIBUTE		= 0;
const MLint ML_MAX_ATTRIBUTE		= (1 << 8) - 1;
const MLint ML_MIN_LEVEL			= 1;
const MLint ML_MAX_LEVEL			= (1 << 8) - 1;
const MLint ML_MIN_SPRITE_ID		= 0;
const MLint ML_MAX_SPRITE_ID		= (1 << 15) - 1;
const MLint ML_MIN_BODY_ID			= 0;
const MLint ML_MAX_BODY_ID			= (1 << 15) - 1;
const MLint ML_MIN_HAIR_ID			= 0;
const MLint ML_MAX_HAIR_ID			= (1 << 15) - 1;
const MLint ML_MIN_CLOTHES_ID		= 0;
const MLint ML_MAX_CLOTHES_ID		= (1 << 15) - 1;
const MLint ML_MIN_BOUNTY			= 0;
const MLint ML_MAX_BOUNTY			= (1 << 30) - 1;
const MLint ML_MIN_BASE_ATTACK		= 0;
const MLint ML_MAX_BASE_ATTACK		= (1 << 15) - 1;
const MLint ML_MIN_BASE_DEFENSE		= 0;
const MLint ML_MAX_BASE_DEFENSE		= (1 << 15) - 1;
const MLint ML_MIN_TRAINING_POINTS	= 0;
const MLint ML_MAX_TRAINING_POINTS	= (1 << 16) - 1;
const MLint ML_MIN_CURRENT_HP		= 0;
const MLint ML_MAX_CURRENT_HP		= (1 << 30) - 1;
const MLint ML_MIN_MAXIMUM_HP		= 0;
const MLint ML_MAX_MAXIMUM_HP		= (1 << 30) - 1;
const MLint ML_MIN_CURRENT_MP		= 0;
const MLint ML_MAX_CURRENT_MP		= (1 << 30) - 1;
const MLint ML_MIN_MAXIMUM_MP		= 0;
const MLint ML_MAX_MAXIMUM_MP		= (1 << 30) - 1;
const MLint ML_MIN_SCRIPT_ID		= -1;
const MLint ML_MAX_SCRIPT_ID		= (1 << 15) - 1;
const MLint ML_MIN_EXPERIENCE		= 0;
const MLint ML_MAX_EXPERIENCE		= (1 << 30) - 1;
const MLint ML_PLAYER_NAME_LENGTH	= 32;
const MLint ML_TITLE_LENGTH			= 64;
const MLint ML_IP_ADDRESS_LENGTH	= 16;
const MLint ML_CREATE_DATE_LENGTH	= 64;
const MLint ML_LOG_IN_DATE_LENGTH	= 64;
const MLint ML_LOG_OUT_DATE_LENGTH	= 64;
const MLint ML_MIN_SERENITY			= 0;
const MLint ML_MAX_SERENITY			= (1 << 30) - 1;
const MLint ML_ACCOUNT_NAME_LENGTH	= 8;


// ML item range constants
const MLint ML_MIN_ITEM_ID			= -1;
const MLint ML_MAX_ITEM_ID			= (1 << 30) - 1;
const MLint ML_MIN_QUANTITY			= -1;
const MLint ML_MAX_QUANTITY			= (1 << 30) - 1;
const MLint ML_MIN_IMAGE_ID			= 0;
const MLint ML_MAX_IMAGE_ID			= (1 << 15) - 1;
const MLint ML_ITEM_NAME_LENGTH		= 32;
const MLint ML_MIN_SLOT_ID			= 0;
const MLint ML_MAX_SLOT_ID			= 28;
const MLint ML_MIN_ATTACK			= 0;
const MLint ML_MAX_ATTACK			= (1 << 15) - 1;
const MLint ML_MIN_DEFENSE			= 0;
const MLint ML_MAX_DEFENSE			= (1 << 15) - 1;


// ML value constants
const MLint ML_PLAYER_ID_NONE		= -1;
const MLint ML_MAP_ID_NONE			= -1;
const MLint ML_SPRITE_ID_NONE		= 0;
const MLint ML_BODY_ID_NONE			= 0;
const MLint ML_HAIR_ID_NONE			= 0;
const MLint ML_CLOTHES_ID_NONE		= 0;
const MLint ML_SCRIPT_ID_NONE		= -1;
const MLint ML_ITEM_ID_NONE			= -1;
const MLint ML_EQUIPMENT_ID_NONE	= -1;


// ML item type contants
//const MLenum ML_EMPTY		= 0;
const MLenum ML_ONE_HANDED	= 1;
const MLenum ML_ITEM		= 2;
const MLenum ML_CURRENCY	= 3;
const MLenum ML_ARMOR		= 4;
const MLenum ML_HELMET		= 5;
const MLenum ML_TWO_HANDED	= 6;
const MLenum ML_OTHER		= 7;


// ML interface function declarations
MLenum		mlGetError();
MLvoid		mlEnable(MLbitfield xState);
MLvoid		mlDisable(MLbitfield xState);
MLboolean	mlIsEnabled(MLbitfield xState);
MLvoid		mlPushAttrib();
MLvoid		mlPopAttrib();
MLboolean	mlIsPlayer(MLint xPlayerID);
MLvoid		mlGenPlayers(MLsize xNumPlayers, MLint* xpPlayerIDs);
MLvoid		mlDeletePlayers(MLsize xNumPlayers, MLint* xpPlayerIDs);
MLboolean	mlGetPlayerb(MLint xPlayerID, MLenum xParamName);
MLint		mlGetPlayeri(MLint xPlayerID, MLenum xParamName);
MLvoid		mlGetPlayercv(MLint xPlayerID, MLenum xParamName, MLchar* xpBuffer);
MLvoid		mlSetPlayerb(MLint xPlayerID, MLenum xParamName, MLboolean xParam);
MLvoid		mlSetPlayeri(MLint xPlayerID, MLenum xParamName, MLint xParam);
MLvoid		mlSetPlayercv(MLint xPlayerID, MLenum xParamName, MLchar* xpBuffer);
MLint		mlGetPlayerInventory(MLint xPlayerID, MLint xSlotID);
MLvoid		mlSetPlayerInventory(MLint xPlayerID, MLint xSlotID, MLint xItemID);
MLboolean	mlIsItem(MLint xItemID);
MLvoid		mlGenItems(MLsize xNumItems, MLint* xpItemIDs);
MLvoid		mlDeleteItems(MLsize xNumItems, MLint* xpItemIDs);
MLboolean	mlGetItemb(MLint xItemID, MLenum xParamName);
MLint		mlGetItemi(MLint xItemID, MLenum xParamName);
MLvoid		mlGetItemcv(MLint xItemID, MLenum xParamName, MLchar* xpBuffer);
MLvoid		mlSetItemb(MLint xItemID, MLenum xParamName, MLboolean xParam);
MLvoid		mlSetItemi(MLint xItemID, MLenum xParamName, MLint xParam);
MLvoid		mlSetItemcv(MLint xItemID, MLenum xParamName, MLchar* xpBuffer);
MLvoid		mlUpdate();


// ML interface private use declarations
struct ATTRIB_STACK
{
	ATTRIB_STACK* pNext;
	MLbitfield State;
};

struct UPDATE_LIST
{
	UPDATE_LIST* pNext;
	MLint ID;
};

MLvoid		mlSetError(MLenum xErrorState);
MLvoid		mlQueueUpdate(UPDATE_LIST** xppList, MLint xID);


// ML state variables
static MLenum			gErrorState;
static ATTRIB_STACK		gMLDefaultState = { NULL, ML_HP_BAR };
static ATTRIB_STACK*	gpMLState = &gMLDefaultState;
static UPDATE_LIST*		gpUpdateClientPosition = NULL;
static UPDATE_LIST*		gpUpdateClientAttributes = NULL;
static UPDATE_LIST*		gpUpdateClientLevel = NULL;
static UPDATE_LIST*		gpUpdateClientHP = NULL;
static UPDATE_LIST*		gpUpdateClientMP = NULL;
static UPDATE_LIST*		gpUpdateClientExperience = NULL;
static UPDATE_LIST*		gpUpdateClientPlayer = NULL;
static UPDATE_LIST*		gpUpdateClientHPBar = NULL;


// ML interface function definitions
MLenum mlGetError()
{
	// Return error state and clear error
	MLenum PrevErrorState;
	PrevErrorState = gErrorState;
	gErrorState = ML_NO_ERROR;
	return PrevErrorState;
}

MLvoid mlSetError(MLenum xErrorState)
{
	// Set error state only if no prior error
	if (gErrorState == ML_NO_ERROR)
		gErrorState = xErrorState;
}

MLvoid mlEnable(MLbitfield xState)
{
	gpMLState->State |= xState;
}

MLvoid mlDisable(MLbitfield xState)
{
	gpMLState->State &= ~xState;
}

MLboolean mlIsEnabled(MLbitfield xState)
{
	return ((gpMLState->State & xState) != 0);
}

MLvoid mlPushAttrib()
{
	ATTRIB_STACK* pState;
	pState = new ATTRIB_STACK;
	if (pState == NULL)
		{
		mlSetError(ML_OUT_OF_MEMORY);
		return;
		}
	pState->pNext = gpMLState;
	pState->State = gpMLState->State;
	gpMLState = pState;
}

MLvoid mlPopAttrib()
{
	ATTRIB_STACK* pState;
	if (gpMLState->pNext == NULL)
		{
		mlSetError(ML_STACK_UNDERFLOW);
		return;
		}
	pState = gpMLState;
	gpMLState = gpMLState->pNext;
	delete pState;
}

MLboolean mlIsPlayer(MLint xPlayerID)
{
	cPlayer* pPlayer;

	if (xPlayerID < 0)
		return ML_FALSE;

	if (xPlayerID >= playerLen())
		return ML_FALSE;

	pPlayer = playerStruct(xPlayerID);

	// TODO: Ask James how to determine if a player structure is "empty"
	return (pPlayer->name[0] == '\0');
}

MLvoid mlGenPlayers(MLsize xNumPlayers, MLint* xpPlayerIDs)
{
	MLint PlayerID;
	MLint i;
	cPlayer* pPlayer;

	if (xNumPlayers <= 0)
		{
		mlSetError(ML_INVALID_VALUE);
		return;
		}

	PlayerID = 0;
	i = 0;
	while (true)
		{
		if (i == xNumPlayers)
			return;

		if (mlIsPlayer(PlayerID))
			{
			PlayerID++;
			continue;
			}

		xpPlayerIDs[i] = PlayerID;

		// TODO: Set default player values
		pPlayer = playerStruct(PlayerID);
		pPlayer->id = 0;
		pPlayer->type = 1;	// NPC
		strncpy(pPlayer->name, "New", ML_PLAYER_NAME_LENGTH);

		PlayerID++;
		i++;
		}
}

MLvoid mlDeletePlayers(MLsize xNumPlayers, MLint* xpPlayerIDs)
{
	MLint i;
	MLint PlayerID;
	MLint NumPlayerIDs;
	cPlayer* pPlayer;

	if (xNumPlayers <= 0)
		{
		mlSetError(ML_INVALID_VALUE);
		return;
		}

	NumPlayerIDs = playerLen();
	for (i = 0; i < xNumPlayers; i++)
		{
		PlayerID = xpPlayerIDs[i];

		if (PlayerID < 0 || PlayerID >= NumPlayerIDs)
			continue;

		pPlayer = playerStruct(PlayerID);

		// TODO: Ask James how to determine if a player structure is "empty"
		strncpy(pPlayer->name, "", ML_PLAYER_NAME_LENGTH);
		}
}

MLboolean mlGetPlayerb(MLint xPlayerID, MLenum xParamName)
{
	cPlayer* pPlayer;

	if (xPlayerID < 0)
		{
		mlSetError(ML_INVALID_VALUE);
		return ML_FALSE;
		}

	pPlayer = playerStruct(xPlayerID);

	switch (xParamName)
		{
		case ML_IS_NPC:
			return (pPlayer->type == 1);
		case ML_IS_HOSTILE:
			return (pPlayer->state == 1);
		case ML_IS_MERCHANT:
			return (pPlayer->state == 3);
		case ML_IS_PREMIUM_ACCOUNT:
			return (pPlayer->premium == 1);
		}

	mlSetError(ML_INVALID_ENUM);
	return ML_FALSE;
}

MLint mlGetPlayeri(MLint xPlayerID, MLenum xParamName)
{
	cPlayer* pPlayer;

	if (xPlayerID < 0)
		{
		mlSetError(ML_INVALID_VALUE);
		return 0;
		}

	pPlayer = playerStruct(xPlayerID);

	switch (xParamName)
		{
		case ML_DATABASE_ID:
			return pPlayer->id;
		case ML_X:
			return pPlayer->x;
		case ML_Y:
			return pPlayer->y;
		case ML_MAP_ID:
			return pPlayer->map;
		case ML_DIRECTION:
			return pPlayer->dir;
		case ML_VISION_RANGE:
			return pPlayer->range;
		case ML_STRENGTH:
			return pPlayer->str;
		case ML_DEXTERITY:
			return pPlayer->dex;
		case ML_CONSTITUTION:
			return pPlayer->con;
		case ML_INTELLIGENCE:
			return pPlayer->itl;
		case ML_WISDOM:
			return pPlayer->wis;
		case ML_EQUIPMENT_LEFT_HAND:
			if (pPlayer->eLeft == ML_EQUIPMENT_ID_NONE)
				return ML_ITEM_ID_NONE;
			return pPlayer->inventory[pPlayer->eLeft];
		case ML_EQUIPMENT_RIGHT_HAND:
			if (pPlayer->eRight == ML_EQUIPMENT_ID_NONE)
				return ML_ITEM_ID_NONE;
			return pPlayer->inventory[pPlayer->eRight];
		case ML_EQUIPMENT_HEAD:
			if (pPlayer->eHead == ML_EQUIPMENT_ID_NONE)
				return ML_ITEM_ID_NONE;
			return pPlayer->inventory[pPlayer->eHead];
		case ML_EQUIPMENT_BODY:
			if (pPlayer->eBody == ML_EQUIPMENT_ID_NONE)
				return ML_ITEM_ID_NONE;
			return pPlayer->inventory[pPlayer->eBody];
		case ML_EQUIPMENT_OTHER:
			if (pPlayer->eSpecial == ML_EQUIPMENT_ID_NONE)
				return ML_ITEM_ID_NONE;
			return pPlayer->inventory[pPlayer->eSpecial];
		case ML_LEVEL:
			return pPlayer->lvl;
		case ML_SPRITE_ID:
			return pPlayer->sprite;
		case ML_BODY_ID:
			return pPlayer->body;
		case ML_HAIR_ID:
			return pPlayer->hair;
		case ML_CLOTHES_ID:
			return pPlayer->clothes;
		case ML_BOUNTY:
			return pPlayer->worth;
		case ML_BASE_ATTACK:
			return pPlayer->atk;
		case ML_BASE_DEFENSE:
			return pPlayer->def;
		case ML_TRAINING_POINTS:
			return pPlayer->train;
		case ML_CURRENT_HP:
			return pPlayer->hp;
		case ML_MAXIMUM_HP:
			return pPlayer->mhp;
		case ML_CURRENT_MP:
			return pPlayer->mp;
		case ML_MAXIMUM_MP:
			return pPlayer->mmp;
		case ML_AGGRESSOR_ID:
			return pPlayer->target;
		case ML_MAGIC_TARGET_ID:
			return pPlayer->target_at;
		case ML_CHAT_SCRIPT_ID:
			return pPlayer->chat_script;
		case ML_MOVE_SCRIPT_ID:
			return pPlayer->move_script;
		case ML_EXPERIENCE:
			return pPlayer->exp;
		case ML_ORIGIN_X:
			return pPlayer->origin_x;
		case ML_ORIGIN_Y:
			return pPlayer->origin_y;
		case ML_ORIGIN_MAP_ID:
			return pPlayer->origin_map;
		case ML_LOGGED_IN_TIME:
			return pPlayer->total_time;
		case ML_SERENITY:
			return pPlayer->serenity;
		case ML_STATIONARY_TIME:
			return pPlayer->stationary;
		}

	mlSetError(ML_INVALID_ENUM);
	return 0;
}

MLvoid mlGetPlayercv(MLint xPlayerID, MLenum xParamName, MLchar* xpBuffer)
{
	cPlayer* pPlayer;

	if (xPlayerID < 0)
		{
		mlSetError(ML_INVALID_VALUE);
		return;
		}

	pPlayer = playerStruct(xPlayerID);

	switch (xParamName)
		{
		case ML_NAME:
			strncpy(xpBuffer, pPlayer->name, ML_PLAYER_NAME_LENGTH);
			return;
		case ML_TITLE:
			strncpy(xpBuffer, pPlayer->title, ML_TITLE_LENGTH);
			return;
		case ML_IP_ADDRESS:
			strncpy(xpBuffer, pPlayer->ip, ML_IP_ADDRESS_LENGTH);
			return;
		case ML_CREATE_DATE:
			strncpy(xpBuffer, pPlayer->create_date, ML_CREATE_DATE_LENGTH);
			return;
		case ML_LOG_IN_DATE:
			strncpy(xpBuffer, pPlayer->login_date, ML_LOG_IN_DATE_LENGTH);
			return;
		case ML_LOG_OUT_DATE:
			strncpy(xpBuffer, pPlayer->logout_date, ML_LOG_OUT_DATE_LENGTH);
			return;
		case ML_ACCOUNT_NAME:
			strncpy(xpBuffer, pPlayer->accid, ML_ACCOUNT_NAME_LENGTH - 1);
			xpBuffer[ML_ACCOUNT_NAME_LENGTH - 1] = '\0';
			return;
		}

	mlSetError(ML_INVALID_ENUM);
}

MLvoid mlSetPlayerb(MLint xPlayerID, MLenum xParamName, MLboolean xParam)
{
	cPlayer* pPlayer;

	if (xPlayerID < 0)
		{
		mlSetError(ML_INVALID_VALUE);
		return;
		}

	pPlayer = playerStruct(xPlayerID);

	switch (xParamName)
		{
		}

	mlSetError(ML_INVALID_ENUM);
}

MLvoid mlSetPlayeri(MLint xPlayerID, MLenum xParamName, MLint xParam)
{
	cPlayer* pPlayer;

	if (xPlayerID < 0)
		{
		mlSetError(ML_INVALID_VALUE);
		return;
		}

	pPlayer = playerStruct(xPlayerID);

	switch (xParamName)
		{
		case ML_X:
			if (xParam < ML_MIN_X || xParam > ML_MAX_X)
				{
				mlSetError(ML_INVALID_VALUE);
				return;
				}
			pPlayer->x = xParam;
			mlQueueUpdate(&gpUpdateClientPosition, xPlayerID);
			return;
		case ML_Y:
			if (xParam < ML_MIN_Y || xParam > ML_MAX_Y)
				{
				mlSetError(ML_INVALID_VALUE);
				return;
				}
			pPlayer->y = xParam;
			mlQueueUpdate(&gpUpdateClientPosition, xPlayerID);
			return;
		case ML_MAP_ID:
			if (xParam < ML_MIN_MAP_ID || xParam > ML_MAX_MAP_ID)
				{
				mlSetError(ML_INVALID_VALUE);
				return;
				}
			pPlayer->map = xParam;
			mlQueueUpdate(&gpUpdateClientPosition, xPlayerID);
			return;
		case ML_DIRECTION:
			if (xParam != ML_DOWN && xParam != ML_UP && xParam != ML_LEFT && xParam != ML_RIGHT)
				{
				mlSetError(ML_INVALID_VALUE);
				return;
				}
			pPlayer->dir = xParam;
			mlQueueUpdate(&gpUpdateClientPosition, xPlayerID);
			return;
		case ML_STRENGTH:
			if (xParam < ML_MIN_ATTRIBUTE || xParam > ML_MAX_ATTRIBUTE)
				{
				mlSetError(ML_INVALID_VALUE);
				return;
				}
			pPlayer->str = xParam;
			mlQueueUpdate(&gpUpdateClientAttributes, xPlayerID);
			return;
		case ML_DEXTERITY:
			if (xParam < ML_MIN_ATTRIBUTE || xParam > ML_MAX_ATTRIBUTE)
				{
				mlSetError(ML_INVALID_VALUE);
				return;
				}
			pPlayer->dex = xParam;
			mlQueueUpdate(&gpUpdateClientAttributes, xPlayerID);
			return;
		case ML_CONSTITUTION:
			if (xParam < ML_MIN_ATTRIBUTE || xParam > ML_MAX_ATTRIBUTE)
				{
				mlSetError(ML_INVALID_VALUE);
				return;
				}
			pPlayer->con = xParam;
			mlQueueUpdate(&gpUpdateClientAttributes, xPlayerID);
			return;
		case ML_INTELLIGENCE:
			if (xParam < ML_MIN_ATTRIBUTE || xParam > ML_MAX_ATTRIBUTE)
				{
				mlSetError(ML_INVALID_VALUE);
				return;
				}
			pPlayer->itl = xParam;
			mlQueueUpdate(&gpUpdateClientAttributes, xPlayerID);
			return;
		case ML_WISDOM:
			if (xParam < ML_MIN_ATTRIBUTE || xParam > ML_MAX_ATTRIBUTE)
				{
				mlSetError(ML_INVALID_VALUE);
				return;
				}
			pPlayer->wis = xParam;
			mlQueueUpdate(&gpUpdateClientAttributes, xPlayerID);
			return;
		// TODO: Figure out how equipment works!
		case ML_SPRITE_ID:
			if (xParam < ML_MIN_SPRITE_ID || xParam > ML_MAX_SPRITE_ID)
				{
				mlSetError(ML_INVALID_VALUE);
				return;
				}
			pPlayer->sprite = xParam;
			mlQueueUpdate(&gpUpdateClientPlayer, xPlayerID);
			return;
		case ML_BODY_ID:
			if (xParam < ML_MIN_BODY_ID || xParam > ML_MAX_BODY_ID)
				{
				mlSetError(ML_INVALID_VALUE);
				return;
				}
			pPlayer->body = xParam;
			mlQueueUpdate(&gpUpdateClientPlayer, xPlayerID);
			return;
		case ML_HAIR_ID:
			if (xParam < ML_MIN_HAIR_ID || xParam > ML_MAX_HAIR_ID)
				{
				mlSetError(ML_INVALID_VALUE);
				return;
				}
			pPlayer->hair = xParam;
			mlQueueUpdate(&gpUpdateClientPlayer, xPlayerID);
			return;
		case ML_CLOTHES_ID:
			if (xParam < ML_MIN_CLOTHES_ID || xParam > ML_MAX_CLOTHES_ID)
				{
				mlSetError(ML_INVALID_VALUE);
				return;
				}
			pPlayer->clothes = xParam;
			mlQueueUpdate(&gpUpdateClientPlayer, xPlayerID);
			return;
		case ML_BOUNTY:
			if (xParam < ML_MIN_BOUNTY || xParam > ML_MAX_BOUNTY)
				{
				mlSetError(ML_INVALID_VALUE);
				return;
				}
			pPlayer->worth = xParam;
			// TODO: Ask James what message to send to client for changes in bounty
			return;
		case ML_BASE_ATTACK:
			if (xParam < ML_MIN_BASE_ATTACK || xParam > ML_MAX_BASE_ATTACK)
				{
				mlSetError(ML_INVALID_VALUE);
				return;
				}
			pPlayer->atk = xParam;
			return;
		case ML_BASE_DEFENSE:
			if (xParam < ML_MIN_BASE_DEFENSE || xParam > ML_MAX_BASE_DEFENSE)
				{
				mlSetError(ML_INVALID_VALUE);
				return;
				}
			pPlayer->def = xParam;
			return;
		case ML_TRAINING_POINTS:
			if (xParam < ML_MIN_TRAINING_POINTS || xParam > ML_MAX_TRAINING_POINTS)
				{
				mlSetError(ML_INVALID_VALUE);
				return;
				}
			pPlayer->train = xParam;
			mlQueueUpdate(&gpUpdateClientAttributes, xPlayerID);
			return;
		case ML_CURRENT_HP:
			if (xParam < ML_MIN_CURRENT_HP || xParam > ML_MAX_CURRENT_HP)
				{
				mlSetError(ML_INVALID_VALUE);
				return;
				}
			// TODO: If attacker is player and this player has serenity, nullify damage
			// TODO: If HP decreases, set time_safe = 0
			pPlayer->hp = xParam;
			mlQueueUpdate(&gpUpdateClientHP, xPlayerID);
			if (mlIsEnabled(ML_HP_BAR))
				mlQueueUpdate(&gpUpdateClientHPBar, xPlayerID);
			return;
		case ML_MAXIMUM_HP:
			if (xParam < ML_MIN_MAXIMUM_HP || xParam > ML_MAX_MAXIMUM_HP)
				{
				mlSetError(ML_INVALID_VALUE);
				return;
				}
			pPlayer->mhp = xParam;
			mlQueueUpdate(&gpUpdateClientLevel, xPlayerID);
			if (mlIsEnabled(ML_HP_BAR))
				mlQueueUpdate(&gpUpdateClientHPBar, xPlayerID);
			return;
		case ML_CURRENT_MP:
			if (xParam < ML_MIN_CURRENT_MP || xParam > ML_MAX_CURRENT_MP)
				{
				mlSetError(ML_INVALID_VALUE);
				return;
				}
			pPlayer->mp = xParam;
			mlQueueUpdate(&gpUpdateClientMP, xPlayerID);
			return;
		case ML_MAXIMUM_MP:
			if (xParam < ML_MIN_MAXIMUM_MP || xParam > ML_MAX_MAXIMUM_MP)
				{
				mlSetError(ML_INVALID_VALUE);
				return;
				}
			pPlayer->mmp = xParam;
			mlQueueUpdate(&gpUpdateClientLevel, xPlayerID);
			return;
		case ML_AGGRESSOR_ID:
			if (xParam < ML_MIN_PLAYER_ID || xParam > ML_MAX_PLAYER_ID)
				{
				mlSetError(ML_INVALID_VALUE);
				return;
				}
			pPlayer->target = xParam;
			return;
		case ML_MAGIC_TARGET_ID:
			if (xParam < ML_MIN_PLAYER_ID || xParam > ML_MAX_PLAYER_ID)
				{
				mlSetError(ML_INVALID_VALUE);
				return;
				}
			pPlayer->target_at = xParam;
			return;
		case ML_CHAT_SCRIPT_ID:
			if (xParam < ML_MIN_SCRIPT_ID || xParam > ML_MAX_SCRIPT_ID)
				{
				mlSetError(ML_INVALID_VALUE);
				return;
				}
			pPlayer->chat_script = xParam;
			return;
		case ML_MOVE_SCRIPT_ID:
			if (xParam < ML_MIN_SCRIPT_ID || xParam > ML_MAX_SCRIPT_ID)
				{
				mlSetError(ML_INVALID_VALUE);
				return;
				}
			pPlayer->move_script = xParam;
			return;
		case ML_EXPERIENCE:
			if (xParam < ML_MIN_EXPERIENCE || xParam > ML_MAX_EXPERIENCE)
				{
				mlSetError(ML_INVALID_VALUE);
				return;
				}
			pPlayer->exp = xParam;
			mlQueueUpdate(&gpUpdateClientExperience, xPlayerID);
			return;
		case ML_ORIGIN_X:
			if (xParam < ML_MIN_X || xParam > ML_MAX_X)
				{
				mlSetError(ML_INVALID_VALUE);
				return;
				}
			pPlayer->origin_x = xParam;
			return;
		case ML_ORIGIN_Y:
			if (xParam < ML_MIN_Y || xParam > ML_MAX_Y)
				{
				mlSetError(ML_INVALID_VALUE);
				return;
				}
			pPlayer->origin_y = xParam;
			return;
		case ML_ORIGIN_MAP_ID:
			if (xParam < ML_MIN_MAP_ID || xParam > ML_MAX_MAP_ID)
				{
				mlSetError(ML_INVALID_VALUE);
				return;
				}
			pPlayer->origin_map = xParam;
			return;
		case ML_SERENITY:
			if (xParam < ML_MIN_SERENITY || xParam > ML_MAX_SERENITY)
				{
				mlSetError(ML_INVALID_VALUE);
				return;
				}
			pPlayer->serenity = xParam;
			return;
		}

	mlSetError(ML_INVALID_ENUM);
}

MLvoid mlSetPlayercv(MLint xPlayerID, MLenum xParamName, MLchar* xpBuffer)
{
	cPlayer* pPlayer;

	if (xPlayerID < 0)
		{
		mlSetError(ML_INVALID_VALUE);
		return;
		}

	pPlayer = playerStruct(xPlayerID);

	switch (xParamName)
		{
		case ML_NAME:
			if (strlen(xpBuffer) + 1 > ML_PLAYER_NAME_LENGTH)
				{
				mlSetError(ML_INVALID_VALUE);
				return;
				}
			strncpy(pPlayer->name, xpBuffer, ML_PLAYER_NAME_LENGTH);
			return;
		case ML_TITLE:
			if (strlen(xpBuffer) + 1 > ML_TITLE_LENGTH)
				{
				mlSetError(ML_INVALID_VALUE);
				return;
				}
			strncpy(pPlayer->title, xpBuffer, ML_TITLE_LENGTH);
			return;
		case ML_IP_ADDRESS:
			if (strlen(xpBuffer) + 1 > ML_IP_ADDRESS_LENGTH)
				{
				mlSetError(ML_INVALID_VALUE);
				return;
				}
			strncpy(pPlayer->ip, xpBuffer, ML_IP_ADDRESS_LENGTH);
			return;
		case ML_CREATE_DATE:
			if (strlen(xpBuffer) + 1 > ML_CREATE_DATE_LENGTH)
				{
				mlSetError(ML_INVALID_VALUE);
				return;
				}
			strncpy(pPlayer->create_date, xpBuffer, ML_CREATE_DATE_LENGTH);
			return;
		case ML_LOG_IN_DATE:
			if (strlen(xpBuffer) + 1 > ML_LOG_IN_DATE_LENGTH)
				{
				mlSetError(ML_INVALID_VALUE);
				return;
				}
			strncpy(pPlayer->login_date, xpBuffer, ML_LOG_IN_DATE_LENGTH);
			return;
		case ML_LOG_OUT_DATE:
			if (strlen(xpBuffer) + 1 > ML_LOG_OUT_DATE_LENGTH)
				{
				mlSetError(ML_INVALID_VALUE);
				return;
				}
			strncpy(pPlayer->logout_date, xpBuffer, ML_LOG_OUT_DATE_LENGTH);
			return;
		}

	mlSetError(ML_INVALID_ENUM);
}

MLint mlGetPlayerInventory(MLint xPlayerID, MLint xSlotID)
{
	cPlayer* pPlayer;

	if (xPlayerID < 0)
		{
		mlSetError(ML_INVALID_VALUE);
		return 0;
		}

	if (xSlotID < ML_MIN_SLOT_ID || xSlotID > ML_MAX_SLOT_ID)
		{
		mlSetError(ML_INVALID_VALUE);
		return 0;
		}

	pPlayer = playerStruct(xPlayerID);

	return pPlayer->inventory[xSlotID];
}

MLvoid mlSetPlayerInventory(MLint xPlayerID, MLint xSlotID, MLint xItemID)
{
	cPlayer* pPlayer;
	cItem* pItem;
	MLint OldItemID;

	if (xPlayerID < 0)
		{
		mlSetError(ML_INVALID_VALUE);
		return;
		}

	if (xSlotID < ML_MIN_SLOT_ID || xSlotID > ML_MAX_SLOT_ID)
		{
		mlSetError(ML_INVALID_VALUE);
		return;
		}

	pPlayer = playerStruct(xPlayerID);

	// If inventory slot contains an item already, delete old item
	OldItemID = pPlayer->inventory[xSlotID];
	if (OldItemID != ML_ITEM_ID_NONE)
		mlDeleteItems(1, &OldItemID);

	// Associate new item with player's inventory
	if (xItemID != ML_ITEM_ID_NONE)
		{
		pItem = itemStruct(xItemID);
		pItem->owner = xPlayerID;
		pItem->slot = xSlotID;
		}

	pPlayer->inventory[xSlotID] = xItemID;
}

MLboolean mlIsItem(MLint xItemID)
{
	cItem* pItem;

	if (xItemID < 0)
		return ML_FALSE;

	if (xItemID >= itemLen())
		return ML_FALSE;

	pItem = itemStruct(xItemID);

	// TODO: Ask James how to determine if an item structure is "empty"
	return (pItem->name[0] == '\0');
}

MLvoid mlGenItems(MLsize xNumItems, MLint* xpItemIDs)
{
	MLint ItemID;
	MLint i;
	cItem* pItem;

	if (xNumItems <= 0)
		{
		mlSetError(ML_INVALID_VALUE);
		return;
		}

	ItemID = 0;
	i = 0;
	while (true)
		{
		if (i == xNumItems)
			return;

		if (mlIsItem(ItemID))
			{
			ItemID++;
			continue;
			}

		xpItemIDs[i] = ItemID;

		// TODO: Set default item values
		pItem = itemStruct(ItemID);
		pItem->id = 0;
		pItem->qty = -1;
		pItem->stack = 0;
		strncpy(pItem->name, "New", ML_ITEM_NAME_LENGTH);

		ItemID++;
		i++;
		}
}

MLvoid mlDeleteItems(MLsize xNumItems, MLint* xpItemIDs)
{
	MLint i;
	MLint ItemID;
	MLint NumItemIDs;
	cItem* pItem;

	if (xNumItems <= 0)
		{
		mlSetError(ML_INVALID_VALUE);
		return;
		}

	NumItemIDs = itemLen();
	for (i = 0; i < xNumItems; i++)
		{
		ItemID = xpItemIDs[i];

		if (ItemID < 0 || ItemID >= NumItemIDs)
			continue;

		pItem = itemStruct(ItemID);

		// TODO: Ask James how to determine if an item structure is "empty"
		pItem->owner = ML_PLAYER_ID_NONE;
		strncpy(pItem->name, "", ML_ITEM_NAME_LENGTH);
		}
}

MLboolean mlGetItemb(MLint xItemID, MLenum xParamName)
{
	cItem* pItem;

	if (xItemID < 0)
		{
		mlSetError(ML_INVALID_VALUE);
		return ML_FALSE;
		}

	pItem = itemStruct(xItemID);

	switch (xParamName)
		{
		case ML_IS_STACKABLE:
			return (pItem->stack == 1);
		case ML_IS_DROPABLE:
			return (pItem->stack == 2);
		}

	mlSetError(ML_INVALID_ENUM);
	return ML_FALSE;
}

MLint mlGetItemi(MLint xItemID, MLenum xParamName)
{
	cItem* pItem;

	if (xItemID < 0)
		{
		mlSetError(ML_INVALID_VALUE);
		return 0;
		}

	pItem = itemStruct(xItemID);

	switch (xParamName)
		{
		case ML_DATABASE_ID:
			return pItem->id;
		case ML_QUANTITY:
			return pItem->qty;
		case ML_IMAGE_ID:
			return pItem->graphic;
		case ML_MAP_ID:
			return pItem->map;
		case ML_X:
			return pItem->x;
		case ML_Y:
			return pItem->y;
		case ML_OWNER_ID:
			return pItem->owner;
		case ML_SLOT_ID:
			return pItem->slot;
		case ML_TYPE:
			return pItem->type;
		case ML_USE_SCRIPT_ID:
			return pItem->use_script;
		case ML_EQUIP_SCRIPT_ID:
			return pItem->equip_script;
		case ML_UNEQUIP_SCRIPT_ID:
			return pItem->unequip_script;
		case ML_PICK_UP_SCRIPT_ID:
			return pItem->pickup_script;
		case ML_DROP_SCRIPT_ID:
			return pItem->drop_script;
		case ML_LOSE_SCRIPT_ID:
			return pItem->lose_script;
		case ML_ATTACK:
			return pItem->atk;
		case ML_DEFENSE:
			return pItem->def;
		}

	mlSetError(ML_INVALID_ENUM);
	return 0;
}

MLvoid mlGetItemcv(MLint xItemID, MLenum xParamName, MLchar* xpBuffer)
{
	cItem* pItem;

	if (xItemID < 0)
		{
		mlSetError(ML_INVALID_VALUE);
		return;
		}

	pItem = itemStruct(xItemID);

	switch (xParamName)
		{
		case ML_NAME:
			strncpy(xpBuffer, pItem->name, ML_ITEM_NAME_LENGTH);
			return;
		}

	mlSetError(ML_INVALID_ENUM);
}

MLvoid mlSetItemb(MLint xItemID, MLenum xParamName, MLboolean xParam)
{
	cItem* pItem;

	if (xItemID < 0)
		{
		mlSetError(ML_INVALID_VALUE);
		return;
		}

	pItem = itemStruct(xItemID);

	switch (xParamName)
		{
		}

	mlSetError(ML_INVALID_ENUM);
}

MLvoid mlSetItemi(MLint xItemID, MLenum xParamName, MLint xParam)
{
	cItem* pItem;

	if (xItemID < 0)
		{
		mlSetError(ML_INVALID_VALUE);
		return;
		}

	pItem = itemStruct(xItemID);

	switch (xParamName)
		{
		case ML_QUANTITY:
			if (xParam < ML_MIN_QUANTITY || xParam > ML_MAX_QUANTITY)
				{
				mlSetError(ML_INVALID_VALUE);
				return;
				}
			pItem->qty = xParam;
			// TODO: Ask James whether a client update message needs to be called for changes in item quantity
			return;
		case ML_IMAGE_ID:
			if (xParam < ML_MIN_IMAGE_ID || xParam > ML_MAX_IMAGE_ID)
				{
				mlSetError(ML_INVALID_VALUE);
				return;
				}
			pItem->graphic = xParam;
			// TODO: Ask James whether a client update message needs to be called for changes in item image
			return;
		case ML_MAP_ID:
			if (xParam < ML_MIN_MAP_ID || xParam > ML_MAX_MAP_ID)
				{
				mlSetError(ML_INVALID_VALUE);
				return;
				}
			if (pItem->owner != ML_PLAYER_ID_NONE)
				{
				mlSetError(ML_INVALID_OPERATION);
				return;
				}
			pItem->map = xParam;
			// TODO: Ask James whether a client update message needs to be called for changes in item position
			return;
		case ML_X:
			if (xParam < ML_MIN_X || xParam > ML_MAX_X)
				{
				mlSetError(ML_INVALID_VALUE);
				return;
				}
			if (pItem->owner != ML_PLAYER_ID_NONE)
				{
				mlSetError(ML_INVALID_OPERATION);
				return;
				}
			pItem->x = xParam;
			// TODO: Ask James whether a client update message needs to be called for changes in item position
			return;
		case ML_Y:
			if (xParam < ML_MIN_Y || xParam > ML_MAX_Y)
				{
				mlSetError(ML_INVALID_VALUE);
				return;
				}
			if (pItem->owner != ML_PLAYER_ID_NONE)
				{
				mlSetError(ML_INVALID_OPERATION);
				return;
				}
			pItem->y = xParam;
			// TODO: Ask James whether a client update message needs to be called for changes in item position
			return;
		case ML_OWNER_ID:
			// TODO: Insure that player's inventory updates correctly
			if (xParam < ML_MIN_PLAYER_ID || xParam > ML_MAX_PLAYER_ID)
				{
				mlSetError(ML_INVALID_VALUE);
				return;
				}
			pItem->owner = xParam;
			return;
		case ML_TYPE:
			if (xParam < ML_ONE_HANDED || xParam > ML_OTHER)
				{
				mlSetError(ML_INVALID_VALUE);
				return;
				}
			// TODO: If this item is currently equipped, set INVALID_OPERATION error
			pItem->type = xParam;
			return;
		case ML_SLOT_ID:
			// TODO: Insure that player's inventory updates correctly
			if (xParam < ML_MIN_SLOT_ID || xParam > ML_MAX_SLOT_ID)
				{
				mlSetError(ML_INVALID_VALUE);
				return;
				}
			pItem->slot = xParam;
			return;
		case ML_USE_SCRIPT_ID:
			if (xParam < ML_MIN_SCRIPT_ID || xParam > ML_MAX_SCRIPT_ID)
				{
				mlSetError(ML_INVALID_VALUE);
				return;
				}
			pItem->use_script = xParam;
			return;
		case ML_EQUIP_SCRIPT_ID:
			if (xParam < ML_MIN_SCRIPT_ID || xParam > ML_MAX_SCRIPT_ID)
				{
				mlSetError(ML_INVALID_VALUE);
				return;
				}
			pItem->equip_script = xParam;
			return;
		case ML_UNEQUIP_SCRIPT_ID:
			if (xParam < ML_MIN_SCRIPT_ID || xParam > ML_MAX_SCRIPT_ID)
				{
				mlSetError(ML_INVALID_VALUE);
				return;
				}
			pItem->unequip_script = xParam;
			return;
		case ML_PICK_UP_SCRIPT_ID:
			if (xParam < ML_MIN_SCRIPT_ID || xParam > ML_MAX_SCRIPT_ID)
				{
				mlSetError(ML_INVALID_VALUE);
				return;
				}
			pItem->pickup_script = xParam;
			return;
		case ML_DROP_SCRIPT_ID:
			if (xParam < ML_MIN_SCRIPT_ID || xParam > ML_MAX_SCRIPT_ID)
				{
				mlSetError(ML_INVALID_VALUE);
				return;
				}
			pItem->drop_script = xParam;
			return;
		case ML_LOSE_SCRIPT_ID:
			if (xParam < ML_MIN_SCRIPT_ID || xParam > ML_MAX_SCRIPT_ID)
				{
				mlSetError(ML_INVALID_VALUE);
				return;
				}
			pItem->lose_script = xParam;
			return;
		case ML_ATTACK:
			if (xParam < ML_MIN_ATTACK || xParam > ML_MAX_ATTACK)
				{
				mlSetError(ML_INVALID_VALUE);
				return;
				}
			pItem->atk = xParam;
			return;
		case ML_DEFENSE:
			if (xParam < ML_MIN_DEFENSE || xParam > ML_MAX_DEFENSE)
				{
				mlSetError(ML_INVALID_VALUE);
				return;
				}
			pItem->def = xParam;
			return;
		}

	mlSetError(ML_INVALID_ENUM);
}

MLvoid mlSetItemcv(MLint xItemID, MLenum xParamName, MLchar* xpBuffer)
{
	cItem* pItem;

	if (xItemID < 0)
		{
		mlSetError(ML_INVALID_VALUE);
		return;
		}

	pItem = itemStruct(xItemID);

	switch (xParamName)
		{
		case ML_NAME:
			if (strlen(xpBuffer) + 1 > ML_ITEM_NAME_LENGTH)
				{
				mlSetError(ML_INVALID_VALUE);
				return;
				}
			strncpy(pItem->name, xpBuffer, ML_ITEM_NAME_LENGTH);
			return;
		}

	mlSetError(ML_INVALID_ENUM);
}

MLvoid mlQueueUpdate(UPDATE_LIST** xppList, MLint xID)
{
	// Search list to make sure ID is not already queued for update
	UPDATE_LIST* pList;
	pList = *xppList;
	while (pList != NULL)
		{
		if (pList->ID == xID)
			return;
		pList = pList->pNext;
		}

	// Add ID to list
	pList = new UPDATE_LIST;
	if (pList == NULL)
		{
		mlSetError(ML_OUT_OF_MEMORY);
		return;
		}
	pList->pNext = *xppList;
	pList->ID = xID;
	*xppList = pList;
}

MLvoid mlUpdate()
{
	UPDATE_LIST* pList;
	UPDATE_LIST* pTemp;

	// Send all pending client position updates
	pList = gpUpdateClientPosition;
	while (pList != NULL)
		{
		sendPosition(pList->ID);
		pTemp = pList;
		pList = pList->pNext;
		delete pTemp;
		}
	gpUpdateClientPosition = NULL;

	// Send all pending client attributes updates
	pList = gpUpdateClientAttributes;
	while (pList != NULL)
		{
		sendAttribute(pList->ID);
		pTemp = pList;
		pList = pList->pNext;
		delete pTemp;
		}
	gpUpdateClientAttributes = NULL;

	// Send all pending client level updates
	pList = gpUpdateClientLevel;
	while (pList != NULL)
		{
		sendLevel(pList->ID);
		pTemp = pList;
		pList = pList->pNext;
		delete pTemp;
		}
	gpUpdateClientLevel = NULL;

	// Send all pending client HP updates
	pList = gpUpdateClientHP;
	while (pList != NULL)
		{
		sendHP(pList->ID);
		pTemp = pList;
		pList = pList->pNext;
		delete pTemp;
		}
	gpUpdateClientHP = NULL;

	// Send all pending client MP updates
	pList = gpUpdateClientMP;
	while (pList != NULL)
		{
		sendMP(pList->ID);
		pTemp = pList;
		pList = pList->pNext;
		delete pTemp;
		}
	gpUpdateClientMP = NULL;

	// Send all pending client experience updates
	pList = gpUpdateClientExperience;
	while (pList != NULL)
		{
		sendEXP(pList->ID);
		pTemp = pList;
		pList = pList->pNext;
		delete pTemp;
		}
	gpUpdateClientExperience = NULL;

	// Send all pending player updates
	pList = gpUpdateClientPlayer;
	while (pList != NULL)
		{
		sendPlayerUpdate(pList->ID);
		pTemp = pList;
		pList = pList->pNext;
		delete pTemp;
		}
	gpUpdateClientPlayer = NULL;

	// Send all pending client HP bar updates
	pList = gpUpdateClientHPBar;
	while (pList != NULL)
		{
		sendHPbar(playerStruct(pList->ID)->map, pList->ID);
		pTemp = pList;
		pList = pList->pNext;
		delete pTemp;
		}
	gpUpdateClientHPBar = NULL;
}


#endif	// !defined(ML_H)


// In mlu.h

/*
	ML scripting utility functions
	Written by Steve Northamer
	SteveNorthamer@yahoo.com
	February 2, 2004
*/

// Header inclusion guard
#if !defined(MLU_H)
#define MLU_H


// Include files
//#include <ml.h>


// ML utility function declarations
MLvoid	mluSetPlayerPosition(MLint xPlayerID, MLint xMapID, MLint x, MLint y, MLenum xDir);
MLvoid	mluSetPlayerSprite(MLint xPlayerID, MLint xSpriteID);
MLvoid	mluSetPlayerAppearance(MLint xPlayerID, MLint xBodyID, MLint xHairID, MLint xClothesID);
MLvoid	mluOffsetPlayerHP(MLint xPlayerID, MLint xHPOffset);
MLvoid	mluSetPlayerOrigin(MLint xPlayerID, MLint xMapID, MLint x, MLint y);
// TODO: Implement utilities to calculate weapon attack/defense and total attack/defense
MLvoid	mluSetItemPosition(MLint xItemID, MLint xMapID, MLint x, MLint y);


// ML utility function defintions
MLvoid mluSetPlayerPosition(MLint xPlayerID, MLint xMapID, MLint x, MLint y, MLenum xDir)
{
	mlSetPlayeri(xPlayerID, ML_MAP_ID, xMapID);
	mlSetPlayeri(xPlayerID, ML_X, x);
	mlSetPlayeri(xPlayerID, ML_Y, y);
	mlSetPlayeri(xPlayerID, ML_DIRECTION, xDir);
}

MLvoid mluSetPlayerSprite(MLint xPlayerID, MLint xSpriteID)
{
	mlSetPlayeri(xPlayerID, ML_SPRITE_ID, xSpriteID);
}

MLvoid mluSetPlayerAppearance(MLint xPlayerID, MLint xBodyID, MLint xHairID, MLint xClothesID)
{
	mlSetPlayeri(xPlayerID, ML_SPRITE_ID, ML_SPRITE_ID_NONE);
	mlSetPlayeri(xPlayerID, ML_BODY_ID, xBodyID);
	mlSetPlayeri(xPlayerID, ML_HAIR_ID, xHairID);
	mlSetPlayeri(xPlayerID, ML_CLOTHES_ID, xClothesID);
}

MLvoid mluOffsetPlayerHP(MLint xPlayerID, MLint xHPOffset)
{
	int CurrentHP;
	int MaximumHP;

	CurrentHP = mlGetPlayeri(xPlayerID, ML_CURRENT_HP);
	MaximumHP = mlGetPlayeri(xPlayerID, ML_MAXIMUM_HP);

	// Clamp HP
	CurrentHP += xHPOffset;
	if (CurrentHP < ML_MIN_CURRENT_HP)
		CurrentHP = ML_MIN_CURRENT_HP;
	if (CurrentHP > MaximumHP)
		CurrentHP = MaximumHP;

	mlSetPlayeri(xPlayerID, ML_CURRENT_HP, CurrentHP);
}

MLvoid mluSetPlayerOrigin(MLint xPlayerID, MLint xMapID, MLint x, MLint y)
{
	mlSetPlayeri(xPlayerID, ML_ORIGIN_MAP_ID, xMapID);
	mlSetPlayeri(xPlayerID, ML_ORIGIN_X, x);
	mlSetPlayeri(xPlayerID, ML_ORIGIN_Y, y);
}

MLvoid mluSetItemPosition(MLint xItemID, MLint xMapID, MLint x, MLint y)
{
	mlSetItemi(xItemID, ML_MAP_ID, xMapID);
	mlSetItemi(xItemID, ML_X, x);
	mlSetItemi(xItemID, ML_Y, y);
}


#endif	// !defined(MLU_H)
