#include "pch.h"
#include "CLevel_Start.h"

#include "CEngine.h"
#include "CPlayer.h"
#include "CCollider.h"
#include "CPatrolMonster.h"
#include "CTraceMonster.h"
#include "CProjectileMonster.h"
#include "ItemDropEvent.h"
#include "CPlatform.h"
#include "CTile.h"
#include "CImage.h"
#include "CCoinItem.h"
#include "CEndPointItem.h"

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
	pPlayer->SetPos(vResol.x * 0.5f, vResol.y / 3.f);
	pPlayer->SetScale(64.f, 64.f);
	// 플레이어를 현재 레벨에 등록
	RegisterPlayer(pPlayer);
	// 플레이어를 레벨에 추가
	AddObject(pPlayer, LAYER_TYPE::PLAYER);

	// Monster
	DeathEventStrategy* deathEvent = new ItemDropEvent();
	CMonster* monster1 = new CProjectileMonster(3,150.0f,300.0f,deathEvent);
	monster1->SetScale(64.f, 64.f);
	monster1->SetName(L"Monster");
	monster1->SetPos(750.f,100.f);
	AddObject(monster1, LAYER_TYPE::MONSTER);

	//CMonster* monster2 = new CTraceMonster(3, 150.0f, 300.0f, deathEvent);
	//monster2->SetScale(64.f, 64.f);
	//monster2->SetName(L"Monster2");
	//monster2->SetPos(700.f, 100.f);
	//AddObject(monster2, LAYER_TYPE::MONSTER);

		//	// Item
	CItem* coin = new CCoinItem;
	coin->SetName(L"coin");
	coin->SetPos(1200.f, 500.f);
	coin->SetScale(32.f, 32.f);
	AddObject(coin, LAYER_TYPE::ITEM);

	CItem* coin2 = new CCoinItem;
	coin2->SetName(L"coin");
	coin2->SetPos(1250.f, 500.f);
	coin2->SetScale(32.f, 32.f);
	AddObject(coin2, LAYER_TYPE::ITEM);


	// Platform
	CPlatform* pPlatform = new CPlatform;
	pPlatform->SetName(L"Platform");
	pPlatform->SetPos(700.f, 700.f);
	pPlatform->SetScale(1800.f, 100.f);
	AddObject(pPlatform, LAYER_TYPE::PLATFORM);

	CPlatform* pPlatform2 = new CPlatform;
	pPlatform2->SetName(L"Platform");
	pPlatform2->SetPos(700.f, 550.f);
	pPlatform2->SetScale(400.f, 100.f);
	AddObject(pPlatform2, LAYER_TYPE::PLATFORM);

	CPlatform* pPlatform4 = new CPlatform;
	pPlatform4->SetPos(500.f, 450.f);
	pPlatform4->SetScale(10.f, 10.f);
	pPlatform4->GetComponent<CCollider>()->SetTrigger(true);
	AddObject(pPlatform4, LAYER_TYPE::PLATFORM);

	CPlatform* pPlatform3 = new CPlatform;
	pPlatform3->SetPos(900.f, 450.f);
	pPlatform3->SetScale(10.f, 10.f);
	pPlatform4->GetComponent<CCollider>()->SetTrigger(true);
	AddObject(pPlatform3, LAYER_TYPE::PLATFORM);

	CImage* image = new CImage;
	image->SetPos(500.f, 50.f);
	image->SetTexture(CAssetMgr::Get()->LoadTexture(L"gemImage", L"texture\\gemImage.png"));
	AddObject(image, LAYER_TYPE::UI);
	


	// 충돌 지정
	CCollisionMgr::Get()->CollisionCheck(5, 3, true);
	CCollisionMgr::Get()->CollisionCheck((UINT)LAYER_TYPE::PLAYER, (UINT)LAYER_TYPE::MONSTER, true);
	CCollisionMgr::Get()->CollisionCheck((UINT)LAYER_TYPE::PLAYER, (UINT)LAYER_TYPE::ITEM, true);
	CCollisionMgr::Get()->CollisionCheck((UINT)LAYER_TYPE::PLATFORM, (UINT)LAYER_TYPE::MONSTER, true);
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

	if (KEY_TAP(KEY::ENTER))
	{
		ChangeLevel(LEVEL_TYPE::EIDTOR);
		CCamera::Get()->SetFilterEffect(FADE_OUT, 0.5f);
		CCamera::Get()->SetFilterEffect(FADE_IN, 0.5f);
	}
}