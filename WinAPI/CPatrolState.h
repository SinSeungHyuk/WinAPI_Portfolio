#pragma once
#include "CState.h"

class CMonster;

class CPatrolState :
    public CState
{
private:
    CMonster* monster;

public:
    virtual void Enter() override;
    virtual void FinalTick() override;
    virtual void Exit() override;

    CLONE(CPatrolState);
    CPatrolState();
    ~CPatrolState();
};

