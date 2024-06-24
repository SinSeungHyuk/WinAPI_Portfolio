#pragma once
#include "CStateMachine.h"

enum PlayerLayer {
    MovementLayer,
    AttackLayer,
};

class CPlayerStateMachine :
    public CStateMachine
{
public:
    CPlayerStateMachine();
    ~CPlayerStateMachine();

    virtual void AddStates() override;

    CLONE(CPlayerStateMachine);
};

