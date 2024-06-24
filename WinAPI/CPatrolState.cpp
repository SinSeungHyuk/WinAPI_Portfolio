#include "pch.h"
#include "CPatrolState.h"

#include "CMonster.h"


void CPatrolState::Enter()
{
	monster = GetOwner<CMonster>();

	monster->animator->Play(L"PINK_RUN_RIGHT", true);
}

void CPatrolState::FinalTick()
{

}

void CPatrolState::Exit()
{
}

CPatrolState::CPatrolState()
	: monster(nullptr)
{
}

CPatrolState::~CPatrolState()
{
}
