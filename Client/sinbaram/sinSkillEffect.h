/*----------------------------------------------------------------------------*
*	파일명 :  sinSkillEffect.h	
*	하는일 :  이펙트 관련 작업 (각각의 이펙트 )
*	작성일 :  최종업데이트 2002년 6월
*	적성자 :  박상열 
*-----------------------------------------------------------------------------*/	

int sinSkillTestKey(); //스킬 테스트 Key

/*----------------------------------------------------------------------------*
*							시스템
*-----------------------------------------------------------------------------*/	
void sinInitSkillEffect();
void sinSkillEffectMove(cSINEFFECT2 *pEffect);	//Move
void sinProcess7();
extern int Index2;
/*----------------------------------------------------------------------------*
*						모라이온 스킬 
*-----------------------------------------------------------------------------*/	
//////////// 나이트
int sinEffect_Sword_Blast_Particle(POINT3D *pPosi);
int sinEffect_Sword_Blast(Unit *pChar , Unit *desChar);
int sinEffect_Holy_Body(Unit *pChar);
int sinEffect_Holy_Body_Cross(Unit *pChar );
int sinEffect_Holy_Body_Particle(POINT3D *pPosi);	


//////////// 아틀란타 
int sinEffect_Farina(Unit *pChar , Unit *desChar);
int sinEffect_Farina_Particle(POINT3D *pPosi);
int sinEffect_VigorSpear(Unit *pChar , Unit *desChar);
int sinEffect_VigorSpear_Particle(POINT3D *pPosi);
int sinEffect_Shield_Strike(POINT3D *pPosi);
int sinEffect_Shield_Strike_Particle(POINT3D *pPosi);

//////////// 프리스트 
//int MultiSpark_Effect(Unit *pChar , Unit *desChar);
int sinEffect_MultiSpark_Particle(POINT3D *pPosi);
int sinEffect_MultiSpark_Particle2(POINT3D *pPosi);
int sinEffect_MultiSpark(Unit *pChar , Unit *desChar , int Num);
int sinEffect_HolyMind(Unit *pChar , int Time);
int sinEffect_HolyMind_Particle(POINT3D *pPosi);
int sinEffect_SilraphimEffect(POINT3D *pPosi);
int sinEffect_TenusEffect(POINT3D *pPosi);
int sinEffect_Healing(Unit *pChar);
int sinEffect_Healing_Particle(POINT3D *pPosi);
int sinEffect_Healing_Particle2(POINT3D *pPosi);
int sinEffect_HealParticle3(POINT3D *pPosi ,int Mat ,int Num , int Size , int Time , int Gravity );

//테스트 
int sinEffect_Healing2(Unit *pChar);

//////////// 메지션
int sinEffect_Agony(Unit *pChar);
int sinEffect_Agony_Particle(POINT3D *pPosi);
int sinEffect_Zenith(Unit *pChar,int Time,int Flag = 0);
int sinEffect_Zenith_Particle(POINT3D *pPosi , int R , int G , int B);
int sinEffect_FireBolt(Unit *pChar , Unit *desChar);
int sinEffect_FireBolt_Particle(POINT3D *pPosi);
int sinEffect_FireBolt_Particle2(POINT3D *pPosi); //어케하다보니 일케됬다 된장!

//////////// 공용 코드
int sinEffect_Bomb6(POINT3D *pPosi); //폭팔
int sinEffect_Bomb6_Particle(POINT3D *pPosi);
int sinEffect_SkillHit(DWORD CODE , POINT3D *pPosi); //스킬 Hit 이펙트 
int sinEffect_SetCharPosi(cSINEFFECT2 *pEffect); //좌표 셋팅
int sinEfect_CheckCrash(cSINEFFECT2 *pEffect);

int sinEffect_StartMagic2(POINT3D *pPosi,int CharFlag);
int sinEffect_StartMagic(POINT3D *pPosi , int CharFlag,int Type = 0);

int AddCodeEffectTime(Unit *pChar,int Code);

//직槿삽黛
int sinEffect_Silraphim(Unit *pChar);
//鍵鬼裂減
int sinEffect_Tenus(Unit *pChar);
//�誅Ο느�
int sinEffect_Anima(Unit *pChar,int Time,int Flag);
extern int MatFireBolt[3];
