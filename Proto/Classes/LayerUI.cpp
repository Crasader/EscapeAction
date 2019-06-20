#include "LayerUI.h"
#include "SimpleAudioEngine.h"
#include "UIManager.h"


USING_NS_CC;

bool LayerUI::init()
{
	//������ ��ư ����
	player_Item* pl = player_Item::create();
	this->addChild(pl);

	//UIManager�� 4���� ��ư ����
	UIManager::getInstance()->setWeaponBtn((ui::Button*)pl->getChildByName("btn1"));
	UIManager::getInstance()->setReserchBtn((ui::Button*)pl->getChildByName("btn2"));
	UIManager::getInstance()->setKeyBtn((ui::Button*)pl->getChildByName("btn3"));
	UIManager::getInstance()->setBombBtn((ui::Button*)pl->getChildByName("btn4"));

	Joystick* js = Joystick::create();
	this->addChild(js);
	return true;
}
