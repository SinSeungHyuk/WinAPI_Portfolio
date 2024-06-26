#pragma once
#include "CItem.h"

class CAnimator;

class CEndPointItem:
    public CItem
{
private:
    CAnimator* animator;

public:
    virtual void Tick() override;
    virtual void Render() override;

    virtual void GetItem() override;

    CLONE(CEndPointItem);
    CEndPointItem();
    ~CEndPointItem();
};

