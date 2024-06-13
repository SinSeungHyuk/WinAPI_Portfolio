#pragma once
#include "CLevel.h"

class CTileMap;

class CLevel_Start :
    public CLevel
{
private:
    CTileMap* m_TileMap;

    void TileMode();

public:
    virtual void Init() override;   // ���� �ʱ�ȭ
    virtual void Exit() override;   // ������ �����Ҷ� ����

    virtual void Tick() override;

public:    
    CLevel_Start(const CLevel_Start& _Other) = delete;
    CLevel_Start();
    ~CLevel_Start();
};

