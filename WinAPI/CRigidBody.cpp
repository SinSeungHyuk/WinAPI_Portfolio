#include "pch.h"
#include "CRigidBody.h"

#include "CEngine.h"
#include "CTimeMgr.h"

CRigidBody::CRigidBody()
	: CComponent(COMPONENT_TYPE::RIGIDBODY)
	, m_MaxSpeed(0.f)
	, m_IsMove(false)
	, m_Friction(0.f)
	, m_UseGravity(true)
	, m_GravityAccel(1500.f)
	, m_GravityMaxSpeed(0.f)
	, m_JumpSpeed(300.f)
	, m_IsGound(false)
	, m_Mass(0.f)
{
}

CRigidBody::CRigidBody(const CRigidBody& _Other)
	: CComponent(_Other)
	, m_Mass(_Other.m_Mass)
	, m_Friction(_Other.m_Friction)
	, m_MaxSpeed(_Other.m_MaxSpeed)
    , m_GravityAccel(_Other.m_GravityAccel)
    , m_GravityMaxSpeed(_Other.m_GravityMaxSpeed)
    , m_JumpSpeed(_Other.m_JumpSpeed)
    , m_IsMove(false)
    , m_IsGound(false)
    , m_UseGravity(_Other.m_UseGravity)
{
}

CRigidBody::~CRigidBody()
{
}


void CRigidBody::FinalTick()
{
	// 가속도 구하기
	// F == M x A
	// F / M == A
	Vec2 Accel = m_Force / m_Mass;

	// 가속도 방향으로 가속도의 크기만큼 속도가 증가함
	m_Velocity += Accel * DT;

	// 최대속력 체크, 0.f == m_MaxSpeed ==> 속력 제한이 없다
	if (0.f != m_MaxSpeed)
	{
		if (m_MaxSpeed < m_Velocity.Length())
		{
			m_Velocity.Normalize();
			m_Velocity *= m_MaxSpeed;
		}		
	}

	// 주어진 힘이 없다면, 반대방향으로 마찰력을 준다.
	if (m_Force == Vec2(0.f, 0.f) && m_Velocity != Vec2(0.f, 0.f))
	{
		Vec2 vFriction = -m_Velocity;
		vFriction.Normalize();
		vFriction *= m_Friction * m_Mass;
		vFriction *= DT;

		if (m_Velocity.Length() < vFriction.Length())
		{
			m_Velocity = Vec2(0.f, 0.f);
		}
		else
		{
			m_Velocity += vFriction;
		}
	}


	Vec2 vFinalVelocity = m_Velocity;
	// 중력기능 On
	if (m_UseGravity && !m_IsGound)
	{
		m_GravityVelocity += Vec2(0.f, 1.f) * m_GravityAccel * DT;
		if (m_GravityMaxSpeed < m_GravityVelocity.Length())
		{
			m_GravityVelocity.Normalize();
			m_GravityVelocity *= m_GravityMaxSpeed;
		}

		vFinalVelocity += m_GravityVelocity;
	}
	// 중력기능 Off
	else
	{
		m_GravityVelocity = Vec2(0.f, 0.f);
	}		


	// 속도에 따른 물체의 이동 발생
	Vec2 vObjPos = GetOwner()->GetPos();	
	GetOwner()->SetPos(vObjPos + vFinalVelocity * DT);

	// 오브젝트의 움직임 체크
	if (vObjPos == GetOwner()->GetPos())
		m_IsMove = false;
	else
		m_IsMove = true;

	// 이번에 받은 힘을 0 으로 초기화
	m_Force = Vec2(0.f, 0.f);

	// 속도의 방향을 시각화
	DrawDebugLine(PEN_TYPE::YELLOW, GetOwner()->GetRenderPos(), GetOwner()->GetRenderPos() + m_Velocity / 2.f, 0.f);
}


void CRigidBody::SetGround(bool _Ground)
{
	m_IsGound = _Ground;

	if (m_IsGound)
	{
		m_GravityVelocity = Vec2(0.f, 0.f);
	}
}

void CRigidBody::Jump()
{	
	m_GravityVelocity += (Vec2(0.f, -1.f) * m_JumpSpeed);
	m_IsGound = false;
}