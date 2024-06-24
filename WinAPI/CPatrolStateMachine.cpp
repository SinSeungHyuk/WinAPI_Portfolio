#include "pch.h"
#include "CPatrolStateMachine.h"

#include "CPatrolState.h"

CPatrolStateMachine::CPatrolStateMachine()
{
	AddStates();
}

CPatrolStateMachine::~CPatrolStateMachine()
{
}

void CPatrolStateMachine::AddStates()
{
	AddState(L"PatrolState", new CPatrolState, 0);
}
