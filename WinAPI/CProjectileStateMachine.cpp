#include "pch.h"
#include "CProjectileStateMachine.h"

#include "CPatrolState.h"
#include "CDetectePlayerState.h"
#include "CProjectileState.h"

CProjectileStateMachine::CProjectileStateMachine()
{
	AddStates();
}

CProjectileStateMachine::~CProjectileStateMachine()
{
}

void CProjectileStateMachine::AddStates()
{
	AddState(L"PatrolState", new CPatrolState, (int)StateMachineLayer::MovementLayer);
	AddState(L"ProjectileState", new CProjectileState, (int)StateMachineLayer::MovementLayer);

	AddState(L"DetectePlayerState", new CDetectePlayerState, (int)StateMachineLayer::DetectLayer);
}
