#pragma once
#include "CMonster.h"

class CStateMachine;

class CProjectileMonster :
    public CMonster
{
private:
    CStateMachine* stateMachine;
    bool           isPlayerLeft; // �÷��̾ ���� ���� ���ʿ� �ִ��� Ȯ��

public:
    void PlayAnimation(ANIMATION_TYPE type) override;

    bool IsPlayerLeft() { return isPlayerLeft; }
    void SetPlayerLeft(bool trace) { isPlayerLeft = trace; }

    virtual void DetectPlayer(bool isDetected) override;

    CLONE(CProjectileMonster);
    CProjectileMonster(int hp, float speed, float range, DeathEventStrategy* deathEvent);
    CProjectileMonster(const CProjectileMonster& other);
    ~CProjectileMonster();

private:
    virtual void Tick() override;

    void LoadAnimations() override;
    virtual void BeginOverlap(CCollider* ownCollider, CObj* otherObj, CCollider* otherCollider);
};

