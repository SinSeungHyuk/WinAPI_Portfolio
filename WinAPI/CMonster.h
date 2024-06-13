#pragma once
#include "CObj.h"

class CCollider;

class CMonster :
    public CObj
{
private:
    tMonsterInfo    m_Info;

    CTexture*       m_Texture;
    CCollider*      m_Collider;
    int             m_HP;

public:
    void SetTexture(CTexture* _tex) {  m_Texture = _tex; }
    const tMonsterInfo& GetMonsterInfo() { return m_Info; }

public:
    virtual void Tick() override;
    virtual void Render() override;
    virtual void BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider);

public:
    CLONE(CMonster);
    CMonster();
    CMonster(const CMonster& _Other);
    ~CMonster();
};

