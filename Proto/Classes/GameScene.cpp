#include "GameScene.h"
#include "SimpleAudioEngine.h"

bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
	auto ly_game = LayerGame::create();
	auto ly_ui = LayerUI::create();

	this->addChild(ly_game);
	this->addChild(ly_ui);

    return true;
}
