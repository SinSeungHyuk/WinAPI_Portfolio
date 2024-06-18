#pragma once
#include "CState.h"
class CPlayerMoveState :
    public CState
{
private:
    float timer = 0.f;

public:
    virtual void Enter() override;
    virtual void FinalTick() override;
    virtual void Exit() override;

public:
    CLONE(CPlayerMoveState);
    CPlayerMoveState();
    ~CPlayerMoveState();
};

