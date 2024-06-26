#include "pch.h"
#include "ItemDropEvent.h"
#include "CLogMgr.h"
#include "CMonster.h"
#include "CAnimator.h"
#include "CTimeMgr.h"

void ItemDropEvent::OnDeath(CMonster& monster)
{
	LOG(LOG_LEVEL::LOG, L"OnDeath Log Test");

	//monster.PlayAnimation(ANIMATION_TYPE::DEAD);

	float timer = 0.f;


}
