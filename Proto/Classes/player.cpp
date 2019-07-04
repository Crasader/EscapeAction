#include "player.h"

player::~player()
{
}

bool player::init()
{
	_camera = NULL;
	delayAfterimg = 0;
	//test
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_1(player::onPress, this);
	listener->onKeyReleased = CC_CALLBACK_1(player::onRelease, this);

	 _eventDispatcher->addEventListenerWithFixedPriority(listener, 1);



	rc = Rect(0, 0, 0, 0);
	speed = 5;

	oncheck = false;

	win_size = Director::getInstance()->getWinSize();

	_player = Sprite::create("I0.png");
	_player->setAnchorPoint(Vec2(0,0));
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
	auto player_animetion_move = UIManager::getInstance()->get_Player_m_p2()*3;
	int move = 3;
	//CCLOG("_p %f", _player->getPositionX());

	if (player_animetion_move.x > 0)
	{
		if (playerState != RMOVE)
		{
			playerState = RMOVE;
			oncheck = true;
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
		}
		//if (_player->getPositionX() > -780){
			_player->setPosition(_player->getPosition() - (Point(move, 0)));
		//}
	}
	else
	{
		if (playerState != IDLE)
		{
			playerState = IDLE;
			oncheck = true;
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

			this->schedule(schedule_selector(player::afterImage));
			
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

void player::afterImage(float dt)
{
	if (playerState != LMOVE) {
		delayAfterimg = 0;
		unscheduleAllSelectors();
		return;
	}else if (_player_anime->getDelayPerUnit()<=delayAfterimg) {
		delayAfterimg = 0;
		Sprite* spr = Sprite::createWithSpriteFrame(_player->getDisplayFrame());
		spr->setAnchorPoint(Vec2(0, 0));
		spr->setPosition(_player->getPosition());
		spr->setFlipX(true);
		//action
		float time = 0.5;
		DelayTime* delay = DelayTime::create(time);
		FadeOut* fade = FadeOut::create(time);
		RemoveSelf* remove = RemoveSelf::create();
		Spawn* spw = Spawn::create(delay, fade, NULL);
		Sequence* seq = Sequence::create(spw, remove, NULL);
		this->addChild(spr,-1);
		spr->runAction(seq);
		spr->setCameraMask(_camera->getCameraMask());
	}
	else {
		delayAfterimg += dt*2;
	}
}
