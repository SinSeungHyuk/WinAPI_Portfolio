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
	if (animator->IsFinish()) {
		Destroy(this);
	}
}

void CPatrolMonster::LoadAnimations()
{
	animator = AddComponent(new CAnimator);

	animator->LoadAnimation(L"animation\\Monster\\Chicken_Hit.anim");
	animator->LoadAnimation(L"animation\\Monster\\Chicken_Hit_Left.anim");
	animator->LoadAnimation(L"animation\\Monster\\Chicken_Run.anim");
	animator->LoadAnimation(L"animation\\Monster\\Chicken_Run_Left.anim");

	// Animation 플레이
	animator->Play(L"Chicken_Run", true);
}

void CPatrolMonster::PlayAnimation(ANIMATION_TYPE type)
{
	if (type == ANIMATION_TYPE::DEAD) {
		if (isMonsterLeft) {
			animator->Play(L"Chicken_Hit_Left", false);
		}
		else 
			animator->Play(L"Chicken_Hit", false);
		return;
	}

	if (isMonsterLeft) {
		animator->Play(L"Chicken_Run_Left", true);
	}
	else 
		animator->Play(L"Chicken_Run", true);


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


