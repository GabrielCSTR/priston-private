/*----------------------------------------------------------------------------*
*	파일명 :  sinShop.h	
*	하는일 :  상점을 관리한다 
*	작성일 :  최종업데이트 12월
*	적성자 :  박상열 
*-----------------------------------------------------------------------------*/	

#define     MAX_SHOP_CLASS_ITEM	30  //각 클래스당 30씩

#define     SHOP_ROW			9  //임시 상점 아이템 영역 
#define     SHOP_COL			9
	
#define 	SINALLREPAIR		1 
#define 	SINREPAIR			2    
#define 	SINSELL				3      
#define 	SINBUY				4       
#define 	SINRIGHTARROW		5
#define 	SINLEFTARROW		6  
#define     SINSHOPEXIT			7

#define 	SIN_WEAPON			1 
#define 	SIN_DEFENSE			2 
#define 	SIN_ETC				3 


struct	sMYSHOP_ITEM
{
	Item	sItem;
	int			Price;
	short       Posi[2];
	DWORD		dwTemp[3];
};

struct sMYSHOP
{
	DWORD			CHAR_CODE;
	DWORD			dwTemp[6];
	sMYSHOP_ITEM	sMyShopItem[30];
};

struct sMYSHOP_ITEM_SERVER
{
	DWORD CODE;
	DWORD CkSum;
	DWORD Head;
	DWORD sTime;
	DWORD Price;
	DWORD SendFlag;
	DWORD Buyer;

	DWORD Temp[4];

};

class cSHOP
{

public:

	int OpenFlag;
	int UseItemFlag;

	int PosX;
	int PosY;

	int MatShop[10];

	int SelectShop;

	int ShopIconPosi;

	ItemData ShowShopItem[30];
	ItemData ShopItem[60];
	
	int RevWeaponCnt;
	int RevDefenseCnt;
	int RevEtcCnt;
	int MatMyShop_Button;
	
	smTEXTUREHANDLE *lpGoldEdit;

	smTEXTUREHANDLE *lpAllRepair;
	smTEXTUREHANDLE *lpRepair;

	smTEXTUREHANDLE *lpSell;
	smTEXTUREHANDLE *lpBuy;

	smTEXTUREHANDLE *lpAllRepair_D;
	smTEXTUREHANDLE *lpRepair_D;

	smTEXTUREHANDLE *lpSell_D;
	smTEXTUREHANDLE *lpBuy_D;

	smTEXTUREHANDLE *lpArrow[4];

	smTEXTUREHANDLE *lpTabAttack;
	smTEXTUREHANDLE *lpTabDefense;
	smTEXTUREHANDLE *lpTabEtc;

	smTEXTUREHANDLE *lpTabAttack_D;
	smTEXTUREHANDLE *lpTabDefense_D;
	smTEXTUREHANDLE *lpTabEtc_D;

	smTEXTUREHANDLE *lpExit;
	smTEXTUREHANDLE *lpGrid;

	smTEXTUREHANDLE *lpRepairAllInfo;
	smTEXTUREHANDLE *lpRepairInfo;
	smTEXTUREHANDLE *lpDefaultRepairAll;
	smTEXTUREHANDLE *lpDefaultRepair;

	smTEXTUREHANDLE *lpSellInfo;
	smTEXTUREHANDLE *lpBuyInfo;

	smTEXTUREHANDLE *lpTitle_Attack;
	smTEXTUREHANDLE *lpTitle_Etc;
	smTEXTUREHANDLE *lpTitle_Trade;
	smTEXTUREHANDLE *lpTitle_WareHouse;

	smTEXTUREHANDLE *lpWeightEdit;

	smTEXTUREHANDLE *lpNoUseBox;

	smTEXTUREHANDLE *lpCraftItemMain;
	smTEXTUREHANDLE *lpCraftItemButton;
	smTEXTUREHANDLE *lpCraftItemButtonInfo;
	smTEXTUREHANDLE *lpTitle_CraftItem;

	smTEXTUREHANDLE *lpSmeltingItemMain;
	smTEXTUREHANDLE *lpTitle_SmeltingItem;
	smTEXTUREHANDLE *lpSmeltingItemButtonInfo;

	smTEXTUREHANDLE *lpManufactureItemMain;
	smTEXTUREHANDLE *lpTitle_ManufactureItem;
	smTEXTUREHANDLE *lpManufactureItemButtonInfo;

	smTEXTUREHANDLE *lpMResetTitle;
	smTEXTUREHANDLE *lpMResetMain;
	smTEXTUREHANDLE *lpMResetButton;
	smTEXTUREHANDLE *lpMResetButtonInfo;

	smTEXTUREHANDLE *lpElementTitle;
	smTEXTUREHANDLE *lpElementMain;
	smTEXTUREHANDLE *lpElementButton;
	smTEXTUREHANDLE *lpElementButtonInfo;

	smTEXTUREHANDLE *lpSocketTitle;
	smTEXTUREHANDLE *lpSocketMain;
	smTEXTUREHANDLE *lpSocketButton;
	smTEXTUREHANDLE *lpSocketButtonInfo;

	smTEXTUREHANDLE *lpCaravanMain[7];
	smTEXTUREHANDLE *lpCaravanStart[2];
	smTEXTUREHANDLE *lpCaravanStop[2];
	smTEXTUREHANDLE *lpCaravanRename[2];
	
	smTEXTUREHANDLE *lpTitle_Aging;
	smTEXTUREHANDLE *lpAging_Info;
	
	smTEXTUREHANDLE *lpShopMain;
	smTEXTUREHANDLE *lpShopMain2;

	smTEXTUREHANDLE *lpMyShopExp;
	smTEXTUREHANDLE *lpMyShopExp_;
	smTEXTUREHANDLE *lpMyShopExp_T;
	smTEXTUREHANDLE *lpMyShopNoSale;
	smTEXTUREHANDLE *lpMyShopNoSale_;
	smTEXTUREHANDLE *lpMyShopNoSale_T;
	smTEXTUREHANDLE *lpMyShopSale;
	smTEXTUREHANDLE *lpMyShopSale_;
	smTEXTUREHANDLE *lpMyShopSale_T;
	smTEXTUREHANDLE *lpTitle_MyShop;
	smTEXTUREHANDLE *lpImage_MyShop;
	smTEXTUREHANDLE *lpMyShop_T;
	
public:
	cSHOP();
	~cSHOP();

	void Init();
	void Load();
	void Release();
	void Draw();
	void Close();
	void Main();
	void LButtonDown(int x , int y);
	void LButtonUp(int x , int y);
	void RButtonDown(int x , int y);
	void RButtonUp(int x, int y);
	void KeyDown(); 

	void CheckShopNpcState();

	void CopyShopItemToShow(int Index,int Kind=0);
	int GetShopItemXY(ItemData *pItem);
	void DrawShopText();
	int RecvBuyItemToServer(ItemData *pItem ,int ItemCount=1);
	int SellItemToShop(ItemData *pItem,int ItemCount=1);
	int SendBuyItemToServer(ItemData *pItem , int ItemCount=1 );
	void DeleteShopItem();
	int CheckHighRankItem(ItemData *pItem);
	int haBuyMoneyCheck(int BuyMoney);
	int haShopItemPrice(int Money);
};

class cMYSHOP
{
public:
	int OpenFlag;	
	ItemData MyShopItem[30];

	char szDoc[128];
	char szSendDoc[128];

public:
	
	//�阮처輜滂켑鮎�
	int SetMyShopItem(ItemData *pItem,int Kind = 0);

	//셋팅한다
	int LastSetMyShopItem(ItemData *pItem);

	//인벤아이템을 등록한다
	int SetShopItemToInven(ItemData *pItem);

	//상점에 등록한 아이템을 찾는다
	int SearchShopItemToInven(ItemData *pItem);

	//아이템을 서버로 보낸다 
	int SendMyShopItem(); 

	//서버에서 구매요청이 들어온 아이템을 받는다
	int RecvMyShopItem( DWORD dwCharCode , sMYSHOP_ITEM_SERVER *lpShopItem );

	//자신이 가질수 있는 금액을 리턴한다
	int GetLimitMoney(int Money);

	//물건이 다팔리면 상점을 닫는다
	int AutoCloseShop();

	//개인상점의 돈을 구해온다
	int GetTotalMyShopItemMoney();

};
/*----------------------------------------------------------------------------*
*								개인상점 클래스 
*-----------------------------------------------------------------------------*/
class cCHARSHOP{
public:
	int OpenFlag;	

public:
	ItemData CharShopItem[30];
	
	//아이템을 받는다
	int RecvShopItem(sMYSHOP *sMyShop);

	//받은 아이템을 찾는다
	int SearchMyShopItem(DWORD CODE ,DWORD Head , DWORD CheckSum);

	//개인상점에서산 아이템을 인벤토리로 셋팅한다
	int SetCharShopItemToInven(Item *pItem_Info);

	//개인상점에서 아이템을 산다
	int BuyItem(int Index);

};

extern cSHOP cShop;

extern int sinShopKind;  //현재 상점의 종류  1  무기 2 방어 3 물약 (defalt 는 상점)

extern int TalkNpcState; //현재 상점 NPC와 함께 있을경우 

extern int ShopGoldEdit[2][4];

extern int ShopArrowPosi; //상점 화살표 방향 

extern int BuyItemServerFlag; //서버에서 물건을 살때 메세지를 받지않으면 살수없다 

extern cMYSHOP cMyShop;
extern cCHARSHOP cCharShop;

extern sMYSHOP     sMyShop;       //보내는 MyShop 구조체
extern sMYSHOP     sRecvMyShop;   //받는 MyShop 구조체
extern int MyShopSendButton;

extern int MyShopExpBox;
extern int MyShopItemSellMoney2;
extern sMYSHOP_ITEM_SERVER sMyShop_Server;
extern Item MyShopPotion;
extern int MyShopItemCancelIndex[2];
