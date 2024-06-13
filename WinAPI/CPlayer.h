#pragma once
#include "CObj.h"

class CTexture;
class CCollider;
class CAnimator;
class CRigidBody;

class CPlayer :
    public CObj
{
private:
    CTexture*   m_Texture;
    float       m_Speed;

    CCollider*  m_Body;
    CCollider*  m_Face;
    CAnimator*  m_Animator;
    CRigidBody* m_RigidBody;

public:
    virtual void Tick() override;
    virtual void Render() override;


public:
    virtual void BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider);

public:
    CLONE(CPlayer);
    CPlayer();
    CPlayer(const CPlayer& _Other);
    ~CPlayer();
};

