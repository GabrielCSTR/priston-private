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
int	Mix_CodeVram();

extern char	szLastWhisperName[32];				//마지막 귓말전송한 사람
extern int	LastWhisperLen;
extern int	PlayerArmor;
extern int	PlayerArmorFlag;

extern int	PlayUsed_Resurrection;

int SetPlayerArmor(int armor,int Kind);

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


//인벤토리와 거래창에서 물약을 찾어 갯수 기록
int GetInvenPotionCount( sCHK_POTION_COUNT *ChkPotion );
//물약 갯수 새로 설정
int	ResetPotion();
//물약 갯수 새로 설정
int	ResetPotion2();
//물약갯수 비교
int	ComparePotion();
//물약갯수 기록 반전
int	XorCheckPotion( sCHK_POTION_COUNT *ChkPotion );
///////////////////////////////////////////////////////////////////////

//파티원 귓말 보내기
int	WhisperPartyPlayer( char *szName );
//클랜원 채팅 보내기
int	SetClanChatting();
//클랜 채팅 모드 설정
int IsClanChatting();

//경험치 추가
int AddExp( int Exp );
//다음 경험치 구하기
INT64 GetNextExp( int Level );
//레벨과 경험치가 맞는지 확인
int	CheckLevelExp( int Level , INT64 Exp );
//경험치로 레벨 추산
int	GetLevelFromExp( INT64 Exp );
//64비트 경험치 설정
int	SetExp64(CharacterData *sCharacterData , INT64 Exp64 );
//�阮첸�駱된섬
int SetExp(int Exp_High,int Exp,int Flag);
//64비트 경험치 반환
INT64 GetExp64(CharacterData *sCharacterData );

//필드 재시작 가능한지 확인
int CheckFieldContExp();


//귀환아이템 사용
int	ActionEtherCore(ItemData	*lpItem );

//죽어서 경험치 깍임
int DeadPlayerExp(Unit *lpChar );
//필드에서 재시작 캐릭터 경험치 추가 깍임
int ContGameExp(Unit *lpChar );
//방어율 계산
int GetPlayDefence(CharacterData *lpAttackCharInfo , CharacterData *lpDefenceCharInfo );

//날씨
int DrawWeather( int ax );
int InitWeatherSystem();
//로딩중 화면 표시
int OpenDispLoading();
//로딩 표시종료
int CloseDispLoading();
//나이나믹 패턴 삭제 추가
int AddRemoveDynPattern( smDPAT *lpDinaPattern );

//로딩 램프 제거
int CloseLoadingLamp();
//로딩램프
int InitLoadingLamp( HWND hWnd );

//자주사용하는 모델들 로드
int LoadOftenModels();

//자주쓰는 메시 로드
int	LoadOftenMeshPattern( char *szFileName );
//자주쓰는 갑옷 미리 로딩
int LoadOftenArmor();
//자주쓰는 아이템 미리 로딩
int LoadOftenItem();
//NPC 미리 로딩
int LoadOftenNpc();
//얼굴파일 미리 로딩
int LoadOftenFace();
//자주쓸 메시 텍스쳐 스왑첵크
int CheckOftenMeshTextureSwap();
//모델 스킨 변경
int	ChangeModelSkin(Unit *lpChar , int ComicArmor , int ComicHeadNum , char *szArmor , char *szHead );
//머리모양 바꿔버리기
int ChangeHairModel( int HairCode );


//필드 맵 초기화
int InitFieldMap();

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

//캐릭터 정보 인증 확인
int CheckCharForm();
//캐릭터 정보 인증 받기
int ReformCharForm();
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

//캐릭터 정보를 캐시데이타로 부터 얻는다
smTRNAS_PLAYERINFO	*GetCharInfoCache( char *lpData );
//캐릭터 정보를 캐시데이타에 저장
int SaveCharInfoCache( smTRNAS_PLAYERINFO *lpTransPlayInfo );

extern Unit	chrPartyPlayer;
//파티 플레이어 얼굴 오픈
int OpenPartyPlayer( char *szName , char *szModelFile1 , char *szModelFile2 );


//공격 비율 첵크
int	CheckPlayAttackCount();
//공격 받은 모션 카운터
int AttackMotionCountUp();
//공격 받은 패킷 카운터
int	AttackRecvCountUp();
//등록된 불량 아이템 검사
int	CheckCopyItem(Item *lpItem );
//집업 변경 얼굴 변화
int ChangeJobFace();


//예약 이펙트 초기화
int InitTimeEffect();
//이펙트 예약 추가
int AddTimeEffect( DWORD EffectCode , DWORD dwTime , int x, int y, int z );
int AddTimeEffect( DWORD EffectCode , DWORD dwTime , int x, int y, int z , Unit *lpChar );
//예약 이펙트 실행
int TimeEffectMain();


//회전 플레이어 포인터 선택
Unit *SelectRotPlayer(Unit *lpCurrentChar );
//회전 플레이어 포인터 종료
int	CloseRotPlayer();
//회전 플레이어 포인터 초기화
Unit *InitRotPlayer();

//PLAYSUB 펑션루틴 첵크
int Check_PlaySubReleaseFunc();

//얼굴 변경한거 적용
int SetJobFace( char *szModelName );
//모델이 맞는지 확인
int	CheckUserModel(CharacterData *lpCharInfo );

//이벤토리 아이템 코드 초기화
int	ResetInvenItemCode();
//이벤토리 아이템 코드에서 특정 아이템 제거
int SubInvenItemCode(Item *lpItem );
//인벤토리 아이템 코드 확인
int	CheckInvenItemCode();

//모듈 첵크 2
void CheckPlaySubFunc2();
//�阮척擦럿싶셕�
int SetBigHeadToImage(int Kind,int Time);


//에너지 그래프 첵크 초기화
int	ResetEnergyGraph( int Num );
//에너지 그래프 오류 첵크
int CheckEnergyGraphError();
//에너지 그래프의 오류 첵크
int CheckEnergyGraph();

//인벤토리의 지정한 아이템을 찾아 검색하여 찾는다
Item *FindInvenItem( DWORD dwItemCode , DWORD dwHead , DWORD dwChkSum );
//인벤토리 아이템 복사 오류
int SendInvenItemError( DWORD dwKind , DWORD dwItemCode , DWORD dwHead , DWORD dwChkSum );
//인벤토리의 장착 아이템 정보 서버에 보내기
int SendUsingItemListToServer();
//인벤토리의 장착 아이템 정보 서버에 보내기
int SendUsingItemListToServer2();


//이벤토리 돈 검사 초기화
int	ResetInvenMoney();
//인벤토리 검사용돈 추가
int	AddInvenMoney( int Money );
//인벤토리 돈 검사
int	CheckInvenMoney();


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


//색상으로 아이템의 상태를 판별한다
int GetItemKindFromBliankColor( smCHARTOOL	*lpCharTool );


extern char	szSOD_String[64];
extern BYTE	bSOD_StringColor[4];
extern int	SOD_StringCount;

extern sSOD_SCORE	sSodScore;
extern int		SoDGateFlag;

int	DisplaySodScore();	//Sod점수 표시 함수
int	SodScoreMain();		//SoD 연출
int	Sod_SodEffect( int Round );			//SoD 라운드 이펙트