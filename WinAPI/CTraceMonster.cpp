#include "pch.h"
#include "CTraceMonster.h"

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
#include "CTraceStateMachine.h"

#include "CPlatform.h"


CTraceMonster::CTraceMonster(int hp, float speed, float range, DeathEventStrategy* deathEvent)
	: CMonster(hp, speed, range, deathEvent)
{
	LoadAnimations();

	collider = AddComponent(new CCollider);
	collider->SetName(L"Body Collider");
	collider->SetOffset(Vec2(0.f, -32.f));
	collider->SetScale(Vec2(60.f, 64.f));

	// 스테이트머신
	stateMachine = AddComponent(new CTraceStateMachine);
	stateMachine->SetLayer();
}

CTraceMonster::CTraceMonster(const CTraceMonster& other)
	: CMonster(other)
{
	collider = (CCollider*)GetComponentByName(L"Body Collider");
	animator = GetComponent<CAnimator>();
	rigidbody = GetComponent<CRigidBody>();
}

CTraceMonster::~CTraceMonster()
{
}

void CTraceMonster::Tick()
{
	if (animator->IsFinish()) {
		Destroy(this);
	}


}

void CTraceMonster::LoadAnimations()
{
	animator = AddComponent(new CAnimator);

	animator->LoadAnimation(L"animation\\Monster\\Pig_Hit.anim");
	animator->LoadAnimation(L"animation\\Monster\\Pig_Hit_Left.anim");
	animator->LoadAnimation(L"animation\\Monster\\Pig_Run.anim");
	animator->LoadAnimation(L"animation\\Monster\\Pig_Run_Left.anim");
	animator->LoadAnimation(L"animation\\Monster\\Pig_Walk_Left.anim");
	animator->LoadAnimation(L"animation\\Monster\\Pig_Walk.anim");

	// Animation 플레이
	animator->Play(L"Pig_Walk", true);
}

void CTraceMonster::PlayTraceAnim(bool _isPlayerLeft)
{
	if (_isPlayerLeft != isPlayerLeft) {
		PlayAnimation(ANIMATION_TYPE::MOVEMENT);
		isPlayerLeft = !isPlayerLeft;
	}
}

void CTraceMonster::DetectPlayer(bool isDetected)
{
	if (!isDetected) return;

	stateMachine->ChangeState(L"TracePlayerState", (int)StateMachineLayer::MovementLayer);
}

void CTraceMonster::PlayAnimation(ANIMATION_TYPE type)
{
	if (type == ANIMATION_TYPE::DEAD) {
		if (isMonsterLeft) {
			animator->Play(L"Pig_Hit_Left", false);
		}
		else
			animator->Play(L"Pig_Hit", false);
		return;
	}

	if (isMonsterLeft && !isTrace) 
		animator->Play(L"Pig_Walk_Left", true);	
	else if (!isMonsterLeft && !isTrace)
		animator->Play(L"Pig_Walk", true);

	if (isTrace && isPlayerLeft) 
		animator->Play(L"Pig_Run_Left", true);
	else if (isTrace && !isPlayerLeft)
		animator->Play(L"Pig_Run", true);
}

void CTraceMonster::BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider)
{
	CMonster::BeginOverlap(_OwnCollider, _OtherObj, _OtherCollider);

	if (_OtherObj->GetLayerType() == (int)LAYER_TYPE::PLATFORM && !isTrace)
	{
		isMonsterLeft = !isMonsterLeft;
		PlayAnimation(ANIMATION_TYPE::MOVEMENT);
	}
}


