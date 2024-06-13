#include "pch.h"
#include "CPlatform.h"

#include "CPlayer.h"
#include "CCollider.h"
#include "CRigidBody.h"

CPlatform::CPlatform()
	: m_Collider(nullptr)
{
	m_Collider = AddComponent(new CCollider);
}

CPlatform::CPlatform(const CPlatform& _Other)
	: CObj(_Other)
	, m_Collider(nullptr)
{
	m_Collider = GetComponent<CCollider>();
}

CPlatform::~CPlatform()
{

}

void CPlatform::SetScale(Vec2 _Scale)
{
	CObj::SetScale(_Scale);

	if (m_Collider)
	{
		m_Collider->SetScale(_Scale);
	}
}

void CPlatform::SetScale(float _Width, float _Height)
{
	CObj::SetScale(_Width, _Height);

	if (m_Collider)
	{
		m_Collider->SetScale(Vec2(_Width, _Height));
	}
}

void CPlatform::Tick()
{

}

void CPlatform::BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider)
{
	CPlayer* pOtherObj = dynamic_cast<CPlayer*>(_OtherObj);
	if (pOtherObj)
	{
		CRigidBody* pRigidBody = pOtherObj->GetComponent<CRigidBody>();
		pRigidBody->SetGround(true);
	}
}

void CPlatform::EndOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider)
{
	CPlayer* pOtherObj = dynamic_cast<CPlayer*>(_OtherObj);
	if (pOtherObj)
	{
		CRigidBody* pRigidBody = pOtherObj->GetComponent<CRigidBody>();
		pRigidBody->SetGround(false);
	}
}
