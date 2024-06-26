#include "pch.h"
#include "CItem.h"

#include "CTimeMgr.h"
#include "CEngine.h"
#include "CCollider.h"
#include "CTexture.h"

CItem::CItem()
	: texture(nullptr),
	collider(nullptr)
{
}

CItem::~CItem()
{
}


void CItem::Tick()
{
}

void CItem::Render()
{
	if (texture) {
		Vec2 vPos = GetRenderPos();
		UINT width = texture->GetWidth();
		UINT height = texture->GetHeight();

		TransparentBlt(BackDC, (int)vPos.x, (int)vPos.y
			, width, height, texture->GetDC(), 0, 0, width, height, RGB(0, 0, 0));
	}
}

void CItem::BeginOverlap(CCollider* ownCollider, CObj* otherObj, CCollider* otherCollider)
{
	if (otherObj->GetLayerType() == (int)LAYER_TYPE::PLAYER) {
		GetItem();

		Destroy(this);
	}
}


