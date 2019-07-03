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
	_player->setScale(3.5);
	this->addChild(_player);
	_player->setName("player_ani");

	_player_anime = Animation::create();
	_player_anime->setDelayPerUnit(0.5f);
	_player_anime->addSpriteFrameWithFile("I1.png");
	_player_anime->addSpriteFrameWithFile("I0.png");

	_player_animat = Animate::create(_player_anime);
	rep_player = RepeatForever::create(_player_animat);
	_player->runAction(rep_player);

	s_check = false;

	_UIM = UIManager::getInstance();
	return true;
}

void player::setRect(Rect back_rc)
{
	rc = back_rc;
}

void player::Joy_move_check()
{
	auto player_animetion_move = UIManager::getInstance()->get_Player_m_p1();
	atk_check = UIManager::getInstance()->getAttack_btn();
	s_check = UIManager::getInstance()->getSearch_btn();

	CCLOG("_playerState %d", _playerState);
	CCLOG("s_check %d", s_check);
	CCLOG("oncheck %d", oncheck);
	CCLOG("atk_check %d", atk_check);

	if (atk_check == true)
	{
		_playerState = ATTACK;
		UIManager::getInstance()->setAttack_btn(false);
		oncheck = true;
	}
	else if (s_check == true)
	{
		_playerState = SEARCH;
		UIManager::getInstance()->setSearch_btn(false);
		oncheck = true;
	}
	else if (player_animetion_move.x > 0)
	{
		if (_playerState != RMOVE)
		{
			_playerState = RMOVE;
			oncheck = true;
		}
		if (_player->getPositionX() < 780)
		{
			_player->setPosition(_player->getPosition() + (Point(10, 0)));
		}
	}
	else if (player_animetion_move.x < 0)
	{
		if (_playerState != LMOVE)
		{
			_playerState = LMOVE;
			oncheck = true;
		}
		if (_player->getPositionX() > -780)
		{
			_player->setPosition(_player->getPosition() - (Point(10, 0)));
		}
	}
	else if (player_animetion_move.x == 0 && _playerState != ATTACK && _playerState != SEARCH)
	{
		if (_playerState != IDLE)
		{
			_playerState = IDLE;
			oncheck = true;
		}
	}
	else
	{
	}

	if (oncheck == true)
	{
		switch (_playerState)
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
			RL_Flip = true;
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
			RL_Flip = false;
			break;
		case ATTACK:
		{
			_player->stopAllActions();
			_player->setFlipX(RL_Flip);

			_player_anime = Animation::create();
			_player_anime->setDelayPerUnit(0.075f);

			_player_anime->addSpriteFrameWithFile("a0.png");
			_player_anime->addSpriteFrameWithFile("a1.png");
			_player_anime->addSpriteFrameWithFile("a2.png");
			_player_anime->addSpriteFrameWithFile("a3.png");
			_player_anime->addSpriteFrameWithFile("a4.png");
			_player_anime->addSpriteFrameWithFile("a5.png");
			_player_anime->addSpriteFrameWithFile("a6.png");

			_player_animat = Animate::create(_player_anime);

			Sequence* A_player = Sequence::create(_player_animat, CallFunc::create(CC_CALLBACK_0(player::pause_ani, this)), NULL);

			_player->runAction(A_player);

			oncheck = false;
			break;
		}
		case SEARCH:
		{
			_player->stopAllActions();
			_player->setFlipX(RL_Flip);

			_player_anime = Animation::create();
			_player_anime->setDelayPerUnit(0.1f);

			_player_anime->addSpriteFrameWithFile("s0.png");
			_player_anime->addSpriteFrameWithFile("s1.png");
			_player_anime->addSpriteFrameWithFile("s2.png");
			_player_anime->addSpriteFrameWithFile("s1.png");
			_player_anime->addSpriteFrameWithFile("s0.png");

			_player_animat = Animate::create(_player_anime);

			Sequence* S_player = Sequence::create(_player_animat, CallFunc::create(CC_CALLBACK_0(player::pause_ani, this)), NULL);

			_player->runAction(S_player);

			oncheck = false;
			break;
		}
		}
	}
}

void player::pause_ani()
{
	_playerState = IDLE;
	oncheck = true;
}
