#pragma once
#include "CState.h"

class CPlayer;
class CProjectileMonster;
class MonsterData;

class CProjectileState :
    public CState
{
private:
    CPlayer* player;
    CProjectileMonster* monster;

    Vec2 pos;
    Vec2 playerPos;
    MonsterData* data;

    float timer;

public:
    virtual void Enter() override;
    virtual void FinalTick() override;
    virtual void Exit() override;

    CLONE(CProjectileState);
    CProjectileState();
    ~CProjectileState();
};



