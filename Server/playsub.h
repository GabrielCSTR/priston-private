#define CHAR_CHANGE_JOB_LEVEL 4

#define sinNPC_SHOP				0x00000001
#define sinNPC_MIX				0x00000002
#define sinNPC_AGING			0x00000004
#define sinNPC_WARE				0x00000008
#define sinNPC_SKILL			0x00000010
#define sinNPC_FORCE			0x00000020
#define sinNPC_SMELTING			0x00000030
#define sinNPC_MANUFACTURE		0x00000040
#define sinNPC_MIXTURE_RESET	0x00000080

#define MAX_JOBNUM				10

#define RIGHTHAND	0
#define LEFTHAND	1


extern DWORD	dwFuncChkTime;

DWORD Check_CodeSafe( DWORD dwStartFunc );		//코드보호
DWORD Check_CodeSafe2();						//코드보호2
DWORD	GetSafeCode();							//보호 코드 구하기
DWORD	GetSafeCode2();
int Code_VRamBuffOpen();

extern char	szLastWhisperName[32];				//마지막 귓말전송한 사람
extern int	LastWhisperLen;
extern int	PlayerArmor;
extern int	PlayerArmorFlag;

extern int	PlayUsed_Resurrection;

char *GetFaceHairSkin(Unit *lpChar );		//얼굴 복구 // 얼큰이 오류 수정

/*
//////////////////////////////////////////////////////////////////////
//메모리 전체 첵크
int	CheckKeepMemFull();
//메모리 첵크
int	CheckKeepMem(DWORD ChkCount );
//메모리 첵크 종료
int CloseKeepMem();
//메모리 첵크 초기화
int	InitKeepMemFunc();
//////////////////////////////////////////////////////////////////////
*/
//////////////////////////// 물약 첵크 ////////////////////////////////


//물약 갯수 새로 설정
int	ResetPotion();
//물약 갯수 새로 설정
int	ResetPotion2();
//물약갯수 비교
int	ComparePotion();
//물약갯수 기록 반전
int	XorCheckPotion( sCHK_POTION_COUNT *ChkPotion );

//다음 경험치 구하기
INT64 GetNextExp( int Level );
//레벨과 경험치가 맞는지 확인
int	CheckLevelExp( int Level , INT64 Exp );
//경험치로 레벨 추산
int	GetLevelFromExp( INT64 Exp );
//방어율 계산
int GetPlayDefence(CharacterData *lpAttackCharInfo , CharacterData *lpDefenceCharInfo );

//나이나믹 패턴 삭제 추가
int AddRemoveDynPattern( smDPAT *lpDinaPattern );

//로딩 램프 제거
int CloseLoadingLamp();
//로딩램프
int InitLoadingLamp( HWND hWnd );

//자주쓰는 메시 로드
int	LoadOftenMeshPattern( char *szFileName );
//자주쓰는 갑옷 미리 로딩
int LoadOftenArmor();
//NPC 미리 로딩
int LoadOftenNpc();
//얼굴파일 미리 로딩
int LoadOftenFace();



//필드 맵 그리기
int MainFieldMap();
//필드 맵 그리기
int DrawFieldMap();

int GetFieldMapCursor();		//미니맵 위치에 마우스 유무


//데이타 압축 ( Z/NZ 방식 )
int EecodeCompress( BYTE *lpSrcData , BYTE *lpDestData , int size );
//압축데이타 해독 ( Z/NZ 방식 )
int DecodeCompress( BYTE *lpSrcData , BYTE *lpDestData );
//압축데이타 해독 ( Z/NZ 방식 )
int DecodeCompress( BYTE *lpSrcData , BYTE *lpDestData , int dCount );
//데이타 압축 ( Z/NZ 방식 )
int EecodeCompress( BYTE *lpSrcData , BYTE *lpDestData , int size , int DestSize );

//압축데이타 서버 아이템 해독용 ( Z/NZ 방식 )
int DecodeCompress_ItemPotion(User *lpPlayInfo , BYTE *lpSrcData , BYTE *lpDestData , int deCount , void *lpTransRecdata );


//다른 캐릭터와의 위치 겹치는지 확인
Unit *CheckOtherPlayPosi( int x, int y, int z );

//아이템 인증 받기
int ReformItem(Item *lpItemInfo );
//아이템 인증 받기 ( 생성시간 보정 )
int ReformItem_AdjustTime(Item *lpItemInfo , int TimeAdjust );

//아이템 인증 확인
int CheckItemForm(Item *lpItemInfo );
//아이템 2개를 비교한다
int CompareItems(Item *lpItemInfo1 , Item *lpItemInfo2 );
//아이템 서버 인증만 받기
int	rsReformItem_Server(Item *lpItemInfo );
//캐릭터 정보 인증 받기
int ReformCharForm(CharacterData *lpCharInfo );
//캐릭터 정보 인증 확인
int CheckCharForm(CharacterData *lpCharInfo );
//트레이드 정보 인증 받기
int ReformTrade( void *lpTrade );
//트레이드터 정보 인증 확인
int CheckTrade( void *lpTrade );

//아이템 에이징 인증 받기
int ReformMixItem(Item *lpItemInfo );
//아이템 에이징 인증 확인
int CheckMixItem(Item *lpItemInfo );

//흡수력 보정하여 구하기
float GetItemAbsorb(Item *lpItemInfo );

//캐릭터 정보를 캐시데이타에 저장
int SaveCharInfoCache( smTRNAS_PLAYERINFO *lpTransPlayInfo );

extern Unit	chrPartyPlayer;


//공격 비율 첵크
int	CheckPlayAttackCount();
//공격 받은 모션 카운터
int AttackMotionCountUp();
//공격 받은 패킷 카운터
int	AttackRecvCountUp();
//등록된 불량 아이템 검사
int	CheckCopyItem(Item *lpItem );


//PLAYSUB 펑션루틴 첵크
int Check_PlaySubReleaseFunc();

//모델이 맞는지 확인
int	CheckUserModel(CharacterData *lpCharInfo );

//이벤토리 아이템 코드 초기화
int	ResetInvenItemCode();
//이벤토리 아이템 코드에서 특정 아이템 제거
int SubInvenItemCode(Item *lpItem );

//�阮척擦럿싶셕�
int SetBigHeadToImage(int Kind,int Time);

//인벤토리의 장착 아이템 정보 서버에 보내기
//인벤토리의 장착 아이템 정보 서버에 보내기


//이벤토리 돈 검사 초기화
int	ResetInvenMoney();
//인벤토리 검사용돈 추가
int	AddInvenMoney( int Money );


//공격속도를 프레임속도로 변환
int GetAttackSpeedMainFrame( int AttackSpeed );
int	GetAttackSpeedFrame( int AttackSpeed , int AddSpeed );
int	GetAttackSpeedFrame( int AttackSpeed );


extern int DispLoading;			//로딩 상태 표시 유무
extern int MessageLoading;		//로딩중 메세지 처리

//에티르코어 포션 로그 코드
#define POTION_ETHERCORE		0x40

extern int	CodeXorLife;				//생명력 숨김코드
extern int	CodeXorMana;				//기력 숨김코드
extern int	CodeXorStamina;				//근력 숨김코드
extern int	CodeXorMoney;				//돈 숨김코드


extern char	szSOD_String[64];
extern BYTE	bSOD_StringColor[4];
extern int	SOD_StringCount;

extern sSOD_SCORE	sSodScore;
extern int		SoDGateFlag;



