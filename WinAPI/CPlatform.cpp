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

void CPlatform::BeginOverlap(CCollider* ownCollider, CObj* otherObj, CCollider* otherCollider)
{
	if (ownCollider->GetTrigger()) {

	}


	CPlayer* player = dynamic_cast<CPlayer*>(otherObj);
	if (player)
	{
		CRigidBody* playerRigidbody = player->GetComponent<CRigidBody>();

 		float playerPosUp = player->GetPos().y - player->GetScale().y;
		float playerPosDown = player->GetPos().y;
		float platformPosUp = GetPos().y - GetScale().y * 0.49;
		float platformPosDown = GetPos().y + GetScale().y * 0.49;

		// �Ʒ����� ���� �ö������ �ε���
		if (playerPosUp - platformPosDown > 0.f) {
			playerRigidbody->SetGravityVelocity(Vec2(0.f, 0.f));
			overlapType = OVERLAP_TYPE::IS_COLLISION_UP;
		}
		// ������ �Ʒ��� ���������� �ε���
		else if (playerPosDown - platformPosUp < 0.f) {
			playerRigidbody->SetGround(true); // �ٴ� ���鿡 ���� ��� SetGround(true)
			overlapType = OVERLAP_TYPE::IS_COLLISION_DOWN;
		}
		// ���ʿ��� ���������� �ε���
		else if (player->GetPrevPos().x - player->GetPos().x > 0.f) overlapType = OVERLAP_TYPE::IS_COLLISION_LEFT;
		// �����ʿ��� �������� �ε���
		else if (player->GetPrevPos().x - player->GetPos().x < 0.f) overlapType = OVERLAP_TYPE::IS_COLLISION_RIGHT;
	}
}

void CPlatform::Overlap(CCollider* ownCollider, CObj* otherObj, CCollider* otherCollider)
{
	CPlayer* player = dynamic_cast<CPlayer*>(otherObj);
	if (player)
	{
		player->SetCollisionType(overlapType, true);
	}
}

void CPlatform::EndOverlap(CCollider* ownCollider, CObj* otherObj, CCollider* otherCollider)
{
	CPlayer* player = dynamic_cast<CPlayer*>(otherObj);
	if (player)
	{
		CRigidBody* playerRigidbody = player->GetComponent<CRigidBody>();
		if (overlapType == OVERLAP_TYPE::IS_COLLISION_DOWN)
			playerRigidbody->SetGround(false); // �ٴ� ���鿡 �ִٰ� ������ ��� SetGround(false)

		player->SetCollisionType(overlapType, false);
	}
}