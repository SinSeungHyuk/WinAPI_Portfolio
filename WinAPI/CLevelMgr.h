#pragma once


class CLevel;

class CLevelMgr
{
	SINGLE(CLevelMgr);
private:
	CLevel*		m_arrLevel[(int)LEVEL_TYPE::END];	// ��� ����
	CLevel*		m_CurLevel; // ���� ������ ����

public:
	CLevel* GetCurrentLevel() { return m_CurLevel ; }
	void ChangeLevel(LEVEL_TYPE _Type);

public:
	void Init();
	void Tick();
	void Render();

private:
	friend class CTaskMgr;
};

