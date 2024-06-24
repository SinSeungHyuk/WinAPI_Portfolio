#pragma once
#include "CStateMachine.h"
class CPatrolStateMachine :
    public CStateMachine
{
public:
    CPatrolStateMachine();
    ~CPatrolStateMachine();

    virtual void AddStates() override;

    CLONE(CPatrolStateMachine);
};

