#pragma once
#include "CObj.h"

class CCollider; 
class CTexture;


class CPlatform :
    public CObj
{
private:
    CCollider*  m_Collider;
    CTexture* texture;

    OVERLAP_TYPE overlapType;

public:
    virtual void SetScale(Vec2 _Scale) override;
    virtual void SetScale(float _Width, float _Height) override;

    virtual void Tick() override;
    virtual void Render() override {}
    virtual void BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider) override;
    virtual void Overlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider) override;
    virtual void EndOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider) override;

public:
    CLONE(CPlatform);
    CPlatform();
    CPlatform(const CPlatform& _Other);
    ~CPlatform();
};

