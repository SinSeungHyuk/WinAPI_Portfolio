#include "pch.h"
#include "CLevel_Editor.h"

#include "CLogMgr.h"
#include "CPathMgr.h"

#include "CKeyMgr.h"
#include "CTile.h"
#include "resource.h"

#include "CLevelMgr.h"
#include "CLevel.h"

#include "CAssetMgr.h"

#include "CEngine.h"
#include "CTileMap.h"

#include "CBtnUI.h"
#include "CPanel.h"
#include "CUIMgr.h"

#include "CSound.h"

#include "resource.h"


LRESULT CALLBACK TileProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
void TestFunc()
{
	DialogBox(nullptr, MAKEINTRESOURCE(IDD_TILE_ROWCOL), CEngine::Get()->GetMainHwnd(), TileProc);
	CUIMgr::Get()->SetPreventFrame(1);
}

void TestFunc2()
{
	ChangeLevel(LEVEL_TYPE::START);
}



CLevel_Editor::CLevel_Editor()
	: m_hMenu(nullptr)
	, m_TileMap(nullptr)
{
	m_hMenu = LoadMenu(nullptr, MAKEINTRESOURCE(IDC_WINAPI));
}

CLevel_Editor::~CLevel_Editor()
{
	DestroyMenu(m_hMenu);
}


void CLevel_Editor::Init()
{
	// BGM ����
	//CSound* pBGM = CAssetMgr::Get()->LoadSound(L"BattleBGM", L"sound\\BGM_Stage1.wav");
	//pBGM->Play();

	// �޴� �߰�	
	SetMenu(CEngine::Get()->GetMainHwnd(), m_hMenu);

	// �޴��� �پ����ϱ�, �ٽ� ������ ũ�� ����
	UINT width = CEngine::Get()->GetResolution().x;
	UINT height = CEngine::Get()->GetResolution().y;
	CEngine::Get()->ChangeWindowResolution(width, height);

	// ������Ʈ ����
	CObj* pObj = nullptr;

	// Tile
	pObj = new CTile;
	pObj->SetName(L"Tile Object");
	pObj->SetPos(0.f, 0.f);

	m_TileMap = pObj->GetComponent<CTileMap>();

	m_TileMap->SetAtlas(CAssetMgr::Get()->LoadTexture(L"TileAtlasTex", L"texture\\TILE.bmp"));
	m_TileMap->SetAtlasTileSize(Vec2(64.f, 64.f));

	m_TileMap->SetTileSize(Vec2(64.f, 64.f));
	m_TileMap->SetRowCol(5, 5);

	AddObject(pObj, LAYER_TYPE::TILE);


	// Panel �߰�
	CPanel* pPanel = new CPanel;
	pPanel->SetName(L"Origin Panel");
	pPanel->SetScale(Vec2(500.f, 400.f));
	pPanel->SetPos(Vec2(700.f, 30.f));
	AddObject(pPanel, LAYER_TYPE::UI);


	// UI �߰��ϱ�
	CBtnUI* pUI = new CBtnUI;
	Vec2 vResol = CEngine::Get()->GetResolution();
	pUI->SetScale(Vec2(120.f, 50.f));
	pUI->SetPos(Vec2(10.f, 20.f));
	pUI->SetCallBack(&TestFunc);
	pPanel->AddChildUI(pUI);
	
	pUI = new CBtnUI;
	pUI->SetScale(Vec2(120.f, 50.f));
	pUI->SetPos(Vec2(10.f, 120.f));
	pUI->SetCallBack(&TestFunc2);
	pPanel->AddChildUI(pUI);

	pUI = new CBtnUI;
	pUI->SetScale(Vec2(120.f, 50.f));
	pUI->SetPos(Vec2(10.f, 220.f));
	pUI->SetDelegate(this, (BaseFunc)&CLevel_Editor::SaveTile);
	pPanel->AddChildUI(pUI);

	pUI = new CBtnUI;
	pUI->SetScale(Vec2(120.f, 50.f));
	pUI->SetPos(Vec2(10.f, 320.f));
	pUI->SetDelegate(this, (BaseFunc)&CLevel_Editor::LoadTile);
	pPanel->AddChildUI(pUI);


	CPanel* pClonePanel = pPanel->Clone();
	pClonePanel->SetName(L"Clone Panel");
	pClonePanel->SetPos(Vec2(300.f, 100.f));

	AddObject(pClonePanel, LAYER_TYPE::UI);
}

void CLevel_Editor::Exit()
{
	// �޴� ����
	SetMenu(CEngine::Get()->GetMainHwnd(), nullptr);

	// �޴��� ���ŵǾ�����, ������ ũ�� �ٽ� ���
	UINT width = CEngine::Get()->GetResolution().x;
	UINT height = CEngine::Get()->GetResolution().y;
	CEngine::Get()->ChangeWindowResolution(width, height);


	// ������Ʈ ����
	DeleteAllObjects();
}

void CLevel_Editor::Tick()
{
	CLevel::Tick();

	if (KEY_TAP(KEY::ENTER))
	{
		ChangeLevel(LEVEL_TYPE::START);
		CCamera::Get()->SetFilterEffect(FADE_OUT, 1.f);
		CCamera::Get()->SetFilterEffect(FADE_IN, 1.f);		
	}

	// Ÿ�� ���� ���콺 üũ
	TileMode();
}

void CLevel_Editor::TileMode()
{
	Vec2 vMousePos = CKeyMgr::Get()->GetMousePos();
	vMousePos = CCamera::Get()->GetRealPos(vMousePos);

	if (KEY_TAP(KEY::LBTN))
	{
		Vec2 TileSize = m_TileMap->GetTileSize();

		UINT Col = vMousePos.x / TileSize.x;
		UINT Row = vMousePos.y / TileSize.y;

		tTileInfo* pTileInfo = m_TileMap->GetTileInfo(Col, Row);

		if (nullptr != pTileInfo)
		{
			++pTileInfo->ImgIdx;
		}

		//wchar_t szMousePos[255] = {};
		//swprintf_s(szMousePos, 255, L"MouseX : %d, MousY : %d", (int)vMousePos.x, (int)vMousePos.y);
		//LOG(LOG_LEVEL::WARNING, szMousePos);
	}
}

void CLevel_Editor::SaveTile()
{
	wstring strContentPath = CPathMgr::Get()->GetContentPath();
	
	// ���� ��� ���ڿ�
	wchar_t szFilePath[255] = {};

	OPENFILENAME Desc = {};

	Desc.lStructSize = sizeof(OPENFILENAME);
	Desc.hwndOwner = nullptr;
	Desc.lpstrFile = szFilePath;
	Desc.nMaxFile = 255;
	Desc.lpstrFilter = L"Tile\0*.tile\0ALL\0*.*"; 
	Desc.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	Desc.lpstrInitialDir = strContentPath.c_str();

	if (GetSaveFileName(&Desc))
	{
		if (wcslen(szFilePath) != 0)
		{
			m_TileMap->Save(szFilePath);
		}		
	}

	CUIMgr::Get()->SetPreventFrame(1);
}

void CLevel_Editor::LoadTile()
{
	wstring strContentPath = CPathMgr::Get()->GetContentPath();

	// ���� ��� ���ڿ�
	wchar_t szFilePath[255] = {};

	OPENFILENAME Desc = {};

	Desc.lStructSize = sizeof(OPENFILENAME);
	Desc.hwndOwner = nullptr;
	Desc.lpstrFile = szFilePath;
	Desc.nMaxFile = 255;
	Desc.lpstrFilter = L"Tile\0*.tile\0ALL\0*.*";
	Desc.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	Desc.lpstrInitialDir = strContentPath.c_str();

	if (GetOpenFileName(&Desc))
	{
		if (wcslen(szFilePath) != 0)
		{
			m_TileMap->Load(szFilePath);
		}		
	}

	CUIMgr::Get()->SetPreventFrame(1);
}






// ===============================
// Ÿ�ϰ��� ���̾�α� ���ν��� �Լ�
// ===============================
LRESULT CALLBACK TileProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			int Col = GetDlgItemInt(hWnd, IDC_COL, nullptr, true);
			int Row = GetDlgItemInt(hWnd, IDC_ROW, nullptr, true);
						
			if (Col == 0 || Row == 0)
			{
				MessageBox(nullptr, L"Ÿ���� �� or ���� 0 �� �� �� �����ϴ�.", L"Ÿ�� ��, �� ���� ����", MB_OK);
				return (INT_PTR)TRUE;
			}

			// 1. ���� ������ ����
			CLevel* pCurLevel = CLevelMgr::Get()->GetCurrentLevel();
			CLevel_Editor* pEditorLevel = dynamic_cast<CLevel_Editor*>(pCurLevel);

			// ������ ���������� ����ؾ��ϴ� ���̾�α� �����찡 �ٸ��������� ����� ���
			assert(pEditorLevel);

			CTileMap* pTileMap = pEditorLevel->GetTileMap();
			pTileMap->SetRowCol(Col, Row);


			EndDialog(hWnd, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		else if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hWnd, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}

		break;
	}
	return (INT_PTR)FALSE;
}