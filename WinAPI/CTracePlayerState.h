#pragma once
#include "CState.h"

class MonsterData;
class CTraceMonster;
class CPlayer;

class CTracePlayerState :
    public CState
{
private:
    CTraceMonster* monster;
    CPlayer* player;

    Vec2 pos;
    Vec2 playerPos;
    MonsterData* data;

public:
    virtual void Enter() override;
    virtual void FinalTick() override;
    virtual void Exit() override;

    CLONE(CTracePlayerState);
    CTracePlayerState();
    ~CTracePlayerState();
};

