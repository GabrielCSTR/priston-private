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

DWORD Check_CodeSafe( DWORD dwStartFunc );		//�ڵ庸ȣ
DWORD Check_CodeSafe2();						//�ڵ庸ȣ2
DWORD	GetSafeCode();							//��ȣ �ڵ� ���ϱ�
DWORD	GetSafeCode2();
int Code_VRamBuffOpen();
int	Mix_CodeVram();

extern char	szLastWhisperName[32];				//������ �Ӹ������� ���
extern int	LastWhisperLen;
extern int	PlayerArmor;
extern int	PlayerArmorFlag;

extern int	PlayUsed_Resurrection;

int SetPlayerArmor(int armor,int Kind);

char *GetFaceHairSkin(Unit *lpChar );		//�� ���� // ��ū�� ���� ����

/*
//////////////////////////////////////////////////////////////////////
//�޸� ��ü ýũ
int	CheckKeepMemFull();
//�޸� ýũ
int	CheckKeepMem(DWORD ChkCount );
//�޸� ýũ ����
int CloseKeepMem();
//�޸� ýũ �ʱ�ȭ
int	InitKeepMemFunc();
//////////////////////////////////////////////////////////////////////
*/
//////////////////////////// ���� ýũ ////////////////////////////////


//�κ��丮�� �ŷ�â���� ������ ã�� ���� ���
int GetInvenPotionCount( sCHK_POTION_COUNT *ChkPotion );
//���� ���� ���� ����
int	ResetPotion();
//���� ���� ���� ����
int	ResetPotion2();
//���హ�� ��
int	ComparePotion();
//���హ�� ��� ����
int	XorCheckPotion( sCHK_POTION_COUNT *ChkPotion );
///////////////////////////////////////////////////////////////////////

//��Ƽ�� �Ӹ� ������
int	WhisperPartyPlayer( char *szName );
//Ŭ���� ä�� ������
int	SetClanChatting();
//Ŭ�� ä�� ��� ����
int IsClanChatting();

//����ġ �߰�
int AddExp( int Exp );
//���� ����ġ ���ϱ�
INT64 GetNextExp( int Level );
//������ ����ġ�� �´��� Ȯ��
int	CheckLevelExp( int Level , INT64 Exp );
//����ġ�� ���� �߻�
int	GetLevelFromExp( INT64 Exp );
//64��Ʈ ����ġ ����
int	SetExp64(CharacterData *sCharacterData , INT64 Exp64 );
//���þ���ȼ�
int SetExp(int Exp_High,int Exp,int Flag);
//64��Ʈ ����ġ ��ȯ
INT64 GetExp64(CharacterData *sCharacterData );

//�ʵ� ����� �������� Ȯ��
int CheckFieldContExp();


//��ȯ������ ���
int	ActionEtherCore(ItemData	*lpItem );

//�׾ ����ġ ����
int DeadPlayerExp(Unit *lpChar );
//�ʵ忡�� ����� ĳ���� ����ġ �߰� ����
int ContGameExp(Unit *lpChar );
//����� ���
int GetPlayDefence(CharacterData *lpAttackCharInfo , CharacterData *lpDefenceCharInfo );

//����
int DrawWeather( int ax );
int InitWeatherSystem();
//�ε��� ȭ�� ǥ��
int OpenDispLoading();
//�ε� ǥ������
int CloseDispLoading();
//���̳��� ���� ���� �߰�
int AddRemoveDynPattern( smDPAT *lpDinaPattern );

//�ε� ���� ����
int CloseLoadingLamp();
//�ε�����
int InitLoadingLamp( HWND hWnd );

//���ֻ���ϴ� �𵨵� �ε�
int LoadOftenModels();

//���־��� �޽� �ε�
int	LoadOftenMeshPattern( char *szFileName );
//���־��� ���� �̸� �ε�
int LoadOftenArmor();
//���־��� ������ �̸� �ε�
int LoadOftenItem();
//NPC �̸� �ε�
int LoadOftenNpc();
//������ �̸� �ε�
int LoadOftenFace();
//���־� �޽� �ؽ��� ����ýũ
int CheckOftenMeshTextureSwap();
//�� ��Ų ����
int	ChangeModelSkin(Unit *lpChar , int ComicArmor , int ComicHeadNum , char *szArmor , char *szHead );
//�Ӹ���� �ٲ������
int ChangeHairModel( int HairCode );


//�ʵ� �� �ʱ�ȭ
int InitFieldMap();

//�ʵ� �� �׸���
int MainFieldMap();
//�ʵ� �� �׸���
int DrawFieldMap();

int GetFieldMapCursor();		//�̴ϸ� ��ġ�� ���콺 ����


//����Ÿ ���� ( Z/NZ ��� )
int EecodeCompress( BYTE *lpSrcData , BYTE *lpDestData , int size );
//���൥��Ÿ �ص� ( Z/NZ ��� )
int DecodeCompress( BYTE *lpSrcData , BYTE *lpDestData );
//���൥��Ÿ �ص� ( Z/NZ ��� )
int DecodeCompress( BYTE *lpSrcData , BYTE *lpDestData , int dCount );
//����Ÿ ���� ( Z/NZ ��� )
int EecodeCompress( BYTE *lpSrcData , BYTE *lpDestData , int size , int DestSize );


//�ٸ� ĳ���Ϳ��� ��ġ ��ġ���� Ȯ��
Unit *CheckOtherPlayPosi( int x, int y, int z );

//������ ���� �ޱ�
int ReformItem(Item *lpItemInfo );
//������ ���� �ޱ� ( �����ð� ���� )
int ReformItem_AdjustTime(Item *lpItemInfo , int TimeAdjust );

//������ ���� Ȯ��
int CheckItemForm(Item *lpItemInfo );
//������ 2���� ���Ѵ�
int CompareItems(Item *lpItemInfo1 , Item *lpItemInfo2 );
//������ ���� ������ �ޱ�
int	rsReformItem_Server(Item *lpItemInfo );

//ĳ���� ���� ���� Ȯ��
int CheckCharForm();
//ĳ���� ���� ���� �ޱ�
int ReformCharForm();
//ĳ���� ���� ���� �ޱ�
int ReformCharForm(CharacterData *lpCharInfo );
//ĳ���� ���� ���� Ȯ��
int CheckCharForm(CharacterData *lpCharInfo );
//Ʈ���̵� ���� ���� �ޱ�
int ReformTrade( void *lpTrade );
//Ʈ���̵��� ���� ���� Ȯ��
int CheckTrade( void *lpTrade );

//������ ����¡ ���� �ޱ�
int ReformMixItem(Item *lpItemInfo );
//������ ����¡ ���� Ȯ��
int CheckMixItem(Item *lpItemInfo );

//������ �����Ͽ� ���ϱ�
float GetItemAbsorb(Item *lpItemInfo );

//ĳ���� ������ ĳ�õ���Ÿ�� ���� ��´�
smTRNAS_PLAYERINFO	*GetCharInfoCache( char *lpData );
//ĳ���� ������ ĳ�õ���Ÿ�� ����
int SaveCharInfoCache( smTRNAS_PLAYERINFO *lpTransPlayInfo );

extern Unit	chrPartyPlayer;
//��Ƽ �÷��̾� �� ����
int OpenPartyPlayer( char *szName , char *szModelFile1 , char *szModelFile2 );


//���� ���� ýũ
int	CheckPlayAttackCount();
//���� ���� ��� ī����
int AttackMotionCountUp();
//���� ���� ��Ŷ ī����
int	AttackRecvCountUp();
//��ϵ� �ҷ� ������ �˻�
int	CheckCopyItem(Item *lpItem );
//���� ���� �� ��ȭ
int ChangeJobFace();


//���� ����Ʈ �ʱ�ȭ
int InitTimeEffect();
//����Ʈ ���� �߰�
int AddTimeEffect( DWORD EffectCode , DWORD dwTime , int x, int y, int z );
int AddTimeEffect( DWORD EffectCode , DWORD dwTime , int x, int y, int z , Unit *lpChar );
//���� ����Ʈ ����
int TimeEffectMain();


//ȸ�� �÷��̾� ������ ����
Unit *SelectRotPlayer(Unit *lpCurrentChar );
//ȸ�� �÷��̾� ������ ����
int	CloseRotPlayer();
//ȸ�� �÷��̾� ������ �ʱ�ȭ
Unit *InitRotPlayer();

//PLAYSUB ��Ƿ�ƾ ýũ
int Check_PlaySubReleaseFunc();

//�� �����Ѱ� ����
int SetJobFace( char *szModelName );
//���� �´��� Ȯ��
int	CheckUserModel(CharacterData *lpCharInfo );

//�̺��丮 ������ �ڵ� �ʱ�ȭ
int	ResetInvenItemCode();
//�̺��丮 ������ �ڵ忡�� Ư�� ������ ����
int SubInvenItemCode(Item *lpItem );
//�κ��丮 ������ �ڵ� Ȯ��
int	CheckInvenItemCode();

//��� ýũ 2
void CheckPlaySubFunc2();
//���ô�ͷ��ͼƬ
int SetBigHeadToImage(int Kind,int Time);


//������ �׷��� ýũ �ʱ�ȭ
int	ResetEnergyGraph( int Num );
//������ �׷��� ���� ýũ
int CheckEnergyGraphError();
//������ �׷����� ���� ýũ
int CheckEnergyGraph();

//�κ��丮�� ������ �������� ã�� �˻��Ͽ� ã�´�
Item *FindInvenItem( DWORD dwItemCode , DWORD dwHead , DWORD dwChkSum );
//�κ��丮 ������ ���� ����
int SendInvenItemError( DWORD dwKind , DWORD dwItemCode , DWORD dwHead , DWORD dwChkSum );
//�κ��丮�� ���� ������ ���� ������ ������
int SendUsingItemListToServer();
//�κ��丮�� ���� ������ ���� ������ ������
int SendUsingItemListToServer2();


//�̺��丮 �� �˻� �ʱ�ȭ
int	ResetInvenMoney();
//�κ��丮 �˻�뵷 �߰�
int	AddInvenMoney( int Money );
//�κ��丮 �� �˻�
int	CheckInvenMoney();


//���ݼӵ��� �����Ӽӵ��� ��ȯ
int GetAttackSpeedMainFrame( int AttackSpeed );
int	GetAttackSpeedFrame( int AttackSpeed , int AddSpeed );
int	GetAttackSpeedFrame( int AttackSpeed );


extern int DispLoading;			//�ε� ���� ǥ�� ����
extern int MessageLoading;		//�ε��� �޼��� ó��

//��Ƽ���ھ� ���� �α� �ڵ�
#define POTION_ETHERCORE		0x40

extern int	CodeXorLife;				//������ �����ڵ�
extern int	CodeXorMana;				//��� �����ڵ�
extern int	CodeXorStamina;				//�ٷ� �����ڵ�
extern int	CodeXorMoney;				//�� �����ڵ�


//�������� �������� ���¸� �Ǻ��Ѵ�
int GetItemKindFromBliankColor( smCHARTOOL	*lpCharTool );


extern char	szSOD_String[64];
extern BYTE	bSOD_StringColor[4];
extern int	SOD_StringCount;

extern sSOD_SCORE	sSodScore;
extern int		SoDGateFlag;

int	DisplaySodScore();	//Sod���� ǥ�� �Լ�
int	SodScoreMain();		//SoD ����
int	Sod_SodEffect( int Round );			//SoD ���� ����Ʈ