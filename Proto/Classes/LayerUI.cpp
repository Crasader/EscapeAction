#include "LayerUI.h"
#include "SimpleAudioEngine.h"
#include "UIManager.h"


USING_NS_CC;

bool LayerUI::init()
{
	//아이템 버튼 생성
	player_Item* pl = player_Item::create();
	this->addChild(pl);

	//UIManager에 4개의 버튼 세팅
	UIManager::getInstance()->setWeaponBtn((ui::Button*)pl->getChildByName("btn1"));
	UIManager::getInstance()->setReserchBtn((ui::Button*)pl->getChildByName("btn2"));
	UIManager::getInstance()->setKeyBtn((ui::Button*)pl->getChildByName("btn3"));
	UIManager::getInstance()->setBombBtn((ui::Button*)pl->getChildByName("btn4"));

	return true;
}
