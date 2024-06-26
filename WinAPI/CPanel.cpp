#include "pch.h"
#include "CPanel.h"

#include "CKeyMgr.h"
#include "CEngine.h"
#include "CLogMgr.h"

CPanel::CPanel()
{
}

CPanel::~CPanel()
{
}

void CPanel::Tick_UI()
{
	if (IsLBtnDown())
	{
		Vec2 vCurMousePos = CKeyMgr::Get()->GetMousePos();
		Vec2 vDiff = vCurMousePos - m_GrabPos;

		Vec2 vPos = GetPos();
		vPos += vDiff;
		SetPos(vPos);

		m_GrabPos = vCurMousePos;
	}
}

void CPanel::Render_UI()
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

	//SELECT_PEN(BackDC, Pen);
	//SELECT_BRUSH(BackDC, BRUSH_TYPE::TURQUOISE);

	//Vec2 vFinalPos = GetFinalPos();
	//Vec2 vScale = GetScale();
	//Rectangle(BackDC, (int)vFinalPos.x, (int)vFinalPos.y
	//	, (int)vFinalPos.x + (int)vScale.x, (int)vFinalPos.y + (int)vScale.y);
}

void CPanel::BeginHovered()
{
	LOG(LOG_LEVEL::WARNING, GetName().c_str());
}

void CPanel::LBtnDown()
{
	m_GrabPos = CKeyMgr::Get()->GetMousePos();
}