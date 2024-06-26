#pragma once
#include "CUI.h"

class CTexture;

class CImage :
    public CUI
{
private:
    CTexture* image;

public:
    void SetTexture(CTexture* texture) { image = texture; }

    virtual void Tick_UI() override {};
    virtual void Render_UI() override;

    CLONE(CImage);
    CImage();
    ~CImage();
};

