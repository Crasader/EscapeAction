#include "LayerUI.h"
#include "SimpleAudioEngine.h"
#include "UIManager.h"


USING_NS_CC;

bool LayerUI::init()
{

	player_Item* pl = player_Item::create();
	this->addChild(pl);

	UIManager::getInstance()->setWeaponBtn((ui::Button*)pl->getChildByName("btn1"));
	return true;
}
