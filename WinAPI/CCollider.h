#pragma once
#include "CComponent.h"

enum COLLIDER_STATE
{
    ACTIVE,
    SEMIDEACTIVE,
    DEACTIVE,
};

class CCollider :
    public CComponent
{
private:
    Vec2            m_OffsetPos;
    Vec2            m_FinalPos;
    Vec2            m_Scale;
    bool            isTrigger;
    int             m_OverlapCount;

    COLLIDER_STATE  m_State;

public:
    void SetOffset(Vec2 _Offset) { m_OffsetPos = _Offset; }
    void SetScale(Vec2 _Scale) { m_Scale = _Scale; }

    Vec2 GetFinalPos() { return m_FinalPos; }
    Vec2 GetScale() { return m_Scale; }

    void SetTrigger(bool isTrigger) { this->isTrigger = isTrigger; }
    bool GetTrigger() { return isTrigger; }

    COLLIDER_STATE GetState() { return m_State; }
    bool IsActive() { return m_State == ACTIVE; }

    // 충돌체 화성화
    void Activate();

    // 충돌체 비활성화
    void Deactivate();    



public:
    virtual void FinalTick() override;

    void BeginOverlap(CCollider* _Other);
    void Overlap(CCollider* _Other);
    void EndOverlap(CCollider* _Other);

    //void OnTriggerEnter(CCollider* _Other);
    //void OnTriggerStay(CCollider* _Other);
    //void OnTriggerExit(CCollider* _Other);

public:
    CLONE(CCollider);
    CCollider();
    CCollider(const CCollider& _Other);
    ~CCollider();
};

