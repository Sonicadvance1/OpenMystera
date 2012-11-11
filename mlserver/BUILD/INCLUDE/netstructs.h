#ifndef _MLNETSTRUCTS_
#define _MLNETSTRUCTS_

#include "gamedefs.h"

enum {
	NULL_MSG,
	CHAT_MSG,
	PLYR_MSG,
	ATTR_MSG,
	LEFT_MSG,
	UPDT_MSG,
	LOGN_MSG,
	ALGN_MSG,
	NWAC_MSG,
	FLAG_MSG,
	PARM_MSG,
	CHAR_MSG,
	MYCR_MSG,
	CORE_MSG,
	CMND_MSG,
	UPLD_MSG,
	VRSN_MSG,
	ITEM_MSG,
	ITMR_MSG,
	INVT_MSG,
	INVR_MSG,
	ATCK_MSG,
	HITP_MSG,
	MANP_MSG,
	EFCT_MSG,
	EXPR_MSG,
	LEVL_MSG,
	PICK_MSG,
	DROP_MSG,
	EQUI_MSG,
	ACSS_MSG,
	SNFO_MSG,
	FILE_MSG,
	HBAR_MSG,
	NCHR_MSG,
	PLYV_MSG,
	TRGT_MSG,
	ITMV_MSG,
	INVV_MSG,
	SNDF_MSG,
	SHAD_MSG,
	DLOG_MSG,
	SLOT_MSG,
	QUIT_MSG,
	IQTY_MSG
};

#pragma pack(push)

// Precede each struct with a #pragma pack(1)
// --------------------------
// YOUR STRUCTURES BELOW HERE!
// --------------------------
#pragma pack(1)
struct chat_msg
{
	unsigned char type;
	unsigned char size;
};
#pragma pack(1)
struct plyr_msg//player look update msg
{
	unsigned char type;
	unsigned short index;
	signed short sprite;
	signed short body;
	signed short hair;
	signed short clothes;
	char name[18];
};
#pragma pack(1)
struct attr_msg
{
	unsigned char type;
	unsigned short train;
	unsigned char str;
	unsigned char dex;
	unsigned char con;
	unsigned char itl;
	unsigned char wis;
};
#pragma pack(1)
struct left_msg
{
	unsigned char type;
	unsigned short index;
};
#pragma pack(1)
struct logn_msg//player login
{
	unsigned char type;
	unsigned char slot;
};
#pragma pack(1)
struct algn_msg//account login
{
	unsigned char type;
	char id[8];
	char pass[16];
};
#pragma pack(1)
struct nwac_msg//new account
{
	unsigned char type;
	char pass[16];
	char conf[16];
	char email[64];
};
#pragma pack(1)
struct flag_msg
{
	unsigned char type;
	unsigned char flag;
};
#pragma pack(1)
struct parm_msg
{
	unsigned char type;
	unsigned char flag;
	unsigned char parm;
};
#pragma pack(1)
struct mycr_msg
{
	unsigned char type;
	pos p;
	unsigned char dir;
};
#pragma pack(1)
struct core_msg//not using
{
	unsigned char type;
	unsigned short map;
	unsigned short num;
	//unsigned short index;
	//cBasePlayer *base;
};
#pragma pack(1)
struct cmnd_msg
{
	unsigned char type;
	unsigned char size;
};
#pragma pack(1)
struct upld_msg
{
	unsigned char type;
	unsigned short size;
};
#pragma pack(1)
struct vrsn_msg
{
	unsigned char type;
	float version;
};
#pragma pack(1)
struct item_msg
{
	unsigned char type;
	unsigned short graphic;
	unsigned char x;
	unsigned char y;
};
#pragma pack(1)
struct itmr_msg
{
	unsigned char type;
	unsigned char x;
	unsigned char y;
};
#pragma pack(1)
struct invt_msg
{
	unsigned char type;
	unsigned short graphic;
	signed short index;
	char name[20];
	signed long qty;
};
#pragma pack(1)
struct invr_msg
{
	unsigned char type;
	signed short index;
	signed long qty;
};
#pragma pack(1)
struct atck_msg
{
	unsigned char type;
	unsigned short index;
};
#pragma pack(1)
struct hitp_msg
{
	unsigned char type;
	signed long hp;
};
#pragma pack(1)
struct manp_msg
{
	unsigned char type;
	signed long mp;
};
#pragma pack(1)
struct efct_msg
{
	unsigned char index;
	unsigned char x;
	unsigned char y;
};
#pragma pack(1)
struct expr_msg
{
	unsigned char type;
	unsigned long exp;
};
#pragma pack(1)
struct levl_msg
{
	unsigned char type;
	unsigned long exp;
	unsigned short lvl;
	signed long hp,mhp,mp,mmp;
};
#pragma pack(1)
struct pick_msg
{
	unsigned char type;
};
#pragma pack(1)
struct drop_msg
{
	unsigned char type;
	unsigned char index;
};
#pragma pack(1)
struct npcx_msg
{
	unsigned char type;
	unsigned char index;
	unsigned char chr;
	char name[20];
};
#pragma pack(1)
struct equi_msg
{
	unsigned char type;
	signed char eLeft,eRight,eHead,eBody,eSpecial;
};
#pragma pack(1)
struct acss_msg
{
	unsigned char type;
	signed char access;
};
#pragma pack(1)
struct snfo_msg
{
	unsigned char type;
	char tilebmp[16];
	char charbmp[16];
	char itembmp[16];
	char afctbmp[16];
};
#pragma pack(1)
struct file_msg
{
	unsigned char type;
	char name[16];
	unsigned int size;
};
#pragma pack(1)
struct hbar_msg
{
	unsigned char type;
	unsigned short index;
	unsigned char hp;
};
#pragma pack(1)
struct nchr_msg
{
	unsigned char type;
	char name[20];
	unsigned char slot;
	signed short body;
	signed short hair;
	signed short clothes;
};

#pragma pack(1)
struct updt_msg
{
	unsigned char type;
	unsigned short qty;
};
#pragma pack(1)
struct xyps_msg
{
	unsigned short index;
	unsigned char x;
	unsigned char y;
};
#pragma pack(1)
struct plyv_msg
{
	unsigned char type;
	unsigned short size;
};
#pragma pack(1)
struct trgt_msg
{
	unsigned char type;
	unsigned short index;
};
#pragma pack(1)
struct pvms_msg//player look update msg
{
	unsigned short index;
	signed short sprite;
	signed short body;
	signed short hair;
	signed short clothes;
	char name[18];
};
#pragma pack(1)
struct itmv_msg//itemv msg
{
	unsigned char type;
	unsigned short size;
};
#pragma pack(1)
struct ivms_msg//itemv msg
{
	unsigned short graphic;
	unsigned char x;
	unsigned char y;
};
#pragma pack(1)
struct sndf_msg//sound msg
{
	unsigned char type;
	unsigned char effect;
};
#pragma pack(1)
struct shad_msg//shading msg
{
	unsigned char type;
	unsigned char shade;
};
#pragma pack(1)
struct dlog_msg//dialog msg
{
	unsigned char type;
	unsigned char dialog;
};
#pragma pack(1)
struct slot_msg//dialog msg
{
	unsigned char type;
	char name[4][20];
	unsigned short lvl[4];
	signed short sprite[4];
	signed short body[4];
	signed short hair[4];
	signed short clothes[4];
};
#pragma pack(1)
struct quit_msg//quit msg
{
	unsigned char type;
};
#pragma pack(1)
struct iqty_msg//inventory qty set
{
	unsigned char type;
	signed short index;
	signed long qty;
};
#pragma pack(1)
struct efpk_msg
{
	unsigned char type;
	unsigned char qty;
};
#pragma pack(pop)

#endif
