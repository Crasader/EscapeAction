#include "player.h"

player::~player()
{
}

bool player::init()
{
	rc = Rect(0, 0, 0, 0);
	speed = 5;
	plyer = Sprite::create("player.png");
	this->addChild(plyer);
	plyer_size = plyer->getContentSize();
	win_size = Director::getInstance()->getWinSize();
	plyer->setName("player_move");
	plyer->setPosition(Vec2(win_size.width*0.5f, win_size.height*0.5f));

	oncheck = false;

	return true;
}

void player::setRect(Rect back_rc)
{
	rc = back_rc;
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
