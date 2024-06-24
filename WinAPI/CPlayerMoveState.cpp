#include "pch.h"
#include "CPlayerMoveState.h"
#include "CTimeMgr.h"
#include "CPlayer.h"


void CPlayerMoveState::Enter()
{
	player = GetOwner<CPlayer>();

	if (player->IsPlayerLeft())
		player->animator->Play(L"RUN_LEFT", true);
	else 
		player->animator->Play(L"RUN_RIGHT", true);
}

void CPlayerMoveState::FinalTick()
{
	

}

void CPlayerMoveState::Exit()
{
}

CPlayerMoveState::CPlayerMoveState()
	: player(nullptr)
{
}


CPlayerMoveState::~CPlayerMoveState()
{
}
