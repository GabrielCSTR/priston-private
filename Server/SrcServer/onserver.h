//PK가능한 레벨 
#define	LIMIT_PK_LEVEL	20				// pluto PK허용 필드 전부

#define AUTOPLAYER_MAX		2048
#define AUTOPLAYER_MASK		2047


//유료 아이템 기본 사용시간 설정
#define	PRIME_ITEM_TIME_THIRDEYES		(60*60*24)
#define	PRIME_ITEM_TIME_EXPUP			(60*60*24)

#define	PRIME_ITEM_TIME_THIRDEYESx7		(60*60*24*7)
#define	PRIME_ITEM_TIME_EXPUPx7			(60*60*24*7)

#define	PRIME_ITEM_TIME_VAMPCUSPID		(60*60*3)	// pluto 뱀피릭 커스핏 3시간
#define	PRIME_ITEM_TIME_MANARECHARG		(60*60*3)	// pluto 마나 리차징 포션 3시간

#define	PRIME_ITEM_TIME_VAMPCUSPIDx2	(60*60*6)	// pluto 뱀피릭 커스핏 1일
#define	PRIME_ITEM_TIME_MANARECHARGx2	(60*60*6)	// pluto 마나 리차징 포션 1일
#define PRIME_ITEM_TIME_6HOUR			(60*60*6)

#define	PRIME_ITEM_TIME_PACKAGE1		(60*60*3)
#define	PRIME_ITEM_TIME_PACKAGE2		(60*60*24)
#define	PRIME_ITEM_TIME_PACKAGE3		(60*60*24*7)
#define	PRIME_ITEM_TIME_PACKAGE4		(60*60*24*30)
#define	PRIME_ITEM_TIME_PACKAGE5		(60*60*1) // 장별 - 경험치증가 포션(100% 1시간)


#define	PRIME_ITEM_PACKAGE_NONE			0
#define	PRIME_ITEM_PACKAGE_BRONZE		1
#define	PRIME_ITEM_PACKAGE_SILVER		2
#define	PRIME_ITEM_PACKAGE_GOLD			3
#define	PRIME_ITEM_PACKAGE_ULTRA		4

// pluto 마나 리듀스 포션
#define PRIME_ITEM_MIGHTOFAWELL			5
#define PRIME_ITEM_MANAREDUCE			6


//SOD 관련
#define	rsSOD_FIELD			30
#define	rsSOD_VILLAGE		9
#define	rsBABEL_FIELD		27
#define	rsKELVEZU_FIELD		36
#define	rsMOKOVA_FIELD		38
//공성
#define	rsCASTLE_FIELD	33
#define	rsACTION_FIELD	39

//퀘스트용 대전 격투장
#define	QUEST_ARENA_FIELD		32
#define	QUEST_ARENA_NPC_POS_X	(22091*fONE)
#define	QUEST_ARENA_NPC_POS_Z	(9673*fONE)


#define	WHERE_TRADE				300
#define	WHERE_GIFT_EXPRESS		600
#define	WHERE_AGINGITEM			400
#define	WHERE_CRAFTITEM			420
#define	WHERE_FORECORB			440
#define	WHERE_LEARNSKILL		460
#define	WHERE_WARPGATE			470
#define	WHERE_BUY_ITEM			200
#define	WHERE_BUY_POTION		210
#define	WHERE_SELL_ITEM			220
#define	WHERE_LOAD_PLAYER		100
#define	WHERE_THROW_ITEM		120
#define	WHERE_GET_ITEM			130
#define	WHERE_STAR_POINT		620
#define	WHERE_CLAN_MONEY		630
#define	WHERE_GIVE_MONEY		640
#define	WHERE_PERSONAL_SHOP		320
#define	WHERE_OPEN_WAREHOUES	500
#define WHERE_ELEMENT			650
#define WHERE_DEATH				700
#define WHERE_SOCKET			750


#define STG_START_POINT_MAX			200

#define SIN_CLANSKILL_ABSORB			1
#define SIN_CLANSKILL_DAMAGE			2
#define SIN_CLANSKILL_EVASION			3

#define SIN_GURAD_CRISTAL_ICE		    1
#define SIN_GURAD_CRISTAL_LIGHTNING		2
#define SIN_GURAD_CRISTAL_FIRE			3


#define QUESTBIT_ELEMENTARY_A			1       //피곤한 창고지기
#define QUESTBIT_ELEMENTARY_B			2       //두련운 기운
#define QUESTBIT_ELEMENTARY_C			4       //사탕 배달
#define QUESTBIT_ELEMENTARY_D			8       //고블린 동산 
#define QUESTBIT_ELEMENTARY_E			16      //언데드의 위협
#define QUESTBIT_ELEMENTARY_F			32      //외눈박이 괴물
#define QUESTBIT_ELEMENTARY_G			64      //잃어버린 망치
#define QUESTBIT_FURYOFPHANTOM          128      //퓨리의 환영
#define QUESTBIT_ELEMENTARY_H			256
#define QUESTBIT_ELEMENTARY_I			512
#define QUESTBIT_ELEMENTARY_J			1024
#define QUESTBIT_ELEMENTARY_K			2048
#define QUESTBIT_ELEMENTARY_L			4096
#define HAQUEST_CODE_ELEMENTARY_A		0x0020
#define HAQUEST_CODE_ELEMENTARY_B	    0x0021
#define HAQUEST_CODE_ELEMENTARY_C	    0x0022
#define HAQUEST_CODE_ELEMENTARY_D   	0x0023
#define HAQUEST_CODE_ELEMENTARY_E   	0x0024
#define HAQUEST_CODE_ELEMENTARY_F		0x0025
#define HAQUEST_CODE_ELEMENTARY_G		0x0026
#define HAQUEST_CODE_FURYOFPHANTOM      0x0027
#define HAQUEST_CODE_ELEMENTARY_H		0x0028
#define HAQUEST_CODE_ELEMENTARY_I		0x0029
#define HAQUEST_CODE_ELEMENTARY_J		0x0030
#define HAQUEST_CODE_ELEMENTARY_K		0x0031
#define HAQUEST_CODE_ELEMENTARY_L		0x0032

const int ForceOrbUseLevel[][2] =
{
	{1,19},{1,29},{1,39},{1,49},{50,200},{50,200},{50,200},{50,200},{50,200},{50,200},{50,200},{50,200},{50,200},{50,200},{50,200},{50,200},
};

const int ForceOrbUseTime[] = { 500,500,500,500,700,900,1800,2400,3600,4800,6000,7200,8400,10000,12000,14400 };

const int ForceOrbDamage[] = { 2,4,7,10,15,25,40,60,80,100,120,140,160,180,200,220 };

const int BoosterItem_UseTime[] = { 3600,10800,86400 };
const int BoosterItem_DataPercent[] = { 15,15,15 };

const int nSkillDelay_UseTime[] = { 300,10800,86400 };

struct STG_CHAR_INFO {

	CharacterData	sCharacterData;					//기본 캐릭터 정보 이름 모델 레벨 등등

	int		PosiState;						//속성 종류 ( 적/NPC )

	int		StartFixed;						//시작 위치 고정이면 TRUE ( FALSE면 수시로 변경)
	POINT	StartPosi;						//시작 위치 ( 고정일 경우 )

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

#define STG_ITEM_MAX	1024

struct Rune_Formula
{
	DWORD Recipe;
	DWORD Rune[3];
};

#define INVENTORY_MAXITEM 100

#define FIX_CHAR_MAX	100

struct	rsSERVER_NOTICE
{
	DWORD Counter;
	char szMessage[256];
};

extern rsSERVER_NOTICE rsNoticeMessage;

int ReformItem(Item *lpItemInfo);

extern rsSERVER_CONFIG		rsServerConfig;				//서버 설정 구조

extern int Server_SqlReady;
extern HWND	hDebugWnd;

extern int Server_SqlReady;

extern DWORD		dwKelvezuPlayTime;
extern int			KelvezuPlayField;

extern DWORD		dwWeatherPlayTime;
extern DWORD		dwRainTime;

extern int	rsSodTeamScore[4];

///////////////////////////////////////////////////////////////////////

//블레스 캐슬 용병 제한수량 정의
#define srCASLTE_SOLDER_CLAN_MAX	20
#define srCASLTE_SOLDER_MAX			1
#define srCASLTE_SOLDER_KIND_MAX	5


struct	rsCURRENCY_LOG {	
	//사용된 돈 통화량 기록
	INT64	int64_CraftMoney;
	INT64	int64_AgingMoney;
	INT64	int64_ShopMoney;
	INT64	int64_ShopPotionMoney[3];

	INT64	int64_ForceOrbMoney;
	INT64	int64_WarpgateMoney;
	INT64	int64_LearnSkillMoney;
};

extern	rsCURRENCY_LOG	CurrencyLog;

//////////////////////////////////////////////////////////////////////////

#define	srMONSTER_KILL_QUE_MAX		1024
#define	srMONSTER_KILL_QUE_MASK		1023

struct	rsKILL_MONSTER_INFO {
	DWORD	dwAutoCharCode;
	DWORD	dwCharSoundCode;
	DWORD	dwMonObjectSerial;
	DWORD	dwUserObjectSerial;
	int		x,y,z,Area;
	int		PartyFlag;
	DWORD	dwParam[4];
};

struct	TRANS_KILL_MONSTER_INFO {
	int		size,code;
	DWORD	tCode;
	int		KillInfo_Count;
	int		Temp[4];
};

//////////////////////////////////////////////////////////////////////////

/////////////// 벨라트라 몬스터 배치 구조체 //////////////////////////////
//마지막 카운터
#define	rsHARDCORE_COUNT_END	8	
#define	hCORE_ROUND_MAX		9

struct	_sHCORE_MONSTER {
	char	szName[32];
	CharacterData	*lpCharInfo;
	int		perCount;
};

struct	sHCORE_MONSTER {

	_sHCORE_MONSTER	hCoreMonster1;
	_sHCORE_MONSTER	hCoreMonster2;
	_sHCORE_MONSTER	hCoreMonster3;
	_sHCORE_MONSTER	hCoreMonster4;
	_sHCORE_MONSTER	hCoreMonsterBoss;

	int		PerCount;
	int		StartHour;
	int		State;
	int		MaxMonster;
	int		DelayTime;			//시작시 딜레이 시간
};

extern int rsCristalEvent;

int rsProcessQuest(User *lpPlayInfo , Unit *lpChar , int QuestCode , int QuestParam );
//상점 아이템 목록 클라이언트에 전송
int SendShopItemList(User *pcUser, Unit *lpChar );
//스킬 수련 NPC
int SendSkillMenu(User *pcUser, Unit *lpChar , int Mode );
//창고 열기
int SendOpenWareHouse(User *pcUser);
//아이템 조합창 열기
int SendOpenMixItem(User *pcUser, int MixFlag );
//모금함 열기
int SendOpenCollectMoney(User *lpPlayInfo,int sEvent,int sEventCount);
//경품이벤트
int SendOpenEventGift(User *pcUser);
//에이징 창 열기
int SendOpenAgingItem(User *pcUser);
// 댔왝溝固
int SendOpenSocketItem(User *pcUser);
//클랜 메뉴 열기
int SendOpenClanMenu(User *pcUser);
//이벤트 NPC
int SendOpenEvent(Unit *lpChar , User *lpPlayInfo , int EventFlag );
// pluto 아이템 제련창 열기
int SendOpenSmelting(User *pcUser);
// pluto 아이템 제작창 열기
int SendOpenManufacture(User *pcUser);
//SoD 진행 상황 출력
TRANS_SOD_RESULT *rsSod_GetRealTimeScore(User *lpPlayInfo );
// 석지용 - 믹스쳐 리셋 창 열기
int SendOpenMixtureItemReset(User *pcUser);
// 댔역橄昑膠틔
int SendOpenElementItem(User *pcUser);
// 댔역녘膠꾑욋
int SendOpenCaravanItem(User *pcUser,int Kind);
// �阮처琬粘Ｊ�
int rsSetCaravanHopyMode(User *lpPlayInfo,int Kind);
// 랙箇우醵句口
int SendQuickMessage2(User *lpPlayInfo,char *szMessage,int iType = 0);
int RecordHackLogFile(User *lpPlayInfo , void *lpTransCommand );
int RecvRangeAttack(User *lpPlayInfo , TRANS_SKIL_ATTACKDATA *lpTransSkilAttackData );
int RecvRangeAttackUser(User *lpPlayInfo , TRANS_SKIL_ATTACKDATA *lpTransSkilAttackData );
int	rsPlayHealing( smTRANS_COMMAND *lpTransCommand );
int srDisplayBillingTime(User *lpPlayInfo , int Add_BillingTime );
int	rsSendCommandUser2(User *lpPlayInfo , smTRANS_COMMAND *lpTransCommand );
int	rsShutDown();
DWORD GetSwapIPCode( char *szIP );
int rsEventLogOn_Sucess(User *lpPlayInfo );
int rsGetSoD_AreaCode( int x, int y, int z ) ;
int rsSendRangeDamage(Unit *lpChar , User *lpMainPlayInfo , int Range , int SubDamgePers );
int rsGetMonsterLifeRegen(Unit *lpChar );
int	rsClanMoneyLog(User *lpPlayInfo , int Money , int RestMoney );
int rsGetServerPotion(User *lpPlayInfo , DWORD dwPotionCode );
int RecordHackLogFile(User *lpPlayInfo , void *lpBuff );
int rsGetlpLinkChar(User *lpPlayInfo, Unit *lpChar);
int	rsUpdateServerParam(User *lpPlayInfo , DWORD dwUpdateCode , int Param1 , int Param2 , int TargetMode );
int rsDebugMessageToClient(User *lpPlayInfo , char *szDmgMsg );
int rsGetExp_GameTime(User *lpPlayInfo );
DWORD ManufactureCheckRune(User *lpPlayInfo, DWORD RecipeCode, DWORD *pRuneCode );
int rsDispay_GameTime(User *lpPlayInfo , DWORD dwTimeOld );
int	rsUseSoccerBallPotionItem( DWORD dwItemCode , User *lpPlayInfo );
int SetAgingItem(Item *pItem, int AgingNum);
int rsSendGameServer_PrimeItem2(User *lpPlayInfo );
int rsSendGameServer_PrimeItem3(User *lpPlayInfo );
int EventMonsterTime();

// 랙箇댕庫돕와빵똥
int rsSendBigHeadToClient(User *lpPlayInfo,DWORD Time,int Kind);
// 랙箇뤄뽐돕와빵똥
int rsSendPhoenixToClient(User *lpPlayInfo,DWORD Time,int Kind);
// 랙箇벎茄
int rsSendFruitToGame(User *lpPlayInfo,smTRANS_COMMAND *lpTransCommand);
// 賈痰�餉潢㈚�
int rsSendLifeRegentoClient(User *lpPlayInfo,DWORD Time);
// 强痰침랬浪彊
int rsSendManaRegentoClient(User *lpPlayInfo,DWORD Time);
// 랙箇무멩
int SendQuickNoticeMessage(char *szMessage);
// 랙箇BOX무멩
int SendQuickMessageBox(User *lpPlayInfo,char *szMessage);
// 랙箇淚斂돕와빵똥
int rsSendChangeJobLevelToClient(User *lpPlayInfo);
// 랙箇묏삔무멩斤口
int SendClanNoticeMessage(User *lpPlayInfo,char *szMessage);

void rsSendDataServer(User *pcUser, void *szData);
void rsSendGameServer(User *pcUser, void *pcData);

int rsRefreshConfig();
int InitAll();
void RemoveAll();
void OnRecvMessage(User * pcUser, PacketReceiving * p);
int srGetMonsterItem(User *lpPlayInfo, Unit *lpChar, LootItem *lpsItem);
int rsShowHardCoreEventScore(User *lpPlayInfo);
int rsOpen_SodItem(Unit *lpChar, User *lprsPlayInfo);
int rsSendTransSkillAttack(Unit *lpChar, User *lpPlayInfo);
int	rsInitHardCoreEvent();
int	rsSoD_CatchItem(DWORD dwItemCode, User *lpPlayInfo);