#include "UIManager.h"
#include "Button_Ui.h"

static UIManager* pUIManager = NULL;

UIManager::UIManager()
{
	_atk = NULL;
	_search = NULL;
	_trap = NULL;
	_key = NULL;
	_joystick = NULL;
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

Point UIManager::get_Player_m_p1()
{
	return _joystick->Move_p_joy1;
}

Vec2 UIManager::get_Player_m_p2()
{
	return _joystick->Move_p_joy2;
}

void UIManager::set_btn_UI(Button_Ui * btn_UI)
{
	_btn_UI = btn_UI;
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

bool UIManager::setJoystick(Joystick * joystick)
{
	if (_joystick == NULL) {
		_joystick = joystick;
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

void UIManager::setAttack_btn(bool atk)
{
	_btn_UI->atk_on = atk;
}

bool UIManager::getAttack_btn()
{
	return _btn_UI->atk_on;
}

void UIManager::setSearch_btn(bool sch)
{
	_btn_UI->search_on = sch;
}

bool UIManager::getSearch_btn()
{
	return _btn_UI->search_on;
}

