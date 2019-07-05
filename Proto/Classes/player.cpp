#include "player.h"

player::~player()
{
}

bool player::init()
{
	//test
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_1(player::onPress, this);
	listener->onKeyReleased = CC_CALLBACK_1(player::onRelease, this);

	 _eventDispatcher->addEventListenerWithFixedPriority(listener, 1);
	 
	rc = Rect(0, 0, 0, 0);
	speed = 3;

	all_stop = false;
	oncheck = false;
	src_check = false;
	atk_check = false;

	win_size = Director::getInstance()->getWinSize();

	_player = Sprite::create("I0.png");
	_player->setAnchorPoint(Vec2(0.5,0));
	_player->setPosition(0,120);
	this->addChild(_player);
	_player->setName("player_ani");

	_player_anime = Animation::create();
	_player_anime->setDelayPerUnit(0.5f);
	_player_anime->addSpriteFrameWithFile("I1.png");
	_player_anime->addSpriteFrameWithFile("I0.png");

	_player_animat = Animate::create(_player_anime);
	rep_player = RepeatForever::create(_player_animat);
	_player->runAction(rep_player);

	_UIM = UIManager::getInstance();

	

	return true;
}

void player::setRect(Rect back_rc)
{
	rc = back_rc;
}

void player::ani_pause()
{
	playerState = IDLE;
	oncheck = true;
	all_stop = false;
	SimpleAudioEngine::getInstance()->stopAllEffects();
}

void player::ani_forward()
{
	if (RL_filp == true)
	{
		MoveBy::create(0.1, Point(_player->getPositionX()+50,0));
	}
}

void player::make_atk_ani()
{
	_player->stopAllActions();
	_player->setFlipX(RL_filp);

	_player_anime = Animation::create();
	_player_anime->setDelayPerUnit(0.1f);

	_player_anime->addSpriteFrameWithFile("pa0.png");
	_player_anime->addSpriteFrameWithFile("pa1.png");
	_player_anime->addSpriteFrameWithFile("pa2.png");
	_player_anime->addSpriteFrameWithFile("pa3.png");
	_player_anime->addSpriteFrameWithFile("pa4.png");
	//_player_anime->addSpriteFrameWithFile("tumyung.png");
	_player_anime->addSpriteFrameWithFile("pa5.png");
	/*_player_anime->addSpriteFrameWithFile("tumyung.png");
	_player_anime->addSpriteFrameWithFile("tumyung.png");
	_player_anime->addSpriteFrameWithFile("tumyung.png");
	_player_anime->addSpriteFrameWithFile("tumyung.png");
	_player_anime->addSpriteFrameWithFile("tumyung.png");
	_player_anime->addSpriteFrameWithFile("tumyung.png");
	_player_anime->addSpriteFrameWithFile("tumyung.png");*/
	_player_anime->addSpriteFrameWithFile("pa6.png");
	//_player_anime->addSpriteFrameWithFile("tumyung.png");
	_player_anime->addSpriteFrameWithFile("pa7.png");
	_player_anime->addSpriteFrameWithFile("pa8.png");
	_player_anime->addSpriteFrameWithFile("pa9.png");
	_player_anime->addSpriteFrameWithFile("pa5.png");
	_player_anime->addSpriteFrameWithFile("pa4.png");

	_player_animat = Animate::create(_player_anime);

	if (RL_filp == false)
	{
		auto P_M = MoveTo::create(1.0, Point(_player->getPositionX() + 50, _player->getPositionY()));
		auto Ease_pmb = EaseIn::create(P_M, 7.5);
		p_f_atk = Spawn::create(_player_animat, Ease_pmb, NULL);
	}
	else
	{
		auto P_M = MoveTo::create(1.0, Point(_player->getPositionX() - 50, _player->getPositionY()));
		auto Ease_pmb = EaseIn::create(P_M, 7.5);
		p_f_atk = Spawn::create(_player_animat, Ease_pmb, NULL);
	}
}

void player::Joy_move_check()
{
	auto player_animetion_move = UIManager::getInstance()->get_Player_m_p2()*3;
	int move = 3;

	atk_ran = RandomHelper::random_int(0, 1);

	atk_check = UIManager::getInstance()->get_atk_btn();
	src_check = UIManager::getInstance()->get_src_btn();

	//CCLOG("_p %f", _player->getPositionX());
	if (all_stop == false)
	{
		if (atk_check == true)
		{
			playerState = ATTACK;
			UIManager::getInstance()->set_atk_btn(false);
			oncheck = true;
			all_stop = true;
		}
		else if (src_check == true)
		{
			playerState = SEARCH;
			UIManager::getInstance()->set_src_btn(false);
			oncheck = true;
			if (playerState == SEARCH)
			{				
				SimpleAudioEngine::getInstance()->playEffect("sound/Search_soung.wav", true);
			}
		}
		else if (player_animetion_move.x > 0)
		{
			if (playerState != RMOVE)
			{
				playerState = RMOVE;
				oncheck = true;
				RL_filp = false;
				SimpleAudioEngine::getInstance()->playEffect("sound/walking_sound.wav", true);
			}
			//if (_player->getPositionX() < 780){
			_player->setPosition(_player->getPosition() + (Point(move, 0)));
			//}
		}
		else if (player_animetion_move.x < 0)
		{
			if (playerState != LMOVE)
			{
				playerState = LMOVE;
				oncheck = true;
				RL_filp = true;
				SimpleAudioEngine::getInstance()->playEffect("sound/walking_sound.wav", true);
			}
			//if (_player->getPositionX() > -780){
			_player->setPosition(_player->getPosition() - (Point(move, 0)));			
			//}
		}
		else if (player_animetion_move.x == 0 && playerState != ATTACK && playerState != SEARCH)
		{
			if (playerState != IDLE)
			{
				playerState = IDLE;
				oncheck = true;
				SimpleAudioEngine::getInstance()->stopAllEffects();
			}
		}

		//_player->setPosition(_player->getPosition() + player_animetion_move);

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
				_player->setFlipX(RL_filp);

				_player_anime = Animation::create();
				_player_anime->setDelayPerUnit(0.125f);


				_player_anime->addSpriteFrameWithFile("rr0.png");
				_player_anime->addSpriteFrameWithFile("rr1.png");
				_player_anime->addSpriteFrameWithFile("rr2.png");
				_player_anime->addSpriteFrameWithFile("rr3.png");
				_player_anime->addSpriteFrameWithFile("rr4.png");
				_player_anime->addSpriteFrameWithFile("rr5.png");

				_player_animat = Animate::create(_player_anime);
				rep_player = RepeatForever::create(_player_animat);

				_player->runAction(rep_player);

				oncheck = false;
				break;
			case RMOVE:
				_player->stopAllActions();
				_player->setFlipX(RL_filp);

				_player_anime = Animation::create();
				_player_anime->setDelayPerUnit(0.125f);

				_player_anime->addSpriteFrameWithFile("rr0.png");
				_player_anime->addSpriteFrameWithFile("rr1.png");
				_player_anime->addSpriteFrameWithFile("rr2.png");
				_player_anime->addSpriteFrameWithFile("rr3.png");
				_player_anime->addSpriteFrameWithFile("rr4.png");
				_player_anime->addSpriteFrameWithFile("rr5.png");

				_player_animat = Animate::create(_player_anime);
				rep_player = RepeatForever::create(_player_animat);

				_player->runAction(rep_player);
				oncheck = false;
				break;
			case ATTACK:
			{
				if (atk_ran == 0)
				{
					make_atk_ani();

					Sequence* A_player = Sequence::create(p_f_atk, CallFunc::create(CC_CALLBACK_0(player::ani_pause, this)), NULL);

					_player->runAction(A_player);

					oncheck = false;
					break;
				}
				else if (atk_ran == 1)
				{
					_player->stopAllActions();
					_player->setFlipX(RL_filp);

					_player_anime = Animation::create();
					_player_anime->setDelayPerUnit(0.1f);

					_player_anime->addSpriteFrameWithFile("a6.png");
					_player_anime->addSpriteFrameWithFile("a5.png");
					_player_anime->addSpriteFrameWithFile("a4.png");
					_player_anime->addSpriteFrameWithFile("a3.png");
					_player_anime->addSpriteFrameWithFile("a2.png");
					_player_anime->addSpriteFrameWithFile("a1.png");
					_player_anime->addSpriteFrameWithFile("a0.png");
					_player_animat = Animate::create(_player_anime);

					Sequence* A_player = Sequence::create(_player_animat, CallFunc::create(CC_CALLBACK_0(player::ani_pause, this)), NULL);

					_player->runAction(A_player);

					oncheck = false;
					break;
				}
				else if (atk_ran == 2)
				{
					_player->stopAllActions();
					_player->setFlipX(RL_filp);

					_player_anime = Animation::create();
					_player_anime->setDelayPerUnit(0.1f);

					_player_anime->addSpriteFrameWithFile("a0.png");
					_player_anime->addSpriteFrameWithFile("a1.png");
					_player_anime->addSpriteFrameWithFile("a2.png");
					_player_anime->addSpriteFrameWithFile("a3.png");
					_player_anime->addSpriteFrameWithFile("a4.png");
					_player_anime->addSpriteFrameWithFile("a5.png");
					_player_anime->addSpriteFrameWithFile("a6.png");

					_player_animat = Animate::create(_player_anime);

					Sequence* A_player = Sequence::create(_player_animat, CallFunc::create(CC_CALLBACK_0(player::ani_pause, this)), NULL);

					_player->runAction(A_player);

					oncheck = false;
					break;
				}
			}
			case SEARCH:
			{
				_player->stopAllActions();
				_player->setFlipX(RL_filp);

				_player_anime = Animation::create();
				_player_anime->setDelayPerUnit(0.15f);

				_player_anime->addSpriteFrameWithFile("s0.png");
				_player_anime->addSpriteFrameWithFile("s1.png");
				_player_anime->addSpriteFrameWithFile("s2.png");
				_player_anime->addSpriteFrameWithFile("s3.png");
				_player_anime->addSpriteFrameWithFile("s4.png");
				_player_anime->addSpriteFrameWithFile("s2.png");
				_player_anime->addSpriteFrameWithFile("s3.png");
				_player_anime->addSpriteFrameWithFile("s4.png");

				_player_animat = Animate::create(_player_anime);

				Sequence* S_player = Sequence::create(_player_animat, CallFunc::create(CC_CALLBACK_0(player::ani_pause, this)), NULL);

				_player->runAction(S_player);

				oncheck = false;
				break;
			}
			default:
				break;
			}
		}
	}
}

void player::onPress(EventKeyboard::KeyCode key)
{
	if (key == EventKeyboard::KeyCode::KEY_UP_ARROW) {
		_player->setPositionY(_player->getPositionY()+120);
	}
	if (key == EventKeyboard::KeyCode::KEY_DOWN_ARROW) {
		_player->setPositionY(_player->getPositionY() - 120);
	}
}

void player::onRelease(EventKeyboard::KeyCode key)
{
}
