#pragma once
class MonsterData
{
private:
	int hp;
	float speed;
	float detectRange;

public:
	MonsterData(int hp, float speed, float range);

	void SetHP(int value) { hp = value; }
	void TakeDamage(int value) { hp-=value; }
	int GetHP() { return hp; }

	void SetSpeed(int value) { speed = value; }
	int GetSpeed() { return speed; }

	void SetDetectRange(int value) { detectRange = value; }
	int GetDetectRange() { return detectRange; }
};

