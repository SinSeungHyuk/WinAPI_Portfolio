#include "pch.h"
#include "CPatrolMonster.h"

#include "CAssetMgr.h"
#include "CCollider.h"
#include "CTimeMgr.h"
#include "CTaskMgr.h"
#include "CPathMgr.h"
#include "CAssetMgr.h"
#include "CCollider.h"
#include "CRigidBody.h"
#include "CAnim.h"
#include "MonsterData.h"
#include "CPatrolStateMachine.h"

#include "CPlatform.h"


CPatrolMonster::CPatrolMonster(int hp, float speed, float range, DeathEventStrategy* deathEvent)
	: CMonster(hp, speed, range, deathEvent)
{
	LoadAnimations();

	collider = AddComponent(new CCollider);
	collider->SetName(L"Body Collider");
	collider->SetOffset(Vec2(0.f, -32.f));
	collider->SetScale(Vec2(60.f, 64.f));



	//rigidbody->SetGround(true);

	// 스테이트머신
	stateMachine = AddComponent(new CPatrolStateMachine);
	stateMachine->SetLayer();
}

CPatrolMonster::CPatrolMonster(const CPatrolMonster& other)
	: CMonster(other)
{
	collider = (CCollider*)GetComponentByName(L"Body Collider");
	animator = GetComponent<CAnimator>();
	rigidbody = GetComponent<CRigidBody>();
}

CPatrolMonster::~CPatrolMonster()
{
}

void CPatrolMonster::Tick()
{
	Vec2 pos = GetPos();
	MonsterData* data = GetMonsterData();

	if (!isMonsterLeft) 
		pos.x += data->GetSpeed() * DT;
	else 
		pos.x -= data->GetSpeed() * DT;

	SetPos(pos);
}

void CPatrolMonster::LoadAnimations()
{
	animator = AddComponent(new CAnimator);
										 
	animator->LoadAnimation(L"animation\\Monster\\PINK_IDLE_RIGHT.anim");
	animator->LoadAnimation(L"animation\\Monster\\PINK_IDLE_LEFT.anim");
	animator->LoadAnimation(L"animation\\Monster\\PINK_RUN_LEFT.anim");
	animator->LoadAnimation(L"animation\\Monster\\PINK_RUN_RIGHT.anim");

	// Animation 플레이
	animator->Play(L"PINK_IDLE_RIGHT", true);

}

void CPatrolMonster::PlayAnimation(ANIMATION_TYPE type)
{
	if (isMonsterLeft) {
		animator->Play(L"PINK_RUN_LEFT", true);
	}
	else 
		animator->Play(L"PINK_RUN_RIGHT", true);
}

void CPatrolMonster::BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider)
{
	CMonster::BeginOverlap(_OwnCollider, _OtherObj, _OtherCollider);

	if (_OtherObj->GetLayerType() == (int)LAYER_TYPE::PLATFORM)
	{
		isMonsterLeft = !isMonsterLeft;
		PlayAnimation(ANIMATION_TYPE::MOVEMENT);
	}
}


