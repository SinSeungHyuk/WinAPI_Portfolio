#pragma once
#include "CObj.h"

class CTexture;

class CMissile :
    public CObj
{
private:
    Vec2    velocity;
    float   mass;
    float   speed;

    CTexture* texture;

public:
    void SetVelocity(Vec2 _vDir, float _Speed)
    {
        velocity = _vDir;
        speed = _Speed;
        velocity.Normalize();
    }
    Vec2 GetVelocity() { return velocity; }
    float GetMass() { return mass; }

    void SetTexture(CTexture* _tex) { texture = _tex; }

    virtual void Tick() override;
    virtual void Render() override;
    virtual void BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider);

    CLONE(CMissile);
    CMissile();
    ~CMissile();
};

