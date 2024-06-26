#include "pch.h"
#include "CPatrolState.h"

#include "CMonster.h"
#include "MonsterData.h"


void CPatrolState::Enter()
{
	monster = GetOwner<CMonster>();
}

void CPatrolState::FinalTick()
{
	pos = monster->GetPos();
	data = monster->GetMonsterData();

	if (!monster->isMonsterLeft)
		pos.x += data->GetSpeed() * DT;
	else
		pos.x -= data->GetSpeed() * DT;

	monster->SetPos(pos);
}

void CPatrolState::Exit()
{
}

CPatrolState::CPatrolState()
	: monster(nullptr), data(nullptr)
{
}

CPatrolState::~CPatrolState()
{
}
