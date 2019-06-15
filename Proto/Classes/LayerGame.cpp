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

	auto back = new Room(1);//level 1 room

    return true;
}
