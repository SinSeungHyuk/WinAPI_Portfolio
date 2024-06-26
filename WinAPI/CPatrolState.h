#pragma once
#include "CState.h"

class CMonster;
class MonsterData;

class CPatrolState :
    public CState
{
private:
    CMonster* monster;

    Vec2 pos;
    MonsterData* data;

public:
    virtual void Enter() override;
    virtual void FinalTick() override;
    virtual void Exit() override;

    CLONE(CPatrolState);
    CPatrolState();
    ~CPatrolState();
};

