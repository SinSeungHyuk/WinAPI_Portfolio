#include "pch.h"
#include "CPlatform.h"

#include "CPlayer.h"
#include "CCollider.h"
#include "CRigidBody.h"
#include "CTexture.h"
#include "CAssetMgr.h"
#include "CLevelMgr.h"
#include "CEngine.h"

CPlatform::CPlatform()
	: collider(nullptr), texture(nullptr)
{
	collider = AddComponent(new CCollider);
}

CPlatform::CPlatform(const CPlatform& _Other)
	: CObj(_Other)
	, collider(nullptr), texture(nullptr)
{
	collider = GetComponent<CCollider>();
	texture = GetComponent<CTexture>();
}

CPlatform::~CPlatform()
{

}

void CPlatform::SetScale(Vec2 _Scale)
{
	CObj::SetScale(_Scale);

	if (collider)
	{
		collider->SetScale(_Scale);
	}
}

void CPlatform::SetScale(float _Width, float _Height)
{
	CObj::SetScale(_Width, _Height);

	if (collider)
	{
		collider->SetScale(Vec2(_Width, _Height));
	}
}

void CPlatform::Tick()
{

}

void CPlatform::BeginOverlap(CCollider* ownCollider, CObj* otherObj, CCollider* otherCollider)
{
	CPlayer* player = dynamic_cast<CPlayer*>(otherObj);

	if (collider->GetTrigger() && player) {

		return;
	}

	if (player)
	{
		CRigidBody* playerRigidbody = player->GetComponent<CRigidBody>();

 		float playerPosUp = player->GetPos().y - player->GetScale().y;
		float playerPosDown = player->GetPos().y;
		float platformPosUp = GetPos().y - GetScale().y * 0.45;
		float platformPosDown = GetPos().y + GetScale().y * 0.45;

		// ¾Æ·¡¿¡¼­ À§·Î ¿Ã¶ó¿ÔÀ»¶§ ºÎµúÈû
		if (playerPosUp - platformPosDown > 0.f) {
			playerRigidbody->SetGravityVelocity(Vec2(0.f, 0.f));
			overlapType = OVERLAP_TYPE::IS_COLLISION_UP;
		}
		// À§¿¡¼­ ¾Æ·¡·Î ³»·Á¿ÔÀ»¶§ ºÎµúÈû
		else if (playerPosDown - platformPosUp < 0.f) {
			playerRigidbody->SetGround(true); // ¹Ù´Ú À­¸é¿¡ ÀÖÀ» °æ¿ì SetGround(true)
			overlapType = OVERLAP_TYPE::IS_COLLISION_DOWN;
		}
		// ¿ÞÂÊ¿¡¼­ ¿À¸¥ÂÊÀ¸·Î ºÎµúÈû
		else if (player->GetPrevPos().x - player->GetPos().x > 0.f) overlapType = OVERLAP_TYPE::IS_COLLISION_LEFT;
		// ¿À¸¥ÂÊ¿¡¼­ ¿ÞÂÊÀ¸·Î ºÎµúÈû
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
			playerRigidbody->SetGround(false); // ¹Ù´Ú À­¸é¿¡ ÀÖ´Ù°¡ ¶³¾îÁú °æ¿ì SetGround(false)

		player->SetCollisionType(overlapType, false);
	}
}