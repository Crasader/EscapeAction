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
	auto fnt = Sprite::create("�ж�ж�.png"); //���� ��������Ʈ ����

	int x = 50 + ((rand() % (int)win_size.width*0.5)); //x��ǥ ����(���� �� �־��)
	int y = 50 + ((rand() % (int)win_size.height*0.5)); //y��ǥ ����(���� �� �־��)

	fnt->setPosition(Point(x, y));

	this->addChild(fnt);
}

void LayerGame::React()
{

}

