#include "pch.h"
#include "CMonster.h"


#include "CEngine.h"
#include "CAssetMgr.h"
#include "CCollider.h"
#include "CTimeMgr.h"

#include "CTexture.h"

#include "CStateMachine.h"
#include "CIdleState.h"
#include "CTraceState.h"
#include "CAttackState.h"

CMonster::CMonster()
	: m_Texture(nullptr)
	, m_HP(5)
	, m_Info{}
{
	m_Info.DetectRange = 300.f;
	m_Info.Speed = 100.f;


	m_Collider = AddComponent(new CCollider);
	m_Collider->SetScale(Vec2(200.f, 200.f));

	CStateMachine* pSM = AddComponent(new CStateMachine);
	pSM->AddState(L"IdleState", new CIdleState);
	pSM->AddState(L"TraceState", new CTraceState);
	pSM->AddState(L"AttackState", new CAttackState);

	pSM->ChangeState(L"IdleState");
}

CMonster::CMonster(const CMonster& _Other)
	: CObj(_Other)
	, m_Info(_Other.m_Info)
	, m_Texture(_Other.m_Texture)
	, m_Collider(nullptr)
	, m_HP(_Other.m_HP)
{
	m_Collider = GetComponent<CCollider>();
}

CMonster::~CMonster()
{
}

void CMonster::Tick()
{

}

void CMonster::Render()
{
	HDC dc = CEngine::Get()->GetBackDC();

	Vec2 vPos = GetRenderPos();	
	UINT width = m_Texture->GetWidth();
	UINT height = m_Texture->GetHeight();
	
	// TransparentBlt
	/*{
		TransparentBlt(BackDC, (int)vPos.x - width / 2, (int)vPos.y - height / 2
			, width, height, m_Texture->GetDC(), 0, 0, width, height, RGB(255, 0, 255));
	}*/

	// AlphaBlending
	{
		BLENDFUNCTION blend = {};
		blend.BlendOp = AC_SRC_OVER;
		blend.BlendFlags = 0;
		blend.SourceConstantAlpha = 255;
		blend.AlphaFormat = AC_SRC_ALPHA;
				
		AlphaBlend(BackDC, (int)vPos.x - width / 2, (int)vPos.y - height / 2
				  , width, height, m_Texture->GetDC(), 0, 0, width, height, blend);
	}
}

void CMonster::BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider)
{
	return;

	/*if (L"Player" == _OtherObj->GetName())
	{
		DeleteObject(this);
	}*/

	if (L"Missile" == _OtherObj->GetName())
	{
		m_HP -= 1;

		if (m_HP <= 0)
		{
			DeleteObject(this);
		}
	}
}