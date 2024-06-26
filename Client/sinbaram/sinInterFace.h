/*----------------------------------------------------------------------------*
*	파일명 :  sinInterFace.h	
*	하는일 :  인터페이스에 관한 모든걸 관리한다 
*	작성일 :  최종업데이트 12월
*	적성자 :  박상열 
*-----------------------------------------------------------------------------*/	

//////////전사시 귀환 
#define		RESTART_FEILD		1
#define		RESTART_TOWN		2
#define		RESTART_EXIT		3

/////////스킬 사용시 인터페이스 표시
#define     HA_DEFANCE			1
#define     HA_BLOCK			2
#define     HA_EVASION			3

/*----------------------------------------------------------------------------*
*						(인터페이스  )class
*-----------------------------------------------------------------------------*/	
struct sRUNCAMERAMAP{ //버튼 기능 플랙 

	int RunFlag;			 //걷기 달리기 플랙 
	int CameraAutoFlag;		 //카메라 자동 플랙 
	int MapOnFlag;			 //맵보기 플랙 

	//이곳에 인터페이스에서 일어나는 모든 이벤트 버튼을 추가시킬 예정 

};

////// 라이프 마나 스테미나 잔상효과 
struct sSHADOWSTATE{
	int Flag;
	int Time;
	POINT Posi;
	POINT Size;
	DWORD Color;

};


class cINTERFACE
{
public:

	sRUNCAMERAMAP	sInterFlags;

	int MatMain;					    //상단 인터페이스 
	int MatMenu[2];						//메뉴  
	int MatExitMenu;					//나가기 메뉴 
	int MatComPass;						//나침반 구슬 	

	int MatLife;						//라이프   잔상효과
	int MatMana;						//마나     잔상효과
	int MatStamina;						//스테미나 잔상효과

	smTEXTUREHANDLE *lpEXP;      //경험치  
	smTEXTUREHANDLE *lpMP;		//마나  	
	smTEXTUREHANDLE *lpLIFE;     //라이프 
	smTEXTUREHANDLE *lpSTM;      //스테미나 
	smTEXTUREHANDLE *lpANGER;    //분노게이지 

	smTEXTUREHANDLE *lpLIFESpot;     //라이프 
	smTEXTUREHANDLE *lpSTMSpot;      //스테미나 
	smTEXTUREHANDLE *lpMANASpot;     //마나

	smTEXTUREHANDLE *lpButton[6];//버튼 아이콘 
	smTEXTUREHANDLE *lpButton2[6];//버튼 아이콘2 

	smTEXTUREHANDLE *lpMenuButton[3];//메뉴 버튼 

	smTEXTUREHANDLE *lpInfoBox[6]; //풍선 도움말 
	smTEXTUREHANDLE *lpWalk;		  //걷기 

	smTEXTUREHANDLE *lpRunInfo;    //뛰기풍선 도움말 
	smTEXTUREHANDLE *lpWalkInfo;   //걷기풍선 도움말 

	smTEXTUREHANDLE *lpCameraAutoInfo;   //자동 카메라 풍선 도움말 
	smTEXTUREHANDLE *lpCameraHandInfo;   //수동 카메라 풍선 도움말 
	smTEXTUREHANDLE *lpCameraFixInfo;   //수동 카메라 풍선 도움말 

	smTEXTUREHANDLE *lpMapOnInfo;   //자동 카메라 풍선 도움말 
	smTEXTUREHANDLE *lpMapOffInfo;   //수동 카메라 풍선 도움말 

	smTEXTUREHANDLE *lpChatShowButton;	//큰채팅창

	smTEXTUREHANDLE *lpSun;	//해
	smTEXTUREHANDLE *lpMoon;	//달

	smTEXTUREHANDLE *lpGage[2]; //0전체  1꼭따리 

	smTEXTUREHANDLE *lpBar_Anger;
	smTEXTUREHANDLE *lpBar_Time;
	smTEXTUREHANDLE *lpBar_Exp;
	smTEXTUREHANDLE *lpBar_ExpWon;

	smTEXTUREHANDLE *lpButton_Anger;

	smTEXTUREHANDLE *lpMapOnImage;
	smTEXTUREHANDLE *lpCameraImage[2]; //0오토 1 고정 

	smTEXTUREHANDLE *lpReStartMain; //다시시작 
	smTEXTUREHANDLE *lpReStartButton[3]; //다시시작 

	smTEXTUREHANDLE *lpSelectSkill_Main[2];		//스킬 배우기 0 그레이 1 활성 
	smTEXTUREHANDLE *lpSelectChangeJob[2];   //전업        0 그레이 2 활성 

	smTEXTUREHANDLE *lpGrowInterLeft;
	smTEXTUREHANDLE *lpGrowInterMiddle;
	smTEXTUREHANDLE *lpGrowInterRight;


	int MatClock; //시계 
	int DayNightFlag;

public:
	cINTERFACE();
	~cINTERFACE();

	void Init();
	void Load();
	void Release();
	void Close();
	void Draw();
	void Main();
	void LButtonDown(int x , int y);
	void LButtonUp(int x , int y);
	void RButtonDown(int x , int y);
	void RButtonUp(int x, int y);
	void KeyDown(); 

	void InitState();		//생명력 , 기력 , 근력 을 초기화한다 
	void CheckingState();	//생명력 , 기력 , 근력 의 변화에 따라 Bmp의 크기를 변화 시킨다
	void ShowParaState();   //생명력 기력 근력 경험치 수치를 표시한다 

	void DrawInterText();   //인터페이스에 들어갈 텍스트를 표시한다 

	void CheckAllBox(int ButtonFlag); //박스를 하나만 보여준다 

	int GetWordTimeDisplay();

	void ShowExpPercent(); //경험치를 보여준다

	int  SetStringEffect(int); //이펙트글자를 보여준다 

};

extern cINTERFACE	cInterFace;

extern POINT InfoMessageBoxPos;  //텍스를 표시할 좌표 

extern int sinFireShow;           //불을 보여준다 
extern int ExitButtonClick;

extern int ReStartFlag;			  //값이 들어오면 다시시작 인터페이스를 보여준다 
extern int ReStartOptionIndex;	  //다시시작 선택 인덱스 	

extern int SkillNpcFlag;			  //값이 스킬 전업 인터페이스를 보여준다 
extern int SkillMasterOptionIndex;

extern int RestartCheckExp;		  //다시시작할수있는 경험치가 있나 없나 


extern int psDrawTexImage2( smTEXTUREHANDLE *hTexHandle , float *x, float *y, float fx, float fy, float fw, float fh, int Transp , int specular);

extern int NotUseSkillEffect[3];

extern int ChangeJobButtonclick;

extern int  ResetQuset3Flag;

extern int ReStartFlag;
extern POINT ReStartMainXY;
extern int ReStartIndex;
extern POINT ReStartTextXY;
extern char szReStartMsg[128];
extern char szReStartMsg2[128];


