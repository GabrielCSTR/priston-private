#include "StdAfx.h"
#include "character.h"
#include "fileread.h"
#include "effectsnd.h"
#include "playmain.h"
#include "playsub.h"

#include "SrcServer\\gamesql.h"
#include "SrcServer\\onserver.h"

int	NotItemSpecial = 0;

extern	int	quit;

static char decode[512];
static char line[512];

void ModelKeyWordEncode( DWORD dwFileCode, smMODELINFO *lpMODELINFO );
int  ModelKeyWordDecode( DWORD dwFileCode, smMODELINFO *lpMODELINFO );
void MotionKeyWordEncode( DWORD dwCode, smMODELINFO *lpMODELINFO );
int	 MotionKeyWordDecode( DWORD dwCode, smMODELINFO *lpMODELINFO );



//서버용 NPC 메세지 카운터
#ifdef	_W_SERVER
#define	SVR_NPC_MSG_MAX		1024
char	szSvr_NpcMsgs[SVR_NPC_MSG_MAX][256];
DWORD	dwSvr_NpcMsgCode[SVR_NPC_MSG_MAX];
#else
#define	SVR_NPC_MSG_MAX		32
char	szSvr_NpcMsgs[SVR_NPC_MSG_MAX][128];
DWORD	dwSvr_NpcMsgCode[SVR_NPC_MSG_MAX];
#endif

int		NpcMsgCount = 0;

char	*SetNPCMsg( char *szMsg )
{
	char	*lpMsg;
	DWORD	dwCode;
	int		cnt;

	if ( NpcMsgCount>=SVR_NPC_MSG_MAX ) return NULL;

	dwCode = GetCodebyName(szMsg);

	for(cnt=0;cnt<NpcMsgCount;cnt++) {
		if ( dwCode==dwSvr_NpcMsgCode[cnt] && lstrcmp( szSvr_NpcMsgs[cnt] , szMsg )==0 ) {
			break;
		}
	}

	if ( cnt<NpcMsgCount ) {
		return szSvr_NpcMsgs[cnt];
	}

	dwSvr_NpcMsgCode[NpcMsgCount] = dwCode;
	lpMsg = szSvr_NpcMsgs[NpcMsgCount++];
	lstrcpy( lpMsg , szMsg );

	return lpMsg;
}


static char *GetWord(char *q , char *p)
{
	while ( (*p == 32) || (*p == 9) )
	{
		p++;
	}

	while ( (*p != 32) && (*p != 9) )
	{
		if ( *p == '\n' || *p=='\r' ) break;
		*q++ = *p++;
	}
	*q++ = 0;

	return p;
}


char *szIniCommand[] =
{
	"*동작파일",
	"*동작모음",
	"*모양파일",
	"*모양이름",
	"*파일연결",
	"*보조동작파일",

	"*정밀모양",
	"*보통모양",
	"*저질모양",

	"*XX걷는동작",
	"*XX서있기동작",

	"*착용무기",
	"*적용직업",
	"*해당위치",
	"*적용기술",

	"*표정파일연결",
	"*표정파일",
	"*표정모음",

	""
};

char *szIniRepeat = "반복";
char *szMotionWord = "동작";

char *szRunWord = "뛰는";
char *szStandWord = "*서있기";
char *szStandWord2 = "*정지";
char *szWalkWord = "*걷는";

char *szAttackWord = "공격";
char *szDeadWord = "죽기";
char *szDeadWord2 = "죽는";
char *szDamageWord = "타격";
char *szDamageWord2 = "데미지";
char *szDamageWord3 = "막기";

char *szWarpWord = "울기";
char *szWarpWord2 = "워프";

char *szSometimeWord = "가끔";

char *szFallDownWord = "떨어";
char *szFallStandLargeWord = "큰착지";
char *szFallStandSmallWord = "작은착지";

char *szRestartWord = "다시시작";
char *szEatWord = "먹기";
char *szSkillWord = "기술";
char *szYahooWord = "만세";

char *szMotionTalkWord = "표정";

char *szArTalkWord = "아표정";
char *szETalkWord = "이표정";
char *szOhTalkWord = "오표정";
char *szEyeTalkWord = "눈깜빡표정";

char *szBlankTalkWord = "무표정(작동않함)";
char *szSmileTalkWord = "웃는표정";
char *szGrumbleTalkWord = "화난표정";
char *szSorrowTalkWord = "슬픈표정";
char *szStartledTalkWord = "놀란표정";
char *szNatureTalkWord = "고유표정";
char *szSpecialTalkWord = "특별표정";


JOBNAME_BIT BitMaskJobNames[] = 
{
	{	"Fighter"		,	0x0001	},
	{	"Mechanician"	,	0x0002	},
	{	"Archer"		,	0x0004	},
	{	"Pikeman"		,	0x0008	},

	{	"Atalanta"		,	0x0010	},
	{	"Knight"		,	0x0020	},
	{	"Magician"		,	0x0040	},
	{	"Priest"		,	0x0080	},
	{	"Assassin"		,	0x0100	},
	{	"Shaman"		,	0x0200	},

	{	"" , 0 },
	{	"PureBody"		,	0x0400	},
	{	"PureBody"		,	0x0800	},
	{	"PureBody"		,	0x1000	}
};


int SetIniMotionInfo(ModelAnimation *motion, char *p, int *lpRate = NULL )
{
	char strBuff[256];
	int EventCount;

	EventCount = 0;

	p = GetWord( strBuff , p );
	motion->StartFrame = atoi( strBuff );
	p = GetWord( strBuff , p );
	motion->EndFrame   = atoi( strBuff );

	motion->EventFrame[0] = 0;
	motion->EventFrame[1] = 0;
	motion->EventFrame[2] = 0;
	motion->EventFrame[3] = 0;

	while(1) {
		p = GetWord( strBuff , p );
		if ( strBuff[0]<'0' || strBuff[0]>'9' ) break;
		if ( EventCount>=4 ) break;

		motion->EventFrame[EventCount] = (atoi( strBuff )-motion->StartFrame) * 160;
		EventCount++;
	}
	if( lstrcmp( strBuff, szIniRepeat ) == 0 )
	{
		motion->Repeat = TRUE;
	}
	if( strBuff[0] != '(' && strBuff[0] >= ' ' && strBuff[0] <= 0x7F ) 
		motion->KeyCode = strBuff[0];

	if( lpRate )
	{
		p = GetWord( strBuff, p );
		
		int  len = lstrlen(strBuff);
		char NumBuff[10] = {0,};

		if( len > 2 && len < 6 && strBuff[0] == '(' && strBuff[len-1] == ')')
		{
			::CopyMemory( NumBuff, &strBuff[1], len-2 );
			*lpRate = atoi( NumBuff );
			if( *lpRate > 100 )
				*lpRate = 100;
		}
	}

	return TRUE;
}

static char *szFileExt = "inx";



int AddModelDecode( char *iniFile, smMODELINFO *Info )
{
	FILE	*fp;
	char	*szDirecotry;
	char strBuff[64];
	char *p;
	char *pb;
	int CmdNum;
	int cnt;
	_MODELGROUP	*lpModelGroup;
	int JobCount;

	char *szMotionFileList[128];

	int MotionFileListCnt;
	int MotionFrameList[100];
	smPAT3D	*pat3d;

	int MotionLastPos;

	MotionLastPos = 0;


	MotionFileListCnt = 0;
	ZeroMemory(MotionFrameList,sizeof(int)*100);

	fopen_s(&fp, iniFile, "rb");
	if (fp==NULL)
		return FALSE;

	szDirecotry = SetDirectoryFromFile(iniFile);

	while(!feof(fp))
	{
		if( fgets( line, 512, fp ) == NULL)
			break;

		p = GetWord( decode , line);

		CmdNum = 0;

		while(1)
		{
			if (lstrcmp(decode,szIniCommand[CmdNum]) == 0)
				break;

			if (szIniCommand[CmdNum][0]==NULL)
			{
				if ( decode[0]=='*' && strstr( decode , szMotionWord ) )
				{
					if( Info->MotionCount < MOTION_INFO_MAX ) 
						SetIniMotionInfo(&Info->MotionInfo[Info->MotionCount], p,&Info->NpcMotionRate[Info->MotionCount] );


					Info->MotionInfo[Info->MotionCount].MotionFrame = MotionFileListCnt;
					Info->MotionInfo[Info->MotionCount].iType = ANIMATIONTYPE_None;
	
					//달리기 모션
					if ( strstr( decode , szRunWord ) ) {
						Info->MotionInfo[Info->MotionCount].iType = ANIMATIONTYPE_Running;
						Info->MotionInfo[Info->MotionCount].Repeat = TRUE;
					}

					//공격 모션
					if ( strstr( decode , szAttackWord ) ) {
						Info->MotionInfo[Info->MotionCount].iType = ANIMATIONTYPE_Attack;
					}
					//죽는 모션
					if ( strstr( decode , szDeadWord ) ) {
						Info->MotionInfo[Info->MotionCount].iType = ANIMATIONTYPE_Die;
					}
					//죽는 모션
					if ( strstr( decode , szDeadWord2 ) ) {
						Info->MotionInfo[Info->MotionCount].iType = ANIMATIONTYPE_Die;
					}

					//타격 모션
					if ( strstr( decode , szDamageWord ) ) {
						Info->MotionInfo[Info->MotionCount].iType = ANIMATIONTYPE_Flinch;
					}
					//타격 모션
					if ( strstr( decode , szDamageWord2 ) ) {
						Info->MotionInfo[Info->MotionCount].iType = ANIMATIONTYPE_Flinch;
					}
					//타격 모션
					if ( strstr( decode , szDamageWord3 ) ) {
						Info->MotionInfo[Info->MotionCount].iType = ANIMATIONTYPE_Flinch;
					}
					//가끔하는 모션
					if ( strstr( decode , szSometimeWord ) ) {
						Info->MotionInfo[Info->MotionCount].iType = (EAnimationType)CHRMOTION_STATE_SOMETIME;
					}

					//떨어지는 모션
					if ( strstr( decode , szFallDownWord ) ) {
						Info->MotionInfo[Info->MotionCount].iType = ANIMATIONTYPE_Falling;
					}
					//착지 모션
					if ( strstr( decode , szFallStandSmallWord ) ) {
						Info->MotionInfo[Info->MotionCount].iType = ANIMATIONTYPE_FallLow;
					}
					//충격적인 착지 모션
					if ( strstr( decode , szFallStandLargeWord ) ) {
						Info->MotionInfo[Info->MotionCount].iType = ANIMATIONTYPE_FallHigh;
					}

					//서있는 모션
					if ( strstr( decode , szStandWord ) || strstr( decode , szStandWord2 ) ) {
						Info->MotionInfo[Info->MotionCount].iType = ANIMATIONTYPE_Idle;
						Info->MotionInfo[Info->MotionCount].Repeat = TRUE;
					}
					//걷는 모션
					if ( strstr( decode , szWalkWord ) ) {
						Info->MotionInfo[Info->MotionCount].iType = ANIMATIONTYPE_Walking;
						Info->MotionInfo[Info->MotionCount].Repeat = TRUE;
					}
					//다시 시작 모션
					if ( strstr( decode , szRestartWord ) ) {
						Info->MotionInfo[Info->MotionCount].iType = ANIMATIONTYPE_Revive;
					}
					//물약먹기
					if ( strstr( decode , szEatWord ) ) {
						Info->MotionInfo[Info->MotionCount].iType = ANIMATIONTYPE_Potion;
					}
					//기술동작
					if ( strstr( decode , szSkillWord ) ) {
						Info->MotionInfo[Info->MotionCount].iType = ANIMATIONTYPE_Skill;
						Info->MotionInfo[Info->MotionCount].SkillCodeList[0] = 0;
					}

					//기술동작
					if ( strstr( decode , szWarpWord ) || strstr(decode , szWarpWord2))
					{
						Info->MotionInfo[Info->MotionCount].iType = ANIMATIONTYPE_Special;
					}

					if (strstr( decode , szYahooWord))
					{
						Info->MotionInfo[Info->MotionCount].iType = ANIMATIONTYPE_Yahoo;
					}

					if (Info->MotionInfo[Info->MotionCount].iType == ANIMATIONTYPE_Die)
					{
						Info->MotionInfo[Info->MotionCount].EndFrame -= 8;
					}


					MotionLastPos = Info->MotionCount;
					Info->MotionCount++;
				}

				else if(decode[0]=='*' && strstr(decode, szMotionTalkWord) && MotionFileListCnt)
				{
					if (Info->TalkMotionCount < TALK_MOTION_INFO_MAX )
						SetIniMotionInfo(&Info->TalkMotionInfo[Info->TalkMotionCount],p,&Info->TalkMotionRate[Info->TalkMotionCount]);

					Info->TalkMotionInfo[ Info->TalkMotionCount ].MotionFrame = MotionFileListCnt-1;

					// 아표정
					if( strstr(decode, szArTalkWord) )
						Info->TalkMotionInfo[Info->TalkMotionCount].iType = (EAnimationType)CHRMOTION_STATE_TALK_AR;
					// 이표정
					else if( strstr(decode, szETalkWord) )
						Info->TalkMotionInfo[Info->TalkMotionCount].iType = (EAnimationType)CHRMOTION_STATE_TALK_E;
					// 오표정
					else if( strstr(decode, szOhTalkWord) )
						Info->TalkMotionInfo[Info->TalkMotionCount].iType = (EAnimationType)CHRMOTION_STATE_TALK_OH;
					// 눈깜빡표정
					else if( strstr(decode, szEyeTalkWord) )
						Info->TalkMotionInfo[Info->TalkMotionCount].iType = (EAnimationType)CHRMOTION_STATE_TALK_EYE;
					// 무표정(작동않함)
					else if( strstr(decode, szBlankTalkWord) )
						Info->TalkMotionInfo[Info->TalkMotionCount].iType = (EAnimationType)CHRMOTION_STATE_TALK_BLANK;
					// 웃는표정
					else if( strstr(decode, szSmileTalkWord) )
						Info->TalkMotionInfo[Info->TalkMotionCount].iType = (EAnimationType)CHRMOTION_STATE_TALK_SMILE;
                    // 화난표정
					else if( strstr(decode, szGrumbleTalkWord) )
						Info->TalkMotionInfo[Info->TalkMotionCount].iType = (EAnimationType)CHRMOTION_STATE_TALK_GRUMBLE;
					// 슬픈표정
					else if( strstr(decode, szSorrowTalkWord) )
						Info->TalkMotionInfo[Info->TalkMotionCount].iType = (EAnimationType)CHRMOTION_STATE_TALK_SORROW;
					// 놀란표정
					else if( strstr(decode, szStartledTalkWord) )
						Info->TalkMotionInfo[Info->TalkMotionCount].iType = (EAnimationType)CHRMOTION_STATE_TALK_STARTLED;
					// 고유표정
					else if( strstr(decode, szNatureTalkWord) )
						Info->TalkMotionInfo[Info->TalkMotionCount].iType = (EAnimationType)CHRMOTION_STATE_TALK_NATURE;
					// 특별표정
					else if( strstr(decode, szSpecialTalkWord) )
						Info->TalkMotionInfo[Info->TalkMotionCount].iType = (EAnimationType)CHRMOTION_STATE_TALK_SPECIAL;

					Info->TalkMotionCount++;
				}
				break;
			}

			CmdNum++;
		}

		switch(CmdNum) 
		{
		case 0:
			pb = p;
			p = GetWord( strBuff , p );
			if (strBuff[0]==34) 
				p = GetString(strBuff , pb);
			lstrcpy( Info->szMotionFile , szDirecotry );
			lstrcat( Info->szMotionFile , strBuff );
			break;

		case 17:
		case 1:
			//동작모음
			pb = p;
			p = GetWord( strBuff , p );
			if ( strBuff[0]==34 ) {	//따옴표 발견
				p = GetString( strBuff , pb );
			}
			szMotionFileList[ MotionFileListCnt ] = new char [64];
			lstrcpy( szMotionFileList[ MotionFileListCnt ] , szDirecotry );
			lstrcat( szMotionFileList[ MotionFileListCnt ] , strBuff );
			MotionFileListCnt++;
			break;

		case 2:
			//모양 파일
			p = GetWord( strBuff , p );
			lstrcpy( Info->szModelFile , szDirecotry );
			lstrcat( Info->szModelFile , strBuff );
			break;

		case 3:
			//모양 이름
			pb = p;
			p = GetWord( strBuff , p );
			if (strBuff[0]==34)
				p = GetString(strBuff , pb);
			break;
		case 4:
			//"*동작연결파일",
			p = GetWord( strBuff , p );
			lstrcpy( Info->szLinkFile , szDirecotry );
			lstrcat( Info->szLinkFile , strBuff );
			break;
		case 5:
			//"*보조동작파일",
			pb = p;
			p = GetWord( strBuff , p );
			if ( strBuff[0]==34 ) {	//따옴표 발견
				p = GetString( strBuff , pb );
			}
			
			lstrcpy( Info->szSubModelFile , szDirecotry );
			lstrcat( Info->szSubModelFile , strBuff );
			break;

		case 6:
		case 7:
		case 8:

			switch(CmdNum) {
			case 6:
				//정밀 모양
				lpModelGroup = &Info->HighModel;
				break;
			case 7:
				lpModelGroup = &Info->DefaultModel;
				break;
			case 8:
				lpModelGroup = &Info->LowModel;
				break;
			}

			for(cnt=0;cnt<4;cnt++) {
				pb = p;
				p = GetWord( strBuff , p );
				if ( !strBuff[0] ) break;

				if ( strBuff[0]==34 ) {	//따옴표 발견
					p = GetString( strBuff , pb );
				}
				if ( lpModelGroup->ModelNameCnt<4 ) {
					lstrcpy( lpModelGroup->szModelName[ lpModelGroup->ModelNameCnt++ ] , strBuff );
				}
			}
			break;

		case 9:
			//*걷는동작

			break;
		case 10:
			//*서있기동작

			break;

		case 11:
			while(1)
			{
				if (p[0]==0) 
					break;
				strBuff[0] = 0;
				p = GetWord( strBuff , p );
				if (strBuff[0])
				{
					if (lstrcmp( strBuff , "모두" )==0)
					{
						Info->MotionInfo[MotionLastPos].ItemCodeCount = 0; 
						break; 
					}
					if (lstrcmp( strBuff , "없음" )==0)
						Info->MotionInfo[MotionLastPos].ItemCodeList[Info->MotionInfo[MotionLastPos].ItemCodeCount++] = 0xFFFF;
					else
					{
						Info->MotionInfo[MotionLastPos].ItemCodeList[Info->MotionInfo[MotionLastPos].ItemCodeCount++] = 0;
					}

				}
				else
					break;
			}

			break;
		case 12:
			//"*적용직업",
			Info->MotionInfo[MotionLastPos].dwJobCodeBit = 0;
			while(1) 
			{
				p = GetWord( strBuff , p );
				if ( strBuff[0]==0 ) break;
				JobCount = 0;
				while(BitMaskJobNames[JobCount].dwBitMask) 
				{
					if ( lstrcmpi(strBuff , BitMaskJobNames[JobCount].szName ) == 0)
					{
						Info->MotionInfo[MotionLastPos].dwJobCodeBit |= BitMaskJobNames[JobCount].dwBitMask;
						break;
					}
					JobCount++;
				}
			}
			break;
		case 13:
			//"*해당위치",
			p = GetWord( strBuff , p );
			cnt = 0;

			if ( lstrcmp( strBuff, "마을" )==0 ) {
					cnt |= 1;
			}
			if ( lstrcmp( strBuff, "필드" )==0 ) {
					cnt |= 2;
			}

			p = GetWord( strBuff , p );
			if ( strBuff[0] ) {
				if ( lstrcmp( strBuff, "마을" )==0 ) {
						cnt |= 1;
				}
				if ( lstrcmp( strBuff, "필드" )==0 ) {
						cnt |= 2;
				}
			}

			if ( cnt==0 || Info->MotionInfo[MotionLastPos].iType ==ANIMATIONTYPE_Skill )
				cnt=3; 

			Info->MotionInfo[MotionLastPos].MapPosition = cnt;
			break;

		case 14:
			//"*적용기술",
			if ( Info->MotionInfo[MotionLastPos].iType ==ANIMATIONTYPE_Skill )
			{
				JobCount = 0;
				while(1)
				{
					p = GetWord(strBuff,p);
					if (strBuff[0]==0)
						break;
					cnt = 0;
					while(1)
					{
						if (!SkillDataCode[cnt].szSkillName[0]) 
							break;
						if (JobCount>=(MOTION_SKIL_MAX-1)) 
							break;
						if ( lstrcmpi( SkillDataCode[cnt].szSkillName , strBuff )==0 )
						{
							Info->MotionInfo[MotionLastPos].SkillCodeList[JobCount++] = cnt;
							break;
						}
						cnt++;
					}
				}
				Info->MotionInfo[MotionLastPos].SkillCodeList[JobCount] = 0;
			}
			break;
		case 15:	//"*표정파일연결"	(파일연결)
			pb = p;
			p = GetWord( strBuff, p );
			if( strBuff[0] == 34 )	//따옴표 발견
				p = GetString( strBuff , pb );

			lstrcpy( Info->szTalkLinkFile, szDirecotry );
			lstrcat( Info->szTalkLinkFile, strBuff );
			break;

		case 16:	//"*표정파일"
			pb = p;
			p = GetWord( strBuff, p );
			if( strBuff[0] == 34 )	//따옴표 발견
				p = GetString( strBuff , pb );

			lstrcpy( Info->szTalkMotionFile, szDirecotry );
			lstrcat( Info->szTalkMotionFile, strBuff );
			break;
		}
	}

	fclose(fp);

	int MaxRateNum, MaxRatePos;

	// NpcMotionRate
	if( Info->NpcMotionRate[ CHRMOTION_EXT ] )
	{
		MaxRateNum = MaxRatePos = CmdNum = 0;
		for( cnt=CHRMOTION_EXT; cnt < (int)Info->MotionCount; cnt++ )
		{
			if( MaxRateNum < Info->NpcMotionRate[ cnt ] )
			{
				MaxRateNum = Info->NpcMotionRate[ cnt ];
				MaxRatePos = cnt;
			}
			
            CmdNum += Info->NpcMotionRate[ cnt ];
		}
		
		if( CmdNum > 100 )
		{
			MaxRateNum -= (CmdNum - 100);
			if( MaxRateNum <= 0 )
                Info->NpcMotionRate[ CHRMOTION_EXT ] = 0;
			else
				Info->NpcMotionRate[ MaxRatePos ] = MaxRateNum;
		}
		else if( CmdNum < 100 )
		{
			MaxRateNum += (100 - CmdNum);
            Info->NpcMotionRate[ MaxRatePos ] = MaxRateNum;
		}
		///////////////////////////////////////////////////////////////

		if( Info->NpcMotionRate[ CHRMOTION_EXT ] )
		{
			MaxRatePos = 0;
			for( cnt=CHRMOTION_EXT; cnt < (int)Info->MotionCount; cnt++ )
			{
				for( CmdNum=0; CmdNum < Info->NpcMotionRate[ cnt ]; CmdNum++ )
				{
					Info->NpcMotionRateCnt[ MaxRatePos ] = cnt;
					MaxRatePos++;
				}
			}
		}
	}

	if( Info->TalkMotionRate[ CHRMOTION_EXT ] )
	{
		int MotionCntBuff[ TALK_MOTION_FILE_MAX ][ TALK_MOTION_INFO_MAX ] = {0,};
		int RateBuff[ TALK_MOTION_FILE_MAX ][ TALK_MOTION_INFO_MAX ] = {0,};
		int RateCnt[ TALK_MOTION_FILE_MAX ] = { CHRMOTION_EXT, CHRMOTION_EXT };

		for( cnt=CHRMOTION_EXT; cnt < (int)Info->TalkMotionCount; cnt++ )
		{
			if( Info->TalkMotionInfo[cnt].MotionFrame == TALK_MOTION_FILE )
			{
				MotionCntBuff[ TALK_MOTION_FILE ][ RateCnt[TALK_MOTION_FILE] ] = cnt;
				RateBuff[ TALK_MOTION_FILE ][ RateCnt[TALK_MOTION_FILE] ] = Info->TalkMotionRate[cnt];
				RateCnt[ TALK_MOTION_FILE ]++;
			}
			else if( Info->TalkMotionInfo[cnt].MotionFrame == FACIAL_MOTION_FILE )
			{
				MotionCntBuff[ FACIAL_MOTION_FILE ][ RateCnt[FACIAL_MOTION_FILE] ] = cnt;
				RateBuff[ FACIAL_MOTION_FILE ][ RateCnt[FACIAL_MOTION_FILE] ] = Info->TalkMotionRate[cnt];
				RateCnt[FACIAL_MOTION_FILE]++;
			}
		}
		for( int loop=0; loop < TALK_MOTION_FILE_MAX; loop++ )
		{
			MaxRateNum = MaxRatePos = CmdNum = 0;

			int *lpRateBuff = RateBuff[ loop ];
			for( cnt=CHRMOTION_EXT; cnt < RateCnt[ loop ]; cnt++ )
			{
				if( MaxRateNum < lpRateBuff[cnt] )
				{
					MaxRateNum = lpRateBuff[cnt];
					MaxRatePos = cnt;
				}
				
				CmdNum += lpRateBuff[ cnt ];
			}

			if( CmdNum > 100 )
			{
				MaxRateNum -= (CmdNum - 100);
				if( MaxRateNum <= 0 )
					Info->TalkMotionRate[ CHRMOTION_EXT ] = 0;
				else
					lpRateBuff[ MaxRatePos ] = MaxRateNum;
			}
			else if( CmdNum < 100 )
			{
				MaxRateNum += (100 - CmdNum);
				lpRateBuff[ MaxRatePos ] = MaxRateNum;
			}

			if( Info->TalkMotionRate[ CHRMOTION_EXT ] )
			{
				MaxRatePos = 0;
				for( cnt=CHRMOTION_EXT; cnt < RateCnt[ loop ]; cnt++ )
				{
					for( CmdNum=0; CmdNum < lpRateBuff[ cnt ]; CmdNum++ )
					{
						Info->TalkMotionRateCnt[ loop ][ MaxRatePos ] = MotionCntBuff[ loop ][ cnt ];
						MaxRatePos++;
					}
				}
			}
		}
	}
	if(MotionFileListCnt)
	{
		if(smFindPatFile(Info->szMotionFile, "smb") == FALSE)
		{
			pat3d = smASE_MergeBone(Info->szMotionFile, szMotionFileList, MotionFileListCnt);
			if (pat3d)
				delete pat3d;
		}
		else if(smFindPatFile(Info->szTalkMotionFile, "smb") == FALSE)
		{
			pat3d = smASE_MergeBone(Info->szTalkMotionFile, szMotionFileList, MotionFileListCnt,0);
			if (pat3d)
				delete pat3d;
		}

		for(cnt=MotionFileListCnt-1;cnt>=0;cnt--) 
			delete szMotionFileList[cnt];
	}

	char  *szFile = ChangeFileExt(iniFile,szFileExt);
	DWORD  dwCode = GetCodebyName( szFile );
	ModelKeyWordEncode(dwCode, Info);

	if( Info->MotionCount > CHRMOTION_EXT && Info->TalkMotionCount <= CHRMOTION_EXT)
		MotionKeyWordEncode(dwCode, Info );

	szFile = ChangeFileExt(iniFile,szFileExt);
	fopen_s(&fp, szFile, "wb");
	if( fp )
	{
		fwrite( Info , sizeof( smMODELINFO ) , 1, fp);
		fclose(fp);
	}
	if(Info->MotionCount > CHRMOTION_EXT && Info->TalkMotionCount <= CHRMOTION_EXT)
		MotionKeyWordDecode( dwCode, Info );

	return TRUE;
}
int smModelDecode( char *iniFile , smMODELINFO *Info )
{
	char  szFile[64];
	DWORD dwFileLen;
	char *lpFile;
	FILE *fp;
	int	  len;

	smMODELINFO	smModelInfo;
	ZeroMemory(Info, sizeof(smMODELINFO));

	Info->TalkMotionCount = CHRMOTION_EXT;	

	Info->MotionCount = CHRMOTION_EXT;
	Info->HighModel.ModelNameCnt = 0;
	Info->DefaultModel.ModelNameCnt = 0;
	Info->LowModel.ModelNameCnt = 0;

	len = lstrlen( iniFile );

	if (iniFile[len-4]=='.' && (iniFile[len-3]=='a' || iniFile[len-3]=='A') && (iniFile[len-2]=='s' || iniFile[len-2]=='S' ) && (iniFile[len-1]=='e' || iniFile[len-1]=='E' ))
	{
		lstrcpy( Info->szModelFile , iniFile );
		return TRUE;
	}

	for(int i=0; i < 3; i++)
	{
		switch(i)
		{
		case 0:
			lstrcpy(szFile,iniFile);
			break;

		case 1:
			lstrcpy(szFile,Info->szLinkFile);
			break;

		case 2:
			lstrcpy(szFile,Info->szTalkLinkFile);
			break;
		}

		if(szFile[0])
		{
			lpFile = smFindFile(szFile,szFileExt,&dwFileLen);
			if(lpFile && dwFileLen == sizeof(smMODELINFO))
			{
				fopen_s(&fp, lpFile, "rb");
				if(fp)
				{
					ZeroMemory(&smModelInfo, sizeof(smMODELINFO));
					fread(&smModelInfo, sizeof(smMODELINFO) , 1, fp);
					fclose(fp);

					DWORD dwCode = GetCodebyName(lpFile);

					if(ModelKeyWordDecode(dwCode, &smModelInfo) == FALSE)
						return FALSE;

					if(Info->szModelFile[0] && i > 0)
					{
						if(smModelInfo.MotionCount > CHRMOTION_EXT && i == 1)
						{
							if( MotionKeyWordDecode(dwCode, &smModelInfo) == FALSE)
								return FALSE;

							lstrcpy(Info->szMotionFile,smModelInfo.szMotionFile);
							CopyMemory(Info->MotionInfo,smModelInfo.MotionInfo, sizeof(smModelInfo.MotionInfo));
							Info->MotionCount = smModelInfo.MotionCount;

							CopyMemory(Info->NpcMotionRate, smModelInfo.NpcMotionRate, sizeof(smModelInfo.NpcMotionRate));
							CopyMemory(Info->NpcMotionRateCnt, smModelInfo.NpcMotionRateCnt, sizeof(smModelInfo.NpcMotionRateCnt));							
						}
						else if(smModelInfo.TalkMotionCount > CHRMOTION_EXT && i == 2)
						{
							lstrcpy(Info->szTalkLinkFile, smModelInfo.szTalkLinkFile);
							lstrcpy(Info->szTalkMotionFile, smModelInfo.szTalkMotionFile);
							CopyMemory( Info->TalkMotionInfo, smModelInfo.TalkMotionInfo, sizeof(smModelInfo.TalkMotionInfo));
							Info->TalkMotionCount = smModelInfo.TalkMotionCount;
							
							CopyMemory(Info->TalkMotionRate, smModelInfo.TalkMotionRate, sizeof(smModelInfo.TalkMotionRate));
							CopyMemory(Info->TalkMotionRateCnt, smModelInfo.TalkMotionRateCnt, sizeof(smModelInfo.TalkMotionRateCnt));
						}		
					}
					else
					{
						if(smModelInfo.MotionCount > CHRMOTION_EXT)
						{
							if(MotionKeyWordDecode(dwCode, &smModelInfo) == FALSE)
								return FALSE;
						}

						memcpy(Info, &smModelInfo, sizeof(smMODELINFO));
					}
				}
				else
				{
					if(AddModelDecode(szFile, Info) == FALSE)
						return FALSE;
				}
			}
			else
			{
				if( AddModelDecode(szFile, Info) == FALSE )
                    return FALSE;
			}
		}
	}

	return TRUE;
}

smCONFIG	smConfig;


char *szConfigIniCommand[] = 
{
	"*MODE",
	"*SCREENSIZE",
	"*COLORMODE",

	"*배경화면",
	"*메뉴화면",

	"*PLAYERSKIN",
	"*나쁜놈",

	"*지형모델",
	"*지형물체",

	"*배경밝기",
	"*배경선명도",
	"*조명각도",

	"*서버주소",
	"*서버포트",

	"*화면품질",
	"*관찰자모드",

	"*데이타서버주소",
	"*데이타서버포트",

	"*캐릭터서버주소",
	"*캐릭터서버포트",
	

	"*MONSTER_KEY",


	"*지형애니",
	0
};

char *szWordWinMode[5] = { "FULLSCREEN" , "WINDOW" , "SERVER" };

char *szWordTexQualty[4] = { "좋음" , "보통" , "나쁨" , "아주나쁨" };
char *InfoRegPath = "SOFTWARE\\Triglow Pictures\\PristonTale";


ODBC_CONFIG	Odbc_Config;
TRANS_SERVER_LIST	TransServerList;
rsSERVER_CONFIG	rsServerConfig;
static int	srAdminCmdCnt = 0;
DWORD GetSwapIPCode( char *szIP );


#ifdef _W_SERVER

int SetServerConfig( char *decode , char *lpPoint )
{
	int flag;
	char *p = lpPoint;
	char *pb;
	char strBuff[128];
	int cnt;

	flag = 0;

	if ( !flag && lstrcmpi(decode,"*CONNECT_CLIENT_CODE") == 0)
	{
		for(cnt = 0;cnt < 32;cnt++)
		{
			p=GetWord(strBuff,p);
			if (!strBuff[0])
				break;
			rsServerConfig.dwClientCheckSum[rsServerConfig.ClientCheckSumCount] = atoi(strBuff);
			rsServerConfig.ClientCheckSumCount++;
		}
		flag++;
	}

	if (!flag && lstrcmpi(decode , "*DISCONNECT_CLIENT_BADCODE")==0)
	{
		rsServerConfig.ClientCheckOut = TRUE;
		flag++;
	}

	if (!flag && lstrcmpi(decode , "*CLSAFE_CODE")==0)
	{
		for(cnt=0;cnt<32;cnt++)
		{
			p=GetWord(strBuff,p);
			if (!strBuff[0]) 
				break;
			rsServerConfig.dwSafeClientCode[rsServerConfig.SafeClientCodeCount] = atoi(strBuff);
			rsServerConfig.SafeClientCodeCount++;
		}
		flag++;
	}
	if (!flag && lstrcmpi(decode , "*DISCONNECT_CLSAFE_CODE")==0) 
	{
		rsServerConfig.ClientCodeCheckOut = TRUE;
		flag++;
	}
	if (!flag && lstrcmpi(decode , "*ADMIN_COMMAND")==0) 
	{
		pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);
		lstrcpy( rsServerConfig.szAdminPassword[srAdminCmdCnt] , strBuff );
		srAdminCmdCnt++;
		flag++;
	}
	if (!flag && lstrcmpi(decode , "*ADMIN_NAME")==0) 
	{
		pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);
		lstrcpy( rsServerConfig.szAdminName , strBuff );
		flag++;
	}
	if (!flag && lstrcmpi(decode , "*ADMIN_IP")==0) 
	{
		pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);
		lstrcpy( rsServerConfig.szAdminIP , strBuff );
		flag++;
	}
	if (!flag && lstrcmpi(decode , "*ADMIN_LOGIN")==0) 
	{
		pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);
		lstrcpy( rsServerConfig.szAdminLogPassword , strBuff );
		flag++;
	}
	if (!flag && lstrcmpi(decode , "*POTION_MONITOR")==0) 
	{
		pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);
		if ( strBuff[0] )
			rsServerConfig.PotionMonitor = atoi(strBuff);
		else
			rsServerConfig.PotionMonitor = 1;

		flag++;
	}
	if (!flag && lstrcmpi(decode , "*CL_PROTECT")==0) 
	{
		rsServerConfig.CheckProtect = TRUE;
		flag++;
	}

	if (!flag && lstrcmpi(decode , "*REMOVE_PROTECT_TIME")==0) 
	{
		pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);
		rsServerConfig.RemoveNProtectTime = atoi(strBuff);
		flag++;
	}
	if (!flag && lstrcmpi(decode , "*DEBUG_IP")==0) 
	{
		for(cnt=0;cnt<10;cnt++) 
		{
			p=GetWord(strBuff,p);
			if (!strBuff[0])
				break;

			lstrcpy( rsServerConfig.szDebugIP[rsServerConfig.DebugIP_Count] , strBuff );
			rsServerConfig.DebugIP_Count++;
		}
		flag++;
	}

	if (!flag && lstrcmpi( decode , "*DEBUG_ID")==0) 
	{
		for(cnt=0;cnt<32;cnt++) 
		{
			if ( rsServerConfig.DebugID_Count>=32)
				break;

			pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);

			if ( !strBuff[0] )
				break;

			lstrcpy( rsServerConfig.szDebugID[rsServerConfig.DebugID_Count] , strBuff );
			rsServerConfig.DebugID_Count++;
		}
		flag++;
	}
	if (!flag && lstrcmpi( decode , "*BLOCK_LEVEL")==0) 
	{
		pb=p;p=GetWord(strBuff,p);
		if(strBuff[0]==34)
			p=GetString(strBuff,pb);
		rsServerConfig.BlockLevel = atoi(strBuff);
		flag++;
	}
	if (!flag && lstrcmpi( decode , "*BLOCK_LOGOUT")==0) 
	{
		rsServerConfig.BlockLevel_LogOut = TRUE;
		flag++;
	}
	if (!flag && lstrcmpi( decode , "*DISCONNECT_ITEM_ERROR" )==0) 
	{
		pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);
		if ( strBuff[0] )
			rsServerConfig.ItemCodeOut = atoi(strBuff);
		else
			rsServerConfig.ItemCodeOut = 1;

		flag++;
	}
	if (!flag && lstrcmpi( decode , "*CLIENT_CHECK_FUNC")==0)
	{
		rsServerConfig.ClientFuncCheckMode = 1;
		pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);
		rsServerConfig.ClientFuncCheckMode = atoi(strBuff);
		flag++;
	}
	if (!flag && lstrcmpi(decode , "*EVENT_DAMAGEOFF")==0)
	{
		p = GetWord(strBuff,p);
		if (strBuff[0])
			rsServerConfig.Event_DamageOff = atoi(strBuff);
		else
			rsServerConfig.Event_DamageOff = 50;
		flag++;
	}
	if (!flag && lstrcmpi(decode , "*EVENT_CHILD")==0)
	{
		p=GetWord(strBuff,p);
		if ( strBuff[0] )
			rsServerConfig.Event_Child = atoi(strBuff);
		else
			rsServerConfig.Event_Child = 1;

		flag++;
	}
	if (!flag && lstrcmpi(decode , "*EVENT_CRISTAL")==0)
	{

		p=GetWord(strBuff,p);
		if ( strBuff[0] )
			rsServerConfig.Event_Cristal = atoi(strBuff);
		else
			rsServerConfig.Event_Cristal = 1;

		flag++;
	}
	if (!flag && lstrcmpi( decode , "*EVENT_POTION")==0)
	{

		p=GetWord(strBuff,p);
		rsServerConfig.Event_Potion = atoi( strBuff );
		flag++;
	}
	if (!flag && lstrcmpi( decode , "*EVENT_STARPOINT")==0)
	{
		p=GetWord(strBuff,p);
		if ( strBuff[0] )
			rsServerConfig.Event_StarPointTicket = atoi( strBuff );
		else
			rsServerConfig.Event_StarPointTicket = 40;

		flag++;
	}

	if (!flag && lstrcmpi( decode , "*EVENT_BIRTHDAY")==0)
	{
		p=GetWord(strBuff,p);
		if ( strBuff[0] )
			rsServerConfig.Event_ComicBirthDay = atoi( strBuff );
		else
			rsServerConfig.Event_ComicBirthDay = 1;

		flag++;
	}

	if (!flag && lstrcmpi( decode , "*EVENT_PUZZLE")==0)
	{
		p=GetWord(strBuff,p);
		if ( strBuff[0] )
			rsServerConfig.Event_Puzzle = atoi( strBuff );
		else
			rsServerConfig.Event_Puzzle = 200;

		flag++;
	}

	if (!flag && lstrcmpi( decode , "*EVENT_BABELHORN")==0)
	{
		p=GetWord(strBuff,p);
		if ( strBuff[0] )
			rsServerConfig.Event_BabelHorn = atoi( strBuff );
		else
			rsServerConfig.Event_BabelHorn = 4;

		if ( rsServerConfig.Event_BabelHorn>10 ) rsServerConfig.Event_BabelHorn=10;

		flag++;
	}

	if (!flag && lstrcmpi( decode , "*EVENT_NINEFOX")==0)
	{
		p=GetWord(strBuff,p);
		if ( strBuff[0] )
			rsServerConfig.Event_NineFox = atoi( strBuff );
		else
			rsServerConfig.Event_NineFox = 20;

		flag++;
	}
	if (!flag && lstrcmpi( decode , "*EVENT_CHRISTMAS")==0)
	{
		p=GetWord(strBuff,p);
		if ( strBuff[0] )
			rsServerConfig.EVENT_Christmas = atoi( strBuff );
		else
			rsServerConfig.EVENT_Christmas = 100;

		flag++;
	}
	if (!flag && lstrcmpi( decode , "*EVENT_VALENTINEDAY")==0)
	{
		p=GetWord(strBuff,p);
		if ( strBuff[0] )
			rsServerConfig.Event_ValentineDay = atoi( strBuff );
		else
			rsServerConfig.Event_ValentineDay = 100;

		flag++;
	}
	if (!flag && lstrcmpi( decode , "*EVENT_COUPLERING")==0)
	{
		p=GetWord(strBuff,p);
		if ( strBuff[0] )
			rsServerConfig.Event_CoupleRing = atoi( strBuff );
		else
			rsServerConfig.Event_CoupleRing = 100;

		flag++;
	}
	if (!flag && lstrcmpi( decode , "*EVENT_WATERMELON")==0)
	{
		p=GetWord(strBuff,p);
		if ( strBuff[0] )
			rsServerConfig.Event_Watermelon = atoi( strBuff );
		else
			rsServerConfig.Event_Watermelon = 100;

		flag++;
	}
	if (!flag && lstrcmpi( decode , "*EVENT_VALENTINE")==0)
	{
		p=GetWord(strBuff,p);
		if ( strBuff[0] )
			rsServerConfig.Event_Valentine = atoi( strBuff );
		else
			rsServerConfig.Event_Valentine = 100;

		flag++;
	}
	if (!flag && lstrcmpi( decode , "*EVENT_CANDYDAYS")==0)
	{
		p=GetWord(strBuff,p);
		if ( strBuff[0] )
			rsServerConfig.Event_Candydays = atoi( strBuff );
		else
			rsServerConfig.Event_Candydays = 100;

		flag++;
	}
	if (!flag && lstrcmpi( decode , "*EVENT_STAR")==0)
	{
		p=GetWord(strBuff,p);
		if ( strBuff[0] )
			rsServerConfig.Event_Star = atoi( strBuff );
		else
			rsServerConfig.Event_Star = 100;

		flag++;
	}
	if (!flag && lstrcmpi( decode , "*EVENT_PRISTON_ALPHABET")==0)
	{
		p=GetWord(strBuff,p);
		if ( strBuff[0] )
			rsServerConfig.Event_PristonAlphabet = atoi( strBuff );
		else
			rsServerConfig.Event_PristonAlphabet = 100;
		flag++;
	}
	if (!flag && lstrcmpi( decode , "*EVENT_WHITECONTRAST")==0)
	{
		p=GetWord(strBuff,p);
		if ( strBuff[0] )
			rsServerConfig.Event_WhiteContrast = atoi( strBuff );
		else
			rsServerConfig.Event_WhiteContrast = 100;

		flag++;
	}
	if (!flag && lstrcmpi( decode , "*EVENT_BLACKSMITH")==0)
	{
		p=GetWord(strBuff,p);
		if ( strBuff[0] )
			rsServerConfig.Event_BlackSmith = atoi( strBuff );
		else
			rsServerConfig.Event_BlackSmith = 100;

		flag++;
	}
	if (!flag && lstrcmpi( decode , "*EVENT_MAGICALGREEN")==0)
	{
		p=GetWord(strBuff,p);
		if ( strBuff[0] )
			rsServerConfig.Event_MagicalGreen = atoi( strBuff );
		else
			rsServerConfig.Event_MagicalGreen = 100;

		flag++;
	}
	if (!flag && lstrcmpi( decode , "*EVENT_TEAROFKARA")==0)
	{
		p=GetWord(strBuff,p);
		if ( strBuff[0] )
			rsServerConfig.Event_TearOfKara = atoi( strBuff );
		else
			rsServerConfig.Event_TearOfKara = 100;

		flag++;
	}
	if (!flag && lstrcmpi( decode , "*EVENT_WHITEDAY")==0)
	{

		p=GetWord(strBuff,p);
		if ( strBuff[0] )
			rsServerConfig.Event_WhiteDay = atoi( strBuff );
		else
			rsServerConfig.Event_WhiteDay = 100;

		flag++;
	}
	if (!flag && lstrcmpi( decode , "*EVENT_MORIFSHELTOM")==0)
	{
		p=GetWord(strBuff,p);
		if ( strBuff[0] )
			rsServerConfig.Event_MorifSheltom = atoi( strBuff );
		else
			rsServerConfig.Event_MorifSheltom = 1;

		flag++;
	}

	if (!flag && lstrcmpi( decode , "*EVENT_WORLDCUP")==0)
	{

		p=GetWord(strBuff,p);
		if ( strBuff[0] )
			rsServerConfig.Event_WorldCup = atoi( strBuff );
		else
			rsServerConfig.Event_WorldCup = 5;

		flag++;
	}
	if (!flag && lstrcmpi( decode , "*EVENT_WATERMELONMONSTER")==0) 
	{

		p=GetWord(strBuff,p);
		if (strBuff[0])
			rsServerConfig.Event_WarerMelonMonster = atoi( strBuff );
		else
			rsServerConfig.Event_WarerMelonMonster = 1;

		flag++;
	}
	if ( !flag && lstrcmpi( decode , "*EVENT_MOLLYWOLF")==0)
	{
		p=GetWord(strBuff,p);
		if ( strBuff[0] )
			rsServerConfig.Event_MollyWolf = atoi( strBuff );
		else
			rsServerConfig.Event_MollyWolf = 9;

		flag++;
	}
	if (!flag && lstrcmpi( decode , "*EVENT_CHICHEN_DAY")==0) 
	{
		p=GetWord(strBuff,p);
		if ( strBuff[0] )
			rsServerConfig.Event_Chichen_Day = atoi( strBuff );
		else
			rsServerConfig.Event_Chichen_Day = 1;

		flag++;
	}
	if (!flag && lstrcmpi( decode , "*EVENT_SANTAGOBLIN")==0)
	{

		p=GetWord(strBuff,p);
		if ( strBuff[0] )
			rsServerConfig.Event_SantaGoblin = atoi( strBuff );
		else
			rsServerConfig.Event_SantaGoblin = 5;

		flag++;
	}
	if (!flag && lstrcmpi( decode , "*EVENT_SUMMER_CHICKEN")==0)
	{

		p=GetWord(strBuff,p);
		if ( strBuff[0] )
			rsServerConfig.Event_SummerChicken = atoi( strBuff );
		else
			rsServerConfig.Event_SummerChicken = 5;

		flag++;
	}
	if (!flag && lstrcmpi( decode , "*EVENT_PCBANG_PET")==0)
	{
		p=GetWord(strBuff,p);
		if ( strBuff[0] )
			rsServerConfig.Event_PCBangPet = atoi( strBuff );
		else
			rsServerConfig.Event_PCBangPet = 1;

		flag++;
	}

	if (!flag && lstrcmpi( decode , "*EVENT_HALLOWEEN")==0)
	{
		p=GetWord(strBuff,p);
		if ( strBuff[0] )
			rsServerConfig.Event_GiftBox = atoi( strBuff );
		else
			rsServerConfig.Event_GiftBox = 0;

		flag++;
	}
	if (!flag && lstrcmpi( decode , "*EVENT_BLESSCASTLE")==0)
	{
		p=GetWord(strBuff,p);
		if ( strBuff[0] )
			rsServerConfig.BlessCastleMode = atoi( strBuff );
		else
			rsServerConfig.BlessCastleMode = 1;

		flag++;
	}
	if (!flag && lstrcmpi( decode , "*EVENT_SIEGE_TIME")==0) 
	{
		p=GetWord(strBuff,p);
		if (strBuff[0])
			rsServerConfig.sBlessCastle_StartTime[0] = atoi(strBuff);
		p=GetWord(strBuff,p);
		if (strBuff[0])
			rsServerConfig.sBlessCastle_StartTime[1] = atoi(strBuff);

		flag++;
	}
	if (!flag && lstrcmpi( decode , "*EVENT_BITMASK")==0) 
	{
		p=GetWord(strBuff,p);
		if (strBuff[0])
			rsServerConfig.EventPlay_BitMask = atoi( strBuff );

		flag++;
	}
	if (!flag && lstrcmpi( decode , "*EVENT_FRUIT")==0)
	{
		p = GetWord(strBuff,p);
		if (strBuff[0])
			rsServerConfig.Event_Fruit = atoi(strBuff);
		else
			rsServerConfig.Event_Fruit = 50;

		flag++;
	}
	if (!flag && lstrcmpi( decode , "*EVENT_WEATH")==0)
	{
		p = GetWord(strBuff,p);

		if (strBuff[0])
			rsServerConfig.Event_Weath = atoi(strBuff);
		else
			rsServerConfig.Event_Weath = 15;

		flag ++;
	}
	if (!flag && lstrcmpi( decode , "*DEFAULT_ITEM_USER")==0)
	{
		p=GetWord(strBuff,p);
		if ( strBuff[0] )
			rsServerConfig.StartUser_PresentItem = atoi( strBuff );
		else
			rsServerConfig.StartUser_PresentItem = TRUE;

		flag++;
	}
	if (!flag && lstrcmpi( decode , "*RECORD_JOBCHANGER")==0) 
	{
		rsServerConfig.Record_JobChanger = TRUE;;
		flag++;
	}

	if (!flag && lstrcmpi( decode , "*ENABLE_BLOCK_FOREVER" )==0) 
	{
		rsServerConfig.ForeverBlockMode = TRUE;;
		flag++;
	}
	if (!flag && lstrcmpi(decode,"*EVENT_CASTLE_EXPUP") == 0)
	{
		//rsServerConfig.Event_Castle_Expup = TRUE;
		//if (rsServerConfig.Event_Castle_Expup[rsServerConfig.])

		if (rsServerConfig.Event_ExpUpCount< 10)
		{
			p=GetWord(strBuff,p);
			if (strBuff[0])
				rsServerConfig.Event_Castle_Expup[rsServerConfig.Event_ExpUpCount].MinLevel = atoi(strBuff);

			p=GetWord(strBuff,p);
			if (strBuff[0])
				rsServerConfig.Event_Castle_Expup[rsServerConfig.Event_ExpUpCount].MaxLevel = atoi(strBuff);

			p=GetWord(strBuff,p);
			if (strBuff[0])
				rsServerConfig.Event_Castle_Expup[rsServerConfig.Event_ExpUpCount].TimeDelay = atoi(strBuff);

			rsServerConfig.Event_ExpUpCount ++;
		}
		flag ++;
	}
	if (!flag && lstrcmpi( decode , "*PERMIT_EXP" )==0) 
	{
		pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);
		rsServerConfig.Permit_Exp = atoi(strBuff);
		flag++;
	}
	if (!flag && lstrcmpi( decode , "*PERMIT_MONEY" )==0) 
	{
		pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);
		rsServerConfig.Permit_Money = atoi(strBuff);
		flag++;
	}

	if (!flag && lstrcmpi( decode , "*CLIENT_CHECK_PROCESS_TIME")==0) 
	{
		pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);
		rsServerConfig.ClientProcessTimeChk = atoi(strBuff);
		flag++;
	}
	if (!flag && lstrcmpi( decode , "*CLIENT_PROCESS_TIME_OUT" )==0) 
	{
		rsServerConfig.ClientProcessTimeChkOut = TRUE;
		flag++;
	}
	if (!flag && lstrcmpi( decode , "*CHECK_POTION_COUNT" )==0) 
	{
		pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);
		rsServerConfig.Dis_PotionError = atoi(strBuff);
		flag++;
	}
	if (!flag && lstrcmpi( decode , "*ENABLE_SERVER_EXP" )==0)
	{
		pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);

		if ( strBuff[0] ) rsServerConfig.ExpFixMode = atoi(strBuff);
		else rsServerConfig.ExpFixMode = 50;

		flag++;
	}

	if (!flag && lstrcmpi( decode , "*BLOCK_USER_PATH" )==0) 
	{
		pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);
		lstrcpy( rsServerConfig.szBlockUserPath , strBuff );
		flag++;
	}

	if (!flag && lstrcmpi( decode , "*DISP_BILLING_TIME" )==0) 
	{
		pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);
		if ( strBuff[0] )
			rsServerConfig.DispBillingTime = atoi( strBuff );
		else
			rsServerConfig.DispBillingTime = 1;

		flag++;
	}

	if (!flag && lstrcmpi( decode , "*DISABLE_LOGIN")==0)
	{

		pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);
		if ( strBuff[0] )
			rsServerConfig.Disable_LogIn = atoi( strBuff );
		else
			rsServerConfig.Disable_LogIn = 1;
		flag++;
	}
	if (!flag && lstrcmpi( decode , "*DISABLE_LOGQUE")==0)
	{
		rsServerConfig.Disable_LogQue = TRUE;
		flag++;
	}
	if (!flag && lstrcmpi( decode , "*DISABLE_CHECK_LOGOUT")==0)
	{
		rsServerConfig.Disable_CheckLogOut = TRUE;
		flag++;
	}

	if (!flag && lstrcmpi( decode , "*DISABLE_LOGINX")==0)
	{
		rsServerConfig.Disable_LogIn2 = TRUE;
		flag++;
	}

	if (!flag && lstrcmpi( decode , "*DISABLE_PCBANG")==0)
	{
		rsServerConfig.Disable_PCBang = TRUE;
		flag++;
	}

	if (!flag && lstrcmpi( decode , "*FREE_LEVEL")==0) 
	{
		pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);
		rsServerConfig.FreeLevel = atoi(strBuff);

		pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);
		if ( strBuff[0] )
			lstrcpy( rsServerConfig.szFreeGpCode , strBuff );

		flag++;
	}

	if (!flag && lstrcmpi( decode , "*PRESENT_LEVEL")==0) 
	{
		pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);
		rsServerConfig.PresentLevel = atoi(strBuff);
		flag++;
	}

	if (!flag && lstrcmpi( decode , "*ENABLE_PARTYITEM")==0) 
	{
		rsServerConfig.Enable_PartyItem = TRUE;
		flag++;
	}

	if (!flag && lstrcmpi( decode , "*CHECK_PLAYFIELD")==0)
	{
		rsServerConfig.CheckPlayField = TRUE;
		flag++;
	}
	if (!flag && lstrcmpi( decode , "*CHECK_MODELFILE")==0)
	{
		rsServerConfig.CheckModelFile = TRUE;
		flag++;
	}
	if (!flag && lstrcmpi( decode , "*DISABLE_IP")==0) 
	{

		if ( rsServerConfig.DisableIP_Count<DISABLE_IP_MAX ) 
		{
			p=GetWord(strBuff,p);
			rsServerConfig.DisableIP[rsServerConfig.DisableIP_Count][0] = GetSwapIPCode( strBuff );
			p=GetWord(strBuff,p);
			rsServerConfig.DisableIP[rsServerConfig.DisableIP_Count][1] = GetSwapIPCode( strBuff );
			rsServerConfig.DisableIP_Count++;
		}

		flag++;
	}
	if (!flag && lstrcmpi( decode , "*ENABLE_IP")==0) 
	{
		if ( rsServerConfig.EnableIP_Count<ENABLE_IP_MAX )
		{
			p=GetWord(strBuff,p);
			rsServerConfig.EnableIP[rsServerConfig.EnableIP_Count][0] = GetSwapIPCode( strBuff );
			p=GetWord(strBuff,p);
			rsServerConfig.EnableIP[rsServerConfig.EnableIP_Count][1] = GetSwapIPCode( strBuff );
			rsServerConfig.EnableIP_Count++;
		}

		flag++;
	}
	if (!flag && lstrcmpi( decode , "*ADMINISTRATOR_IP")==0) 
	{
		if ( rsServerConfig.AdminIP_Count<ADMIN_IP_MAX) 
		{
			p=GetWord(strBuff,p);
			rsServerConfig.AdminIP[rsServerConfig.AdminIP_Count][0] = GetSwapIPCode( strBuff );
			p=GetWord(strBuff,p);
			rsServerConfig.AdminIP[rsServerConfig.AdminIP_Count][1] = GetSwapIPCode( strBuff );
			rsServerConfig.AdminIP_Count++;
		}

		flag++;
	}
	if (!flag && lstrcmpi( decode , "*SYSTEM_IP")==0) 
	{
		if ( rsServerConfig.SystemIP_Count<ADMIN_IP_MAX ) 
		{
			p=GetWord(strBuff,p);
			rsServerConfig.SystemIP[rsServerConfig.SystemIP_Count][0] = GetSwapIPCode( strBuff );
			p=GetWord(strBuff,p);
			rsServerConfig.SystemIP[rsServerConfig.SystemIP_Count][1] = GetSwapIPCode( strBuff );
			rsServerConfig.SystemIP_Count++;
		}

		flag++;
	}
	if (!flag && lstrcmpi( decode , "*LOGIN_SERVER_IP")==0) 
	{
		if ( rsServerConfig.SystemIP_Count<LOGIN_IP_MAX ) 
		{
			p=GetWord(strBuff,p);
			rsServerConfig.LoginServerIP[rsServerConfig.LoginServerIP_Count][0] = GetSwapIPCode( strBuff );
			p=GetWord(strBuff,p);
			rsServerConfig.LoginServerIP[rsServerConfig.LoginServerIP_Count][1] = GetSwapIPCode( strBuff );
			rsServerConfig.LoginServerIP_Count++;
		}

		flag++;
	}
	if (!flag && lstrcmpi( decode , "*BACKUP_PATH")==0) 
	{
		pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);
		lstrcpy( rsServerConfig.szBackupPath , strBuff );
		flag++;
	}
	if (!flag && lstrcmpi( decode , "*DISABLE_DEC_SKILLPOINT")==0) 
	{

		rsServerConfig.Disable_DecSkillPoint = TRUE;
		flag++;
	}
	if (!flag && lstrcmpi( decode , "*DISABLE_QUEST")==0) 
	{

		pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);
		rsServerConfig.Disable_Quest = atoi(strBuff);
		flag++;
	}
	if (!flag && lstrcmpi( decode , "*START_FIELD")==0) 
	{

		pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);
		if ( strBuff[0] )
			rsServerConfig.FixedStartField = atoi(strBuff);
		flag++;
	}
	if (!flag && lstrcmpi( decode , "*DISABLE_THROWITEM")==0) 
	{

		pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);
		if ( strBuff[0] )
			rsServerConfig.DisableThrowItem = atoi(strBuff);
		else
			rsServerConfig.DisableThrowItem = 1;

		flag++;
	}
	if (!flag && lstrcmpi( decode , "*CRAZY_PACKET")==0) 
	{

		rsServerConfig.CrazyPacketMode = TRUE;
		flag++;
	}
	if (!flag && lstrcmpi( decode , "*NOTICE_URL")==0) 
	{
		pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);
		lstrcpy( rsServerConfig.szNoticeURL , strBuff );
		flag++;
	}
	if (!flag && lstrcmpi( decode , "*REC_ADMIN_CMD")==0) 
	{
		pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);
		if ( strBuff[0] )
			rsServerConfig.RecordAdminCommand = atoi( strBuff );
		else
			rsServerConfig.RecordAdminCommand = 2;

		flag++;
	}
	if (!flag && lstrcmpi( decode , "*SERVER_LINK_IP")==0) 
	{
		pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);
		lstrcpy( rsServerConfig.szLinkServerIP , strBuff );
		flag++;
	}
	if (!flag && lstrcmpi( decode , "*AREA_SERVER")==0) 
	{

		for( cnt=0;cnt<32;cnt++ ) 
		{
			if ( rsServerConfig.AreaServer.IP_Count>=SERVER_MAP_MAX ) 
				break;

			pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);
			if ( !strBuff[0] )
				break;

			rsServerConfig.AreaServer.dwIP[ rsServerConfig.AreaServer.IP_Count ] = inet_addr( strBuff );

			rsServerConfig.AreaServer.IP_Count++;
			rsServerConfig.AreaServer.size = sizeof(TRANS_SEVER_MAP)-(sizeof(DWORD)*(SERVER_MAP_MAX-rsServerConfig.AreaServer.IP_Count));
			rsServerConfig.AreaServer.code = smTRANSCODE_AREA_SERVER_MAP;
		}
		flag++;
	}
	if (!flag && lstrcmpi( decode , "*TT_DATA_SERVER" )==0)
	{
		cnt = rsServerConfig.TT_DataServer_Count;

		if ( cnt>=TT_DATA_SERVER_MAX ) goto skip_t;

		pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);
		if ( !strBuff[0] ) goto skip_t;
		lstrcpy( rsServerConfig.TT_DataServer[cnt].szServerID , strBuff );

		pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);
		if ( !strBuff[0] ) goto skip_t;
		lstrcpy( rsServerConfig.TT_DataServer[cnt].szServerPath, strBuff );

		rsServerConfig.TT_DataServer_Count++;
skip_t:
		flag++;
	}


	return flag;
}

#else

int SetServerConfig( char *decode , char *lpPoint )
{
	return NULL;
}

#endif


smCONFIG::smCONFIG()
{
	ZeroMemory(this,sizeof(this));

	TextureQuality		= FALSE;
	ScreenColorBit		= 16;
	NetworkQuality		= TRUE;
	Anti				= FALSE;
	Vsync				= FALSE;
	ScreenSize.x		= 800;
	ScreenSize.y		= 600;
	WinMode				= TRUE;
	CameraSight			= FALSE;
	Music				= TRUE;
	Sound				= TRUE;
	MusicVolume			= 100;
	SoundVolume			= 100;
	Ratio				= -1;
	dwDataServerPort	= 10009;
	dwServerPort		= 10009;
	dwUserServerPort	= 10009;
	dwExtendServerPort	= 10009;

	MapBright			= DEFAULT_BRIGHT;
	MapContrast			= DEFAULT_CONTRAST;
	MapLightVector.x	= fONE;
	MapLightVector.y	= -fONE;
	MapLightVector.z	= fONE/2;
}
smCONFIG::~smCONFIG()
{

}

smCONFIG *smConfigDecode(char *iniFile)
{
	FILE	*fp = NULL;
	char strBuff[64];
	char *p,*pb;
	int CmdNum;
	int MapLightAngX,MapLightAngY;
	int x,y,z;
	int cnt;

	smCONFIG *Config = &smConfig;

	srAdminCmdCnt = 0;

	ZeroMemory( &Odbc_Config , sizeof( ODBC_CONFIG ) );
	ZeroMemory( &TransServerList , sizeof( TRANS_SERVER_LIST ));
	ZeroMemory( &rsServerConfig , sizeof( rsSERVER_CONFIG ) );


#ifdef _W_SERVER
	rsServerConfig.Event_Fruit			= 50;
#endif

	fopen_s(&fp, iniFile, "rb");
	
	if ( fp==NULL )
	{
		return NULL;
	}

	while( !feof( fp ) )
	{
		if( fgets( line, 255, fp ) == NULL)
			break;

		p = GetWord( decode , line);

		CmdNum = 0;

		while(1)
		{

			if ( lstrcmp( decode, szConfigIniCommand[CmdNum] ) == 0 )
				break;

			if ( szConfigIniCommand[CmdNum]==NULL )
				break;
			CmdNum++;

#ifdef _W_SERVER
			if (SetServerConfig(decode , p)) 
				break;
#endif
		}

		switch( CmdNum )
		{
		case 0:
			//"*화면모드",
			p = GetWord( strBuff , p );
#ifdef _W_SERVER
			if ( lstrcmpi( strBuff , szWordWinMode[2])==0 ) {				//서버 모드
				Config->WinMode = -1;
				break;
			}
#endif

#ifdef _WINMODE_DEBUG
			if ( lstrcmpi( strBuff , szWordWinMode[1] )==0 ) 
				Config->WinMode = 1;
			else
				Config->WinMode = 0;
#else 
				Config->WinMode = 0;
#endif
			break;

		case 1:
			//"*화면해상도",
			p = GetWord( strBuff , p );
			Config->ScreenSize.x = atoi(strBuff);
			p = GetWord( strBuff , p );
			Config->ScreenSize.y = atoi(strBuff);
			break;

		case 2://
			//"*화면색상비트",
			p = GetWord( strBuff , p );
			//Config->ScreenColorBit = atoi(strBuff);
			break;

		case 3:
			//"*배경화면",
			p = GetWord( strBuff , p );
			lstrcpy( Config->szFile_BackGround[0] , strBuff );
			p = GetWord( strBuff , p );
			lstrcpy( Config->szFile_BackGround[1] , strBuff );
			break;

		case 4:
			//"*메뉴화면",
			p = GetWord( strBuff , p );
			lstrcpy( Config->szFile_Menu , strBuff );
			break;

		case 5:
#ifdef _WINMODE_DEBUG
			//"*주인공",
			p = GetWord( strBuff , p );
			lstrcpy( Config->szFile_Player , strBuff );
			p = GetWord( strBuff , p );
			Config->Posi_Player.x = (int)(atof(strBuff) * fONE);
			p = GetWord( strBuff , p );
			Config->Posi_Player.y = (int)(atof(strBuff) * fONE);
#endif
			break;

		case 6:
#ifdef _WINMODE_DEBUG
			//"*나쁜놈",
			p = GetWord( strBuff , p );
			lstrcpy( Config->szFile_Enemy , strBuff );
			p = GetWord( strBuff , p );
			Config->Posi_Enemy.x = (int)(atof(strBuff) * fONE);
			p = GetWord( strBuff , p );
			Config->Posi_Enemy.y = (int)(atof(strBuff) * fONE);
#endif
			break;

		case 7:
			//"*지형모델",
			p = GetWord( strBuff , p );
			lstrcpy( Config->szFile_Stage , strBuff );

			p = GetWord( strBuff , p );
			if ( strBuff[0] )
				Config->Posi_Stage.x = (int)(atof(strBuff) * fONE);

			p = GetWord( strBuff , p );

			if ( strBuff[0] )
				Config->Posi_Stage.y = (int)(atof(strBuff) * fONE);
			break;
		case 8:
			//*지형물체			
			p = GetWord( strBuff, p );
			if( Config->StageObjCnt < MAX_OBJECTMAP)
			{
				lstrcpy( Config->szFile_StageObject[ Config->StageObjCnt ], strBuff );
				Config->IsStageAniObject[ Config->StageObjCnt ] = 0;
				Config->StageObjCnt++;
			}
			break;
		case 9:
			break;

		case 10:
			break;

		case 11:
			break;
		case 12:
			//"*서버주소",
			p = GetWord( strBuff , p );
			lstrcpy( Config->szServerIP , strBuff );
			break;

		case 13:
			//"*서버포트",
			p = GetWord( strBuff , p );
			Config->dwServerPort = atoi( strBuff );
			break;

		case 14:
			//"*화면품질",
			p = GetWord( strBuff , p );

			if ( lstrcmp( strBuff , szWordTexQualty[0] )==0 ) {
				//좋음
				Config->TextureQuality = 0;
				break;
			}
			if ( lstrcmp( strBuff , szWordTexQualty[1] )==0 ) {
				//보통
				Config->TextureQuality = 1;
				break;
			}
			if ( lstrcmp( strBuff , szWordTexQualty[2] )==0 ) {
				//나쁨
				Config->TextureQuality = 2;
				break;
			}
			if ( lstrcmp( strBuff , szWordTexQualty[3] )==0 ) {
				//아주나쁨
				Config->TextureQuality = 3;
				break;
			}
			break;
		case 15:
			break;

		case 16:
			//"*데이타서버주소",
			p = GetWord( strBuff , p );
			lstrcpy( Config->szDataServerIP , strBuff );
			break;

		case 17:
			//"*데이타서버포트",
			p = GetWord( strBuff , p );
			Config->dwDataServerPort = atoi( strBuff );
			break;

		case 18:
			//"*캐릭터서버주소",
			p = GetWord( strBuff , p );
			lstrcpy( Config->szUserServerIP , strBuff );
			break;
		case 19:
			//"*캐릭터서버포트",
			p = GetWord( strBuff , p );
			Config->dwUserServerPort = atoi( strBuff );
			break;


		case 20:
			p = GetWord( strBuff , p );
			if ( lstrcmp( strBuff, szConfigIniCommand[CmdNum] )!=0 ) break;
			p = GetWord( strBuff , p );
			if ( lstrcmp( strBuff, szConfigIniCommand[CmdNum] )!=0 ) break;

			p = GetWord( strBuff , p );
			if ( strBuff[0]=='^' && strBuff[1]=='^' ) 
				Config->DebugMode = TRUE;
			break;
		case 21:
		{
				p = GetWord( strBuff , p );
				if ( lstrcmp( strBuff, szConfigIniCommand[CmdNum-1] )!=0 ) break;

				p = GetWord( strBuff , p );
				if ( strBuff[0]=='/' && strBuff[1]=='0' ) 
					Config->DebugMode = 0x100;

		}break;

		case 22:
			for(cnt=0;cnt<CONFIG_KEY_MONSTER_MAX;cnt++) 
			{
				pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);
				if ( !strBuff[0] ) break;			
				if ( Config->CmdMonsterCount>=CONFIG_KEY_MONSTER_MAX ) break;
				lstrcpy( Config->szCmdOpenMonster[Config->CmdMonsterCount++] , strBuff );
			}
			break;
		case 23:
			p = GetWord( strBuff, p );
			if( Config->StageObjCnt < MAX_OBJECTMAP)
			{
				lstrcpy( Config->szFile_StageObject[ Config->StageObjCnt ], strBuff );
				Config->IsStageAniObject[ Config->StageObjCnt ] = 1;
				Config->StageObjCnt++;
			}
			break;
		}
	}

	fclose(fp);

	smMATRIX rX , rY , mVect;
	int vx,vy,vz;

	MapLightAngY = 128 * 16;
	MapLightAngX = (128-10) * 16;
	MapLightAngX = (MapLightAngX - ANGLE_90) & ANGCLIP;

	x = 0;
	y = 0;
	z = (int)(1.5*fONE);

	smIdentityMatrix( rX );
	smIdentityMatrix( rY );

	smRotateYMatrix( rY , MapLightAngY );
	smRotateXMatrix( rX , MapLightAngX );
	smMatrixMult( mVect , rX , rY );

	vx = x * mVect._11 + y * mVect._21 + z * mVect._31;
	vy = x * mVect._12 + y * mVect._22 + z * mVect._32;
	vz = x * mVect._13 + y * mVect._23 + z * mVect._33;

	vx>>=FLOATNS;
	vy>>=FLOATNS;
	vz>>=FLOATNS;

	Config->MapLightVector.x = vx;
	Config->MapLightVector.y = vy;
	Config->MapLightVector.z = vz;

	Config->MapBright = 130;
	Config->MapContrast = 300;

	return NULL;
};

char *GetDirectoryFromFile( char *filename , char *szDirectory )
{
	int len;
	int cnt;

	if ( !szDirectory ) return NULL;

	lstrcpy( szDirectory , filename );

	len = lstrlen( szDirectory );

	for( cnt=len; cnt>=0 ; cnt-- )
		if ( szDirectory[cnt]=='\\' ) break;

	szDirectory[cnt+1] = NULL;

	return szDirectory;
}

struct szSTATE_CODE
{
	char	*szCodeName;
	DWORD	dwCode;
};

szSTATE_CODE	dwCharSoundCode[] = 
{
	{	"CYCLOPS"		,	snCHAR_SOUND_CYCLOPS		},
	{	"HOBGOBLIN"		,	snCHAR_SOUND_HOBGOBLIN		},
	{	"IMP"			,	snCHAR_SOUND_IMP			},
	{	"MINIG"			,	snCHAR_SOUND_MINIG			},
	{	"PLANT"			,	snCHAR_SOUND_PLANT			},
	{	"SKELETON"		,	snCHAR_SOUND_SKELETON		},
	{	"ZOMBI"			,	snCHAR_SOUND_ZOMBI			},
	{	"OBIT"			,	snCHAR_SOUND_OBIT			},

	{	"HOPT"			,	snCHAR_SOUND_HOPT			},
	{	"BARGON"		,	snCHAR_SOUND_BARGON			},
	{	"LEECH"			,	snCHAR_SOUND_LEECH			},
	{	"MUSHROOM"		,	snCHAR_SOUND_MUSHROOM		},

	{	"ARMA"			,	snCHAR_SOUND_ARMA			},
	{	"ARMADIL"		,	snCHAR_SOUND_ARMA			},
	{	"SCORPION"		,	snCHAR_SOUND_SCORPION		},

	{	"HEADCUTTER"	,	snCHAR_SOUND_HEADCUTTER		},
	{	"SANDLEM"		,	snCHAR_SOUND_SANDLEM		},
	{	"WEB"			,	snCHAR_SOUND_WEB			},
	{	"HOPYKING"		,	snCHAR_SOUND_HOPYKING		},
	{	"CRIP"			,	snCHAR_SOUND_CRIP			},
	{	"BUMA"			,	snCHAR_SOUND_BUMA			},
	{	"DECOY"			,	snCHAR_SOUND_DECOY			},
	{	"DORAL"			,	snCHAR_SOUND_DORAL			},
	{	"FIGON"			,	snCHAR_SOUND_FIGON			},
	{	"GOLEM"			,	snCHAR_SOUND_STONEGIANT		},
	{	"GREVEN"		,	snCHAR_SOUND_GREVEN			},
	{	"ILLUSIONKNIGHT" , snCHAR_SOUND_ILLUSIONKNIGHT	},
	{	"SKELETONRANGE" , snCHAR_SOUND_SKELETONRANGE	},
	{	"SKELETONMELEE" , snCHAR_SOUND_SKELETONMELEE	},
	{	"WOLVERLIN"		, snCHAR_SOUND_WOLVERLIN		},

	{	"RABIE"			, snCHAR_SOUND_RABIE			},
	{	"MUDY"			, snCHAR_SOUND_MUDY				},
	{	"SEN"			, snCHAR_SOUND_SEN				},
	{	"EGAN"			, snCHAR_SOUND_EGAN				},
	{	"BEEDOG"		, snCHAR_SOUND_BEEDOG			},
	{	"MUTANTPLANT"	, snCHAR_SOUND_MUTANTPLANT		},
	{	"MUTANTRABIE"	, snCHAR_SOUND_MUTANTRABIE		},
	{	"MUTANTTREE"	, snCHAR_SOUND_MUTANTTREE		},
	{	"AVELISK"		, snCHAR_SOUND_AVELISK			},
	{	"NAZ"			, snCHAR_SOUND_NAZ				},
	{	"MUMMY"			, snCHAR_SOUND_MUMMY			},
	{	"HULK"			, snCHAR_SOUND_HULK				},
	{	"HUNGKY"		, snCHAR_SOUND_HUNGKY			},
	{	"SUCCUBUS"		, snCHAR_SOUND_SUCCUBUS			},
	{	"DAWLIN"		, snCHAR_SOUND_DAWLIN			},
	{	"SHADOW"		, snCHAR_SOUND_SHADOW			},
	{	"BERSERKER"		, snCHAR_SOUND_BERSERKER		},
	{	"IRONGUARD"		, snCHAR_SOUND_IRONGUARD		},
	{	"FURY"			, snCHAR_SOUND_FURY				},
	{	"SLIVER"		, snCHAR_SOUND_SLIVER			},

	{	"RATOO"			, snCHAR_SOUND_RATOO			},
	{	"STYGIANLORD"	, snCHAR_SOUND_STYGIANLORD		},
	{	"OMICRON"		, snCHAR_SOUND_OMICRON			},
	{	"D-MACHINE"		, snCHAR_SOUND_DMACHINE			},
	{	"METRON"		, snCHAR_SOUND_METRON			},
	{	"MRGHOST"		, snCHAR_SOUND_MRGHOST			},

	{	"VAMPIRICBAT"	, snCHAR_SOUND_VAMPIRICBAT		},
	{	"MIREKEEPER"	, snCHAR_SOUND_MIREKEEPER		},
	{	"MUFFIN"		, snCHAR_SOUND_MUFFIN			},
	{	"SOLIDSNAIL"	, snCHAR_SOUND_SOLIDSNAIL		},
	{	"BEEVIL"		, snCHAR_SOUND_BEEVIL			},
	{	"NIGHTMARE"		, snCHAR_SOUND_NIGHTMARE		},
	{	"STONEGOLEM"	, snCHAR_SOUND_STONEGOLEM		},
	{	"THORNCRAWLER"	, snCHAR_SOUND_THORNCRAWLER		},
	{	"HEAVYGOBLIN"	, snCHAR_SOUND_HEAVYGOBLIN		},
	{	"EVILPLANT"		, snCHAR_SOUND_EVILPLANT		},
	{	"HAUNTINGPLANT"	, snCHAR_SOUND_HAUNTINGPLANT	},
	{	"DARKKNIGHT"	, snCHAR_SOUND_DARKKNIGHT		},
	{	"GUARDIAN-SAINT", snCHAR_SOUND_GUARDIAN_SAINT	},


	{	"CHAINGOLEM"	, snCHAR_SOUND_CHAINGOLEM		},
	{	"DEADZONE"		, snCHAR_SOUND_DEADZONE			},
	{	"GROTESQUE"		, snCHAR_SOUND_GROTESQUE		},
	{	"HYPERMACHINE"	, snCHAR_SOUND_HYPERMACHINE		},
	{	"IRONFIST"		, snCHAR_SOUND_IRONFIST			},
	{	"MORGON"		, snCHAR_SOUND_MORGON			},
	{	"MOUNTAIN"		, snCHAR_SOUND_MOUNTAIN			},
	{	"RAMPAGE"		, snCHAR_SOUND_RAMPAGE			},
	{	"RUNICGUARDIAN"	, snCHAR_SOUND_RUNICGUARDIAN	},
	{	"SADNESS"		, snCHAR_SOUND_SADNESS			},
	{	"TOWERGOLEM"	, snCHAR_SOUND_TOWERGOLEM		},
	{	"VAMPIRICBEE"	, snCHAR_SOUND_VAMPRICBEE		},
	{	"VAMPIRICMACHINE", MONSTEREFFECTID_VAMPRICMACHINE	},
	{	"AVELINARCHER"	, snCHAR_SOUND_AVELIN_ARCHER	},
	{	"AVELINQUEEN"	, snCHAR_SOUND_AVELIN_QUEEN		},
	{	"BABEL"			, snCHAR_SOUND_BABEL			},

	{	"MYSTIC"		, snCHAR_SOUND_MYSTIC			},
	{	"ICEGOBLIN"		, snCHAR_SOUND_ICEGOBLIN		},
	{	"COLDEYE"		, snCHAR_SOUND_COLDEYE			},
	{	"FROZEN"		, snCHAR_SOUND_FROZEN			},
	{	"ICEGOLEM"		, snCHAR_SOUND_ICEGOLEM			},
	{	"FROST"			, snCHAR_SOUND_FROST			},
	{	"CHAOSCARA"		, snCHAR_SOUND_CHAOSCARA		},
	{	"DEATHKNIGHT"	, snCHAR_SOUND_DEATHKNIGHT		},

	{	"GREATE_GREVEN"	, snCHAR_SOUND_GREATE_GREVEN	},
	{	"LIZARDFOLK"	, snCHAR_SOUND_LIZARDFOLK		},
	{	"M_LORD"		, snCHAR_SOUND_M_LORD			},
	{	"SPIDER"		, snCHAR_SOUND_SPIDER			},
	{	"STINGRAY"		, snCHAR_SOUND_STINGRAY			},
	{	"STRIDER"		, snCHAR_SOUND_STRIDER			},
	{	"OMU"			, snCHAR_SOUND_OMU				},

	{	"TURTLECANNON"	, snCHAR_SOUND_TURTLE_CANNON	},
	{	"DEVILBIRD"		, snCHAR_SOUND_DEVIL_BIRD		},
	{	"BLIZZARDGIANT"	, snCHAR_SOUND_BLIZZARD_GIANT	},
	{	"KELVEZU"		, snCHAR_SOUND_KELVEZU			},
	{	"DARKPHALANX"	, snCHAR_SOUND_DARKPHALANX		},
	{	"BLOODYKNIGHT"	, snCHAR_SOUND_BLOODYKNIGHT		},
	{	"CHIMERA"		, snCHAR_SOUND_CHIMERA			},
	{	"FIREWORM"		, snCHAR_SOUND_FIREWORM			},
	{	"HELLHOUND"		, snCHAR_SOUND_HELLHOUND		},
	{	"DARKGUARD"		, snCHAR_SOUND_DARKGUARD		},
	{	"DARKMAGE"		, snCHAR_SOUND_DARKMAGE			},
	{	"MONMOKOVA"		, snCHAR_SOUND_MOKOVA			},
	{	"MONTEMPLEGUARD", snCHAR_SOUND_TEMPLEGUARD		},
	{	"MONSETO"		, snCHAR_SOUND_SETO				},
	{	"MONKINGSPIDER"	, snCHAR_SOUND_KINGSPIDER		},

	{	"D_KN"			, snCHAR_SOUND_REVIVED_KNIGHT	},
	{	"D_MAGI"		, snCHAR_SOUND_REVIVED_MAGICIAN },
	{	"D_ATAL"		, snCHAR_SOUND_REVIVED_ATALANTA },
	{	"D_FI"			, snCHAR_SOUND_REVIVED_FIGTHER	},
	{	"D_AR"			, snCHAR_SOUND_REVIVED_ARCHER	},
	{	"D_MECA"		, snCHAR_SOUND_REVIVED_MECANICIAN },
	{	"D_PA"			, snCHAR_SOUND_REVIVED_PIKEMAN	},
	{	"D_PR"			, snCHAR_SOUND_REVIVED_PRIESTESS},
	{	"DEADHOPT"		, snCHAR_SOUND_DEADHOPT			},
	{	"DEADKINGHOPY"	, snCHAR_SOUND_DEADKINGHOPY		},
	{	"GORGON"		, snCHAR_SOUND_GORGON			},
	{	"HOBOGOLEM"		, snCHAR_SOUND_HOBOGOLEM		},
	
	// 쁩폭凱췰3꿔
	{	"NIKEN"			, snCHAR_SOUND_NIKEN			},
	{	"MIMIC"			, snCHAR_SOUND_MIMIC			},
	{	"KINGBAT"		, snCHAR_SOUND_KINGBAT			},
	{	"GOBLINSHAMAN"	, snCHAR_SOUND_GOBLINSHAMAN		}, 
	{	"HEST"			, snCHAR_SOUND_HEST				},

	// 轟쐴裂檢3꿔
	{	"RUCA"			, snCHAR_SOUND_RUCA				},
	{	"NAZSENIOR"		, snCHAR_SOUND_NAZSENIOR		},
	{	"IGOLATION"		, snCHAR_SOUND_IGOLATION		},
	{	"KAKOA"			, snCHAR_SOUND_KAKOA			}, 
	{	"SPRIN"			, snCHAR_SOUND_SPRIN			},
	{	"UNDEADMAPLE"	, snCHAR_SOUND_UNDEADMAPLE		},
	{	"XETAN"			, snCHAR_SOUND_XETAN			},

	{	"BEBECHICK"		, snCHAR_SOUND_BEBECHICK		},
	{	"PAPACHICK"		, snCHAR_SOUND_PAPACHICK		},

	{	"BEAR"			, snCHAR_SOUND_BEAR				},
	{	"WATERMELON"	, snCHAR_SOUND_WATERMELON		},
	{	"PUMPKINGHOST"	, snCHAR_SOUND_PUMPKINGHOST 	},
	{	"SNOWMAN"		, snCHAR_SOUND_SNOWMAN		 	},
	{	"DEVILSHY"		, snCHAR_SOUND_DEVILSHY			},
	{	"SAKURA"		, snCHAR_SOUND_SAKURA		 	},

	{	"COMA"			, snCHAR_SOUND_COMA				},
	{	"BRAZILBEAR"	, snCHAR_SOUND_BRAZILBEAR		},

	// 쳄뗘��
	{	"BOITATA"		, snCHAR_SOUND_BOITATA			},
	{	"RIBBON_HOPY"	, snCHAR_SOUND_RIBBON_HOPY		},

	// 깥룐웁떪
	{	"ICESERPENT"	, smCHAR_SOUND_ICESERPENT		},
	{	"ICEWORM"		, smCHAR_SOUND_ICEWORM			},
	{	"MINEBAT"		, smCHAR_SOUND_MINEBAT			},
	{	"MINEGOLEM"		, smCHAR_SOUND_MINEGOLEM		},
	{	"SEALCRASHER"	, smCHAR_SOUND_SEALCRASHER		},
	{	"TARANTULIKA"	, smCHAR_SOUND_TARANTULIKA		},
	{	"TULLA"			, smCHAR_SOUND_TULLA			},
	{	"UNDEADMANAGER"	, smChAR_SOUND_UNDEADMANAGER	},
	{	"UNDEADMINER"	, smCHAR_SOUND_UNDEADMINER		},

	// 릴굶밍膠
	{	"BILLY"			, smCHAR_SOUND_BILLY			},
	{	"HOUND"			, smCHAR_SOUND_HOUND			},
	{	"LENA"			, smCHAR_SOUND_LENA				},
	{	"MARIONETTE"	, smCHAR_SOUND_MARIONETTE		},
	{	"UNDEADSTALKER"	, smCHAR_SOUND_UNDEADSTALKER	},
	{	"KHANDOOR"		, smCHAR_SOUND_KHANDOOR			},

	// 코郭薑옹웁떪
	{	"ITECHNICIAN"	, smCHAR_SOUND_ITECHNICIAN		},
	{	"LTECHNICIAN"	, smCHAR_SOUND_LTECHNICIAN		},
	{	"LENGINEER"		, smCHAR_SOUND_LENGINEER		},
	{	"ISOLDIER"		, smCHAR_SOUND_ISOLDIER			},
	{	"IBOMBER"		, smCHAR_SOUND_IBOMBER			},
	{	"LGUARDIAN"		, smCHAR_SOUND_LGUARDIAN		},
	{	"IELITE"		, smCHAR_SOUND_IELITE			},
	{	"DRAXOS"		, MONSTEREFFECTID_Draxos },

	// DIGMAMA
	{	"LIZARD_BIGMAMA"	, smCHAR_SOUND_LIZARD_BIGMAMA	},
	{	"LIZADR_COMMANDER"	, smCHAR_SOUND_LIZADR_COMMANDER	},
	{	"LIZADR_DOCTOR"		, smCHAR_SOUND_LIZADR_DOCTOR	},
	{	"LIZADR_ELDER"		, smCHAR_SOUND_LIZADR_ELDER		},
	{	"LIZADR_PAPA"		, smCHAR_SOUND_LIZADR_PAPA		},
	{	"LIZADR_SOLDIER"	, smCHAR_SOUND_LIZADR_SOLDIER	},
	{	"LIZADR_DOOR"		, smCHAR_SOUND_LIZADR_DOOR		},

	//쭤옹떪氣

	{	"NIHIL"				, smCHAR_SOUND_NIHIL			},
	{	"ACERO"				, smCHAR_SOUND_ACERO			},
	{	"CHALYBS"			, smCHAR_SOUND_CHALYBS			},
	{	"GREEDY"			, smCHAR_SOUND_GREEDY			},
	{	"INFERNO"			, smCHAR_SOUND_INFERNO			},
	{	"RGUARD"			, smCHAR_SOUND_RGUARD			},
	{	"DMYSTERY"			, smCHAR_SOUND_DMYSTERY			},
	{	"IGNIS"				, smCHAR_SOUND_IGNIS			},
	{	"NAJAN"				, smCHAR_SOUND_NAJAN			},
	{	"CRIOS"				, smCHAR_SOUND_CRIOS			},
	{	"WLORD"				, smCHAR_SOUND_WLORD			},
	{	"MIDRANDA"			, smCHAR_SOUND_MIDRANDA			},
	{	"DEY"				, smCHAR_SOUND_DEY				},
	{	"GURKOB"			, smCHAR_SOUND_GURKOB			},
	{	"SHOGOTH"			, smCHAR_SOUND_SHOGOTH			},
	{	"ARHDYRA"			, smCHAR_SOUND_ARHDYRA			},
	{	"SATHLA"			, smCHAR_SOUND_SATHLA			},
	{	"FAUGN"				, smCHAR_SOUND_FAUGN			},
	{	"KOON"				, smCHAR_SOUND_KOON				},
	{	"YAGDITHA"			, smCHAR_SOUND_YAGDITHA			},

	{	"CSTONE"			, smCHAR_SOUND_CSTONE			},
	{	"BLUEMOUNTAIN"		, smCHAR_SOUND_BLUEMOUNTAIN		},
	{	"MORGONIA"			, smCHAR_SOUND_MORGONIA			},
	{	"REDEYE"			, smCHAR_SOUND_REDEYE			},
	{	"TURTLEDRAGON"		, smCHAR_SOUND_TURTLEDRAGON		},
	{	"BONEHOUND"			, smCHAR_SOUND_BONEHOUND		},
	{	"HESTIAN"			, smCHAR_SOUND_HESTIAN			},



	/////////////// 이벤트용 NPC //////////////////
	{	"MORIF"			, snCHAR_SOUND_NPC_MORIF		},
	{	"MOLLYWOLF"		, snCHAR_SOUND_NPC_MOLLYWOLF	},
	{	"SKILLMASTER"	, snCHAR_SOUND_NPC_SKILLMASTER	},
	{	"MAGE"			, snCHAR_SOUND_NPC_MAGICMASTER	},
	{	"WORLDCUP"		, snCHAR_SOUND_WORLDCUP			},

	/////////////// 스킬 소환용 //////////////////

	{	"WOLVERIN"			, snCHAR_SOUND_S_WOLVERLIN		},
	{	"METALGOLEM"		, snCHAR_SOUND_S_METALGOLEM		},
	{	"FIREELEMENTAL"		, snCHAR_SOUND_S_F_ELEMENTAL	},
	{	"ARCUDA"			, snCHAR_SOUND_S_ARCUDA			},


	///////////////// 공성 관련 물체 /////////////////////
	{	"CASTLEDOOR"		, MONSTEREFFECTID_CASTLE_DOOR },
	{	"T_CRYSTAL_R"		, snCHAR_SOUND_CASTLE_CRYSTAL_R	},
	{	"T_CRYSTAL_G"		, snCHAR_SOUND_CASTLE_CRYSTAL_G	},
	{	"T_CRYSTAL_B"		, snCHAR_SOUND_CASTLE_CRYSTAL_B	},
	{	"T_CRYSTAL_N"		, snCHAR_SOUND_CASTLE_CRYSTAL_N	},
	{	"TOWER-B"			, snCHAR_SOUND_CASTLE_TOWER_B	},

	//용병 A,B,C
	{	"SOLDIER_A"			, snCHAR_SOUND_CASTLE_SOLDER_A	},
	{	"SOLDIER_B"			, snCHAR_SOUND_CASTLE_SOLDER_B	},
	{	"SOLDIER_C"			, snCHAR_SOUND_CASTLE_SOLDER_C	},

	// 장별 - 소울스톤
	{	"S_AVELIN"				, snCHAR_SOUND_S_AVELIN	},
	{	"S_BAGON"				, snCHAR_SOUND_S_BAGON	},
	{	"S_BEEDOG"				, snCHAR_SOUND_S_BEEDOG	},
	{	"S_BEEVIL"				, snCHAR_SOUND_S_BEEVIL	},
	{	"S_BERSERKER"			, snCHAR_SOUND_S_BERSERKER	},
	{	"S_BUMA"					, snCHAR_SOUND_S_BUMA	},
	{	"S_COKRIS"				, snCHAR_SOUND_S_COKRIS	},
	{	"S_COLDEYE"			, snCHAR_SOUND_S_COLDEYE	},
	{	"S_CRYPT"				, snCHAR_SOUND_S_CRYPT	},
	{	"S_CYCLOPS"			, snCHAR_SOUND_S_CYCLOPS	},
	{	"S_DEADZONE"			, snCHAR_SOUND_S_DEADZONE	},
	{	"S_DECOY"				, snCHAR_SOUND_S_DECOY	},
	{	"S_D-Machine"			, snCHAR_SOUND_S_DMACHINE	},
	{	"S_EVILSNAIL"			, snCHAR_SOUND_S_EVILSNAIL	},
	{	"S_GREVEN"				, snCHAR_SOUND_S_GREVEN	},
	{	"S_GROTESQUE"		, snCHAR_SOUND_S_GROTESQUE	},
	{	"S_ICEGOBLIN"			, snCHAR_SOUND_S_ICEGOBLIN	},
	{	"S_ICEGOLEM"			, snCHAR_SOUND_S_ICEGOLEM	},
	{	"S_INCUBUS"				, snCHAR_SOUND_S_INCUBUS	},
	{	"S_KINGHOPY"			, snCHAR_SOUND_S_KINGHOPY	},
	{	"S_LEECH"				, snCHAR_SOUND_S_LEECH	},
	{	"S_LIZARDFOLK"		, snCHAR_SOUND_S_LIZARDFOLK	},
	{	"S_MEPHIT"				, snCHAR_SOUND_S_MEPHIT	},
	{	"S_METRON"				, snCHAR_SOUND_S_METRON	},
	{	"S_MUFFIN"				, snCHAR_SOUND_S_MUFFIN	},
	{	"S_MUMMY"				, snCHAR_SOUND_S_MUMMY	},
	{	"S_NAZ"					, snCHAR_SOUND_S_NAZ	},
	{	"S_OMEGA"				, snCHAR_SOUND_S_OMEGA	},
	{	"S_RAMPAGE"			, snCHAR_SOUND_S_RAMPAGE	},
	{	"S_SADNESS"			, snCHAR_SOUND_S_SADNESS	},
	{	"S_SLAUGHTER"			, snCHAR_SOUND_S_SLAUGHTER	},
	{	"S_SLAYON"				, snCHAR_SOUND_S_SLAYON	},
	{	"S_SLIVER"				, snCHAR_SOUND_S_SLIVER	},
	{	"S_TITAN"					, snCHAR_SOUND_S_TITAN	},
	{	"S_TOWERGOLEM"		, snCHAR_SOUND_S_TOWERGOLEM	},
	{	"S_TYPHOON"			, snCHAR_SOUND_S_TYPHOON	},
	{	"S_VAMPIRICBAT"		, snCHAR_SOUND_S_VAMPIRICBAT	},
	{	"S_WITCH"					, snCHAR_SOUND_S_WITCH	},
	{	"S_ZOMBIE"				, snCHAR_SOUND_S_ZOMBIE	},


	{	"" , 0 }
};

int GetRandomPos( int Min , int Max )
{
	int sb;
	int rnd;

	sb = (Max+1)-Min;

	if ( sb==0 ) return Max;

	rnd = rand()%sb;
	return Min+rnd;
}


///////////////////////////////////////
static int	Random_NormalMode = 0;

//최소 최대치에서 랜덤값 산출
int GetRandomPos_Normal( int inMin , int inMax )
{
	int sb,sc;
	int rnd;
	int	Min,Max;

	if ( !Random_NormalMode ) 
		return GetRandomPos( inMin , inMax );

	sc = inMax-inMin;
	sb = sc/4;

	if ( sb==0 && sc>=2 ) sb=1;

	Min = inMin+sb;
	Max = inMax-sb;

	sb = (Max+1)-Min;

	if ( sb==0 ) return Max;

	rnd = rand()%sb;
	return Min+rnd;
}

SKILL_DATA_CODE	SkillDataCode[] = 
{
	{	"xxxxxxxxxxxxx"			,	0								},		//NULL Code
		//1瘻 샙筠
	{	"ExtremeShield"			,	SKILL_PLAY_EXTREME_SHIELD		},
	{	"MechanicBomb"			,	SKILL_PLAY_MECHANIC_BOMB		},
	{	"PhysicalAbsorption"	,	SKILL_PLAY_PHYSICAL_ABSORB		},
	{	"PoisonAttribute"		,	0								},
	//2瘻
	{	"roundimpact"			,	SKILL_PLAY_GREAT_SMASH			},
	{	"Maximize"				,	SKILL_PLAY_MAXIMIZE				},
	{	"Automation"			,	SKILL_PLAY_AUTOMATION			},
	{	"Spark"					,	SKILL_PLAY_SPARK				},
	//3瘻
	{	"MetalArmor"			,	SKILL_PLAY_METAL_ARMOR			},
	{	"GrandSmash"			,	SKILL_PLAY_GRAND_SMASH			},
	{	"MechanicMastery"		,	0								},
	{	"SparkShield"			,	SKILL_PLAY_SPARK_SHIELD			},
	//4瘻
	{	"IMPULSION"				,	SKILL_PLAY_IMPULSION			},
	{	"COMPULSION"			,	SKILL_PLAY_COMPULSION			},
	{	"MAGNETICSPHERE"		,	SKILL_PLAY_MAGNETIC_SPHERE		},
	{	"METALGOLEM"			,	SKILL_PLAY_METAL_GOLEM			},
	//5瘻
	{	"LandMining"			,	SKILL_PLAY_LANDMINNING			},
	{	"HyperSonic"			,	SKILL_PLAY_H_SONIC				},
	{	"RollingSmash"			,	SKILL_PLAY_R_SMASH				},
	{	"PowerEnhance"			,	SKILL_PLAY_P_ENHENCE			},

	//1瘻 嶠却
	{	"MeleeMastery"			,	0								},
	{	"FireAttribute"			,	0								},
	{	"Raving"				,	SKILL_PLAY_RAVING				},
	{	"Impact"				,	SKILL_PLAY_IMPACT				},
	//2瘻
	{	"TripleImpact"			,	SKILL_PLAY_TRIPLE_IMPACT		},
	{	"BrutalSwing"			,	SKILL_PLAY_BRUTAL_SWING			},
	{	"Roar"					,	SKILL_PLAY_ROAR					},
	{	"RageofZecram"			,	SKILL_PLAY_RAGEOF_ZECRAM		},
	//3瘻
	{	"Concentration"			,	SKILL_PLAY_CONCENTRATION		},
	{	"AvangingCrash"			,	SKILL_PLAY_AVANGING_CRASH		},
	{	"SwiftAxe"				,	SKILL_PLAY_SWIFT_AXE			},
	{	"BoneSmash"				,	SKILL_PLAY_BONE_SMASH			},
	//4瘻
	{	"DESTROYER"				,	SKILL_PLAY_DESTROYER			},
	{	"BERSERKER"				,	SKILL_PLAY_BERSERKER			},
	{	"CYCLONESTRIKE"			,	SKILL_PLAY_CYCLONE_STRIKE		},
	{	"BoostHealth"			,	0								},
	//5瘻
	{	"DownHit"				,	SKILL_PLAY_D_HIT				},
	{	"PowerDash"				,	SKILL_PLAY_P_DASH				},
	{	"MotalBlow"				,	SKILL_PLAY_M_BLOW				},
	{	"BloodyBerserker"		,	SKILL_PLAY_B_BERSERKER			},

	//1瘻 퓜깡
	{	"PikeWind"				,	SKILL_PLAY_PIKEWIND				},
	{	"IceAttribute"			,	0								},
	{	"CriticalHit"			,	SKILL_PLAY_CRITICAL_HIT			},
	{	"JumpingCrash"			,	SKILL_PLAY_JUMPING_CRASH		},
	//2瘻
	{	"GroundPike"			,	SKILL_PLAY_GROUND_PIKE			},
	{	"Tornado"				,	SKILL_PLAY_TORNADO				},
	{	"WeaponDefenceMastery"	,	0								},
	{	"Expansion"				,	SKILL_PLAY_EXPANSION			},
	//3瘻
	{	"VenomSpear"			,	SKILL_PLAY_VENOM_SPEAR			},
	{	"Vanish"				,	SKILL_PLAY_VANISH				},
	{	"CriticalMastery"		,	0								},
	{	"ChainLance"			,	SKILL_PLAY_CHAIN_LANCE			},
	//4瘻
	{	"ASSASSINEYE"			,	SKILL_PLAY_ASSASSIN_EYE			},
	{	"CHARGINGSTRIKE"		,	SKILL_PLAY_CHARGING_STRIKE		},
	{	"VAGUE"					,	SKILL_PLAY_VAGUE				},
	{	"SHADOWMASTER"			,	SKILL_PLAY_SHADOW_MASTER		},
	//5瘻
	{	"DancingReaper"			,	SKILL_PLAY_D_REAPER				},
	{	"FinalSpear"			,	SKILL_PLAY_F_SPEAR				},
	{	"AmpliFied"				,	SKILL_PLAY_AMPLIFIED			},
	{	"SideSpinAttack"		,	SKILL_PLAY_SS_ATTACK			},

	//1瘻 묶癎
	{	"ScoutHawk"				,	SKILL_PLAY_SCOUT_HAWK			},
	{	"ShootingMastery"		,	0								},
	{	"WindArrow"				,	SKILL_PLAY_WIND_ARROW			},
	{	"PerfectAim"			,	SKILL_PLAY_PERFECT_AIM			},
	//2瘻
	{	"DionsEye"				,	0								},
	{	"Falcon"				,	SKILL_PLAY_FALCON				},
	{	"ArrowofRage"			,	SKILL_PLAY_ARROWOF_RAGE			},
	{	"Avalanche"				,	SKILL_PLAY_AVALANCHE			},
	//3瘻
	{	"ElementalShot"			,	SKILL_PLAY_ELEMENTAL_SHOT		},
	{	"GoldenFalcon"			,	SKILL_PLAY_GOLDEN_FALCON		},
	{	"BombShot"				,	SKILL_PLAY_BOMB_SHOT			},
	{	"Perforation"			,	SKILL_PLAY_PERFORATION			},
	//4瘻
	{	"RecallWolverin"		,	SKILL_PLAY_RECALL_WOLVERIN		},
	{	"EvasionMastery"		,	0								},
	{	"PhoenixShot"			,	SKILL_PLAY_PHOENIX_SHOT			},
	{	"ForceOfNature"			,	SKILL_PLAY_FORCE_OF_NATURE		},
	//5瘻
	{	"EvadEshot"				,	SKILL_PLAY_E_SHOT				},
	{	"ThunderRoop"			,	SKILL_PLAY_S_ROPE				},
	{	"NatureSplesh"			,	SKILL_PLAY_N_SPLASH				},
	{	"CircletRap"			,	SKILL_PLAY_C_TRAP				},

	//1瘻 踏舅
	{	"SwordBlast"			,	SKILL_PLAY_SWORD_BLAST			},
	{	"HolyBody"				,	SKILL_PLAY_HOLY_BODY			},
	{	"PhysicalTraning"		,	0								},
	{	"DoubleCrash"			,	SKILL_PLAY_DOUBLE_CRASH			},
	//2瘻
	{	"holyteam"				,	SKILL_PLAY_HOLY_VALOR			},
	{	"Brandish"				,	SKILL_PLAY_BRANDISH				},
	{	"Piercing"				,	SKILL_PLAY_PIERCING				},
	{	"DrasticSpirit"			,	SKILL_PLAY_DRASTIC_SPIRIT		},
	//3瘻
	{	"SwordMastery"			,	0								},
	{	"Divineinhalation"		,	SKILL_PLAY_DIVINE_INHALATION	},
	{	"HolyIncantation"		,	SKILL_PLAY_HOLY_INCANTATION		},
	{	"GrandCross"			,	SKILL_PLAY_GRAND_CROSS			},
	//4瘻
	{	"DIVINEPIERCING"		,	SKILL_PLAY_DIVINE_PIERCING		},
	{	"DIVINEPIERCING2"		,	SKILL_PLAY_DIVINE_PIERCING2		},
	{	"DIVINEPIERCING3"		,	SKILL_PLAY_DIVINE_PIERCING3		},
	{	"GODLYSHIELD"			,	SKILL_PLAY_GODLY_SHIELD			},
	{	"GODSBLESS"				,	SKILL_PLAY_GODS_BLESS			},
	{	"SWORDOFJUSTICE"		,	SKILL_PLAY_SWORD_OF_JUSTICE		},
	//5瘻
	{	"SoulBreaker"			,	SKILL_PLAY_S_BREAKER			},
	{	"CrescentMoon"			,	SKILL_PLAY_C_MOON				},
	{	"Saintblade"			,	SKILL_PLAY_S_BLADE				},
	{	"HolyBenedic"			,	SKILL_PLAY_H_BENEDIC			},

	//1瘻 침퓜
	{	"ShieldStrike"			,	SKILL_PLAY_SHIELD_STRIKE		},
	{	"Farina"				,	SKILL_PLAY_FARINA				},
	{	"ThrowingMastery"		,	0								},
	{	"VigorSpear"			,	SKILL_PLAY_VIGOR_SPEAR			},
	//2瘻
	{	"Windy"					,	SKILL_PLAY_WINDY				},
	{	"TwistJavelin"			,	SKILL_PLAY_TWIST_JAVELIN		},
	{	"SoulSucker"			,	SKILL_PLAY_SOUL_SUCKER			},
	{	"FireJavelin"			,	SKILL_PLAY_FIRE_JAVELIN			},
	//3瘻
	{	"SplitJavelin"			,	SKILL_PLAY_SPLIT_JAVELIN		},
	{	"TriumphOfValhalla"		,	SKILL_PLAY_TRIUMPH_OF_VALHALLA	},
	{	"LightningJavelin"		,	SKILL_PLAY_LIGHTNING_JAVELIN	},
	{	"StormJavelin"			,	SKILL_PLAY_STORM_JAVELIN		},
	//4瘻
	{	"HALLOFVALHALLA"		,	SKILL_PLAY_HALL_OF_VALHALLA		},
	{	"XRAGE"					,	SKILL_PLAY_X_RAGE				},
	{	"FROSTJAVELIN"			,	SKILL_PLAY_FROST_JAVELIN		},
	{	"VENGEANCE"				,	SKILL_PLAY_VENGEANCE			},
	//5瘻
	{	"Talaria"				,	SKILL_PLAY_TALARIA				},
	{	"GalaxyCoup"			,	SKILL_PLAY_G_COUP				},
	{	"SummonarCude"			,	SKILL_PLAY_S_ARCUDA				},
	{	"SnipPyfear"			,	SKILL_PLAY_S_FEAR				},

	//1瘻 셈鱇
	{	"Healing"				,	SKILL_PLAY_HEALING				},
	{	"HolyBolt"				,	SKILL_PLAY_HOLY_BOLT			},
	{	"MultiSpark"			,	SKILL_PLAY_MULTI_SPARK			},
	{	"HolyMind"				,	SKILL_PLAY_HOLY_MIND			},
	//2瘻
	{	"Meditation"			,	0								},
	{	"DivineLightning"		,	SKILL_PLAY_DIVINE_LIGHTNING		},
	{	"HolyReflection"		,	SKILL_PLAY_HOLY_REFLECTION		},
	{	"GrandHealing"			,	SKILL_PLAY_GREAT_HEALING		},
	//3瘻
	{	"VigorBall"				,	SKILL_PLAY_VIGOR_BALL			},
	{	"Resurrection"			,	SKILL_PLAY_RESURRECTION			},
	{	"Extinction"			,	SKILL_PLAY_EXTINCTION			},
	{	"VirtualLife"			,	SKILL_PLAY_VIRTUAL_LIFE			},
	//4瘻
	{	"GLACIALSPIKE"			,	SKILL_PLAY_GLACIAL_SPIKE		},
	{	"REGENERATIONFIELD"		,	SKILL_PLAY_REGENERATION_FIELD	},
	{	"CHAINLIGHTNING"		,	SKILL_PLAY_CHAIN_LIGHTNING		},
	{	"SUMMONMUSPELL"			,	SKILL_PLAY_SUMMON_MUSPELL		},
	//5瘻
	{	"SpiritImpact"			,	SKILL_PLAY_S_IMPACT				},
	{	"PiercingIce"			,	SKILL_PLAY_P_ICE				},
	{	"SummonRamiel"			,	SKILL_PLAY_S_PRMIEL				},
	{	"BlessingKrishna"		,	SKILL_PLAY_B_KRISHNA			},

	//1瘻 침랬可
	{	"Agony"					,	SKILL_PLAY_AGONY				},
	{	"FireBolt"				,	SKILL_PLAY_FIRE_BOLT			},
	{	"Zenith"				,	SKILL_PLAY_ZENITH				},
	{	"FireBall"				,	SKILL_PLAY_FIRE_BALL			},
	//2瘻
	{	"MentalMastery"			,	0								},
	{	"ColumnOfWater"			,	SKILL_PLAY_COLUMN_OF_WATER		},
	{	"EnchantWeapon"			,	SKILL_PLAY_ENCHANT_WEAPON		},
	{	"DeadRay"				,	SKILL_PLAY_DEAD_RAY				},
	//3瘻
	{	"EnergyShield"			,	SKILL_PLAY_ENERGY_SHIELD		},
	{	"Diastrophism"			,	SKILL_PLAY_DIASTROPHISM			},
	{	"SpiritElemental"		,	SKILL_PLAY_SPIRIT_ELEMENTAL		},
	{	"DancingSword"			,	SKILL_PLAY_DANCING_SWORD		},
	//4瘻
	{	"FIREELEMENTAL"			,	SKILL_PLAY_FIRE_ELEMENTAL		},
	{	"FLAMEWAVE"				,	SKILL_PLAY_FLAME_WAVE			},
	{	"DISTORTION"			,	SKILL_PLAY_DISTORTION			},
	{	"METEO"					,	SKILL_PLAY_METEO				},
	//5瘻
	{	"Silraphim"				,	SKILL_PLAY_SILRAPHIM			},
	{	"Vistenus"				,	SKILL_PLAY_V_TENUS				},
	{	"Primaignis"			,	SKILL_PLAY_P_IGNIS				},
	{	"Thirdanima"			,	SKILL_PLAY_T_ANIMA				},

	//1瘻 늬와
	{	"Stinger"				,	SKILL_PLAY_STRINGER				},
	{	"RunningHit"			,	SKILL_PLAY_RUNNING_HIT			},
	{	"DualSwordMastery"		,	0								},
	{	"Wisp"					,	SKILL_PLAY_WISP					},
	//2瘻
	{	"VenomThrone"			,	SKILL_PLAY_VENOM_THORN			},
	{	"Alas"					,	SKILL_PLAY_ALAS					},
	{	"SoulShock"				,	SKILL_PLAY_SOUL_SHOCK			},
	{	"AttackMastery"			,	0								},
	//3瘻
	{	"SoreSword"				,	SKILL_PLAY_SORE_SWORD			},
	{	"BeatUp"				,	SKILL_PLAY_BEAT_UP				},
	{	"Inpes"					,	SKILL_PLAY_INPES				},
	{	"Blind"					,	SKILL_PLAY_BLIND				},
	//4瘻
	{	"FrostWind"				,	SKILL_PLAY_FROST_WIND			},
	{	"CriticalMastery"		,	0								},
	{	"Polluted"				,	SKILL_PLAY_POLLUTE				},
	{	"PastingShadow"			,	SKILL_PLAY_PASTING_SHADOW		},
	//5瘻
	{	"ShadowBomb"			,	SKILL_PLAY_SHADOW_BOMB			},
	{	"RisingSlash"			,	SKILL_PLAY_RISING_SLASH			},
	{	"ViolenceStab"			,	SKILL_PLAY_VIOLENT_STUB			},
	{	"Storm"					,	SKILL_PLAY_SHADOW_STORM			},

	//1瘻  힉찮
	{	"DarkBolt"				,	SKILL_PLAY_DARK_BOLT			},
	{	"DarkWave"				,	SKILL_PLAY_DARK_WAVE			},
	{	"CurseLazy"				,	SKILL_PLAY_INERTIA				},
	{	"InnerPeace"			,	0								},
	//2瘻
	{	"SpiritualFlare"		,	SKILL_PLAY_SPIRITUAL_FLARE		},
	{	"SoulManacle"			,	SKILL_PLAY_SPIRITUAL_MANACLE	},
	{	"ChasingHunt"			,	SKILL_PLAY_CHASING_HUNT			},
	{	"AdventMigal"			,	SKILL_PLAY_ADVENT_MIGAL			},
	//3瘻
	{	"RainMaker"				,	SKILL_PLAY_RAINMAKER			},
	{	"LandOfGhost"			,	SKILL_PLAY_LAND_OF_GHOST		},
	{	"Haunt"					,	SKILL_PLAY_HAUNT				},
	{	"Scratch"				,	SKILL_PLAY_SCRATCH				},
	//4瘻
	{	"RecallBloodyKnight"	,	SKILL_PLAY_CRIMSON_KNIGHT		},
	{	"Judgement"				,	SKILL_PLAY_JUDGEMENT			},
	{	"AdventMidranda"		,	SKILL_PLAY_ADVENT_MIDRANDA		},
	{	"MourningOfPray"		,	SKILL_PLAY_MOURNING_PRAY		},
	//5瘻
	{	"Creed"					,	SKILL_PLAY_CREED				},
	{	"PressOfDeity"			,	SKILL_PLAY_PRESS_DEITY			},
	{	"GhostNail"				,	SKILL_PLAY_PHANTOM_NAIL			},
	{	"HightRegeneration"		,	0								},

	{	"",0 }
};

// 친謹속쵱
void ModelKeyWordEncode(DWORD dwFileCode,smMODELINFO *lpMODELINFO)
{
	char *szFile;
	int   dwCode_1, dwCode_2, dwCode_3, dwCode_4;

	if( lpMODELINFO->szLinkFile[0] )
	{
		szFile = ChangeFileExt(lpMODELINFO->szLinkFile, szFileExt);
		DWORD dwLinkCode = GetCodebyName( szFile );

		dwCode_1 = ((dwFileCode & 0x00ff0000) << 8);
		dwCode_2 = ((dwLinkCode & 0x000000ff) << 16);
		dwCode_3 = ((dwFileCode & 0x000000ff) << 8);
		dwCode_4 = ((dwLinkCode & 0xff000000) >> 24);
		lpMODELINFO->FileTypeKeyWord = (dwCode_1 | dwCode_2 | dwCode_3 | dwCode_4); 

		dwCode_1 = ((dwFileCode & 0xff000000) );
		dwCode_2 = ((dwLinkCode & 0x0000ff00) << 8);
		dwCode_3 = ((dwFileCode & 0x0000ff00) );
		dwCode_4 = ((dwLinkCode & 0x00ff0000) >> 16);
		lpMODELINFO->LinkFileKeyWord = (dwCode_1 | dwCode_2 | dwCode_3 | dwCode_4); 
	}
	else
	{
		dwCode_1 = ((dwFileCode & 0x0000ff00) << 16);
		dwCode_2 = ((dwFileCode & 0xff000000) >> 8);
		dwCode_3 = ((dwFileCode & 0x000000ff) << 8);
		dwCode_4 = ((dwFileCode & 0x00ff0000) >> 16);
		lpMODELINFO->FileTypeKeyWord = (dwCode_1 | dwCode_2 | dwCode_3 | dwCode_4); 
	}
}
int ModelKeyWordDecode(DWORD dwFileCode, smMODELINFO *lpMODELINFO)
{
	char *szFile;
	int   dwCode_1, dwCode_2, dwCode_3, dwCode_4;

	if(lpMODELINFO->szLinkFile[0])
	{
		szFile = ChangeFileExt(lpMODELINFO->szLinkFile, szFileExt);
		DWORD dwLinkCode = GetCodebyName( szFile );

		dwCode_1 = ((lpMODELINFO->LinkFileKeyWord & 0xff000000));
		dwCode_2 = ((lpMODELINFO->FileTypeKeyWord & 0xff000000)>> 8);
		dwCode_3 = ((lpMODELINFO->LinkFileKeyWord & 0x0000ff00));
		dwCode_4 = ((lpMODELINFO->FileTypeKeyWord & 0x0000ff00)>> 8);
		if( dwFileCode != (dwCode_1 | dwCode_2 | dwCode_3 | dwCode_4))
			return FALSE;

		dwCode_1 = ((lpMODELINFO->FileTypeKeyWord & 0x000000ff) << 24);
		dwCode_2 = ((lpMODELINFO->LinkFileKeyWord & 0x000000ff) << 16);
		dwCode_3 = ((lpMODELINFO->LinkFileKeyWord & 0x00ff0000) >> 8);
		dwCode_4 = ((lpMODELINFO->FileTypeKeyWord & 0x00ff0000) >> 16);
		if( dwLinkCode != (dwCode_1 | dwCode_2 | dwCode_3 | dwCode_4))
			return FALSE;
	}
	else
	{
		dwCode_1 = ((lpMODELINFO->FileTypeKeyWord & 0xff000000) >> 16);
		dwCode_2 = ((lpMODELINFO->FileTypeKeyWord & 0x00ff0000) << 8);
		dwCode_3 = ((lpMODELINFO->FileTypeKeyWord & 0x0000ff00) >> 8);
		dwCode_4 = ((lpMODELINFO->FileTypeKeyWord & 0x000000ff) << 16);
		if( dwFileCode != (dwCode_2 | dwCode_4 | dwCode_1 | dwCode_3))
			return FALSE;
	}

	return TRUE;
}
// 친謹속쵱
void MotionKeyWordEncode(DWORD dwCode, smMODELINFO *lpMODELINFO)
{
	int cnt, i, stFrm, endFrm;
	ModelAnimation *lpMotionInfo;

	cnt = lpMODELINFO->MotionCount;
	for(i=CHRMOTION_EXT; i < cnt; i++)
	{
		lpMotionInfo = &lpMODELINFO->MotionInfo[i];
		if(lpMotionInfo)
		{
			stFrm  = lpMotionInfo->StartFrame;
			endFrm = lpMotionInfo->EndFrame;
			
			if(stFrm)
			{
				lpMotionInfo->MotionKeyWord_1 = (dwCode & 0xff000000) | ((stFrm & 0x0000ff00)  << 8) | ((dwCode & 0x00ff0000) >> 8) | (stFrm & 0x000000ff);
				lpMotionInfo->StartFrame	  = ((dwCode & 0x000000ff) << 24)  | (stFrm & 0x00ff0000) | (dwCode & 0x0000ff00) | ((stFrm & 0xff000000) >> 24);
			}

			if(endFrm)
			{
				lpMotionInfo->MotionKeyWord_2 = ((dwCode & 0x000000ff) << 24 ) | ((endFrm & 0xff000000) >> 8) | (dwCode & 0x0000ff00) | ((endFrm & 0x00ff0000) >> 16);
				lpMotionInfo->EndFrame		  = ((dwCode & 0x00ff0000) << 8 ) | ((endFrm & 0x0000ff00) << 8) | ((dwCode & 0xff000000) >> 16 ) | (endFrm & 0x000000ff);
			}
		}
	}
}
int MotionKeyWordDecode( DWORD dwCode, smMODELINFO *lpMODELINFO )
{
	int cnt, i, KeyWord, Frame;
	ModelAnimation *lpMotionInfo;

	cnt = lpMODELINFO->MotionCount;
	for(i=CHRMOTION_EXT; i < cnt; i++)
	{
		lpMotionInfo = &lpMODELINFO->MotionInfo[i];
		if(lpMotionInfo)
		{
			if(lpMotionInfo->MotionKeyWord_1 || lpMotionInfo->StartFrame)
			{
				KeyWord = (lpMotionInfo->MotionKeyWord_1 & 0xff000000) | ((lpMotionInfo->MotionKeyWord_1 & 0x0000ff00) << 8 ) | (lpMotionInfo->StartFrame & 0x0000ff00) | ( (lpMotionInfo->StartFrame & 0xff000000) >> 24 );
				Frame   = ((lpMotionInfo->StartFrame & 0x000000ff) << 24 ) | (lpMotionInfo->StartFrame & 0x00ff0000) | ((lpMotionInfo->MotionKeyWord_1 & 0x00ff0000) >> 8) | (lpMotionInfo->MotionKeyWord_1 & 0x000000ff);

				if( dwCode != KeyWord )
					return FALSE;

				lpMotionInfo->MotionKeyWord_1 = 0;
				lpMotionInfo->StartFrame      = Frame;
			}

			if(lpMotionInfo->MotionKeyWord_2 || lpMotionInfo->EndFrame)
			{
				KeyWord = ((lpMotionInfo->EndFrame & 0x0000ff00) << 16) | ((lpMotionInfo->EndFrame & 0xff000000) >> 8) | (lpMotionInfo->MotionKeyWord_2 & 0x0000ff00) | ((lpMotionInfo->MotionKeyWord_2 & 0xff000000) >> 24);
				Frame   = ((lpMotionInfo->MotionKeyWord_2 & 0x00ff0000) << 8 ) | ((lpMotionInfo->MotionKeyWord_2 & 0x000000ff) << 16)| ((lpMotionInfo->EndFrame & 0x00ff0000) >> 8) | (lpMotionInfo->EndFrame & 0x000000ff);

				if( dwCode != KeyWord )
					return FALSE;

				lpMotionInfo->MotionKeyWord_2 = 0;
				lpMotionInfo->EndFrame        = Frame;
			}
		}
	}

	return TRUE;
}
int	Open_SODConfig( char *szFileName , void *lphCoreMonster , int *SodTax , char *szSodText , int *SodScoreDiv )
{

	FILE	*fp;
	char strBuff[256];
	char *p;
	char *pb;
	int NextFlag;
	int cnt;
	int hcRoundCount = 0;

	int	m_SodTax = 0;
	int m_SodScoreDiv = 0;
	char m_szSodText[256];
	sHCORE_MONSTER	hcMonster[hCORE_ROUND_MAX];
	sHCORE_MONSTER	*lpSod_Monster = (sHCORE_MONSTER *)lphCoreMonster;

	m_szSodText[0] = 0;
	memcpy( hcMonster , lpSod_Monster , sizeof(sHCORE_MONSTER)*hCORE_ROUND_MAX );

	for(cnt=0;cnt<rsHARDCORE_COUNT_END;cnt++)
	{
		hcMonster[cnt].hCoreMonster1.szName[0] = 0;
		hcMonster[cnt].hCoreMonster1.lpCharInfo = 0;
		hcMonster[cnt].hCoreMonster1.perCount = 0;

		hcMonster[cnt].hCoreMonster2.szName[0] = 0;
		hcMonster[cnt].hCoreMonster2.lpCharInfo = 0;
		hcMonster[cnt].hCoreMonster2.perCount = 0;

		hcMonster[cnt].hCoreMonster3.szName[0] = 0;
		hcMonster[cnt].hCoreMonster3.lpCharInfo = 0;
		hcMonster[cnt].hCoreMonster3.perCount = 0;

		hcMonster[cnt].hCoreMonster4.szName[0] = 0;
		hcMonster[cnt].hCoreMonster4.lpCharInfo = 0;
		hcMonster[cnt].hCoreMonster4.perCount = 0;

		hcMonster[cnt].hCoreMonsterBoss.szName[0] = 0;
		hcMonster[cnt].hCoreMonsterBoss.lpCharInfo = 0;
		hcMonster[cnt].hCoreMonsterBoss.perCount = 0;

		hcMonster[cnt].MaxMonster = 0;
	}


	fopen_s(&fp, szFileName, "rb");
	if ( fp==NULL ) 
		return FALSE;

	while( !feof( fp ) )
	{
		if( fgets( line, 255, fp ) == NULL)	
			break;

		p = GetWord( decode , line);

		NextFlag = 0;

		///////////////// 세율 ///////////////////////
		if ( lstrcmpi( decode , "*BELATRA_TAX" )==0 ) {

			pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);
			if ( strBuff[0] ) m_SodTax = atoi( strBuff );

			NextFlag = TRUE;
		}


		///////////////// 설명 ///////////////////////
		if ( !NextFlag && lstrcmpi( decode , "*BELATRA_TEXT" )==0 ) {

			pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);
			lstrcpy( m_szSodText , strBuff );

			NextFlag = TRUE;
		}

		///////////////// 설명 ///////////////////////
		if ( !NextFlag && lstrcmpi( decode , "*BELATRA_DIVSCORE" )==0 ) {

			pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);
			if ( strBuff[0] ) m_SodScoreDiv = atoi( strBuff );

			NextFlag = TRUE;
		}


		///////////////// 몬스터 ///////////////////////
		if ( !NextFlag && lstrcmpi( decode , "*BELATRA_MONSTER" )==0 ) {
			if ( hcRoundCount<rsHARDCORE_COUNT_END ) {
				pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);		//1st 몬스터
				lstrcpy( hcMonster[hcRoundCount].hCoreMonster1.szName , strBuff );
				p=GetWord(strBuff,p);
				hcMonster[hcRoundCount].hCoreMonster1.perCount = atoi(strBuff);

				pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);		//2nd 몬스터
				lstrcpy( hcMonster[hcRoundCount].hCoreMonster2.szName , strBuff );
				p=GetWord(strBuff,p);
				hcMonster[hcRoundCount].hCoreMonster2.perCount = atoi(strBuff);

				pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);		//3rd 몬스터
				lstrcpy( hcMonster[hcRoundCount].hCoreMonster3.szName , strBuff );
				p=GetWord(strBuff,p);
				hcMonster[hcRoundCount].hCoreMonster3.perCount = atoi(strBuff);

				pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);		//4th 몬스터
				lstrcpy( hcMonster[hcRoundCount].hCoreMonster4.szName , strBuff );
				p=GetWord(strBuff,p);
				hcMonster[hcRoundCount].hCoreMonster4.perCount = atoi(strBuff);

				pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);		//보스 몬스터
				lstrcpy( hcMonster[hcRoundCount].hCoreMonsterBoss.szName , strBuff );
				hcMonster[hcRoundCount].hCoreMonsterBoss.perCount = 0;

				p=GetWord(strBuff,p);														//출현제한수
				hcMonster[hcRoundCount].MaxMonster = atoi(strBuff);

				hcRoundCount ++;
			}
			NextFlag = TRUE;
		}
	}
	fclose(fp);

	if ( hcRoundCount<rsHARDCORE_COUNT_END ) return 0;

	if ( m_SodTax>=0 && m_SodTax<100 ) 	*SodTax = m_SodTax;
	if ( m_szSodText[0] ) lstrcpy( szSodText , m_szSodText );
	if ( m_SodScoreDiv>0 ) 	*SodScoreDiv = m_SodScoreDiv;

	memcpy( lpSod_Monster , hcMonster , sizeof(sHCORE_MONSTER)*hCORE_ROUND_MAX );

	return 1;		//나중에 갯수 추가된다면 숫자가 그룹만큼 리턴
}