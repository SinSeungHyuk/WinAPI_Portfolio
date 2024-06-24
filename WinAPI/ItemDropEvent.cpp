#include "pch.h"
#include "ItemDropEvent.h"
#include "CLogMgr.h"

void ItemDropEvent::OnDeath(CMonster& monster)
{
	LOG(LOG_LEVEL::LOG, L"OnDeath Log Test");
}
