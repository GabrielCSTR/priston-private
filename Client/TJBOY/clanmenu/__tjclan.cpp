//====================================================================
//ktj : runmap3d.suo���϶����� ���̺갡�ȵǴ°�찡 �����Ƿ� �׷����� �� ������ �����
//====================================================================
//4.01 P10.47
//sinMain.cpp, sinInterFace.cpp���� ���
#define TJCLAN_CPP
#include "tjclanDEF.h"

#ifdef USE_PROSTONTALE		//=========== �������ϼҽ��ΰ��

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




extern HWND hTextWnd;
extern HWND hFocusWnd;

extern char UserAccount[256];		//id�� ����ִ� ����
extern char	szConnServerName[16];	//������ �����̸��� ����ִ� ����




#define MOUSE0() TJmb[0]


#else						//=========== �������ϼҽ��� �ƴѰ��

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

char UserAccount[256];		//id�� ����ִ� ����
extern char UserAccount[256];		//id�� ����ִ� ����
char szConnServerName[16];	//������ �����̸��� ����ִ� ����
extern char szConnServerName[16];	//������ �����̸��� ����ִ� ����

extern int MouseButton[3] ;	//���콺��ư����ýũ : winmain.cpp�� ������
extern int MouseDblClick ;		//tjclan.cpp


extern HWND    g_hwnd;
extern POINT	pCursorPos;
extern HINSTANCE g_hInst;


#define MOUSE0() MouseButton[0]


#endif


int ClanCharMove=0;	//Ŭ���޴��Ǿ��� ���콺�� �����ӿ� ĳ���Ͱ� ��������� �Ѵ�.
int ClanCLCharMove=0;//Ŭ��ä�ø���Ʈ�޴��Ǿ��� ���콺�� �����ӿ� ĳ���Ͱ� ��������� �Ѵ�.


int  banisF[100];

//int TJwheel=0; //ktj : �ٵ���Ÿ
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
	//ktj : Ŭ���󿡼��� ���� ��ġ�� �˾Ƴ���.
	Interface_clanmenu.CLANmenu_clanPOSITION();
}





/*==================================================================================
//
// �ܺο��� ���Ǵ� Ŭ���� ���� ���� �Լ���								   start
//
==================================================================================*/


/*///////////////////////////////////////////////////////////////////////////
: Ŭ�󽺸� : 
: �� �� �� : Ŭ�� �� ó�� ����
///////////////////////////////////////////////////////////////////////////*/

//ktj : Ŭ���޴� �������̽� init
//setN : 0 : ���� ����  1: �ι�°����(��� 
void clanMENU_INIT(int setN)
{	
	if(!bCheckHostNameandPort) return;



	switch(setN) {
	case -1:				//�����δ� �����Կ� ����
		ZeroMemory(&ClanWonList,  sizeof(CLANWONLIST ));

		Interface_clanmenu.CLANmenu_INIT();
		//ktj : Ŭ���󿡼��� ���� ��ġ�� �˾Ƴ���.
		Interface_clanmenu.CLANmenu_clanPOSITION();
		break;


	case 0:				//��ó������ : ĳ���� ������������

		void CreateSaveData_dir();
		CreateSaveData_dir();			//savedata/clandata����


		ZeroMemory(&ClanWonList,  sizeof(CLANWONLIST ));
		Interface_clanmenu.CLANmenu_INIT();

		break;

	case 1:				//�� ���� ���۽� ����
	#ifdef USE_PROSTONTALE		//=========== �������ϼҽ��ΰ��

		cBaseMenu.Load2();
		cClanChatting.Load2();
		Interface_clanmenu.Init2();	
	

		//setN�� 0�� ��� ĳ���̸��� ���� �־�� �Կ� ũ�� �����Ұ�.
		Interface_clanmenu.SetUserData(UserAccount, sinChar->szName, "����", 
			sinChar->Money,500000); //6�� ����

		//ktj: �ӽ÷� ����.
		//ktj : Ŭ���󿡼��� ���� ��ġ�� �˾Ƴ���.
		Interface_clanmenu.CLANmenu_clanPOSITION();
		
	
	#endif
		break;
	}
}


//hoLogin.cpp���� �����.
int isDELETE_character(char *charName) 
{
	if(!bCheckHostNameandPort) return 1;		//1�� ĳ���͸� �������ȴٴ¶�


	int web_DB_state_FLAG_WAIT();
	while(1) {
		if(web_DB_state_FLAG_WAIT() == 1) 
			break;
	}

	Interface_clanmenu.SetUserData(UserAccount, charName, "����", 500000   ,500000); //6�� ����

	//ktj : Ŭ���󿡼��� ���� ��ġ�� �˾Ƴ���.
	Interface_clanmenu.CLANmenu_clanPOSITION();
	cldata.myPosition = 0;//CLANNO_REGESTER;
	while(1) {
		web_DB_main();					//web db�� ����ϴ� Ŭ�� �޴������� �Ҹ�����.	
		cIsClanMember.Main();			//ktj : Ŭ������ ������ üũ ����

		if(cldata.myPosition != 0) 
			break;
	}

	while(1) {
		if(web_DB_state_FLAG_WAIT() == 1) 
			break;
	}

	/*
	#define CLANUSER					100		//�Ϲ�����
	#define CLANCHIP					101		//��
	#define CLANNO_REGESTER				102		//�������
	#define CLAN_NOCONNECT				103		//����Ʈ�� �ȵǼ� �����Ұ�
	*/
	return cldata.myPosition;
}



void CLAN_MENU::Init2()
{
	#ifdef USE_PROSTONTALE		//=========== �������ϼҽ��ΰ��

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


	cBaseMenu.copy_LoadResource2(&cIsClanMember);		//���ҽ� ī��
	cBaseMenu.copy_LoadResource2(&cClanChip);		//���ҽ� ī��
	cBaseMenu.copy_LoadResource2(&cClanUser);		//���ҽ� ī��
	cBaseMenu.copy_LoadResource2(&cClanMake);		//���ҽ� ī��
	cBaseMenu.copy_LoadResource2(&cClanReport);		//���ҽ� ī��
	cBaseMenu.copy_LoadResource2(&cClanChatting);		//���ҽ� ī��
	cBaseMenu.copy_LoadResource2(&cClanDeleteCha);		//���ҽ� ī��
	cBaseMenu.copy_LoadResource2(&cClanJoin);		//���ҽ� ī��	
#endif
}

void CLAN_MENU::CLANmenu_INIT()
{
	if(!bCheckHostNameandPort) return;
	//g_ViewClanInfo.LoadData();

	Init();


#ifdef  USE_PROSTONTALE

	//SetUserData(UserAccount, sinChar->szName, szConnServerName); //6�� ����
	//ktj : �̰� ����.
	//SetUserData(UserAccount, sinChar->szName, szConnServerName, sinChar->Money,1000); //6�� ����

	//ktj : ����
	SetUserData(UserAccount, sinChar->szName, "����", sinChar->Money,500000); //6�� ����
	//SetUserData(UserAccount, "��ƴ�", "����", 500000 ,500000); //6�� ����

	//SetJoinData("������","��Ʈ��","��Ʈ");

#else
	
	strcpy(szConnServerName,"�ϳ�");		
	SetUserData("yung6","��6","����",500000,100000);
	SetUserData("ddd","����","����",500000,100000);
	//SetUserData("aaa","������","�̰�",500000,100000);
	
	//Ŭ�������� ��ϵ� id��	

#endif
}




/*///////////////////////////////////////////////////////////////////////////
: Ŭ�󽺸� :
: �� �� �� : Ŭ�������μ��� ��ġ�� �˾Ƴ�.
///////////////////////////////////////////////////////////////////////////*/
int CLAN_MENU::CLANmenu_clanPOSITION()
{
	if(!bCheckHostNameandPort) {
		cldata.myPosition = CLAN_NOCONNECT;
		return 0;
	}


	if(OpenFlag==1) return 0;		//�� �޴��� ������������ ������.
	
	C_menuN2= 0;
	OpenFlag = 1;
	joinAnswer = 0;
	C_menuN = CLAN_isClanWon;
	

	menuInit(C_menuN );

	ClanCharMove = 1;			//ktj : ���콺�� ýũ�ϴ� �ڽ�ýũ 
	return 1;
}


/*///////////////////////////////////////////////////////////////////////////
: Ŭ�󽺸� :
: �� �� �� : NPC�� ��������
///////////////////////////////////////////////////////////////////////////*/
void CLANmenu_meetNPC()	//newplay.cpp���� �����.
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
		return 0;		//�� �޴��� ������������ ������.
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

	ClanCharMove = 1;			//ktj : ���콺�� ýũ�ϴ� �ڽ�ýũ 
	return 1;
}






/*///////////////////////////////////////////////////////////////////////////
: Ŭ�󽺸� :
: �� �� �� : Ŭ�������� ä�ø���Ʈ�� ����
///////////////////////////////////////////////////////////////////////////*/
void CLANmenu_ChatList(int sw)	//newplay.cpp���� �����.l
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
	case 0: //��ũ�� �ǰ�
		
		cClanChatting.InitClanChatList();
		if(bIsReadData) ChatList_CmenuN = CLAN_DISPLAY_OPEN;
		else	ChatList_CmenuN = CHATLIST_READDATA;
		break;
	case 1: //��ũ�� �ȵǰ�
		cClanChatting.NoScroll();
		//if(bIsReadData) ChatList_CmenuN = CLAN_DISPLAY_OPEN;
		//else	ChatList_CmenuN = CHATLIST_READDATA;		

		ChatList_CmenuN = CLAN_DISPLAY_INFO;				
		cClanChatting.menuInit(ChatList_CmenuN);

#ifdef USE_PROSTONTALE		//=========== �������ϼҽ��ΰ��
		
#else
	OpenFlag = 1;
	C_menuN = ChatList_CmenuN;
	
#endif


		break;
	}
}




void CLANmenu_ChatList_Main()	//newplay.cpp���� �����.l
{
	cClanChatting.Main();			//Ŭ�� ä�ø���Ʈ
}
void CLANmenu_ChatList_Draw()	//newplay.cpp���� �����.l
{
	cClanChatting.Draw();			//Ŭ�� ä�ø���Ʈ
}


/*///////////////////////////////////////////////////////////////////////////
: Ŭ�󽺸� :
: �� �� �� : cldata������Ʈ �Ҷ�
///////////////////////////////////////////////////////////////////////////*/
void Updatecldata()
{
	//Interface_clanmenu.Updatecldata();
	g_UpdateCldata.Updatecldata();
}


/*///////////////////////////////////////////////////////////////////////////
: Ŭ�󽺸� : �����ϴ� �޴���.
: �� �� �� : �Ϲ��ο��� Ŭ���� ������ �����ϸ� �����Ѵٴ� �޴��� ���.
///////////////////////////////////////////////////////////////////////////*/

//�����޴� ����� ����ϴ� �Լ�
void ClanJoin(char *oneClanName, char *oneChipCharid)
{
	//Interface_clanmenu.SetJoinData("��Ʈ��","��Ʈ");
	Interface_clanmenu.SetJoinData(oneClanName,oneChipCharid);
	Interface_clanmenu.ClanJoin();
}

//ktj : ���������ڰ� �������ִ� ��(���Լ��� ����� �������ش�.)
//0:��� 1:OK
int JoinAnswer()
{
	return cClanJoin.nJoinAnswer;
}

void CLAN_MENU::ClanJoin()
{
	if(OpenFlag==1) return;
	C_menuN2 = 0;
	OpenFlag = 1;
	ClanCLCharMove = 1;			//ktj : ���콺�� ýũ�ϴ� �ڽ�ýũ 	
	C_menuN = CLAN_JOIN_before;
	
}

/*///////////////////////////////////////////////////////////////////////////
: Ŭ�󽺸� :
: �� �� �� : Ŭ������ Ŭ������ ��Ͻ�ų��
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
	ClanCLCharMove = 1;			//ktj : ���콺�� ýũ�ϴ� �ڽ�ýũ 	
	C_menuN = CLAN_JOIN_chip;
}



/*///////////////////////////////////////////////////////////////////////////
: Ŭ�󽺸� :
: �� �� �� : ĳ���� ������
///////////////////////////////////////////////////////////////////////////*/
void ktj_IMSI_DELETE()
{
	//extern char UserAccount[256];		//id�� ����ִ� ����
	//extern char szConnServerName[16];	//������ �����̸��� ����ִ� ����
	CLANmenu_DeleteCha_SetCharacter(UserAccount, szConnServerName, "��ƴ�");
}



//ktj :  1. ĳ�� ��������� �����ϴ� �Լ�
void CLANmenu_DeleteCha_SetCharacter(char *id, char *gserver, char *chaname)
{
	cClanDeleteCha.SetDeleteChaInfo(id, gserver, chaname);

	//ktj : 2. ����� �޴��� �����Ѵ�.
	Interface_clanmenu.CLANmenu_DeleteCha();
}

//ktj : ĳ�� ��������� �Ҹ���� �Լ�
void CLAN_MENU::CLANmenu_DeleteCha()
{
	C_menuN2 = 0;
	OpenFlag = 1;
	ClanCLCharMove = 1;			//ktj : ���콺�� ýũ�ϴ� �ڽ�ýũ 	
	C_menuN = CLAN_DELETECHA_START;

	cClanDeleteCha.SetHowDeleteChaFlag();
}

//ktj : 3. ���� �÷��׸� ���� 2�̸� ĳ���� �����ϰ� 3�̸� ���� ����.(0,1�̸� 2,3�ɶ����� ��ٸ���)
int CLANmenu_DeleteCha_flag()
{
	//������ : 0
	//������ : 1
	//���� ok : 2
	//���� �ȵ� : 3
	return cClanDeleteCha.GetHowDeleteChaFlag();
}



//////////////////////////////////////////////////////////////////////////////////
//Ŭ�� ���� �������
//
/////////////////////////////////////////////////////////////////////////////////
int ReadClanInfo(DWORD dwClanNum)
{
	if(OpenFlag==1) return -1;		//�� �޴��� ������������ ������.

	g_ViewClanInfo.SearchClan(dwClanNum);
	BOOL bFlag;
	bFlag = g_ViewClanInfo.GetFlag();  //�ϵ忡 ����Ǿ���� �ƴϸ� �ٿ� �޾ƾ� �ϴ��� üũ 
	
	if(!bFlag)
	{
		//web���� �ٿ����.
		g_ViewClanInfo.DownLoadClanInfo(dwClanNum);
	}
	return ClanInfo_nNum;		//0~99;
}







//==================================================================================
// �ܺο��� ���Ǵ� Ŭ���� ���� ���� �Լ���								    end
//=================================================================================







/*==================================================================================
//
// Ŭ���޴�																	   start
//
==================================================================================*/
CLAN_MENU::CLAN_MENU()
{
	nClanWon_Num = 0;
	nScl_Bar = 0;           //��ũ�ѹ�
	g_nClanIconNum;			//���������� �Ѽ�
	g_HelpIconNumber = 0;    
	g_HelpDisPlay = 0;

}

CLAN_MENU::~CLAN_MENU()
{
}


//���콺��ġ�� ýũ������ϴ°� hoLinkHeader.cpp���� ���
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


	//Ŭ���޴����� �����ʿ� ���콺�� �������� ���޾ȵǵ����Ѵ�.
	clanBoxPos.x = BackStartPos.x;
	clanBoxPos.y = BackStartPos.y;

	//Ŭ��ä�� ����Ʈ�޴����� �����ʿ� ���콺�� �������� ���޾ȵǵ����Ѵ�.
	clanCLBoxPos.x = 540+60;		//60�� �׸��� �������� �پ��ֱ� ������
	clanCLBoxPos.y = CHATLIST_BOX_Y;


	

	ZeroMemory(szRemoveClanWon,sizeof(char)*500);	
	ZeroMemory(ClanHelpIcon,sizeof(CLANHELPICON)*CLANHELPICON_NUM);		
	ZeroMemory(cldata.szJoinClanName,sizeof(char)*64);   //���� Ŭ�� �̸�
	ZeroMemory(cldata.ChaName,sizeof(char)*64);  //�����ϴ� ���� ĳ���� �̸�
	ZeroMemory(cldata.szJoinClanChipName,sizeof(char)*64);   //�����ϴ� Ŭ���� �̸�
	ZeroMemory(szReconfReleaseMsg,sizeof(char)*2048);

	
	nClanWon_Num = 0;			//Ŭ�����Ľ��� Ŭ������ ����(Ŭ��������)
	nReleaseClanWon = 0;		//���� Ŭ����
	membmp = new MENUBMP;
	
	//hMark = NULL;

	Load();	
	cClanChatting.Load();

	//ktj : �޴� ���� Ŭ�� ���� ===================
	
	cBaseMenu.Load();

	
	cIsClanMember.Init(1);
	cIsClanMember.setParent(&cBaseMenu);
	cBaseMenu.copy_LoadResource(&cIsClanMember);		//���ҽ� ī��

	cClanChip.Init(1);
	cClanChip.setParent(&cBaseMenu);
	cBaseMenu.copy_LoadResource(&cClanChip);		//���ҽ� ī��
	cBaseMenu.SetBase(&cClanChip);

	cClanUser.Init(1);
	cClanUser.setParent(&cBaseMenu);
	cBaseMenu.copy_LoadResource(&cClanUser);		//���ҽ� ī��
	cBaseMenu.SetBase(&cClanUser);

	cClanMake.Init(1);
	cClanMake.setParent(&cBaseMenu);
	cBaseMenu.copy_LoadResource(&cClanMake);		//���ҽ� ī��

	cClanReport.Init(1);
	cClanReport.setParent(&cBaseMenu);
	cBaseMenu.copy_LoadResource(&cClanReport);		//���ҽ� ī��


	cClanChatting.Init(1);
	cClanChatting.setParent(&cBaseMenu);
	cBaseMenu.copy_LoadResource(&cClanChatting);		//���ҽ� ī��
	cBaseMenu.SetBase(&cClanChatting);


	cClanDeleteCha.Init(1);
	cClanDeleteCha.setParent(&cBaseMenu);
	cBaseMenu.copy_LoadResource(&cClanDeleteCha);		//���ҽ� ī��

	cClanJoin.Init(1);
	cClanJoin.setParent(&cBaseMenu);
	cBaseMenu.copy_LoadResource(&cClanJoin);		//���ҽ� ī��	
	

}


/*///////////////////////////////////////////////////////////////////////////
: �Լ���   : menuInit
: �� �� �� : �޴� �Ѱ� Init
: �� ȯ �� :
: �Ķ���� :
///////////////////////////////////////////////////////////////////////////*/
void CLAN_MENU::menuInit(int num)
{
	
	cIsClanMember.menuInit(num);		//Ŭ������� �޴� initialize
	cClanMake.menuInit(num);		//Ŭ������� �޴� initialize
	cClanChip.menuInit(num);		//Ŭ���� �޴� initialize
	cClanUser.menuInit(num);		//Ŭ������ �޴� initialize
	cClanChatting.menuInit(num);
	cClanDeleteCha.menuInit(num);
	cClanJoin.menuInit(num);
}







/*///////////////////////////////////////////////////////////////////////////
: Ŭ�� ��: 
: �� �� �� : ���콺�� ���� �޴� ��ȣ ýũ�Լ�.
: �� ȯ �� :
:�Ķ����  :
///////////////////////////////////////////////////////////////////////////*/
int CLAN_MENU::chkMenu(int x, int y, RECT *r) 
{
	if(r->left <= x   &&   x<= r->right ) 
		if(r->top <= y   &&   y<= r->bottom ) 
			return 1;
	return 0;			//�ƹ��͵� ���þ���.
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





//���� �����ϸ� �������� ������� �ߴ� �޴���.(���� netplay.cpp���� �����)
void menu_joinOpen(char *chipCharID)
{
	//Interface_clanmenu.menu_joinOpen(chipCharID);
}


//���θ޴��� Ŭ������ �����ϸ� �������� ������� �޴��� ���.
int CLAN_MENU::menu_joinOpen(char *chipCharID)		//���� ĳ���� id
{
	/*
	if(OpenFlag==1) return 0;					//�� �޴��� ������������ ������.
	if( cldata.myPosition == 100 ||				//100(Ŭ����), 101:Ŭ�������� �����Ҽ� ����.
		cldata.myPosition == 101)				return 0;

	strcpy(cldata.chipCharID, chipCharID);
	C_menuN   = CLAN_JOIN_before;		//���ο� �������� ����.
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
	Interface_clanmenu.menu_joinOpen_Chip(isOK, clanWonID, clanWonCharID);		//���� ĳ���� id;
}


//�������� ����� OK�ϸ� �׸����� Ŭ�������� �ǵ��ƿ� Ŭ������ ���Խ�Ű�� �޴���.
//���� : ȭ��󿡴� �޴��� ��������.
int CLAN_MENU::menu_joinOpen_Chip(int joinOK, char *clanWonID, char *clanWonCharID)		//���� ĳ���� id
{
	if(OpenFlag==1) return 0;		//�� �޴��� ������������ ������.

	if(cldata.myPosition != 101) return 0;	//101:Ŭ������ ��밡���� �޴���.

	/*
	if(joinOK==0) {
		C_menuN= CLAN_JOIN_chip_NO	;		//Ŭ���� �����ϱ⸦ �ź���.
		C_menuN2= -1;
	}
	else {
		*/
		C_menuN = CLAN_JOIN_chip		;	//Ŭ���� ��Ͻ�Ų��.
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
	web_DB_main();					//web db�� ����ϴ� Ŭ�� �޴������� �Ҹ�����.	

	//char		szErrorMsg[256];
	if(OpenFlag==0) return 0;		//�� �޴��´�����


	switch(sw) {
	case PARTY_START:				//ó�� �Ҹ��������� ó��
		return 1;
	case PARTY_END:					//������ �Ҹ��������� ó��
		return 1;
	}

	//ClanCharMove = 1;
									//ktj : auth.cpp�� web_DBýũ����.
	cBaseMenu.Main();				//ktj : ���� �޴� �� ����
	cIsClanMember.Main();			//ktj : Ŭ������ ������ üũ ����
	cClanReport.Main();				//ktj : �޽��� ó���� ����
	cClanMake.Main();				//ktj : Ŭ���� �������� ����
	cClanChip.Main();				//Ŭ�� Ĩ �޼��� ó��
	cClanUser.Main();				//Ŭ�� ���� �޼���ó��
	cClanJoin.Main();
#ifdef USE_PROSTONTALE		//=========== �������ϼҽ��ΰ��

	//cClanChatting.Main();			//Ŭ�� ä�ø���Ʈ
#else
	cClanChatting.Main();			//Ŭ�� ä�ø���Ʈ
#endif

	cClanDeleteCha.Main();            //ĳ���� ������
	return TRUE;
}




char loadis[256] = {0,};
char loadis2[256] = {0,};
char updateis[256] = {0,};


int CLAN_MENU::Draw()
{	
	if(bip_port_error) return 0;
	
	/*
	//ktj : �ӽ÷� ����ýũ
	char buf[256];
	
	wsprintf(buf, "bug :  %d ================ : (myPos:%d ) (Ŭ����ũ��ȣ%s,%d)  cldata.money %d ", C_menuN, cldata.myPosition, cldata.ClanMark, cldata.intClanMark, cldata.money);
	Draw_C_Text(buf, 0,0,   0);
	

	wsprintf(buf, "cldata.szID %s  cldata.ChaName %s cldata.name %s (C_menuN %d C_menuN2 %d) ================ ", cldata.szID,cldata.ChaName, cldata.name, C_menuN, C_menuN2);
	Draw_C_Text(buf, 0,16,   0);
	*/

	/*
	wsprintf(buf, "Ŭ��ä�ø���Ʈ�ε��  %s ================ ", loadis);
	Draw_C_Text(buf, 0,32,   0);
	wsprintf(buf, "Ŭ��ä�ø���Ʈ�ε�2   %s ================ ", loadis2);
	Draw_C_Text(buf, 0,32+16,   0);

	wsprintf(buf, "������Ʈī��Ʈ %s ================ ", updateis);
	Draw_C_Text(buf, 0,64,   0);
	*/
	
	
	


	

	//InvalidateRect(g_hwnd,NULL,1);
	if(OpenFlag==0) return 0;	


#ifndef USE_PROSTONTALE		//=========== �����Լ�

	window_renderINIT();			//ó�� �ѹ�������.
	HDC hdc = GetDC(g_hwnd);	
	HDC sorDC;
	sorDC  = CreateCompatibleDC(hdc);
	HDC destdc=CreateCompatibleDC(hdc);
	SelectObject(destdc, Dback.hb );
	PatBlt(destdc,0,0,800,600,PATCOPY);
	char szBuf[256];
	extern POINT	pCursorPos;
	
	// 0 : �۾������ϱ��� 1: �ٿ�ε� ������ 2 : �۾��Ϸ� 3: ����
	wsprintf(szBuf,"C_menuN : %d  ,x = %d, y = %d , ���� ���� : %d Ŭ�� �̸� : %s",
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
	case CLAN_MAKE_is:		//Ŭ���Ἲ�ǻ� Ȯ�� Y/N

		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();				
		break;
	case CLANMAKE_NOMONEY:
	case CLAN_MONEY_is:		// ��������ǻ繯��

		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();

		break;
	case CLAN_NAME_is:		//Ŭ���̸� ����.
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
	case CLAN_MARK_expl:		//Ŭ����ũ����
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		
		break;
	case CLAN_INSPECTION_expl:		//�ɻ�Ⱓ����
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		
		break;
	case CLAN_NotMake:	//Ŭ���Ἲ���ϴ� ���ư���
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		break;
	case CLANMAKE_DOWN_INFO:
	case CLANMAKE_READ_CLANMARK:
	case CLAN_MAKE_FINISH:
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		break;
	case CLAN_AllEnd:	//Ŭ�� ������ Ŭ�����ϴ¼��úκ�.
		break;


	case CLAN_ERROR:
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		break;


	//============����޴�
	//case CLAN_CHIP_ReadDATA:		
	//	Draw_C_menuN();
	//	break;
	case CLAN_CHIP:
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		break;
		//ycy
		//========= �߹�
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
	//=========Ĩ �����޴�
	case CLANUSER_REMOVE ://Ŭ������ �߹���������
	case	CLANUSER_AUTORELEASE://�ڵ���ü
	case CLAN_USER:
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		break;
	//Ŭ���� ���� �Ἲ ����
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

	//Ŭ������ ���Ա����Ҷ� �ߴ� �޴�
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
#ifdef USE_PROSTONTALE		//=========== �������ϼҽ��ΰ��
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

#ifndef USE_PROSTONTALE		//=========== �����Լ�
	window_renderFLIP();
#endif

	return TRUE;
}


//sw==0 : �Ϲ� sw==1: Ű�Է��� �޴°�� sw==2: Ŭ���̸��� Ÿ��Ʋ�� �������(�׸���ó��)
void CLAN_MENU::Draw_C_Text(char *str, int x, int y, int sw=0)
{
#ifdef USE_PROSTONTALE		//=========== �������ϼҽ��ΰ��
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
				SetTextColor( hdc, RGB(100, 100, 100));	//�׸��ڿ� ���ڻ�
				//SetTextColor( hdc, RGB(255, 255,255));	//�׸��ڿ� ���ڻ�
				TextOut(hdc, x+1, y+1, strbuf, lstrlen(strbuf));

				SetTextColor( hdc, RGB(230, 255, 240));	//�Ϲݱ��ڻ�
				TextOut(hdc, x, y, strbuf, lstrlen(strbuf));
			}
			else     {
				SetTextColor( hdc, RGB(230, 255, 240));	//�Ϲݱ��ڻ�
				TextOut(hdc, x, y, strbuf, lstrlen(strbuf));
			}
			
			/*
			if(sw==2){
				SetTextColor( hdc, RGB(255, 255, 255));	//Ŭ���̸��Է½� ���				
			}
			else {
				SetTextColor( hdc, RGB(230, 255, 240));	//�Ϲݱ��ڻ�
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






//ycy : �ڽ� �׸���
int CLAN_MENU::DrawBox(int x,int y,int x_width,int y_height)
{

	isDrawClanMenu = 1;


#ifdef USE_PROSTONTALE		//=========== �������ϼҽ��ΰ��

	#define BOXFONTSIZE 64

	if(lpD3DDevice == NULL)
		return FALSE;

	lpD3DDevice->BeginScene();


	//�޹�����
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
		//���� ����
		sinDrawTexImage( hBox2, (float) sx, (float)y, 32, 32,
				(float)0,(float)0,  
				(float)0, (float)0, (float)32, (float)32,
				255);
		
		//�Ʒ��� ����
		sinDrawTexImage( hBox8, (float)sx, (float)( ey ), 32, 64,
				0,0,
				0, 0, 32, 64,
				255);
				
		sx+=32;
	}

	int sy = y+32;
	int ex = x+(32*x_width) + 64 ;
	for(line=0; line<y_height; line++) {
		//�����ʶ���
		sinDrawTexImage( hBox4, (float)x, (float)sy, 64, 32,
				0,0,
				0, 0, 64, 32,
				255);
		//���� ����
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

	SelectObject(destdc, Dback.hb );		//off��ũ������.
	//SelectObject(sorDC, backBMP );

	/*
	for(int i=0; i<coordNum; i++) {

		BitBlt(
			destDC,
			coordB[i].left,coordB[i].top,
			//���� : ������.
			coordB[i].right, coordB[i].bottom,	//offscr�� ����â���� ī��
			sorDC,
			coordB[i].left,coordB[i].top,
			SRCCOPY);

	}

	
	*/


	//���� top
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

	//������ top

	SelectObject(sorDC, hBox3 );
	GetObject(hBox3,sizeof(BITMAP),&bit);	
	bx = bit.bmWidth;
	by = bit.bmHeight;	
	StretchBlt(destdc,x+nTotal_Width,y,bx,by,sorDC,0,0,bx,by,SRCCOPY);


    //���� �׵θ�

	for(i=0; i< y_height; i++)
	{
		SelectObject(sorDC, hBox4 );
		GetObject(hBox4,sizeof(BITMAP),&bit);	
		bx = bit.bmWidth;
		by = bit.bmHeight;
		nTotal_Height +=by ;
		StretchBlt(destdc,x,y+BOXCORNER_HEIGHT+(by*i),bx,by,sorDC,0,0,bx,by,SRCCOPY);
	}



	
	
	//���� BOTTOM 	
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

	//������ BOTTOM
	SelectObject(sorDC,hBox9);
	GetObject(hBox9,sizeof(BITMAP),&bit);	
	bx = bit.bmWidth;
	by = bit.bmHeight;	
	StretchBlt(destdc,x+nTotal_Width,y +BOXCORNER_HEIGHT+nTotal_Height,bx,by,sorDC,0,0,bx,by,SRCCOPY);	

 
	//������ �׵θ�
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
: Ŭ�� ��: class CLAN_MENU
: �� �� �� : 
: ��    �� :
: ��    �� :
: �� ȯ �� :
: ��    �� : ��db�� ����� ����Ÿ�� �̾Ƴ��� �Ұ�� �� Ŭ�󽺸� �̿��Ѵ�.
: ��    �� :
: PROJECT  :
///////////////////////////////////////////////////////////////////////////*/
void CLAN_MENU::Draw_C_menuN()
{		
	cBaseMenu.Draw();
	cClanChip.Draw();	
	cClanUser.Draw();	
	cClanMake.Draw();	
	cClanReport.Draw();
#ifdef USE_PROSTONTALE		//=========== �������ϼҽ��ΰ��
#else
	cClanChatting.Draw();
#endif
	cClanJoin.Draw();
}


//=============��ο� ���� �Լ� ==================================================================end









/*///////////////////////////////////////////////////////////////////////////
: Ŭ�� ��: Ŭ�� ��Ʈ��ó ����Ÿ ���� �Լ���
: �� �� �� : 
: �� ȯ �� :
///////////////////////////////////////////////////////////////////////////*/
//���� id, ĳ���� id, ������ �̸�.
void CLAN_MENU::SetUserData(char* id, char* chaname, char* gserver,int money, int ability)
{
	strcpy(cldata.szID,  id);
	strcpy(cldata.ChaName, chaname);
	strcpy(cldata.gserver, gserver);

	cldata.money = money;
	//ktj : �ӽ�
	//if(cldata.money ==0) cldata.money = 100000;
	cldata.ability = ability;
}



//������ �޴� ������׿��� ����Ÿ
void CLAN_MENU::SetJoinData(char *joinclanname, char *joinclanchip)
{
	strcpy(cldata.szJoinClanName,    joinclanname);			//���Ե� Ŭ�� �̸�
	strcpy(cldata.szJoinClanChipName,joinclanchip);		//���Ե� Ŭ���� Ŭ���� id
}











#ifdef USE_PROSTONTALE		//=========== �������ϼҽ��ΰ��

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




#ifdef USE_PROSTONTALE		//=========== �������ϼҽ��ΰ��
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
                        "����ü" );

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
                        "����ü" );

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
#ifdef USE_PROSTONTALE		//=========== �������ϼҽ��ΰ��

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
	//Ŭ�� ������
	hSecession[0] = LoadDibSurfaceOffscreen("image\\clanImage\\chipbutton\\s.bmp");
	hSecession[1] = LoadDibSurfaceOffscreen("image\\clanImage\\chipbutton\\s1.bmp");
	//�߹�,â�� ����
	hIcon = LoadDibSurfaceOffscreen("image\\party\\party_man_0.bmp");
	hIcon_Click = LoadDibSurfaceOffscreen("image\\party\\party_man_1.bmp");

										
	hClose[0] = LoadDibSurfaceOffscreen("image\\clanImage\\MessageBox\\c.bmp");
	hClose[1] = LoadDibSurfaceOffscreen("image\\clanImage\\MessageBox\\c1.bmp");
	//����
	hHelp1 = LoadDibSurfaceOffscreen("image\\Sinimage\\chipbutton\\help1.bmp");


	//hButton_Box = LoadDibSurfaceOffscreen("image\\Sinimage\\Help\\box-test-title2.bmp");
	hClanTitle = LoadDibSurfaceOffscreen("image\\clanImage\\chipbutton\\title.bmp");



	//�߹�޴��ȿ��� �߹� ��ư
	hRemoveToMenu[0]= LoadDibSurfaceOffscreen("image\\clanImage\\MessageBox\\Button_deport_Glay.bmp");
	hRemoveToMenu[1] = LoadDibSurfaceOffscreen("image\\clanImage\\MessageBox\\Button_deport_Yellow.bmp");

	//��ũ�ѹ�
	hScl_Bar= LoadDibSurfaceOffscreen("image\\clanImage\\chipbutton\\scl_bar.bmp");
	hScl_icon = LoadDibSurfaceOffscreen("image\\clanImage\\chipbutton\\msBox.bmp");
	
	hClanNameInput = LoadDibSurfaceOffscreen("image\\clanImage\\chipbutton\\clan_name.bmp");

	//====Ŭ�� ���ϼ��� �κ�
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

	//Ŭ�� ������
	hSecession[0] = (HBITMAP)LoadImage(NULL,"image\\clanImage\\chipbutton\\s.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);

	hSecession[1] = (HBITMAP)LoadImage(NULL,"image\\clanImage\\chipbutton\\s1.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);
//�߹�,â�� ����
	hIcon = (HBITMAP)LoadImage(NULL,"image\\party\\party_man_0.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);
	hIcon_Click = (HBITMAP)LoadImage(NULL,"image\\party\\party_man_1.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);
//�߹�޴��ȿ��� �߹� ��ư
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
	//����
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
	//====Ŭ�� ���ϼ��� �κ�
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



//simMain.cpp���� �ҷ��� Ŭ���� �Ѵ�.
void clanMENU_close()
{
	Interface_clanmenu.Close();
}

void CLAN_MENU::Close()
{
	#ifdef USE_PROSTONTALE		//=========== �������ϼҽ��ΰ��

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

	//�߹�
	if(	hIcon ) {   hIcon->Release();  hIcon = NULL;}
	//����
	if(	hHelp1 ) {   hHelp1->Release();  hHelp1 = NULL;}

	if(	hButton_Box) {   hClanTitle ->Release();  hClanTitle = NULL;}
	if(	hClanTitle ) {   hClanTitle ->Release();  hClanTitle = NULL;}


	//ygy ��ũ��
	if(	hScl_Bar) {   hScl_Bar->Release();  hScl_Bar = NULL;}
	if(	hScl_icon ) {   hScl_icon->Release();  hScl_icon = NULL;}

	//ygyŬ���̸� �Է� �̹���
	if(	hClanNameInput ) {   hClanNameInput->Release();  hClanNameInput = NULL;}*/
	


	if(cldata.hClanMark) { cldata.hClanMark->Release(); cldata.hClanMark = NULL;}
	if(cldata.hClanMark16) {cldata.hClanMark16->Release(); cldata.hClanMark16 = NULL;}

	cClanChatting.Close();
	cBaseMenu.Close();


	#else

	//bitmap���ٰ�.
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
#ifdef USE_PROSTONTALE		//=========== �������ϼҽ��ΰ��
	Draw_C_Text(szLoading, BackStartPos.x + 80,BackStartPos.y + 90);
#else

	HDC hdc, sorDC,destdc;

	hdc = GetDC(g_hwnd);
	sorDC  = CreateCompatibleDC(hdc);
	destdc = CreateCompatibleDC(hdc);
	SelectObject(destdc, Dback.hb );		//off��ũ������.	
	Text_Out(destdc,BackStartPos.x + 80,BackStartPos.y + 90 ,szLoading);

	DeleteDC(sorDC);
	DeleteDC(destdc);
	ReleaseDC(g_hwnd, hdc );
#endif

}


#ifdef USE_PROSTONTALE		//=========== �������ϼҽ��ΰ��
//Ŭ���� ���� ���ۿ� �Լ�
int SendClanCommandUser( smWINSOCK *lpsmSock , DWORD	dwCode , int Param1, int Param2 , CLANWONLIST *lpClanUserList , int ClanUserCount );
#endif


void SetClanWon()
{
	if(cldata.nTotalClanWonCount==0) return;

	memcpy(ClanWonList.clanWon,cldata.clanWon,sizeof(cldata.clanWon));

	//========================================================

#ifdef USE_PROSTONTALE		//=========== �������ϼҽ��ΰ��
	//Ŭ���� ���� ���ۿ� �Լ�
	SendClanCommandUser( smWsockDataServer , smTRANSCODE_CLAN_UPDATE  , 0,0, &ClanWonList , cldata.nTotalClanWonCount );

	//========================================================
#endif

}





//savedata\\clanDATA �����==============================================start
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

//savedata\\clanDATA �����==============================================end

void Text_Out1()
{
}