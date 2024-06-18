#pragma once
#include "CObj.h"

class CTexture;
class CCollider;
class CAnimator;
class CRigidBody;
class CPlayerStateMachine;

class CPlayer :
    public CObj
{
private:
    CTexture*   m_Texture;
    float       m_Speed;

    CCamera* mainCam;

    CCollider*  m_Body;
    CAnimator*  m_Animator;
    CRigidBody* m_RigidBody;
    CPlayerStateMachine* stateMachine;

    Vec2 prevPos;
    bool isCollisionUp;
    bool isCollisionDown;
    bool isCollisionLeft;
    bool isCollisionRight;

public:
    virtual void Tick() override;    
    virtual void Render() override;

    Vec2 GetPrevPos() { return prevPos; }
    void SetCollisionType(OVERLAP_TYPE type, bool isCollision);

public:
    virtual void BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider);
    virtual void Overlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider);
    virtual void EndOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider);

public:
    CLONE(CPlayer);
    CPlayer();
    CPlayer(const CPlayer& _Other);
    ~CPlayer();
};

