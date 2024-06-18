#include "pch.h"
#include "CLevel_Start.h"

#include "CEngine.h"
#include "CPlayer.h"
#include "CForce.h"
#include "CMonster.h"
#include "CPlatform.h"
#include "CTile.h"

#include "CAssetMgr.h"
#include "CSound.h"


#include "CCollisionMgr.h"
#include "CKeyMgr.h"

CLevel_Start::CLevel_Start()
{
}

CLevel_Start::~CLevel_Start()
{
}

void CLevel_Start::Init()
{
	// BGM 지정
	//CSound* pBGM = CAssetMgr::Get()->LoadSound(L"DM_BGM", L"sound\\DM.wav");
	//pBGM->Play();



	// 오브젝트 위치 설정
	CPlayer* pPlayer = new CPlayer;
	pPlayer->SetName(L"Player");
	Vec2 vResol = CEngine::Get()->GetResolution();
	pPlayer->SetPos(vResol.x / 2.f, vResol.y / 4.f);
	pPlayer->SetScale(64.f, 64.f);

	// 플레이어를 현재 레벨에 등록
	RegisterPlayer(pPlayer);

	// 플레이어를 레벨에 추가
	AddObject(pPlayer, LAYER_TYPE::PLAYER);

	// Monster
	CMonster* pObj = new CMonster;
	pObj->SetName(L"Monster");
	pObj->SetPos(vResol.x / 2.f + 300.f, vResol.y / 4.f - 100.f);	
	pObj->SetTexture(CAssetMgr::Get()->LoadTexture(L"Character", L"texture\\Character.png"));

	AddObject(pObj, LAYER_TYPE::MONSTER);

	CMonster* pCloneMonster = pObj->Clone();
	pCloneMonster->SetPos(pObj->GetPos() + Vec2(-200.f, 0.f));	
	AddObject(pCloneMonster, LAYER_TYPE::MONSTER);


	// Platform
	CPlatform* pPlatform = new CPlatform;
	pPlatform->SetName(L"Platform");
	pPlatform->SetPos(vResol.x / 2.f, 3.f * (vResol.y / 4.f));
	pPlatform->SetScale(800.f, 150.f);
	AddObject(pPlatform, LAYER_TYPE::PLATFORM);



	


	// 충돌 지정
	CCollisionMgr::Get()->CollisionCheck(5, 3, true);
	CCollisionMgr::Get()->CollisionCheck((UINT)LAYER_TYPE::PLAYER_PROJECTILE, (UINT)LAYER_TYPE::MONSTER, true);
	CCollisionMgr::Get()->CollisionCheck((UINT)LAYER_TYPE::PLAYER, (UINT)LAYER_TYPE::PLATFORM, true);
}

void CLevel_Start::Exit()
{
	// 모든 오브젝트를 삭제해둔다.
	DeleteAllObjects();
}

void CLevel_Start::Tick()
{
	CLevel::Tick();

	// 마우스 클릭이 발생 시, 해당 위치에 Force 오브젝트 생성
	if (KEY_TAP(KEY::LBTN))
	{
		Vec2 vPos = CKeyMgr::Get()->GetMousePos();

		CForce* pForce = new CForce;
		pForce->SetPos(vPos);
		pForce->SetForce(-1000.f, 300.f);
		pForce->SetLifeTime(0.2f);
		
		CreateObject(pForce, LAYER_TYPE::DEFAULT);
	}

	if (KEY_TAP(KEY::ENTER))
	{
		ChangeLevel(LEVEL_TYPE::EIDTOR);
		CCamera::Get()->SetFilterEffect(FADE_OUT, 0.5f);
		CCamera::Get()->SetFilterEffect(FADE_IN, 0.5f);
	}
}