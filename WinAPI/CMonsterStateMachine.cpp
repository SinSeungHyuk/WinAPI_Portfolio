#include "pch.h"
#include "CMonsterStateMachine.h"
//#include "CIdleState.h"

CMonsterStateMachine::CMonsterStateMachine()
{
	AddStates();
	SetLayer();
}

CMonsterStateMachine::~CMonsterStateMachine()
{
}

void CMonsterStateMachine::AddStates()
{
	int a = 2;

	//AddState(L"IdleState", new CIdleState);
}
