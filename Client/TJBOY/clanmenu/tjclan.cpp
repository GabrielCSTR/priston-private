#include "StdAfx.h"
#define TJCLAN_CPP

#include "tjclanDEF.h"
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
#include "cE_Notice.h"

#include "..\\isaocheck\\auth.h"
#include "..\\isaocheck\\isaocheck.h"
#include "Help.h"
#include "GuideHelp.h" 

#include "..\\ygy\\ygyheader.h"

extern HWND hTextWnd;
extern HWND hFocusWnd;

extern char UserAccount[256];
extern char	szConnServerName[16];

#define MOUSE0() TJmb[0]


int ClanCharMove=0;	//클랜메뉴판안의 마우스의 움직임에 캐릭터가 영향없도록 한다.
int ClanCLCharMove=0;//클랜채팅리스트메뉴판안의 마우스의 움직임에 캐릭터가 영향없도록 한다.


int  banisF[100];

//int TJwheel=0; //ktj : 휠데이타
void fd2( char *fmt, ...);




//유광열 도움말 마우스 이벤트 갖어오기====START
int GuideHelpButton[3] = {0,0,0}; //가이드 도움말
int LevelpUpButton[3]= {0,0,0}; //레벨업 도움말
//END

BOOL bKeyDown = FALSE;
int nKeyDown = 0;
BOOL bKeyUp = FALSE;
int nKeyUp = 0;
BOOL bLButtonDown = FALSE;
BOOL bKeyPageDown = FALSE;
BOOL bKeyPageUp = FALSE;

BOOL IsDrawGuideHelp = FALSE; //가이드 도움말이 떠져있음

void clan_Mouse(int msg,WPARAM wParam)
{
	switch(msg){
	//유광열 WM_KEYUP추가
	case WM_KEYUP:
		switch(wParam)
		{
		case VK_DOWN:
			GuideHelpButton[0] = FALSE; //가이드 도움말
			bKeyUp = FALSE;
			bKeyDown = FALSE;
			break;
		case VK_UP:						
			bKeyDown = FALSE;
			bKeyUp = FALSE;
			GuideHelpButton[0] = FALSE; //가이드 도움말			
			break;
		
		}		
		break;
	case WM_KEYDOWN:
		switch(wParam)
		{
		case VK_DOWN:
			GuideHelpButton[0] = TRUE; //가이드 도움말
			bKeyDown = TRUE;
			bKeyUp = FALSE;
			nKeyDown++;
			break;
		case VK_UP:						
			GuideHelpButton[0] = TRUE; //가이드 도움말
			bKeyUp = TRUE;
			bKeyDown = FALSE;
			nKeyUp++;
			break;
		case VK_ESCAPE://esc키로 도움말 끄기
			g_GuideHelp.GuidHelpEnd();
			g_Help.HelpEnd();
			break;
		
		}		
		break;
	//==============END
	
	case WM_LBUTTONDOWN:
		TJmb2[0] = TJmb[0] = TRUE;
		//유광열==============start		
		bKeyDown = FALSE;
		bKeyUp = FALSE;		
		
		GuideHelpButton[0] = TRUE; //가이드 도움말
		LevelpUpButton[0]=TRUE; //레벨업 도움말	

		//end
		break;

	case WM_LBUTTONUP:
		TJmb2[0] = TJmb[0] = FALSE;
		//유광열==============start
		bKeyDown = FALSE;
		bKeyUp = FALSE;
		bLButtonDown = FALSE;
		
		GuideHelpButton[0] = FALSE; //가이드 도움말
		LevelpUpButton[0]=FALSE; //레벨업 도움말
		//==============END
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
	static int cnt=0;
	cnt++;

	int mainchk;
	
	if(cnt<10) 
		mainchk = PARTY_START;
	else 
		mainchk = PARTY_PROCESS;

	Interface_clanmenu.Main(mainchk);
#ifdef VOICE_CHAT
	
	g_CtrlProcess.Main();

#endif
}

void ktj_imsi_clanMENU_Draw()
{
	if( cSinHelp.sinGetHelpShowFlag() && !IsDrawGuideHelp ) return;	// 무한 텔레포트 코어 때문에 넣었음
	Interface_clanmenu.Draw();
}
		

void clanMENUinit()
{
	Interface_clanmenu.CLANmenu_INIT();
	Interface_clanmenu.CLANmenu_clanPOSITION();
}
void InitHelp()
{	
	if(!g_GuideHelp.GetIsOn()) return; //레벨업 도움말이 꺼져있을 경우
	//if((sinChar->Level == 20)&&(sinChar->JOB_CODE > 4)) return;
	g_Help.SetStartPos(0,0);
	if(!g_Help.CheckLevel(sinChar->iLevel,sinChar->iClass)) return;
	g_Help.SetHelpN(LEVELUP_HELP);
	g_Help.menuInit(LEVELUP_HELP);
}

void InitGuideHelp()
{	
	g_GuideHelp.SetDoing(TRUE);
	g_GuideHelp.SetStartPos(0,0);	
	g_GuideHelp.CheckLevel(sinChar->iLevel);
	//g_GuideHelp.CheckLevel(17);
	g_GuideHelp.SetHelpN(GUIDEHELP_LIST);
	g_GuideHelp.menuInit(GUIDEHELP_LIST);

	IsDrawGuideHelp = TRUE;
}



void HelpDraw()
{
	if(g_Help.GetHelpN() !=-1)
	{
		switch(g_Help.GetHelpN())
		{
		case LEVELUP_HELP:
			g_Help.Draw(0);
			break;
		case LEVELUP_HELP_CONTENT:	

			g_Help.Draw(0);			
			break;		
		}
	}
}

void CLAN_MENU::GuideHelpDraw()
{
	if(g_GuideHelp.GetHelpN() !=-1)
	{
		switch(g_GuideHelp.GetHelpN())
		{			
		case GUIDEHELP_LIST:
			DrawBox(NOTICE_X,NOTICE_Y-50,9,9);
			g_GuideHelp.Draw();
			break;
		case GUIDEHELP_CONTENT:
			DrawBox(NOTICE_X,NOTICE_Y-50,9,9);
			g_GuideHelp.Draw();
			break;

		}
	}
}
//=============겜들어가기직전에 나오는 경고 메세지=====================
int GoNotice_chking = 0;
int m_nNoticeCount = -1;
char szNoticeUrl[255] = {0,};
//1. 셋팅함수
int GetNoticeUrl(char *url)  
{
	GoNotice_chking = 0;
	ZeroMemory(szNoticeUrl,sizeof(szNoticeUrl));
	lstrcpy(szNoticeUrl,url);

	GoNotice_chking = 1;
	return 1;
}
void GoNotice_chk()
{
	if(OpenFlag == 1) 
		return;

	if( GoNotice_chking == 1)
	{		
		if(m_nNoticeCount <NOTICECOUNT-1)
		{
			GoNotice_chking = 0;
			++m_nNoticeCount;
			void GoNotice();
			GoNotice();
		}
		
	}
}
void GoNotice()
{
	C_menuN2= 0;
	OpenFlag = 1;
	C_menuN = CLAN_NOTICE;
}

void clanMENU_INIT(int setN)
{	
	if(bCheckHostNameandPort==0) 
	{
		switch(setN) 
		{
		case 0:
			void ReadWEBDebugOption();
			ReadWEBDebugOption();
			break;

		case 1:
			Interface_clanmenu.NoticeMessage_Init2();

			Interface_clanmenu.SetUserData(UserAccount, sinChar->szName, szConnServerName,sinChar->iGold,500000);
			break;
		}
	}
	


	if(!bCheckHostNameandPort) 
		return;

	switch(setN)
	{
	case -1:
		void ReadWEBDebugOption();
		ReadWEBDebugOption();


		ZeroMemory(&ClanWonList,  sizeof(CLANWONLIST ));

		Interface_clanmenu.CLANmenu_INIT();
		Interface_clanmenu.CLANmenu_clanPOSITION();

		break;

	case 0:				//맨처음셋팅 : 캐릭터 선택직전셋팅
		void ReadWEBDebugOption();
		ReadWEBDebugOption();

		int LoadClanMessage();
			LoadClanMessage();

		void CreateSaveData_dir();
		CreateSaveData_dir();			//savedata/clandata만듦

		ZeroMemory(&ClanWonList,  sizeof(CLANWONLIST ));
		Interface_clanmenu.CLANmenu_INIT();
#ifdef VOICE_CHAT
		
		//{
			//유광열 : 음성채팅 관련 클라이언트 프로세스를 실행시킴.
			g_CtrlProcess.CheckIPandPort(0, 0);  
		//}
#endif

		break;

	case 1:

#ifdef VOICE_CHAT
		g_CtrlProcess.Init();
#endif

		cBaseMenu.Load2();
		cClanChatting.Load2();
		Interface_clanmenu.Init2();	
		Interface_clanmenu.SetUserData(UserAccount, sinChar->szName, szConnServerName,sinChar->iGold,500000);
		Interface_clanmenu.CLANmenu_clanPOSITION();
		break;
	}
}
int isDELETE_character(char *charName) 
{
	if(!bCheckHostNameandPort) 
		return 1;

	int web_DB_state_FLAG_WAIT();

	while(1)
	{
		if(web_DB_state_FLAG_WAIT() == 1) 
			break;
	}

	Interface_clanmenu.SetUserData(UserAccount, charName, szConnServerName,500000,500000);

	Interface_clanmenu.CLANmenu_clanPOSITION();
	cldata.myPosition = 0;
	while(1)
	{
		web_DB_main();
		cIsClanMember.Main();

		if(cldata.myPosition != 0) 
			break;
	}

	while(1)
	{
		if(web_DB_state_FLAG_WAIT() == 1) 
			break;
	}

	return cldata.myPosition;
}



void CLAN_MENU::Init2()
{

	MatPartyBackGround =CreateTextureMaterial( "image\\Sinimage\\Help\\party_win.tga" , 0, 0, 0, SMMAT_BLEND_ALPHA );


	hBox1 = CreateTextureMaterial( "image\\Sinimage\\Help\\HelpBoxCorner.tga",  0, 0, 0, SMMAT_BLEND_ALPHA );

	hBox2 = CreateTextureMaterial( "image\\Sinimage\\Help\\HelpBoxLine.tga",  0, 0, 0, SMMAT_BLEND_ALPHA );

	hBox3 = CreateTextureMaterial( "image\\Sinimage\\Help\\box3.tga",  0, 0, 0, SMMAT_BLEND_ALPHA );

	hBox4 = CreateTextureMaterial( "image\\Sinimage\\Help\\box4.tga",  0, 0, 0, SMMAT_BLEND_ALPHA );
	hBox5 = CreateTextureMaterial( "image\\Sinimage\\Help\\box5.tga",  0, 0, 0, SMMAT_BLEND_ALPHA );

	hBox6 = CreateTextureMaterial( "image\\Sinimage\\Help\\box6.tga",  0, 0, 0, SMMAT_BLEND_ALPHA );

	hBox7 = CreateTextureMaterial( "image\\Sinimage\\Help\\box7.tga",  0, 0, 0, SMMAT_BLEND_ALPHA );

	hBox8 = CreateTextureMaterial( "image\\Sinimage\\Help\\box8.tga",  0, 0, 0, SMMAT_BLEND_ALPHA );

	hBox9 = CreateTextureMaterial( "image\\Sinimage\\Help\\box9.tga",  0, 0, 0, SMMAT_BLEND_ALPHA );

	hScl_icon_tj = CreateTextureMaterial( "image\\Sinimage\\Help\\scl_icon.tga", 0, 0, 0, SMMAT_BLEND_ALPHA );
	g_Help.Load();
	g_GuideHelp.Load();


	cBaseMenu.copy_LoadResource2(&cIsClanMember);
	cBaseMenu.copy_LoadResource2(&cClanChip);
	cBaseMenu.copy_LoadResource2(&cClanUser);
	cBaseMenu.copy_LoadResource2(&cClanMake);
	cBaseMenu.copy_LoadResource2(&cClanReport);
	cBaseMenu.copy_LoadResource2(&cClanChatting);
	cBaseMenu.copy_LoadResource2(&cClanDeleteCha);
	cBaseMenu.copy_LoadResource2(&cClanJoin);
	
	cBaseMenu.copy_LoadResource2(&cClanNotice);	
}

//notice메시지로드용의 Init2()에 상응하는 함수
void CLAN_MENU::NoticeMessage_Init2()
{
	MatPartyBackGround =CreateTextureMaterial( "image\\Sinimage\\Help\\party_win.tga" , 0, 0, 0, SMMAT_BLEND_ALPHA );

	hBox1 = CreateTextureMaterial( "image\\Sinimage\\Help\\HelpBoxCorner.tga",  0, 0, 0, SMMAT_BLEND_ALPHA );

	hBox2 = CreateTextureMaterial( "image\\Sinimage\\Help\\HelpBoxLine.tga",  0, 0, 0, SMMAT_BLEND_ALPHA );

	hBox3 = CreateTextureMaterial( "image\\Sinimage\\Help\\box3.tga",  0, 0, 0, SMMAT_BLEND_ALPHA );

	hBox4 = CreateTextureMaterial( "image\\Sinimage\\Help\\box4.tga",  0, 0, 0, SMMAT_BLEND_ALPHA );
	hBox5 = CreateTextureMaterial( "image\\Sinimage\\Help\\box5.tga",  0, 0, 0, SMMAT_BLEND_ALPHA );

	hBox6 = CreateTextureMaterial( "image\\Sinimage\\Help\\box6.tga",  0, 0, 0, SMMAT_BLEND_ALPHA );

	hBox7 = CreateTextureMaterial( "image\\Sinimage\\Help\\box7.tga",  0, 0, 0, SMMAT_BLEND_ALPHA );

	hBox8 = CreateTextureMaterial( "image\\Sinimage\\Help\\box8.tga",  0, 0, 0, SMMAT_BLEND_ALPHA );

	hBox9 = CreateTextureMaterial( "image\\Sinimage\\Help\\box9.tga",  0, 0, 0, SMMAT_BLEND_ALPHA );

	hScl_icon_tj = CreateTextureMaterial( "image\\Sinimage\\Help\\scl_icon.tga", 0, 0, 0, SMMAT_BLEND_ALPHA );
	cBaseMenu.copy_LoadResource2(&cClanNotice);

}




void CLAN_MENU::CLANmenu_INIT()
{
	if(!bCheckHostNameandPort)
		return;
	Init();
	SetUserData(UserAccount, sinChar->szName, szConnServerName, sinChar->iGold,500000);
}

BOOL bGetChaClan = FALSE; //계정에 관련된 캐릭터들의 클랜정보를 읽어오는지 체크
int  nGetChaClan = 0;   //0: 진행안됨 1: 진행되고있음 2: 진행완료  3: 에러
int nStatusCount=0;	


int cntsu = 0;
char *szSelectCha[5][2];


void InitSelectCha()
{
	if(!bCheckHostNameandPort) return;

	nStatusCount=0;	
	ZeroMemory(chacldata,sizeof(chacldata));
	ZeroMemory(szSelectCha,sizeof(szSelectCha));
	cntsu = 0;
}

void ClearSelectCha()
{
	if(!bCheckHostNameandPort)
		return;
	int i;
	for(i =0; i< 5; i++)
	{
		DELET(chacldata[i].hClanMark);
		DELET(chacldata[i].hClanMark16);
	}

	bGetChaClan = FALSE;
	ZeroMemory(szSelectCha,sizeof(szSelectCha));
	ZeroMemory(chacldata,sizeof(chacldata));
	ZeroMemory(&cldata,sizeof(CLANDATA));
	nStatusCount = 0;

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

	//while(1) {

	Interface_clanmenu.Main(PARTY_PROCESS );

	if(nStatusCount>=cntsu){
		return 1;
	}
	else	
	{
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


	//임시
	Interface_clanmenu.Main(PARTY_PROCESS );


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

#ifdef VOICE_CHAT
BOOL bCheckClan = FALSE;
#endif
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

#ifdef VOICE_CHAT	
		bCheckClan = TRUE;
#endif
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

		cClanChatting.menuInit(ChatList_CmenuN);

		break;
	case 1: //스크롤 안되게
		cClanChatting.NoScroll();	

		ChatList_CmenuN = CLAN_DISPLAY_INFO;				
		cClanChatting.menuInit(ChatList_CmenuN);

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
: 클라스명 :권유하는사람이 사용
: 하 는 일 : 클랜장이 클랜원을 등록시킬때
///////////////////////////////////////////////////////////////////////////*/

//===================================
//ktj:사용안함.
//====================================
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


int g_ClanCount=-1;
int ClanMark[10] = {0,0,0,0,0,0,0,0,0,0};

//============= 디버깅용 클랜인포 데이타세이브
int ReadClanInfo(DWORD dwClanNum)
{
	//디버깅용으로 그리기 위한것
	g_ClanCount++;
	if(g_ClanCount > 9) g_ClanCount = 0;
	ClanMark[g_ClanCount] = dwClanNum; 
	//============================

	/*
	if(OpenFlag==1) {
		return -1;		//이 메뉴가 닫혀있을때만 가능함.
	}
	*/

	g_ViewClanInfo.SearchClan(dwClanNum);
	return ClanInfo_nNum;		//0~99;
}


// 현재 16*16 으로 된 그림만 로드되있으나 32*32가 필요한 경우 부른다.
// 32*32가 메모리를 많이 차지해서 이렇게 따로 필요한 극소수의 경우에만 부른다.
int ReadClanInfo_32X32(DWORD dwClanNum)
{
	int claninfo_n = ReadClanInfo(dwClanNum);
	if(claninfo_n >= 0) {
		int clanINFO_Load32X32(int claninfo_n );
		clanINFO_Load32X32(claninfo_n );
	}
	return claninfo_n;
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

	
	nClanWon_Num = 0;
	nReleaseClanWon = 0;

	Load();	
	cClanChatting.Load();
	
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


	cClanNotice.Init(1);
	cClanNotice.setParent(&cBaseMenu);
	cBaseMenu.copy_LoadResource(&cClanNotice);		//리소스 카피	

	//도움말 초기화
	//g_Help.Init(1);
	//g_Help.setParent(&cBaseMenu);
	//cBaseMenu.copy_LoadResource(&g_Help);		//리소스 카피	

	//guie 초기화
	g_GuideHelp.Init(1);
	g_GuideHelp.setParent(&cBaseMenu);
	cBaseMenu.copy_LoadResource(&g_GuideHelp);		//리소스 카피	
	g_GuideHelp.InitLevelHelpLabel();

}


//notice메시지는 따로 셋팅되며 Init()과 동시에 쎗팅할수없음.
//클랜 서버가 죽어 있을 경우 세팅
void CLAN_MENU::NoticeMessage_Init()
{
	BackStartPos.x = 101;
	BackStartPos.y = 114;

	cBaseMenu.Load();

	cClanNotice.Init(1);
	cClanNotice.setParent(&cBaseMenu);
	cBaseMenu.copy_LoadResource(&cClanNotice);		//리소스 카피	

	g_Help.Load();
	g_GuideHelp.Load();

	g_GuideHelp.Init(1);
	g_GuideHelp.setParent(&cBaseMenu);
	cBaseMenu.copy_LoadResource(&g_GuideHelp);		//리소스 카피	
	g_GuideHelp.InitLevelHelpLabel();
	
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
	Interface_clanmenu.menu_joinOpen_Chip(isOK, clanWonID, clanWonCharID,0,0);		//칲의 캐릭터 id;
}
void menu_joinOpen_Chip(int isOK, char *clanWonID, char *clanWonCharID, int clanWonJob, int clanWonLevel)
{
	Interface_clanmenu.menu_joinOpen_Chip(isOK, clanWonID, clanWonCharID,clanWonJob, clanWonLevel);		//칲의 캐릭터 id;
}

//호동Clan추가
void g_IsCheckClanMember(Unit *pChar)
{
	Interface_clanmenu.IsCheckClanMember(pChar);
}

int CLAN_MENU::IsCheckClanMember(Unit *pChar)
{
	if(OpenFlag == 1)
		return 0;
	
	C_menuN = CLAN_IS_CHECK_MEMBER;	//클랜에 가입한지 4일이 지났는지 검사를 한다.
	cldata.TargetChar = NULL;
	if(pChar)
		cldata.TargetChar = pChar;
	
	//strcpy(cldata.ChaName, pChar->smCharInfo.szName);
	
	C_menuN2= 0;
	OpenFlag = 1;
	joinAnswer = 0;
	ClanCharMove = 1;
	
	return 0;
}



//======================================================================
//권유하는 메뉴를 누르면 이함수를 불러 리턴이 1이면 권유하는 데이타를 보내고 아니면 말것.
// 0 이면 더이상 클랜원을 추가 할수 없음(자체메뉴에서 등록시킬수없다고 나온다)
BOOL CheckClanWon(int level);		//

//======================================================================


//권유받은 사람이 OK하면 그명령이 클랜칲에게 되돌아와 클랜칲이 가입시키는 메뉴임.
//주의 : 화면상에는 메뉴가 뜨지않음.
int CLAN_MENU::menu_joinOpen_Chip(int joinOK, char *clanWonID, char *clanWonCharID, int clanWonJob, int clanWonLevel)		//칲의 캐릭터 id
{
	if(OpenFlag==1)
		return 0;

	//if(cldata.myPosition != 101 || cldata.myPosition != 104 )
		//return 0;

	int chk = CheckClanWon(sinChar->iLevel);

	if(chk==0)
		return 0;

	C_menuN = CLAN_JOIN_chip;
	lstrcpy(cldata.clanJoinID,clanWonID);
	lstrcpy(cldata.clanJoinCharID,clanWonCharID);
	cldata.clanJoinJob   = clanWonJob;
	cldata.clanJoinLevel = clanWonLevel;

	C_menuN2= 0;

	OpenFlag = 1;
	joinAnswer = 0;

	ClanCharMove = 1;


	return 1;
}

extern BOOL bip_port_error;
int CLAN_MENU::Main(int sw)
{
	web_DB_main();

	GoNotice_chk();
	if((bip_port_error==1)||GoNotice_chking||(m_nNoticeCount > -1))  
		cClanNotice.Main();

	g_Help.Main();
	g_GuideHelp.Main();




	if(bip_port_error) 
		return 0;

	if(OpenFlag==0) 
		return 0;


	switch(sw) 
	{
	case PARTY_START:				//처음 불리워질때의 처리
		return 1;
	case PARTY_END:					//끝날즘에 불리워질때의 처리
		return 1;
	}
									//ktj : auth.cpp의 web_DB첵크용임.
	cBaseMenu.Main();				//ktj : 공용 메뉴 의 메인
	cIsClanMember.Main();			//ktj : 클랜원의 포지션 체크 메인
	cClanReport.Main();				//ktj : 메시지 처리용 메인
	cClanMake.Main();				//ktj : 클랜을 만들경우의 메인
	cClanChip.Main();				//클랜 칩 메세지 처리
	cClanUser.Main();				//클랜 유저 메세지처리
	cClanJoin.Main();

	cClanDeleteCha.Main();            //캐릭터 삭제시
	cClanNotice.Main();	//그메인
	
	return TRUE;
}




char loadis[256] = {0,};
char loadis2[256] = {0,};
char updateis[256] = {0,};


int ktj_imsiDRAWinfo = 0;


int CLAN_MENU::Draw()
{	
	HelpDraw();
	GuideHelpDraw();

	if((bip_port_error==1)||(m_nNoticeCount > -1)) 
	{
		if(C_menuN==CLAN_DRAWNOTICE) 
		{
			DrawBox(NOTICE_X,NOTICE_Y-50,9,10);
			Draw_C_menuN();
		}
		if(m_nNoticeCount > -1)
			cClanNotice.Draw();
	}

	if(bip_port_error) 
		return 0;

	if(SETTINGHANDLE->Get().bDebugMode && ktj_imsiDRAWinfo == 1)
	{
		char buf[256];

		wsprintf(buf, "bug :  %d ================ : (myPos:%d ) (클랜마크번호%s,%d)  cldata.money %d, cldata.nCurrentClanWon_Num %d ", C_menuN, cldata.myPosition, cldata.ClanMark, cldata.intClanMark, cldata.money, cldata.nCurrentClanWon_Num);
		Draw_C_Text(buf, 0,0,   0);


		wsprintf(buf, "cldata.szID %s  cldata.ChaName %s cldata.name %s (C_menuN %d C_menuN2 %d) ================ ", cldata.szID,cldata.ChaName, cldata.name, C_menuN, C_menuN2);
		Draw_C_Text(buf, 0,16,   0);

		int cinfoX = 0;
		int cinfoY = 32;
		int i2;

		for(i2=0; i2<100; i2++)
		{
			if(ClanInfo[i2].nStatus==0)
				continue;

			char buf[256];
			wsprintf(buf, "ClanInfo[%d] %s %s %s ", i2, 
				ClanInfo[i2].ClanInfoHeader.ClanMark_Num,
				ClanInfo[i2].ClanInfoHeader.ClanName,
				ClanInfo[i2].ClanInfoHeader.ClanReport);

			Draw_C_Text(buf, cinfoX ,cinfoY,   0);
			cinfoY+=16;
		}

		int cinfoX2 = 16*25;
		int cinfoY2 = 32;

		for(i2=0; i2<10; i2++)
		{
			char buf[256];
			wsprintf(buf, "up 마크번호 [%d]:%d (최종 %d)", i2, ClanMark[i2], g_ClanCount);
			Draw_C_Text(buf, cinfoX2 ,cinfoY2,   0);
			cinfoY2+=16;
		}


		cinfoX2 = 20*35;
		cinfoY2 = 32;

		for(i2=0; i2<41; i2++)
		{
			Draw_C_Text(cldata.clanWon[i2], cinfoX2 ,cinfoY2,   0);
			cinfoY2+=16;
		}

		char Msg3[1024] = {0,};
		int nPos= 0;
		extern char g_AllClanWon[_CLANWON_MAX][STRING_MAX];

		for(int i = 0; i< 90; i+=5)
		{
			wsprintf(Msg3,"%s, %s,  %s , %s, %s\n",g_AllClanWon[i],g_AllClanWon[i+1],g_AllClanWon[i+2],g_AllClanWon[i+3],g_AllClanWon[i+4]);
			Draw_C_Text(Msg3, 300,230+nPos,   0);
			nPos+=20;
		}
	}

	if(OpenFlag==0) 
		return 0;	

	switch(C_menuN)
	{
	case CLAN_DRAWNOTICE:

		DrawBox(NOTICE_X,NOTICE_Y,9,10);		

		cClanNotice.Draw();
		break;
	case CLAN_NOLEVEL: //레벨이 안되서 클랜을 못만듬
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();						
		break;
	case CLAN_ABILITYDOWN:
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
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		break;
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

	case CLANCHIP_SUBCHIP_LOAD_DATA:
	case CLANCHIP_APPOINTSUBCHIP_DO:	    //클랜부칩 임명 ASP호출
	case CLANCHIP_RELEASESUBCHIP_DO:	    //클랜부칩 해임 ASP호출
	case CLANCHIP_SUBCHIP_APPOINT_FLAG:		//클랜부침이 임명되어다는 플래그세팅
	case CLANCHIP_SUBCHIP_RELEASE_FLAG:		//클랜부침이 해임되어다는 플래그세팅
	case CLANCHIP_SUBCHIP_READMSG_FLAG:		//클랜장이 부침관련메세지를 읽어다는 플래그세팅
	case CLANUSER_SUBCHIP_READMSG_FLAG:		//클랜유저가 부침관련 메세지를 읽어다는 플래그 세팅
	case CLANCHIP_SUBCHIP_LIST:			//클랜원들 리스트 보여줌 부 클랜칩이 있으면 따로 보여줌
	case CLANCHIP_RESUBCHIP_APPOINT:		//부 클랜칩 임명 재확인
	case CLANCHIP_RESUBCHIP_APPOINT_END:	//부 클랜칩임명 마지막 메세지
	case CLANCHIP_RELEASESUBCHIP:			//부 클랜칩해임 재확인
	case CLANCHIP_RELEASESUBCHIP_END:		//클랜칩 해임 마지막 메세지
	case CLANCHIP_SUBCHIP_APPOINTMSG:
	case CLANCHIP_SUBCHIP_RELEASEMSG:
	case CLANUSER_SUBCHIP_APPOINTMSG:
	case CLANUSER_SUBCHIP_RELEASEMSG:
	case CLANCHIP_NOSUBCHIP:

	case CLANCHIP_LEAVECLAN_NOLEVEL:
	case CLANCHIP_LEAVECLANDOWNLEVEL:
	case CLANCHIP_LEAVECLAN_PFLAG:		
	case CLANCHIP_LEAVECLAN_MESSAGE:		
	case CLANUSER_LEAVECLAN_MESSAGE:		
	case CLANCHIP_LEAVECLAN_MESSAGEEND:	
	case CLANUSER_LEAVECLAN_MESSAGEEND:	
	case CLANCHIP_NOLEAVECLAN:
	case CLANCHIP_LEAVECLAN_RECONFIRM:
	case CLANCHIP_LEAVECLAN_CONFIRM:
	case CLANCHIP_LEAVECLAN_NOMONEY:
	case CLANCHIP_LEAVECLAN_SUCESS:
	case CLANCHIP_LEAVECLAN://이임
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		break;
	case CLAN_CHIP:
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		break;
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


	case CLANCHIP_LEAVECLAN_DO:		//이임 asp호출
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
	case CLAN_CLANWONOVER:
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		break;

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
	return TRUE;
}
void CLAN_MENU::Draw_C_Text(char *str, int x, int y, int sw=0)
{
	char strbuf[1024];

	ZeroMemory(strbuf, sizeof(strbuf));

	int strL = lstrlen(str);
	int cnt=0;
	int i=0;

	while(1)
	{
		strbuf[i] = str[cnt];
		cnt++;
		if(strbuf[i] == '\n')
		{
			strbuf[i] =0;
			i=0;
jmp1:
			if(sw==2)
			{
				dsTextLineOut(0, x+1, y+1, strbuf, lstrlen(strbuf),D3DCOLOR_XRGB(100, 100, 100));
				dsTextLineOut(0, x, y, strbuf, lstrlen(strbuf),D3DCOLOR_XRGB(230, 255, 240));
			}
			else
				dsTextLineOut(0, x, y, strbuf, lstrlen(strbuf),D3DCOLOR_XRGB(230, 255, 240));
			
			ZeroMemory(strbuf, sizeof(strbuf));
			y+=16;

			if(cnt>=strL) break;
		}
		else if(cnt>=strL)
			goto jmp1;
		else 
			i++;
	}
	

	if(sw==1) 
	{
		static int cnt=0;
		cnt++;
		if(cnt<20)
			dsTextLineOut(0, x + (lstrlen(str)*6) , y-16, "|", 1,D3DCOLOR_XRGB(255, 255, 255));

		if(cnt>=40) 
			cnt=0;
	}
}



int g_nTotalWidth = 0;

#define BOXFONTSIZE 64

int CLAN_MENU::DrawBox(int x,int y,int x_width,int y_height)
{
	if( cSinHelp.sinGetHelpShowFlag() && !IsDrawGuideHelp ) 
		return FALSE;
	isDrawClanMenu = 1;

	g_nTotalWidth = x_width;

	sinDrawTexImage( hBox5, (float)x+64, (float)y+32, (float)( 64+((x_width-2) *32) ), (float)(   32+(  (y_height-1) *32) ),0,0,0, 0, 32, 32, 255);

	sinDrawTexImage( hBox1,(float) x,(float) y, (float)64, (float)32,(float)0,(float)0,(float)0, (float)0, (float)64, (float)32,255);

	sinDrawTexImage( hBox3,(float)(   x+(32*x_width) +64 ), (float)y, 64, 32,(float)0,(float)0,(float)0, (float)0, (float)64, (float)32,255);	

	sinDrawTexImage( hBox7, (float)x, (float)(  y+(32*y_height) + 32 ), 64, 64 ,(float)0,(float)0,(float)0, (float)0, (float)64, (float)32,255);

	sinDrawTexImage( hBox9,(float)(   x+(32*x_width) +64 ), (float)(  y+(32*y_height) + 32  ), 64, 64,(float)0,(float)0,(float)0, (float)0, (float)64, (float)32,255);
				
	int line;
	int sx = x+64;
	int ey=  y+(32*y_height) + 32 ;
	for(line=0; line<x_width; line++)
	{
		sinDrawTexImage( hBox2, (float) sx, (float)y, 32, 32,(float)0,(float)0,(float)0, (float)0, (float)32, (float)32,255);
		sinDrawTexImage( hBox8, (float)sx, (float)( ey ), 32, 64,0,0,0, 0, 32, 64,255);		
		sx+=32;
	}

	int sy = y+32;
	int ex = x+(32*x_width) + 64 ;
	for(line=0; line<y_height; line++)
	{
		sinDrawTexImage( hBox4, (float)x, (float)sy, 64, 32,0,0,0, 0, 64, 32,255);
		sinDrawTexImage( hBox6,(float)ex, (float)sy, 64, 32,0,0,0, 0, 64, 32,255);
		sy+=32;
	}
	return TRUE;
}

void CLAN_MENU::RenderMenu()
{

}

void CLAN_MENU::Draw_C_menuN()
{		
	cBaseMenu.Draw();
	cClanChip.Draw();	
	cClanUser.Draw();	
	cClanMake.Draw();	
	cClanReport.Draw();
	cClanJoin.Draw();
}

void SetUserData2(char* id, char* chaname, char* gserver)
{
	lstrcpy(cldata.szID,id);
	lstrcpy(cldata.ChaName,chaname);
	lstrcpy(cldata.gserver,gserver);
}

void CLAN_MENU::SetUserData(char* id, char* chaname, char* gserver,int money, int ability)
{
	lstrcpy(cldata.szID,id);
	lstrcpy(cldata.ChaName,chaname);
	lstrcpy(cldata.gserver,gserver);

	cldata.money = money;

	cldata.ability = ability;
}


void CLAN_MENU::SetJoinData(char *joinclanname, char *joinclanchip)
{
	lstrcpy(cldata.szJoinClanName,joinclanname);
	lstrcpy(cldata.szJoinClanChipName,joinclanchip);
}

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
	
}
void CLAN_MENU::Load()
{
	MatPartyBackGround =CreateTextureMaterial( "image\\Sinimage\\Help\\party_win.tga" , 0, 0, 0, SMMAT_BLEND_ALPHA );

	hBox1 = CreateTextureMaterial( "image\\Sinimage\\Help\\HelpBoxCorner.tga",  0, 0, 0, SMMAT_BLEND_ALPHA );

	hBox2 = CreateTextureMaterial( "image\\Sinimage\\Help\\HelpBoxLine.tga",  0, 0, 0, SMMAT_BLEND_ALPHA );

	hBox3 = CreateTextureMaterial( "image\\Sinimage\\Help\\box3.tga",  0, 0, 0, SMMAT_BLEND_ALPHA );

	hBox4 = CreateTextureMaterial( "image\\Sinimage\\Help\\box4.tga",  0, 0, 0, SMMAT_BLEND_ALPHA );
	hBox5 = CreateTextureMaterial( "image\\Sinimage\\Help\\box5.tga",  0, 0, 0, SMMAT_BLEND_ALPHA );

	hBox6 = CreateTextureMaterial( "image\\Sinimage\\Help\\box6.tga",  0, 0, 0, SMMAT_BLEND_ALPHA );

	hBox7 = CreateTextureMaterial( "image\\Sinimage\\Help\\box7.tga",  0, 0, 0, SMMAT_BLEND_ALPHA );

	hBox8 = CreateTextureMaterial( "image\\Sinimage\\Help\\box8.tga",  0, 0, 0, SMMAT_BLEND_ALPHA );

	hBox9 = CreateTextureMaterial( "image\\Sinimage\\Help\\box9.tga",  0, 0, 0, SMMAT_BLEND_ALPHA );
}

void clanMENU_close()
{
	Interface_clanmenu.Close();
}

void CLAN_MENU::Close()
{
	DELET(cldata.hClanMark);
	DELET(cldata.hClanMark16);

	cClanChatting.Close();
	cBaseMenu.Close();

#ifdef VOICE_CHAT
	g_CtrlProcess.Clear();
#endif
}

void CLAN_MENU::Loading()
{
	Draw_C_Text(clanLoading.szMsg, BackStartPos.x + 80,BackStartPos.y + 90);
}


int SendClanCommandUser(DWORD	dwCode , int Param1, int Param2 , CLANWONLIST *lpClanUserList , int ClanUserCount );

void SetClanWon()
{
	if(cldata.nTotalClanWonCount==0) 
		return;

	memcpy(ClanWonList.clanWon,cldata.clanWon,sizeof(cldata.clanWon));

	SendClanCommandUser(smTRANSCODE_CLAN_UPDATE  , 0,0, &ClanWonList , cldata.nTotalClanWonCount );
}
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

	if(!SearchDirectory(SAVEDATA_DIR))
		MakeDirectory(SAVEDATA_DIR);

	if(!SearchDirectory(CLANDATA_DIR))
		MakeDirectory(CLANDATA_DIR);

	ZeroMemory(szTemp,sizeof(szTemp));
	wsprintf(szTemp,"%s",CLANDATA_DIR);
	wsprintf(szTemp,"%s\\%s",szTemp,szConnServerName);

	if(!SearchDirectory(szTemp))
		MakeDirectory(szTemp);
}

int ReadMessage(char *save,char *savename,char *readbuf);

#define CLANMESSAGE_DIR "image/clanImage/Help/clanText.msg"

int LoadClanMessage()
{
	char *g_ClanMessage;


	HANDLE hFile = NULL;
	DWORD dwFileSize;	
	DWORD dwRead = 0;
	char c;
	c = '\n';
	hFile = CreateFile( CLANMESSAGE_DIR, GENERIC_READ, FILE_SHARE_READ,
                        NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL , NULL );

	if(hFile == NULL) return -1;

	dwFileSize = GetFileSize(hFile,NULL);

	g_ClanMessage = new char[dwFileSize];

	ReadFile(hFile,g_ClanMessage,dwFileSize,&dwRead,NULL);
	CloseHandle(hFile);

	ReadMessage(clanMake1.szMsg,"szMsg1",g_ClanMessage);
	CheckMsgPos(&clanMake1,BOX_MAX_WIDTH,0);
	ReadMessage(clanMake2.szMsg,"szMsg2",g_ClanMessage);
	CheckMsgPos(&clanMake2,BOX_MAX_WIDTH,0);
	ReadMessage(clanMake4.szMsg,"szMsg4",g_ClanMessage);
	CheckMsgPos(&clanMake4,BOX_MAX_WIDTH,0);
	ReadMessage(clanMake5.szMsg,"szMsg5",g_ClanMessage);
	CheckMsgPos(&clanMake5,BOX_MAX_WIDTH,0);
	ReadMessage(clanMake6.szMsg,"szClanMakeFinishMsg",g_ClanMessage);
	CheckMsgPos(&clanMake6,BOX_MAX_WIDTH,0);
	ReadMessage(szMsg3,"szMsg3",g_ClanMessage);
	ReadMessage(clanMsg21.szMsg,"szMsg21",g_ClanMessage);
	CheckMsgPos(&clanMsg21,BOX_MAX_WIDTH,0);	
	
	ReadMessage(clanMsg254.szMsg,"szMsg254",g_ClanMessage);
	CheckMsgPos(&clanMsg254,BOX_MAX_WIDTH,0);	
	ReadMessage(clanMsg15.szMsg,"szMsg15",g_ClanMessage);
	CheckMsgPos(&clanMsg15,BOX_MAX_WIDTH,0);
	ReadMessage(clanJoin.szMsg,"szJoin",g_ClanMessage);
	CheckMsgPos(&clanJoin,BOX_MAX_WIDTH,0);	
	ReadMessage(clanSecession.szMsg,"szSecession",g_ClanMessage);
	CheckMsgPos(&clanSecession,BOX_MAX_WIDTH,0);
	ReadMessage(clanServerConnectErrorMsg.szMsg,"szServerConnectErrorMsg",g_ClanMessage);
	CheckMsgPos(&clanServerConnectErrorMsg,BOX_MAX_WIDTH,0);
	ReadMessage(clanszError_Msg.szMsg,"szError_Msg",g_ClanMessage);
	CheckMsgPos(&clanszError_Msg,BOX_MAX_WIDTH,0);
	ReadMessage(clanCancelMakeClan.szMsg,"szCancelMakeClan",g_ClanMessage);
	CheckMsgPos(&clanCancelMakeClan,BOX_MAX_WIDTH,0);
	ReadMessage(clanClanNameError.szMsg,"szClanNameError",g_ClanMessage);
	CheckMsgPos(&clanClanNameError,BOX_MAX_WIDTH,0);

	ReadMessage(clanSecession6DownMsg.szMsg,"szSecession6DownMsg",g_ClanMessage);
	CheckMsgPos(&clanSecession6DownMsg,BOX_MAX_WIDTH,0);
	
	ReadMessage(clanClanJoinMsg.szMsg,"szClanJoinMsg",g_ClanMessage);
	CheckMsgPos(&clanClanJoinMsg,BOX_MAX_WIDTH,0);

	ReadMessage(clanClanJoinCancelMsg.szMsg,"szClanJoinCancelMsg",g_ClanMessage);
	CheckMsgPos(&clanClanJoinCancelMsg,BOX_MAX_WIDTH,0);

	ReadMessage(clanClanJoinsucesssMsg.szMsg,"szClanJoinsucesssMsg",g_ClanMessage);
	CheckMsgPos(&clanClanJoinsucesssMsg,BOX_MAX_WIDTH,0);

	ReadMessage(clanszReMoveClanWonMsg.szMsg,"szReMoveClanWonMsg",g_ClanMessage);
	CheckMsgPos(&clanszReMoveClanWonMsg,BOX_MAX_WIDTH,0);

	ReadMessage(clanReMoveHeaderMsg.szMsg,"szReMoveHeaderMsg",g_ClanMessage);
	CheckMsgPos(&clanReMoveHeaderMsg,BOX_MAX_WIDTH,0);

	ReadMessage(clanszReConfReleaseMsg.szMsg,"szReConfReleaseMsg",g_ClanMessage);
	CheckMsgPos(&clanszReConfReleaseMsg,BOX_MAX_WIDTH,0);

	ReadMessage(clanNoRecordReleaseMsg.szMsg,"szNoRecordReleaseMsg",g_ClanMessage);
	CheckMsgPos(&clanNoRecordReleaseMsg,BOX_MAX_WIDTH,0);

	ReadMessage(clanFinishReleaseMsg.szMsg,"szFinishReleaseMsg",g_ClanMessage);
	CheckMsgPos(&clanFinishReleaseMsg,BOX_MAX_WIDTH,0);

	ReadMessage(clanSecessionMsg.szMsg,"szSecessionMsg",g_ClanMessage);
	CheckMsgPos(&clanSecessionMsg,BOX_MAX_WIDTH,0);

	ReadMessage(clanFinishSecessionMsg.szMsg,"szFinishSecessionMsg",g_ClanMessage);
	CheckMsgPos(&clanFinishSecessionMsg,BOX_MAX_WIDTH,0);

	ReadMessage(clanisCheckClanJangErrorMsg.szMsg,"szisCheckClanJangErrorMsg",g_ClanMessage);
	CheckMsgPos(&clanisCheckClanJangErrorMsg,BOX_MAX_WIDTH,0);

	ReadMessage(clanMoneyErrorMsg.szMsg,"szMoneyErrorMsg",g_ClanMessage);
	CheckMsgPos(&clanMoneyErrorMsg,BOX_MAX_WIDTH,0);

	ReadMessage(clanAbilityErrorMsg.szMsg,"szAbilityErrorMsg",g_ClanMessage);
	CheckMsgPos(&clanAbilityErrorMsg,BOX_MAX_WIDTH,0);

	ReadMessage(clanszRemoveShortClanWonMsg.szMsg,"szRemoveShortClanWonMsg",g_ClanMessage);
	CheckMsgPos(&clanszRemoveShortClanWonMsg,BOX_MAX_WIDTH,0);

	ReadMessage(clanRemoveShowrtClanWonResultMsg.szMsg,"szRemoveShowrtClanWonResultMsg",g_ClanMessage);
	CheckMsgPos(&clanRemoveShowrtClanWonResultMsg,BOX_MAX_WIDTH,0);

	ReadMessage(clanNoName.szMsg,"szNoName",g_ClanMessage);
	CheckMsgPos(&clanNoName,BOX_MAX_WIDTH,0);

	ReadMessage(clanLoading.szMsg,"szLoading",g_ClanMessage);
	CheckMsgPos(&clanLoading,BOX_MAX_WIDTH,0);

	ReadMessage(clanMsg6.szMsg,"szMsg6",g_ClanMessage);
	CheckMsgPos(&clanMsg6,BOX_MAX_WIDTH,0);

	ReadMessage(szDeleteChaReleaseBefore,"szDeleteChaReleaseBefore",g_ClanMessage);
	ReadMessage(szDeleteChaReleaseFinish,"szDeleteChaReleaseFinish",g_ClanMessage);
	ReadMessage(szDeleteChaSecessionBefore,"szDeleteChaSecessionBefore",g_ClanMessage);
	ReadMessage(szDeleteChaSecessionFinish,"szDeleteChaSecessionFinish",g_ClanMessage);
	
	ReadMessage(clanDeleteChaError.szMsg,"szDeleteChaError",g_ClanMessage);
	CheckMsgPos(&clanDeleteChaError,BOX_MAX_WIDTH,0);
	
	ReadMessage(clanMakeFinishClan.szMsg,"szMakeFinishClan",g_ClanMessage);
	CheckMsgPos(&clanMakeFinishClan,BOX_MAX_WIDTH,0);

	ReadMessage(szClanWon6Down,"szClanWon6Down",g_ClanMessage);

	ReadMessage(clanClanUserNoMakeMsg.szMsg,"szClanUserNoMakeMsg",g_ClanMessage);
	CheckMsgPos(&clanClanUserNoMakeMsg,BOX_MAX_WIDTH,0);

	ReadMessage(clanMakeFinishClanWon.szMsg,"szMakeFinishClanWon",g_ClanMessage);
	CheckMsgPos(&clanMakeFinishClanWon,BOX_MAX_WIDTH,0);

	ReadMessage(clanClanServerInspect.szMsg,"ClanServerInspect",g_ClanMessage);
	CheckMsgPos(&clanClanServerInspect,BOX_MAX_WIDTH,0);

	ReadMessage(clanClanUserRelease.szMsg,"szClanUserRelease",g_ClanMessage);
	CheckMsgPos(&clanClanUserRelease,BOX_MAX_WIDTH,0);

	ReadMessage(clanClanMakedowninfo.szMsg,"szClanMakedowninfo",g_ClanMessage);
	CheckMsgPos(&clanClanMakedowninfo,BOX_MAX_WIDTH,0);

	ReadMessage(clanClanUserReleaseMsg.szMsg,"szClanUserReleaseMsg",g_ClanMessage);
	CheckMsgPos(&clanClanUserReleaseMsg,BOX_MAX_WIDTH,0);

	ReadMessage(clanClanUserRemove.szMsg,"szClanUserRemove",g_ClanMessage);
	CheckMsgPos(&clanClanUserRemove,BOX_MAX_WIDTH,0);

	ReadMessage(clanClanWonOver.szMsg,"szClanWonOver",g_ClanMessage);
	CheckMsgPos(&clanClanWonOver,BOX_MAX_WIDTH,0);

	ReadMessage(clanMsg7.szMsg,"szMsg7",g_ClanMessage);
	CheckMsgPos(&clanMsg7,BOX_MAX_WIDTH,0);

	ReadMessage(clanNoLevel.szMsg,"szNoLevel",g_ClanMessage);
	CheckMsgPos(&clanNoLevel,BOX_MAX_WIDTH,0);

	ReadMessage(clanRemoveSecond.szMsg,"szRemoveSecond",g_ClanMessage);
	CheckMsgPos(&clanRemoveSecond,BOX_MAX_WIDTH,0);

	ReadMessage(clanRemoveSecondResult.szMsg,"szRemoveSecondResult",g_ClanMessage);
	CheckMsgPos(&clanRemoveSecondResult,BOX_MAX_WIDTH,0);

	ReadMessage(LeaveClanConfirm.szMsg,"szLeaveClanConfirm",g_ClanMessage);
	CheckMsgPos(&LeaveClanConfirm,BOX_MAX_WIDTH,0);

	ReadMessage(LeaveClanNoMoney.szMsg,"szLeaveClanNoMoney",g_ClanMessage);
	CheckMsgPos(&LeaveClanNoMoney,BOX_MAX_WIDTH,0);

	ReadMessage(LeaveClanSuccess.szMsg,"szLeaveClanSuccess",g_ClanMessage);
	CheckMsgPos(&LeaveClanSuccess,BOX_MAX_WIDTH,0);

	ReadMessage(LeaveClanNoLevel.szMsg,"szLeaveClanNoLevel",g_ClanMessage);
	CheckMsgPos(&LeaveClanNoLevel,BOX_MAX_WIDTH,0);

	ReadMessage(LeaveClanReConfirm.szMsg,"szLeaveClanReConfirm",g_ClanMessage);
	CheckMsgPos(&LeaveClanReConfirm,BOX_MAX_WIDTH,0);

	ReadMessage(NoLeaveClan.szMsg,"szNoLeaveClan",g_ClanMessage);
	CheckMsgPos(&NoLeaveClan,BOX_MAX_WIDTH,0);

	ReadMessage(LeaveClanMessage.szMsg,"szLeaveClanMessage",g_ClanMessage);
	CheckMsgPos(&LeaveClanMessage,BOX_MAX_WIDTH,0);

	ReadMessage(LeaveClanDownLevel.szMsg,"szLeaveClanDownLevel",g_ClanMessage);
	CheckMsgPos(&LeaveClanDownLevel,BOX_MAX_WIDTH,0);

	ReadMessage(SubChipAppoint.szMsg,"szSubChipAppoint",g_ClanMessage);
	CheckMsgPos(&SubChipAppoint,BOX_MAX_WIDTH,0);

	ReadMessage(SubChipAppointEnd.szMsg,"szSubChipAppointEnd",g_ClanMessage);
	CheckMsgPos(&SubChipAppointEnd,BOX_MAX_WIDTH,0);

	ReadMessage(SubChipRelease.szMsg,"szSubChipRelease",g_ClanMessage);
	CheckMsgPos(&SubChipRelease,BOX_MAX_WIDTH,0);

	ReadMessage(SubChipReleaseEnd.szMsg,"szSubChipReleseEnd",g_ClanMessage);
	CheckMsgPos(&SubChipReleaseEnd,BOX_MAX_WIDTH,0);

	ReadMessage(NoSubChip.szMsg,"szNoSubChip",g_ClanMessage);
	CheckMsgPos(&NoSubChip,BOX_MAX_WIDTH,0);
	
	ReadMessage(ClanIs4DayCheckMsg.szMsg,"szClanIs4DayCheckMsg",g_ClanMessage);
	CheckMsgPos(&ClanIs4DayCheckMsg,BOX_MAX_WIDTH,0);

	delete[] g_ClanMessage;
	g_ClanMessage = NULL;
	return 1;
}

int ReadMessage(char *save,char *savename,char *readbuf)
{
	char szTemp[256];
	char *pBuf;
	char szReadData[1024];
	int nCount =0;
	int nCount1 =0;
	BOOL bFlag = FALSE;

	ZeroMemory(szReadData,sizeof(szReadData));
	wsprintf(szTemp,"*%s",savename);

	pBuf = strstr(readbuf,szTemp);
    if(pBuf == NULL)
		return -1;

	pBuf = pBuf + lstrlen(szTemp) + 2;
	nCount = (int)(pBuf - readbuf);

	if(readbuf[nCount] == 0x0a)
		nCount++;
	while(1)
	{		
		if((readbuf[nCount] == 0x5c)) 
		{				
			szReadData[nCount1] = '\n';		
			nCount1++;				
			nCount +=3;			
			if(readbuf[nCount] == 0x0a)
			{	
				nCount++;
				continue;
			}			
			
		}
		if((readbuf[nCount] == 0x0d) ||(readbuf[nCount] == 0x0a)) 
			break;
		szReadData[nCount1] = readbuf[nCount];		
		nCount++;
		nCount1++;
	}

	lstrcpy(save,szReadData);
	return 1;
}

void MsgXsu_Ysu(CLANMSG* clanmsg, int *xsu, int *ysu)
{
	char strbuf[256], strbuf2[256];
	ZeroMemory(strbuf, sizeof(strbuf));

	int nCount = 0;
	int maxXsu = 0;
	int cntX= 0, cntY = 0;

	while(1)
	{
		strbuf[cntX] = clanmsg->szMsg[nCount];

		if(clanmsg->szMsg[nCount] =='\n')
		{
			strbuf[cntX] = 0;
			if(cntX>maxXsu)
			{
				maxXsu = cntX;
				lstrcpy(strbuf2,strbuf);
			}

			cntY++;
			cntX = -1;
		}

		if(clanmsg->szMsg[nCount] ==0x00)
		{
			strbuf[cntX] = 0;
			if(cntX>maxXsu)
			{
				maxXsu = cntX;
				lstrcpy(strbuf2,strbuf);
			}
			cntY++;
			break;
		}

		
		cntX++;
		nCount+=1;
	}

	*xsu = maxXsu;
	*ysu = cntY ;
}



void CheckMsgPos(CLANMSG* clanmsg,int width, int height)
{
	int nCount = 0;
	int nXMax = 0,nYMax;	
	int nX = 0;
	nX = width;
	nX = nX/2;
	int nY = 40;

	MsgXsu_Ysu(clanmsg, &nXMax, &nYMax);
	int strDotlen = nXMax*6;
	strDotlen /= 2;

	if(nYMax == 1) nY = 80;
	if(nYMax == 2 ) nY = 60;

	clanmsg->pos.x = (nX - strDotlen);
	clanmsg->pos.y = nY;
}



int g_nCount = 0;

#define DEBUGOPTION  "DDD2.txt"
BOOL	g_bDebugOption  = FALSE;
void ReadWEBDebugOption()
{
	HANDLE hFile = NULL;
	DWORD dwRead;
	char DebugOption;
	hFile = CreateFile( DEBUGOPTION, GENERIC_READ, FILE_SHARE_READ|FILE_SHARE_WRITE,NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL );
							
	if( hFile != INVALID_HANDLE_VALUE )
	{
		ReadFile(hFile,&DebugOption,1,&dwRead,NULL);
		CloseHandle(hFile);

		DebugOption = '1';
	}
	else 
		DebugOption = '0';

	if(DebugOption == '1') g_bDebugOption = TRUE;
	else g_bDebugOption = FALSE;
}

