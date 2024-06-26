#include "pch.h"
#include "CTracePlayerState.h"

#include "CTraceMonster.h"
#include "MonsterData.h"


void CTracePlayerState::Enter()
{
	monster = GetOwner<CTraceMonster>();
	player = CLevelMgr::Get()->GetCurrentLevel()->GetPlayer();

	monster->SetTrace(true);
	monster->GetMonsterData()->SetSpeed(monster->GetMonsterData()->GetSpeed() * 2);
}

void CTracePlayerState::FinalTick()
{
	pos = monster->GetPos();
	playerPos = player->GetPos();
	data = monster->GetMonsterData();

	bool isPlayerLeft = (pos.x - playerPos.x) < 0 ? true : false;

	if (isPlayerLeft) {
		pos.x += data->GetSpeed() * DT;
		isPlayerLeft = true;
	}
	else {
		pos.x -= data->GetSpeed() * DT;
		isPlayerLeft = false;
	}

	monster->PlayTraceAnim(isPlayerLeft);
	monster->SetPos(pos);
}

void CTracePlayerState::Exit()
{
	monster->GetMonsterData()->SetSpeed(150.f);
	monster->SetTrace(false);
}

CTracePlayerState::CTracePlayerState()
	: monster(nullptr), player(nullptr), data(nullptr)
{
}

CTracePlayerState::~CTracePlayerState()
{
}
