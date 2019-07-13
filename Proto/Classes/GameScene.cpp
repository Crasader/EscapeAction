#include "GameScene.h"
#include "SimpleAudioEngine.h"
bool GameScene::init()
{

	LayerGame* ly_game = LayerGame::create();
	auto ly_ui = LayerUI::create();
	auto Joy_ui = Joystick::create();

	this->addChild(ly_game);
	this->addChild(ly_ui);
	this->addChild(Joy_ui);

	UIManager::getInstance()->setJoystick(Joy_ui);

    return true;
}
