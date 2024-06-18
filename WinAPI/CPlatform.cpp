#include "pch.h"
#include "CPlatform.h"

#include "CPlayer.h"
#include "CCollider.h"
#include "CRigidBody.h"
#include "CTexture.h"
#include "CAssetMgr.h"
#include "CEngine.h"

CPlatform::CPlatform()
	: m_Collider(nullptr), texture(nullptr)
{
	m_Collider = AddComponent(new CCollider);
}

CPlatform::CPlatform(const CPlatform& _Other)
	: CObj(_Other)
	, m_Collider(nullptr), texture(nullptr)
{
	m_Collider = GetComponent<CCollider>();
	texture = GetComponent<CTexture>();
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


		// �Ʒ����� ���� �ö������ �ε���
		if (pOtherObj->GetPrevPos().y - pOtherObj->GetPos().y > 0.f) overlapType = OVERLAP_TYPE::IS_COLLISION_UP;
		// ������ �Ʒ��� ���������� �ε���
		else if (pOtherObj->GetPrevPos().y - (GetPos().y - GetScale().y * 0.45f) < 0.f) {

			pRigidBody->SetGround(true); // �ٴ� ���鿡 ���� ��� SetGround(true)
			overlapType = OVERLAP_TYPE::IS_COLLISION_DOWN;
		}
		// ���ʿ��� ���������� �ε���
		else if (pOtherObj->GetPrevPos().x - pOtherObj->GetPos().x > 0.f) overlapType = OVERLAP_TYPE::IS_COLLISION_LEFT;
		// �����ʿ��� �������� �ε���
		else if (pOtherObj->GetPrevPos().x - pOtherObj->GetPos().x < 0.f) overlapType = OVERLAP_TYPE::IS_COLLISION_RIGHT;
	}
}

void CPlatform::Overlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider)
{
	CPlayer* pOtherObj = dynamic_cast<CPlayer*>(_OtherObj);
	if (pOtherObj)
	{
		pOtherObj->SetCollisionType(overlapType, true);
	}
}

void CPlatform::EndOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider)
{
	CPlayer* pOtherObj = dynamic_cast<CPlayer*>(_OtherObj);
	if (pOtherObj)
	{
		CRigidBody* pRigidBody = pOtherObj->GetComponent<CRigidBody>();
		if (overlapType == OVERLAP_TYPE::IS_COLLISION_DOWN)
			pRigidBody->SetGround(false); // �ٴ� ���鿡 �ִٰ� ������ ��� SetGround(false)

		pOtherObj->SetCollisionType(overlapType, false);

	}
}