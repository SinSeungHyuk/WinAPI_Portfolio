#include "pch.h"
#include "CImage.h"
#include "Resource.h"
#include "CEngine.h"
#include "CTexture.h"

CImage::CImage()
	: image(nullptr)
{
}

CImage::~CImage()
{
}

void CImage::Render_UI()
{
	Vec2 vPos = GetPos();
	UINT width = image->GetWidth();
	UINT height = image->GetHeight();

	TransparentBlt(BackDC, (int)vPos.x, (int)vPos.y
		, width, height, image->GetDC(), 0, 0, width, height, RGB(0, 0, 0));
}