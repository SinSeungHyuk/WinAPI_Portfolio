#pragma once
#include "CStateMachine.h"

class CPlayerStateMachine :
    public CStateMachine
{
public:
    CPlayerStateMachine();
    ~CPlayerStateMachine();

    virtual void AddStates() override;

    CLONE(CPlayerStateMachine);
};

