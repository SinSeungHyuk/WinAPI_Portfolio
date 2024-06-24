#pragma once
class CMonster;

class DeathEventStrategy
{
public:
    virtual ~DeathEventStrategy() = default;
    virtual void OnDeath(CMonster & monster) = 0;
};

