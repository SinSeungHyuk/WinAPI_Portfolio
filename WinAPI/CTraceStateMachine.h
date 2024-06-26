#pragma once
#include "CStateMachine.h"

class CTraceStateMachine :
    public CStateMachine
{
public:
    CTraceStateMachine();
    ~CTraceStateMachine();

    virtual void AddStates() override;

    CLONE(CTraceStateMachine);
};

