#include "StdAfx.h"
#include "HoNewEffectHeader.h"
#include "HoNewEffectFunction.h"
#include "HoEffectManager.h"
#include "HoEffectMain.h"
#include "HoEffectController.h"

#include "..\\..\\HoMinMax.h"
#include "..\\..\\HoNewParticle.h"
#include "..\\..\\HoNewParticleMgr.h"
#include "..\\..\\AssaParticle.h"
void SkillMetalionImpulsionHit(Unit **pChar, int charCount)
{
 	if(charCount < 2)
		return;

	point3 currentPos;
	point3 desPos;

	POINT3D partCurPos;
	POINT3D partDesPos;
	//2개만 연결하는 경우만 구현되었음
 	for(int index = 0; index < charCount-1; index++)
	{
 		HoEffectType_Attach_AvaterToAvater *effectType = new HoEffectType_Attach_AvaterToAvater();
		partCurPos.x = pChar[index]->pX;
		partCurPos.y = pChar[index]->pY;
		partCurPos.z = pChar[index]->pZ;

		partDesPos.x = pChar[index+1]->pX;
		partDesPos.y = pChar[index+1]->pY;
		partDesPos.z = pChar[index+1]->pZ;

		int num1 = g_NewParticleMgr.Start("Skill4ImpulsionLight", partCurPos);
		int num2 = g_NewParticleMgr.Start("Skill4ImpulsionLight", partDesPos);

		effectType->Init(pChar[index], pChar[index+1], num1, num2);
		currentPos.x = (float)pChar[index]->pX/256.f;
		currentPos.y = (float)pChar[index]->pY/256.f;
		currentPos.z = (float)pChar[index]->pZ/256.f;

		desPos.x = (float)pChar[index+1]->pX/256.f;
		desPos.y = (float)pChar[index+1]->pY/256.f;
		desPos.z = (float)pChar[index+1]->pZ/256.f;

		effectType->m_AxialController.Init("Effect\\NewEffect\\Res\\TextureHit\\spark01_0.bmp", 4, 0.005f);
		effectType->m_AxialController.InitLoop(1);
		effectType->m_AxialController.InitEndTime(1.f);
		effectType->m_AxialController.InitColor(150,255,200, 255);
		effectType->m_AxialController.InitSize(15,25);
		effectType->m_AxialController.InitPos(currentPos.x, currentPos.y, currentPos.z, desPos.x, desPos.y, desPos.z);

		HoEffectEventColor *eventColor = new HoEffectEventColor;
		eventColor->SetStartTime(HoEffectMinMax<float>(0.f,0.f));
		eventColor->SetFade(true);
		HoEffectMinMax<color4> color;
		color.Max.r = 150;
		color.Min.r = 150;
		color.Max.g = 255;
		color.Min.g = 255;
		color.Max.b = 150;
		color.Min.b = 150;
		color.Max.a = 150;
		color.Min.a = 150;
		eventColor->Set(color);
		effectType->m_AxialController.AddEvent(eventColor);

		eventColor = NULL;
		eventColor = new HoEffectEventColor;
		eventColor->SetStartTime(HoEffectMinMax<float>(0.4f, 0.4f));
		eventColor->SetFade(true);
		color.Max.r = 150;
		color.Min.r = 150;
		color.Max.g = 255;
		color.Min.g = 255;
		color.Max.b = 150;
		color.Min.b = 150;
		color.Max.a = 255;
		color.Min.a = 255;
		eventColor->Set(color);
		effectType->m_AxialController.AddEvent(eventColor);
		
		eventColor = NULL;
		eventColor = new HoEffectEventColor;
		eventColor->SetStartTime(HoEffectMinMax<float>(0.6f, 0.6f));
		eventColor->SetFade(true);
		color.Max.r = 150;
		color.Min.r = 150;
		color.Max.g = 255;
		color.Min.g = 255;
		color.Max.b = 150;
		color.Min.b = 150;
		color.Max.a = 255;
		color.Min.a = 255;
		eventColor->Set(color);
		effectType->m_AxialController.AddEvent(eventColor);

		eventColor = NULL;
		eventColor = new HoEffectEventColor;
		eventColor->SetStartTime(HoEffectMinMax<float>(1, 1));
		eventColor->SetFade(true);
		color.Max.r = 150;
		color.Min.r = 150;
		color.Max.g = 255;
		color.Min.g = 255;
		color.Max.b = 150;
		color.Min.b = 150;
		color.Max.a =  0;
		color.Min.a = 0;
		eventColor->Set(color);
		effectType->m_AxialController.AddEvent(eventColor);

		effectType->m_AxialController.Main(0.f);
		effectType->m_AxialController.CreateFadeList();

		HoEffectManager::GetInstance()->AddEffect(effectType);
	}
}
// 瓜�楊�븟
void SkillMetalionCompulsion(Unit *pChar)
{
 	HoEffectGroup *effectGroup = NULL;
	effectGroup = MainWindow.LoadScript("Effect\\NewEffect\\SkillMetalionCompulsion1.lua");
	if(effectGroup)
	{
		HoEffectType_Default *effectType = new HoEffectType_Default();
		effectType->Init(effectGroup, pChar->pX,pChar->pY, pChar->pZ,0,pChar->Angle.y,0);
		HoEffectManager::GetInstance()->AddEffect(effectType);
	}
}
// 우醵댔샌
void SkillMetalionHyperSonic(Unit *pChar)
{
	HoEffectGroup *effectGroup = NULL;
	effectGroup = MainWindow.LoadScript("Effect\\NewEffect\\Skill5_Mecanician_HyperSonic.lua");
	if(effectGroup)
	{
		HoEffectType_Default *effectType = new HoEffectType_Default();
		effectType->Init(effectGroup, pChar->pX,pChar->pY, pChar->pZ,0,pChar->Angle.y,0);
		HoEffectManager::GetInstance()->AddEffect(effectType);
	}
}


void SkillMetalionSphereDefence(POINT3D *curPos, POINT3D *desPos, bool flag)
{
	g_NewParticleMgr.Start("magneticShot", *curPos);
	if(flag)
	{
		g_NewParticleMgr.Start("magneticShot", *desPos);
		SetDynLight( desPos->x, desPos->y, desPos->z, 255, 255, 255, 255, 100, 3);
	}

	Assa = SetAssaEffect(100,"spark01_01.bmp",0,curPos,0);
	AssaGetAniFileMat(cAssaEffect[Assa]);
	cAssaEffect[Assa]->AniDelayTime = 3;
	cAssaEffect[Assa]->Face.r = 150;
	cAssaEffect[Assa]->Face.g = 255;
	cAssaEffect[Assa]->Face.b = 150;
	cAssaEffect[Assa]->Face.Transparency = 255;
	cAssaEffect[Assa]->Size.w = 5000;
	cAssaEffect[Assa]->FACE_TYPE = ASSAFACE_SCALE; 
	
	cAssaEffect[Assa]->ScalePosi.x = desPos->x - curPos->x;
	cAssaEffect[Assa]->ScalePosi.y = desPos->y - curPos->y;
	cAssaEffect[Assa]->ScalePosi.z = desPos->z - curPos->z;

	Assa = SetAssaEffect(100,"spark01_01.bmp",0,curPos,0);
	AssaGetAniFileMat(cAssaEffect[Assa]);
	cAssaEffect[Assa]->AniDelayTime = 3;
	cAssaEffect[Assa]->Face.r = 150;
	cAssaEffect[Assa]->Face.g = 255;
	cAssaEffect[Assa]->Face.b = 150;
	cAssaEffect[Assa]->Face.Transparency = 255;
	cAssaEffect[Assa]->Size.w = 5000;
	cAssaEffect[Assa]->FACE_TYPE = ASSAFACE_SCALE; 
	
	cAssaEffect[Assa]->ScalePosi.x = desPos->x - curPos->x;
	cAssaEffect[Assa]->ScalePosi.y = desPos->y - curPos->y;
	cAssaEffect[Assa]->ScalePosi.z = desPos->z - curPos->z;
}

void SkillMetalionSphereStart(Unit *pChar)
{
	auto sPosition = GetMoveLocation(0, 0, 10 * fONE, 0, pChar->Angle.y, 0);
	POINT3D curPos;
  	curPos.x = pChar->pX + sPosition.iX;
	curPos.y = pChar->pY + 8000;
	curPos.z = pChar->pZ + sPosition.iZ;
	
	g_NewParticleMgr.Start("Skill3MechanicianSparkShield", curPos, 0.2f);
	POINT3D destPos;
	destPos.x = curPos.x+30000;
	destPos.y = curPos.y+80000;
	destPos.z = curPos.z+30000;
	
   	Assa = SetAssaEffect(90,"spark01_01.bmp",0,&curPos,0);
	AssaGetAniFileMat(cAssaEffect[Assa]);
	cAssaEffect[Assa]->AniDelayTime = 3;
	cAssaEffect[Assa]->Face.r = 150;
	cAssaEffect[Assa]->Face.g = 255;
	cAssaEffect[Assa]->Face.b = 150;
	cAssaEffect[Assa]->Face.Transparency = 200;
	cAssaEffect[Assa]->Size.w = 5000;
	cAssaEffect[Assa]->FACE_TYPE = ASSAFACE_SCALE; 
	
	cAssaEffect[Assa]->ScalePosi.x = destPos.x - curPos.x;
	cAssaEffect[Assa]->ScalePosi.y = destPos.y - curPos.y;
	cAssaEffect[Assa]->ScalePosi.z = destPos.z - curPos.z;

  	destPos.x = curPos.x+22000;
	destPos.y = curPos.y+75000;
	destPos.z = curPos.z+22000;
	
  	Assa = SetAssaEffect(100,"spark01_01.bmp",0,&curPos,0);
	AssaGetAniFileMat(cAssaEffect[Assa]);
	cAssaEffect[Assa]->AniDelayTime = 3;
	cAssaEffect[Assa]->Face.r = 150;
	cAssaEffect[Assa]->Face.g = 255;
	cAssaEffect[Assa]->Face.b = 150;
	cAssaEffect[Assa]->Face.Transparency = 200;
	cAssaEffect[Assa]->Size.w = 5000;
	cAssaEffect[Assa]->FACE_TYPE = ASSAFACE_SCALE; 
	
	cAssaEffect[Assa]->ScalePosi.x = destPos.x - curPos.x;
	cAssaEffect[Assa]->ScalePosi.y = destPos.y - curPos.y;
	cAssaEffect[Assa]->ScalePosi.z = destPos.z - curPos.z;

	destPos.x = curPos.x-30000;
	destPos.y = curPos.y+80000;
	destPos.z = curPos.z-30000;

 	Assa = SetAssaEffect(80,"spark01_01.bmp",0,&curPos,0);
	AssaGetAniFileMat(cAssaEffect[Assa]);
	cAssaEffect[Assa]->AniDelayTime = 3;
	cAssaEffect[Assa]->Face.r = 150;
	cAssaEffect[Assa]->Face.g = 255;
	cAssaEffect[Assa]->Face.b = 150;
	cAssaEffect[Assa]->Face.Transparency = 200;
	cAssaEffect[Assa]->Size.w = 5000;
	cAssaEffect[Assa]->FACE_TYPE = ASSAFACE_SCALE; 
	
	cAssaEffect[Assa]->ScalePosi.x = destPos.x - curPos.x;
	cAssaEffect[Assa]->ScalePosi.y = destPos.y - curPos.y;
	cAssaEffect[Assa]->ScalePosi.z = destPos.z - curPos.z;

	destPos.x = curPos.x-22000;
	destPos.y = curPos.y+75000;
	destPos.z = curPos.z-22000;

   	Assa = SetAssaEffect(85,"spark01_01.bmp",0,&curPos,0);
	AssaGetAniFileMat(cAssaEffect[Assa]);
	cAssaEffect[Assa]->AniDelayTime = 3;
	cAssaEffect[Assa]->Face.r = 150;
	cAssaEffect[Assa]->Face.g = 255;
	cAssaEffect[Assa]->Face.b = 150;
	cAssaEffect[Assa]->Face.Transparency = 200;
	cAssaEffect[Assa]->Size.w = 5000;
	cAssaEffect[Assa]->FACE_TYPE = ASSAFACE_SCALE; 
	
	cAssaEffect[Assa]->ScalePosi.x = destPos.x - curPos.x;
	cAssaEffect[Assa]->ScalePosi.y = destPos.y - curPos.y;
	cAssaEffect[Assa]->ScalePosi.z = destPos.z - curPos.z;
}
void SkillMetalionSphereEffect(Unit *pChar, float time, float attackTime)
{
	if(HoEffectManager::GetInstance()->SetMaintainEffect(SKILL_MAGNETIC_SPHERE,pChar,time))
		return;
	else
	{
		HoEffectType_Magnetic_Sphere *effectType = new HoEffectType_Magnetic_Sphere();
		effectType->Init(pChar, time, attackTime);
		effectType->SetSkillCode(SKILL_MAGNETIC_SPHERE);
		HoEffectManager::GetInstance()->AddMaintainEffect(effectType);
	}
}

void SkillMetalionGolem(Unit *pChar)
{
 	HoEffectGroup *effectGroup = NULL;
	effectGroup = MainWindow.LoadScript("Effect\\NewEffect\\SkillMetalionMetalGolem.lua");
	if(effectGroup)
	{
		auto sPosition = GetMoveLocation(0, 0, 30 * fONE, 0, pChar->Angle.y, 0);
 		
		POINT3D pos;
		pos.x = pChar->pX + sPosition.iX;
		pos.y = pChar->pY + 10000;
		pos.z = pChar->pZ + sPosition.iZ;

		HoEffectType_Default *effectType = new HoEffectType_Default();
		effectType->Init(effectGroup, pos.x, pos.y, pos.z, 0, pChar->Angle.y, 0);
		HoEffectManager::GetInstance()->AddEffect(effectType);
	}
}

void SkillWarriorDestroyerBlade(Unit *pChar, float time)
{
	/*
	HoEffectType_Avater_Blade_Blur *effectType = new HoEffectType_Avater_Blade_Blur();
	effectType->Init(pChar, "Effect\\NewEffect\\Res\\TextureHit\\FT4-33.bmp", time);
	HoEffectManager::GetInstance()->AddEffect(effectType);
	*/

	int i = GetAssaEffect();
 	AssaSkillWeaponMotionBlur *motionBlur = new AssaSkillWeaponMotionBlur;
	motionBlur->Start(pChar, int(time*70.f));
	cAssaEffect[i] = motionBlur;
}

void SkillWarriorDestroyerHit(POINT3D *pos)
{
    HoEffectGroup *effectGroup = NULL;
	effectGroup = MainWindow.LoadScript("Effect\\NewEffect\\SkillWarriorDestroyerHit.lua");
	if(effectGroup)
	{
		HoEffectType_Default *effectType = new HoEffectType_Default();
		effectType->Init(effectGroup, pos->x, pos->y+1000, pos->z,0,0,0);
		HoEffectManager::GetInstance()->AddEffect(effectType);
		SetDynLight( pos->x, pos->y, pos->z, 255, 150, 50, 0, 100, 3);
	}
}

void SkillWarriorBetserker(Unit *pChar,float time,int Effect)
{
	HoEffectManager::GetInstance()->StopMaintainEffect(SKILL_B_BERSERKER,pChar,NULL);

	if(HoEffectManager::GetInstance()->SetMaintainEffect(SKILL_BERSERKER, pChar, time))
		return;
	else
	{
		HoEffectGroup *effectGroup = MainWindow.LoadScript("Effect\\NewEffect\\SkillWarriorBetserker.lua");
		if(effectGroup)
		{
			HoEffectType_Attach_Avater *effectType = new HoEffectType_Attach_Avater();
			if (Effect)
				effectType->Init(pChar,effectGroup,time,0.f);
			else
				effectType->Init(pChar,NULL,time,0.f);
			effectType->SetSkillCode(SKILL_BERSERKER);

			POINT3D pos;
			pos.x = pChar->pX;
			pos.y = pChar->pY;
			pos.z = pChar->pZ;

			int num = g_NewParticleMgr.Start("Skill4Betserker",pos);
			effectType->SetParticleID(num);

			HoEffectManager::GetInstance()->AddMaintainEffect(effectType);
		}
	}
}
void SkillBloodyBerserker(Unit *pChar,float time,int Effect)
{
	HoEffectManager::GetInstance()->StopMaintainEffect(SKILL_BERSERKER,pChar,NULL);

	if(HoEffectManager::GetInstance()->SetMaintainEffect(SKILL_B_BERSERKER,pChar,time))
		return;
	else
	{
		HoEffectGroup *effectGroup = MainWindow.LoadScript("Effect\\NewEffect\\Skill5_Fighter_BloodyBerserker.lua");

		if(effectGroup)
		{
			HoEffectType_Attach_Avater *effectType = new HoEffectType_Attach_Avater();
			if (Effect)
				effectType->Init(pChar,effectGroup,time,0.f);
			else
				effectType->Init(pChar,NULL,time,0.f);
			effectType->SetSkillCode(SKILL_B_BERSERKER);

			POINT3D pos;
			pos.x = pChar->pX;
			pos.y = pChar->pY;
			pos.z = pChar->pZ;

			int num = g_NewParticleMgr.Start("Skill5_Fighter_BloodyBerserker", pos);
			effectType->SetParticleID(num);

			HoEffectManager::GetInstance()->AddMaintainEffect(effectType);
		}
	}
}
// 욺괬큼鸞 槻벎// 쀼旗댔샌槻벎
void SkillWarriorCycloneStrikeBlade(Unit *pChar, float time,int Flag)
{
	int i = GetAssaEffect();
 	AssaSkillWeaponMotionBlur *motionBlur = new AssaSkillWeaponMotionBlur;
	motionBlur->Start(pChar, int(time*70.f),Flag);
	cAssaEffect[i] = motionBlur;
}
//욺괬큼鸞槻벎
void SkillFighterDownHit(Unit *pChar,int x,int y,int z)
{
	POINT3D pos;
	pos.x = x;
	pos.y = y;
	pos.z = z;

	SetDynLight(x,pChar->pY,z,255,100,50,0,190,3);
	g_NewParticleMgr.Start("Skill5_Fighter_DownHit",pos);
}

void SkillLancelotAssassinEye(Unit *pChar, float time)
{
	if(HoEffectManager::GetInstance()->SetMaintainEffect(SKILL_ASSASSIN_EYE, pChar, time))
		return;
	else
	{
		HoEffectGroup *effectGroup = NULL;
		effectGroup = MainWindow.LoadScript("Effect\\NewEffect\\SkillLancelotAssassinEye.lua");
		if(effectGroup)
		{
   			HoEffectType_Attach_Avater *effectType = new HoEffectType_Attach_Avater();
			effectType->Init(pChar, effectGroup, time, (float)pChar->PatHeight+(20.f*256));
			effectType->SetSkillCode(SKILL_ASSASSIN_EYE);
			HoEffectManager::GetInstance()->AddMaintainEffect(effectType);
		}	
	}

}

void SkillLancelotChargingStrike(Unit *pChar)
{
	HoEffectGroup *effectGroup = MainWindow.LoadScript("Effect\\NewEffect\\SkillLancelotChargingStrike1.lua");
	if(effectGroup)
	{
		auto sPosition = GetMoveLocation(0, 0, 30 * fONE, 0, lpCurPlayer->Angle.y, 0);
		POINT3D pos;
		pos.x = pChar->pX + sPosition.iX;
		pos.y = pChar->pY + 5000;
		pos.z = pChar->pZ + sPosition.iZ;

		HoEffectType_Default *effectType = new HoEffectType_Default();
		effectType->Init(effectGroup, pos.x, pos.y, pos.y,0, pChar->Angle.y, 0);
		HoEffectManager::GetInstance()->AddEffect(effectType);
	}
}
void SkillLancelotVague(Unit *pChar)
{
	HoEffectGroup *effectGroup = MainWindow.LoadScript("Effect\\NewEffect\\SkillArchMageMeteo1.lua");
	if(effectGroup)
	{
		auto sPosition = GetMoveLocation(0, 0, 30 * fONE, 0, lpCurPlayer->Angle.y, 0);
		POINT3D pos;
		pos.x = pChar->pX + sPosition.iX;
		pos.y = pChar->pY;
		pos.z = pChar->pZ + sPosition.iZ;

		HoEffectType_Default *effectType = new HoEffectType_Default();
		effectType->Init(effectGroup, pos.x, pos.y, pos.y,0, pChar->Angle.y, 0);
		HoEffectManager::GetInstance()->AddEffect(effectType);
	}
}

void SkillSagittarionPhoneixShot(Unit *pChar, POINT3D *curPos, POINT3D *desPos)
{
	HoEffectType_Avater_Shot_Info ShotInfo;
	/*
	ShotInfo.m_CurrentPos.x = curPos->x;
 	ShotInfo.m_CurrentPos.y = curPos->y;
	ShotInfo.m_CurrentPos.z = curPos->z;

	ShotInfo.m_AttackPos.x = desPos->x;
	ShotInfo.m_AttackPos.y = desPos->y;
	ShotInfo.m_AttackPos.z = desPos->z;
	ShotInfo.m_EffectGroup[SHOT_PROCESS] = MainWindow.LoadScript("Effect\\NewEffect\\SkillSagittarionPhoneixShot.lua");
	ShotInfo.m_EffectGroup[SHOT_END] =  MainWindow.LoadScript("Effect\\NewEffect\\SkillWarriorDestroyerHit.lua");
	HoEffectType_Avater_Shot_Default *effectType = new HoEffectType_Avater_Shot_Default();
	effectType->Init(ShotInfo);
	*/
	
	point3 currentPos;
	point3 attackPos;
	currentPos.x = (float)curPos->x;
	currentPos.y = (float)curPos->y;
	currentPos.z = (float)curPos->z;

	attackPos.x = (float)desPos->x;
	attackPos.y = (float)desPos->y;
	attackPos.z = (float)desPos->z;

	HoEffectType_PhoneixShot *effectType = new HoEffectType_PhoneixShot();
	effectType->Init(currentPos, attackPos);
	HoEffectManager::GetInstance()->AddEffect(effectType);
	//SkillPhoenixShotFlame(pChar, curPos);
}

void SkillArchMageFireElementalShot(POINT3D *curPos, POINT3D *desPos)
{
	point3 currentPos;
	point3 attackPos;
	currentPos.x = (float)curPos->x;
	currentPos.y = (float)curPos->y;
	currentPos.z = (float)curPos->z;

	attackPos.x = (float)desPos->x;
	attackPos.y = (float)desPos->y;
	attackPos.z = (float)desPos->z;

	HoEffectType_FireShot *effectType = new HoEffectType_FireShot();
	effectType->Init(currentPos, attackPos);
	HoEffectManager::GetInstance()->AddEffect(effectType);
}

void SkillSagittarionForceOfNature1(Unit *pChar, float time)
{
	if(HoEffectManager::GetInstance()->SetMaintainEffect(SKILL_FORCE_OF_NATURE, pChar, time))
		return;
	else
	{
		HoEffectGroup *effectGroup = NULL;
		effectGroup = MainWindow.LoadScript("Effect\\NewEffect\\SkillSagittarionForceofNature.lua");
		if(effectGroup)
		{
   			HoEffectType_Attach_Avater *effectType = new HoEffectType_Attach_Avater();
			effectType->Init(pChar, effectGroup, time);
			effectType->SetSkillCode(SKILL_FORCE_OF_NATURE);
			HoEffectManager::GetInstance()->AddMaintainEffect(effectType);
		}	
	}

}

void SkillSagittarionForceOfNature2(Unit *pChar, float time)
{
	if(HoEffectManager::GetInstance()->SetMaintainEffect(SKILL_FORCE_OF_NATURE, pChar, time))
		return;
	else
	{
		HoEffectGroup *effectGroup = NULL;
		effectGroup = MainWindow.LoadScript("Effect\\NewEffect\\SkillSagittarionForceofNature2.lua");
		if(effectGroup)
		{
   			HoEffectType_Attach_Avater *effectType = new HoEffectType_Attach_Avater();
			effectType->Init(pChar, effectGroup, time);
			effectType->SetSkillCode(SKILL_FORCE_OF_NATURE);
			HoEffectManager::GetInstance()->AddMaintainEffect(effectType);
		}	
	}
}

void SkillSaintDivinePiercing(Unit *pChar)
{
	auto sPosition = GetMoveLocation(0, 0, 30 * fONE, 0, lpCurPlayer->Angle.y, 0);
	POINT3D pos;
	pos.x = pChar->pX + sPosition.iX;
	pos.y = pChar->pY + 5000;
	pos.z = pChar->pZ + sPosition.iZ;

	AssaParticle_ChainLance(&pos);
}

void SkillSaintGodBless(Unit *pChar, float time)
{
	if(HoEffectManager::GetInstance()->SetMaintainEffect(SKILL_GOD_BLESS,pChar,time))
		return;
	HoEffectGroup *effectGroup = MainWindow.LoadScript("Effect\\NewEffect\\SkillSaintNightGodsBless.lua");
	if(effectGroup)
	{
		HoEffectType_Attach_Avater *effectType = new HoEffectType_Attach_Avater();
		effectType->Init(pChar, effectGroup, time, 4500.f);
		effectType->SetSkillCode(SKILL_GOD_BLESS);
		HoEffectManager::GetInstance()->AddMaintainEffect(effectType);
	}
}

void SkillSwordOfUstice(Unit *pChar)
{
	HoEffectGroup *effectGroup = NULL;
	effectGroup = MainWindow.LoadScript("Effect\\NewEffect\\SkillSaintNightSwordOfustice.lua");
	if(effectGroup)
	{
		HoEffectType_Default *effectType = new HoEffectType_Default();
		effectType->Init(effectGroup, pChar->pX, pChar->pY, pChar->pZ, 0, pChar->Angle.y, 0);
		HoEffectManager::GetInstance()->AddEffect(effectType);
		SetDynLight( pChar->pX, pChar->pY, pChar->pZ, 100, 100, 255, 255, 230, 2);
	}		
}

void SkillValhallaHallOfValhalla1(Unit *pChar)
{
	HoEffectGroup *effectGroup = NULL;
	effectGroup = MainWindow.LoadScript("Effect\\NewEffect\\SkillValhallaHallofVahalla.lua");
	if(effectGroup)
	{
		HoEffectType_Default *effectType = new HoEffectType_Default();
		effectType->Init(effectGroup, pChar->pX, pChar->pY+10000, pChar->pZ, 0, 0, 0);
		HoEffectManager::GetInstance()->AddEffect(effectType);
	}
}

void SkillValhallaXRage(POINT3D *curPos, POINT3D *desPos)
{
  	HoEffectType_Avater_Shot_Info ShotInfo;

	ShotInfo.m_CurrentPos.x = curPos->x;
 	ShotInfo.m_CurrentPos.y = curPos->y+20000;
	ShotInfo.m_CurrentPos.z = curPos->z;
	
	ShotInfo.m_AttackPos.x = desPos->x;
 	ShotInfo.m_AttackPos.y = desPos->y;
	ShotInfo.m_AttackPos.z = desPos->z;

	ShotInfo.m_EffectGroup[SHOT_PROCESS] = MainWindow.LoadScript("Effect\\NewEffect\\SkillValhallaXRage.lua");
	ShotInfo.m_EffectGroup[SHOT_END] =  MainWindow.LoadScript("Effect\\NewEffect\\SkillValhallaHit1.lua");
	ShotInfo.m_LineTextureName = "Effect\\NewEffect\\Res\\TextureHit\\Shield1.tga";
	HoEffectType_Avater_Shot_Default *effectType = new HoEffectType_Avater_Shot_Default();
	effectType->Init(ShotInfo);
	effectType->SetSkillCode(SKILL_X_RAGE);
	HoEffectManager::GetInstance()->AddEffect(effectType);
}

void SkillFrostJavelin(POINT3D *curPos, POINT3D *desPos)
{
	HoEffectType_Avater_Shot_Info ShotInfo;
	
	ShotInfo.m_CurrentPos.x = curPos->x;
 	ShotInfo.m_CurrentPos.y = curPos->y;
	ShotInfo.m_CurrentPos.z = curPos->z;
	
	ShotInfo.m_AttackPos.x = desPos->x;
 	ShotInfo.m_AttackPos.y = desPos->y;
	ShotInfo.m_AttackPos.z = desPos->z;

	ShotInfo.m_EffectGroup[SHOT_PROCESS] = MainWindow.LoadScript("Effect\\NewEffect\\SkillFrostJavelin.lua");
	//ShotInfo.m_EffectGroup[SHOT_PROCESS] = MainWindow.LoadScript("Effect\\NewEffect\\SkillValhallaXRage.lua");
 	ShotInfo.m_EffectGroup[SHOT_END] =  MainWindow.LoadScript("Effect\\NewEffect\\SkillValhallaFrostJavellin1.lua");
	ShotInfo.m_LineTextureName = "Effect\\NewEffect\\Res\\TextureHit\\Shield1.tga";
	HoEffectType_Avater_Shot_Default *effectType = new HoEffectType_Avater_Shot_Default();
	effectType->Init(ShotInfo);
	HoEffectManager::GetInstance()->AddEffect(effectType);
}

void SkillForstJavelinAttach(Unit *pChar, float time)
{
	HoEffectGroup *effectGroup = MainWindow.LoadScript("Effect\\NewEffect\\SkillValhallaFrostJavellin1.lua");
	if(effectGroup)
	{
		HoEffectType_Attach_Avater *effectType = new HoEffectType_Attach_Avater();
		effectType->Init(pChar, effectGroup, time);
		HoEffectManager::GetInstance()->AddEffect(effectType);
	}
}

void SkillVengeance(POINT3D *curPos, POINT3D *desPos)
{
	HoEffectType_Avater_Shot_Info ShotInfo;

	ShotInfo.m_CurrentPos.x = curPos->x;
 	ShotInfo.m_CurrentPos.y = curPos->y;
	ShotInfo.m_CurrentPos.z = curPos->z;
	
	ShotInfo.m_AttackPos.x = desPos->x;
 	ShotInfo.m_AttackPos.y = desPos->y;
	ShotInfo.m_AttackPos.z = desPos->z;

	ShotInfo.m_EffectGroup[SHOT_PROCESS] = MainWindow.LoadScript("Effect\\NewEffect\\SkillValhallaXRage.lua");
	ShotInfo.m_EffectGroup[SHOT_END] =  MainWindow.LoadScript("Effect\\NewEffect\\SkillValhallaHit1.lua");
	ShotInfo.m_LineTextureName = "Effect\\NewEffect\\Res\\TextureHit\\Shield1.tga";
	HoEffectType_Avater_Shot_Default *effectType = new HoEffectType_Avater_Shot_Default();
	effectType->Init(ShotInfo);
	HoEffectManager::GetInstance()->AddEffect(effectType);
}

void SkillCelestialGlacialSpike(Unit *pChar)
{
	HoEffectGroup *effectGroup = NULL;
	effectGroup = MainWindow.LoadScript("Effect\\NewEffect\\SkillCelestialGlacialSpike.lua");
	if(effectGroup)
	{
		HoEffectType_Default *effectType = new HoEffectType_Default();
	 	effectType->Init(effectGroup, pChar->pX, pChar->pY, pChar->pZ, 0, pChar->Angle.y, 0);
		HoEffectManager::GetInstance()->AddEffect(effectType);
	}	
}

void SkillCelestialRegnerationField(Unit *pChar, float time)
{
 	time += 1.f;
	if(HoEffectManager::GetInstance()->SetMaintainEffect(SKILL_REGENERATION_FIELD, pChar, time))
		return;
	else
	{
		HoEffectType_RegenerationField *effectType = new HoEffectType_RegenerationField();
		effectType->Init(pChar);
		effectType->SetSkillCode(SKILL_REGENERATION_FIELD);
		HoEffectManager::GetInstance()->AddMaintainEffect(effectType);
	}
}
void SkillCelestialMusPel(Unit* pChar, float time, float attackTime,int Kind)
{
	if(HoEffectManager::GetInstance()->SetMaintainEffect(SKILL_SUMMON_MUSPELL,pChar,time))
		return;
	else
	{
		HoEffectType_MusPel *effectType = new HoEffectType_MusPel();
		effectType->Init(pChar, time, attackTime,Kind);
		effectType->SetSkillCode(SKILL_SUMMON_MUSPELL);
		HoEffectManager::GetInstance()->AddMaintainEffect(effectType);
	}
}

void CelestialChainLighting(Unit **pChar, int count)
{
	if(count < 2)
		return;
	
	point3 currentPos;
	point3 desPos;

	POINT3D partCurPos;
	POINT3D partDesPos;

	//2개만 연결하는 경우만 구현되었음
	for(int index = 0; index < count-1; index++)
	{
 		HoEffectType_Attach_AvaterToAvater *effectType = new HoEffectType_Attach_AvaterToAvater();
		partCurPos.x = pChar[index]->pX;
		partCurPos.y = pChar[index]->pY;
		partCurPos.z = pChar[index]->pZ;

		partDesPos.x = pChar[index+1]->pX;
		partDesPos.y = pChar[index+1]->pY;
		partDesPos.z = pChar[index+1]->pZ;

		int num1 = g_NewParticleMgr.Start("Skill4CelestialChainLightingLight", partCurPos);
		int num2 = g_NewParticleMgr.Start("Skill4CelestialChainLightingLight", partDesPos);

		effectType->Init(pChar[index], pChar[index+1], num1, num2);
		currentPos.x = (float)pChar[index]->pX/256.f;
		currentPos.y = (float)pChar[index]->pY/256.f;
		currentPos.z = (float)pChar[index]->pZ/256.f;

		desPos.x = (float)pChar[index+1]->pX/256.f;
		desPos.y = (float)pChar[index+1]->pY/256.f;
		desPos.z = (float)pChar[index+1]->pZ/256.f;

		effectType->m_AxialController.Init("Effect\\NewEffect\\Res\\TextureHit\\B_e20.bmp", 3, 0.005f);
		effectType->m_AxialController.InitLoop(1);
		effectType->m_AxialController.InitEndTime(1.f);
		effectType->m_AxialController.InitColor(150,255,200, 255);
		effectType->m_AxialController.InitSize(15,25);
		effectType->m_AxialController.InitPos(currentPos.x, currentPos.y, currentPos.z, desPos.x, desPos.y, desPos.z);

		HoEffectEventColor *eventColor = new HoEffectEventColor;
		eventColor->SetStartTime(HoEffectMinMax<float>(0.f,0.f));
		eventColor->SetFade(true);
		HoEffectMinMax<color4> color;
		color.Max.r = 255;
		color.Min.r = 255;
		color.Max.g = 255;
		color.Min.g = 255;
		color.Max.b = 255;
		color.Min.b = 255;
		color.Max.a = 255;
		color.Min.a = 255;
		eventColor->Set(color);
		effectType->m_AxialController.AddEvent(eventColor);

		eventColor = NULL;
		eventColor = new HoEffectEventColor;
		eventColor->SetStartTime(HoEffectMinMax<float>(0.4f, 0.4f));
		eventColor->SetFade(true);
		color.Max.r = 255;
		color.Min.r = 255;
		color.Max.g = 255;
		color.Min.g = 255;
		color.Max.b = 255;
		color.Min.b = 255;
		color.Max.a = 255;
		color.Min.a = 255;
		eventColor->Set(color);
		effectType->m_AxialController.AddEvent(eventColor);
		
		eventColor = NULL;
		eventColor = new HoEffectEventColor;
		eventColor->SetStartTime(HoEffectMinMax<float>(0.6f, 0.6f));
		eventColor->SetFade(true);
		color.Max.r = 255;
		color.Min.r = 255;
		color.Max.g = 255;
		color.Min.g = 255;
		color.Max.b = 255;
		color.Min.b = 255;
		color.Max.a = 255;
		color.Min.a = 255;
		eventColor->Set(color);
		effectType->m_AxialController.AddEvent(eventColor);

		eventColor = NULL;
		eventColor = new HoEffectEventColor;
		eventColor->SetStartTime(HoEffectMinMax<float>(1, 1));
		eventColor->SetFade(true);
		color.Max.r = 150;
		color.Min.r = 150;
		color.Max.g = 255;
		color.Min.g = 255;
		color.Max.b = 150;
		color.Min.b = 150;
		color.Max.a =  0;
		color.Min.a = 0;
		eventColor->Set(color);
		effectType->m_AxialController.AddEvent(eventColor);
		effectType->m_AxialController.Main(0.f);
		effectType->m_AxialController.CreateFadeList();
		
		HoEffectManager::GetInstance()->AddEffect(effectType);
	}
}

void SkillArchMageMeteo(POINT3D *desPos,int SkillCode)
{
	POINT3D curPos;
	POINT3D attackPos;
	switch(SkillCode)
	{
	case SKILL_PRESS_OF_DEITY:
		attackPos.x = desPos->x;
		attackPos.y = desPos->y;
		attackPos.z = desPos->z;
		curPos.x = attackPos.x;
		curPos.y = attackPos.y+130000;
		curPos.z = attackPos.z+50000;
		AssaParticle_TerrainFire(&curPos,&attackPos,0,SKILL_PRESS_OF_DEITY);
		break;
	default:
		attackPos.x = desPos->x;
		attackPos.y = desPos->y;
		attackPos.z = desPos->z+10000;
		curPos.x = attackPos.x;
		curPos.y = attackPos.y+130000;
		curPos.z = attackPos.z+50000;
		AssaParticle_TerrainFire(&curPos,&attackPos);

		attackPos.x = desPos->x;
		attackPos.y = desPos->y;
		attackPos.z = desPos->z-10000;
		curPos.x = attackPos.x;
		curPos.y = attackPos.y+130000;
		curPos.z = attackPos.z+50000;
		AssaParticle_TerrainFire(&curPos,&attackPos,30);

		attackPos.x = desPos->x+10000;
		attackPos.y = desPos->y;
		attackPos.z = desPos->z;
		curPos.x = attackPos.x;
		curPos.y = attackPos.y+130000;
		curPos.z = attackPos.z+50000;
		AssaParticle_TerrainFire(&curPos,&attackPos,60);
		attackPos.x = desPos->x-10000;
		attackPos.y = desPos->y;
		attackPos.z = desPos->z;
		curPos.x = attackPos.x;
		curPos.y = attackPos.y+130000;
		curPos.z = attackPos.z+50000;
		AssaParticle_TerrainFire(&curPos,&attackPos,90);
		break;
	}
}
void SkillIceMeteorite(Unit *pChar,int Level)
{
	POINT3D attackPos;
	POINT3D curPos;

	switch(Level)
	{
	case 1:
	case 2:
	case 3:
		//1몸燉柯
		attackPos.x = pChar->pX;
		attackPos.y = pChar->pY;
		attackPos.z = pChar->pZ;
		curPos.x	= attackPos.x;
		curPos.y	= attackPos.y + 130000;
		curPos.z	= attackPos.z + 50000;
		ParkAssaParticle_TerrainFire(&curPos,&attackPos,0,4);
		break;
	case 4:
		//2몸燉柯
	{
		auto sPosition = GetMoveLocation(0, 0, 120 * fONE, pChar->Angle.x, pChar->Angle.y, 1);

		attackPos.x = pChar->pX + sPosition.iX;
		attackPos.y = pChar->pY + sPosition.iY;
		attackPos.z = pChar->pZ + sPosition.iZ;
		curPos.x = attackPos.x;
		curPos.y = attackPos.y + 130000;
		curPos.z = attackPos.z + 50000;
		ParkAssaParticle_TerrainFire(&curPos, &attackPos, 0, 4);
	}
	{
		auto sPosition = GetMoveLocation(0, 0, 70 * fONE, pChar->Angle.x, pChar->Angle.y + ANGLE_45, 1);

		attackPos.x = pChar->pX + sPosition.iX;
		attackPos.y = pChar->pY + sPosition.iY;
		attackPos.z = pChar->pZ + sPosition.iZ;

		curPos.x = attackPos.x;
		curPos.y = attackPos.y + 130000;
		curPos.z = attackPos.z + 50000;
		ParkAssaParticle_TerrainFire(&curPos, &attackPos, 10, 4);
	}
		break;
	case 5:
		//3몸燉柯
	{
		auto sPosition = GetMoveLocation(0, 0, 120 * fONE, pChar->Angle.x, pChar->Angle.y, 1);

		attackPos.x = pChar->pX + sPosition.iX;
		attackPos.y = pChar->pY + sPosition.iY;
		attackPos.z = pChar->pZ + sPosition.iZ;
		curPos.x = attackPos.x;
		curPos.y = attackPos.y + 130000;
		curPos.z = attackPos.z + 50000;
		ParkAssaParticle_TerrainFire(&curPos, &attackPos, 0, 4);
	}
	{
		auto sPosition = GetMoveLocation(0, 0, 70 * fONE, pChar->Angle.x, pChar->Angle.y + ANGLE_45, 1);

		attackPos.x = pChar->pX + sPosition.iX;
		attackPos.y = pChar->pY + sPosition.iY;
		attackPos.z = pChar->pZ + sPosition.iZ;

		curPos.x = attackPos.x;
		curPos.y = attackPos.y + 130000;
		curPos.z = attackPos.z + 50000;
		ParkAssaParticle_TerrainFire(&curPos, &attackPos, 10, 4);
	}
	{
		auto sPosition = GetMoveLocation(0, 0, 20 * fONE, pChar->Angle.x, pChar->Angle.y + ANGLE_90, 1);

		attackPos.x = pChar->pX + sPosition.iX;
		attackPos.y = pChar->pY + sPosition.iY;
		attackPos.z = pChar->pZ + sPosition.iZ;

		curPos.x = attackPos.x;
		curPos.y = attackPos.y + 130000;
		curPos.z = attackPos.z + 50000;
		ParkAssaParticle_TerrainFire(&curPos, &attackPos, 20, 4);
	}
		break;
	case 6:
		//4몸燉柯
	{
		auto sPosition = GetMoveLocation(0, 0, 120 * fONE, pChar->Angle.x, pChar->Angle.y, 1);

		attackPos.x = pChar->pX + sPosition.iX;
		attackPos.y = pChar->pY + sPosition.iY;
		attackPos.z = pChar->pZ + sPosition.iZ;
		curPos.x = attackPos.x;
		curPos.y = attackPos.y + 130000;
		curPos.z = attackPos.z + 50000;
		ParkAssaParticle_TerrainFire(&curPos, &attackPos, 0, 4);
	}
	{
		auto sPosition = GetMoveLocation(0, 0, 70 * fONE, pChar->Angle.x, pChar->Angle.y + ANGLE_45, 1);

		attackPos.x = pChar->pX + sPosition.iX;
		attackPos.y = pChar->pY + sPosition.iY;
		attackPos.z = pChar->pZ + sPosition.iZ;

		curPos.x = attackPos.x;
		curPos.y = attackPos.y + 130000;
		curPos.z = attackPos.z + 50000;
		ParkAssaParticle_TerrainFire(&curPos, &attackPos, 10, 4);
	}
	{
		auto sPosition = GetMoveLocation(0, 0, 20 * fONE, pChar->Angle.x, pChar->Angle.y + ANGLE_90, 1);

		attackPos.x = pChar->pX + sPosition.iX;
		attackPos.y = pChar->pY + sPosition.iY;
		attackPos.z = pChar->pZ + sPosition.iZ;

		curPos.x = attackPos.x;
		curPos.y = attackPos.y + 130000;
		curPos.z = attackPos.z + 50000;
		ParkAssaParticle_TerrainFire(&curPos, &attackPos, 20, 4);
	}
	{
		auto sPosition = GetMoveLocation(0, 0, 70 * fONE, pChar->Angle.x, pChar->Angle.y + ANGLE_90 + ANGLE_45, 1);

		attackPos.x = pChar->pX + sPosition.iX;
		attackPos.y = pChar->pY + sPosition.iY;
		attackPos.z = pChar->pZ + sPosition.iZ;

		curPos.x = attackPos.x;
		curPos.y = attackPos.y + 130000;
		curPos.z = attackPos.z + 50000;
		ParkAssaParticle_TerrainFire(&curPos, &attackPos, 30, 4);
	}
		break;
	case 7:
		//5몸燉柯
	{
		auto sPosition = GetMoveLocation(0, 0, 120 * fONE, pChar->Angle.x, pChar->Angle.y, 1);

		attackPos.x = pChar->pX + sPosition.iX;
		attackPos.y = pChar->pY + sPosition.iY;
		attackPos.z = pChar->pZ + sPosition.iZ;
		curPos.x = attackPos.x;
		curPos.y = attackPos.y + 130000;
		curPos.z = attackPos.z + 50000;
		ParkAssaParticle_TerrainFire(&curPos, &attackPos, 0, 4);
	}
	{
		auto sPosition = GetMoveLocation(0, 0, 70 * fONE, pChar->Angle.x, pChar->Angle.y + ANGLE_45, 1);

		attackPos.x = pChar->pX + sPosition.iX;
		attackPos.y = pChar->pY + sPosition.iY;
		attackPos.z = pChar->pZ + sPosition.iZ;

		curPos.x = attackPos.x;
		curPos.y = attackPos.y + 130000;
		curPos.z = attackPos.z + 50000;
		ParkAssaParticle_TerrainFire(&curPos, &attackPos, 10, 4);
	}
	{
		auto sPosition = GetMoveLocation(0, 0, 20 * fONE, pChar->Angle.x, pChar->Angle.y + ANGLE_90, 1);

		attackPos.x = pChar->pX + sPosition.iX;
		attackPos.y = pChar->pY + sPosition.iY;
		attackPos.z = pChar->pZ + sPosition.iZ;

		curPos.x = attackPos.x;
		curPos.y = attackPos.y + 130000;
		curPos.z = attackPos.z + 50000;
		ParkAssaParticle_TerrainFire(&curPos, &attackPos, 20, 4);
	}
	{
		auto sPosition = GetMoveLocation(0, 0, 70 * fONE, pChar->Angle.x, pChar->Angle.y + ANGLE_90 + ANGLE_45, 1);

		attackPos.x = pChar->pX + sPosition.iX;
		attackPos.y = pChar->pY + sPosition.iY;
		attackPos.z = pChar->pZ + sPosition.iZ;

		curPos.x = attackPos.x;
		curPos.y = attackPos.y + 130000;
		curPos.z = attackPos.z + 50000;
		ParkAssaParticle_TerrainFire(&curPos, &attackPos, 30, 4);
	}
	{
		auto sPosition = GetMoveLocation(0, 0, 120 * fONE, pChar->Angle.x, pChar->Angle.y + ANGLE_180, 1);

		attackPos.x = pChar->pX + sPosition.iX;
		attackPos.y = pChar->pY + sPosition.iY;
		attackPos.z = pChar->pZ + sPosition.iZ;

		curPos.x = attackPos.x;
		curPos.y = attackPos.y + 130000;
		curPos.z = attackPos.z + 50000;
		ParkAssaParticle_TerrainFire(&curPos, &attackPos, 40, 4);
	}
		break;
	case 8:
		//6몸燉柯
	{
		auto sPosition = GetMoveLocation(0, 0, 120 * fONE, pChar->Angle.x, pChar->Angle.y, 1);

		attackPos.x = pChar->pX + sPosition.iX;
		attackPos.y = pChar->pY + sPosition.iY;
		attackPos.z = pChar->pZ + sPosition.iZ;
		curPos.x = attackPos.x;
		curPos.y = attackPos.y + 130000;
		curPos.z = attackPos.z + 50000;
		ParkAssaParticle_TerrainFire(&curPos, &attackPos, 0, 4);
	}
	{
		auto sPosition = GetMoveLocation(0, 0, 70 * fONE, pChar->Angle.x, pChar->Angle.y + ANGLE_45, 1);

		attackPos.x = pChar->pX + sPosition.iX;
		attackPos.y = pChar->pY + sPosition.iY;
		attackPos.z = pChar->pZ + sPosition.iZ;

		curPos.x = attackPos.x;
		curPos.y = attackPos.y + 130000;
		curPos.z = attackPos.z + 50000;
		ParkAssaParticle_TerrainFire(&curPos, &attackPos, 10, 4);
	}
	{
		auto sPosition = GetMoveLocation(0, 0, 20 * fONE, pChar->Angle.x, pChar->Angle.y + ANGLE_90, 1);

		attackPos.x = pChar->pX + sPosition.iX;
		attackPos.y = pChar->pY + sPosition.iY;
		attackPos.z = pChar->pZ + sPosition.iZ;

		curPos.x = attackPos.x;
		curPos.y = attackPos.y + 130000;
		curPos.z = attackPos.z + 50000;
		ParkAssaParticle_TerrainFire(&curPos, &attackPos, 20, 4);
	}
	{
		auto sPosition = GetMoveLocation(0, 0, 70 * fONE, pChar->Angle.x, pChar->Angle.y + ANGLE_90 + ANGLE_45, 1);

		attackPos.x = pChar->pX + sPosition.iX;
		attackPos.y = pChar->pY + sPosition.iY;
		attackPos.z = pChar->pZ + sPosition.iZ;

		curPos.x = attackPos.x;
		curPos.y = attackPos.y + 130000;
		curPos.z = attackPos.z + 50000;
		ParkAssaParticle_TerrainFire(&curPos, &attackPos, 30, 4);
	}
	{
		auto sPosition = GetMoveLocation(0, 0, 120 * fONE, pChar->Angle.x, pChar->Angle.y + ANGLE_180, 1);

		attackPos.x = pChar->pX + sPosition.iX;
		attackPos.y = pChar->pY + sPosition.iY;
		attackPos.z = pChar->pZ + sPosition.iZ;

		curPos.x = attackPos.x;
		curPos.y = attackPos.y + 130000;
		curPos.z = attackPos.z + 50000;
		ParkAssaParticle_TerrainFire(&curPos, &attackPos, 40, 4);
	}
	{
		auto sPosition = GetMoveLocation(0, 0, 70 * fONE, pChar->Angle.x, pChar->Angle.y + ANGLE_180 + ANGLE_45, 1);

		attackPos.x = pChar->pX + sPosition.iX;
		attackPos.y = pChar->pY + sPosition.iY;
		attackPos.z = pChar->pZ + sPosition.iZ;

		curPos.x = attackPos.x;
		curPos.y = attackPos.y + 130000;
		curPos.z = attackPos.z + 50000;
		ParkAssaParticle_TerrainFire(&curPos, &attackPos, 50, 4);
	}
		break;
	case 9:
		//7몸燉柯
	{
		auto sPosition = GetMoveLocation(0, 0, 120 * fONE, pChar->Angle.x, pChar->Angle.y, 1);

		attackPos.x = pChar->pX + sPosition.iX;
		attackPos.y = pChar->pY + sPosition.iY;
		attackPos.z = pChar->pZ + sPosition.iZ;
		curPos.x = attackPos.x;
		curPos.y = attackPos.y + 130000;
		curPos.z = attackPos.z + 50000;
		ParkAssaParticle_TerrainFire(&curPos, &attackPos, 0, 4);
	}
	{
		auto sPosition = GetMoveLocation(0, 0, 70 * fONE, pChar->Angle.x, pChar->Angle.y + ANGLE_45, 1);

		attackPos.x = pChar->pX + sPosition.iX;
		attackPos.y = pChar->pY + sPosition.iY;
		attackPos.z = pChar->pZ + sPosition.iZ;

		curPos.x = attackPos.x;
		curPos.y = attackPos.y + 130000;
		curPos.z = attackPos.z + 50000;
		ParkAssaParticle_TerrainFire(&curPos, &attackPos, 10, 4);
	}
	{
		auto sPosition = GetMoveLocation(0, 0, 20 * fONE, pChar->Angle.x, pChar->Angle.y + ANGLE_90, 1);

		attackPos.x = pChar->pX + sPosition.iX;
		attackPos.y = pChar->pY + sPosition.iY;
		attackPos.z = pChar->pZ + sPosition.iZ;

		curPos.x = attackPos.x;
		curPos.y = attackPos.y + 130000;
		curPos.z = attackPos.z + 50000;
		ParkAssaParticle_TerrainFire(&curPos, &attackPos, 20, 4);
	}
	{
		auto sPosition = GetMoveLocation(0, 0, 70 * fONE, pChar->Angle.x, pChar->Angle.y + ANGLE_90 + ANGLE_45, 1);

		attackPos.x = pChar->pX + sPosition.iX;
		attackPos.y = pChar->pY + sPosition.iY;
		attackPos.z = pChar->pZ + sPosition.iZ;

		curPos.x = attackPos.x;
		curPos.y = attackPos.y + 130000;
		curPos.z = attackPos.z + 50000;
		ParkAssaParticle_TerrainFire(&curPos, &attackPos, 30, 4);
	}
	{
		auto sPosition = GetMoveLocation(0, 0, 120 * fONE, pChar->Angle.x, pChar->Angle.y + ANGLE_180, 1);

		attackPos.x = pChar->pX + sPosition.iX;
		attackPos.y = pChar->pY + sPosition.iY;
		attackPos.z = pChar->pZ + sPosition.iZ;

		curPos.x = attackPos.x;
		curPos.y = attackPos.y + 130000;
		curPos.z = attackPos.z + 50000;
		ParkAssaParticle_TerrainFire(&curPos, &attackPos, 40, 4);
	}
	{
		auto sPosition = GetMoveLocation(0, 0, 70 * fONE, pChar->Angle.x, pChar->Angle.y + ANGLE_180 + ANGLE_45, 1);

		attackPos.x = pChar->pX + sPosition.iX;
		attackPos.y = pChar->pY + sPosition.iY;
		attackPos.z = pChar->pZ + sPosition.iZ;

		curPos.x = attackPos.x;
		curPos.y = attackPos.y + 130000;
		curPos.z = attackPos.z + 50000;
		ParkAssaParticle_TerrainFire(&curPos, &attackPos, 50, 4);
	}
	{
		auto sPosition = GetMoveLocation(0, 0, 20 * fONE, pChar->Angle.x, pChar->Angle.y + ANGLE_270, 1);

		attackPos.x = pChar->pX + sPosition.iX;
		attackPos.y = pChar->pY + sPosition.iY;
		attackPos.z = pChar->pZ + sPosition.iZ;

		curPos.x = attackPos.x;
		curPos.y = attackPos.y + 130000;
		curPos.z = attackPos.z + 50000;
		ParkAssaParticle_TerrainFire(&curPos, &attackPos, 60, 4);
	}
		break;
	case 10:
		//8몸燉柯
	{
		auto sPosition = GetMoveLocation(0, 0, 120 * fONE, pChar->Angle.x, pChar->Angle.y, 1);

		attackPos.x = pChar->pX + sPosition.iX;
		attackPos.y = pChar->pY + sPosition.iY;
		attackPos.z = pChar->pZ + sPosition.iZ;
		curPos.x = attackPos.x;
		curPos.y = attackPos.y + 130000;
		curPos.z = attackPos.z + 50000;
		ParkAssaParticle_TerrainFire(&curPos, &attackPos, 0, 4);
	}
	{
		auto sPosition = GetMoveLocation(0, 0, 70 * fONE, pChar->Angle.x, pChar->Angle.y + ANGLE_45, 1);

		attackPos.x = pChar->pX + sPosition.iX;
		attackPos.y = pChar->pY + sPosition.iY;
		attackPos.z = pChar->pZ + sPosition.iZ;

		curPos.x = attackPos.x;
		curPos.y = attackPos.y + 130000;
		curPos.z = attackPos.z + 50000;
		ParkAssaParticle_TerrainFire(&curPos, &attackPos, 10, 4);
	}
	{
		auto sPosition = GetMoveLocation(0, 0, 20 * fONE, pChar->Angle.x, pChar->Angle.y + ANGLE_90, 1);

		attackPos.x = pChar->pX + sPosition.iX;
		attackPos.y = pChar->pY + sPosition.iY;
		attackPos.z = pChar->pZ + sPosition.iZ;

		curPos.x = attackPos.x;
		curPos.y = attackPos.y + 130000;
		curPos.z = attackPos.z + 50000;
		ParkAssaParticle_TerrainFire(&curPos, &attackPos, 20, 4);
	}
	{
		auto sPosition = GetMoveLocation(0, 0, 70 * fONE, pChar->Angle.x, pChar->Angle.y + ANGLE_90 + ANGLE_45, 1);

		attackPos.x = pChar->pX + sPosition.iX;
		attackPos.y = pChar->pY + sPosition.iY;
		attackPos.z = pChar->pZ + sPosition.iZ;

		curPos.x = attackPos.x;
		curPos.y = attackPos.y + 130000;
		curPos.z = attackPos.z + 50000;
		ParkAssaParticle_TerrainFire(&curPos, &attackPos, 30, 4);
	}
	{
		auto sPosition = GetMoveLocation(0, 0, 120 * fONE, pChar->Angle.x, pChar->Angle.y + ANGLE_180, 1);

		attackPos.x = pChar->pX + sPosition.iX;
		attackPos.y = pChar->pY + sPosition.iY;
		attackPos.z = pChar->pZ + sPosition.iZ;

		curPos.x = attackPos.x;
		curPos.y = attackPos.y + 130000;
		curPos.z = attackPos.z + 50000;
		ParkAssaParticle_TerrainFire(&curPos, &attackPos, 40, 4);
	}
	{
		auto sPosition = GetMoveLocation(0, 0, 70 * fONE, pChar->Angle.x, pChar->Angle.y + ANGLE_180 + ANGLE_45, 1);

		attackPos.x = pChar->pX + sPosition.iX;
		attackPos.y = pChar->pY + sPosition.iY;
		attackPos.z = pChar->pZ + sPosition.iZ;

		curPos.x = attackPos.x;
		curPos.y = attackPos.y + 130000;
		curPos.z = attackPos.z + 50000;
		ParkAssaParticle_TerrainFire(&curPos, &attackPos, 50, 4);
	}
	{
		auto sPosition = GetMoveLocation(0, 0, 20 * fONE, pChar->Angle.x, pChar->Angle.y + ANGLE_270, 1);

		attackPos.x = pChar->pX + sPosition.iX;
		attackPos.y = pChar->pY + sPosition.iY;
		attackPos.z = pChar->pZ + sPosition.iZ;

		curPos.x = attackPos.x;
		curPos.y = attackPos.y + 130000;
		curPos.z = attackPos.z + 50000;
		ParkAssaParticle_TerrainFire(&curPos, &attackPos, 60, 4);
	}
	{
		auto sPosition = GetMoveLocation(0, 0, 70 * fONE, pChar->Angle.x, pChar->Angle.y + ANGLE_270 + ANGLE_45, 1);

		attackPos.x = pChar->pX + sPosition.iX;
		attackPos.y = pChar->pY + sPosition.iY;
		attackPos.z = pChar->pZ + sPosition.iZ;

		curPos.x = attackPos.x;
		curPos.y = attackPos.y + 130000;
		curPos.z = attackPos.z + 50000;
		ParkAssaParticle_TerrainFire(&curPos, &attackPos, 70, 4);
	}
		break;
	}
}
void SkillArchMageFireElementalHand(Unit *pChar)
{
	AssaParticle_MonsterPigonHand(pChar);
}
BOOL GetAssaCodeEffect(Unit *pChar, int code)
{
    for(int i = 0; i < cASSAEFFECT_MAX; i++)
	{
		if(cAssaEffect[i])
		{
			if(cAssaEffect[i]->CODE == code)
			{
				if(cAssaEffect[i]->pChar == pChar)
   					return TRUE;
			}
		}
	}

	BOOL ret = FALSE;
	ret = HoEffectManager::GetInstance()->GetSkillCode(pChar, code);
	if(ret)
		return ret;
	return FALSE;
}
void Valento_PowerUp(Unit *pChar)
{
 	HoEffectGroup *effectGroup = MainWindow.LoadScript("Effect\\NewEffect\\ValentoPowerUp.Lua");
	if(effectGroup)
	{
		HoEffectType_Default *effectType = new HoEffectType_Default();

		effectType->Init(effectGroup, pChar->pX, pChar->pY, pChar->pZ, 0, pChar->Angle.y, 0);
		HoEffectManager::GetInstance()->AddEffect(effectType);
	}
}
void Valento_Justice(Unit *pChar)
{

	 HoEffectGroup *effectGroup = MainWindow.LoadScript("Effect\\NewEffect\\ValentoJustice.Lua");
	if(effectGroup)
	{
		HoEffectType_Default *effectType = new HoEffectType_Default();

		effectType->Init(effectGroup, pChar->pX, pChar->pY, pChar->pZ, 0, pChar->Angle.y, 0);
		HoEffectManager::GetInstance()->AddEffect(effectType);
	}
}

void DevilBird_Skill(Unit *pChar)
{

	 HoEffectGroup *effectGroup = MainWindow.LoadScript("Effect\\NewEffect\\DevilBirdSkill.Lua");
	if(effectGroup)
	{
		HoEffectType_Default *effectType = new HoEffectType_Default();

		effectType->Init(effectGroup, pChar->pX, pChar->pY, pChar->pZ, 0, pChar->Angle.y, 0);
		HoEffectManager::GetInstance()->AddEffect(effectType);
	}
}

void ParkIncubusSummonerSkill(Unit *pChar)
{
	if(pChar)
	{
		HoEffectGroup *effectGroup = NULL;
		effectGroup = MainWindow.LoadScript("Effect\\NewEffect\\Incu_summSkill.lua");
		if(effectGroup)
		{
			auto sPosition = GetMoveLocation( 0, 0, 30*fONE, 0, pChar->Angle.y, 0);
	 		
			POINT3D pos;
			pos.x = pChar->pX + sPosition.iX;
			pos.y = pChar->pY + 10000;
			pos.z = pChar->pZ + sPosition.iZ;

			HoEffectType_Default *effectType = new HoEffectType_Default();
			effectType->Init(effectGroup, pos.x, pos.y, pos.z, 0, pChar->Angle.y, 0);
			HoEffectManager::GetInstance()->AddEffect(effectType);
		}
	}
}
void ParkWingEffect(Unit *pChar,int iCode)
{
	if (!HoEffectManager::GetInstance()->StopMaintainEffect(SKILL_WING_EFFECT,pChar,iCode))
	{
		HoEffectGroup *effectGroup = NULL;
		switch(iCode)
		{
		case sinCW1|sin01:
			effectGroup = MainWindow.LoadScript("Effect\\NewEffect\\Arcangel_wings.lua");
			break;
		case sinCW1|sin02:
			effectGroup = MainWindow.LoadScript("Effect\\NewEffect\\Butterfly_wings.lua");
			break;
		case sinCW1|sin03:
			effectGroup = MainWindow.LoadScript("Effect\\NewEffect\\Demoniac_wings.lua");
			break;
		case sinCW1|sin04:
			effectGroup = MainWindow.LoadScript("Effect\\NewEffect\\Devine_wings.lua");
			break;
		case sinCW1|sin05:
			effectGroup = MainWindow.LoadScript("Effect\\NewEffect\\Ice_wings.lua");
			break;
		case sinCW1|sin06:
			effectGroup = MainWindow.LoadScript("Effect\\NewEffect\\Love_wings.lua");
			break;
		case sinCW1|sin07:
			effectGroup = MainWindow.LoadScript("Effect\\NewEffect\\Meadow_wings.lua");
			break;
		case sinCW1|sin08:
			effectGroup = MainWindow.LoadScript("Effect\\NewEffect\\Short_wings.lua");
			break;
		}
		if(effectGroup)
		{
			HoEffectWing *effectType = new HoEffectWing;
			effectType->Init(pChar,effectGroup,iCode);
			effectType->SetSkillCode(SKILL_WING_EFFECT);
			HoEffectManager::GetInstance()->AddMaintainEffect(effectType);
		}
	}
}