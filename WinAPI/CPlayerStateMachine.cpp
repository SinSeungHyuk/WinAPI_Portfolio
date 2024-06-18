#include "pch.h"
#include "CPlayerStateMachine.h"

#include "CPlayerIdleState.h"
#include "CPlayerMoveState.h"


CPlayerStateMachine::CPlayerStateMachine()
{
	AddStates();
	SetLayer();
}

CPlayerStateMachine::~CPlayerStateMachine()
{
}

void CPlayerStateMachine::AddStates()
{
	AddState(L"IdleState", new CPlayerIdleState, 0);
	AddState(L"MoveState", new CPlayerMoveState, 1);
}
