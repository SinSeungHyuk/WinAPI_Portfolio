#pragma once
#include "CObj.h"

class CCollider;
class CAnimator;
class MonsterData;
class CRigidBody;
class DeathEventStrategy;

class CMonster :
    public CObj
{
private:
    DeathEventStrategy* deathEvent; // �� ���͸��� ���� �ı�ó��

protected:
    MonsterData*    monsterData;
    CCollider*      collider;
    CRigidBody*     rigidbody;

public:
    CAnimator* animator;
    bool isMonsterLeft; // false : right

    MonsterData* GetMonsterData() { return monsterData; }

    virtual void Tick() override;
    virtual void Render() override;
    virtual void BeginOverlap(CCollider* ownCollider, CObj* otherObj, CCollider* _OtherCollider);
    virtual void EndOverlap(CCollider* ownCollider, CObj* otherObj, CCollider* _OtherCollider);

    virtual void LoadAnimations() = 0; // �� ���͸��� �ʿ��� �ִϸ��̼� ��������
    virtual void PlayAnimation(ANIMATION_TYPE type) = 0; // �� ���͸��� �ִϸ��̼� �̸��� �ٸ��Ƿ� �����Լ��� ���� ����

    virtual CMonster* Clone() = 0;
    CMonster(int hp, float speed, float range, DeathEventStrategy* deathEvent);
    CMonster(const CMonster& _Other);
    ~CMonster();
};

