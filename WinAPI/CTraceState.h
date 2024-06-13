#pragma once

#include "CState.h"

class CTraceState
	: public CState
{
private:
    Vec2    m_InitPos;
        
    bool    m_Return;

public:
    virtual void Enter() override;
    virtual void FinalTick() override;
    virtual void Exit() override;

public:
    CLONE(CTraceState);
    CTraceState();
    ~CTraceState();
};

