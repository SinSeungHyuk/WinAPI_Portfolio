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
#include "CCamera.h"

#include "CLogMgr.h"

CPlayer::CPlayer()
	: m_Speed(300.f)
	, m_Texture(nullptr)
	, m_Body(nullptr)
	, m_Face(nullptr)
	, m_Animator(nullptr)
	, m_RigidBody(nullptr)
{
	// 컴포넌트 설정
	m_Body = AddComponent(new CCollider);
	m_Body->SetName(L"Body Collider");

	m_Face = AddComponent(new CCollider);
	m_Face->SetName(L"Face Collider");

	m_Body->SetOffset(Vec2(0.f, 20.f));
	m_Body->SetScale(Vec2(50.f, 60.f));

	m_Face->SetOffset(Vec2(0.f, -40.f));
	m_Face->SetScale(Vec2(20.f, 30.f));

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
	//desc.AnimName = L"MOVE_DOWN";
	//desc.FPS = 20;
	//desc.FrmCount = 10;
	//desc.pAtlas = CAssetMgr::Get()->LoadTexture(L"LinkTex", L"texture\\link_32.bmp");
	//desc.SliceSize = Vec2(120.f, 130.f);
	//desc.StartLeftTop = Vec2(0.f, 520.f);	
	//m_Animator->CreateAnimation(desc);

	//desc.AnimName = L"MOVE_LEFT";
	//desc.StartLeftTop = Vec2(0.f, 650.f);
	//m_Animator->CreateAnimation(desc);

	//desc.AnimName = L"MOVE_UP";
	//desc.StartLeftTop = Vec2(0.f, 780.f);
	//m_Animator->CreateAnimation(desc);

	//desc.AnimName = L"MOVE_RIGHT";
	//desc.StartLeftTop = Vec2(0.f, 910.f);
	//m_Animator->CreateAnimation(desc);

	//desc.AnimName = L"IDLE_RIGHT";
	//desc.StartLeftTop = Vec2(0.f, 390.f);
	//desc.FrmCount = 3;
	//desc.FPS = 10;
	//m_Animator->CreateAnimation(desc);

	//CAnim* pIdleRight = m_Animator->FindAnimation(L"IDLE_RIGHT");
	//pIdleRight->GetFrame(1).vOffset = Vec2(1.f, 0.f);

	//desc.AnimName = L"IDLE_LEFT";
	//desc.StartLeftTop = Vec2(0.f, 130.f);
	//desc.FrmCount = 3;
	//desc.FPS = 10;
	//m_Animator->CreateAnimation(desc);

	//desc.AnimName = L"IDLE_UP";
	//desc.StartLeftTop = Vec2(0.f, 260.f);
	//desc.FrmCount = 1;
	//desc.FPS = 1;
	//m_Animator->CreateAnimation(desc);

	//desc.AnimName = L"IDLE_DOWN";
	//desc.StartLeftTop = Vec2(0.f, 0.f);
	//desc.FrmCount = 3;
	//desc.FPS = 10;
	//m_Animator->CreateAnimation(desc);

	//// Animation 정보 저장하기
	//m_Animator->SaveAnimation(L"animation\\Player\\");

	m_Animator->LoadAnimation(L"animation\\Player\\IDLE_DOWN.anim");
	m_Animator->LoadAnimation(L"animation\\Player\\IDLE_LEFT.anim");
	m_Animator->LoadAnimation(L"animation\\Player\\IDLE_RIGHT.anim");
	m_Animator->LoadAnimation(L"animation\\Player\\IDLE_UP.anim");
	m_Animator->LoadAnimation(L"animation\\Player\\MOVE_DOWN.anim");
	m_Animator->LoadAnimation(L"animation\\Player\\MOVE_LEFT.anim");
	m_Animator->LoadAnimation(L"animation\\Player\\MOVE_RIGHT.anim");
	m_Animator->LoadAnimation(L"animation\\Player\\MOVE_UP.anim");

	// Animation 플레이
	m_Animator->Play(L"IDLE_DOWN", true);
}

CPlayer::CPlayer(const CPlayer& _Other)
	: CObj(_Other)
	, m_Body(nullptr)
	, m_Face(nullptr)
	, m_Animator(nullptr)
	, m_RigidBody(nullptr)
{
	m_Body = (CCollider*)GetComponentByName(L"Body Collider");
	m_Face = (CCollider*)GetComponentByName(L"Face Collider");
	m_Animator = GetComponent<CAnimator>();
	m_RigidBody = GetComponent<CRigidBody>();
}

CPlayer::~CPlayer()
{
	
}

void CPlayer::Tick()
{
	float fDT = CTimeMgr::Get()->GetDeltaTime();

	if (KEY_TAP(KEY::LEFT))		
		m_Animator->Play(L"MOVE_LEFT", true);	
	if (KEY_RELEASED(KEY::LEFT))
		m_Animator->Play(L"IDLE_LEFT", true);		
	if (KEY_PRESSED(KEY::LEFT))
	{
		m_RigidBody->AddForce(Vec2(-300.f, 0.f));
		if (!m_RigidBody->IsMove())
		{
			m_RigidBody->SetVelocity(Vec2(-100.f, 0.f));
		}
	}	

	if (KEY_TAP(KEY::RIGHT))
		m_Animator->Play(L"MOVE_RIGHT", true);	
	if (KEY_RELEASED(KEY::RIGHT))
		m_Animator->Play(L"IDLE_RIGHT", true);
	if (KEY_PRESSED(KEY::RIGHT))
	{
		m_RigidBody->AddForce(Vec2(300.f, 0.f));
		if (!m_RigidBody->IsMove())
		{
			m_RigidBody->SetVelocity(Vec2(100.f, 0.f));
		}
	}

	if (KEY_TAP(KEY::UP))
	{		
		m_Animator->Play(L"MOVE_UP", true);
	}
	if (KEY_RELEASED(KEY::UP))
		m_Animator->Play(L"IDLE_UP", true);

	if (KEY_TAP(KEY::DOWN))
	{
		m_Animator->Play(L"MOVE_DOWN", true);
	}
	if (KEY_RELEASED(KEY::DOWN))
		m_Animator->Play(L"IDLE_DOWN", true);
	
	if (KEY_TAP(KEY::SPACE))
	{		
		/*CMissile* pMissile = new CGuidedMissile;
		pMissile->SetName(L"Missile");
		pMissile->SetPos(GetPos().x, GetPos().y - GetScale().y / 2.f);
		pMissile->SetScale(20.f, 20.f);	
		pMissile->SetVelocity(Vec2(0, -1), 500.f);
		CreateObject(pMissile, LAYER_TYPE::PLAYER_PROJECTILE);*/		
		m_RigidBody->Jump();
		//CCamera::Get()->SetFilterEffect(FADE_OUT, 1.f);
		//CCamera::Get()->SetFilterEffect(FADE_IN, 3.f);	
	}
}

void CPlayer::Render()
{
	m_Animator->Render();
}

void CPlayer::BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider)
{
	CCamera::Get()->SetCamShake(100.f, 10.f, 0.1f);

	if (_OwnCollider->GetName() == L"Body Collider")
	{
		int a = 0;
	}

	if (_OwnCollider == m_Body)
	{
		int a = 0;
	}
}