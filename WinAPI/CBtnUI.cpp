#include "pch.h"
#include "CBtnUI.h"

#include "Resource.h"
#include "CEngine.h"

CBtnUI::CBtnUI()
	: m_CallBack(nullptr)
	, m_Inst(nullptr)
	, m_MemFunc(nullptr)
	, m_MemFunc_1(nullptr)
	, m_MemFunc_2(nullptr)
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
	PEN_TYPE Pen = PEN_TYPE::GREEN;
	if (IsMouseOn())
	{
		Pen = PEN_TYPE::BLUE;
	}

	if (IsLBtnDown())
	{
		Pen = PEN_TYPE::RED;
	}

	SELECT_PEN(BackDC, Pen);
	SELECT_BRUSH(BackDC, BRUSH_TYPE::GRAY);

	Vec2 vFinalPos = GetFinalPos();
	Vec2 vScale = GetScale();
	Rectangle(BackDC, (int)vFinalPos.x, (int)vFinalPos.y
		, (int)vFinalPos.x + (int)vScale.x, (int)vFinalPos.y + (int)vScale.y);
}