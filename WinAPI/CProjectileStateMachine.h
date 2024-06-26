#pragma once
#include "CStateMachine.h"
class CProjectileStateMachine :
    public CStateMachine
{
public:
    CProjectileStateMachine();
    ~CProjectileStateMachine();

    virtual void AddStates() override;

    CLONE(CProjectileStateMachine);
};

