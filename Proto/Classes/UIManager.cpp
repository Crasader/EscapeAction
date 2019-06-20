#include "UIManager.h"

static UIManager* pUIManager = NULL;

UIManager::UIManager()
{
	_atk = NULL;
	_search = NULL;
	_trap = NULL;
	_key = NULL;
}
UIManager::~UIManager()
{
}
UIManager * UIManager::getInstance()
{
	if (pUIManager == NULL) {
		pUIManager = new UIManager();
	}
		return pUIManager;
}

bool UIManager::setAtkBtn(ui::Button * atk)
{
	if (_atk == NULL) {
		_atk = atk;
		return true;
	}
	return false;
}

bool UIManager::setSearchBtn(ui::Button * search)
{
	if (_search == NULL) {
		_search = search;
		return true;
	}
	return false;
}

bool UIManager::setKeyBtn(ui::Button * key)
{
	if (_key == NULL) {
		_key = key;
		return true;
	}
	return false;
}

bool UIManager::setTrapBtn(ui::Button * trap)
{
	if (_trap == NULL) {
		_trap = trap;
		return true;
	}
	return false;
}

void UIManager::setEnable_AtkBtn(bool enable)
{
	_atk->setEnabled(enable);
}

void UIManager::setEnable_SearchBtn(bool enable)
{
	_search->setEnabled(enable);
}

void UIManager::setEnable_KeyBtn(bool enable)
{
	_key->setEnabled(enable);
}

void UIManager::setEnable_TrapBtn(bool enable)
{
	_trap->setEnabled(enable);
}
