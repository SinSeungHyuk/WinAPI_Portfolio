#include "pch.h"
#include "CPlayerMoveState.h"
#include "CTimeMgr.h"

void CPlayerMoveState::Enter()
{
	LOG(LOG_LEVEL::WARNING, L"Enter 1번 레이어");
}

void CPlayerMoveState::FinalTick()
{
	timer += DT;

	if (timer > 1.3f) {
		LOG(LOG_LEVEL::LOG, L"1번 레이어");
		timer = 0.f;
	}
	

}

void CPlayerMoveState::Exit()
{
}

CPlayerMoveState::CPlayerMoveState()
{
}


CPlayerMoveState::~CPlayerMoveState()
{
}
