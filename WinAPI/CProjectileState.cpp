#include "pch.h"
#include "CProjectileState.h"

#include "CProjectileMonster.h"
#include "MonsterData.h"
#include "CMissile.h"
#include "CTaskMgr.h"
#include "CAssetMgr.h"

void CProjectileState::Enter()
{
	monster = GetOwner<CProjectileMonster>();
	player = CLevelMgr::Get()->GetCurrentLevel()->GetPlayer();
	data = monster->GetMonsterData();

	timer = 0.f;
}

void CProjectileState::FinalTick()
{
	pos = monster->GetPos();
	playerPos = player->GetPos();

	timer += DT;

	if (timer > 1.f) {
		bool isPlayerLeft = (pos.x - playerPos.x) < 0 ? true : false;
		monster->SetPlayerLeft(isPlayerLeft);
		monster->PlayAnimation(ANIMATION_TYPE::ATTACK);

		CMissile* pMissile = new CMissile;
		pMissile->SetName(L"Missile");
		pMissile->SetTexture(CAssetMgr::Get()->LoadTexture(L"bullet", L"texture\\bullet.png"));
		pMissile->SetPos(pos.x, pos.y-monster->GetScale().y*0.5f);
		pMissile->SetVelocity(playerPos - pos, 350.f);

		CreateObject(pMissile, LAYER_TYPE::MONSTER_PROJECTILE);

		timer = 0.f;
	}
}

void CProjectileState::Exit()
{
}

CProjectileState::CProjectileState()
{
}

CProjectileState::~CProjectileState()
{
}
