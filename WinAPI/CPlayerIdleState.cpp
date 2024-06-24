#include "pch.h"
#include "CPlayerIdleState.h"

void CPlayerIdleState::Enter()
{
	player = GetOwner<CPlayer>();

	if (player->IsPlayerLeft())
		player->animator->Play(L"IDLE_LEFT", true);
	else 
		player->animator->Play(L"IDLE_RIGHT", true);
}

void CPlayerIdleState::FinalTick()
{
	
}

void CPlayerIdleState::Exit()
{
}

CPlayerIdleState::CPlayerIdleState()
	: player(nullptr)
{

}

CPlayerIdleState::~CPlayerIdleState()
{
}
