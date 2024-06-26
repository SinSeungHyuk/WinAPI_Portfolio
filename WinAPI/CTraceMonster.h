#pragma once
#include "CMonster.h"

class CStateMachine;

class CTraceMonster :
    public CMonster
{
private:
    CStateMachine* stateMachine;
    bool           isTrace; // 추격상태
    bool           isPlayerLeft; // 플레이어가 몬스터 기준 왼쪽에 있는지 확인

public:
    bool IsTrace() { return isTrace; }
    void SetTrace(bool trace) { isTrace = trace; }
    bool IsPlayerLeft() { return isPlayerLeft; }
    void SetPlayerLeft(bool trace) { isPlayerLeft = trace; }

    void PlayTraceAnim(bool isPlayerLeft);
    virtual void DetectPlayer(bool isDetected) override;

    CLONE(CTraceMonster);
    CTraceMonster(int hp, float speed, float range, DeathEventStrategy* deathEvent);
    CTraceMonster(const CTraceMonster& other);
    ~CTraceMonster();

private:
    virtual void Tick() override;

    void LoadAnimations() override;
    void PlayAnimation(ANIMATION_TYPE type) override;
    virtual void BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider);

};
