#pragma once
#include "DeathEventStrategy.h"
class ItemDropEvent :
    public DeathEventStrategy
{
public:
    void OnDeath(CMonster& monster) override;
};

