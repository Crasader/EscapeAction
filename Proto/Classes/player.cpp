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
	oncheck = false;

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
	if (keyDown&&plyer->getPositionY() > rc.getMinY() + plyer_size.height*0.5f) {
		plyer->setPositionY(plyer->getPositionY() - speed);
	}

	if (keyLeft&&plyer->getPositionX() > rc.getMinX() + plyer_size.width*0.5f) {
		plyer->setPositionX(plyer->getPositionX() - speed);
	}
	if (keyRight&&plyer->getPositionX() < rc.getMaxX() - plyer_size.width*0.5f) {
		plyer->setPositionX(plyer->getPositionX() + speed);
	}

	//가구충돌체크
	check();
	
	//조이스틱
	Move_joy_player = UIManager::getInstance()->get_Player_m_p();

	if (Move_joy_player != Vec2::ZERO)
	{
		if (Move_joy_player.y > 0 && plyer->getPositionY() < rc.getMaxY() - plyer_size.height*0.5f)
		{
			plyer->setPositionY((plyer->getPositionY() + Move_joy_player.y)+ speed);
		}
		if (Move_joy_player.y < 0 && plyer->getPositionY() > rc.getMinY() + plyer_size.height*0.5f)
		{
			plyer->setPositionY((plyer->getPositionY() + Move_joy_player.y)- speed);
		}
		if (Move_joy_player.x < 0 && plyer->getPositionX() > rc.getMinX() + plyer_size.height*0.5f)
		{
			plyer->setPositionX((plyer->getPositionX() + Move_joy_player.x)- speed);
		}
		if (Move_joy_player.x > 0 && plyer->getPositionX() < rc.getMaxX() - plyer_size.height*0.5f)
		{
			plyer->setPositionX((plyer->getPositionX() + Move_joy_player.x)+speed);
		}
	}
}

void player::check()
{
	auto player_bounding = (Sprite*)this->getChildByName("player_move");

	if (player_bounding->getPosition() < win_size*0.5)
	{
		if (oncheck == false)
		{
			UIManager::getInstance()->setEnable_AtkBtn(true);
			oncheck = true;
		}
	}
	else if(player_bounding->getPosition() > win_size*0.5)
	{
		UIManager::getInstance()->setEnable_AtkBtn(false);
		oncheck = false;
	}
}

void player::Joy_move_check()
{
	auto player_bounding = (Sprite*)this->getChildByName("player_move");
}
