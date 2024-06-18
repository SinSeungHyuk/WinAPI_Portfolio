#include "pch.h"
#include "CAnim.h"

#include "CObj.h"
#include "CEngine.h"
#include "CTexture.h"
#include "CTimeMgr.h"

#include "CAssetMgr.h"

CAnim::CAnim()
	: m_Owner(nullptr)
	, m_Atlas(nullptr)
	, m_CurIdx(0)
	, m_AccTime(0.f)
	, m_Finish(false)
{
}

CAnim::CAnim(const CAnim& _Other)
	: CBase(_Other)
	, m_Owner(nullptr)
	, m_vecFrm(_Other.m_vecFrm)
	, m_Atlas(_Other.m_Atlas)
	, m_CurIdx(_Other.m_CurIdx)
	, m_AccTime(_Other.m_AccTime)
	, m_Finish(_Other.m_Finish)
{
}

CAnim::~CAnim()
{
}

void CAnim::FinalTick()
{
	if (m_Finish)
		return;

	// �ð��� �帧�� üũ
	m_AccTime += DT;

	// ����� �ð��� ���� �������� Duration �� �ʰ��ϸ�
	if (m_vecFrm[m_CurIdx].Duration < m_AccTime)
	{		
		m_AccTime -= m_vecFrm[m_CurIdx].Duration;
		++m_CurIdx;

		if (m_vecFrm.size() <= m_CurIdx)
		{
			m_CurIdx = m_vecFrm.size() - 1.f;
			m_Finish = true;
		}
	}
}

void CAnim::Render()
{
	assert(m_Atlas);

	HDC dc = CEngine::Get()->GetBackDC();

	// Animation �� ������ ������Ʈ�� ��ġ
	Vec2 vPos = m_Owner->GetOwner()->GetRenderPos();

	TransparentBlt(dc, 
				  vPos.x - m_vecFrm[m_CurIdx].vSlice.x / 2.f + m_vecFrm[m_CurIdx].vOffset.x,
				  vPos.y - m_vecFrm[m_CurIdx].vSlice.y / 2.f + m_vecFrm[m_CurIdx].vOffset.y,
				  m_vecFrm[m_CurIdx].vSlice.x, m_vecFrm[m_CurIdx].vSlice.y,
				  m_Atlas->GetDC(),
				  m_vecFrm[m_CurIdx].vLeftTop.x, m_vecFrm[m_CurIdx].vLeftTop.y,
				  m_vecFrm[m_CurIdx].vSlice.x, m_vecFrm[m_CurIdx].vSlice.y,
				  RGB(0, 0, 0));
}


void CAnim::Create(const tAnimDesc& _Info)
{
	SetName(_Info.AnimName);
	m_Atlas = _Info.pAtlas;
	
	for (int i = 0; i < _Info.FrmCount; ++i)
	{
		tAnimFrm frm = {};

		frm.vLeftTop.x = _Info.StartLeftTop.x + _Info.SliceSize.x * (float)i;
		frm.vLeftTop.y = _Info.StartLeftTop.y;

		frm.vSlice = _Info.SliceSize;

		frm.vOffset = _Info.animOffset;

		frm.Duration = 1.f / (float)_Info.FPS;

		m_vecFrm.push_back(frm);
	}
}

void CAnim::Save(const wstring& _FolderPath)
{
	wstring strName = GetName();
	wstring FilePath = _FolderPath + strName + L".anim";
	
	FILE* pFile = nullptr;
	_wfopen_s(&pFile, FilePath.c_str(), L"w");
	
	// �ִϸ��̼� �̸�
	fwprintf_s(pFile, L"[ANIMATION_NAME]\n");
	fwprintf_s(pFile, strName.c_str());
	fwprintf_s(pFile, L"\n\n");

	// �����ϴ� ��Ʋ�� �ؽ��� ����
	fwprintf_s(pFile, L"[ATLAS_TEXTURE]\n");

	if (m_Atlas)
	{
		fwprintf_s(pFile, L"%s\n", m_Atlas->GetKey().c_str());
		fwprintf_s(pFile, L"%s\n", m_Atlas->GetRelativePath().c_str());
	}
	else
	{
		fwprintf_s(pFile, L"None\n");
		fwprintf_s(pFile, L"None\n");
	}
	fwprintf_s(pFile, L"\n");


	// �� �����Ӻ� ������
	fwprintf_s(pFile, L"[FRAME_DATA]\n");
	fwprintf_s(pFile, L"Frame_Count %d\n\n", m_vecFrm.size());

	for (size_t i = 0; i < m_vecFrm.size(); ++i)
	{
		fwprintf_s(pFile, L"Frame_Index %d\n", i);
		fwprintf_s(pFile, L"Left_Top    %f %f\n", m_vecFrm[i].vLeftTop.x, m_vecFrm[i].vLeftTop.y);
		fwprintf_s(pFile, L"Offset      %f %f\n", m_vecFrm[i].vOffset.x, m_vecFrm[i].vOffset.y);
		fwprintf_s(pFile, L"Slice       %f %f\n", m_vecFrm[i].vSlice.x, m_vecFrm[i].vSlice.y);
		fwprintf_s(pFile, L"Duration    %f\n\n", m_vecFrm[i].Duration);
	}	
	
		
	
	fclose(pFile);
}

void CAnim::Load(const wstring& _FilePath)
{
	FILE* pFile = nullptr;
	_wfopen_s(&pFile, _FilePath.c_str(), L"r");

	wchar_t szRead[255] = {};
	while (true)
	{		
		if (EOF == fwscanf_s(pFile, L"%s", szRead, 255))
			break;

		wstring str = szRead;

		if (str == L"[ANIMATION_NAME]")
		{
			fwscanf_s(pFile, L"%s", szRead, 255);
			SetName(szRead);
		}
		else if (str == L"[ATLAS_TEXTURE]")
		{
			wstring strKey, strRelativePath;
			fwscanf_s(pFile, L"%s", szRead, 255);
			strKey = szRead;

			fwscanf_s(pFile, L"%s", szRead, 255);
			strRelativePath = szRead;

			if (strKey != L"None")
			{
				m_Atlas = CAssetMgr::Get()->LoadTexture(strKey, strRelativePath);
			}			
		}
		else if (str == L"[FRAME_DATA]")			
		{
			wchar_t FrameBuff[255] = {};

			tAnimFrm frm = {};

			while (true)
			{
				if (EOF == fwscanf_s(pFile, L"%s", FrameBuff, 255))
				{
					break;
				}
				
				if (!wcscmp(L"Left_Top", FrameBuff))
				{
					fwscanf_s(pFile, L"%f %f", &frm.vLeftTop.x, &frm.vLeftTop.y);
				}
				else if (!wcscmp(L"Offset", FrameBuff))
				{
					fwscanf_s(pFile, L"%f %f", &frm.vOffset.x, &frm.vOffset.y);
				}
				else if (!wcscmp(L"Slice", FrameBuff))
				{
					fwscanf_s(pFile, L"%f %f", &frm.vSlice.x, &frm.vSlice.y);
				}
				else if (!wcscmp(L"Duration", FrameBuff))
				{
					fwscanf_s(pFile, L"%f", &frm.Duration);
					m_vecFrm.push_back(frm);
				}				
			}			
		}
	}

	fclose(pFile);
}

