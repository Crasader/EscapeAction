#include "Joystick.h"

bool Joystick::init()
{
	Win_size = Director::getInstance()->getWinSize();

	_MoveJoy = Sprite::create("Joy.png");
	_MoveJoy->setName("Joystick_mj");
	this->addChild(_MoveJoy);

	_UnMoveJoy = Sprite::create("Unjoy.png");
	_UnMoveJoy->setName("Joystick_umj");
	this->addChild(_UnMoveJoy);

	auto Joy_listener = EventListenerTouchOneByOne::create();
	Joy_listener->onTouchBegan = CC_CALLBACK_2(Joystick::onTouchBegan, this);
	Joy_listener->onTouchMoved = CC_CALLBACK_2(Joystick::onTouchMoved, this);
	Joy_listener->onTouchEnded = CC_CALLBACK_2(Joystick::onTouchEnded, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(Joy_listener, this);

	return true;
}

Joystick::~Joystick()
{
}

bool Joystick::onTouchBegan(Touch * touch, Event * unused_event)
{
	auto mj = (Sprite*)this->getChildByName("Joystick_mj");
	auto umj = (Sprite*)this->getChildByName("Joystick_umj");

	Mj_Touch_p = touch->getLocation();
	Umj_Touch_p = touch->getLocation();

	umj->setPosition(Point(Mj_Touch_p));
	mj->setPosition(Point(Umj_Touch_p));

	umj->setVisible(true);
	mj->setVisible(true);
	return true;
}

void Joystick::onTouchMoved(Touch * touch, Event * unused_event)
{
	auto mj_p = (Sprite*)this->getChildByName("Joystick_mj");
	mj_p->setPosition(Point(touch->getLocation()));
}

void Joystick::onTouchEnded(Touch * touch, Event * unused_event)
{
	auto umj = (Sprite*)this->getChildByName("Joystick_umj");
	auto mj = (Sprite*)this->getChildByName("Joystick_mj");

	Mj_Touch_p = touch->getLocation();
	umj->setVisible(false);
	mj->setVisible(false);
}
