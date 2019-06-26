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

	//½ºÄÉÁì ½ÇÇà
	this->scheduleUpdate();

    return true;
}

void LayerGame::update(float dt)
{
	//pyer->Joy_move_check();
}


