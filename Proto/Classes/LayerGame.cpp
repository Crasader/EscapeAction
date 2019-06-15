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

	win_size = Director::getInstance()->getWinSize();

	player = Sprite::create("CloseNormal.png");
	player->setPosition(Point(win_size.width * 0.5, win_size.height * 0.5));
	this->addChild(player);

	auto keyboard_lis = EventListenerKeyboard::create();
	keyboard_lis->onKeyPressed = CC_CALLBACK_1(LayerGame::onPress, this);
	keyboard_lis->onKeyReleased = CC_CALLBACK_1(LayerGame::onRelease, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboard_lis, this);

	//this->schedule(schedule_selector(HelloWorld::Check_Player));

	//this is Player branch!

    return true;
}

void LayerGame::onPress(EventKeyboard::KeyCode code)
{
	switch (code)
	{
	case cocos2d::EventKeyboard::KeyCode::KEY_A:
		this->schedule(schedule_selector(LayerGame::Move_L), 0.005);
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_D:
		this->schedule(schedule_selector(LayerGame::Move_R), 0.005);
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_S:
		this->schedule(schedule_selector(LayerGame::Move_D), 0.005);
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_W:
		this->schedule(schedule_selector(LayerGame::Move_U), 0.005);
		break;
	default:
		break;
	}
}

void LayerGame::onRelease(EventKeyboard::KeyCode code)
{
	switch (code)
	{
	case cocos2d::EventKeyboard::KeyCode::KEY_A:
		this->unschedule(schedule_selector(LayerGame::Move_L));
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_D:
		this->unschedule(schedule_selector(LayerGame::Move_R));
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_S:
		this->unschedule(schedule_selector(LayerGame::Move_D));
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_W:
		this->unschedule(schedule_selector(LayerGame::Move_U));
		break;
	default:
		break;
	}
}

void LayerGame::Move_R(float dt)
{
	if (player->getPosition().x + player->getContentSize().width * 0.5 >= win_size.width) //화면 안나가게
		return;
	Point temp_pos = Point(player->getPosition().x + 1, player->getPosition().y);
	player->setPosition(temp_pos);
}

void LayerGame::Move_L(float dt)
{
	if (player->getPosition().x - player->getContentSize().width * 0.5 <= 0) //화면 안나가게
		return;
	Point temp_pos = Point(player->getPosition().x - 1, player->getPosition().y);
	player->setPosition(temp_pos);
}

void LayerGame::Move_U(float dt)
{
	if (player->getPosition().y + player->getContentSize().height * 0.5 >= win_size.height) //화면 안나가게
		return;
	Point temp_pos = Point(player->getPosition().x, player->getPosition().y + 1);
	player->setPosition(temp_pos);
}

void LayerGame::Move_D(float dt)
{
	if (player->getPosition().y - player->getContentSize().height * 0.5 <= 0) //화면 안나가게
		return;
	Point temp_pos = Point(player->getPosition().x, player->getPosition().y - 1);
	player->setPosition(temp_pos);
}
