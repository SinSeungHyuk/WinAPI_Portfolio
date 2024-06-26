#pragma once

class CImage;

class CGameManager
{
	SINGLE(CGameManager);

private:
	int coins;		 // 코인 개수
	int gems;		 // 젬 개수
	const int gemOffset = 50.f; // 화면 상단에 나올 젬의 간격
	const int coinsPerGem = 5;  // 젬으로 교환하기 위한 코인개수

	vector<CImage*> gemArray; // 젬UI를 관리하기 위한 벡터

public:
	void Init();
	void Tick();

	void GetCoin(); // 코인 획득
	void GetGem(); // 코인 획득
	bool UseGem();	// 젬 사용
};
