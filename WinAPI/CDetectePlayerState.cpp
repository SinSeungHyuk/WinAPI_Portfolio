#include "pch.h"
#include "CDetectePlayerState.h"

#include "CMonster.h"
#include "MonsterData.h"

void CDetectePlayerState::Enter()
{
	monster = GetOwner<CMonster>();
	player = CLevelMgr::Get()->GetCurrentLevel()->GetPlayer();
	data = monster->GetMonsterData();
}

void CDetectePlayerState::FinalTick()
{
	pos = monster->GetPos();
	playerPos = player->GetPos();

	float distance = pos.Distance(playerPos);

	if (data->GetDetectRange() >= distance) {
		if (pos.y < playerPos.y) return; // 몬스터가 위에 있으면 감지x
		monster->DetectPlayer(true);
	}
	else monster->DetectPlayer(false);
}

void CDetectePlayerState::Exit()
{
}

CDetectePlayerState::CDetectePlayerState()
	: monster(nullptr), player(nullptr), data(nullptr)
{
}

CDetectePlayerState::~CDetectePlayerState()
{
}
