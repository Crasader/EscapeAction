#include "LayerUI.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;


bool LayerUI::init()
{

	player_Item* pl = player_Item::create();
	this->addChild(pl);
	return true;
}
