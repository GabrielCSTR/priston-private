#define MAX_TRADE_ITEM			20
#define MAX_CRAFTITEM_INFO		300
#define MAX_AGINGITEM_INFO		100
#define MAX_MAKEITEM_INFO		100

#define T_SET_BOX				0
#define T_MONEY_POSI			1
#define T_MONEY_TEXT_POSI		2
#define T_WEIGHT_TEXT_POSI		3
#define T_CHECK_POSI			4
#define T_CLOSE_POSI			5

#define MAX_SHELTOM				16
#define MAX_AGING				24
#define MAX_RUNE				14
#define MAX_RECIPE_KIND			11
#define MAX_RECIPE_ITEM			60
#define MAX_HANDMADEITEM		176

#define MAX_SEEL_COUNT			4
#define MAX_MIX_STONE			16
#define MAX_ELEMENT				6
#define MAX_SOCKET				5

struct sTRADE
{
	ItemData TradeItem[MAX_TRADE_ITEM];
	int Money;
	int Weight;
	int CheckFlag;
	int CheckMoney;
};
struct sWAREHOUSE
{
	ItemData WareHouseItem[100];
	//int Money;
	//short Weight[2];
	//int BuyAreaCount;
	//int FakeMoney;
};

struct sCRAFTITEM
{
	ItemData CraftItem[15];
	int   SheltomIndex[16];

};

struct sCRAFTITEM_SERVER
{
	int size, code;
	int DocIndex;
	int Result;
	ItemData DesCraftItem;
	DWORD SheltomCode[12];
	DWORD Head[12];
	DWORD CheckSum[12];
	int  Index;
	int  Money;

	DWORD A_StoneItemCode;
	DWORD A_StoneHead;
	DWORD A_StoneCheckSum;
};

struct sCRAFTITEM_INFO
{
	DWORD MainItemCode[10];
	int AddItem[MAX_MIX_STONE];	// 合成石头的数量
	int PlusElementCode[8];
	float AddElement[8];
	int ElementKind[8];
	char Name[128];
	char Doc[256];
};

struct sMIXTURE_RESET_ITEM
{
	ItemData	MixtureResetItem[2];
};

struct sMIXTURE_RESET_ITEM_SERVER
{
	int		size, code;
	int		DocIndex;
	int		Result;
	int		Index;

	ItemData	DesMixtureResetItem;

	DWORD	dwMixtureResetStoneItemCode;
	DWORD	dwMixtureResetStoneHead;
	DWORD	dwMixtureResetStoneCheckSum;
};
struct ELEMENT_ITEM_SERVER
{
	int		size,code;
	int		Result;
	int		Index;
	int		Money;
	ItemData	DesItem;
	DWORD	SheltomCode[5];
	DWORD	Head[5];
	DWORD	CheckSum[5];
};
struct SOCKET_ITEM_SERVER
{
	int size,code;
	int Result;
	int Index;
	int Money;
	ItemData DesItem;
	DWORD SheltomCode[4];
	DWORD Head[4];
	DWORD CheckSum[4];
};
struct sCARAVAN
{
	ItemData	Item[100];
};
struct sAGINGITEM
{
	ItemData AgingItem[15];
	int   SheltomIndex[12];
	int   AgingOkFlag;

};

struct sAGINGITEM_INFO
{
	DWORD MainItemCode;
	int PlusElementCode[8];
	float AddElement[8];
	int ElementKind[8];
	char Doc[128];
};

struct sMAKEITEM_INFO
{
	DWORD CODE[15];
	DWORD Result_CODE;
};

struct sPOSTBOX_ITEM
{
	char	szName[64];
	DWORD	CODE;
};

struct sRECON_ITEM
{
	DWORD  dwCODE;
	int	   iLevel[2];
	int	   iCount;
	int    iPrice;
};
struct SSmeltingItem
{
	ItemData SmeltingItem[5];
	int   SheltomIndex[12];
};
struct sSMELTINGITEM_SERVER
{
	int size, code;
	int DocIndex;
	int Result;
	ItemData DesSmeltingItem;
	DWORD SmeltingCode[5];
	DWORD Head[5];
	DWORD CheckSum[5];
	int  Index;
	int  Money;

	DWORD A_StoneItemCode;
	DWORD A_StoneHead;
	DWORD A_StoneCheckSum;
};
struct SManufactureItem
{
	ItemData	ManufactureItem[4];
	int		RuneIndex[12];
};
struct SManufactureItem_Server
{
	int size, code;
	int DocIndex;
	int Result;
	ItemData DesManufactureItem;
	DWORD RuneCode[4];
	DWORD Head[4];
	DWORD CheckSum[4];
	int  Index;
	int  Money;

	DWORD A_StoneItemCode;
	DWORD A_StoneHead;
	DWORD A_StoneCheckSum;
};
struct SManufacture_Rune
{
	int RecipeCode;
	int NeedRuneIndex[3];
};
struct SManufacture_CreateItemCode
{
	DWORD RecipeKind[2];
	DWORD CheckRuneCode[8][3];
	DWORD CreateItemCode[2][8];
};
struct SManufacture_ResultItemInfo
{
	DWORD ItemCode;
	int	Weight;
	int Price;
	char ItemName[32];
};
struct SManufacture_ResultItemInfo_Server
{
	smTRANS_COMMAND		smTransCommand;
	DWORD ItemCode[MAX_HANDMADEITEM];
	int Weight[MAX_HANDMADEITEM];
	int Price[MAX_HANDMADEITEM];
	char ItemName[MAX_HANDMADEITEM][32];
};

class cAGING
{
public:
	int OpenFlag;
	int AgingItemCheckSum;
	smTEXTUREHANDLE	*lpGraySheltom[MAX_SHELTOM];
public:
	int  AginStoneKind;
public:
	int AgingItem(int MakeItemFlag =0);
	int CheckItem(ItemData *pItem);
	int sinRecvAgingItem(sCRAFTITEM_SERVER *pCraftItem_Server);
};
class cMIXTURERESET
{
public:
	int	OpenFlag;
	int	MixtureResetItemCheckSum;
	int	HaveMixtureResetStone;

public:
	int ResetItem(sMIXTURE_RESET_ITEM_SERVER *pResetItem);
	int	sinRecvMixtureItemReset(sMIXTURE_RESET_ITEM_SERVER *pMixtureResetItem);
};
class cELEMENT
{
public:
	int OpenFlag;
	int ElementItemCheckSum;
	ItemData ElementItem[MAX_ELEMENT];
	ItemData ElementItemBackUp[MAX_ELEMENT];
	int ElementCheckFlag;
	ELEMENT_ITEM_SERVER ElementItemServer;
public:
	int RecvItem(ELEMENT_ITEM_SERVER *pItemServer);
	int CreateElementItem();
};
class cSOCKET
{
public:
	int OpenFlag;
	int SocketItemCheckSum;
	ItemData SocketItem[MAX_SOCKET];
	ItemData SocketItemBackUp[MAX_SOCKET];
	int SocketCheckFlag;
	SOCKET_ITEM_SERVER SocketItemServer;
public:
	int CheckItem();
	int RecvItem(SOCKET_ITEM_SERVER *pItemServer);
	int CreateSocketItem();
};
class CSmeltingItem
{
public:
	int OpenFlag;
	int SmeltingItemCheckSum;
	int m_SmeltingPrice;
public:
	int sinRecvSmeltingItem( sSMELTINGITEM_SERVER *pSmeltingItem_Server );
	int CheckSmeltingPrice();
	int GetSheltomIndex( DWORD SmeltingItemCode );
};
class CManufacture
{
public:
	int m_OpenFlag;
	int m_ManufactureItemCheckSum;
	int m_ManufacturePrice;
public:
	void RuneIndexInit();
	int sinRecvManufactureItem(SManufactureItem_Server *pManufactureItem_Server);
	int GetRecipeIndex(DWORD Code);
	int GetManufactureCheckEmptyArea();
	SManufacture_ResultItemInfo ManufactureCheckItem(ItemData *pItemCode, CharacterData *charInfo);
};
class cCRAFTITEM
{
public:
	int OpenFlag;
	int CraftItemCheckSum;
	int ForceFlag;
	int ForceItemPrice;
	int iReconItemFlag;
public:
	int MixingItem();

	int sinRecvCraftItem(sCRAFTITEM_SERVER *pCraftItem_Server);


	int CheckForceOrbPrice();
	int CheckForceOrbPrice(ItemData *pItem);
};

class cWAREHOUSE
{
public:
	int OpenFlag;
	int WareHouseCheckSum;
	int Money;
	short Weight[2];
	int SaveFlag;
	sWAREHOUSE WareHouse;
	
};
class cCARAVAN
{
public:
	int		OpenFlag;
	int		SelectFlag;
	int		SelectMode;
	int		SaveFlag;
	int		dwChkSum;
	int		CaravanCheckSum;
	int		SelectTypeFlag;
	sCARAVAN sCaravan;
};
class cTRADE
{
public:
	int OpenFlag;
	int MatTrade[4];
	int MatWareHouse[3];
	int MatTradebuttonMain;
	int MatTradebuttonCancel;

	smTEXTUREHANDLE *lpbuttonCancel;
	smTEXTUREHANDLE *lpbuttonCancelInfo;
	smTEXTUREHANDLE *lpbuttonOk;
	smTEXTUREHANDLE *lpCheck;

	smTEXTUREHANDLE *lpCheck_Glay;
	smTEXTUREHANDLE *lpCheckInfo;
	smTEXTUREHANDLE *lpDelayCheck;

	smTEXTUREHANDLE *lpCenterBox;

	ItemData CheckItem[100];
	ItemData CheckRecvItem[MAX_TRADE_ITEM];

	int   TradeRequestFlag;
	DWORD TradeCharCode;
	char  szTradeCharName[64];

	int   TradeItemCheckSum;
public:
	cTRADE();
	~cTRADE();
};

int ManufactureItemResultInfo( SManufacture_ResultItemInfo_Server *pResultItemInfo );

int CopyMixItemCheckDelete(ItemData *pItem);
int sinMakeItemCheck();
int sinPosBoxNpc();
extern SManufacture_ResultItemInfo g_Manufacture_ItemInfo[MAX_HANDMADEITEM];
extern cTRADE cTrade;
extern sTRADE sTrade;
extern sTRADE sTradeRecv;

extern int RequestTradeButtonFlag;
	   
extern cWAREHOUSE cWareHouse;
extern sWAREHOUSE sWareHouse;
extern ItemData *BackUpInvenItem2;

extern int ForceOrbPriceIndex[];
extern DWORD SheltomCode2[];
extern int MagicForceOrbPriceIndex[];
extern DWORD MagicSheltomCode[];
extern cCRAFTITEM cCraftItem;

extern CSmeltingItem SmeltingItem;
extern SSmeltingItem S_smeltingItem;
extern sSMELTINGITEM_SERVER sSmeltingItem_Send;
extern sSMELTINGITEM_SERVER sSmeltingItem_Recv;

extern CManufacture ManufactureItem;
extern SManufactureItem sManufactureItem;
extern SManufactureItem_Server sManufactureItem_Send;
extern SManufactureItem_Server sManufactureItem_Recv;
extern SManufacture_Rune sManufacture_Rune[MAX_RECIPE_KIND];
extern sCRAFTITEM sCraftItem;
extern sCRAFTITEM_INFO sCraftItem_Info[MAX_CRAFTITEM_INFO];

extern sCRAFTITEM_SERVER sCraftItem_Send;
extern sCRAFTITEM_SERVER sCraftItem_Recv;

extern sCRAFTITEM_SERVER sAging_Send;
extern sCRAFTITEM_SERVER sAging_Recv; 

extern int ShowItemCraftMessageFlag;
extern int ShowItemAgingMessageFlag;
extern int ShowItemSmeltingMessageFlag;
extern int ShowItemManufactureMessageFlag;
extern int ShowItemOverSpace;

extern int TempShowMoney;
extern int ItemPickUpFlag;
extern int WareHouseSaveFlag;

extern cAGING	cAging;
extern sAGINGITEM sAgingItem;
extern sAGINGITEM_INFO sAgingItem_Info[MAX_AGINGITEM_INFO];

extern char szAgingItemBuff[128];
extern POINT CraftItemMessageSize;

extern int AgingCheckSheltomFlag;
extern int AgingSheltomCnt2;
extern int MixItemNoCopyFlag;
extern int CheckMixItemCopyFlag;
extern sMAKEITEM_INFO sMakeItem_Info[MAX_MAKEITEM_INFO];

// 属性系统
extern cELEMENT cElement;
extern cSOCKET cSocket;
extern cCARAVAN cCaravan;

extern cMIXTURERESET cMixtureReset;
extern sMIXTURE_RESET_ITEM	sMixtureResetItem;
extern sMIXTURE_RESET_ITEM sMixtureResetItemBackUp;
extern int	MixtureResetCheckFlag;
extern sMIXTURE_RESET_ITEM_SERVER	sMixtureReset_Send;
extern sMIXTURE_RESET_ITEM_SERVER	sMixtureReset_Recv;

extern char *PostBoxDocFilePath[];

extern sPOSTBOX_ITEM sPostbox_Item[50];
extern int PostBoxIndexCnt;
extern DWORD ExpressItemCode;
extern char  szExpressItemName[64];

extern sCRAFTITEM_SERVER sWingItem_Send;
extern sCRAFTITEM_SERVER sWingItem_Recv;

extern int DownTradePosi[6][4];
extern DWORD SheltomCode2[];
extern DWORD MagicSheltomCode[];
extern DWORD BillingMagicSheltomCode[];
extern int ForceItemPrice2;
extern sRECON_ITEM sReconItem[MAX_SEEL_COUNT];
extern int		MixCancelButtonDelayFlag;