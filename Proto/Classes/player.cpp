#include "player.h"

player::~player()
{
}

bool player::init()
{
	rc = Rect(0, 0, 0, 0);
	speed = 3;
	plyer = Sprite::create("player.png");
	this->addChild(plyer);
	plyer_size = plyer->getContentSize();
	win_size = Director::getInstance()->getWinSize();
	plyer->setName("player_move");

	plyer->setPosition(Vec2(win_size.width*0.5f, win_size.height*0.5f));
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_1(player::onPress, this);
	listener->onKeyReleased = CC_CALLBACK_1(player::onRelease, this);

	_eventDispatcher->addEventListenerWithFixedPriority(listener, 1);

	this->scheduleUpdate();

	return true;
}

void player::setRect(Rect back_rc)
{
	rc = back_rc;
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
	if (keyUp&&plyer->getPositionY() < rc.getMaxY() - plyer_size.height*0.5f) {
		plyer->setPositionY(plyer->getPositionY() + speed);
	}
	if (keyDown&&plyer->getPositionY() >rc.getMinY()+ plyer_size.height*0.5f) {
		plyer->setPositionY(plyer->getPositionY() - speed);
	}

	if (keyLeft&&plyer->getPositionX() >rc.getMinX()+ plyer_size.width*0.5f) {
		plyer->setPositionX(plyer->getPositionX() - speed);
	}
	if (keyRight&&plyer->getPositionX() < rc.getMaxX() - plyer_size.width*0.5f) {
		plyer->setPositionX(plyer->getPositionX() + speed);
	}
}

void player::set_player(player * p)
{
	player_db = p;
}

player* player::get_player()
{
	return player_db;
}
