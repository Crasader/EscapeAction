#include "player.h"

player::~player()
{
}

bool player::init()
{
	rc = Rect(0, 0, 0, 0);
	speed = 5;

	oncheck = false;

	win_size = Director::getInstance()->getWinSize();

	_player = Sprite::create("I0.png");
	this->addChild(_player);
	_player->setName("player_ani");
	_player->setPosition(Vec2(win_size.width*0.5f, win_size.height*0.5f));
	_player->setScale(3.5);

	_player_anime = Animation::create();
	_player_anime->setDelayPerUnit(0.5f);
	_player_anime->addSpriteFrameWithFile("I1.png");
	_player_anime->addSpriteFrameWithFile("I0.png");

	_player_animat = Animate::create(_player_anime);
	rep_player = RepeatForever::create(_player_animat);
	_player->runAction(rep_player);

	return true;
}

void player::setRect(Rect back_rc)
{
	rc = back_rc;
}


void player::check()
{
	auto player_bounding = (Sprite*)this->getChildByName("player_move");
	//가구 오브젝트랑 만나는것 체크
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
	auto player_animetion_move = UIManager::getInstance()->get_Player_m_p1();


	if (oncheck == false)
	{
		_player->stopAllActions();
		_player_anime = Animation::create();
		_player_anime->setDelayPerUnit(0.5f);

		_player_anime->addSpriteFrameWithFile("1.png");
		_player_anime->addSpriteFrameWithFile("2.png");
		_player_anime->addSpriteFrameWithFile("3.png");
		_player_anime->addSpriteFrameWithFile("4.png");
		_player_anime->addSpriteFrameWithFile("5.png");

		_player_animat = Animate::create(_player_anime);
		rep_player = RepeatForever::create(_player_animat);

		_player->runAction(rep_player);

		oncheck = true;
	}
	else
	{
		if (player_animetion_move.x < 0)
		{
			_player->stopAllActions();

			_player_anime = Animation::create();
			_player_anime->setDelayPerUnit(0.15f);

			_player_anime->addSpriteFrameWithFile("17.png");
			_player_anime->addSpriteFrameWithFile("18.png");
			_player_anime->addSpriteFrameWithFile("19.png");
			_player_anime->addSpriteFrameWithFile("18.png");

			_player_animat = Animate::create(_player_anime);
			rep_player = RepeatForever::create(_player_animat);

			_player->runAction(rep_player);
		}
		else if (player_animetion_move.x > 0)
		{
			_player->stopAllActions();

			_player_anime = Animation::create();
			_player_anime->setDelayPerUnit(0.15f);


			_player_anime->addSpriteFrameWithFile("5.png");
			_player_anime->addSpriteFrameWithFile("4.png");
			_player_anime->addSpriteFrameWithFile("3.png");
			_player_anime->addSpriteFrameWithFile("2.png");
			_player_anime->addSpriteFrameWithFile("1.png");
			_player_anime->addSpriteFrameWithFile("0.png");

			_player_animat = Animate::create(_player_anime);
			rep_player = RepeatForever::create(_player_animat);

			_player->runAction(rep_player);
		}
	}
}
