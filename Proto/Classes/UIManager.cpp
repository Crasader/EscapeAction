#include "UIManager.h"

static UIManager* pUIManager = NULL;

UIManager::UIManager()
{
}
UIManager::~UIManager()
{
}
UIManager * UIManager::getInstance()
{
	if (pUIManager = NULL) {
		pUIManager = new UIManager();
	}
		return pUIManager;
}


void UIManager::setEnableWBtn(bool setEnable)
{
	_weapon->setEnabled(setEnable);
}

void UIManager::setWeaponBtn(ui::Button * weapon)
{
	_weapon = weapon;
}
