#include "LayerGame.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;


bool LayerGame::init()
{
	Furniture* funt = Furniture::create();
	funt->Create_Furniture();
	this->addChild(funt);


    return true;
}


