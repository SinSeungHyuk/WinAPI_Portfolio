#include "pch.h"
#include "CTraceStateMachine.h"

#include "CPatrolState.h"
#include "CTracePlayerState.h"
#include "CDetectePlayerState.h"

CTraceStateMachine::CTraceStateMachine()
{
	AddStates();
}

CTraceStateMachine::~CTraceStateMachine()
{
}

void CTraceStateMachine::AddStates()
{
	AddState(L"PatrolState", new CPatrolState, (int)StateMachineLayer::MovementLayer);
	AddState(L"TracePlayerState", new CTracePlayerState, (int)StateMachineLayer::MovementLayer);


	AddState(L"DetectePlayerState", new CDetectePlayerState, (int)StateMachineLayer::DetectLayer);
}
