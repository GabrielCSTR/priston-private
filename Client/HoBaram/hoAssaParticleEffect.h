#ifndef _HO_ASSA_PARTICLE_EFFECT_
#define _HO_ASSA_PARTICLE_EFFECT_




//비어 있는 버퍼를 리턴하는 함수..(함수 안에서 동적으로 생성 하면 sin의 함수를 고쳐야 하므로)
int GetAssaEffect();
int	StopAssaCodeEffect(Unit *pChar, int code, int setTime = 0);
bool AddAssaCodeEffectTime(Unit *pChar, int code, int time);
int AddAssaCodeEffectTime(Unit *pChar,int Code);

BOOL GetAssaUseEffect(Unit *pChar, int code);
bool GetAssaContinueSkill(int skillCode);
//모이는 라인 파티클...
int AssaParticle_LineIn(POINT3D *pPosi , char *texName = NULL, int continueTime = 15, int speed = 0);
int AssaParticle_LineOut(POINT3D *pPosi , char *texName = NULL, int continueTime = 10, int speed = 0);
int AssaParticle_Star(POINT3D *pPosi);

//�珠┶滿�
int AssaParticle_HolyValor_Jang(Unit *pChar);
int AssaParticle_HolyValor_JangEffect(Unit *pChar,int maxTime);
int AssaParticle_HolyValor_Member(Unit *pChar, int maxTime = 0);
int AssaParticle_HolyValorIsUse(Unit *pChar);

//莖幢�櫛�
int AssaParticle_DrasticSpirit_Jang(Unit *pChar);
int AssaParticle_DrasticSpirit_JangEffect(Unit *pChar,int maxTime);
int AssaParticle_DrasticSpirit_Member(Unit *pChar, int maxTime = 0);

//Valkyrie (Windy, TwistJavelin, FireJavelin)
int AssaParticle_Windy(Unit *pChar, int maxTime = 0);
int AssaParticle_TwistJavelinShot(POINT3D *pPosi, POINT3D *pDesti);
int AssaParticle_FireJavelin(POINT3D *pPosi, POINT3D *pDesti);
int AssaParticle_FireJavelin(Unit *pChar, POINT3D *pDesti);


int AssaParticle_DivineLighting(Unit *pChar);
int AssaParticle_Sprak(POINT3D *pPosi);

//Wizard (ColumnOfWater, EnchantWeapon, DeadLay)
int AssaParticle_ColumnOfWater(POINT3D *pPosi, POINT3D *pDesti, int level = 1);
int AssaParticle_ColumnOfWaterHit(POINT3D *pPosi);

int AssaParticle_EnchantWeaponIceJang(Unit *pChar, int maxTime = 0);
int AssaParticle_EnchantWeaponFireJang(Unit *pChar, int maxTime = 0);
int AssaParticle_EnchantWeaponLightJang(Unit *pChar, int maxTime = 0);


int AssaParticle_EnchantWeaponJinMember(Unit *pChar);
int AssaParticle_EnchantWeaponIceMember(Unit *pChar, int maxTime = 0);
int AssaParticle_EnchantWeaponFireMember(Unit *pChar, int maxTime = 0);
int AssaParticle_EnchantWeaponLightMember(Unit *pChar, int maxTime = 0);

int AssaParticle_LightShot(POINT3D *pPosi, POINT3D *pDesti);
int AssaParticle_FireShot(POINT3D *pPosi, POINT3D *pDesti);
int AssaParticle_IceShot(POINT3D *pPosi, POINT3D *pDesti);

int AssaParticle_LightHit1(POINT3D *pPosi);
int AssaParticle_IceHit1(POINT3D *pPosi);
int AssaParticle_FireHit1(POINT3D *pPosi);
int AssaParticle_FireHit2(POINT3D *pPosi);

int AssaParticle_BigFireHit1(POINT3D *pPosi);

int AssaParticle_DeadLay(POINT3D *pPosi, POINT3D *pDesti);
int AssaParticle_HolyMind_Attack(Unit *pChar, int liveCount);

//int AssaParticle_AgingBody(Unit *pChar);

int StartEffect_Serqbus_Skill1(Unit *pChar, int liveCount);
int StartEffect_Serqbus_Skill2(Unit *pChar, int liveCount);
int StartEffect_Serqbus_Skill3(Unit *pChar, int liveCount);

//Fury 관련 이펙트
int AssaParticle_Fury_Eye(Unit *pChar);							//눈에 붙는 이펙트
int AssaParticle_Fury_ShotFire(Unit *pChar, POINT3D *destPos);	//불쏘기..

int AssaParticle_Fury_RespawnMonster(POINT3D *pPosi);						//몬스터들 소환..
int AssaParticle_Fury_RespawnBody(Unit *pChar);                  //몬스터 손환시 퓨리의 입에서 나오는 파티클.
int AssaParticle_Fury_Skill1(Unit *pChar);						//영역 공격..

int AssaParticle_Fury_Skill1(POINT3D *pPosi, POINT3D *pAngle);      //영역 공격.. 옛날 버전을 위해서..

//Evil Maple관련 이펙트..
int AssaParticle_EvilMapleShot(Unit *pChar);

//Evil Plant관련 이펙트..
int AssaParticle_EvilPlantShot(Unit *pChar);

void AssaParticle_IceserpentHit(Unit *pChar);

void AssaParticle_IceserpentSkill(Unit *pChar);

//Thorn Crawler관련 이펙트..
int AssaParticle_ThornCrawlerShot(Unit *pChar, POINT3D *destPos);

//Stone Golem관련 이펙트..
int AssaParticle_StoneGolemShot(Unit *pChar);


//Heavy Goblin관련 이펙트..
int AssaParticle_HeavyGoblinHit1(Unit *pChar); //위에서 내려치는 동작
int AssaParticle_HeavyGoblinHit2(Unit *pChar); //양사이드에서 치는 동작

//Doom Gurad관련 이펙트..
int AssaParticle_DoomGuardHit1(Unit *pChar); //위에서 내려치는 동작
int AssaParticle_DoomGuardHit2(Unit *pChar); //양사이드 치는 동작

//Snail 관련 이펙트..
int AssaParticle_SnailShot(Unit *pChar, POINT3D *destPos);

//Night Mare관련 이펙트..
int AssaParticle_NightMare(Unit *pChar);

//Ratoo 이펙스
int AssaParticle_RatooHit1(Unit *pChar);

//Monster 치기
int AssaParticle_Hit1(POINT3D *destPos);


//Spider 거미 뺏어 내기
int AssaParticleSpiderSkill1(Unit *pChar);

void AssParticle_UnDeadManger(Unit *pChar,int nSkill);
//굻굻襟세콘
void AssaParticle_Arcuda(Unit *pChar);
// �阮촛㏏�
void AssaParticle_Effect(char *szName, Unit *pChar,int Kind);
// 씩섐裂훵
void AssaParticle_RollingSmashHit(int x,int y,int z);
void AssaParticle_RollingSmashDown(int x,int y,int z);


void AssaParticle_CastleRed(Unit *pChar);
void AssaParticle_CastleGreen(Unit *pChar);
void AssaParticle_CastleBlue(Unit *pChar);

//ClanMonster 이펙트
int AssaParticleClanMonster(Unit *pChar);
int AssaParticleClanMonsterHit1(Unit *pChar);
int AssaParticleClanMonsterHit2(Unit *pChar);
int AssaParticle_Sprak1(POINT3D *pPosi);

// 띳침껍얽槻벎
int AssaParticleTulla(Unit *pChar);

void AssaParticle_BlueMountainHit(Unit *pChar);
void AssaParticle_BlueMountainSkill(Unit *pChar);
void AssaParticle_MorgoniaHit(Unit *pChar);
void AssaParticle_MorgoniaSkill(Unit *pChar);
void AssaParticle_BoneHoundSkill(Unit *pChar);
void AssaParticle_BoneHoundSkillHit(Unit *pChar);

// 삔懃寧샌
void AssaParticle_ConcentrationStart(Unit *pChar);
void AssaParticle_ConcentrationEffect(Unit *pChar,int liveCount,int SkillCode,int Light = TRUE);
//늬�귤�릊
void AssaParticle_SwiftAxeStart(Unit *pChar);
void AssaParticle_SwiftAxeEffect(Unit *pChar,int liveCount,int SkillCode,int Light = TRUE);

void AssaParticle_AvangingCrash(Unit* pChar);
void AssaParticle_BoneSmash1(Unit* pChar);
void AssaParticle_BoneSmash2(Unit* pChar);

//3차 스킬 파이크
void AssaParticle_VeonmSpear(Unit *pDest);
void AssaParticle_VeonmSpearPike(Unit *pChar);
void AssaParticle_Vanish(Unit *pChar);
void AssaParticle_ChainLance(POINT3D *pPosi);


//3차 스킬 아처
void AssaParticle_ElementalShotFire(POINT3D* pCur, POINT3D* pDest);
void AssaParticle_ElementalShotLighting(POINT3D* pCur, POINT3D* pDest);
void AssaParticle_GoldenFalcon(Unit *pChar, int liveCount);
void AssaParticle_BombHit1(POINT3D *pPosi);
void AssaParticle_BombShot(POINT3D* pCur, POINT3D* pDest);
void AssaParticle_Perforation(POINT3D* pCur, POINT3D* Dest);
void AssaParticle_PerforationHit(Unit* monster, Unit* character, float delay = 0.f);


//3차 스킬 메카니션
void AssaParticle_MetalArmorStart(Unit *pChar);
void AssaParticle_MetalArmorEffect(Unit *pChar, int liveCount);
void AssaParticle_GrandSmash(Unit *pChar);
void AssaParticle_SparkShieldStart(Unit* pChar);
void AssaParticle_SparkShieldEffect(Unit *pChar, int liveCount);
void AssaParticle_SparkShieldDefence(POINT3D *pPosi, POINT3D *pDesti);


//3차 스킬 메지션
void AssaParticle_EnergyShield(Unit *pChar,int liveCount);
void AssaParticle_EnergyShieldDefence(Unit *pChar);
void AssaParticle_Diastrophism(Unit *pChar);
void AssaParticle_DiastrophismPart(Unit *pChar);
void AssaParticle_SpiritElemental(Unit *pChar, int liveCount);

void AssaParticle_DancingSwordFire(Unit *pChar,int liveCount, int level);
void AssaParticle_DancingSwordIce(Unit *pChar,int liveCount, int level);

//3차 스킬 나이트
void AssaParticle_FlameBrandish(Unit *pChar);
void AssaParticle_FlameBrandishHit1(Unit *pChar);
void AssaParticle_HolyIncantationShot(Unit* pDestChar);
void AssaParticle_HolyIncantationPart(Unit* pDestChar, int liveCount);
void AssaParticle_HolyIncantationHand(Unit* pDestChar);

void AssaParticle_GrandCrossHorz(POINT3D* pPosi, int angleY);
void AssaParticle_GrandCrossVert(POINT3D* pPosi, int angleY);
void AssaParticle_DivineInhalationStart(Unit* pChar);
void AssaParticle_DivineInhalationPart(Unit* pChar, int liveCount);
void AssaParticle_DivineInhalationDefence(POINT3D *pDest);


//3차 아탈란타
void AssaParticle_SplitJavelin(POINT3D* pCur, POINT3D* pDest, int count = 2);
void AssaParticle_TriumphOfValhalla(Unit *pDestChar, int liveCount);
void AssaParticle_TriumphOfValhallaMember(Unit *pCurChar, Unit *pDestChar, int liveCount);
void AssaParticle_LightingJavelin(POINT3D* pCur, POINT3D* pDest);
void AssaParticle_StormJavelin(POINT3D* pCur, POINT3D* pDest);
void AssaParticle_StormJavelinHit(Unit* monster, Unit* character, float delay = 0.f);


//3차 스킬 프리스티스
void AssaParticle_VigorBall(Unit* pCurChar, Unit* pDestChar);
void AssaParticle_ResurrectionShot(Unit* pDestChar);
void AssaParticle_ResurrectionPart(Unit* pDestChar);
void AssaParticle_Extinction(Unit* pDestChar);
// �誅Χ�밟
void AssaParticle_VirtualLifeStart(Unit *pDestChar);
void AssaParticle_VirtualLifeEffect(Unit* pDestChar, int liveCount);

//쀼旗댔샌
void AssaParticle_Reaper(POINT3D *pos);
//뒈枸펜퓜
void AssaParticle_Spear(Unit *pDest);

//Monster 파티클
void AssaParticle_MonsterPigonHand(Unit* pChar);

//ClassUp 파티클
void AssaParticle_ClassUpWeapon(Unit* pChar);
void AssaParticle_StopClassUpWeapon(Unit* pChar);
void AssaParticle_AgingBody(Unit* pChar, int num);

// Element槻벎
void AssaParticle_ElementWeapon(Unit *pChar,int Kind,int Hand = 0);
void AssaParticle_ElementHit(Unit *pChar,int Kind,POINT3D *pos);

void AssParticle_AdvEffect(Unit *pChar);


//Iron Monster 스킬
void AssaParticle_MonsterExplision(POINT3D *pPosi);
void AssaParticle_MonsterIronSadNessHit1(Unit *pChar);
void AssaParticle_MonsterIronSadNessSkill1(Unit *pChar);
void AssaParticle_MonsterIronHyperHit1(Unit *pChar, POINT3D *pDest);
void AssaParticle_MonsterIronHyperSkill1(Unit *pChar, POINT3D *pDest);

void AssaParticle_MonsterIronChainGolem(Unit *pChar);
void AssaParticle_MonsterIronRunicGuardian(Unit *pChar, Unit *pDestChar);
void AssaParticle_MonsterIronMountainHit1(Unit *pChar);
void AssaParticle_MonsterIronMountainSkill1(Unit *pChar);
void AssaParticle_MonsterIronTowerGolemHit1(Unit *pChar);
void AssaParticle_MonsterIronTowerGolemSkill1(Unit *pChar);
void AssaParticle_MonsterIronHit1(POINT3D *pPosi);

void AssaParticle_MonsterIronOmuHit1(Unit *pChar);
void AssaParticle_MonsterIronFist(Unit *pChar);
void AssaParticle_MonsterIronMorgonHit(Unit *pChar);
void AssaParticle_MonsterAvelArcher(Unit *pChar, Unit *pDestChar);
void AssaParticle_MonsterAvelQueen(Unit *pChar, Unit *pDestChar);
void AssaParticle_MonsterDeadZoneDead(Unit *pChar);
void AssaParticle_MonsterHyperDead(Unit *pChar);

void AssaParticle_MonsterRunicGuardianHand(Unit *pChar);
void AssaParticle_MonsterRunicGuardianShot(Unit *pChar, Unit *pDestChar);
void AssaParticle_MonsterRunicGuardianBossLightShot(Unit **pCharList, int charCount);

void AssaParticle_MonsterRunicGuardianBossShot(Unit *pChar, int blendType = SMMAT_BLEND_INVSHADOW);
void AssaParticle_MonsterRunicGrardianBossSkill(Unit *pChar);
void AssaParticle_MonsterRunicGuardianBossSkillHit(POINT3D *pDest);
void AssaParticle_MonsterRunicGuardianBossWeapon(Unit *pChar);
void AssaParticle_MonsterRunicGuardianBossHit(Unit *pCurChar, Unit *pDestChar, Unit **charList = 0, int charCount = 0);

void AssaParticle_ShelltomShot(POINT3D *pPosi, POINT3D *pDest, int type = 0);
void AssaParticle_BamShot(POINT3D *pPosi, POINT3D *pDest);

void AssaParticle_ShelltomWeapon(Unit *pChar, int time, int code);
void AssaParticle_ShelltomWeaponHit(POINT3D *pPosi);

//Terrain 효과
void AssaParticle_TerrainShowStart();
void AssaParticle_TerrainFire(POINT3D *pCur, POINT3D *pDest, int delay = 0,int SkillCode = 0);
void AssaParticle_TerrainFireHit(POINT3D *pCur,int SkillCode);

void ParkAssaParticle_TurtleDragonHit(Unit *pCur, Unit *pDes);

void AssaMonsterHitTest(Unit *pChar);

void AssaParticle_TurtleDragonHit(POINT3D *pPosi);
void AssaParticle_TurtleDragonSkill(POINT3D *pPosi);
void AssaParticle_BoneHoundHit(Unit *pChar);

//4차 스킬
void SkillSaintGodlyShieldStart(Unit *pChar);
void SkillArchMageFlameWave(Unit *pChar);
void SkillCelestialChainLighting(Unit **pCharList, int charCount);
void SkillValhallaHallOfValhallaHandEffect(Unit *pChar, float time);
void SkillImpulsionLight(Unit *pChar, float time);
void SkillImpulsionLightHit(POINT3D *pos);
void SkillShadowMasterHit(POINT3D *pos);
void SkillPhoenixShotFlame(Unit *pChar, POINT3D *curPos);
void SkillGodBless(Unit *pChar);
void SkillParticle_FrostJavelin(Unit *pChar, float time);

void AssaMotionBlur(Unit *pChar, char *meshName1, char *meshName2, int timeCount);

//간옹薑세콘
void ParkParticle_DraxosSkill(Unit *pChar,int LiveCount);
void AssaParticle_Draxos(Unit *pChar);

void AssParticle_Greedy(Unit *pChar);

void AssParticle_Midranda(Unit *pChar);

void AssParticle_Faugn(Unit *pChar);

void AssParticle_Yagditha(Unit *pChar);


// 샙筠 툼翠旗루세콘槻벎
int ParkParticle_LandMinning_Skill(Unit *pChar);
// 우醵댔샌
void AssaParticle_HyperSonic(Unit *pChar,int LiveCount);
//濫�准８Ｐ㏏�
void AssaParticle_EnhenceEffect(Unit *pChar,int LiveCount);
void AssaParticle_EnhenceStart(Unit *pChar);
//쀼旗裂校槻벎
void AssaParticle_EvadEshot(Unit *pChar);
//旣밟裂校
void AssaParticle_S_Rope(POINT3D *curPos,POINT3D *desPos);
//已루裂숫
void AssaParticle_Splash(POINT3D *pos);
//벽깥裂숫
void AssaParticle_CircleTrap(POINT3D *curPos,POINT3D *desPos,int Level);
//뒈枸펜퓜
void AssParticle_Spear(Unit *pChar);
//�卉峴滿�
void AssaParticle_Moon(Unit *pChar);
//空쥣裂麓
void AssaParticle_Benedic(Unit *pChar);
//�卉峴滿�
void AssaParticle_Moon2(Unit *pChar);
//�溝陪滿�
void AssaParticle_Blade(Unit *pChar);
//空쥣裂麓
void AssaParticle_Benedic2(Unit *pChar);
void Assa_Benedic(Unit *pChar,int LiveCount);
//�誅Ο느�
void AssaParticle_Ignis(Unit *pChar,int blendType,int Count);
//햐校령爛
void AssaParticle_Taltria(Unit *pChar);
void AssaParticle_TaltriaEffect(Unit *pChar,int LiveCount);
//槿黛깃퓜
void AssaParticle_G_Coup(Unit *pChar);
void AssaParticle_G_Coup_Effect(POINT3D* pCur, POINT3D* pDest, int count);
//굻굻襟
void AssaParticle_SummonArcuda(Unit *pChar);
//죠落敲枸
void AssaParticle_S_Fear(POINT3D *pCur,POINT3D *pDest);
//�儁�깥훵
void AssaP_IceEffect(Unit *pCurChar, Unit *pDestChar);
//莖큽�♤�
void Assa_KrishnaEffect(Unit *pChar);
void Assa_KrishnaEffect(Unit *pChar,int LiveCount);

//세콘槻벎
void AssaCodeSkillEffect(char *pFileName, Unit *pChar,int Time,int SkillCode);
//갠붚�졔領㏏�
void AssaDarkWaveEffect(Unit *pCurChar, Unit *pDestChar,int SkillCode);
//�纘�
int ParkAssaParticle_Judgement(POINT3D *pPosi,POINT3D *pDesti);


// 아이스 필드

//ColdEye 레이저 쏘기..
int ParkAssaParticle_ColdEye(POINT3D *pPosi, POINT3D *pDesti);
//ColdEye 스킬공격
int ParkParticle_ColdEyeSkill(Unit *pChar);

int ParkParticle_RedEyeSkill(Unit *pChar);
// 깥彊쑨槻벎
int ParkAssaParticle_MisticSpinel(Unit *pChar);
// 웁�슭㎁�槻벎
int ParkAssaParticle_SealCrasherl(Unit *pChar);
// 깥솖뗀籠槻벎
int ParkAssaParticle_Tarantulika(Unit *pChar);

int ParkAssaParticle_AcientDia(Unit *pChar);
// 프로스트 에이션트 피어싱
int ParksinSkillEffect_AcientPiercing(Unit *pChar);
int ParksinSkillEffect_AcientPiercingAtt(Unit *pChar);

// 아이스 골렘 이펙트
int ParkAssaParticle_IceGolemShot(Unit *pChar);
// 프로즌 미스트	기본공격
int ParkAssaParticle_MistIceBolt(Unit* pCurChar, Unit* pDestChar);
// 프로즌 미스트	스킬공격
int ParkAssaParticle_MistIceBall(Unit* pCurChar, Unit* pDestChar);

// 아이스 고블린
int ParkAssaParticle_IceGoblinHit1(Unit *pChar);

int ParkAssaParticle_RedEye(POINT3D *pPosi,POINT3D *pDesti);

int ParkAssaParticle_Valento1(Unit* pValento);	// 데스나이트 브랜디쉬
int ParkAssaParticle_Valento2_1(Unit* pValento);	// 데스나이트 버서커 (피어싱의 기 모으기)
int ParkAssaParticle_Valento2_2(Unit* pValento);	// 버서커 후에 기를 모아쏜다.
int ParkAssaParticle_Valento3_1(Unit* pValento);	// 데스나이트 내려치기는 (ParkAssaParticle_Valento1) 호출 이함수는 올려치기.
void ParkAssaParticle_MonsterIceValentoBody(Unit *pValento);	// 데스나이트 몸통에 붙는 파티클
void ParkValentSwordShow(Unit* pValento, int nTime);	// 데스나이트 검기

// 띳침껍얽槻벎
void ParksinSkillEffect_TullaPiercing(Unit* pChar);

int ParkAssaParticle_ChaosKara1(Unit* pChar);	// 카오스 카라 일반공격
int ParkAssaParticle_ChaosKara2(Unit* pChar);	// 카오스 카라 아이스 미티어
int ParkAssaParticle_ChaosKaraSkill_Monster(Unit* pMonster); // 카오스카라 뱀파이어릭 (몬스터 자신)
int ParkAssaParticle_ChaosKaraSkill_User(Unit* pUser);	// 카오스카라 뱀파이어릭 (유저)
void ParkAssaParticle_MonsterIceChaosKara(Unit *pChar);	// 카오스 카라 스태프 파티클


///////////////// 새로운 필드 ////////////////
// 박철호 //
void ParkAssaParticle_SpiderTrooperHit1(Unit *pChar);	// 스파이더 트루퍼 독가스 뿜어내기

void ParkAssaParticle_StingRay(Unit *pChar);	//스팅레이 독가스 뿜어내기..
int ParkDivineLight_Effect(Unit *lpChar );		//디바인 라이트닝 스킬 연출 ( 이펙트 실현 )
int ParkAssaParticle_DivineLighting(Unit *pChar);	//디바인 라이트닝 스킬 연출 ( 이펙트 실현 )
int ParkAssaParticle_Sprak1(POINT3D *pPosi);
int ParkAssaParticle_Posion(Unit *pChar, int liveCount);		// 독걸린거 표현
void ParkAssaParticle_MummyShot(Unit *pChar, Unit *pDestChar);	// 머미로드 통상공격
#define STINGRAY_POSION_TIME	5

void ParkBlizzardGiantSkillToTarget(Unit *pTarget);	//블리자드 자이언트 스킬 이펙트

void ParkDevilBirdAttackBlur(Unit* pDevilBird);	// 데블 버드 일반 공격 시작시 블러
void ParkDevilBirdAttackNormal(Unit *pTarget);	// 데블 버드 공격동작 2번 타격이펙트
void ParkDevilBirdSkillToTarget(Unit *pTarget);	// 데블 버드 기술동작 타격 이펙트

void ParkAssaParticle_MonsterTurtleCanonNormal(Unit *pTCanon, Unit* pTarget);	// 터틀캐논 일반 공격

void ParkAssaParticle_FireCracker(Unit *pChar, int nFireCracker);	// 폭죽이펙트

// 푹죽 터트릴시 20개의 4차원배열 즉 20 ^ 4 의 테이블을 정의하여 리턴시켜준다.
// 번호만 입력하면 그 번호에 맞는 배열을 찿아서 인코드 하여 리턴시켜준다.
DWORD GetTableNum(int n);

// 4개의 값을 인코드한다.
DWORD Park_VarEncode(int a, int b, int c, int d);

// 인코드된 값을 다시 디코드 해준다.
void Park_VarDecode(DWORD dwData, int &nData1, int &nData2, int &nData3, int &nData4);

// 켈베쥬 이펙트
void ParkKelvezuHit(Unit *pChar);	// 켈베쥬 공격시 캐릭터 피격이펙트
void ParkKelvezuSkillHit(Unit *pChar);	// 켈베쥬 공격시 캐릭터 피격이펙트
void ParkKelvezuNormal1(Unit *pChar);
void ParkKelvezuNormal2(Unit *pKelvezu);
void ParkKelvezuSkill1(Unit *pKelvezu);
void ParkKelvezuSkill2(Unit *pKelvezu);
void ParkKelvezuJin(Unit *pKelvezu);	// 켈베쥬 마법진및 입에서 연기나는거

// 켈베쥬 공격시 발톱에서 검기효과
void ParkKelvezuFingerShow(Unit* pKelvezu, int nTime);

// 켈베쥬 공격시 날개에서 검기효과
void ParkKelvezuWingShow(Unit* pKelvezu, int nTime);

// 켈베쥬 공격시 꼬리에서 검기효과
void ParkKelvezuTaleShow(Unit* pKelvezu, int nTime);

// 월드컵 몬스터 이펙트
void ParkAssaParticle_WorldCupMonsterAttack(Unit* pMonster, Unit *pChar);
// 월드컵 몬스터가 공격시 캐릭터 피격이펙트
void ParkWorldCupMonsterHit(Unit *pChar);



// Dark Phalanx 기술 동작 이펙트 (창으로 찌를때 창이 파고드는 느낌의 이펙트 - 피어싱으로 처리)
void ParkAssaParticle_DarkPhalanx(Unit *pDarkPhalanx);

// 파이어 웜 일반 공격 및 스킬공격
void ParkAssaParticle_TerrainFireHit(POINT3D *pCur, int nType);
void ParkAssaParticle_TerrainFire(POINT3D *pCur, POINT3D *pDest, int delay = 0, int nType = 0);

void ParkAssaParticle_FireWorm(Unit* pTarget, BOOL bSkill = FALSE);
void ParkAssaParticle_IceWorm(Unit* pTarget, BOOL bSkill = FALSE);


// 키메라 일반공격 ( 발톱 블러 )
void ParkAssaParticle_ChimeraNormal(Unit *pChimera);

// 키메라 스킬공격 (헤딩 - 머리에 익스트림실드)
void ParkAssaParticle_ChimeraSkill(Unit *pChar);

// Bloody Knight 스킬 공격 (로어)
void ParkAssaParticle_BloodySkill(Unit *pBloodKnight);

// Bloody Knight 스킬 공격 피격 (스턴)
void ParkAssaParticle_BloodySkillStun(Unit *pChar);

// 헬 하운드 노말공격 (두발을 들어 대상을 내려찍음)
void ParkAssaParticle_HellHoundNormal(Unit *pChar);

// 헬 하운드 스킬공격 (입에서 불나감)
void ParkAssaParticle_HellHoundSkillAttack(Unit *pHellHound);

// 헬 하운드 스킬공격의 피격시 (화염에 휩싸인듯한 이펙트)
void ParkAssaParticle_HellHoundSkillTaget(Unit *pChar);

// 다크 가드 기본공격 피격시
void ParkAssaParticle_DarkGuardTaget(Unit *pChar);

// 다크 가드 스킬공격
void ParkAssaParticle_DarkGuardSkill(Unit *pDarkGuard, Unit *pChar);

// 다크 메이지 기본공격
void ParkAssaParticle_DarkMageNormal(Unit *pDarkMage, Unit *pChar);

// 다크 메이지 스킬공격
void ParkAssaParticle_DarkMageSkill(Unit *pChar);

// 다크 메이지 죽을때
void ParkAssaParticle_DarkMageDead(Unit *pDarkMage);






#endif