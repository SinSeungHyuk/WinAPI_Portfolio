#include "pch.h"
#include "CProjectileMonster.h"

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
#include "CProjectileStateMachine.h"

#include "CPlatform.h"

CProjectileMonster::CProjectileMonster(int hp, float speed, float range, DeathEventStrategy* deathEvent)
	: CMonster(hp, speed, range, deathEvent)
{
	LoadAnimations();

	collider = AddComponent(new CCollider);
	collider->SetName(L"Body Collider");
	collider->SetOffset(Vec2(0.f, -32.f));
	collider->SetScale(Vec2(60.f, 64.f));

	// 스테이트머신
	stateMachine = AddComponent(new CProjectileStateMachine);
	stateMachine->SetLayer();
}

CProjectileMonster::CProjectileMonster(const CProjectileMonster& other)
	: CMonster(other)
{
	collider = (CCollider*)GetComponentByName(L"Body Collider");
	animator = GetComponent<CAnimator>();
	rigidbody = GetComponent<CRigidBody>();
}

CProjectileMonster::~CProjectileMonster()
{
}

void CProjectileMonster::Tick()
{
	if (animator->IsFinish()) {
		Destroy(this);
	}
}

void CProjectileMonster::DetectPlayer(bool isDetected)
{
	if (!isDetected) stateMachine->ChangeState(L"PatrolState", (int)StateMachineLayer::MovementLayer);

	else stateMachine->ChangeState(L"ProjectileState", (int)StateMachineLayer::MovementLayer);
}

void CProjectileMonster::LoadAnimations()
{
	animator = AddComponent(new CAnimator);

	animator->LoadAnimation(L"animation\\Monster\\Trunk_Hit.anim");
	animator->LoadAnimation(L"animation\\Monster\\Trunk_Hit_Left.anim");
	animator->LoadAnimation(L"animation\\Monster\\Trunk_Run.anim");
	animator->LoadAnimation(L"animation\\Monster\\Trunk_Run_Left.anim");
	animator->LoadAnimation(L"animation\\Monster\\Trunk_Attack_Left.anim");
	animator->LoadAnimation(L"animation\\Monster\\Trunk_Attack.anim");

	// Animation 플레이
	animator->Play(L"Trunk_Run", true);
}

void CProjectileMonster::PlayAnimation(ANIMATION_TYPE type)
{
	if (type == ANIMATION_TYPE::DEAD) {
		if (isMonsterLeft) {
			animator->Play(L"Trunk_Hit_Left", false);
		}
		else
			animator->Play(L"Trunk_Hit", false);
		return;
	}

	if (type == ANIMATION_TYPE::ATTACK) {
		if (!isPlayerLeft) {
			animator->Play(L"Trunk_Attack_Left", true);
		}
		else
			animator->Play(L"Trunk_Attack", true);
		return;
	}

	if (isMonsterLeft)
		animator->Play(L"Trunk_Run_Left", true);
	else if (!isMonsterLeft)
		animator->Play(L"Trunk_Run", true);
}

void CProjectileMonster::BeginOverlap(CCollider* ownCollider, CObj* otherObj, CCollider* otherCollider)
{
	CMonster::BeginOverlap(ownCollider, otherObj, otherCollider);

	if (otherObj->GetLayerType() == (int)LAYER_TYPE::PLATFORM)
	{
		isMonsterLeft = !isMonsterLeft;
		PlayAnimation(ANIMATION_TYPE::MOVEMENT);
	}
}
