#ifndef	_SMPACKET_HEADER

#define _SMPACKET_HEADER

#include	"sinbaram\\sinitem.h"
#include	<atltime.h>

#define	smTRANSCODE_OPENLIVE				0x38000000

#define	smTRANSCODE_SYSTEM					0x48400000

#define	smTRANSCODE_CONNECTED				0x48470080
#define smTRANSCODE_RECORDDATA				0x48470081
#define smTRANSCODE_GETRECORDDATA			0x48470082
#define smTRANSCODE_FAILRECORDDATA			0x48470083
#define smTRANSCODE_RECORDRESULT			0x48470084
#define smTRANSCODE_ID_SETUSERINFO			0x48470086
#define smTRANSCODE_ISRECORDDATA			0x48470089

#define smTRANSCODE_VERSION					0x4847008A
#define smTRANSCODE_CHECK_NETSTATE			0x4847008B
#define smTRANSCODE_ADMINMODE				0x4847008C
#define smTRANSCODE_SET_OBJSERIAL			0x4847008D
#define smTRANSCODE_CHECK_NETSTATE2			0x4847008E
#define smTRANSCODE_CHECK_NETSTATE3			0x4847008F
#define smTRANSCODE_CHECK_NETSTATE4			0x48470090
#define smTRANSCODE_CHECK_NETSTATE5			0x48470091
#define smTRANSCODE_IPLIST					0x48471000
#define smTRANSCODE_CHATMESSAGE				0x48471001
#define smTRANSCODE_POSITION				0x48471002
#define smTRANSCODE_PLAYLIST				0x48471003
#define smTRANSCODE_CONTINUEDATA			0x48471004
#define smTRANSCODE_WHISPERMESSAGE			0x48471005
#define smTRANSCODE_COUPLERING				0x48471006
#define smTRANSCODE_DISPLAYDAMGE			0x48471007
#define smTRANSCODE_PLAYDATA1				0x48470010
#define smTRANSCODE_PLAYDATA2				0x48470011
#define smTRANSCODE_PLAYDATA3				0x48470012
#define smTRANSCODE_TRANSPLAYDATA			0x48470013
#define smTRANSCODE_PLAYDATAGROUP			0x48470014
#define smTRANSCODE_PLAY_COMMAND			0x48470018
#define smTRANSCODE_PARTY_CHATMSG			0x48471015
#define smTRANSCODE_ADDEXP_PARTY			0x48470029
#define smTRANSCODE_ATTACKDATA				0x48470030
#define smTRANSCODE_ADDEXP					0x48470031
#define smTRANSCODE_PLAYERINFO2				0x48470032
#define smTRANSCODE_SET_BLACKLIST			0x48470033
#define smTRANSCODE_SET_ITEMCOPYLIST		0x48470034
#define smTRANSCODE_SKIL_ATTACKDATA			0x48470035
#define smTRANSCODE_FINDCRACK				0x48470036
#define smTRANSCODE_MODULE_WARNIG			0x48470037
#define smTRANSCODE_UPDATE_CINFO			0x48470038
#define smTRANSCODE_OPENMONSTER				0x48470039
#define smTRANSCODE_WARPFIELD				0x48470040
#define smTRANSCODE_TRADEITEMS				0x48470041
#define smTRANSCODE_TRADE_REQUST			0x48470042
#define smTRANSCODE_TRADE_ITEMKEY			0x48470043
#define smTRANSCODE_TRADE_READYITEM			0x48470044
#define smTRANSCODE_SKILL_MENU				0x48470045
#define smTRANSCODE_FINDCRACK2				0x48470046
#define smTRANSCODE_WAREHOUSE				0x48470047
#define smTRANSCODE_OPEN_WAREHOUSE			0x48470048
#define smTRANSCODE_OPEN_MIXITEM			0x48470049
#define smTRANSCODE_OPEN_COLLECT			0x4847004A
#define smTRANSCODE_COLLECTMONEY			0x4847004B
#define	smTRANSCODE_PLAYERINFO_Q			0x4847004C
#define smTRANSCODE_OPEN_AGING				0x4847004D
#define smTRANSCODE_SKIL_ATTACKUSER			0x4847004E
#define smTRANSCODE_OPEN_EVENTGIFT			0x4847004F
#define smTRANSCODE_PLAYERINFO				0x48470020
#define smTRANSCODE_GETPLAYERINFO			0x48470021
#define smTRANSCODE_FAILCONNECT				0x48470023
#define smTRANSCODE_OPEN_SOCKET				0x48470024
#define smTRANSCODE_PLAYITEM				0x48470050
#define smTRANSCODE_DELITEM					0x48470051
#define smTRANSCODE_PUTITEM					0x48470052
#define smTRANSCODE_THROWITEM				0x48470053
#define smTRANSCODE_SHOP_ITEMLIST			0x48470054
#define smTRANSCODE_SAVETHROWITEM			0x48470055
#define smTRANSCODE_SAVETHROWMONEY			0x48470056
#define smTRANSCODE_SAVETHROWITEM2			0x48470057
#define smTRANSCODE_SAVETHROWITEMS			0x48470058
#define smTRANSCODE_PLAYERKILLING			0x48470059
#define smTRANSCODE_GETITEM					0x4847005A
#define smTRANSCODE_USEITEM_CODE			0x4847005B
#define smTRANSCODE_COMMAND_USER			0x4847005C
#define smTRANSCODE_WING_NPC				0x4847005D
#define smTRANSCODE_PAYMENT_MONEY			0x4847005E
#define smTRANSCODE_MEDIA_NPC				0x4847005F
#define smTRANSCODE_ADD_STARTPOSI			0x48470060
#define smTRANSCODE_DEL_STARTPOSI			0x48470061
#define smTRANSCODE_ADMIN_COPYCHAR			0x48470062
#define smTRANSCODE_ADD_NPC					0x48470070
#define smTRANSCODE_DEL_NPC					0x48470071
#define smTRANSOCDE_SET_EXPUP				0x48470072
#define smTRANSOCDE_SET_PLAYINFO_EXP		0x48470073
#define smTRANSOCDE_SET_PLAYSIZE			0x48470074
#define	smTRANSCODE_PARTY_UPDATE			0x484700A0
#define	smTRANSCODE_PARTY_REQUEST			0x484700A1
#define	smTRANSCODE_PARTY_JOIN				0x484700A2
#define	smTRANSCODE_PARTY_PLAYUPDATE		0x484700A3
#define	smTRANSCODE_PARTY_RELEASE			0x484700A4
#define	smTRANSCODE_PARTY_COMMAND			0x484700A5
#define smTRANSCODE_OPEN_MIXTURE_RESET		0x484700A6
#define smTRANSCODE_OPEN_ELEMENT			0x484700A9
#define smTRANSCODE_OPEN_CARAVAN			0x484700AA
#define smTRANSCODE_CARAVAN					0x484700AB
#define smTRANSCODE_PCBANG_PET				0x484700B0
#define smTRANSCODE_PHENIX_PET				0x484700B1
#define smTRANSCODE_HELP_PET				0x484700B2
#define smTRANSCODE_FRUIT					0x484700B3
#define smTRANSCODE_CANCEL_BIGHEAD			0x484700B4
#define smTRANSCODE_FORCE_ROE				0x484700B5
#define smTRANSCODE_CANCEL_FORCE			0x484700B6
#define smTRANSCODE_WAREHOUSEMONEY			0x484700B7
#define smTRANSCODE_CHANGEJOBLEVEL			0x484700B8
#define smTRANSCODE_MAPLEVEL				0x484700B9
#define smTRANSCODE_CANCEL_CARAVAN			0x484700BA
#define	smTRANSCODE_SERVER_INFO				0x484700C0
#define	smTRANSCODE_PARTY_POTION			0x484700D0
#define	smTRANSCODE_HEALING					0x484700D2
#define	smTRANSCODE_HOLYMIND				0x484700D3
#define	smTRANSCODE_GRAND_HEALING			0x484700D4
#define	smTRANSCODE_VAMPRIC_CUSPID			0x484700D6
#define	smTRANSCODE_VAMPRIC_CUSPID_EX		0x484700D7
#define	smTRANSCODE_MANA_RECHARGING			0x484700D8
#define	smTRANSCODE_RECORD_TRADE			0x48480010
#define smTRANSCODE_NETWORK_QUALITY			0x484700E0
#define smTRANSCODE_PROCESSINFO				0x484700E4
#define	smTRANSCODE_CLOSECLIENT				0x484700E6
#define smTRANSCODE_CHECKIP					0x484700E7
#define	smTRANSCODE_SAVECLIENT				0x484700E8
#define smTRANSCODE_EFFECT_ITEM				0x48478000
#define smTRANSCODE_EFFECT_ELEMENT			0x48478001
#define smTRANSCODE_EFFECT_WEAPON			0x48478002
#define smTRANSCODE_EFFECT_STUN				0x48478004
#define smTRANSCODE_EFFECT_CURSE			0x48478006
#define smTRANSCODE_EFFECT_ICE				0x48478008
#define smTRANSCODE_EFFECT_POISION			0x4847800A
#define smTRANSCODE_EFFECT_FIRE				0x4847800B
#define smTRANSCODE_EFFECT_VANISH			0x4847800C
#define smTRANSCODE_EFFECT_PERSHOP			0x4847800E
#define smTRANSCODE_EFFECT_LOWPET			0x4847800F
#define smTRANSCODE_EFFECT_CLANMGR			0x48479000
#define smTRANSCODE_EFFECT_FORCEORB			0x48479010
#define smTRANSCODE_EFFECT_CURSE_QUEST		0x48479011
#define smTRANSCODE_EFFECT_BLESS_SCORE		0x48479012
#define smTRANSCODE_EFFECT_KEEPSKILL		0x48479020
#define smTRANSCODE_EFFECT_VIPER			0x48479030
#define smTRANSCODE_EFFECT_WING				0x48479040
#define smTRANSCODE_EFFECT_LEVEL			0x48479050
#define smTRANSCODE_CONT_OBJSERIAL			0x48478010
#define smTRANSCODE_MESSAGEBOX				0x48478100
#define	smTRANSCODE_FUNCERROR				0x48478200
#define smTRANSCODE_FUNCTION_MEM2			0x48478300
#define	smTRANSCODE_SET_BLACKLIST2			0x48478400
#define smTRANSCODE_SET_BLACKLIST3			0x48478500
#define	smTRANSCODE_BAD_PLAYER				0x48478600
#define	smTRANSCODE_FIX_ATTACK				0x48478700
#define	smTRANSCODE_DEAD_PLAYER				0x48478800
#define smTRANSCODE_CLIENT_ERROR			0x48478900
#define	smTRANSCODE_INVEN_ERR_ITEM			0x48478910
#define	smTRANSCODE_INVEN_ERR_MONEY			0x48478920
#define	smTRANSCODE_INVEN_POSITION			0x48478930
#define	smTRANSCODE_INVEN_POSITION2			0x48478931
#define smTRANSCODE_ENCODE_PACKET			0x80010000
#define smTRANSCODE_ENCODE_PACKET2			0x90010000
#define smTRANSCODE_OPEN_CLANMENU			0x48478A00
#define smTRANSCODE_OPEN_STARPOINT			0x48478A10
#define smTRANSCODE_STARPOINT				0x48478A12
#define smTRANSCODE_OPEN_GIVEMONEY			0x48478A14
#define smTRANSCODE_GIVEMONEY				0x48478A16
#define smTRANSCODE_CLANMONEY				0x48478A18
#define smTRANSCODE_ITEM_EXPRESS			0x48478A80
#define smTRANSCODE_OPEN_MYSHOP				0x48478A90
#define smTRANSCODE_CALL_MYSHOP				0x48478AA0
#define	smTRANSCODE_MYSHOP_ITEM				0x48478AB0
#define	smTRANSCODE_MYSHOP_MESSAGE			0x48478AC0
#define	smTRANSCODE_MYSHOP_TRADE			0x48478AD0
#define smTRANSCODE_EFFECT_PCBANGPET		0x48478AE0
#define smTRANSCODE_ADMINMODE2				0x5047108C
#define smTRANSCODE_CHECK_NETSTATE20		0x5047008E
#define smTRANSCODE_CHECK_EXPMONEY			0x50320010
#define smTRANSCODE_FORCEORB_DATA			0x50320030
#define smTRANSCODE_PRIMEITEM_DATA			0x50320031
#define smTRANSCODE_PRIMEITEM_DATA2			0x50320032
#define smTRANSCODE_PRIMEITEM_DATA3			0x50320033
#define smTRANSCODE_PRIMEITEM_DATA4			0x50320036
#define smTRANSCODE_BOOSTER_DATA			0x50320034
#define smTRANSCODE_AGING_DATA				0x50320035
#define smTRANSCODE_SKILLDELAY_DATA			0x50320036
#define smTRANSCODE_SEND_DATASERVER			0x50320100
#define smTRANSCODE_SEND_GAMESERVER			0x50320110
#define smTRANSCODE_SEND_AREASERVER			0x50320120
#define smTRANSCODE_SEND_AGAME_SERVER		0x50320130

#define smTRANSCODE_SEND_AGAME_PRIMEITEM_DATA2	0x50320140
#define smTRANSCODE_SEND_AGAME_PRIMEITEM_DATA3	0x50320150
#define smTRANSCODE_SEND_AGAME_PRIMEITEM_DATA4	0x50320160


#define smTRANSCODE_CRAFTITEM				0x50320200
// 똴芚膠틔葵累
#define smTRANSCODE_AGINGITEM				0x50320202
#define	smTRANSCODE_AGING_UPGRADE			0x50320204
#define	smTRANSCODE_MAKE_LINKCORE			0x50320205
#define	smTRANSCODE_USE_LINKCORE			0x50320206
#define smTRANSCODE_WINGITEM				0x50320208
#define smTRANSCODE_SHOPTITEM				0x50320210
#define smTRANSCODE_SHOP_SELLITEM			0x50320212
#define	smTRANSCODE_ITEM_FORCEORB			0x50320214
#define smTRANSCODE_ELEMENTITEM				0x50320216
#define smTRANSCODE_SOCKETITEM				0x50320217	
#define	smTRANSCODE_QUEST_COMMAND			0x50320220
#define smTRANSCODE_CHECKITEM				0x50320300
#define smTRANSCODE_ERRORITEM				0x50320310
#define smTRANSCODE_CLEARPOTION				0x50320320

#ifdef _CHECK_MESH
#define smTRANSCODE_CHECK_ITEMMESH			0x50320330
#endif

#define smTRANSCODE_CLIENT_FUNCPOS			0x50320400
#define smTRANSCODE_GETCLIENT_FUNCPOS		0x50320410
#define smTRANSCODE_FUNCTION_MEM			0x50320420
#define smTRANSCODE_FUNCTON_RESULT			0x50320430
#define smTRANSCODE_PROCESS_TIMEMAX			0x50320500
#define smTRANSCODE_NSPRITE					0x50320600
#define smTRANSCODE_NPROTECT				0x50320700
#define smTRANSCODE_GAMEGUARD_AUTH			0x50320710
#define	smTRANSCODE_REC_DAMAGEDATA			0x50320800

#define	smTRANSCODE_SOD_RESULT				0x50320900
#define	smTRANSCODE_SOD_RESULT2				0x50320901

#define	smTRANSCODE_PARTY_SKILL				0x50320A00

#define	smTRANSCODE_CANCEL_SKILL			0x50320A10
#define	smTRANSCODE_PROCESS_SKILL			0x50320A20
#define smTRANSCODE_PROCESS_SKILL2			0x50320A30
#define smTRANSCODE_PROCESS_CLAN_SKILL		0x50320A35
#define	smTRANSCODE_UPDATEL_SKILL			0x50320A40
#define	smTRANSCODE_SUCCESS_EVATION			0x50320A50
#define	smTRANSCODE_RESISTANCE				0x50320A60
#define	smTRANSCODE_PUBLIC_POLLING			0x50320A70
#define	smTRANSCODE_NOTICE_BOX				0x50320A80
#define	smTRANSCODE_HACKTRAP				0x50320A90

#define	smTRANSCODE_VIRTURAL_POTION			0x50320B00
#define	smTRANSCODE_CLAN_SERVICE			0x50320C00
#define	smTRANSCODE_CLAN_UPDATE				0x50320C10
#define	smTRANSCODE_QUEST_MESSAGE			0x50320D00
#define	smTRANSCODE_DEAD_USER				0x50320E00
#define	smTRANSCODE_DEAD_EXP				0x50320E02
#define	smTRANSCODE_YAHOO_MOTION			0x50320E10
#define	smTRANSCODE_CHANGE_EVENT			0x50320F00
#define	smTRANSCODE_CLIENTINFO				0x50321000
#define	smTRANSCODE_WARNING_BLINK_ATT		0x50321010
#define smTRANSCODE_ATTACK_DAMAGE			0x50322000
#define smTRANSCODE_RANGE_DAMAGE			0x50322010
#define smTRANSCODE_ATTACK_RESULT			0x50322020
#define smTRANSCODE_DISP_DAMAGE				0x50322030
#define smTRANSCODE_ATTACKDATA2				0x50322040
#define smTRANSCODE_LIMIT_DAMAGE			0x50322050
#define smTRANSCODE_WARNING_CLIENT			0x50322060
#define smTRANSCODE_WARNING_SKILL			0x50322080
#define smTRANSCODE_COMIC_SKIN				0x50322070
#define	smTRANSCODE_REC_ADMIN_COMMAND		0x50322090
#define smTRANSCODE_CHECK_ADMINMODE			0x503220A0
#define smTRANSCODE_SOD_INFOMATION			0x503220B0
#define smTRANSCODE_BLESSCASTLE_INFO		0x503220C0
#define smTRANSCODE_BLESSCASTLE_TAX			0x503220D0
#define smTRANSCODE_ATTACK_SLASH_LIST		0x503220E0
#define smTRANSCODE_UPDATE_SERVER_PARAM		0x503220F0
#define smUPDATE_PARAM_LOWUSER_PRESENT		0x100
#define smTRANSCODE_USER_ID					0x50322100
#define smTRANSCODE_DAMAGE_ENCODE_MEM		0x50322F00
#define smTRANSCODE_DAMAGE_ENCODE_MEM2		0x50322EC0
#define	smTRANSCODE_PACKET_DYNFUNC			0x50323000
#define	smTRANSCODE_AREA_SERVER_MAP			0x50324000
#define smTRANSCODE_OPEN_SMELTING			0x50325000
#define smTRANSCODE_SMELTINGITEM			0x50325001
#define smTRANSCODE_OPEN_MANUFACTURE		0x50326000
#define smTRANSCODE_MANUFACTURE				0x50326001
#define smTRANSCODE_MANUFACTURE_WEIGHT_PRICE 0x50326002
#define smTRANSCODE_GIFTBOX_MONEY			0x50326003
#define smTRANSCODE_PREMIUMITEM_INIT		0x50326004
#define smTRANSCODE_MIXTURE_RESET_ITEM		0x50326006
#define smTRANSCODE_PLAYER_DATA_VIP			0x50326009
#define smTRANSCODE_PLAYER_GAME_VIP			0x50326010

// 밍膠彊쑨葵累 혤句彊쑨葵累
#define smTRANSCODE_CRYSTAL_ORB				0x50326011
// 뗌실艱寧소鑒앴葵累
#define smTRANSCODE_CARAVAN_HOPY			0x50326012
#define smTRANSCODE_CARAVAN_SELECT			0x50326013
#define	rsHARDCORE_EVENT_FLAG				0x100
#define smCODE_SOD_EFFECT					100
#define smTRANSCODE_EVENT_GAME				0x50326007
#define smCODE_EVENT_STATE_INIT				100

#define smTRANSCODE_ITEMDOC					0x50326008


#define TRANS_BUFF_SIZE						4096

#define	smCHAR_STATE_NPC					0
#define	smCHAR_STATE_ENEMY					1
#define	smCHAR_STATE_USER					0x80

#define	smCHAR_MONSTER_NATURAL				0x80
#define	smCHAR_MONSTER_GOOD					0x81
#define	smCHAR_MONSTER_EVIL					0x82

#define	smCOMMNAD_USER_WARP					0x100
#define	smCOMMNAD_USER_AGINGUP				0x110
#define	smCOMMNAD_USER_HOLY_INCANTATION		0x120
#define	smCOMMNAD_USER_RESURRECTION			0x130
#define	smCOMMNAD_USER_FORCEORB				0x140
#define	smCOMMNAD_USER_VALENTO				0x150
#define	smCOMMNAD_USER_FIREFLOWER			0x160

#define	smCOMMAND_PLAY_BABEL				0x200
#define	smCOMMAND_PLAY_BELSS_CASTLE			0x210
#define	smCOMMAND_PLAY_PK_FIELD				0x220
#define	smCOMMAND_PLAY_KELVEZU				0x230
#define smCOMMAND_PLAY_WEATHER				0x300 //苟黛葵累

class	Unit;

class	rsRECORD_DBASE;

#define	FALLITEM_MAX						200
#define	FALLITEM2_MAX						3

struct _FALLITEM{
	DWORD	dwItemCode;
	int		Percentage;
	short	sPrice[2];
};

#define	NPC_MESSAGE_MAX		20

//캐릭터 정보 단축 크기
#define	smCHAR_INFO_QUICK_SIZE		192
#define	smCHAR_INFO_QUICK_SIZE2		352

#define	THROW_ITEM_INFO_MAX		64
#define	THROW_ITEM_INFO_MASK	63
#define	INVEN_ITEM_INFO_MAX		300


//캐릭터 좌표 구조
struct rsPLAYPOS {
	DWORD	Area;		// Low->Wolrd High->Area	: 현재 존재하고 있는 지역의 위치 코드
	int		x,y,z;		// 좌표
};

//내용 : 자신의 위치및 정보를 서버에 전송
//대상 : 클라이언트 -> 서버
//코드 : smTRANSCODE_POSITION
//10초 간격으로 서버에 보내지는 플레이어 위치 정보
struct TRANS_PLAYPOS {
	int size,code;
	
	rsPLAYPOS	rsPlayPos;
	short Hp[2];
};



//내용 : 상대한테 공격 정보를 보낸다
//대상 : 클라이언트 -> 서버  클라이언트 -> 클라이언트
//코드 : smTRANSCODE_ATTACKDATA
struct TRANS_ATTACKDATA
{
	int size,code;

	DWORD	dwDestObjectSerial;	//공격하는 캐릭터 고유번호
	DWORD	dwTarObjectSerial;	//공격대상 캐릭터 고유번호

	int		x,y,z;			// 좌표
	int		AttackState;	// 속성
	int		AttackSize;		// 공격 범위
	int		Power;
	int		PowerType;
	DWORD	dwChkSum;

	short	sRating[2];	//[0]-레벨 [1]-명중력
	DWORD	dwDamageChkSum;
};

struct TRANS_ATTACKDATA2 {
	int size,code;

	DWORD	dwChkSum;

	DWORD	dwDestObjectSerial;	//공격하는 캐릭터 고유번호
	DWORD	dwTarObjectSerial;	//공격대상 캐릭터 고유번호

	int		x,y,z;			// 좌표
	int		AttackState;	// 속성
	int		AttackSize;		// 공격 범위
	short	Power[2];		// 공격 파워
	short	Power2[2];		// 공격 파워 ( 추가 공격 )
	short	Critical[2];	// 크리티컬
	int		SkillCode;		// 스킬코드
	DWORD	dwTime;			// 클라이언트 시간
	int		AttackCount;	// 공격 카운터
	short	MotionCount[2];	// 공격 모션 카운터
	DWORD	dwWeaponCode;	// 주 공격 무기
	short	Area[2];		// 지역
	int		Temp[4];		// 예비
};


// 장별 - 범위형 스킬( 32 -> 42 )
#define SKIL_ATTACK_CHAR_MAX		42

struct TRANS_SKIL_ATTACKDATA
{
	int size,code;

	DWORD	dwDestObjectSerial;

	int x,y,z;
	int AttackState;
	int AttackSize;
	int Power;

	DWORD	dwChkSum;

	int	TargetCount;
	DWORD	dwTarObjectSerial[SKIL_ATTACK_CHAR_MAX];
};

struct TRANS_SKIL_ATTACKDATA2
{
	int size,code;

	DWORD	dwDestObjectSerial;	//공격하는 캐릭터 고유번호

	DWORD	dwChkSum;

	int		x,y,z;			// 좌표
	int		AttackState;	// 속성
	int		AttackSize;		// 공격 범위
	short	Power[2];		// 공격 파워
	short	Power2[2];		// 공격 파워 ( 추가 공격 )
	short	Critical[2];	// 크리티컬
	int		SkillCode;		// 스킬코드
	DWORD	dwTime;			// 클라이언트 시간
	int		AttackCount;	// 공격 카운터
	short	MotionCount[2];	// 공격 모션 카운터
	DWORD	dwWeaponCode;	// 주 공격 무기
	short	Area[2];		// 지역
	int		Temp[4];		// 예비

	DWORD	dwMainTargetObject;		//주 타겟

	int	TargetCount;
	DWORD	dwTarObjectSerial[SKIL_ATTACK_CHAR_MAX];	//공격대상 캐릭터 고유번호
};



//내용 : 지역에 존재하는 다른 플레이어 정보 목록 전송
//대상 : 서버 -> 클라이언트
//코드 : smTRANSCODE_IPLIST
struct TRANS_AREAINFO_HEADER {
	int		size;
	int		code;
	DWORD	dwIP;
	int		Stats;					//전송 완료면 TRUE 아직 더 보낼 데이타가 있으면 FALSE
	int		TransListCnt;			//전송하는 TRANS_IPLIST 갯수
};
struct TRANS_IPLIST {
	DWORD	dwIP;
	rsPLAYPOS	Pos;
};

/////////////// 아이템 택배 서비스 /////////////////
#define	POST_ITEM_MAX				500

struct _POST_BOX_ITEM {
	int		Flag;
	char	szCharName[32];
	char	szItemCode[32];
	char	szSpeJob[32];
	char	szDoc[128];
	char	szFormCode[64];
	char	szPassCode[16];

	DWORD	dwItemCode;
	DWORD	dwJobCode;
	DWORD	dwFormCode;
	DWORD	dwPassCode;
	DWORD	dwParam[4];
};

struct	rsPOST_BOX_ITEM {
	DWORD	dwHead;
	int		ItemCounter;

	_POST_BOX_ITEM	PostItem[POST_ITEM_MAX];
};

struct	TRANS_POST_ITEM {
	int		size,code;

	char	szItemName[32];
	char	szDoc[128];
	DWORD	dwItemCode;
	DWORD	dwItemJobCode;
	DWORD	dwParam[4];

	DWORD	dwItemFlag;
	int		Weight;			// pluto 해외 빌링 아이템 무게
};
//	sITEM_INFO	sItemInfo;


///////////////////////////////////////////////////////


#define	srPLAYBUFF_MAX		4
#define	srPLAYBUFF_MASK		3

#define	PARTY_PLAYER_MAX		6

// 장별 - 예비버퍼
#define	srRECORD_DEFAULT_SIZE	16384
//#define	srRECORD_DEFAULT_SIZE	32768
#define	srRECORD_MEMORY_SIZE	24576
//#define	srRECORD_MEMORY_SIZE	49152

#define SKILL_POINT_COLUM_MAX	20

struct	TRANS_PARTY_PLAYINFO;

struct	npGAME_GUARD_AUTH_INFO {
	 DWORD	Auth_Value;		//게임가드 확인코드 ( 값을 리턴 받음 )
	 DWORD	Auth_Time;		//게임가드 확인시간 ( 다음처리 시간 )
	 DWORD	Auth_Count;		//게임가드 확인카운터 ( 총 보낸 횟수 )
	 DWORD	Auth_Retry;		//게임가드 확인 재시도 ( 응답이 60초 안에 안오면 몇번까지 재시도 )
};

//아이템 구매 카운터
struct	sMYSHOP_SELL_INFO {
	DWORD	dwCode;
	DWORD	dwHead;
	DWORD	dwChkSum;
	int		Price;
};

#define	MYSHOP_LIST_MAX		32
#define	MYSHOP_LIST_MASK	31


struct	sCASTLE_MASTER {
	int		Flag;
	DWORD	dwCheckTime;
	int		SelectSkill;
};

#define	rsDATA_ERROR_WAREHOUSE	1
#define rsDATA_ERROR_CARAVAN	2


struct smTRANS_COMMAND
{
	int	size;
	int code;

	int LParam;
	int WParam;
	int SParam;
	int EParam;
};

//박재원 - XignCode
#define PACKET_SIZE 512


//박재원 - XignCode
typedef struct _XIGNCODE_PACKET {
	int size;
	int code;
	BYTE data[PACKET_SIZE]; //박재원 - XignCode
} XIGNCODE_PACKET;

typedef struct _XIGNCODE_TempData{
	BOOL m_type;
	BOOL m_ceComplete;
	DWORD	dwWaitTime_NC;
	DWORD	dwWaitTime_CE;
	BOOL   dwClientReady;
	HANDLE xigncode_handle;
	int m_pcount;
} XIGNCODE_TempData;

//박재원 - XignCode
#define smTRANSCODE_XIGNCODE_PACKET		0x48470400
#define smTRANSCODE_XIGNCODE_START		0x48470500


typedef struct _WSABUF {
	u_long      len;     
	char FAR *  buf;     
} WSABUF, FAR * LPWSABUF;

#define BILLING_GPTYPE_DAY		0
#define BILLING_GPTYPE_TIME		1
#define BILLING_GPTYPE_FREE		2
#define BILLING_GPTYPE_POTAL	3

#define BILLING_PGTYPE_PERSONAL	0
#define BILLING_PGTYPE_PCROOM	0




/////////////////////////////////////////////////////////////////////////////////////////

//내용 : 채팅 문자열 전송 코드
//대상 : 클라이언트 <-> 서버
//코드 : smTRANSCODE_CHATMESSAGE
struct TRANS_CHATBUFF {
	int		size;
	int		code;
	DWORD	dwIP;
};
struct CHATBUFF {
	DWORD	dwIP;
	char szMessage[256];
};

struct TRANS_CHATMESSAGE {
	int		size;
	int		code;
	DWORD	dwIP;
	DWORD	dwObjectSerial;	//객체의 고유값

	char szMessage[256];
};


struct smPLAYDATA_GROUP {
	int		size,code;
	int		PlayDataCnt;
	DWORD	dwSendCode;
};


#define smPLAYBUFF_FRAME_NONE			0xFFFF0000

#define	smPLAYBUFF_ITEM_BODY			0
#define	smPLAYBUFF_ITEM_LEFT			1
#define	smPLAYBUFF_ITEM_RIGHT			2
#define	smPLAYBUFF_ITEM_SKIL			3
#define TRANS_PLAYDATA_EVENT_LEVEL		0
#define TRANS_PLAYDATA_EVENT_POTION		1
#define TRANS_PLAYDATA_EVENT_SKIL		2
#define TRANS_PLAYDATA_EVENT_EXT		3

struct smTRANS_CHAR_COMMAND
{
	int	size;
	int code;

	int LParam;
	int WParam;
	int SParam;

	char	szName[32];
};

struct smTRANS_CHAR_COMMAND2
{
	int	size;
	int code;

	int LParam;
	int WParam;
	int SParam;

	char	szId[32];
	char	szName[32];
};

struct smTRANS_MAP_LEVEL
{
	int size;
	int code;

	int MapLevel[MAX_FIELD];
};

struct smTRNAS_PLAYERINFO
{
	int	size;
	int code;

	CharacterData	sCharacterData;

	DWORD	dwObjectSerial;

	int	x,y,z;
	int ax,ay,az;
	int state;
};

struct smTRNAS_PLAYERINFO_QUICK
{
	int	size;
	int code;

	DWORD	dwObjectSerial;

	int	x,y,z;				//최초 좌표
	int ax,ay,az;			//최초 각도
	int state;				//속성

	CharacterData	sCharacterData;
};


//간단한 코멘드 전송용 구조
struct smTRANS_COMMAND_DWORD
{
	int	size;
	int code;

	DWORD LParam;
	DWORD WParam;
	DWORD SParam;
	DWORD EParam;
};

struct smTRANS_COMMAND_EX
{
	int	size;
	int code;

	int LParam;
	int WParam;
	int SParam;
	int EParam;

	int LxParam;
	int WxParam;
	int SxParam;
	int ExParam;

};


struct smTRANS_COMMAND_BUFF {
	smTRANS_COMMAND		smTransCommand;
	char	*Buff[256];
};

struct smTRANS_COMMAND_SOD {
	smTRANS_COMMAND		smTransCommand;
	int		MyScore;
	int		MyTeam;
	int		TeamScore[4];
	int		Temp[4];
};

struct smTRANS_COMMAND_POLLING {
	smTRANS_COMMAND		smTransCommand;
	BYTE	bPolling[10];
};



//속성 호출
struct smTRANS_RESISTANCE {
	int	size;
	int code;
	int	Param;
	short Resistance[8];
	int	Absorb;
};


//공성
struct smTRANS_BLESSCASTLE {
	smTRANS_COMMAND		smTransCommand;
	int				TaxRate;
	short			Tower[12];		//타워설정	
	unsigned char	MercenaryNum[4];	//int		MercenaryType;	//용병설정
	int				ClanSkill;		//클랜스킬
	int				Price;
	DWORD			dwMasterClan;	//성주클랜
	int				Temp[4];
};

//공격순위 톱10
struct	rsUSER_LIST_TOP10 {
	//SYSTEM HEADER
	int		size,code;

	int		tCode;
	DWORD	dwObjectSerial;
	DWORD	dwNameCode;
	int		x,y,z;

	//BODY

	DWORD	dwCharCode;
	DWORD	dwUpdateTime;
	DWORD	dwTotalDamage;
	char	bCrystalTowerCount[4];
	DWORD	dwTemp[2];

	DWORD	dwUserCode[10];
	int		Damage[10];
	int		Counter[10];
};

/////////////// 아이템을 그룹으로 묶어서 전송 /////////////////////

/*
/////서버로 보내질 아이템 구조체 
struct sCRAFTITEM_SERVER{
	int size, code;
	int DocIndex;
	int Result;
	sITEM DesCraftItem;
	DWORD SheltomCode[12];
	DWORD Head[12];
	DWORD CheckSum[12];
	int Index;
	int Money;
};
*/


//아이템 그룹으로 전송
#define	TRANS_GROUPITEM_MAX		16
#define	TRANS_GROUPITEM_HEADER_SIZE		(14*4)

//압축을 푼경우
struct	TRANS_ITEMINFO_GROUP {
	int	size,code;

	int Index;
	int Result;
	int Money;
	int	ItemCount;

	DWORD	dwTemp[8];

	Item	sItemInfo[TRANS_GROUPITEM_MAX];
};

//압축포맷
struct	TRANS_ITEMINFO_GROUP2 {
	int	size,code;

	int Index;
	int Result;
	int Money;
	int	ItemCount;

	DWORD	dwTemp[8];

	char	szBuff[ sizeof(Item) * TRANS_GROUPITEM_MAX ];
};


//단일 아이템 전송
struct TRANS_ITEMINFO {
	//------------------------------------------------------------------< _ignore_bug_fix_0x00000000_ //해외
	/*
	TRANS_ITEMINFO()  // 생성자
	{
		size = 0,code = 0;x=0,y=0,z=0,
		ZeroMemory(&Item,sizeof(Item));
		for(int i=0;i<4;i++)
		{
			dwSeCode[i] = 0;
		}
		
	};
	*/
	//------------------------------------------------------------------  _ignore_bug_fix_0x00000000_ >
	int	size,code;

	//char	szItemName[32];
	//DWORD	ItemCode;

	Item	sItem;

	int x,y,z;

	DWORD	dwSeCode[4];		//보안 코드
};


struct	TRANS_ITEM_CODE {
	int size,code;

	DWORD	dwFlag;

	DWORD	dwItemCode;
	DWORD	dwHead;
	DWORD	dwChkSum;
	DWORD	dwTime;
};


struct TRANS_ITEM {
	int			state;

	int			type;
	int			ItemCode;

	int			x,y,z;
	char		szName[64];
	void		*lpStgArea;
	//char szModelName[64];
};


struct _TRANS_THROW_ITEM {
	DWORD	dwCode;
	DWORD	dwHead;
	DWORD	dwChkSum;
};

#define	THROW_ITEMS_MAX				32
//구조체 헤더 사이즈
#define	TRANS_THROW_ITEMS_DEFSIZE	(sizeof(int)*4)

struct TRANS_THROW_ITEMS {
	int		size,code;
	int		ThrowItemCount;
	int		Temp;

	_TRANS_THROW_ITEM	ThrowItems[THROW_ITEMS_MAX];
};



//거래후 아이템 보고
struct _TRANS_RECORD_TRADE_ITEM {
	DWORD	dwCode;
	DWORD	dwHead;
	DWORD	dwChkSum;
	int		State;
};

//sinTrade.h 에서 재정의
#define _MAX_TRADE_ITEM			20

struct TRANS_TRADE_ITEMKEY	{
	int size,code;
	DWORD	dwSender;
	DWORD	dwRecver;
	DWORD	dwSum;

	DWORD	dwItemCode[_MAX_TRADE_ITEM];
	DWORD	dwItemKey[_MAX_TRADE_ITEM];
	DWORD	dwItemSum[_MAX_TRADE_ITEM];

	int		Money;
};


#define	TRADE_RECV_ITEMS_MAX				32

//구조체 헤더 사이즈
#define	TRANS_RECORD_TRADE_DEFSIZE		(sizeof(int)*16)

struct TRANS_RECORD_TRADE_ITEMS {
	int		size,code;
	int		Money;
	int		ThrowItemCount;
	char	szTradeUserName[32];			//상대방 캐릭명
	int		Temp[4];

	_TRANS_RECORD_TRADE_ITEM	Items[TRADE_RECV_ITEMS_MAX];
};


#define TRANS_ITEM_MAX			16

//아이템 정보
struct smTRANS_ITEMS
{
	int size,code;

	int state;
	int Count;

	TRANS_ITEM	Items[ TRANS_ITEM_MAX ];
};

//아이템 정보
struct smTRANS_ACITON_ITEM
{
	int size,code;

	int state;

	int			x,y,z;
	void		*lpStgArea;
};
//상점 아이템 정보
struct smTRANS_SELL_ITEM {
	int size,code;
	int	ItemKind;					//공격 / 방어 /기타 등등의 구분
	int	ItemCounter;				//판매 아이템의 수
	int	Ext[4];						//예비
};

//아이템 교환 창
#define TRANS_TRADE_BUFF_SIZE		4000
struct TRANS_TRADEITEMS {
	int size,code;
	DWORD	dwSender;
	DWORD	dwRecver;
	DWORD	dwSum;
	DWORD	Temp[4];

	BYTE	TradeBuff[TRANS_TRADE_BUFF_SIZE];
};

#define	SOD_RESULT_MAX	32

struct	_SOD_RESULT {
	char		szName[32];
	void	*lpPlayInfo;
	int			JobCode;
	int			Class;
	int			Score;
	int			Monster;
	DWORD		dwTemp[4];
};

//SoD 순위 정보
struct	TRANS_SOD_RESULT {
	int	size,code;

	DWORD	dwGameCode;
	DWORD	dwGameTime;
	DWORD	dwDisplayMode;
	short	TeamRound[2];

	DWORD	dwTemp[15];

	int		ResultCount;

	_SOD_RESULT	Result[SOD_RESULT_MAX];
};



//////// 서버와 클라이언트의 돈,경험치 수치 조회 //////////
struct	sSERVER_MONEY {
	int	InputMoney;
	int	Counter;
	int	TotalX;
	int	TotalY;
	int	TotalZ;
};

struct sSERVER_EXP {
	int	Counter;
	int	InputExp;
	int	Total1;
	int	Total2;
};

struct TRANS_TOTAL_EXPMONEY {
	int	size,code;

	sSERVER_MONEY	sServerMoney;
	sSERVER_EXP		sServerExp;
};

//데이타 서버로 클라이언트 경유 전송
struct	TRANS_SEND_DATASERVER {
	int size,code;
	char	szBuff[1024];
};


//아이템 구입용 구조체
struct	TRANS_BUY_SHOPITEM {
	int	size,code;

	ItemData	sItem;			//구입하는 아이템
	int		ItemCount;		//구입하는 아이템 갯수
};



//거래시 아이템 보낸후 보낸 아이템이 인벤에 존재 하는지 확인
struct	_TRANS_USINGITEM {
	DWORD	dwCode;
	short	Performance[8];
};

struct	TRANS_USINGITEM {
	int	size,code;
	int	ItemListCount;
	_TRANS_USINGITEM	ItemList[16];
};


#define	PARTY_STATE_NONE		0
#define	PARTY_STATE_MASTER		1
#define	PARTY_STATE_MEMBER		2


struct _PARTY_USER 
{
	char	szName[32];				//이름
	char	szModelName[64];		//모델 이름
	char	szModelName2[64];		//모델 이름2

	DWORD	dwObjectSerial;			//객체 고유번호
	DWORD	Level;
	short	Life[2];
	DWORD	Class;
	int		x,z;
};

struct TRANS_PARTY_USERS {
	int		size,code;

	DWORD	dwObjectSerial;
	DWORD	dwTemp[8];

	int		PartyUserCount;

	_PARTY_USER		PartyUser[PARTY_PLAYER_MAX];
};

struct _PARTY_PLAYINFO
{
	DWORD	dwObjectSerial;			//객체 고유번호
	DWORD	Level;					//된섬
	short	Life[2];				//�餉�
	DWORD	Class;
	int		x,z;
};

struct	TRANS_PARTY_PLAYINFO 
{
	int		size,code;

	DWORD	dwObjectSerial;
	DWORD	dwTemp;

	int		PartyUserCount;

	_PARTY_PLAYINFO	PlayInfo[PARTY_PLAYER_MAX];
};

struct	TRANS_PARTY_SKILL {
	int		size,code;
	DWORD	dwSkillCode;
	int		Point;
	int		wParam;
	int		lParam;
	int		sParam;
	int		eParam;
	int		PartyCount;
	DWORD	dwPartyUser[8];
};

struct TRANS_CLAN_COMMAND_USER {
	int size,code;
	int	Param[4];
	int	UserCount;

	char	szUserBuff[2048];
};

#define	CLAN_USER_MAX	64

struct _CLAN_USER_INFO {
	char		szName[32];
	DWORD		dwSpeedSum;
	DWORD		dwObjectSerial;
	void	*lpPlayInfo;
};

struct	rsCLAN_INFOMATION {
	DWORD	dwClanCode;
	DWORD	dwTemp[32];

	_CLAN_USER_INFO	ClanUserInfo[CLAN_USER_MAX];
};
struct	TRANS_WAREHOUSE 
{
	int size,code;

	DWORD	dwChkSum;
	WORD	wVersion[2];
	int		WareHouseMoney;
	DWORD	dwTemp[5];

	int		DataSize;
	BYTE	Data[sizeof(ItemData)*100+256];
};
struct TRANS_CARAVAN
{
	int		size,code;
	DWORD	dwChkSum;
	WORD	wVersion[2];

	int		DataSize;
	BYTE	Data[sizeof(ItemData) * 100 + 256];
};

#define	TRANS_SERVER_MAX		8

//서버 정보
struct _TRANS_SERVER_INFO {
	char	szServerName[32];
	char	szServerIp1[20];
	char	szServerIp2[20];
	char	szServerIp3[20];

	DWORD	dwServerPort1;
	DWORD	dwServerPort2;
	DWORD	dwServerPort3;

	DWORD	ConnState;
};

struct TRANS_SERVER_LIST
{
	int size,code;

	char szServerName[16];

	DWORD dwServerTime_t;
	int		ClanTicket;
	int	dwTemp[1];
	int	ClanServerCount;
	int	ServerCount;
	_TRANS_SERVER_INFO ServerInfo[TRANS_SERVER_MAX];
};

#define	SERVER_MAP_MAX		64

struct	TRANS_SEVER_MAP {
	int size,code;

	DWORD	dwTemp[30];

	int		IP_Count;
	DWORD	dwIP[SERVER_MAP_MAX];
};

struct	TT_DATA_SERVER_INFO {
	char	szServerID[16];
	char	szServerPath[128];
};

struct sEVENT_CASTLE_EXPUP
{
	int MinLevel;
	int MaxLevel;
	int TimeDelay;
};

#define	SYSTEM_IP_MAX			32
#define	LOGIN_IP_MAX			16
#define	DISABLE_IP_MAX			500
#define	ENABLE_IP_MAX			100
#define	ADMIN_IP_MAX			16
#define CLAN_SERVER_MAX			3
#define ENABLE_MODULE_CHECK_MAX	64	
#define	TT_DATA_SERVER_MAX		16

//서버 설정 구조
struct rsSERVER_CONFIG	{

	DWORD	ServerCode;
	DWORD	AutoPlayer;
	DWORD	DisableParty;		//동료금지
	DWORD	EnablePlayerKill;	//PK허가
	DWORD	ConnectUserMax;		//최대 접속 허가 인원

	int		TestSeverMode;		//테스트 서버용

	int		UseRecorMemory;		//저장데이타 메모리 버퍼사용
	int		PotionMonitor;		//물약 감시

	int		ClientCheckSumCount;	//클라이언트 체크섬 카운터
	int		ClientCheckOut;			//문제 클라이언트 접속 종료
	DWORD	dwClientCheckSum[32];	//접속 가능한 체크섬 목록

	int		SafeClientCodeCount;	//클라이언트의 펑션첵크 코드카운트
	int		ClientCodeCheckOut;		//펑션문제 클라이언트 접속 종료
	DWORD	dwSafeClientCode[32];	//클라이언트의 펑션첵크 코드

	int		LimitVersion;			//접속 가능한 최하 버전
	int		LimitVersionMax;		//접속 가능한 최상 버전
	char	szAdminPassword[3][32];	//관리자 권한 부여 패스워드
	char	szAdminName[32];		//관리자 이름

	char	szAdminIP[16];			//관리자 IP
	char	szAdminLogPassword[32];	//관리자 Password

	char	szServerName[64];		//서버 이름
	int		Enable_PK;				//PK허가
	int		CheckProtect;			//nProtect 수시로 검사유무
	DWORD	RemoveNProtectTime;		//게임중에 nProtect제거 시간

	char	szDebugIP[10][32];		//디비깅용 IP
	int		DebugIP_Count;			//디버깅 IP 카운터

	char	szDebugID[32][32];		//디버깅용 ID
	int		DebugID_Count;			//디버깅용 ID 카운터

	int		BlockLevel;				//ID 임시 블럭의 레벨
	int		BlockLevel_LogOut;		//로그 아웃시에만 적용( 중국측 요구 )
	int		ItemCodeOut;			//아이템 코드 오류시 종료

	int		ClientFuncCheckMode;	//클라이언트 펑션 검사 모드
	int		Enable_PartyItem;		//동료가 획득한 아이템 출력
	int		CharLevel;				//�阮첵핀サ횝�
	
	int		Event_Mandoo;			//만두(송편) 이벤트
	int		Event_HardCore;			//하드코어 이벤트
	int		Event_DamageOff;		//공격력 활인 이벤트

	int		Event_DefenseOff;		//몬스터 방어력 약화 이벤트
/////////////////////////////////////////////////////////////////////////////////////////
	int		Event_Child;			//어린이 이벤트
	int		Event_Cristal;			//크리스탈 이벤트 ( 특정 시간대에 크리스탈 몬스터 강화 )
	int		Event_Potion;			//물약 이벤트 ( 물약 동시에 떨어지는 갯수 증가 )
	int		Event_StarPointTicket;	//별포인트 이벤트 ( 별상품권 발생 )
	int		Event_ValentineDay;		//발렌타인 데이 이벤트
	int		Event_WhiteDay;			//화이트 데이 이벤트
	int		Event_MorifSheltom;		//모리프의 쉘텀 탈취 이벤트
	int		Event_MollyWolf;		//몰리와늑대 이벤트
	int		Event_Ghost;			//고스트 이벤트
	int		Event_SantaGoblin;		//산타고블린 이벤트
	int		Event_WorldCup;			//월드컵 이벤트
	int		Event_ExpUp;			//경험치업 이벤트
	int		Event_CoupleRing;		// pluto 커플링 이벤트
	int		Event_Watermelon;		// 박재원 - 수박 이벤트
	int		Event_Star;				// 박재원 - 밤하늘의 소원이벤트
	int		Event_Valentine;		// 장별 - 발렌타인 이벤트
	int		Event_PristonAlphabet;	// 박재원 - 알파벳 조합 이벤트
	int		Event_WhiteContrast;	// 장별 - 화이트콘트라스트 이벤트
	int		Event_Candydays;		// 장별 - 캔디데이즈
	int		Event_BlackSmith;		// 장별 - 대장장이의 혼
	int		Event_MagicalGreen;	// 장별 - 매지컬그린
	int		Event_TearOfKara;		// 장별 - 카라의 눈물
	int		Event_WarerMelonMonster;		// 장별 - 수박몬스터 이벤트
	int		Event_Chichen_Day;		// 박재원 - 복날 이벤트(아기 꼬고 몬스터가 나타난다)
	int		Event_MovieBloodyBattle; // 장별 - 영화 혈투
	int		Event_SummerChicken;	//삼계탕 이벤트
	int		Event_GiftBox;			// pluto 선물상자 이벤트
	int		Event_Weath;			// 苟黛岬밍膠
	int		Event_Monster_HP;		// 	밍膠돨HP삶땡

	sEVENT_CASTLE_EXPUP Event_Castle_Expup[10]; //냘쟁삿돤쒔駱;

	int		Event_ExpUpCount;		// 悧鑒긴좆

	int		BlessCastleMode;			//블레스캐슬 설정
	short	sBlessCastle_StartTime[2];	//블레스캐슬 시작 시간 예약 [0]요일 [1]시간

	int		Event_Fruit;				//벎茄

	int		FieldCount;					//뒈暠固셕

	int		Record_JobChanger;		//전업한자 기록
	int		ForeverBlockMode;		//영원한 블럭

	int		Permit_Exp;				//허용오차 경험치
	int		Permit_Money;			//허용오차 돈

	int		ClientProcessTimeChk;	//클라이언트 프로세스 시간감시 최대치
	int		ClientProcessTimeChkOut;//클라이언트 프로세스 시간 초과시 연결종료
	int		Dis_PotionError;		//포션 에러나면 연결 끈음

	int		ExpFixMode;				//오류 경험치 보정

	char	szBlockUserPath[64];	//유저 블럭 데이타 경로

	int		DispBillingTime;		//빌링 남은시간 표시

	int		Disable_LogIn;			//로그인 금지
	int		Disable_LogQue;			//로그큐 처리 금지
	int		Disable_CheckLogOut;	//로그아웃 큐검사 금지

	int		Disable_LogIn2;			//로그인 금지2번째 신규 로그인만 금지
	int		Disable_PCBang;			//PC방 금지 모드

	int		ExpGameTimeMode;		//경험치 시간별 분배(베트남)

	int		ChageJobLevel;			// 淚斂된섬

	int		GamePort;				// 踏狗똥왯

	int		ServerInventoryMode;	//서버의 가상인벤토리로 아이템 관리

	DWORD	DisableIP[DISABLE_IP_MAX][2];		//접근 제한 IP
	int		DisableIP_Count;					//접근 제한 IP 설정 수

	DWORD	EnableIP[ENABLE_IP_MAX][2];			//접근 제한 IP중 허가되는 IP
	int		EnableIP_Count;						//접근 제한 IP 설정 수

	DWORD	AdminIP[ADMIN_IP_MAX][2];			//관리자 IP 목록
	int		AdminIP_Count;						//관리자 IP 설정 수

	DWORD	SystemIP[SYSTEM_IP_MAX][2];			//시스템 IP 목록
	int		SystemIP_Count;						//시스템 IP 설정 수

	DWORD	LoginServerIP[LOGIN_IP_MAX][2];		//로긴서버 IP 목록
	int		LoginServerIP_Count;				//로긴서버 IP 설정 수

	char	szBackupPath[80];					//*백업폴더이름

	char	szClanServerIP[CLAN_SERVER_MAX][20];	//클랜 서버	주소
	int		ClanServerPort[CLAN_SERVER_MAX];		//클랜 서버 포트
	int		ClanServerCount;


	DWORD	Enable_ClientModule[ENABLE_MODULE_CHECK_MAX];	//클라이언트 모튤첵크섬
	int		Enable_ClientModuleCount;						//클라이언트 모듈 첵크섬 카운터

	int		Disable_DecSkillPoint;							//스킬 포인트 감소 첵크 처리

	int		Disable_Quest;									//금지 퀘스트 설정

	int		CrazyPacketMode;							//보안 패킷 모드

	char	szNoticeURL[256];							//Notice URL 설정


	TRANS_SEVER_MAP	AreaServer;							//지역별 서버 매핑

	char	szLinkServerIP[32];							//링크된 서버 IP

	int		RecordAdminCommand;							//운영자 명령 기록

	int		FreeLevel;									//무료 레벨
	char	szFreeGpCode[32];							//무료사용 GPCODE
	int		PresentLevel;								//선물주는 레벨
	int		Event_ComicBirthDay;						//생일선물 얼큰이
	int		Event_Puzzle;								//퍼즐 맞추기 이벤트
	int		Event_BabelHorn;							//바벨뿔이벤트
	int		Event_NineFox;								//구미호이벤트
	int		EVENT_Christmas;							//크리스마스 이벤트
	int		EventPlay_BitMask;							//이벤트 플레이 비트마스크
	int		Event_PCBangPet;							//PC방 펫 이벤트

	int		StartUser_PresentItem;						//시작유저에게 선물 주기

	int		GameGuard_Auth;								//게임가드 보안 설정

#ifdef _XTRAP_GUARD_4_
	int		XTRAP_Timer;								//XTRAP 검사주기		XTRAP_GUARD
	int		XTRAP_MaxDealy;								//XTRAP 검사지체 제한치  XTRAP_GUARD
#endif

	//토너먼트서버 계정 관리
	int		TT_DataServer_Count;									//토너먼트서버 데이타 경로 갯수
	TT_DATA_SERVER_INFO		TT_DataServer[TT_DATA_SERVER_MAX];		//토너먼트서버 데이타 정보

	int		FixedStartField;							//시작 필드 강제 고정시키기
	int		DisableThrowItem;							//아이템 땅에 못버림

	int		CheckPlayField;								//클라이언트 와 서버의  필드 지형 비교 검사

	int		Enable_PKField;								// PK허용 필드 번호

	int		Enable_PKField_All;							// pluto PK허용 필드 전부

	//스킨핵 방지
	int		CheckModelFile;								//모델파일 확인 옵션

	bool	bPK_LOG;
	rsSERVER_CONFIG()
	{
		bPK_LOG = false;
	};
};

//서버 기동 
extern int	ServerMode;

Unit *Serv_CheckOtherPlayPosi( int x, int y, int z );

//경험치와 돈의 결과 한계치 ( 이한계를 넘어가면 저장이 안된다 )
#define	TOTAL_CHECK_MONEY_MAX		52000
#define	TOTAL_CHECK_EXP_MAX			100000




/////////////////// 클라이언트 펑션 위치 구조체 ////////////////////////
#define	dwFUNC_VALUE_MAX	64

struct	sFUNC_VALUE {
	DWORD	dwFunc;
	DWORD	dwLen;
	DWORD	dwChkSum;
};

struct	TRANS_CLIENT_FUNPOS {
	int	size,code;

	int	ClientVersion;

	DWORD	dwFunc_CheckMemSum;
	int		FuncCount;

	sFUNC_VALUE	dwFuncValue[dwFUNC_VALUE_MAX];
};


struct	TRANS_FUNC_MEMORY	{
	int		size,code;
	int		Param[8];
	char	szData[6000];
};


struct	sCHK_POTION_COUNT  {
	int	Ps101;
	int	Ps102;
	int	Ps103;
	int	Ps104;

	int	Pm101;
	int	Pm102;
	int	Pm103;
	int	Pm104;

	int	Pl101;
	int	Pl102;
	int	Pl103;
	int	Pl104;
};

//SOD 점수 출력
struct	sSOD_SCORE {
	int		Flag;
	DWORD	dwDispTime;
	int		Score;
	int		MyTeam;
	int		TeamScore[4];
	int		Round;
	DWORD	dwPlayTime;

	/////// SOD 연출 이벤트 /////////

	DWORD	dwSoD_NextStageTime;		//다음 스테이지 넘어가는 시간
	int		SodNextStageNum;			//넘어갈 스테이지 번호
	int		NextRound;
	DWORD	dwSoD_CloseStageTime;		//화면은 닫는 이펙트 적용시간

	///////// SOD 예약 연출 //////////////
	int		EffectStartCount;			//이펙트 시작까지의 카운터
	int		EffectCode;					//이펙트 코드

	//////// SOD 득점 효과 /////////////
	int		ScoreEffectCount;				//득점 효과

};



#define	CHAR_EVENT_STARPOINT		300

#define	ITEM_UNIQUE_CODE_NORMAL		1
#define	ITEM_UNIQUE_CODE_QUEST		2


#define BIMASK_PRORATE_USER			1
#define BIMASK_FREE_USER			2
#define BIMASK_VIP_USER				4
#define BIMASK_BIRTHDAY_USER		8
#define BIMASK_TIMELEVEL_USER		16
#define BIMASK_ADULT_USER			32


#define	MONSTER_CLASS_NORMAL		0
#define	MONSTER_CLASS_BOSS			1
#define	MONSTER_CLASS_HAMMER		200
#define	MONSTER_CLASS_GHOST			300

#endif