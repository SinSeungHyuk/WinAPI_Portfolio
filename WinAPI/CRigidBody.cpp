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
	// ���ӵ� ���ϱ�
	// F == M x A
	// F / M == A
	Vec2 Accel = m_Force / m_Mass;

	// ���ӵ� �������� ���ӵ��� ũ�⸸ŭ �ӵ��� ������
	m_Velocity += Accel * DT;

	// �ִ�ӷ� üũ, 0.f == m_MaxSpeed ==> �ӷ� ������ ����
	if (0.f != m_MaxSpeed)
	{
		if (m_MaxSpeed < m_Velocity.Length())
		{
			m_Velocity.Normalize();
			m_Velocity *= m_MaxSpeed;
		}		
	}

	// �־��� ���� ���ٸ�, �ݴ�������� �������� �ش�.
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
	// �߷±�� On
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
	// �߷±�� Off
	else
	{
		m_GravityVelocity = Vec2(0.f, 0.f);
	}		


	// �ӵ��� ���� ��ü�� �̵� �߻�
	Vec2 vObjPos = GetOwner()->GetPos();	
	GetOwner()->SetPos(vObjPos + vFinalVelocity * DT);

	// ������Ʈ�� ������ üũ
	if (vObjPos == GetOwner()->GetPos())
		m_IsMove = false;
	else
		m_IsMove = true;

	// �̹��� ���� ���� 0 ���� �ʱ�ȭ
	m_Force = Vec2(0.f, 0.f);

	// �ӵ��� ������ �ð�ȭ
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