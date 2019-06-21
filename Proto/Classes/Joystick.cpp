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

	Mj_Touch_p = Vec2(0,0);

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

	Vec2 max_touch = touch->getLocation();

	if (max_touch.x > Win_size.width *0.5)
	{
		umj->setPosition(Point(Mj_Touch_p));
		mj->setPosition(Point(Umj_Touch_p));

		umj->setVisible(true);
		mj->setVisible(true);

		Move_p_joy = Mj_Touch_p - Umj_Touch_p;
		Move_p_joy = Move_p_joy.getNormalized();
	}
	else
	{
		umj->setVisible(false);
		mj->setVisible(false);
	}
	return true;
}

void Joystick::onTouchMoved(Touch * touch, Event * unused_event)
{
	auto mj_p = (Sprite*)this->getChildByName("Joystick_mj");
	mj_p->setPosition(Point(touch->getLocation()));
	auto umj = (Sprite*)this->getChildByName("Joystick_umj");
	Umj_Touch_p = umj->getPosition();

	Mj_Touch_p = touch->getLocation();

	Move_p_joy = Mj_Touch_p - Umj_Touch_p;
	Move_p_joy = Move_p_joy.getNormalized();

}

void Joystick::onTouchEnded(Touch * touch, Event * unused_event)
{
	auto umj = (Sprite*)this->getChildByName("Joystick_umj");
	auto mj = (Sprite*)this->getChildByName("Joystick_mj");

	Move_p_joy = Vec2::ZERO;

	umj->setVisible(false);
	mj->setVisible(false);
}
