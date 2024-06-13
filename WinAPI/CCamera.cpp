#include "pch.h"
#include "CCamera.h"

#include "CEngine.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CAssetMgr.h"
#include "CTexture.h"


CCamera::CCamera()
	: m_CamSpeed(500.f)
	, m_BlackFilterTex(nullptr)
	, m_Frequency(0.f)
	, m_Amplitude(0.f)
	, m_Duration(0.f)
	, m_AccTime(0.f)
	, m_CamShake(false)
	, m_FilterInfo{}
{	
	// Black Filter Texture 생성
	Vec2 vResolution = CEngine::Get()->GetResolution();
	m_BlackFilterTex = CAssetMgr::Get()->CreateTexture(L"BlackFliterTex", (UINT)vResolution.x, (UINT)vResolution.y);

	m_FilterInfo.Effect = NONE;
}

CCamera::~CCamera()
{
}

void CCamera::Init()
{
	Vec2 vResolution = CEngine::Get()->GetResolution();
	m_LookAt = vResolution / 2.f;
}

void CCamera::Tick()
{
	if (KEY_PRESSED(KEY::W))	
		m_LookAt.y -= m_CamSpeed * DT;

	if (KEY_PRESSED(KEY::S))
		m_LookAt.y += m_CamSpeed * DT;

	if (KEY_PRESSED(KEY::A))
		m_LookAt.x -= m_CamSpeed * DT;

	if (KEY_PRESSED(KEY::D))
		m_LookAt.x += m_CamSpeed * DT;

	// 카메라 효과 동작
	CameraEffect();
	
	// 카메라가 보고있는 지점과, 해상도 중심위치의 차이값
	m_LookAtDiff = (m_LookAt + m_ShakeOffset) - (CEngine::Get()->GetResolution() / 2.f);
}

void CCamera::Render()
{		
	if (m_FilterInfo.Effect == NONE)
		return;
		
	UINT Alpha = 0;

	if (FILTER_EFFECT::FADE_OUT == m_FilterInfo.Effect)
	{
		float fRatio = m_FilterInfo.AccTime / m_FilterInfo.Duration;
		Alpha = (UINT)(255.f * fRatio);
	}

	else if (FILTER_EFFECT::FADE_IN == m_FilterInfo.Effect)
	{
		float fRatio = 1.f - (m_FilterInfo.AccTime / m_FilterInfo.Duration);
		Alpha = (UINT)(255.f * fRatio);
	}

	m_FilterInfo.AccTime += DT;
	if (m_FilterInfo.Duration < m_FilterInfo.AccTime)
	{
		m_FilterInfo.Effect = NONE;
		m_AccTime = 0.f;
		m_Duration = 0.f;
	}

	BLENDFUNCTION blend = {};
	blend.BlendOp = AC_SRC_OVER;
	blend.BlendFlags = 0;
	blend.SourceConstantAlpha = Alpha;
	blend.AlphaFormat = 0;
	
	AlphaBlend(BackDC, 0, 0
		, m_BlackFilterTex->GetWidth()
		, m_BlackFilterTex->GetHeight()
		, m_BlackFilterTex->GetDC()
		, 0, 0
		, m_BlackFilterTex->GetWidth()
		, m_BlackFilterTex->GetHeight()
		, blend);
}

void CCamera::CameraEffect()
{
	if (false == m_CamShake)
		return;

	// 카메라 이동 방향(1.f == 아래, -1.f == 위)	
	m_ShakeOffset.y += m_Amplitude * 4.f * m_Frequency * DT * m_Dir;

	// 진폭 수치를 넘어서면 방향을 전환시켜준다.
	if (m_Amplitude < fabs(m_ShakeOffset.y))
	{
		// 초과량을 다시 안쪽으로 적용시킨다.
		m_ShakeOffset.y += (fabs(m_ShakeOffset.y) - m_Amplitude) * -m_Dir;

		// 방향 전환
		m_Dir *= -1.f;
	}

	// 효과 유지시간이 다 되었는지 체크
	m_AccTime += DT;
	if (m_Duration < m_AccTime)
	{
		// 효과가 만료되면 세팅 값 정리
		m_AccTime = 0.f;
		m_CamShake = false;
		m_ShakeOffset = Vec2(0.f, 0.f);
	}
}