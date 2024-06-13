#include "pch.h"
#include "CIdleState.h"


#include "CMonster.h"

CIdleState::CIdleState()
{
}

CIdleState::~CIdleState()
{
}

void CIdleState::Enter()
{
	LOG(LOG_LEVEL::WARNING, L"Enter IdleState");
	LOG(LOG_LEVEL::WARNING, L"Enter IdleState");
}

void CIdleState::FinalTick()
{
	// 몬스터의 인식범위 내에 Player 가 있는지 확인한다.
	CMonster* pMonster = GetOwner<CMonster>();

	float DetectRange = pMonster->GetMonsterInfo().DetectRange;

	// DetecteRange 디버그 렌더링
	DrawDebugShape(DEBUG_SHAPE::CIRCLE, PEN_TYPE::BLUE, BRUSH_TYPE::HOLLOW
		         , pMonster->GetRenderPos(), Vec2(DetectRange * 2.f, DetectRange * 2.f));


	// 만약에 인식범위 내에 Player 가 있었으면 자신의 상태를 TraceState 상태로 변경한다.
	CPlayer* pPlayer = CLevelMgr::Get()->GetCurrentLevel()->GetPlayer();

	float Distance = pMonster->GetPos().Distance(pPlayer->GetPos());

	if (Distance < DetectRange)
	{
		GetStateMachine()->ChangeState(L"TraceState");
	}
}

void CIdleState::Exit()
{
	LOG(LOG_LEVEL::WARNING, L"Exit IdleState");
	LOG(LOG_LEVEL::WARNING, L"Exit IdleState");
}
