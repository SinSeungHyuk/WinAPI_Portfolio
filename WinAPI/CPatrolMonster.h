#pragma once
#include "CMonster.h"

class CStateMachine;

class CPatrolMonster :
    public CMonster
{
private:
    CStateMachine* stateMachine;

public:
    CLONE(CPatrolMonster);
    CPatrolMonster(int hp, float speed, float range, DeathEventStrategy* deathEvent);
    CPatrolMonster(const CPatrolMonster& other);
    ~CPatrolMonster();

private:
    virtual void Tick() override;

    void LoadAnimations() override;
    void PlayAnimation(ANIMATION_TYPE type) override;
    virtual void BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider);


};

