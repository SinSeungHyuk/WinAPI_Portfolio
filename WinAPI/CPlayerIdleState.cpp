#include "pch.h"
#include "CPlayerIdleState.h"

void CPlayerIdleState::Enter()
{
	LOG(LOG_LEVEL::WARNING, L"Enter IdleState");
}

void CPlayerIdleState::FinalTick()
{
	timer += DT;

	if (timer > 0.9f) {
		LOG(LOG_LEVEL::LOG, L"0번 레이어");
		timer = 0.f;
	}
}

void CPlayerIdleState::Exit()
{
}

CPlayerIdleState::CPlayerIdleState()
{
}

CPlayerIdleState::~CPlayerIdleState()
{
}
