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
	pyer->setRect(rm->GetBackRect());
	this->addChild(pyer);
	Furniture* funt = Furniture::create();
	funt->Create_Furniture();
	this->addChild(funt);

    return true;
}


