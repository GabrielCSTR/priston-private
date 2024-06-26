#include "StdAfx.h"

#include "smwsock.h"
#include "character.h"
#include "playmain.h"
#include "srcsound\\dxwav.h"
#include "fileread.h"

#include "particle.h"
#include "netplay.h"

#include "effectsnd.h"

#include "record.h"
#include "playsub.h"
#include "resource.h"
#include "drawsub.h"
#include "skillsub.h"

#include "actiongame.h"


int ActionKeyAngle;
int	ActionKeyFlag = 0;
int ActionKeySpace = 0;
int ActionKeyControl = 0;

int		ActionKeyDash = 0;
DWORD	dwActionKeyTime = 0;
int		ActionDashMode = 0;
int		ActionKeyOld = 0;
short	ActionMouseClick[2] = { 0 , 0 };

Unit *agFindAttack();
scITEM *agFindItem();
Unit *agFindUser();


int ActionGameMain()
{
	int KeyFlag = 0;
	DWORD dwKeyBitFlag = 0;

	ActionKeyAngle = 0;

	if (lpCurPlayer->psModelAnimation->iType < ANIMATIONTYPE_Attack)
	{
		if (VRKeyBuff[VK_UP]) 
		{
			ActionKeyOld = VK_UP;
			dwKeyBitFlag |= 1;
			KeyFlag++;
		}
		else if (VRKeyBuff[VK_DOWN]) 
		{
			ActionKeyOld = VK_DOWN;
			dwKeyBitFlag |= 2;
			KeyFlag++;
		}

		if (VRKeyBuff[VK_RIGHT]) 
		{
			if (!ActionKeyOld && ActionKeyDash==VK_RIGHT && (dwPlayTime-dwActionKeyTime)<500)
				ActionDashMode = TRUE;

			if (ActionDashMode && ActionKeyDash!=VK_RIGHT )
				ActionDashMode = FALSE;

			ActionKeyOld = VK_RIGHT;
			dwKeyBitFlag |= 4;
			KeyFlag++;
		}
		else if (VRKeyBuff[VK_LEFT]) 
		{
			if (!ActionKeyOld && ActionKeyDash==VK_LEFT && (dwPlayTime-dwActionKeyTime)<500)
				ActionDashMode = TRUE;

			if (ActionDashMode && ActionKeyDash!=VK_LEFT)
				ActionDashMode = FALSE;

			ActionKeyOld = VK_LEFT;
			dwKeyBitFlag |= 8;
			KeyFlag++;
		}
		else 
		{
			if (ActionDashMode)
			{
				ActionKeyOld = 0;
				ActionDashMode = FALSE;
			}
		}
	}
	if (!KeyFlag)
	{
		if (ActionKeyOld)
		{
			ActionKeyDash = ActionKeyOld;
			dwActionKeyTime = dwPlayTime;
			ActionKeyOld = 0;
		}
	}

	switch(dwKeyBitFlag) 
	{
	case 1:
		if (lpCurPlayer->Angle.y<ANGLE_180)
			ActionKeyAngle = 1;
		else
			ActionKeyAngle = (-1)&ANGCLIP;
		break;
	case 2:
		if (lpCurPlayer->Angle.y<ANGLE_180)
			ActionKeyAngle = ANGLE_180-1; 
		else
			ActionKeyAngle = ANGLE_180+1; 
		break;
	case 4:
		ActionKeyAngle = ANGLE_90;
		break;
	case 5:
		ActionKeyAngle = ANGLE_45;
		break;
	case 6:
		ActionKeyAngle = ANGLE_90+ANGLE_45;
		break;
	case 8:
		ActionKeyAngle = ANGLE_270;
		break;
	case 9:
		ActionKeyAngle = ANGLE_270+ANGLE_45; 
		break;
	case 10:
		ActionKeyAngle = ANGLE_270-ANGLE_45; 
		break;
	}
	if (KeyFlag)
	{
		lpCurPlayer->Angle.y = ActionKeyAngle;
		lpCurPlayer->MoveFlag = TRUE;
		ActionKeyFlag = TRUE;
	}
	else if (ActionKeyFlag==TRUE)
	{
		lpCurPlayer->MoveFlag = FALSE;
		ActionKeyFlag = FALSE;
		CancelAttack();
	}
	if (VRKeyBuff[VK_SPACE] || ActionMouseClick[0]==2)
	{
		if ((!ActionKeySpace || ActionMouseClick[0]==2) && lpCurPlayer->psModelAnimation->iType != ANIMATIONTYPE_Attack)
		{
			Unit *lpChar = agFindAttack();
			if (lpChar)
			{
				lpCharSelPlayer = lpChar;
				lpSelItem = 0;
				SelMouseButton = 1;
				TraceAttackPlay();
			}
			else 
			{
				scITEM *lpItem = agFindItem();
				if (lpItem)
				{
					lpCharSelPlayer = 0;
					lpSelItem = lpItem;
					SelMouseButton = 1;
					TraceAttackPlay();
				}
				else 
				{
					if (lpCurPlayer->psModelAnimation->iType < ANIMATIONTYPE_Attack)
					{
						lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Attack);
						lpCurPlayer->chrAttackTarget = 0;
						lpCurPlayer->AttackCritcal = -1;
					}
				}
			}
		}

		ActionKeySpace = TRUE;
		ActionMouseClick[0] = 0;
	}
	else 
		ActionKeySpace = FALSE;

	if (VRKeyBuff[VK_CONTROL] || ActionMouseClick[1])
	{
		if ((!ActionKeyControl || ActionMouseClick[1]) && lpCurPlayer->psModelAnimation->iType != ANIMATIONTYPE_Attack)
		{
			KeyFlag = 1;

			if (sinSkill.pRightSkill && lpCurPlayer->psModelAnimation->iType != ANIMATIONTYPE_Attack && lpCurPlayer->psModelAnimation->iType != ANIMATIONTYPE_Attack)
			{
				if (lpCurPlayer->psModelAnimation->iType != ANIMATIONTYPE_Potion)
				{
					if (OpenPlaySkill(sinSkill.pRightSkill)) 
						KeyFlag = 0;
				}
			}
			if (KeyFlag)
			{
				Unit *lpChar;

				if (sinSkill.pRightSkill &&(sinSkill.pRightSkill->CODE==SKILL_HEALING || sinSkill.pRightSkill->CODE==SKILL_ENCHANT_WEAPON || sinSkill.pRightSkill->CODE==SKILL_VIRTUAL_LIFE || sinSkill.pRightSkill->CODE==SKILL_TRIUMPH_OF_VALHALLA)) 
					lpChar = agFindUser();
				else
					lpChar = agFindAttack();

				if (lpChar)
				{
					lpCharSelPlayer = lpChar;
					lpSelItem = 0;
					SelMouseButton = 2;
					TraceAttackPlay();
				}
				else 
				{
					scITEM *lpItem = agFindItem();
					if (lpItem)
					{
						lpCharSelPlayer = 0;
						lpSelItem = lpItem;
						SelMouseButton = 1;
						TraceAttackPlay();
					}
					else 
					{
						if (lpCurPlayer->psModelAnimation->iType < ANIMATIONTYPE_Attack)
						{
							lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Attack);
							lpCurPlayer->chrAttackTarget = 0;
							lpCurPlayer->AttackCritcal = -1;
						}
					}
				}
			}
		}

		ActionKeyControl = TRUE;
		ActionMouseClick[1] = FALSE;
	}
	else 
		ActionKeyControl = FALSE;

	return TRUE;
}


Unit *agFindAttack()
{
	int cnt;
	int x,z;
	int flag;
	Unit *lpSelChar = 0;

	int AttackRange = 50*fONE;							//맨속 공격 거리 

	if ( lpCurPlayer->dwActionItemCode ) {
		AttackRange += lpCurPlayer->AttackToolRange;	//무기 길이 더함
	}

	//원거리 공격 거리
	if ( lpCurPlayer->ShootingMode ) {
		AttackRange = lpCurPlayer->sCharacterData.iAttackRange*fONE;
	}


	int lpSelRange = AttackRange;

	for( cnt=0;cnt< MAX_UNITS;cnt++) {
		if ( chrOtherPlayer[cnt].bActive && chrOtherPlayer[cnt].DisplayFlag &&
			chrOtherPlayer[cnt].psModelAnimation->iType != ANIMATIONTYPE_Die &&
			chrOtherPlayer[cnt].sCharacterData.iType != CHARACTERTYPE_Player && chrOtherPlayer[cnt].RendSucess  &&
			chrOtherPlayer[cnt].sCharacterData.iMonsterType !=MONSTERTYPE_Friendly )
		{
			flag = 0;

  			z = (lpCurPlayer->pZ - chrOtherPlayer[cnt].pZ)>>FLOATNS;
			x = abs(lpCurPlayer->pX - chrOtherPlayer[cnt].pX);
			if ( abs(z)<32 ) flag++;
			if ( x<AttackRange ) flag++;

			if ( lpCurPlayer->Angle.y<ANGLE_180 && lpCurPlayer->pX<chrOtherPlayer[cnt].pX ) flag++;
			else if ( lpCurPlayer->Angle.y>=ANGLE_180 && lpCurPlayer->pX>chrOtherPlayer[cnt].pX ) flag++;

			if ( flag>=3 ) {

				if ( !lpSelChar || lpSelRange>x ) {
					lpSelChar = &chrOtherPlayer[cnt];
					lpSelRange = x;
				}
			}
		}
	}

	return lpSelChar;
}


Unit *agFindUser()
{
	int cnt;
	int x,z;
	int flag;
	Unit *lpSelChar = 0;

	int AttackRange = 50*fONE;							//맨속 공격 거리 

	if ( lpCurPlayer->dwActionItemCode ) {
		AttackRange += lpCurPlayer->AttackToolRange;	//무기 길이 더함
	}

	//원거리 공격 거리
	if ( lpCurPlayer->ShootingMode ) {
		AttackRange = lpCurPlayer->sCharacterData.iAttackRange*fONE;
	}


	int lpSelRange = AttackRange;

	for( cnt=0;cnt< MAX_UNITS;cnt++) 
	{
		if ( chrOtherPlayer[cnt].bActive && chrOtherPlayer[cnt].DisplayFlag &&
			chrOtherPlayer[cnt].psModelAnimation->iType != ANIMATIONTYPE_Die &&
			chrOtherPlayer[cnt].RendSucess  &&
			(chrOtherPlayer[cnt].sCharacterData.iType == CHARACTERTYPE_Player || chrOtherPlayer[cnt].sCharacterData.iMonsterType ==MONSTERTYPE_Friendly) )
		{
			flag = 0;

  			z = (lpCurPlayer->pZ - chrOtherPlayer[cnt].pZ)>>FLOATNS;
			x = abs(lpCurPlayer->pX - chrOtherPlayer[cnt].pX);
			if ( abs(z)<32 ) flag++;
			if ( x<AttackRange ) flag++;

			if ( lpCurPlayer->Angle.y<ANGLE_180 && lpCurPlayer->pX<chrOtherPlayer[cnt].pX ) flag++;
			else if ( lpCurPlayer->Angle.y>=ANGLE_180 && lpCurPlayer->pX>chrOtherPlayer[cnt].pX ) flag++;

			if ( flag>=3 ) {

				if ( !lpSelChar || lpSelRange>x ) {
					lpSelChar = &chrOtherPlayer[cnt];
					lpSelRange = x;
				}
			}
		}
	}

	return lpSelChar;
}


scITEM *agFindItem()
{
	int cnt;
	int x,z;
	int flag;
	scITEM *lpSelItem = 0;

	int GetRange = 32*fONE;							//맨속 공격 거리 
	int lpSelRange = GetRange;


	for(cnt=0;cnt<DISP_ITEM_MAX;cnt++)
	{
		if ( scItems[cnt].Flag )
		{
			flag = 0;
  			z = (lpCurPlayer->pZ - scItems[cnt].pZ)>>FLOATNS;
			x = abs(lpCurPlayer->pX - scItems[cnt].pX);
			if ( abs(z)<16 ) flag++;
			if ( x<GetRange ) flag++;

			if ( flag>=2 ) {
				if ( !lpSelItem || lpSelRange>x ) {
					lpSelItem = &scItems[cnt];
					lpSelRange = x;
				}
			}

		}
	}
	return lpSelItem;
}




