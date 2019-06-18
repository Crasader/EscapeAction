#include "player.h"

player::~player()
{
}

bool player::init()
{
	speed = 3;
	plyer = Sprite::create("HelloWorld.png");
	this->addChild(plyer);
	plyer_size = plyer->getContentSize();
	win_size = Director::getInstance()->getWinSize();

	plyer->setPosition(Vec2(win_size.width*0.5f, win_size.height*0.5f));
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_1(player::onPress, this);
	listener->onKeyReleased = CC_CALLBACK_1(player::onRelease, this);

	_eventDispatcher->addEventListenerWithFixedPriority(listener, 1);

	this->scheduleUpdate();
	return true;
}

void player::onPress(EventKeyboard::KeyCode key)
{

	if (key == cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW) {
		keyDown = false;
		keyUp = true;
	}
	else if (key == cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW) {
		keyUp = false;
		keyDown = true;
	}

	if (key == cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW) {
		keyRight = false;
		keyLeft = true;
	}
	else if (key == cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW) {
		keyRight = true;
		keyLeft = false;
	}
}

void player::onRelease(EventKeyboard::KeyCode key)
{
	if (key == cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW) {
		keyUp = false;
	}
	else if (key == cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW) {
		keyDown = false;
	}

	if (key == cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW) {
		keyLeft = false;
	}
	else if (key == cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW) {
		keyRight = false;
	}
}

void player::update(float dt)
{
	if (keyUp&&plyer->getPositionY() < win_size.height - plyer_size.height*0.5f) {
		plyer->setPositionY(plyer->getPositionY() + speed);
	}
	if (keyDown&&plyer->getPositionY() > plyer_size.height*0.5f) {
		plyer->setPositionY(plyer->getPositionY() - speed);
	}

	if (keyLeft&&plyer->getPositionX() > plyer_size.width*0.5f) {
		plyer->setPositionX(plyer->getPositionX() - speed);
	}
	if (keyRight&&plyer->getPositionX() < win_size.width - plyer_size.width*0.5f) {
		plyer->setPositionX(plyer->getPositionX() + speed);
	}
}