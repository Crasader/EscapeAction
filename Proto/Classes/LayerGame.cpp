#include "LayerGame.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

bool LayerGame::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
	rm = Room::create();
	this->addChild(rm);

	pyer = player::create();
	this->addChild(pyer);

    return true;
}
