#pragma once
#include "CItem.h"

class CAnimator;

class CGemItem:
    public CItem
{
private:
    CAnimator* animator;

public:
    virtual void Tick() override;
    virtual void Render() override;

    virtual void GetItem() override;

    CLONE(CGemItem);
    CGemItem();
    ~CGemItem();
};

