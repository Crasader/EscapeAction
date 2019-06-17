#include "LayerGame.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;


Scene * LayerGame::createScene()
{
	return nullptr;
}

bool LayerGame::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

	//this is Object branch!

	win_size = Director::getInstance()->getWinSize();

	srand(time(NULL));

    return true;
}

void LayerGame::Create_Fnt()
{
	auto fnt = Sprite::create("¿Ð¶ó¿Ð¶ó.png"); //°¡±¸ ½ºÇÁ¶óÀÌÆ® »ý¼º

	int x = 50 + ((rand() % (int)win_size.width*0.5)); //xÁÂÇ¥ ·£´ý(ÀÓÀÇ °ª ³Ö¾îµÒ)
	int y = 50 + ((rand() % (int)win_size.height*0.5)); //yÁÂÇ¥ ·£´ý(ÀÓÀÇ °ª ³Ö¾îµÒ)

	fnt->setPosition(Point(x, y));

	this->addChild(fnt);
}

void LayerGame::React()
{

}

