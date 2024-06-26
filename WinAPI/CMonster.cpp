#include "pch.h"
#include "CMonster.h"
#include "CPlayer.h"
#include "CPlatform.h"
#include "MonsterData.h"
#include "CLogMgr.h"


#include "CEngine.h"
#include "CAnimator.h"
#include "CRigidBody.h"

#include "DeathEventStrategy.h"



CMonster::CMonster(int hp, float speed, float range,DeathEventStrategy* deathEvent)
	: collider(nullptr), rigidbody(nullptr), animator(nullptr), deathEvent(deathEvent), isMonsterLeft(false)
{
	monsterData = new MonsterData( hp,speed,range);

	// RigidBody
	rigidbody = AddComponent(new CRigidBody);
	rigidbody->SetMass(1.f);
	rigidbody->SetMaxSpeed(300.f);
	rigidbody->SetFriction(1000.f);
	rigidbody->SetMaxGravitySpeed(1500.f);
}

CMonster::CMonster(const CMonster& _Other)
	: CObj(_Other)
	, monsterData(_Other.monsterData)
	, collider(nullptr)
	, rigidbody(nullptr)
	, animator(nullptr)
	, deathEvent(_Other.deathEvent)
	, isMonsterLeft(_Other.isMonsterLeft)
{

}

CMonster::~CMonster()
{
}

void CMonster::Tick()
{

}

void CMonster::Render()
{
	animator->Render();

	//HDC dc = CEngine::Get()->GetBackDC();

	//Vec2 vPos = GetRenderPos();	
	//UINT width = m_Texture->GetWidth();
	//UINT height = m_Texture->GetHeight();
	//
	//// TransparentBlt
	///*{
	//	TransparentBlt(BackDC, (int)vPos.x - width / 2, (int)vPos.y - height / 2
	//		, width, height, m_Texture->GetDC(), 0, 0, width, height, RGB(255, 0, 255));
	//}*/

	//// AlphaBlending
	//{
	//	BLENDFUNCTION blend = {};
	//	blend.BlendOp = AC_SRC_OVER;
	//	blend.BlendFlags = 0;
	//	blend.SourceConstantAlpha = 255;
	//	blend.AlphaFormat = AC_SRC_ALPHA;
	//			
	//	AlphaBlend(BackDC, (int)vPos.x - width / 2, (int)vPos.y - height / 2
	//			  , width, height, m_Texture->GetDC(), 0, 0, width, height, blend);
	//}
}

void CMonster::BeginOverlap(CCollider* ownCollider, CObj* otherObj, CCollider* _OtherCollider)
{
	CPlayer* player = dynamic_cast<CPlayer*>(otherObj);
	if (player) {
		int playerPos = player->GetPrevPos().y;
		int monsterPos = GetPos().y - GetScale().y + 1.0f;

		if (playerPos <= monsterPos) 
			deathEvent->OnDeath(*this);
		else {
			//player->Dead(); // ���͸� ������ ���� ������ �÷��̾� ���
			LOG(LOG_LEVEL::LOG, L"�÷��̾� ���");
		}
	}

	// ���⼭�� �⺻������ ��� ���͵��� �� ���� �ö󼭰ų� ���� �ε���
	CPlatform* platform = dynamic_cast<CPlatform*>(otherObj);
	if (platform)
	{
		float platformPosUp = platform->GetPos().y - platform->GetScale().y * 0.45;
		float platformPosDown = platform->GetPos().y + platform->GetScale().y * 0.45;
		float posUp = GetPos().y - GetScale().y;
		float posDown = GetPos().y;

		// �Ʒ����� ���� �ö������ �ε���
		if (posUp - platformPosDown > 0.f)
			rigidbody->SetGravityVelocity(Vec2(0.f, 0.f));
		// ������ �Ʒ��� ���������� �ε���
		else if (posDown - platformPosUp <= 0.f)
			rigidbody->SetGround(true); // �ٴ� ���鿡 ���� ��� SetGround(true)
	}
}

void CMonster::Overlap(CCollider* ownCollider, CObj* otherObj, CCollider* _OtherCollider)
{
	if (otherObj->GetLayerType() == (int)LAYER_TYPE::PLATFORM)
	{
		rigidbody->SetGround(true);
	}
}

void CMonster::EndOverlap(CCollider* ownCollider, CObj* otherObj, CCollider* _OtherCollider)
{
	CPlatform* platform = dynamic_cast<CPlatform*>(otherObj);
	if (platform)
	{
		rigidbody->SetGround(false); // �ٴ� ���鿡 �ִٰ� ������ ��� SetGround(false)
	}
}
