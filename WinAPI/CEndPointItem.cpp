#include "pch.h"
#include "CEndPointItem.h"

#include "CCollider.h"
#include "CAnimator.h"
#include "CAnim.h"
#include "CTaskMgr.h"
#include "CEngine.h"
#include "CPathMgr.h"

#include "CAssetMgr.h"
#include "CGameManager.h"
#include "CTexture.h"

CEndPointItem::CEndPointItem()
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
	desc.AnimName = L"ENDPOINT";
	desc.FPS = 15;
	desc.FrmCount = 10;
	desc.pAtlas = CAssetMgr::Get()->LoadTexture(L"ENDPOINT", L"texture\\EndPoint.png");
	desc.SliceSize = Vec2(128.f, 128.f);
	desc.StartLeftTop = Vec2(0.f, 0.f);
	desc.animOffset = Vec2(0.f, -64.f);
	animator->CreateAnimation(desc);

	// Animation 정보 저장하기
	animator->SaveAnimation(L"animation\\Item\\");

	animator->Play(L"ENDPOINT", true);
}

CEndPointItem::~CEndPointItem()
{
}

void CEndPointItem::Tick()
{
}

void CEndPointItem::Render()
{
	animator->Render();
}

void CEndPointItem::GetItem()
{
}

