#include "pch.h"
#include "CPlayer.h"

#include "CDebugMgr.h"

#include "CTimeMgr.h"
#include "CLevelMgr.h"
#include "CLevel.h"
#include "CMissile.h"
#include "CGuidedMissile.h"

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
	: m_Speed(300.f)
	, m_Texture(nullptr)
	, m_Body(nullptr)
	, m_Animator(nullptr)
	, m_RigidBody(nullptr)
	, isCollisionUp(false)
	, isCollisionDown(false)
	, isCollisionLeft(false)
	, isCollisionRight(false)
{
	// 컴포넌트 설정
	m_Body = AddComponent(new CCollider);
	m_Body->SetName(L"Body Collider");
	m_Body->SetOffset(Vec2(0.f, -32.f));
	m_Body->SetScale(Vec2(60.f, 64.f));

	// RigidBody
	m_RigidBody = AddComponent(new CRigidBody);
	m_RigidBody->SetMode(RIGIDBODY_MODE::PLATFOMER);
	m_RigidBody->SetMass(1.f);
	m_RigidBody->SetMaxSpeed(300.f);
	m_RigidBody->SetFriction(1000.f);
	m_RigidBody->SetMaxGravitySpeed(1500.f);
	m_RigidBody->SetJumpSpeed(600.f);

	// Player 에 Animator 컴포넌트 추가
	m_Animator = AddComponent(new CAnimator);

	//tAnimDesc desc = {};
	//desc.AnimName = L"RUN_RIGHT";
	//desc.FPS = 20;
	//desc.FrmCount = 11;
	//desc.pAtlas = CAssetMgr::Get()->LoadTexture(L"VirtualGuy_RUN_RIGHT", L"texture\\Run.png");
	//desc.SliceSize = Vec2(64.f, 64.f);
	//desc.StartLeftTop = Vec2(0.f, 0.f);	
	//desc.animOffset = Vec2(0.f, -32.f);
	//m_Animator->CreateAnimation(desc);
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
	//m_Animator->SaveAnimation(L"animation\\Player\\");

	m_Animator->LoadAnimation(L"animation\\Player\\IDLE_RIGHT.anim");
	m_Animator->LoadAnimation(L"animation\\Player\\IDLE_LEFT.anim");
	m_Animator->LoadAnimation(L"animation\\Player\\RUN_LEFT.anim");
	m_Animator->LoadAnimation(L"animation\\Player\\RUN_RIGHT.anim");

	// Animation 플레이
	m_Animator->Play(L"IDLE_RIGHT", true);

	// 스테이트머신
	stateMachine = AddComponent(new CPlayerStateMachine);

	// 카메라
	mainCam = CCamera::Get();
}

CPlayer::CPlayer(const CPlayer& _Other)
	: CObj(_Other)
	, m_Body(nullptr)
	, m_Animator(nullptr)
	, m_RigidBody(nullptr)
{
	m_Body = (CCollider*)GetComponentByName(L"Body Collider");
	m_Animator = GetComponent<CAnimator>();
	m_RigidBody = GetComponent<CRigidBody>();
}

CPlayer::~CPlayer()
{
	
}

void CPlayer::Tick()
{
	float fDT = CTimeMgr::Get()->GetDeltaTime();
	Vec2 pos = GetPos();
	prevPos = pos;


	if (KEY_TAP(KEY::A))
		m_Animator->Play(L"RUN_LEFT", true);
	if (KEY_RELEASED(KEY::A))
		m_Animator->Play(L"IDLE_LEFT", true);
	if (KEY_PRESSED(KEY::A) && !isCollisionLeft)
		pos.x -= m_Speed * DT;

	if (KEY_TAP(KEY::D))
		m_Animator->Play(L"RUN_RIGHT", true);
	if (KEY_RELEASED(KEY::D))
		m_Animator->Play(L"IDLE_RIGHT", true);
	if (KEY_PRESSED(KEY::D) && !isCollisionRight)
		pos.x += m_Speed * DT;

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
		m_RigidBody->Jump();
	}

	SetPos(pos);

	mainCam->SetLookAt(pos);
}

void CPlayer::Render()
{
	m_Animator->Render();
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