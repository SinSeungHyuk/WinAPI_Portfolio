#include "pch.h"
#include "CTraceState.h"

#include "CMonster.h"

CTraceState::CTraceState()
	: m_Return(false)
{
}

CTraceState::~CTraceState()
{
}

void CTraceState::Enter()
{
	LOG(LOG_LEVEL::WARNING, L"Enter TraceState");
	LOG(LOG_LEVEL::WARNING, L"Enter TraceState");

	CMonster* pMonster = GetOwner<CMonster>();
	m_InitPos = pMonster->GetPos();
}

void CTraceState::FinalTick()
{
	if (false == m_Return)
	{
		// Trace ������ ���͸� �˾Ƴ���.
		CMonster* pMonster = GetOwner<CMonster>();

		// Player �� �����Ѵ�.
		CPlayer* pPlayer = CLevelMgr::Get()->GetCurrentLevel()->GetPlayer();

		Vec2 vDir = pPlayer->GetPos() - pMonster->GetPos();
		vDir.Normalize();

		Vec2 vPos = pMonster->GetPos() + vDir * pMonster->GetMonsterInfo().Speed * DT;
		pMonster->SetPos(vPos);

		// ���� Player �� Ž������ �̻����� �־����� 
		// or ������ ������ ���ķ� �����ð��� ���� ���
		// or �ʱ���ġ���� �����Ÿ� �̻� �߰��Ѱ��
		float Distance = pMonster->GetPos().Distance(pPlayer->GetPos());
		if (pMonster->GetMonsterInfo().DetectRange < Distance)
		{
			m_Return = true;
		}
	}

	else
	{
		// ���� ��ġ�� ���ư���.
		CMonster* pMonster = GetOwner<CMonster>();
		Vec2 vDir = m_InitPos - pMonster->GetPos();
		vDir.Normalize();
		Vec2 vNewPos = pMonster->GetPos() + vDir * pMonster->GetMonsterInfo().Speed * 2.f * DT;
		pMonster->SetPos(vNewPos);

		// �ʱ���ġ�� ������ �ǵ��ƿ��� IdleState �� ����
		if (pMonster->GetPos().Distance(m_InitPos) < 0.1f)
		{
			pMonster->SetPos(m_InitPos);
			GetStateMachine()->ChangeState(L"IdleState");
		}
	}
}

void CTraceState::Exit()
{
	LOG(LOG_LEVEL::WARNING, L"Exit TraceState");
	LOG(LOG_LEVEL::WARNING, L"Exit TraceState");
	m_Return = false;
}