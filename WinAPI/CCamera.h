#pragma once

enum FILTER_EFFECT
{
	FADE_IN,
	FADE_OUT,
	NONE,
};

struct FILTER_INFO
{
	FILTER_EFFECT	Effect;
	float			Duration;
	float			AccTime;
};


class CCamera
{
	SINGLE(CCamera);
private:
	Vec2		m_LookAt;
	Vec2		m_LookAtDiff;
	Vec2		m_ShakeOffset;
	float		m_CamSpeed;

	// Filter Effect
	CTexture*	m_BlackFilterTex;
	FILTER_INFO	m_FilterInfo;


	// Camera Oscillation
	float		m_Frequency;
	float		m_Amplitude;
	float		m_Duration;
	float		m_AccTime;
	float		m_Dir;
	bool		m_CamShake;

public:
	// Oscillation
	void SetCamShake(float _Frequency, float _Amplitude, float _Duration)
	{
		m_Frequency = _Frequency;
		m_Amplitude = _Amplitude;
		m_Duration = _Duration;
		m_Dir = 1.f;
		m_AccTime = 0.f;
		m_CamShake = true;
	}

	void SetFilterEffect(FILTER_EFFECT _Effect, float _Duration)
	{
		m_FilterInfo.Effect = _Effect;
		m_FilterInfo.Duration = _Duration;
		m_FilterInfo.AccTime = 0.f;
	}

	void SetLookAt(Vec2 _Look) { m_LookAt = _Look; }
	Vec2 GetLookAt() { return m_LookAt + m_ShakeOffset; }
	Vec2 GetRenderPos(Vec2 _RealPos) { return _RealPos - m_LookAtDiff; }
	Vec2 GetRealPos(Vec2 _vRenderPos) {return _vRenderPos + m_LookAtDiff; }

public:
	void Init();
	void Tick();
	void Render();

private:
	void CameraEffect();
};

