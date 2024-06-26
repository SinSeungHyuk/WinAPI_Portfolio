#pragma once
#include "CObj.h"

class CTexture;
class CCollider;

class CItem :
    public CObj
{
protected:
    CTexture* texture;
    CCollider* collider;

public:
    void SetTexture(CTexture* texture) { this->texture = texture; }

    virtual void Tick() override;
    virtual void Render() override;
    virtual void BeginOverlap(CCollider* ownCollider, CObj* otherObj, CCollider* otherCollider);

    virtual void GetItem() = 0;

    virtual CItem* Clone() = 0;
    CItem();
    ~CItem();
};

