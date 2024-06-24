#pragma once
#include "CState.h"

class CPlayer;

class CPlayerIdleState :
    public CState
{
private:
    CPlayer* player;

public:
    virtual void Enter() override;
    virtual void FinalTick() override;
    virtual void Exit() override;

    CLONE(CPlayerIdleState);
    CPlayerIdleState();
    ~CPlayerIdleState();
};

