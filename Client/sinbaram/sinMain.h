/*----------------------------------------------------------------------------*
*	파일명 :  sinMain.h
*	하는일 :  신바람 메인 
*	작성일 :  최종업데이트 12월
*	적성자 :  박상열 
*-----------------------------------------------------------------------------*/	

#define		 SINLBUTTONDOWN			10
#define		 SINLBUTTONUP 			11
#define		 SINRBUTTONDOWN			110
#define		 SINRBUTTONUP 			111

#define		 SINMOUSEMOVE			2
#define		 SINKEYDOWN				3

#define      SIN_CHAR_FIGHTER		1
#define      SIN_CHAR_MECANICIAN	2
#define      SIN_CHAR_ARCHER		3
#define      SIN_CHAR_PIKEMAN		4
#define		 SIN_CHAR_KNIGHT		6
#define		 SIN_CHAR_ATALANTA		5
#define		 SIN_CHAR_PRIESTESS		8
#define		 SIN_CHAR_MAGICIAN		7

/*----------------------------------------------------------------------------*
*							함수 

*-----------------------------------------------------------------------------*/	

void sinInit();

void sinMain();

void sinDraw();

void sinDrawText();


void sinClose();

void sinProc(int Message);

int GetSinTime(DWORD dwTime,smTIME *smTime);
int GetSinTime2(DWORD dwTime ,smTIME *smTime);


/*----------------------------------------------------------------------------*
*							   class 
*-----------------------------------------------------------------------------*/	
class cSINBARAM_UI{ //클래스의 기본이 된다

public:
	int OpenFlag;       //포인터 로 접근하기 때문에 위치가 절대루 바뀌면 안된다 

public:
	cSINBARAM_UI();
	~cSINBARAM_UI();

	void Init(); //클래스 초기화
	void Load();
	void Release();
	void Draw();
	void Close();//클래스 종료 
	void Main();
	void LButtonDown(int x , int y);
	void LButtonUp(int x , int y);
	void RButtonDown(int x , int y);
	void RButtonUp(int x, int y);
	void KeyDown(); //키 체크 
};
/*----------------------------------------------------------------------------*
*							extern 변수 
*-----------------------------------------------------------------------------*/	
extern int	 quit;
extern int	 MouseButton[3];	//마우스 배열 
extern BYTE  VRKeyBuff[256];    //키입력 버퍼  
extern POINT pCursorPos;		//마우스 좌표 	

extern HWND  hFocusWnd; //채팅 포커스 

extern HWND hwnd;

extern CharacterData *sinChar;		//캐릭터 정보 구조체 
extern CharacterData sinCharDisplay; //캐릭터 정보 구조체 (해킹방지용 백업)
extern int sinbaram_Stop;