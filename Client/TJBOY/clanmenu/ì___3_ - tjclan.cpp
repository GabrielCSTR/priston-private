//====================================================================
//ktj : runmap3d.suo파일때문에 세이브가안되는경우가 있으므로 그럴때는 그 파일을 지울것
//====================================================================
//4.01 P10.47
//sinMain.cpp, sinInterFace.cpp에서 운영됨
#define TJCLAN_CPP
#include "tjclanDEF.h"

#ifdef USE_PROSTONTALE		//=========== 프리스턴소스인경우

#include "..\\..\\sinbaram\\SinLinkHeader.h"
#include "..\\..\\HoBaram\\HoLinkHeader.h"
//#include "HoParty.h"
#include "..\\..\\language.h"
#include "..\\..\\HoBaram\\HoTextFile.h"
#include "tjclan.h"
#include "tjscroll.h"
#include "cE_Cmake.h"
#include "cE_chip.h"
#include "cE_user.h"
#include "cE_isclanmember.h"
#include "cE_report.h"
#include "cE_chatlist.h"
#include "cE_deletecha.h"
#include "cE_Cjoin.h"
#include "cE_CViewClanInfo.h"
#include "cE_Updatecldata.h"

#include "..\\isaocheck\\auth.h"
#include "..\\isaocheck\\isaocheck.h"


//#define USE_YAHEL		//아웰서버만 사용하는경우는 열어둘것


extern HWND hTextWnd;
extern HWND hFocusWnd;

extern char UserAccount[256];		//id가 들어있는 버퍼
extern char	szConnServerName[16];	//접속한 서버이름이 들어있는 버퍼




#define MOUSE0() TJmb[0]


#else						//=========== 포리스턴소스가 아닌경우

#include <windows.h>
#include <stdio.h>
#include "tjclan.h"
#include "tjscroll.h"

#include "clan_Enti.h"
#include "cE_Cmake.h"
#include "cE_chip.h"
#include "cE_user.h"
#include "cE_isclanmember.h"
#include "cE_report.h"
#include "cE_chatlist.h"
#include "cE_deletecha.h"
#include "cE_CJoin.h"
#include "cE_CViewClanInfo.h"
#include "cE_Updatecldata.h"

#include "..\\isaocheck\\auth.h"
#include "..\\isaocheck\\isaocheck.h"





#define MAX_PARTY_MEMBER	6

#define PARTY_NONE		500
#define PARTY_START		1000
#define PARTY_PROCESS	2000
#define PARTY_END		3000

char UserAccount[256];		//id가 들어있는 버퍼
char szConnServerName[16];	//접속한 서버이름이 들어있는 버퍼

extern int MouseButton[3] ;	//마우스버튼눌림첵크 : winmain.cpp에 정의함
extern int MouseDblClick ;		//tjclan.cpp


extern HWND    g_hwnd;
extern POINT	pCursorPos;
extern HINSTANCE g_hInst;


#define MOUSE0() MouseButton[0]


#endif


int ClanCharMove=0;	//클랜메뉴판안의 마우스의 움직임에 캐릭터가 영향없도록 한다.
int ClanCLCharMove=0;//클랜채팅리스트메뉴판안의 마우스의 움직임에 캐릭터가 영향없도록 한다.


int  banisF[100];

//int TJwheel=0; //ktj : 휠데이타
void fd2( char *fmt, ...);









void clan_Mouse(int msg)
{
	switch(msg){
	case WM_LBUTTONDOWN:
		TJmb2[0] = TJmb[0] = TRUE;
		break;

	case WM_LBUTTONUP:
		TJmb2[0] = TJmb[0] = FALSE;
		break;

	case WM_RBUTTONDOWN:
		TJmb2[1] = TJmb[1] = TRUE; //ktj
		break;

	case WM_RBUTTONUP:
		TJmb2[1] = TJmb[1] = FALSE; //ktj
		break;

	case WM_MBUTTONDOWN:
		TJmb2[2] = TJmb[2] = TRUE; //ktj
		break;

	case WM_MBUTTONUP:
		TJmb2[2] = TJmb[2] = FALSE; //ktj
		break;
	}
}









void ktj_imsi_clanMENU_Main()
{
	static cnt=0;
	cnt++;

	int mainchk;
	
	if(cnt<10) {
		mainchk = PARTY_START;
		
	}
	else {
		mainchk = PARTY_PROCESS;
	}

	

	Interface_clanmenu.Main(mainchk );
}

void ktj_imsi_clanMENU_Draw()
{
	Interface_clanmenu.Draw();
}
		

void clanMENUinit()
{
	
	Interface_clanmenu.CLANmenu_INIT();
	//ktj : 클랜상에서의 현재 위치를 알아낸다.
	Interface_clanmenu.CLANmenu_clanPOSITION();
}





/*==================================================================================
//
// 외부에서 사용되는 클랜의 구동 셋팅 함수들								   start
//
==================================================================================*/


/*///////////////////////////////////////////////////////////////////////////
: 클라스명 : 
: 하 는 일 : 클랜 맨 처음 셋팅
///////////////////////////////////////////////////////////////////////////*/

//ktj : 클랜메뉴 인터페이스 init
//setN : 0 : 최초 셋팅  1: 두번째셋팅(모든 
void clanMENU_INIT(int setN)
{	
	if(!bCheckHostNameandPort) return;



	switch(setN) {
	case -1:				//실제로는 사용안함에 주의
		ZeroMemory(&ClanWonList,  sizeof(CLANWONLIST ));

		Interface_clanmenu.CLANmenu_INIT();
		//ktj : 클랜상에서의 현재 위치를 알아낸다.
		Interface_clanmenu.CLANmenu_clanPOSITION();
		break;


	case 0:				//맨처음셋팅 : 캐릭터 선택직전셋팅

		void CreateSaveData_dir();
		CreateSaveData_dir();			//savedata/clandata만듦


		ZeroMemory(&ClanWonList,  sizeof(CLANWONLIST ));
		Interface_clanmenu.CLANmenu_INIT();

		break;

	case 1:				//겜 실제 시작시 셋팅
	#ifdef USE_PROSTONTALE		//=========== 프리스턴소스인경우

		cBaseMenu.Load2();
		cClanChatting.Load2();
		Interface_clanmenu.Init2();	


		//setN은 0의 경우 캐릭이름을 따로 주어야 함에 크게 주의할것.
#ifdef USE_YAHEL
		Interface_clanmenu.SetUserData(UserAccount, sinChar->szName, "아웰",//szConnServerName, 
#else
		Interface_clanmenu.SetUserData(UserAccount, sinChar->szName, szConnServerName, 
#endif
			sinChar->Money,500000); //6인 이하

		//ktj: 임시로 지움.
		//ktj : 클랜상에서의 현재 위치를 알아낸다.
		Interface_clanmenu.CLANmenu_clanPOSITION();
		
	
	#endif
		break;
	}
}


//hoLogin.cpp에서 사용함.
int isDELETE_character(char *charName) 
{
	if(!bCheckHostNameandPort) return 1;		//1은 캐릭터를 지워도된다는뜻


	int web_DB_state_FLAG_WAIT();
	while(1) {
		if(web_DB_state_FLAG_WAIT() == 1) 
			break;
	}



	//ktj : 이거 이상함 디버깅=====================================================
#ifdef USE_YAHEL
	Interface_clanmenu.SetUserData(UserAccount, charName, "아웰", //szConnServerName, 
#else
	Interface_clanmenu.SetUserData(UserAccount, charName, szConnServerName, 
#endif

		500000   ,500000); //6인 이하 //ktj : 이거 이상함 디버깅=======================================

	//ktj : 클랜상에서의 현재 위치를 알아낸다.
	Interface_clanmenu.CLANmenu_clanPOSITION();
	cldata.myPosition = 0;//CLANNO_REGESTER;
	while(1) {
		web_DB_main();					//web db를 사용하는 클랜 메뉴에서만 불리워짐.	
		cIsClanMember.Main();			//ktj : 클랜원의 포지션 체크 메인

		if(cldata.myPosition != 0) 
			break;
	}

	while(1) {
		if(web_DB_state_FLAG_WAIT() == 1) 
			break;
	}

	/*
	#define CLANUSER					100		//일반유저
	#define CLANCHIP					101		//칲
	#define CLANNO_REGESTER				102		//무등록자
	#define CLAN_NOCONNECT				103		//컨넥트가 안되서 설정불가
	*/
	return cldata.myPosition;
}



void CLAN_MENU::Init2()
{
	#ifdef USE_PROSTONTALE		//=========== 포리스턴소스인경우

	MatPartyBackGround =
		CreateTextureMaterial( "image\\Sinimage\\Help\\party_win.tga" , 0, 0, 0,0, SMMAT_BLEND_ALPHA );

	//box===========================================================================start

	hBox1 = 
		CreateTextureMaterial( "image\\Sinimage\\Help\\HelpBoxCorner.tga",  0, 0, 0,0, SMMAT_BLEND_ALPHA );

	hBox2 = 
		CreateTextureMaterial( "image\\Sinimage\\Help\\HelpBoxLine.tga",  0, 0, 0,0, SMMAT_BLEND_ALPHA );

	hBox3 = 
		CreateTextureMaterial( "image\\Sinimage\\Help\\box3.tga",  0, 0, 0,0, SMMAT_BLEND_ALPHA );

	hBox4 = 
		CreateTextureMaterial( "image\\Sinimage\\Help\\box4.tga",  0, 0, 0,0, SMMAT_BLEND_ALPHA );
	hBox5 = 
		CreateTextureMaterial( "image\\Sinimage\\Help\\box5.tga",  0, 0, 0,0, SMMAT_BLEND_ALPHA );

	hBox6 = 
		CreateTextureMaterial( "image\\Sinimage\\Help\\box6.tga",  0, 0, 0,0, SMMAT_BLEND_ALPHA );

	hBox7 = 
		CreateTextureMaterial( "image\\Sinimage\\Help\\box7.tga",  0, 0, 0,0, SMMAT_BLEND_ALPHA );

	hBox8 = 
		CreateTextureMaterial( "image\\Sinimage\\Help\\box8.tga",  0, 0, 0,0, SMMAT_BLEND_ALPHA );

	hBox9 = 
		CreateTextureMaterial( "image\\Sinimage\\Help\\box9.tga",  0, 0, 0,0, SMMAT_BLEND_ALPHA );

	//box===========================================================================end
	hScl_icon_tj = CreateTextureMaterial( "image\\Sinimage\\Help\\scl_icon.tga", 0, 0, 0,0, SMMAT_BLEND_ALPHA );


	cBaseMenu.copy_LoadResource2(&cIsClanMember);		//리소스 카피
	cBaseMenu.copy_LoadResource2(&cClanChip);		//리소스 카피
	cBaseMenu.copy_LoadResource2(&cClanUser);		//리소스 카피
	cBaseMenu.copy_LoadResource2(&cClanMake);		//리소스 카피
	cBaseMenu.copy_LoadResource2(&cClanReport);		//리소스 카피
	cBaseMenu.copy_LoadResource2(&cClanChatting);		//리소스 카피
	cBaseMenu.copy_LoadResource2(&cClanDeleteCha);		//리소스 카피
	cBaseMenu.copy_LoadResource2(&cClanJoin);		//리소스 카피	
#endif
}

void CLAN_MENU::CLANmenu_INIT()
{
	if(!bCheckHostNameandPort) return;
	//g_ViewClanInfo.LoadData();

	Init();


#ifdef  USE_PROSTONTALE

	//SetUserData(UserAccount, sinChar->szName, szConnServerName); //6인 이하
	//ktj : 이게 맞음.
	//SetUserData(UserAccount, sinChar->szName, szConnServerName, sinChar->Money,1000); //6인 이하

	//ktj : 원본
#ifdef USE_YAHEL
	SetUserData(UserAccount, sinChar->szName, "아웰",//szConnServerName, 
#else
	SetUserData(UserAccount, sinChar->szName, szConnServerName, 
#endif
		sinChar->Money,500000); //6인 이하
	//SetUserData(UserAccount, "허걱덕", "아웰", 500000 ,500000); //6인 이하

	//SetJoinData("하하하","울트라","헌트");

#else



	//SetJoinData("하하하","울트라","헌트");
	//클랜장으로 등록된 id임		
	//SetUserData("cant","캔트","아웰",500000,100000);
	//SetUserData("canto","에혀미치","아웰",500000,100000);
	//SetUserData("ccc","감1","아웰",500000,100000);
	strcpy(szConnServerName,"펭귄서버");
	SetUserData("ubi","우비",szConnServerName,500000,100000);

	//SetUserData("ccc","하하1","아웰",500000,100000);
	//SetUserData("ccc","하하190","아웰",500000,100000);

	//SetUserData("maxy","아뵤","아웰",500000,100000);
	//SetUserData("ccc","오잉4","아웰",500000,100000);
	

	//SetUserData("test2000","클랜무사","아웰",500000,100000); //6인 이하
	//SetUserData("ccc","성남70","아웰",500000,100000);
	//클랜원으로 등록된 id임	

#endif
}


/*///////////////////////////////////////////////////////////////////////////
: 클라스명 :
: 하 는 일 : 계정에 만들어진 캐릭터들의 클랜정보 알아오기
///////////////////////////////////////////////////////////////////////////*/
BOOL bGetChaClan = FALSE; //계정에 관련된 캐릭터들의 클랜정보를 읽어오는지 체크
int  nGetChaClan = 0;   //0: 진행안됨 1: 진행되고있음 2: 진행완료  3: 에러
int nStatusCount=0;	


int cntsu;
char *szSelectCha[5][2];


void InitSelectCha()
{
	if(!bCheckHostNameandPort) return;

	ZeroMemory(chacldata,sizeof(chacldata));
	ZeroMemory(szSelectCha,sizeof(szSelectCha));
}

void ClearSelectCha()
{
	if(!bCheckHostNameandPort) return;


	int i;
#ifdef USE_PROSTONTALE		//=========== 포리스턴소스인경우
	for(i =0; i< 5; i++)
	{
		if(chacldata[i].hClanMark) {

			chacldata[i].hClanMark->Release();
			chacldata[i].hClanMark = NULL;

		}
		if(chacldata[i].hClanMark16) {

			chacldata[i].hClanMark16->Release();
			chacldata[i].hClanMark16 = NULL;

		}
	}

	
#else
	for(i =0; i< 5; i++)
	{
		if(chacldata[i].hClanMark) {

			
			DeleteObject(chacldata[i].hClanMark);

		}
		if(chacldata[i].hClanMark16) {

			DeleteObject(chacldata[i].hClanMark16);

		}
	}
#endif
	bGetChaClan = FALSE;
	ZeroMemory(szSelectCha,sizeof(szSelectCha));
	ZeroMemory(chacldata,sizeof(chacldata));
	ZeroMemory(&cldata,sizeof(CLANDATA));

}

//캐릭터들의 이름을 입력
int HONG_GetChaClanName(char* id, char* chaname)
{
	if(!bCheckHostNameandPort) return 0;


	int i;
	int nReturn = 0;;
	for(i = 0; i < 5; i++)
	{
		if(szSelectCha[i][0] == NULL)
		{
			szSelectCha[i][0] = id;
			szSelectCha[i][1] = chaname;			
			nReturn =1;

			break;
		}
	}

	cntsu = i+1;
	
	if( i == 5) return -1;

	return nReturn;
}


int  main_chaC()
{
	if(!bCheckHostNameandPort) return 0;

	nStatusCount=0;
	
	while(1) {

	Interface_clanmenu.Main(PARTY_PROCESS );
	
	if(nStatusCount>=cntsu) break;

	if(OpenFlag==0) {
		bGetChaClan = TRUE;
		int GetChaClanName(char* id, char* chaname, char* gserver);
		GetChaClanName(szSelectCha[nStatusCount][0], szSelectCha[nStatusCount][1], szConnServerName);
		
		}
	}

	return 0;

}

int GetChaClanName(char* id, char* chaname, char* gserver)
{
	if(!bCheckHostNameandPort) return 0;


	bGetChaClan = FALSE;
	C_menuN2= 0;
	OpenFlag = 1;
	joinAnswer = 0;
	nGetChaClan = 0;
	void SetUserData2(char* id, char* chaname, char* gserver);
	SetUserData2(id, chaname, gserver);
	C_menuN = CLAN_isClanWon;
	bGetChaClan = TRUE;

	return 1;	
}









/*///////////////////////////////////////////////////////////////////////////
: 클라스명 :
: 하 는 일 : 클랜원으로서의 위치를 알아냄.
///////////////////////////////////////////////////////////////////////////*/
int CLAN_MENU::CLANmenu_clanPOSITION()
{
	if(!bCheckHostNameandPort) {
		cldata.myPosition = CLAN_NOCONNECT;
		return 0;
	}


	if(OpenFlag==1) return 0;		//이 메뉴가 닫혀있을때만 가능함.
	
	C_menuN2= 0;
	OpenFlag = 1;
	joinAnswer = 0;
	C_menuN = CLAN_isClanWon;
	

	menuInit(C_menuN );

	ClanCharMove = 1;			//ktj : 마우스가 첵크하는 박스첵크 
	return 1;
}


/*///////////////////////////////////////////////////////////////////////////
: 클라스명 :
: 하 는 일 : NPC와 만났을때
///////////////////////////////////////////////////////////////////////////*/
void CLANmenu_meetNPC()	//newplay.cpp에서 사용함.
{
	Interface_clanmenu.CLANmenu_meetNPC();	
}
int CLAN_MENU::CLANmenu_meetNPC()
{	
	if(OpenFlag==1) {
		if(C_menuN == CLAN_DISPLAY_INFO)
		{
			C_menuN = CLAN_CLOSE_END_BEFORE;									
			
		}
		return 0;		//이 메뉴가 닫혀있을때만 가능함.
	}

	
	C_menuN2= 0;
	OpenFlag = 1;
	joinAnswer = 0;	
	if(!bCheckHostNameandPort)
	{
		C_menuN = CLANSERVER_INSPECT_BEFORE;
		
	}
	else
	{
		C_menuN = CLAN_GO_NPCSTART;
	}
	

	//menuInit(C_menuN );

	ClanCharMove = 1;			//ktj : 마우스가 첵크하는 박스첵크 
	return 1;
}






/*///////////////////////////////////////////////////////////////////////////
: 클라스명 :
: 하 는 일 : 클랜원들의 채팅리스트를 볼때
///////////////////////////////////////////////////////////////////////////*/
void CLANmenu_ChatList(int sw)	//newplay.cpp에서 사용함.l
{
	Interface_clanmenu.CLANmenu_ChatList(sw);	
}
void CLAN_MENU::CLANmenu_ChatList(int sw)
{

	if(!bCheckHostNameandPort) return;
	if(OpenFlag==1) return;
	if(bOpenChatList) return;

	ChatList_CmenuN2 = 0;

	switch(sw)
	{
	case 0: //스크롤 되게
		
		cClanChatting.InitClanChatList();
		if(bIsReadData) ChatList_CmenuN = CLAN_DISPLAY_OPEN;
		else	ChatList_CmenuN = CHATLIST_READDATA;
		break;
	case 1: //스크롤 안되게
		cClanChatting.NoScroll();
		//if(bIsReadData) ChatList_CmenuN = CLAN_DISPLAY_OPEN;
		//else	ChatList_CmenuN = CHATLIST_READDATA;		

		ChatList_CmenuN = CLAN_DISPLAY_INFO;				
		cClanChatting.menuInit(ChatList_CmenuN);

#ifdef USE_PROSTONTALE		//=========== 프리스턴소스인경우
		
#else
	OpenFlag = 1;
	C_menuN = ChatList_CmenuN;
	
#endif


		break;
	}
}




void CLANmenu_ChatList_Main()	//newplay.cpp에서 사용함.l
{
	cClanChatting.Main();			//클랜 채팅리스트
}
void CLANmenu_ChatList_Draw()	//newplay.cpp에서 사용함.l
{
	cClanChatting.Draw();			//클랜 채팅리스트
}


/*///////////////////////////////////////////////////////////////////////////
: 클라스명 :
: 하 는 일 : cldata업데이트 할때
///////////////////////////////////////////////////////////////////////////*/
void Updatecldata()
{
	//Interface_clanmenu.Updatecldata();
	g_UpdateCldata.Updatecldata();
}


/*///////////////////////////////////////////////////////////////////////////
: 클라스명 : 권유하는 메뉴들.
: 하 는 일 : 일반인에게 클랜의 가입을 권유하면 권유한다는 메뉴가 뜬다.
///////////////////////////////////////////////////////////////////////////*/

//권유받는 사람이 사용하는 함수
void ClanJoin(char *oneClanName, char *oneChipCharid)
{
	//Interface_clanmenu.SetJoinData("울트라","헌트");
	Interface_clanmenu.SetJoinData(oneClanName,oneChipCharid);
	Interface_clanmenu.ClanJoin();
}

//ktj : 권유받은자가 리턴해주는 값(이함수를 사용해 리턴해준다.)
//0:취소 1:OK
int JoinAnswer()
{
	return cClanJoin.nJoinAnswer;
}

void CLAN_MENU::ClanJoin()
{
	if(OpenFlag==1) return;
	C_menuN2 = 0;
	OpenFlag = 1;
	ClanCLCharMove = 1;			//ktj : 마우스가 첵크하는 박스첵크 	
	C_menuN = CLAN_JOIN_before;
	
}

/*///////////////////////////////////////////////////////////////////////////
: 클라스명 :
: 하 는 일 : 클랜장이 클랜원을 등록시킬때
///////////////////////////////////////////////////////////////////////////*/
void joinClanMember()
{
	Interface_clanmenu.joinClanMember();
}

void CLAN_MENU::joinClanMember()
{
	if(OpenFlag==1) return;
	C_menuN2 = 0;
	OpenFlag = 1;
	ClanCLCharMove = 1;			//ktj : 마우스가 첵크하는 박스첵크 	
	C_menuN = CLAN_JOIN_chip;
}

//ygy: 캐릭터 삭제 임시
void CLANmenu_DeleteCha(char *id, char *gserver, char *chaname)
{
	cClanDeleteCha.SetDeleteChaInfo(id, gserver, chaname);
	Interface_clanmenu.CLANmenu_DeleteCha();

	cClanDeleteCha.bFlag = FALSE;
}


/*///////////////////////////////////////////////////////////////////////////
: 클라스명 :
: 하 는 일 : 캐릭터 삭제시
///////////////////////////////////////////////////////////////////////////*/
void ktj_IMSI_DELETE()
{
	//extern char UserAccount[256];		//id가 들어있는 버퍼
	//extern char szConnServerName[16];	//접속한 서버이름이 들어있는 버퍼
	//CLANmenu_DeleteCha_SetCharacter(UserAccount, szConnServerName, "허걱덕");
}



//ktj :  1. 캐릭 지우기전에 셋팅하는 함수
void CLANmenu_DeleteCha_SetCharacter(char *id, char *gserver, char *chaname)
{
	cClanDeleteCha.SetDeleteChaInfo(id, gserver, chaname);

	//ktj : 2. 지우는 메뉴를 셋팅한다.
	Interface_clanmenu.CLANmenu_DeleteCha();
}

//ktj : 캐릭 지우기전에 불리우는 함수
void CLAN_MENU::CLANmenu_DeleteCha()
{
	C_menuN2 = 0;
	OpenFlag = 1;
	ClanCLCharMove = 1;			//ktj : 마우스가 첵크하는 박스첵크 	
	C_menuN = CLAN_DELETECHA_START;

	cClanDeleteCha.SetHowDeleteChaFlag();
}

//ktj : 3. 상태 플래그를 보고 2이면 캐릭을 삭제하고 3이면 삭제 못함.(0,1이면 2,3될때까지 기다린다)
int CLANmenu_DeleteCha_flag()
{
	//삭제전 : 0
	//삭제중 : 1
	//삭제 ok : 2
	//삭제 안됨 : 3
	return cClanDeleteCha.GetHowDeleteChaFlag();
}



//////////////////////////////////////////////////////////////////////////////////
//클랜 정보 갖어오기
//
/////////////////////////////////////////////////////////////////////////////////
int ReadClanInfo(DWORD dwClanNum)
{
	if(OpenFlag==1) return -1;		//이 메뉴가 닫혀있을때만 가능함.

	g_ViewClanInfo.SearchClan(dwClanNum);
	BOOL bFlag;
	bFlag = g_ViewClanInfo.GetFlag();  //하드에 저장되어는지 아니면 다운 받아야 하는지 체크 
	
	if(!bFlag)
	{
		//web에서 다운받음.
		g_ViewClanInfo.DownLoadClanInfo(dwClanNum);
	}
	return ClanInfo_nNum;		//0~99;
}







//==================================================================================
// 외부에서 사용되는 클랜의 구동 셋팅 함수들								    end
//=================================================================================







/*==================================================================================
//
// 클랜메뉴																	   start
//
==================================================================================*/
CLAN_MENU::CLAN_MENU()
{
	nClanWon_Num = 0;
	nScl_Bar = 0;           //스크롤바
	g_nClanIconNum;			//헬프아이콘 총수
	g_HelpIconNumber = 0;    
	g_HelpDisPlay = 0;

}

CLAN_MENU::~CLAN_MENU()
{
}


//마우스위치를 첵크안토록하는것 hoLinkHeader.cpp에서 사용
POINT clanBoxPos;
POINT clanCLBoxPos;
void CLAN_MENU::Init()
{
	OpenFlag = 0;

	C_menuN = 0;
	C_menuN2 =0;

	//BackStartPos.x = 70;
	//BackStartPos.y = 94;

	//BackStartPos.x = 100;
	//BackStartPos.y = 94;

	BackStartPos.x = 101;
	BackStartPos.y = 114;


	//클랜메뉴에서 월드쪽에 마우스가 움직임이 전달안되도록한다.
	clanBoxPos.x = BackStartPos.x;
	clanBoxPos.y = BackStartPos.y;

	//클랜채팅 리스트메뉴에서 월드쪽에 마우스가 움직임이 전달안되도록한다.
	clanCLBoxPos.x = 540+60;		//60은 그림이 오른편에 붙어있기 때문임
	clanCLBoxPos.y = CHATLIST_BOX_Y;


	

	ZeroMemory(szRemoveClanWon,sizeof(char)*500);	
	ZeroMemory(ClanHelpIcon,sizeof(CLANHELPICON)*CLANHELPICON_NUM);		
	ZeroMemory(cldata.szJoinClanName,sizeof(char)*64);   //조인 클랜 이름
	ZeroMemory(cldata.ChaName,sizeof(char)*64);  //조인하는 유저 캐릭터 이름
	ZeroMemory(cldata.szJoinClanChipName,sizeof(char)*64);   //조인하는 클랜장 이름
	ZeroMemory(szReconfReleaseMsg,sizeof(char)*2048);

	
	nClanWon_Num = 0;			//클랜원파싱후 클랜원의 명수(클랜장제외)
	nReleaseClanWon = 0;		//삭제 클랜원
	membmp = new MENUBMP;
	
	//hMark = NULL;

	Load();	
	cClanChatting.Load();

	//ktj : 메뉴 관련 클라스 셋팅 ===================
	
	cBaseMenu.Load();

	
	cIsClanMember.Init(1);
	cIsClanMember.setParent(&cBaseMenu);
	cBaseMenu.copy_LoadResource(&cIsClanMember);		//리소스 카피

	cClanChip.Init(1);
	cClanChip.setParent(&cBaseMenu);
	cBaseMenu.copy_LoadResource(&cClanChip);		//리소스 카피
	cBaseMenu.SetBase(&cClanChip);

	cClanUser.Init(1);
	cClanUser.setParent(&cBaseMenu);
	cBaseMenu.copy_LoadResource(&cClanUser);		//리소스 카피
	cBaseMenu.SetBase(&cClanUser);

	cClanMake.Init(1);
	cClanMake.setParent(&cBaseMenu);
	cBaseMenu.copy_LoadResource(&cClanMake);		//리소스 카피

	cClanReport.Init(1);
	cClanReport.setParent(&cBaseMenu);
	cBaseMenu.copy_LoadResource(&cClanReport);		//리소스 카피


	cClanChatting.Init(1);
	cClanChatting.setParent(&cBaseMenu);
	cBaseMenu.copy_LoadResource(&cClanChatting);		//리소스 카피
	cBaseMenu.SetBase(&cClanChatting);


	cClanDeleteCha.Init(1);
	cClanDeleteCha.setParent(&cBaseMenu);
	cBaseMenu.copy_LoadResource(&cClanDeleteCha);		//리소스 카피

	cClanJoin.Init(1);
	cClanJoin.setParent(&cBaseMenu);
	cBaseMenu.copy_LoadResource(&cClanJoin);		//리소스 카피	
	

}


/*///////////////////////////////////////////////////////////////////////////
: 함수명   : menuInit
: 하 는 일 : 메뉴 총괄 Init
: 반 환 값 :
: 파라미터 :
///////////////////////////////////////////////////////////////////////////*/
void CLAN_MENU::menuInit(int num)
{
	
	cIsClanMember.menuInit(num);		//클랜만들기 메뉴 initialize
	cClanMake.menuInit(num);		//클랜만들기 메뉴 initialize
	cClanChip.menuInit(num);		//클렌칲 메뉴 initialize
	cClanUser.menuInit(num);		//클랜유저 메뉴 initialize
	cClanChatting.menuInit(num);
	cClanDeleteCha.menuInit(num);
	cClanJoin.menuInit(num);
}







/*///////////////////////////////////////////////////////////////////////////
: 클라스 명: 
: 하 는 일 : 마우스로 누른 메뉴 번호 첵크함수.
: 반 환 값 :
:파라미터  :
///////////////////////////////////////////////////////////////////////////*/
int CLAN_MENU::chkMenu(int x, int y, RECT *r) 
{
	if(r->left <= x   &&   x<= r->right ) 
		if(r->top <= y   &&   y<= r->bottom ) 
			return 1;
	return 0;			//아무것도 선택안함.
}
int CLAN_MENU::chkeckMenuN()
{
	int i;
	
	for(i=0; i<menuSu; i++) {
		if(  chkMenu(pCursorPos.x, pCursorPos.y, &menuPos[i])  ) {
			return i;
		}
	}
	return -1;
}





//칲이 권유하면 권유받은 사람한테 뜨는 메뉴임.(현재 netplay.cpp에서 사용중)
void menu_joinOpen(char *chipCharID)
{
	//Interface_clanmenu.menu_joinOpen(chipCharID);
}


//조인메뉴는 클랜칲이 권유하면 권유받은 사람한테 메뉴가 뜬다.
int CLAN_MENU::menu_joinOpen(char *chipCharID)		//칲의 캐릭터 id
{
	/*
	if(OpenFlag==1) return 0;					//이 메뉴가 닫혀있을때만 가능함.
	if( cldata.myPosition == 100 ||				//100(클랜원), 101:클랜칲에게 권유할수 없다.
		cldata.myPosition == 101)				return 0;

	strcpy(cldata.chipCharID, chipCharID);
	C_menuN   = CLAN_JOIN_before;		//조인에 적합한지 여부.
	C_menuN2  = 0;
	OpenFlag  = 1;
	joinAnswer= 0;

	//ktj
	ClanCharMove = 1;
	*/

	return 1;
	
}


void menu_joinOpen_Chip(int isOK, char *clanWonID, char *clanWonCharID)
{
	Interface_clanmenu.menu_joinOpen_Chip(isOK, clanWonID, clanWonCharID);		//칲의 캐릭터 id;
}


//권유받은 사람이 OK하면 그명령이 클랜칲에게 되돌아와 클랜칲이 가입시키는 메뉴임.
//주의 : 화면상에는 메뉴가 뜨지않음.
int CLAN_MENU::menu_joinOpen_Chip(int joinOK, char *clanWonID, char *clanWonCharID)		//칲의 캐릭터 id
{
	if(OpenFlag==1) return 0;		//이 메뉴가 닫혀있을때만 가능함.

	if(cldata.myPosition != 101) return 0;	//101:클랜칲만 사용가능한 메뉴임.

	/*
	if(joinOK==0) {
		C_menuN= CLAN_JOIN_chip_NO	;		//클랜에 가입하기를 거부함.
		C_menuN2= -1;
	}
	else {
		*/
		C_menuN = CLAN_JOIN_chip		;	//클랜에 등록시킨다.
		strcpy(cldata.clanJoinID, clanWonID);
		strcpy(cldata.clanJoinCharID, clanWonCharID);

		C_menuN2= 0;
	//}
	OpenFlag = 1;
	joinAnswer = 0;

	//ktj
	ClanCharMove = 1;


	return 1;
}








//int chkN11 = -1;
//int chkN22 = -1;

extern BOOL bip_port_error;
int CLAN_MENU::Main(int sw)
{
	if(bip_port_error) return 0;
	web_DB_main();					//web db를 사용하는 클랜 메뉴에서만 불리워짐.	

	//char		szErrorMsg[256];
	if(OpenFlag==0) return 0;		//이 메뉴는닫혔음


	switch(sw) {
	case PARTY_START:				//처음 불리워질때의 처리
		return 1;
	case PARTY_END:					//끝날즘에 불리워질때의 처리
		return 1;
	}

	//ClanCharMove = 1;
									//ktj : auth.cpp의 web_DB첵크용임.
	cBaseMenu.Main();				//ktj : 공용 메뉴 의 메인
	cIsClanMember.Main();			//ktj : 클랜원의 포지션 체크 메인
	cClanReport.Main();				//ktj : 메시지 처리용 메인
	cClanMake.Main();				//ktj : 클랜을 만들경우의 메인
	cClanChip.Main();				//클랜 칩 메세지 처리
	cClanUser.Main();				//클랜 유저 메세지처리
	cClanJoin.Main();
#ifdef USE_PROSTONTALE		//=========== 프리스턴소스인경우

	//cClanChatting.Main();			//클랜 채팅리스트
#else
	cClanChatting.Main();			//클랜 채팅리스트
#endif

	cClanDeleteCha.Main();            //캐릭터 삭제시
	return TRUE;
}




char loadis[256] = {0,};
char loadis2[256] = {0,};
char updateis[256] = {0,};


int CLAN_MENU::Draw()
{	
	if(bip_port_error) return 0;
	
#ifdef USE_PROSTONTALE		//=========== 포리스턴소스인경우

	if(smConfig.DebugMode ) {



	//ktj : 임시로 버그첵크
	char buf[256];
	
	wsprintf(buf, "bug :  %d ================ : (myPos:%d ) (클랜마크번호%s,%d)  cldata.money %d ", C_menuN, cldata.myPosition, cldata.ClanMark, cldata.intClanMark, cldata.money);
	Draw_C_Text(buf, 0,0,   0);
	

	wsprintf(buf, "cldata.szID %s  cldata.ChaName %s cldata.name %s (C_menuN %d C_menuN2 %d) ================ ", cldata.szID,cldata.ChaName, cldata.name, C_menuN, C_menuN2);
	Draw_C_Text(buf, 0,16,   0);
	

	//클랜인포 디버깅
	int cinfoX = 0;
	int cinfoY = 32;
	int i2;
	for(i2=0; i2<100; i2++) {
		if(ClanInfo[i2].nStatus==0) continue;

		char buf[256];
		wsprintf(buf, "ClanInfo[%d] %s %s %s ", i2, 
				ClanInfo[i2].ClanInfoHeader.ClanMark_Num,
				ClanInfo[i2].ClanInfoHeader.ClanName,
				ClanInfo[i2].ClanInfoHeader.ClanReport);
		//debug_fd2( buf);
		Draw_C_Text(buf, cinfoX ,cinfoY,   0);
		cinfoY+=16;
	}
	

	}



#endif
	/*
	wsprintf(buf, "클랜채팅리스트로드는  %s ================ ", loadis);
	Draw_C_Text(buf, 0,32,   0);
	wsprintf(buf, "클랜채팅리스트로드2   %s ================ ", loadis2);
	Draw_C_Text(buf, 0,32+16,   0);

	wsprintf(buf, "없데이트카운트 %s ================ ", updateis);
	Draw_C_Text(buf, 0,64,   0);
	*/
	
	
	


	

	//InvalidateRect(g_hwnd,NULL,1);
	if(OpenFlag==0) return 0;	


#ifndef USE_PROSTONTALE		//=========== 윈도함수

	window_renderINIT();			//처음 한번셋팅함.
	HDC hdc = GetDC(g_hwnd);	
	HDC sorDC;
	sorDC  = CreateCompatibleDC(hdc);
	HDC destdc=CreateCompatibleDC(hdc);
	SelectObject(destdc, Dback.hb );
	PatBlt(destdc,0,0,800,600,PATCOPY);
	char szBuf[100];
	extern POINT	pCursorPos;
	
	// 0 : 작업수행하기전 1: 다운로드 수행중 2 : 작업완료 3: 에러
	wsprintf(szBuf,"C_menuN : %d  ,x = %d, y = %d , 진행 과정 : %d 클랜 이름 : %s",
		C_menuN,pCursorPos.x,pCursorPos.y,nCheckDownLoad,cldata.name);
	TextOut(destdc,100,0,szBuf,lstrlen(szBuf));

	SelectObject(hdc,ClanInfo[ClanInfo_nNum].hClanMark );
	BitBlt(destdc,0,0,32,32,sorDC,0,0,SRCCOPY);
	TextOut(destdc,0,50,ClanInfo[ClanInfo_nNum].ClanInfoHeader.ClanReport,lstrlen(ClanInfo[ClanInfo_nNum].ClanInfoHeader.ClanReport));
	DeleteDC(destdc);
	DeleteDC(sorDC);
	ReleaseDC(g_hwnd,hdc);

#endif
	
	/*
	if(OpenFlag){
	if(ANSdata.ret_val == -1){
		DrawBox(BackStartPos.x,BackStartPos.y,3,3);		
		//Loading();
		}
	}
	*/

	switch(C_menuN) {
	case CLANSERVER_INSPECT:
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();						
		break;
	case CLAN_READ_CLANMARK:
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();				
		break;	
	case CLAN_isCheckClanJang_Result:
	case CLAN_isCheckClanJang:
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();				
		break;	
	case CLAN_MAKE_is:		//클랜결성의사 확인 Y/N

		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();				
		break;
	case CLANMAKE_NOMONEY:
	case CLAN_MONEY_is:		// 대금지불의사묻기

		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();

		break;
	case CLAN_NAME_is:		//클랜이름 설정.
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		break;
	case CLAN_NONAME:
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		break;
	case CLAN_NAME_BEING:
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		break;
	case CLAN_MARK_expl:		//클랜마크설명
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		
		break;
	case CLAN_INSPECTION_expl:		//심사기간설명
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		
		break;

	case CLANMAKE_REAMMAKR_ERROR:
	case CLAN_NotMake:	//클랜결성못하니 돌아가라
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		break;
	case CLANMAKE_DOWN_INFO:
	case CLANMAKE_READ_CLANMARK:
	case CLAN_MAKE_FINISH:
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		break;
	case CLAN_AllEnd:	//클랜 끝나고 클리어하는셋팅부분.
		break;


	case CLAN_ERROR:
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		break;


	//============칲용메뉴
	//case CLAN_CHIP_ReadDATA:		
	//	Draw_C_menuN();
	//	break;
	case CLAN_CHIP:
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		break;
		//ycy
		//========= 추방
	case CLAN_REMOVE:
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		break;
	case CLAN_REMOVE_SHORTCLANWON_RESULT:		
	case CLAN_REMOVE_RESULT:
	DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		break;
	case CLAN_REMOVE_SHORTCLANWON:
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		break;
	case CLAN_RELEASE:
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		break;
	case CLAN_RECONF_RELEASE:
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		break;
	case CLAN_FINISH_RELEASE:
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		break;
	case CLANCHIP_RELEASEMESSAGE:
	case CLAN_WAREHOUSE_RIGHT:
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		break;
	case CLAN_MARK1:
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		break;
	case CLAN_MARK2:
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		break;
	case CLAN_MARK3:
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		break;
	case CLAN_HELP:
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		break;
	case CLAN_HELP_CONTENT:
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		break;	

	case ISPFLAG_CHIP:
	case CLANCHIP_MAKE_FIRSTMESSAGE: 
	case CLANCHIP_DOWN6_CLANWON:    
	case CLANCHIP_DOWN6_CLANWON_MESSAGE:
	case CLAN_NOMAKE:
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		break;
	//=========칩 유저메뉴
	case CLANUSER_REMOVE ://클랜원이 추방당했을경우
	case	CLANUSER_AUTORELEASE://자동해체
	case CLAN_USER:
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		break;
	//클랜을 아직 결성 못함
	case CLAN_USER_NOMAKE:
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		break;
	case CLAN_SECESSION:
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		break;
	case CLAN_RECONF_SECESSION:
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		break;
	case CLAN_FINISH_SECESSION:
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		break;
	case CLANUSER_MAKE_FIRSTMESSAGE:			
	case CLANUSER_DOWN6_CLANWON_MESSAGE:
	case CLANUSER_DOWN6_CLANWON:			
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		break;

	//클랜칲이 가입권유할때 뜨는 메뉴
	case CLANUSER_JOIN:
	case CLAN_JOIN:
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		break;

	case CLAN_USER_WAREHOUSE:
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		break;
	case CLAN_USER_HELP:
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		break;
	case CLAN_USER_HELP_CONTENT:
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		break;	

	case CLAN_DISPLAY_END:
	case CLAN_DISPLAY_OPEN:		
	case CLAN_DISPLAY_CLOSE:
	case CLAN_CLOSE_ENDING:
	case CLAN_DISPLAY_INFO:
	case CHATLIST_READDATA:	
#ifdef USE_PROSTONTALE		//=========== 프리스턴소스인경우
		//cClanChatting.Draw();
#else
		cClanChatting.Draw();
#endif
		break;	


	case CLAN_DELETECHA_RELEASECLAN_BEFORE: 
	case CLAN_DELETECHA_RELEASECLAN:      
	case	CLAN_DELETECHA_SECESSION_BEFORE:	
	case	CLAN_DELETECHA_SECESSION:
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		cClanDeleteCha.Draw();
		break;
	case CLAN_REAMMAKR_ERROR:
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		break;
	case CLAN_RELEASE_LOADING:
	case CLAN_REMOVE_SHORTCLANWON_LOADING:
	case CLAN_REMOVE_LOADING:
	case CLAN_CHIP_ReadDATA:
	case CLAN_NPC_START:
	case CLAN_USER_ReadDATA:
	case ISPFLAG_USER:
	case CLANUSER_RELEASEMESSAGE:
	case CLANUSER_RELEASE_FLAG:
	case CLAN_RECONF_SECESSION_LOADING:
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		break;	
	
	}	

#ifndef USE_PROSTONTALE		//=========== 윈도함수
	window_renderFLIP();
#endif

	return TRUE;
}


//sw==0 : 일반 sw==1: 키입력을 받는경우 sw==2: 클랜이름을 타이틀에 쓸경우사용(그림자처리)
void CLAN_MENU::Draw_C_Text(char *str, int x, int y, int sw=0)
{
#ifdef USE_PROSTONTALE		//=========== 포리스턴소스인경우
	char strbuf[1024];

	HDC hdc;
	HFONT oldFont;
	lpDDSBack->GetDC(&hdc);
	SetBkMode( hdc, TRANSPARENT );

	if(hFont != NULL)
		oldFont = (HFONT)SelectObject( hdc , hFont );


	ZeroMemory(strbuf, sizeof(strbuf));

	int strL = strlen(str);
	int cnt=0;
	int i=0;

	while(1) {
		

		strbuf[i] = str[cnt];
		cnt++;
		if(strbuf[i] == '\n')  {
			strbuf[i] =0;
			i=0;
jmp1:


			
			if(sw==2){
				SetTextColor( hdc, RGB(100, 100, 100));	//그림자용 글자색
				//SetTextColor( hdc, RGB(255, 255,255));	//그림자용 글자색
				TextOut(hdc, x+1, y+1, strbuf, lstrlen(strbuf));

				SetTextColor( hdc, RGB(230, 255, 240));	//일반글자색
				TextOut(hdc, x, y, strbuf, lstrlen(strbuf));
			}
			else     {
				SetTextColor( hdc, RGB(230, 255, 240));	//일반글자색
				TextOut(hdc, x, y, strbuf, lstrlen(strbuf));
			}
			
			/*
			if(sw==2){
				SetTextColor( hdc, RGB(255, 255, 255));	//클랜이름입력시 흰색				
			}
			else {
				SetTextColor( hdc, RGB(230, 255, 240));	//일반글자색
			}
			TextOut(hdc, x, y, strbuf, lstrlen(strbuf));
			*/
			

			ZeroMemory(strbuf, sizeof(strbuf));
			y+=16;

			if(cnt>=strL) break;
		}
		else if(cnt>=strL)
		{
			goto jmp1;
		}
		else {
			i++;
		}
	}
	

	if(sw==1) 
	{
		static cnt=0;
		cnt++;
		if(cnt<20) {
			SetTextColor( hdc, RGB(255, 255, 255));
			TextOut(hdc, x + (lstrlen(str)*6) , y-16, "|", 1);
		}
		if(cnt>=40) cnt=0;
	}

	if(oldFont)
		SelectObject( hdc, oldFont);
	lpDDSBack->ReleaseDC(hdc);
#else

#endif
}






//ycy : 박스 그리기
int CLAN_MENU::DrawBox(int x,int y,int x_width,int y_height)
{

	isDrawClanMenu = 1;


#ifdef USE_PROSTONTALE		//=========== 포리스턴소스인경우

	#define BOXFONTSIZE 64

	if(lpD3DDevice == NULL)
		return FALSE;

	lpD3DDevice->BeginScene();


	//뒷배경찍기
	//dsDrawColorBox( RGBA_MAKE(0,15,128,125), x+32, y+32, 	(x_width+1)*64, 	(y_height+1)*64);
	//dsDrawColorBox( RGBA_MAKE(0,20,10,125), x+32, y+32, 	((x_width+1)*64)+1, 	((y_height+1)*64)+1);
	
	sinDrawTexImage( hBox5, (float)x+64, (float)y+32, (float)( 64+(  ( x_width-2) *32) ), (float)(   32+(  (y_height-1) *32) ),
				0,0,
				0, 0, 32, 32, 
				255);
	//DrawSprite(x  ,y , hBox1_ktj ,  0, 0, 32, 32, 1);
	//int sinDrawTexImage( int Mat, float x, float y, float w, float h, 
	//						float surW, float surH, 
	//						float tLeft, float tTop, float tRight, float tBottom, 
	//						int Transp);
	//left, top
	sinDrawTexImage( hBox1,(float) x,(float) y, (float)64, (float)32,    
				(float)0,(float)0,  
				(float)0, (float)0, (float)64, (float)32,
				255);
	//right, top
	sinDrawTexImage( hBox3,(float)(   x+(32*x_width) +64 ), (float)y, 64, 32,    
				(float)0,(float)0,  
				(float)0, (float)0, (float)64, (float)32,
				255);	
	//left, bottom
	sinDrawTexImage( hBox7, (float)x, (float)(  y+(32*y_height) + 32 ), 64, 64 ,
				(float)0,(float)0,  
				(float)0, (float)0, (float)64, (float)32,
				255);
	//right, top
	sinDrawTexImage( hBox9,(float)(   x+(32*x_width) +64 ), (float)(  y+(32*y_height) + 32  ), 64, 64,    
				(float)0,(float)0,  
				(float)0, (float)0, (float)64, (float)32,
				255);
				
	int line;
	int sx = x+64;
	int ey=  y+(32*y_height) + 32 ;
	for(line=0; line<x_width; line++) {
		//위쪽 라인
		sinDrawTexImage( hBox2, (float) sx, (float)y, 32, 32,
				(float)0,(float)0,  
				(float)0, (float)0, (float)32, (float)32,
				255);
		
		//아래쪽 라인
		sinDrawTexImage( hBox8, (float)sx, (float)( ey ), 32, 64,
				0,0,
				0, 0, 32, 64,
				255);
				
		sx+=32;
	}

	int sy = y+32;
	int ex = x+(32*x_width) + 64 ;
	for(line=0; line<y_height; line++) {
		//오른쪽라인
		sinDrawTexImage( hBox4, (float)x, (float)sy, 64, 32,
				0,0,
				0, 0, 64, 32,
				255);
		//왼쪽 라인
		sinDrawTexImage( hBox6,(float)ex, (float)sy, 64, 32,
				0,0,
				0, 0, 64, 32,
				255);
		sy+=32;
	}
	
	





	lpD3DDevice->EndScene();

	//DrawSprite(x+128,y+6, hClanTitle ,  0, 0, 139, 32, 0);
	//DrawSprite(x+ ( ((x_width*64)/2))-2 , y-2, hClanTitle ,  0, 0, 139, 32, 1);
	//DrawSprite(x + 90 ,y -10, hClanTitle ,  0, 0, 139, 32, 1);


#else



	//HBITMAP backu_BMP;
	//HDC backu_dc;



	
	BITMAP bit;
	int bx,by;
	int i;
	int nTotal_Width = 0;
	int nTotal_Height = 0;
	//int nStart_x;
	





	HDC hdc=GetDC(g_hwnd);

	HDC sorDC =CreateCompatibleDC(hdc);
	HDC destdc=CreateCompatibleDC(hdc);

	SelectObject(destdc, Dback.hb );		//off스크린설정.
	//SelectObject(sorDC, backBMP );

	/*
	for(int i=0; i<coordNum; i++) {

		BitBlt(
			destDC,
			coordB[i].left,coordB[i].top,
			//주의 : 길이임.
			coordB[i].right, coordB[i].bottom,	//offscr을 윈도창으로 카피
			sorDC,
			coordB[i].left,coordB[i].top,
			SRCCOPY);

	}

	
	*/


	//왼쪽 top
	SelectObject(sorDC, hBox1);
	GetObject(hBox1,sizeof(BITMAP),&bit);
	bx = bit.bmWidth;
	nTotal_Width+=bx;
	by = bit.bmHeight;	
	BitBlt(destdc,x,y,bx,by,sorDC,0,0,SRCCOPY);

	for(i=0; i< x_width; i++)
	{
		SelectObject(sorDC,hBox2);
		GetObject(hBox2,sizeof(BITMAP),&bit);	
		bx = bit.bmWidth;
		nTotal_Width +=bx;
		by = bit.bmHeight;
		StretchBlt(destdc,x+BOXCORNER_WIDTH+(bx*i),y,bx,by,sorDC,0,0,bx,by,SRCCOPY);
	}

	//오른쪽 top

	SelectObject(sorDC, hBox3 );
	GetObject(hBox3,sizeof(BITMAP),&bit);	
	bx = bit.bmWidth;
	by = bit.bmHeight;	
	StretchBlt(destdc,x+nTotal_Width,y,bx,by,sorDC,0,0,bx,by,SRCCOPY);


    //왼쪽 테두리

	for(i=0; i< y_height; i++)
	{
		SelectObject(sorDC, hBox4 );
		GetObject(hBox4,sizeof(BITMAP),&bit);	
		bx = bit.bmWidth;
		by = bit.bmHeight;
		nTotal_Height +=by ;
		StretchBlt(destdc,x,y+BOXCORNER_HEIGHT+(by*i),bx,by,sorDC,0,0,bx,by,SRCCOPY);
	}



	
	
	//왼쪽 BOTTOM 	
	SelectObject(sorDC,hBox7);
	GetObject(hBox7,sizeof(BITMAP),&bit);	
	bx = bit.bmWidth;
	by = bit.bmHeight;
		
	StretchBlt(destdc,x,y +BOXCORNER_HEIGHT+nTotal_Height,bx,by,sorDC,0,0,bx,by,SRCCOPY);

	for(i=0; i< x_width; i++)
	{
		SelectObject(sorDC,hBox8);
		GetObject(hBox8,sizeof(BITMAP),&bit);	
		bx = bit.bmWidth;		
		by = bit.bmHeight;
		StretchBlt(destdc,x+BOXCORNER_WIDTH+(bx*i),y +BOXCORNER_HEIGHT+nTotal_Height,bx,by,sorDC,0,0,bx,by,SRCCOPY);
	}	

	//오른쪽 BOTTOM
	SelectObject(sorDC,hBox9);
	GetObject(hBox9,sizeof(BITMAP),&bit);	
	bx = bit.bmWidth;
	by = bit.bmHeight;	
	StretchBlt(destdc,x+nTotal_Width,y +BOXCORNER_HEIGHT+nTotal_Height,bx,by,sorDC,0,0,bx,by,SRCCOPY);	

 
	//오른쪽 테두리
	for(i=0; i< y_height; i++)
	{
		SelectObject(sorDC, hBox6 );
		GetObject(hBox6,sizeof(BITMAP),&bit);	
		bx = bit.bmWidth;
		by = bit.bmHeight;		
		StretchBlt(destdc,x+nTotal_Width,y+BOXCORNER_HEIGHT+(by*i),bx,by,sorDC,0,0,bx,by,SRCCOPY);
	}


	DeleteDC(sorDC);
	DeleteDC(destdc);

	ReleaseDC(g_hwnd, hdc);


#endif

	return TRUE;
}

void CLAN_MENU::RenderMenu()
{
	/*
	HDC hdc,sorDC;
	HBITMAP oldbmp;

	hdc = GetDC(g_hwnd);
	sorDC  = CreateCompatibleDC(hdc );
	oldbmp = (HBITMAP)SelectObject(sorDC,membmp->membmp);
	BitBlt(hdc,0,0,800,600,sorDC,0,0,SRCCOPY);
	SelectObject(sorDC,oldbmp);	
	DeleteDC(sorDC);
	ReleaseDC(g_hwnd,hdc);
	*/
}
/*///////////////////////////////////////////////////////////////////////////
: 클라스 명: class CLAN_MENU
: 하 는 일 : 
: 서    식 :
: 인    자 :
: 반 환 값 :
: 논    평 : 웹db를 사용해 데이타를 뽑아내야 할경우 본 클라스를 이용한다.
: 버    전 :
: PROJECT  :
///////////////////////////////////////////////////////////////////////////*/
void CLAN_MENU::Draw_C_menuN()
{		
	cBaseMenu.Draw();
	cClanChip.Draw();	
	cClanUser.Draw();	
	cClanMake.Draw();	
	cClanReport.Draw();
#ifdef USE_PROSTONTALE		//=========== 포리스턴소스인경우
#else
	cClanChatting.Draw();
#endif
	cClanJoin.Draw();
}


//=============드로우 관련 함수 ==================================================================end







/*///////////////////////////////////////////////////////////////////////////
: 클라스 명: 계정에 만들어진 캐릭터들이 가입한 클랜을 알기 위해서
: 하 는 일 : 
: 반 환 값 :
///////////////////////////////////////////////////////////////////////////*/
//유저 id, 캐릭터 id, 군서버 이름.
void SetUserData2(char* id, char* chaname, char* gserver)
{
	strcpy(cldata.szID,  id);
	strcpy(cldata.ChaName, chaname);
	strcpy(cldata.gserver, gserver);
	
}

/*///////////////////////////////////////////////////////////////////////////
: 클라스 명: 클랜 스트럭처 데이타 셋팅 함수들
: 하 는 일 : 
: 반 환 값 :
///////////////////////////////////////////////////////////////////////////*/
//유저 id, 캐릭터 id, 군서버 이름.
void CLAN_MENU::SetUserData(char* id, char* chaname, char* gserver,int money, int ability)
{
	strcpy(cldata.szID,  id);
	strcpy(cldata.ChaName, chaname);
	strcpy(cldata.gserver, gserver);

	cldata.money = money;
	//ktj : 임시
	//if(cldata.money ==0) cldata.money = 100000;
	cldata.ability = ability;
}



//권유를 받는 사람한테오는 데이타
void CLAN_MENU::SetJoinData(char *joinclanname, char *joinclanchip)
{
	strcpy(cldata.szJoinClanName,    joinclanname);			//가입될 클랜 이름
	strcpy(cldata.szJoinClanChipName,joinclanchip);		//가입될 클랜의 클랜장 id
}











#ifdef USE_PROSTONTALE		//=========== 포리스턴소스인경우

void DrawSprite_TJB(int winX ,int winY, int winxlen, int winylen, LPDIRECTDRAWSURFACE4 pdds,int x, int y, int width, int height,int Bltflag)
{
	if(!pdds) return;

	//int dx,dy,sx,sy,px,py;
    RECT rcRect;
	RECT dRect;

	dRect.left = winX;
	dRect.right = winX+winxlen;
	dRect.top = winY;
	dRect.bottom = winY+winylen;

	rcRect.top		= 0;
	rcRect.left		= 0;
	rcRect.bottom   = 32;
	rcRect.right    = 32;

//if(Bltflag)
	//{
		//ddrval=lpDDSPrimary->Blt(&destRect,lpDDSBack,&rcRect,NULL,NULL);

		//lpDDSBack->BltFast(winX+px,winY+py,pdds,&rcRect,DDBLTFAST_WAIT|DDBLTFAST_SRCCOLORKEY);

		lpDDSBack->Blt(&dRect,
					pdds,
					&rcRect,
					DDBLTFAST_WAIT|DDBLTFAST_SRCCOLORKEY,
					NULL);
/*
	}
	else
		//lpDDSBack->BltFast( winX,winY, pdds, &rcRect,DDBLTFAST_WAIT);
		lpDDSBack->BltFast( winX,winY, pdds, &rcRect,DDBLTFAST_WAIT);
		*/

}
#endif




#ifdef USE_PROSTONTALE		//=========== 포리스턴소스인경우
#else

void Draw_Text(int x, int y,char *str)
{
	HANDLE hFont,hOldFont;
	HDC hdc;	
	hdc = GetDC(g_hwnd);
    	hFont = CreateFont( 12,
                        0,
                        0,
                        0,
						FW_NORMAL,
                        FALSE,
                        FALSE,
                        FALSE,
                        HANGEUL_CHARSET,
                        OUT_DEFAULT_PRECIS,
                        CLIP_DEFAULT_PRECIS,
                        DEFAULT_QUALITY,
                        VARIABLE_PITCH,
                        "굴림체" );

	hOldFont = SelectObject(hdc,hFont);
	char strbuf[1024];


	ZeroMemory(strbuf, sizeof(strbuf));

	int strL = strlen(str);
	int cnt=0;
	int i=0;
	
	while(1)
	{
		strbuf[i] = str[cnt];
		cnt++;
		if(strbuf[i] == '\n')  {
			strbuf[i] =0;
			i=0;
jmp1:		
			
			TextOut(hdc, x, y, strbuf, lstrlen(strbuf));

			ZeroMemory(strbuf, sizeof(strbuf));
			y+=16;

			if(cnt>=strL) break;
		}
		else if(cnt>=strL)
		{
			goto jmp1;
		}
		else {
			i++;
		}
	}
	
	//DrawText(GetDC(g_hwnd),string,-1,&rect,DT_LEFT | DT_WORDBREAK);

	SelectObject(hdc,hOldFont);
	DeleteObject(hFont);

	ReleaseDC(g_hwnd,hdc);
	
}
#endif



void Text_Out1(HDC hdc,int x, int y,char *str)
{
}

void Text_Out2(HDC hdc,int x, int y,char *str)
{
}

void Text_Out3(HDC hdc,int x, int y,char *str)
{
}
void Text_Out(HDC hdc,int x, int y,char *str)
{
	HANDLE hFont,hOldFont;

	
    	hFont = CreateFont( 12,
                        0,
                        0,
                        0,
						FW_NORMAL,
                        FALSE,
                        FALSE,
                        FALSE,
                        HANGEUL_CHARSET,
                        OUT_DEFAULT_PRECIS,
                        CLIP_DEFAULT_PRECIS,
                        DEFAULT_QUALITY,
                        VARIABLE_PITCH,
                        "굴림체" );

	hOldFont = SelectObject(hdc,hFont);
	char strbuf[1024];


	ZeroMemory(strbuf, sizeof(strbuf));

	int strL = strlen(str);
	int cnt=0;
	int i=0;
	
	while(1)
	{
		strbuf[i] = str[cnt];
		cnt++;
		if(strbuf[i] == '\n')  {
			strbuf[i] =0;
			i=0;
jmp1:		
			
			TextOut(hdc, x, y, strbuf, lstrlen(strbuf));

			ZeroMemory(strbuf, sizeof(strbuf));
			y+=16;

			if(cnt>=strL) break;
		}
		else if(cnt>=strL)
		{
			goto jmp1;
		}
		else {
			i++;
		}
	}
	
	//DrawText(GetDC(g_hwnd),string,-1,&rect,DT_LEFT | DT_WORDBREAK);

	SelectObject(hdc,hOldFont);
	DeleteObject(hFont);
	
	
}



void CLAN_MENU::Load()
{
#ifdef USE_PROSTONTALE		//=========== 포리스턴소스인경우

	MatPartyBackGround =
		CreateTextureMaterial( "image\\Sinimage\\Help\\party_win.tga" , 0, 0, 0,0, SMMAT_BLEND_ALPHA );
	

	//box===========================================================================start

	hBox1 = 
		CreateTextureMaterial( "image\\Sinimage\\Help\\HelpBoxCorner.tga",  0, 0, 0,0, SMMAT_BLEND_ALPHA );

	hBox2 = 
		CreateTextureMaterial( "image\\Sinimage\\Help\\HelpBoxLine.tga",  0, 0, 0,0, SMMAT_BLEND_ALPHA );

	hBox3 = 
		CreateTextureMaterial( "image\\Sinimage\\Help\\box3.tga",  0, 0, 0,0, SMMAT_BLEND_ALPHA );

	hBox4 = 
		CreateTextureMaterial( "image\\Sinimage\\Help\\box4.tga",  0, 0, 0,0, SMMAT_BLEND_ALPHA );
	hBox5 = 
		CreateTextureMaterial( "image\\Sinimage\\Help\\box5.tga",  0, 0, 0,0, SMMAT_BLEND_ALPHA );

	hBox6 = 
		CreateTextureMaterial( "image\\Sinimage\\Help\\box6.tga",  0, 0, 0,0, SMMAT_BLEND_ALPHA );

	hBox7 = 
		CreateTextureMaterial( "image\\Sinimage\\Help\\box7.tga",  0, 0, 0,0, SMMAT_BLEND_ALPHA );

	hBox8 = 
		CreateTextureMaterial( "image\\Sinimage\\Help\\box8.tga",  0, 0, 0,0, SMMAT_BLEND_ALPHA );

	hBox9 = 
		CreateTextureMaterial( "image\\Sinimage\\Help\\box9.tga",  0, 0, 0,0, SMMAT_BLEND_ALPHA );

	//box===========================================================================end


	/*
	//ktj : scroll
	hScl_Bar_tj= CreateTextureMaterial( "image\\Sinimage\\Help\\scl_bar.tga", 0, 0, 0,0, SMMAT_BLEND_ALPHA );
	hScl_icon_tj = CreateTextureMaterial( "image\\Sinimage\\Help\\scl_icon.tga", 0, 0, 0,0, SMMAT_BLEND_ALPHA );

	hOk_Gray  = LoadDibSurfaceOffscreen("image\\Sinimage\\MessageBox\\Button_Ok_Glay.bmp");
	hOk_Yellow= LoadDibSurfaceOffscreen("image\\Sinimage\\MessageBox\\Button_Ok_Yellow.bmp");
	//hCancel_Gray = LoadDibSurfaceOffscreen("image\\Sinimage\\MessageBox\\Button_Cancel_Glay.bmp");
	//hCancel_Yellow = LoadDibSurfaceOffscreen("image\\Sinimage\\MessageBox\\Button_Cancel_Yellow.bmp");
	hYes_Gray = LoadDibSurfaceOffscreen("image\\Sinimage\\MessageBox\\Button_Yes_Glay.bmp");
	hYes_Yellow = LoadDibSurfaceOffscreen("image\\Sinimage\\MessageBox\\Button_Yes_Yellow.bmp");
	//hNo_Gray = LoadDibSurfaceOffscreen("image\\Sinimage\\MessageBox\\Button_No_Glay.bmp");
	//hNo_Yellow =  LoadDibSurfaceOffscreen("image\\Sinimage\\MessageBox\\Button_No_Yellow.bmp");

	//CLAN CHIP
	//hMark = LoadDibSurfaceOffscreen("image\\Sinimage\\chipbutton\\Mark.bmp");
	hClanName = LoadDibSurfaceOffscreen("image\\Sinimage\\Help\\box-test-title.bmp");
	hWareHouse[0]= LoadDibSurfaceOffscreen("image\\clanImage\\chipbutton\\whc.bmp");
	hWareHouse[1] = LoadDibSurfaceOffscreen("image\\clanImage\\chipbutton\\whc1.bmp");
	hWHRight[0] = LoadDibSurfaceOffscreen("image\\clanImage\\chipbutton\\whr.bmp");
	hWHRight[1] = LoadDibSurfaceOffscreen("image\\clanImage\\chipbutton\\whr1.bmp");
	//hClanMark[0] = LoadDibSurfaceOffscreen("image\\clanImage\\chipbutton\\m.bmp");
	hClanMark[1] = LoadDibSurfaceOffscreen("image\\clanImage\\chipbutton\\m1.bmp");
	hRemove[0] = LoadDibSurfaceOffscreen("image\\clanImage\\chipbutton\\r.bmp");
	hRemove[1] = LoadDibSurfaceOffscreen("image\\clanImage\\chipbutton\\r1.bmp");
	hClanRelease[0] = LoadDibSurfaceOffscreen("image\\clanImage\\chipbutton\\cr.bmp");
	hClanRelease[1] = LoadDibSurfaceOffscreen("image\\clanImage\\chipbutton\\cr1.bmp");
	hHelp[0] = LoadDibSurfaceOffscreen("image\\clanImage\\chipbutton\\h.bmp");
	hHelp[1] = LoadDibSurfaceOffscreen("image\\clanImage\\chipbutton\\h1.bmp");
	hOut[0] = LoadDibSurfaceOffscreen("image\\clanImage\\MessageBox\\o.bmp");
	hOut[1] = LoadDibSurfaceOffscreen("image\\clanImage\\MessageBox\\o1.bmp");
	//클랜 구성원
	hSecession[0] = LoadDibSurfaceOffscreen("image\\clanImage\\chipbutton\\s.bmp");
	hSecession[1] = LoadDibSurfaceOffscreen("image\\clanImage\\chipbutton\\s1.bmp");
	//추방,창고 권한
	hIcon = LoadDibSurfaceOffscreen("image\\party\\party_man_0.bmp");
	hIcon_Click = LoadDibSurfaceOffscreen("image\\party\\party_man_1.bmp");

										
	hClose[0] = LoadDibSurfaceOffscreen("image\\clanImage\\MessageBox\\c.bmp");
	hClose[1] = LoadDibSurfaceOffscreen("image\\clanImage\\MessageBox\\c1.bmp");
	//헬프
	hHelp1 = LoadDibSurfaceOffscreen("image\\Sinimage\\chipbutton\\help1.bmp");


	//hButton_Box = LoadDibSurfaceOffscreen("image\\Sinimage\\Help\\box-test-title2.bmp");
	hClanTitle = LoadDibSurfaceOffscreen("image\\clanImage\\chipbutton\\title.bmp");



	//추방메뉴안에서 추방 버튼
	hRemoveToMenu[0]= LoadDibSurfaceOffscreen("image\\clanImage\\MessageBox\\Button_deport_Glay.bmp");
	hRemoveToMenu[1] = LoadDibSurfaceOffscreen("image\\clanImage\\MessageBox\\Button_deport_Yellow.bmp");

	//스크롤바
	hScl_Bar= LoadDibSurfaceOffscreen("image\\clanImage\\chipbutton\\scl_bar.bmp");
	hScl_icon = LoadDibSurfaceOffscreen("image\\clanImage\\chipbutton\\msBox.bmp");
	
	hClanNameInput = LoadDibSurfaceOffscreen("image\\clanImage\\chipbutton\\clan_name.bmp");

	//====클랜 버턴설명 부분
	hTxt_Remove[0] = LoadDibSurfaceOffscreen("image\\clanImage\\chipbutton\\txt_r_.bmp");

	hTxt_Remove[1] = LoadDibSurfaceOffscreen("image\\clanImage\\chipbutton\\txt_r.bmp");

	hTxt_Release[0] = LoadDibSurfaceOffscreen("image\\clanImage\\chipbutton\\txt_cr_.bmp");

	hTxt_Release[1] = LoadDibSurfaceOffscreen("image\\clanImage\\chipbutton\\txt_cr.bmp");

	hTxt_Mark[0] = LoadDibSurfaceOffscreen("image\\clanImage\\chipbutton\\txt_m_.bmp");

	hTxt_Mark[1] = LoadDibSurfaceOffscreen("image\\clanImage\\chipbutton\\txt_m.bmp");

	hTxt_Help[0] = LoadDibSurfaceOffscreen("image\\clanImage\\chipbutton\\txt_h_.bmp");

	hTxt_Help[1] = LoadDibSurfaceOffscreen("image\\clanImage\\chipbutton\\txt_h.bmp");

	hTxt_Secession[0] = LoadDibSurfaceOffscreen("image\\clanImage\\chipbutton\\txt_out_.bmp");

	hTxt_Secession[1] = LoadDibSurfaceOffscreen("image\\clanImage\\chipbutton\\txt_out.bmp");

	*/

#else
	

	MatPartyBackGround = (HBITMAP)LoadImage(
					NULL, 
					"image\\Sinimage\\Help\\box-test-title2.bmp",
					IMAGE_BITMAP,
					0,0,
					LR_LOADFROMFILE);

//box===========================================================================start

	hBox1= (HBITMAP)LoadImage(NULL,"image\\clanimage\\MessageBox\\box1.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);

	hBox2= (HBITMAP)LoadImage(NULL,"image\\clanimage\\MessageBox\\box2.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);
	hBox3= (HBITMAP)LoadImage(NULL,"image\\clanimage\\MessageBox\\box3.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);
	hBox4= (HBITMAP)LoadImage(NULL,"image\\clanimage\\MessageBox\\box4.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);

	hBox6= (HBITMAP)LoadImage(NULL,"image\\clanimage\\MessageBox\\box6.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);
	hBox7= (HBITMAP)LoadImage(NULL,"image\\clanimage\\MessageBox\\box7.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);

	hBox8= (HBITMAP)LoadImage(NULL,"image\\clanimage\\MessageBox\\box8.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);
	hBox9= (HBITMAP)LoadImage(NULL,"image\\clanimage\\MessageBox\\box9.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);
	
	
	//box===========================================================================end



	hOk_Gray= (HBITMAP)LoadImage(NULL,"image\\Sinimage\\MessageBox\\Button_Ok_Glay.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);	

	hOk_Yellow = (HBITMAP)LoadImage(NULL,"image\\Sinimage\\MessageBox\\Button_Ok_Yellow.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);


	if(hOk_Yellow == NULL)
	{
		char temp[50];
		wsprintf(temp,"Num : %d",GetLastError());
	}

	hCancel_Gray = (HBITMAP)LoadImage(NULL,"image\\Sinimage\\MessageBox\\Button_Cancel_Glay.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);

	hCancel_Yellow = (HBITMAP)LoadImage(NULL,"image\\Sinimage\\MessageBox\\Button_Cancel_Yellow.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);
	hYes_Gray = (HBITMAP)LoadImage(NULL,"image\\Sinimage\\MessageBox\\Button_Yes_Glay.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);
	hYes_Yellow = (HBITMAP)LoadImage(NULL,"image\\Sinimage\\MessageBox\\Button_Yes_Yellow.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);

	hNo_Gray = (HBITMAP)LoadImage(NULL,"image\\Sinimage\\MessageBox\\Button_No_Glay.bmp",
						IMAGE_BITMAP,	
						0,0,
						LR_LOADFROMFILE);

	hNo_Yellow =  (HBITMAP)LoadImage(NULL,"image\\Sinimage\\MessageBox\\Button_No_Yellow.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);




	//CLAN CHIP
	//hMark = (HBITMAP)LoadImage(NULL,"image\\Sinimage\\chipbutton\\Mark.bmp",
	//					IMAGE_BITMAP,
	//					0,0,
	//					LR_LOADFROMFILE);
	hClanName = (HBITMAP)LoadImage(NULL,"image\\Sinimage\\Help\\box-test-title.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);
	hWareHouse[0]= (HBITMAP)LoadImage(NULL,"image\\clanImage\\chipbutton\\whc.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);
	hWareHouse[1] = (HBITMAP)LoadImage(NULL,"image\\clanImage\\chipbutton\\whc1.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);
	hWHRight[0] = (HBITMAP)LoadImage(NULL,"image\\clanImage\\chipbutton\\whr.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);
	hWHRight[1] = (HBITMAP)LoadImage(NULL,"image\\clanImage\\chipbutton\\whr1.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);
	hClanMark[0] = (HBITMAP)LoadImage(NULL,"image\\clanImage\\chipbutton\\m.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);
	hClanMark[1] = (HBITMAP)LoadImage(NULL,"image\\clanImage\\chipbutton\\m1.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);
	hRemove[0] = (HBITMAP)LoadImage(NULL,"image\\clanImage\\chipbutton\\r.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);
	hRemove[1] = (HBITMAP)LoadImage(NULL,"image\\clanImage\\chipbutton\\r1.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);
	hClanRelease[0] = (HBITMAP)LoadImage(NULL,"image\\clanImage\\chipbutton\\cr.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);
	hClanRelease[1] = (HBITMAP)LoadImage(NULL,"image\\clanImage\\chipbutton\\cr1.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);
	hHelp[0] = (HBITMAP)LoadImage(NULL,"image\\clanImage\\chipbutton\\h.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);
	hHelp[1] = (HBITMAP)LoadImage(NULL,"image\\clanImage\\chipbutton\\h1.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);
	hOut[0] = (HBITMAP)LoadImage(NULL,"image\\clanImage\\MessageBox\\o.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);
	hOut[1] = (HBITMAP)LoadImage(NULL,"image\\clanImage\\MessageBox\\o1.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);

	//클랜 구성원
	hSecession[0] = (HBITMAP)LoadImage(NULL,"image\\clanImage\\chipbutton\\s.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);

	hSecession[1] = (HBITMAP)LoadImage(NULL,"image\\clanImage\\chipbutton\\s1.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);
//추방,창고 권한
	hIcon = (HBITMAP)LoadImage(NULL,"image\\party\\party_man_0.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);
	hIcon_Click = (HBITMAP)LoadImage(NULL,"image\\party\\party_man_1.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);
//추방메뉴안에서 추방 버튼
	hRemoveToMenu[0]= (HBITMAP)LoadImage(NULL,"image\\clanImage\\MessageBox\\Button_deport_Glay.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);

	hRemoveToMenu[1] = (HBITMAP)LoadImage(NULL,"image\\clanImage\\MessageBox\\Button_deport_Yellow.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);

	hClose[0] = (HBITMAP)LoadImage(NULL,"image\\clanImage\\MessageBox\\c.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);

	hClose[1] = (HBITMAP)LoadImage(NULL,"image\\clanImage\\MessageBox\\c1.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);
	//헬프
	hHelp1 = (HBITMAP)LoadImage(NULL,"image\\Sinimage\\chipbutton\\help1.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);

	hButton_Box = (HBITMAP)LoadImage(NULL,"image\\clanImage\\chipbutton\\msBox.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);
	hClanTitle = (HBITMAP)LoadImage(NULL,"image\\clanImage\\chipbutton\\title.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);
	hScl_Bar = (HBITMAP)LoadImage(NULL,"image\\clanImage\\chipbutton\\scl_bar.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);
	hScl_icon = (HBITMAP)LoadImage(NULL,"image\\Sinimage\\help\\scl_icon.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);
	//====클랜 버턴설명 부분
	hTxt_Remove[0] = (HBITMAP)LoadImage(NULL,"image\\clanImage\\chipbutton\\txt_r_.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);

	hTxt_Remove[1] = (HBITMAP)LoadImage(NULL,"image\\clanImage\\chipbutton\\txt_r.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);

	hTxt_Release[0] = (HBITMAP)LoadImage(NULL,"image\\clanImage\\chipbutton\\txt_cr_.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);

	hTxt_Release[1] = (HBITMAP)LoadImage(NULL,"image\\clanImage\\chipbutton\\txt_cr.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);

	hTxt_Mark[0] = (HBITMAP)LoadImage(NULL,"image\\clanImage\\chipbutton\\txt_m_.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);

	hTxt_Mark[1] = (HBITMAP)LoadImage(NULL,"image\\clanImage\\chipbutton\\txt_m.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);

	hTxt_Help[0] = (HBITMAP)LoadImage(NULL,"image\\clanImage\\chipbutton\\txt_h_.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);

	hTxt_Help[1] = (HBITMAP)LoadImage(NULL,"image\\clanImage\\chipbutton\\txt_h.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);

	hTxt_Secession[0] = (HBITMAP)LoadImage(NULL,"image\\clanImage\\chipbutton\\txt_out_.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);

	hTxt_Secession[1] = (HBITMAP)LoadImage(NULL,"image\\clanImage\\chipbutton\\txt_out.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);

	


	
	

#endif
}



//simMain.cpp에서 불러서 클로즈 한다.
void clanMENU_close()
{
	Interface_clanmenu.Close();
}

void CLAN_MENU::Close()
{
	#ifdef USE_PROSTONTALE		//=========== 포리스턴소스인경우

	/*if(	hOk_Gray ) {   hOk_Gray->Release();  hOk_Gray = NULL;}
	if(	hOk_Yellow ) {   hOk_Yellow->Release();  hOk_Yellow= NULL;}
	if(	hCancel_Gray ) {   hCancel_Gray->Release();  hCancel_Gray= NULL;}
	if(	hCancel_Yellow) {   hCancel_Yellow->Release();  hCancel_Yellow= NULL;}
	if(	hYes_Gray ) {   hYes_Gray->Release();  hYes_Gray = NULL;}
	if(	hYes_Yellow ) {   hYes_Yellow->Release();  hYes_Yellow = NULL;}
	if(	hNo_Gray ) {   hNo_Gray->Release();  hNo_Gray = NULL;}
	if(	hNo_Yellow ) {   hNo_Yellow ->Release();  hNo_Yellow = NULL;}

	//CLAN CHIP
	if(	hMark ) {   hMark->Release();  hMark = NULL;}
	if(	hClanName ) {   hClanName->Release();  hClanName = NULL;}
	


	for(int i=0 ; i <2; i++)
	{
		if(hWHRight[i]) { hWHRight[i]->Release(); hWHRight[i]= NULL; } 
		if(hWareHouse[i]) { hWareHouse[i]->Release(); hWareHouse[i] = NULL;}
		if(hClanMark[i]) { hClanMark[i]->Release(); hClanMark[i] = NULL;}
		if(hRemove[i]) { hRemove[i]->Release(); hRemove[i] = NULL;}
		if(hClanRelease[i]) { hClanRelease[i]->Release(); hClanRelease[i] = NULL;}
		if(hHelp[i]) { hHelp[i]->Release(); hHelp[i] = NULL;}	
		if(hOut[i]) { hOut[i]->Release(); hOut[i] = NULL;}	
		if(hClose[i]) { hClose[i]->Release(); hClose[i] = NULL;}	
		if(hSecession[i]) { hSecession[i]->Release(); hSecession[i] = NULL;}	
		if(hTxt_Remove[i]) { hTxt_Remove[i]->Release(); hTxt_Remove[i] = NULL;}	
		if(hTxt_Release[i]) { hTxt_Release[i]->Release(); hTxt_Release[i] = NULL;}	
		if(hTxt_Mark[i]) { hTxt_Mark[i]->Release(); hTxt_Mark[i] = NULL;}	
		if(hTxt_Help[i]) { hTxt_Help[i]->Release(); hTxt_Help[i] = NULL;}	
		if(hTxt_Secession[i]) { hTxt_Secession[i]->Release(); hTxt_Secession[i] = NULL;}
		
		
	}

	//추방
	if(	hIcon ) {   hIcon->Release();  hIcon = NULL;}
	//헬프
	if(	hHelp1 ) {   hHelp1->Release();  hHelp1 = NULL;}

	if(	hButton_Box) {   hClanTitle ->Release();  hClanTitle = NULL;}
	if(	hClanTitle ) {   hClanTitle ->Release();  hClanTitle = NULL;}


	//ygy 스크롤
	if(	hScl_Bar) {   hScl_Bar->Release();  hScl_Bar = NULL;}
	if(	hScl_icon ) {   hScl_icon->Release();  hScl_icon = NULL;}

	//ygy클랜이름 입력 이미지
	if(	hClanNameInput ) {   hClanNameInput->Release();  hClanNameInput = NULL;}*/
	


	if(cldata.hClanMark) { cldata.hClanMark->Release(); cldata.hClanMark = NULL;}
	if(cldata.hClanMark16) {cldata.hClanMark16->Release(); cldata.hClanMark16 = NULL;}

	cClanChatting.Close();
	cBaseMenu.Close();


	#else

	//bitmap없앨것.
	DeleteObject( MatPartyBackGround );
//	DeleteObject(hBoxCorner);
//	DeleteObject(hBoxLine);
	//DeleteObject(hBoxLine1);
	DeleteObject(hOk_Gray);
	DeleteObject(hOk_Yellow);
	DeleteObject(hCancel_Gray);
	DeleteObject(hCancel_Yellow);
	DeleteObject(hYes_Yellow);
	DeleteObject(hYes_Gray);
	DeleteObject(hNo_Gray);
	DeleteObject(hNo_Yellow);
	DeleteObject(hMark);
	DeleteObject(hClanName);
	DeleteObject(hScl_Bar);
	DeleteObject(hScl_icon);


	for(int i=0 ; i <2; i++)
	{
		DeleteObject(hWHRight[i]);
		DeleteObject(hWareHouse[i]);
		DeleteObject(hClanMark[i]);
		DeleteObject(hRemove[i]);
		DeleteObject(hClanRelease[i]);
		DeleteObject(hHelp[i]);
		DeleteObject(hOut[i]);
		DeleteObject(hClose[i]);
		DeleteObject(hSecession[i]);
		DeleteObject(hTxt_Remove[i]);
		DeleteObject(hTxt_Release[i]);
		DeleteObject(hTxt_Mark[i]);
		DeleteObject(hTxt_Help[i]);
		DeleteObject(hTxt_Secession[i]);
	}
	


	DeleteObject(hIcon);
	DeleteObject(hHelp1);



	#endif
}

void CLAN_MENU::Loading()
{
#ifdef USE_PROSTONTALE		//=========== 포리스턴소스인경우
	Draw_C_Text(szLoading, BackStartPos.x + 80,BackStartPos.y + 90);
#else

	HDC hdc, sorDC,destdc;

	hdc = GetDC(g_hwnd);
	sorDC  = CreateCompatibleDC(hdc);
	destdc = CreateCompatibleDC(hdc);
	SelectObject(destdc, Dback.hb );		//off스크린설정.	
//	Text_Out(destdc,BackStartPos.x + 80,BackStartPos.y + 90 ,szLoading);

	DeleteDC(sorDC);
	DeleteDC(destdc);
	ReleaseDC(g_hwnd, hdc );
#endif

}


#ifdef USE_PROSTONTALE		//=========== 포리스턴소스인경우
//클랜원 정보 전송용 함수
int SendClanCommandUser( smWINSOCK *lpsmSock , DWORD	dwCode , int Param1, int Param2 , CLANWONLIST *lpClanUserList , int ClanUserCount );
#endif


void SetClanWon()
{
	if(cldata.nTotalClanWonCount==0) return;

	memcpy(ClanWonList.clanWon,cldata.clanWon,sizeof(cldata.clanWon));

	//========================================================

#ifdef USE_PROSTONTALE		//=========== 포리스턴소스인경우
	//클랜원 정보 전송용 함수
	SendClanCommandUser( smWsockDataServer , smTRANSCODE_CLAN_UPDATE  , 0,0, &ClanWonList , cldata.nTotalClanWonCount );

	//========================================================
#endif

}





//savedata\\clanDATA 만들기==============================================start
BOOL SearchDirectory(char *dir)
{
	WIN32_FIND_DATA wfd;
	HANDLE hFind;	
	char t[50];
	wsprintf(t,"%s\\*.*",dir);
	hFind = FindFirstFile(t,&wfd);
	if(hFind == INVALID_HANDLE_VALUE)
	{		
		return FALSE;
	}	

	return TRUE;	
}

void MakeDirectory(char *dir)
{
	CreateDirectory(dir,NULL);
}


void CreateSaveData_dir()
{	
	char szTemp[100];
	if(!SearchDirectory(SAVEDATA_DIR)) MakeDirectory(SAVEDATA_DIR);
	if(!SearchDirectory(CLANDATA_DIR)) MakeDirectory(CLANDATA_DIR);

	ZeroMemory(szTemp,sizeof(szTemp));
	wsprintf(szTemp,"%s",CLANDATA_DIR);
	wsprintf(szTemp,"%s\\%s",szTemp,szConnServerName);

	if(!SearchDirectory(szTemp)) MakeDirectory(szTemp);

}

//savedata\\clanDATA 만들기==============================================end

void Text_Out1()
{
}