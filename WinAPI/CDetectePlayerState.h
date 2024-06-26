#pragma once
#include "CState.h"

class CPlayer;
class CMonster;
class MonsterData;

class CDetectePlayerState :
    public CState
{
private:
    CPlayer* player;
    CMonster* monster;

    Vec2 pos;
    Vec2 playerPos;
    MonsterData* data;

public:
    virtual void Enter() override;
    virtual void FinalTick() override;
    virtual void Exit() override;

    CLONE(CDetectePlayerState);
    CDetectePlayerState();
    ~CDetectePlayerState();
};

