#include "pch.h"
#include "CPlayer.h"

#include "CDebugMgr.h"

#include "CTimeMgr.h"
#include "CLevelMgr.h"
#include "CLevel.h"
#include "CMissile.h"

#include "CKeyMgr.h"
#include "CTaskMgr.h"
#include "CEngine.h"
#include "CPathMgr.h"

#include "CAssetMgr.h"
#include "CTexture.h"

#include "CCollider.h"
#include "CAnimator.h"
#include "CAnim.h"
#include "CRigidBody.h"
#include "CPlayerStateMachine.h"
#include "CCamera.h"

#include "CLogMgr.h"

CPlayer::CPlayer()
	: speed(300.f)
	, collider(nullptr)
	, animator(nullptr)
	, rigidbody(nullptr)
	, isPlayerLeft(false)
	, isCollisionUp(false)
	, isCollisionDown(false)
	, isCollisionLeft(false)
	, isCollisionRight(false)
{
	// 컴포넌트 설정
	collider = AddComponent(new CCollider);
	collider->SetName(L"Body Collider");
	collider->SetOffset(Vec2(0.f, -32.f));
	collider->SetScale(Vec2(60.f, 64.f));

	// RigidBody
	rigidbody = AddComponent(new CRigidBody);
	rigidbody->SetMass(1.f);
	rigidbody->SetMaxSpeed(300.f);
	rigidbody->SetFriction(1000.f);
	rigidbody->SetMaxGravitySpeed(1500.f);
	rigidbody->SetJumpSpeed(600.f);



	// Player 에 Animator 컴포넌트 추가
	animator = AddComponent(new CAnimator);

	//tAnimDesc desc = {};
	//desc.AnimName = L"HIT";
	//desc.FPS = 10;
	//desc.FrmCount = 7;
	//desc.pAtlas = CAssetMgr::Get()->LoadTexture(L"VirtualGuy_HIT", L"texture\\Hit.png");
	//desc.SliceSize = Vec2(32.f, 32.f);
	//desc.StartLeftTop = Vec2(0.f, 0.f);	
	//desc.animOffset = Vec2(0.f, -32.f);
	//animator->CreateAnimation(desc);
	//
	//desc.AnimName = L"RUN_LEFT";
	//desc.pAtlas = CAssetMgr::Get()->LoadTexture(L"VirtualGuy_RUN_LEFT", L"texture\\Run_flip.png");
	//m_Animator->CreateAnimation(desc);
	//
	//desc.AnimName = L"IDLE_LEFT";
	//desc.FrmCount = 10;
	//desc.pAtlas = CAssetMgr::Get()->LoadTexture(L"VirtualGuy_IDLE_LEFT", L"texture\\Idle_flip.png");
	//m_Animator->CreateAnimation(desc);
	//
	//desc.AnimName = L"IDLE_RIGHT";
	//desc.pAtlas = CAssetMgr::Get()->LoadTexture(L"VirtualGuy_IDLE_RIGHT", L"texture\\Idle.png");
	//m_Animator->CreateAnimation(desc);
	//
	//// Animation 정보 저장하기
	//animator->SaveAnimation(L"animation\\Player\\");

	animator->LoadAnimation(L"animation\\Player\\HIT.anim");
	animator->LoadAnimation(L"animation\\Player\\HIT_LEFT.anim");
	animator->LoadAnimation(L"animation\\Player\\IDLE_RIGHT.anim");
	animator->LoadAnimation(L"animation\\Player\\IDLE_LEFT.anim");
	animator->LoadAnimation(L"animation\\Player\\RUN_LEFT.anim");
	animator->LoadAnimation(L"animation\\Player\\RUN_RIGHT.anim");

	// Animation 플레이
	animator->Play(L"IDLE_RIGHT", true);

	// 스테이트머신
	stateMachine = AddComponent(new CPlayerStateMachine);
	stateMachine->SetLayer();

	// 카메라
	mainCam = CCamera::Get();
}

CPlayer::CPlayer(const CPlayer& _Other)
	: CObj(_Other)
	, collider(nullptr)
	, animator(nullptr)
	, rigidbody(nullptr)
{
	collider = (CCollider*)GetComponentByName(L"Body Collider");
	animator = GetComponent<CAnimator>();
	rigidbody = GetComponent<CRigidBody>();
}

CPlayer::~CPlayer()
{
	
}

void CPlayer::Tick()
{
	Vec2 pos = GetPos();
	prevPos = pos;

	if (KEY_RELEASED(KEY::A) || KEY_RELEASED(KEY::D))
		stateMachine->ChangeState(L"IdleState", 0);
	if (KEY_TAP(KEY::A)) {
		isPlayerLeft = true;		
		stateMachine->ChangeState(L"MoveState", 0);
	}
	if (KEY_TAP(KEY::D)) {
		isPlayerLeft = false;
		stateMachine->ChangeState(L"MoveState", 0);
	}

	if (KEY_PRESSED(KEY::A) && !isCollisionLeft)
		pos.x -= speed * DT;
	if (KEY_PRESSED(KEY::D) && !isCollisionRight)
		pos.x += speed * DT;


	//if (KEY_TAP(KEY::W))
	//{
	//	if (m_RigidBody->GetMode() == RIGIDBODY_MODE::PLATFOMER) {
	//		CMissile* pMissile = new CMissile;
	//		pMissile->SetName(L"Missile");
	//		pMissile->SetPos(GetPos().x, GetPos().y - GetScale().y / 2.f);
	//		pMissile->SetScale(20.f, 20.f);
	//		pMissile->SetVelocity(Vec2(0, -1), 500.f);

	//		CreateObject(pMissile, LAYER_TYPE::PLAYER_PROJECTILE);
	//	}
	//}


	if (KEY_TAP(KEY::SPACE))
	{
		rigidbody->Jump();
	}

	SetPos(pos);

	mainCam->SetLookAt(pos);
}

void CPlayer::Render()
{
	animator->Render();
}

void CPlayer::SetCollisionType(OVERLAP_TYPE type, bool isCollision) {
	switch (type)
	{
	case OVERLAP_TYPE::IS_COLLISION_UP:
		isCollisionUp = isCollision;
		break;
	case OVERLAP_TYPE::IS_COLLISION_DOWN:
		isCollisionDown = isCollision;
		break;
	case OVERLAP_TYPE::IS_COLLISION_LEFT:
		isCollisionLeft = isCollision;
		break;
	case OVERLAP_TYPE::IS_COLLISION_RIGHT:
		isCollisionRight = isCollision;
		break;
	default:
		break;
	}
}


void CPlayer::BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider)
{
	if (_OtherObj->GetLayerType() == (int)LAYER_TYPE::PLATFORM)
	{
		int a = GetPos().y;
		int b = _OtherObj->GetPos().y - _OtherObj->GetScale().y * 0.5f;

		int c = 0;
	}
}

void CPlayer::Overlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider)
{
	if (_OtherObj->GetLayerType() == (int)LAYER_TYPE::PLATFORM)
	{

	}
}

void CPlayer::EndOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider)
{
	if (_OtherObj->GetLayerType() == (int)LAYER_TYPE::PLATFORM)
	{

	}
}

void CPlayer::Dead()
{
	DeleteObject(this);
}
