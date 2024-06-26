#include "pch.h"
#include "CMissile.h"

#include "CTimeMgr.h"
#include "CEngine.h"
#include "CCollider.h"
#include "CTexture.h"

CMissile::CMissile()
	: velocity(0.f, 0.f)
	, mass(1.f)
	, speed(0.f)
	, texture(nullptr)
{
	CCollider* pCollider = AddComponent(new CCollider);
	pCollider->SetScale(Vec2(200.f, 200.f));
}

CMissile::~CMissile()
{
}

void CMissile::Tick()
{
	Vec2 vPos = GetPos();

	vPos.x += velocity.x * speed * DT;
	vPos.y += velocity.y * speed * DT;

	SetPos(vPos);
}

void CMissile::Render()
{
	Vec2 vPos = GetRenderPos();
	UINT width = texture->GetWidth();
	UINT height = texture->GetHeight();

	TransparentBlt(BackDC, (int)vPos.x - 16.f, (int)vPos.y - 16.f
		, width, height, texture->GetDC(), 0, 0, width, height, RGB(0, 0, 0));
}

void CMissile::BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider)
{
	//DeleteObject(this);
}
