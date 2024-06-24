#pragma once
#include "CObj.h"

class CTexture;
class CCollider;
class CAnimator;
class CRigidBody;
class CStateMachine;

class CPlayer :
    public CObj
{
private:
    float       speed;

    CCamera* mainCam;

    CCollider*  collider;
    CRigidBody* rigidbody;
    CStateMachine* stateMachine;

    Vec2 prevPos;
    bool isPlayerLeft; // false : right
    bool isCollisionUp;
    bool isCollisionDown;
    bool isCollisionLeft;
    bool isCollisionRight;

public:
    CAnimator* animator;

    virtual void Tick() override;    
    virtual void Render() override;

    Vec2 GetPrevPos() { return prevPos; }
    void SetCollisionType(OVERLAP_TYPE type, bool isCollision);

    bool IsPlayerLeft() { return isPlayerLeft; }

    virtual void BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider);
    virtual void Overlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider);
    virtual void EndOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider);

    void Dead();

public:
    CLONE(CPlayer);
    CPlayer();
    CPlayer(const CPlayer& _Other);
    ~CPlayer();
};

