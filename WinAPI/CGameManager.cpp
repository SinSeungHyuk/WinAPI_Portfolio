#include "pch.h"
#include "CGameManager.h"
#include "CLogMgr.h"
#include "CAssetMgr.h"

#include "CImage.h"

CGameManager::CGameManager() : coins(0), gems(0)
{}

CGameManager::~CGameManager()
{
}

void CGameManager::Init()
{
	
}

void CGameManager::Tick()
{
}

void CGameManager::GetCoin()
{
	LOG(LOG_LEVEL::LOG, L"COIN GET!");

	coins++;

	if (coins % 1 == 0) {
		GetGem();
	}
}

void CGameManager::GetGem()
{
	gems++;

	CImage* image = new CImage;
	image->SetPos(550.f + gems * gemOffset, 50.f);
	image->SetTexture(CAssetMgr::Get()->LoadTexture(L"gemImage", L"texture\\gemImage.png"));
	gemArray.push_back(image);
	CreateObject(image, LAYER_TYPE::UI);
}

bool CGameManager::UseGem()
{
	if (gems == 0) 
		return false;

	Destroy(gemArray[--gems]);

	return false;
}