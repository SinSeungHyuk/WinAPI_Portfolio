#pragma once

#include "CBase.h"
#include "CStateMachine.h"
#include "CLogMgr.h"
#include "CLevelMgr.h"
#include "CLevel.h"
#include "CPlayer.h"
#include "CTimeMgr.h"
#include "CAnimator.h"


class CState :
    public CBase
{
private:
    CStateMachine*      owner;

public:
    CStateMachine* GetStateMachine() { return owner; }

    template<typename T>
    T* GetOwner()
    {        
        T* pObject = dynamic_cast<T*>(owner->GetOwner());
        assert(pObject);
        return pObject;
    }

public:
    virtual void Enter() = 0;
    virtual void FinalTick() = 0;
    virtual void Exit() = 0;

public:
    virtual CState* Clone() = 0;
    CState();
    ~CState();

    friend class CStateMachine;
};

