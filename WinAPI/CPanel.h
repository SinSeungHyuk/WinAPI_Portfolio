#pragma once
#include "CUI.h"

class CPanel :
    public CUI
{
private:
    Vec2    m_GrabPos;

public:
    virtual void Tick_UI() override;    
    virtual void Render_UI() override;

    virtual void BeginHovered() override;

public:
    virtual void LBtnDown();

public:
    CLONE(CPanel);
    CPanel();
    ~CPanel();
};

