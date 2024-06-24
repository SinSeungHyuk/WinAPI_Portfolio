#pragma once

#include "CComponent.h"


class CRigidBody :
    public CComponent
{
private:
    Vec2                m_Force;            // ���� �� (ũ�� + ����)
    Vec2                m_Velocity;         // �ӵ�    (ũ�� + ����)
    Vec2                m_GravityVelocity;
    float               m_Mass;             // ����
    float               m_Friction;         // �������
    float               m_MaxSpeed;         // �ִ� �ӷ� ����
    float               m_GravityAccel;     // �߷°��ӵ� ũ��
    float               m_GravityMaxSpeed;  // �߷����� ���ؼ� �߻��ϴ� �ӵ��� �ִ� ����ġ
    float               m_JumpSpeed;
    bool                m_IsMove;           // ���� ������Ʈ�� �����̴� ������ �ƴ��� üũ
    bool                m_IsGound;          // �������� ���ִ��� ����
    bool                m_UseGravity;

public:
    void AddForce(Vec2 _Force) { m_Force += _Force; }
    void SetMass(float _Mass) { m_Mass = _Mass; }
    void SetMaxSpeed(float _Max) { m_MaxSpeed = _Max; }
    void SetVelocity(Vec2 _Velocity) { m_Velocity = _Velocity; }
    void AddVelociy(Vec2 _Velocity) { m_Velocity += _Velocity; }
    void SetFriction(float _Friction) { m_Friction = _Friction; }
    void SetGravityAccelScale(float _Accel) { m_GravityAccel = _Accel; }
    void SetMaxGravitySpeed(float _Max) { m_GravityMaxSpeed = _Max; }
    void UseGravity(bool _Use) { m_UseGravity = _Use; }
    void SetJumpSpeed(float _Speed) { m_JumpSpeed = _Speed; }
    void SetGravityVelocity(Vec2 velocity) { m_GravityVelocity = velocity; }

    void SetGround(bool _Ground);

    void Jump();

    Vec2 GetForce() { return m_Force; }
    float GetMass() { return m_Mass; }
    float GetMaxSpeed() { return m_MaxSpeed; }
    bool IsMove() { return m_IsMove; }

public:
    virtual void FinalTick() override;

public:
    CLONE(CRigidBody);
    CRigidBody();
    CRigidBody(const CRigidBody& _Other);
    ~CRigidBody();
};

 