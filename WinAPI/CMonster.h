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
    DeathEventStrategy* deathEvent; // 각 몬스터마다 가질 파괴처리

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

    virtual void LoadAnimations() = 0; // 각 몬스터마다 필요한 애니메이션 가져오기
    virtual void PlayAnimation(ANIMATION_TYPE type) = 0; // 각 몬스터마다 애니메이션 이름이 다르므로 가상함수로 각자 구현

    virtual CMonster* Clone() = 0;
    CMonster(int hp, float speed, float range, DeathEventStrategy* deathEvent);
    CMonster(const CMonster& _Other);
    ~CMonster();
};

