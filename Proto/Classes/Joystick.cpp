#include "Joystick.h"

bool Joystick::init()
{
	Win_size = Director::getInstance()->getWinSize();

	_UnMoveJoy = Sprite::create("Unjoy.png");
	_UnMoveJoy->setName("Joystick_umj");
	_UnMoveJoy->setOpacity(150);
	_UnMoveJoy->setVisible(false);
	this->addChild(_UnMoveJoy);

	_MoveJoy = Sprite::create("Joy.png");
	_MoveJoy->setName("Joystick_mj");
	_MoveJoy->setOpacity(150);
	_MoveJoy->setVisible(false);
	this->addChild(_MoveJoy);

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

	max_touch = touch->getLocation();

	if (max_touch.x > Win_size.width *0.15)
	{
		umj->setPosition(Point(Mj_Touch_p));
		mj->setPosition(Point(Umj_Touch_p));

		umj->setVisible(true);
		mj->setVisible(true);
	}
	else
	{
		
	}
	return true;
}

void Joystick::onTouchMoved(Touch * touch, Event * unused_event)
{
	auto mj_p = (Sprite*)this->getChildByName("Joystick_mj");
	mj_p->setPosition(Point(touch->getLocation()));

	Mj_Touch_p = mj_p->getPosition();

	if (max_touch.x > Win_size.width *0.15)
	{
		Move_p_joy1 = Mj_Touch_p - Umj_Touch_p;
		Move_p_joy2 = Move_p_joy1.getNormalized();
	}
}

void Joystick::onTouchEnded(Touch * touch, Event * unused_event)
{
	auto umj = (Sprite*)this->getChildByName("Joystick_umj");
	auto mj = (Sprite*)this->getChildByName("Joystick_mj");

	Move_p_joy2 = Vec2::ZERO;

	umj->setVisible(false);
	mj->setVisible(false);
}
