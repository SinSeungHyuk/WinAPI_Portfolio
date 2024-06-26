#include "pch.h"
#include "CCoinItem.h"

#include "CCollider.h"
#include "CAnimator.h"
#include "CAnim.h"
#include "CTaskMgr.h"
#include "CEngine.h"
#include "CPathMgr.h"

#include "CAssetMgr.h"
#include "CGameManager.h"
#include "CTexture.h"

CCoinItem::CCoinItem()
	: CItem()
	, animator(nullptr)
{
	collider = AddComponent(new CCollider);
	collider->SetName(L"Collider");
	collider->SetOffset(Vec2(0.f, -16.f));
	collider->SetScale(Vec2(32.f, 32.f));

	// Player 에 Animator 컴포넌트 추가
	animator = AddComponent(new CAnimator);

	tAnimDesc desc = {};
	desc.AnimName = L"COIN";
	desc.FPS = 10;
	desc.FrmCount = 6;
	desc.pAtlas = CAssetMgr::Get()->LoadTexture(L"COIN", L"texture\\coin.png");
	desc.SliceSize = Vec2(32.f, 32.f);
	desc.StartLeftTop = Vec2(0.f, 0.f);	
	desc.animOffset = Vec2(0.f, -16.f);
	animator->CreateAnimation(desc);
	
	// Animation 정보 저장하기
	animator->SaveAnimation(L"animation\\Item\\");

	animator->Play(L"COIN", true);
}

CCoinItem::~CCoinItem()
{
}


void CCoinItem::Tick()
{
}

void CCoinItem::Render()
{
	animator->Render();
}

void CCoinItem::GetItem()
{
	CGameManager::Get()->GetCoin();
}

