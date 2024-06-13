#pragma once
#include "CState.h"


class CAttackState :
    public CState
{

public:
    virtual void Enter() override;
    virtual void FinalTick() override;
    virtual void Exit() override;

public:
    CLONE(CAttackState);
    CAttackState();
    ~CAttackState();
};

