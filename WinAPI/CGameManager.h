#pragma once

class CImage;

class CGameManager
{
	SINGLE(CGameManager);

private:
	int coins;		 // ���� ����
	int gems;		 // �� ����
	const int gemOffset = 50.f; // ȭ�� ��ܿ� ���� ���� ����
	const int coinsPerGem = 5;  // ������ ��ȯ�ϱ� ���� ���ΰ���

	vector<CImage*> gemArray; // ��UI�� �����ϱ� ���� ����

public:
	void Init();
	void Tick();

	void GetCoin(); // ���� ȹ��
	void GetGem(); // ���� ȹ��
	bool UseGem();	// �� ���
};
