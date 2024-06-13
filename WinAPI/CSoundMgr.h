#pragma once

class CSound;

class CSoundMgr
{
	SINGLE(CSoundMgr)
private:
	LPDIRECTSOUND8	m_pSound;	// ���� ī�� ����
	CSound*			m_pBGM;		// BGM Sound


public:
	int Init();
	LPDIRECTSOUND8 GetSoundDevice() { return m_pSound; }	
	void RegisterToBGM(CSound* _pSound);
};
