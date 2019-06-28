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
	//_player->setPosition(win_size*0.5);
	this->addChild(_player);
	_player->setName("player_ani");

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
	int move = 3;
	CCLOG("_p %f", _player->getPositionX());

	if (player_animetion_move.x > 0)
	{
		if (playerState != RMOVE)
		{
			playerState = RMOVE;
			oncheck = true;
		}
		if (_player->getPositionX() < 780)
		{
			_player->setPosition(_player->getPosition() + (Point(move, 0)));
		}
	}
	else if (player_animetion_move.x < 0)
	{
		if (playerState != LMOVE)
		{
			playerState = LMOVE;
			oncheck = true;
		}
		if (_player->getPositionX() > -780)
		{
			_player->setPosition(_player->getPosition() - (Point(move, 0)));
		}
	}
	else
	{
		if (playerState != IDLE)
		{
			playerState = IDLE;
			oncheck = true;
		}
	}

	

	if (oncheck == true)
	{
		switch (playerState)
		{
		case NONE:

			break;
		case IDLE:
			_player->stopAllActions();
			_player_anime = Animation::create();
			_player_anime->setDelayPerUnit(0.5f);

			_player_anime->addSpriteFrameWithFile("I1.png");
			_player_anime->addSpriteFrameWithFile("I0.png");

			_player_animat = Animate::create(_player_anime);
			rep_player = RepeatForever::create(_player_animat);

			_player->runAction(rep_player);

			oncheck = false;
			break;
		case LMOVE:
			_player->stopAllActions();
			_player->setFlipX(true);

			_player_anime = Animation::create();
			_player_anime->setDelayPerUnit(0.15f);


			_player_anime->addSpriteFrameWithFile("r5.png");
			_player_anime->addSpriteFrameWithFile("r4.png");
			_player_anime->addSpriteFrameWithFile("r3.png");
			_player_anime->addSpriteFrameWithFile("r2.png");
			_player_anime->addSpriteFrameWithFile("r1.png");
			_player_anime->addSpriteFrameWithFile("r0.png");

			_player_animat = Animate::create(_player_anime);
			rep_player = RepeatForever::create(_player_animat);

			_player->runAction(rep_player);

			oncheck = false;
			break;
		case RMOVE:
			_player->stopAllActions();
			_player->setFlipX(false);

			_player_anime = Animation::create();
			_player_anime->setDelayPerUnit(0.15f);

			_player_anime->addSpriteFrameWithFile("r5.png");
			_player_anime->addSpriteFrameWithFile("r4.png");
			_player_anime->addSpriteFrameWithFile("r3.png");
			_player_anime->addSpriteFrameWithFile("r2.png");
			_player_anime->addSpriteFrameWithFile("r1.png");
			_player_anime->addSpriteFrameWithFile("r0.png");

			_player_animat = Animate::create(_player_anime);
			rep_player = RepeatForever::create(_player_animat);

			_player->runAction(rep_player);
			oncheck = false;
			break;
		case SEARCH:

			break;
		default:
			break;
		}
	}
}
