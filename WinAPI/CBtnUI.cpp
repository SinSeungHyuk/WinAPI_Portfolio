#include "pch.h"
#include "CBtnUI.h"

#include "Resource.h"
#include "CEngine.h"
#include "CTexture.h"

CBtnUI::CBtnUI()
	: m_CallBack(nullptr)
	, m_Inst(nullptr)
	, m_MemFunc(nullptr)
	, m_MemFunc_1(nullptr)
	, m_MemFunc_2(nullptr)
	, m_NormalImg(nullptr)
	, m_HoverImg(nullptr)
	, m_PressedImg(nullptr)
{
}

CBtnUI::~CBtnUI()
{
}

LRESULT CALLBACK TileProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

void CBtnUI::LBtnDown()
{
	
}

void CBtnUI::LBtnClicked()
{
	if (m_CallBack)
	{
		m_CallBack();
	}

	if (m_Inst && m_MemFunc)
	{
		(m_Inst->*m_MemFunc)();
	}
}

void CBtnUI::Render_UI()
{
	Vec2 vPos = GetRenderPos();
	UINT width = m_NormalImg->GetWidth();
	UINT height = m_NormalImg->GetHeight();

	TransparentBlt(BackDC, (int)vPos.x, (int)vPos.y
		, width, height, m_NormalImg->GetDC(), 0, 0, width, height, RGB(0, 0, 0));

}