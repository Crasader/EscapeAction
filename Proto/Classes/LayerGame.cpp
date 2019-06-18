#include "LayerGame.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;


bool LayerGame::init()
{

	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_1(LayerGame::onPress, this);
	listener->onKeyReleased = CC_CALLBACK_1(LayerGame::onRelease, this);

	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 1);

	back = Room::create();//level 1 room, now maxLevel is 7. 
						//if want edit maxLevel //goto Room.h and fix p_room MatrixSize

	this->addChild(back);
    return true;

}

void LayerGame::onPress(EventKeyboard::KeyCode key)
{
	switch (key)
	{
	case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
		back->MoveRoom(0);
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		back->MoveRoom(1);
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		back->MoveRoom(2);
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		back->MoveRoom(3);
		break;
	default:
		break;
	}
}

void LayerGame::onRelease(EventKeyboard::KeyCode key)
{
}
