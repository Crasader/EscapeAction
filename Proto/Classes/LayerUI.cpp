#include "LayerUI.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

bool LayerUI::init()
{
	Joystick* js = Joystick::create();
	player_Item* pl = player_Item::create();
	this->addChild(pl);
	this->addChild(js);
	return true;
}
