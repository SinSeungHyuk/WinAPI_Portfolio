#pragma once
#include "CStateMachine.h"

class CMonsterStateMachine :
    public CStateMachine
{
public:
    CMonsterStateMachine();
    ~CMonsterStateMachine();

    virtual void AddStates() override;

    CLONE(CMonsterStateMachine);
};

