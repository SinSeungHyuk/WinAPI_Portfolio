#include "pch.h"
#include "CGemItem.h"

#include "CCollider.h"
#include "CAnimator.h"
#include "CAnim.h"
#include "CTaskMgr.h"
#include "CEngine.h"
#include "CPathMgr.h"

#include "CAssetMgr.h"
#include "CGameManager.h"
#include "CTexture.h"

CGemItem::CGemItem()
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
	desc.AnimName = L"GEM";
	desc.FPS = 10;
	desc.FrmCount = 5;
	desc.pAtlas = CAssetMgr::Get()->LoadTexture(L"GEM", L"texture\\gem.png");
	desc.SliceSize = Vec2(32.f, 32.f);
	desc.StartLeftTop = Vec2(0.f, 0.f);
	desc.animOffset = Vec2(0.f, -16.f);
	animator->CreateAnimation(desc);

	// Animation 정보 저장하기
	animator->SaveAnimation(L"animation\\Item\\");

	animator->Play(L"GEM", true);
}

CGemItem::~CGemItem()
{
}


void CGemItem::Tick()
{
}

void CGemItem::Render()
{
	animator->Render();
}

void CGemItem::GetItem()
{
}

