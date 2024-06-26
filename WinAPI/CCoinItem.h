#pragma once
#include "CItem.h"

class CAnimator;

class CCoinItem :
    public CItem
{
private:
    CAnimator* animator;

public:
    virtual void Tick() override;
    virtual void Render() override;

    virtual void GetItem() override;

    CLONE(CCoinItem);
    CCoinItem();
    ~CCoinItem();
};

