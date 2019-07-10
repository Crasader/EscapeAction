#include "player.h"

player::~player()
{
}

bool player::init()
{
	check_fur = false;
	_camera = NULL;
	delayAfterimg = 0;
	_firstPos = 0;
	_lastPos = 0;

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

	_player->setPosition(50,0);

	this->addChild(_player);
	_player->setName("player_ani");
	plyer_size = _player->getContentSize();

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

void player::ani_pause()
{
	setState(IDLE);
	SimpleAudioEngine::getInstance()->stopAllEffects();
	UIManager::getInstance()->setEnable_AtkBtn(true);
}

void player::ani_move()
{
	_player_anime = Animation::create();
	_player_anime->setDelayPerUnit(0.125f);

	_player_anime->addSpriteFrameWithFile("rr0.png");
	_player_anime->addSpriteFrameWithFile("rr1.png");
	_player_anime->addSpriteFrameWithFile("rr2.png");
	_player_anime->addSpriteFrameWithFile("rr3.png");
	_player_anime->addSpriteFrameWithFile("rr4.png");
	_player_anime->addSpriteFrameWithFile("rr5.png");

	_player_animat = Animate::create(_player_anime);
}

void player::checkFur()
{
	/*	auto player_bounding = (Sprite*)this->getChildByName("player_move");
		//���� ������Ʈ�� �����°� üũ
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
		}*/
	if (playerState != player_Move_enum::SEARCH)
	{
		UIManager::getInstance()->setEnable_AtkBtn(false);
		oncheck = false;
	}

	if (playerState != player_Move_enum::SEARCH) {
		playerState = player_Move_enum::SEARCH;
		check_fur = true;
		oncheck = true;
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
	_player_anime->addSpriteFrameWithFile("pa5.png");
	_player_anime->addSpriteFrameWithFile("pa6.png");
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

bool player::getCheckFur()
{
	return check_fur;
}

void player::Joy_move_check()
{
	if (_player->getPositionX() > _lastPos - (plyer_size.width*0.5) - 6) {
		_player->setPositionX(_lastPos - (plyer_size.width*0.5) - 6);
	}
	else if (_player->getPositionX() < _firstPos + (plyer_size.width*0.5) + 6) {
		_player->setPositionX(_firstPos + (plyer_size.width*0.5) + 6);
	}

	//player_animetion_move = UIManager::getInstance()->get_Player_m_p2() * 3;

	//int move = 3;

	//atk_check = UIManager::getInstance()->get_atk_btn();
	//src_check = UIManager::getInstance()->get_src_btn();

	//_player->setFlippedX(get_RL_filp());//������ġ ����getset

	/*if (all_stop == false)
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
		}
		else if (player_animetion_move.x > 0|| player_fs_move==-1) {
			if (playerState != RMOVE)
			{
				playerState = RMOVE;
				oncheck = true;
				RL_filp = false;
				SimpleAudioEngine::getInstance()->playEffect("sound/walking_sound.wav", true);
			}
			if (_player->getPositionX() < _lastPos - (plyer_size.width*0.5) - 6){
				_player->setPosition(_player->getPosition() + (Point(move, 0)));
			}
		}
		else if (player_animetion_move.x < 0|| player_fs_move==1)
		{
			if (playerState != LMOVE)
			{
				playerState = LMOVE;
				oncheck = true;
				RL_filp = true;
				SimpleAudioEngine::getInstance()->playEffect("sound/walking_sound.wav", true);
			}
			if (_player->getPositionX() > _firstPos + (plyer_size.width*0.5) + 6){
				_player->setPosition(_player->getPosition() - (Point(move, 0)));
			}
		}
		else if (player_animetion_move.x == 0 && playerState != ATTACK && playerState != SEARCH)
		{
			if (playerState != IDLE)
			{
				playerState = IDLE;
				oncheck = true;
				SimpleAudioEngine::getInstance()->stopAllEffects();
			}
		}*/
	
	//if (oncheck == true)
	//{
	//	switch (playerState)
	//	{
	//	case NONE:

	//		break;
	//	case IDLE:
	//		_player->stopAllActions();
	//		_player_anime = Animation::create();
	//		_player_anime->setDelayPerUnit(0.5f);

	//		_player_anime->addSpriteFrameWithFile("I1.png");
	//		_player_anime->addSpriteFrameWithFile("I0.png");

	//		_player_animat = Animate::create(_player_anime);
	//		rep_player = RepeatForever::create(_player_animat);

	//		_player->runAction(rep_player);

	//		oncheck = false;
	//		break;
	//	case LMOVE:
	//		_player->stopAllActions();
	//		_player->setFlipX(RL_filp);

	//		_player_anime = Animation::create();
	//		_player_anime->setDelayPerUnit(0.125f);


	//		_player_anime->addSpriteFrameWithFile("rr0.png");
	//		_player_anime->addSpriteFrameWithFile("rr1.png");
	//		_player_anime->addSpriteFrameWithFile("rr2.png");
	//		_player_anime->addSpriteFrameWithFile("rr3.png");
	//		_player_anime->addSpriteFrameWithFile("rr4.png");
	//		_player_anime->addSpriteFrameWithFile("rr5.png");

	//		_player_animat = Animate::create(_player_anime);
	//		rep_player = RepeatForever::create(_player_animat);

	//		_player->runAction(rep_player);

	//		oncheck = false;
	//		break;
	//	case RMOVE:
	//		_player->stopAllActions();
	//		_player->setFlipX(RL_filp);

	//		_player_anime = Animation::create();
	//		_player_anime->setDelayPerUnit(0.125f);

	//		_player_anime->addSpriteFrameWithFile("rr0.png");
	//		_player_anime->addSpriteFrameWithFile("rr1.png");
	//		_player_anime->addSpriteFrameWithFile("rr2.png");
	//		_player_anime->addSpriteFrameWithFile("rr3.png");
	//		_player_anime->addSpriteFrameWithFile("rr4.png");
	//		_player_anime->addSpriteFrameWithFile("rr5.png");

	//		_player_animat = Animate::create(_player_anime);
	//		rep_player = RepeatForever::create(_player_animat);

	//		_player->runAction(rep_player);
	//		oncheck = false;
	//		break;
	//	case ATTACK:
	//	{
	//		atk_ran = RandomHelper::random_int(0, 2);
	//		if (atk_ran == 0)
	//		{
	//			make_atk_ani();

	//			Sequence* A_player = Sequence::create(p_f_atk, CallFunc::create(CC_CALLBACK_0(player::ani_pause, this)), NULL);

	//			_player->runAction(A_player);

	//			oncheck = false;
	//			break;
	//		}
	//		else if (atk_ran == 1)
	//		{
	//			_player->stopAllActions();
	//			_player->setFlipX(RL_filp);

	//			_player_anime = Animation::create();
	//			_player_anime->setDelayPerUnit(0.1f);

	//			_player_anime->addSpriteFrameWithFile("a6.png");
	//			_player_anime->addSpriteFrameWithFile("a5.png");
	//			_player_anime->addSpriteFrameWithFile("a4.png");
	//			_player_anime->addSpriteFrameWithFile("a3.png");
	//			_player_anime->addSpriteFrameWithFile("a2.png");
	//			_player_anime->addSpriteFrameWithFile("a1.png");
	//			_player_anime->addSpriteFrameWithFile("a0.png");
	//			_player_animat = Animate::create(_player_anime);

	//			Sequence* A_player = Sequence::create(_player_animat, CallFunc::create(CC_CALLBACK_0(player::ani_pause, this)), NULL);

	//			_player->runAction(A_player);

	//			oncheck = false;
	//			break;
	//		}
	//		else if (atk_ran == 2)
	//		{
	//			_player->stopAllActions();
	//			_player->setFlipX(RL_filp);

	//			_player_anime = Animation::create();
	//			_player_anime->setDelayPerUnit(0.1f);

	//			_player_anime->addSpriteFrameWithFile("a0.png");
	//			_player_anime->addSpriteFrameWithFile("a1.png");
	//			_player_anime->addSpriteFrameWithFile("a2.png");
	//			_player_anime->addSpriteFrameWithFile("a3.png");
	//			_player_anime->addSpriteFrameWithFile("a4.png");
	//			_player_anime->addSpriteFrameWithFile("a5.png");
	//			_player_anime->addSpriteFrameWithFile("a6.png");

	//			_player_animat = Animate::create(_player_anime);

	//			Sequence* A_player = Sequence::create(_player_animat, CallFunc::create(CC_CALLBACK_0(player::ani_pause, this)), NULL);

	//			_player->runAction(A_player);

	//			oncheck = false;
	//			break;
	//		}
	//	}
	//	case SEARCH:
	//	{
	//		SimpleAudioEngine::getInstance()->playEffect("sound/Search_soung.wav", true);
	//		_player->stopAllActions();
	//		_player->setFlipX(RL_filp);

	//		_player_anime = Animation::create();
	//		_player_anime->setDelayPerUnit(0.15f);

	//		/*_player_anime->addSpriteFrameWithFile("s0.png");
	//		_player_anime->addSpriteFrameWithFile("s1.png");
	//		_player_anime->addSpriteFrameWithFile("s2.png");
	//		_player_anime->addSpriteFrameWithFile("s3.png");
	//		_player_anime->addSpriteFrameWithFile("s4.png");
	//		_player_anime->addSpriteFrameWithFile("s2.png");
	//		_player_anime->addSpriteFrameWithFile("s3.png");
	//		_player_anime->addSpriteFrameWithFile("s4.png");*/

	//		_player_anime->addSpriteFrameWithFile("ds2.png");
	//		_player_anime->addSpriteFrameWithFile("ds1.png");
	//		_player_anime->addSpriteFrameWithFile("ds0.png");
	//		_player_anime->addSpriteFrameWithFile("ds3.png");
	//		_player_anime->addSpriteFrameWithFile("ds0.png");
	//		_player_anime->addSpriteFrameWithFile("ds1.png");
	//		_player_anime->addSpriteFrameWithFile("ds2.png");
	//		_player_anime->addSpriteFrameWithFile("ds1.png");
	//		_player_anime->addSpriteFrameWithFile("ds0.png");
	//		_player_anime->addSpriteFrameWithFile("ds3.png");
	//		_player_anime->addSpriteFrameWithFile("ds0.png");
	//		_player_anime->addSpriteFrameWithFile("ds1.png");

	//		_player_animat = Animate::create(_player_anime);

	//		Sequence* S_player = Sequence::create(_player_animat, CallFunc::create(CC_CALLBACK_0(player::ani_pause, this)), NULL);

	//		_player->runAction(S_player);

	//		oncheck = false;
	//		break;
	//	}
	//	default:
	//		break;
	//	}
	//}
}

void player::onPress(EventKeyboard::KeyCode key)
{
	if (key == EventKeyboard::KeyCode::KEY_UP_ARROW) {
		_player->setPositionY(_player->getPositionY() + 120);
	}
	if (key == EventKeyboard::KeyCode::KEY_DOWN_ARROW) {
		_player->setPositionY(_player->getPositionY() - 120);
	}
	if (key == EventKeyboard::KeyCode::KEY_SPACE)
	{
		if(playerState == IDLE)
		setState(ATTACK);
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

int player::getRoomNum()
{
	return _roomNum;
}

void player::setRoomNum(int roomNum)
{
	_roomNum = roomNum;
}

void player::setFirst(float first)
{
	_firstPos = first;
}

void player::setLast(float last)
{
	_lastPos = last;
}

player_Move_enum player::getState()
{
	return playerState;
}

bool player::setState(player_Move_enum state)
{
	/*���ǹ�*/
	//���� state�� �ٲ��� �Ǵ� state�ΰ�?
	//�̹� �������� state�� �ƴѰ�?
	//�׷��ٸ� return false;
	//�� ������ �ƴ϶�� �Ʒ��� ����
	
	if (playerState == state)
	{
		return false;
	}
	playerState = state;	
	switch (playerState)
	{
	case NONE:
		break;
	case IDLE:
	{
		_player->stopAllActions();
		_player->setFlipX(RL_filp);
		_player_anime = Animation::create();
		_player_anime->setDelayPerUnit(0.5f);

		_player_anime->addSpriteFrameWithFile("I1.png");
		_player_anime->addSpriteFrameWithFile("I0.png");

		_player_animat = Animate::create(_player_anime);
		rep_player = RepeatForever::create(_player_animat);

		_player->runAction(rep_player);
		break;
	}
	case LMOVE:
	{	RL_filp = true;
	_player->stopAllActions();
	_player->setFlipX(RL_filp);
	ani_move();
	Spawn* A_player = Spawn::create(_player_animat, MoveBy::create(0.75, Point(-80, 0)), NULL);
	rep_player = RepeatForever::create(A_player);
	_player->runAction(rep_player);
	break;
	}
	case RMOVE:
	{
		RL_filp = false;
		_player->stopAllActions();
		_player->setFlipX(RL_filp);
		ani_move();
		Spawn* A_player = Spawn::create(_player_animat, MoveBy::create(0.75, Point(80, 0)), NULL);
		rep_player = RepeatForever::create(A_player);
		_player->runAction(rep_player);
		break;
	}
	case ATTACK:
	{
		atk_ran = RandomHelper::random_int(0, 2);
		UIManager::getInstance()->setEnable_AtkBtn(false);
		if (atk_ran == 0)
		{
			make_atk_ani();

			Sequence* A_player = Sequence::create(p_f_atk, CallFunc::create(CC_CALLBACK_0(player::ani_pause, this)), NULL);

			_player->runAction(A_player);
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
			break;
		}
	}
	case SEARCH:
	{
		SimpleAudioEngine::getInstance()->playEffect("sound/Search_soung.wav", true);
		_player->stopAllActions();
		_player->setFlipX(RL_filp);

		_player_anime = Animation::create();
		_player_anime->setDelayPerUnit(0.15f);

		_player_anime->addSpriteFrameWithFile("ds2.png");
		_player_anime->addSpriteFrameWithFile("ds1.png");
		_player_anime->addSpriteFrameWithFile("ds0.png");
		_player_anime->addSpriteFrameWithFile("ds3.png");
		_player_anime->addSpriteFrameWithFile("ds0.png");
		_player_anime->addSpriteFrameWithFile("ds1.png");
		_player_anime->addSpriteFrameWithFile("ds2.png");
		_player_anime->addSpriteFrameWithFile("ds1.png");
		_player_anime->addSpriteFrameWithFile("ds0.png");
		_player_anime->addSpriteFrameWithFile("ds3.png");
		_player_anime->addSpriteFrameWithFile("ds0.png");
		_player_anime->addSpriteFrameWithFile("ds1.png");

		_player_animat = Animate::create(_player_anime);

		//Sequence* S_player = Sequence::create(_player_animat, CallFunc::create(CC_CALLBACK_0(player::ani_pause, this)), NULL);
		rep_player = RepeatForever::create(_player_animat);
		_player->runAction(rep_player);
		break;
	}
	case OPEN:
	{
		SimpleAudioEngine::getInstance()->playEffect("sound/Search_soung.wav", true);
		_player->stopAllActions();
		_player->setFlipX(RL_filp);

		_player_anime = Animation::create();
		_player_anime->setDelayPerUnit(0.15f);

		_player_anime->addSpriteFrameWithFile("op0.png");
		_player_anime->addSpriteFrameWithFile("op1.png");
		_player_anime->addSpriteFrameWithFile("op2.png");
		_player_anime->addSpriteFrameWithFile("op3.png");
		_player_anime->addSpriteFrameWithFile("op2.png");
		_player_anime->addSpriteFrameWithFile("op1.png");
		/*
		_player_anime->addSpriteFrameWithFile("op4.png");
		_player_anime->addSpriteFrameWithFile("op5.png");
		_player_anime->addSpriteFrameWithFile("op6.png");
		_player_anime->addSpriteFrameWithFile("op7.png");
		_player_anime->addSpriteFrameWithFile("op8.png");*/

		_player_animat = Animate::create(_player_anime);
		Spawn* O_player = Spawn::create(_player_animat, MoveBy::create(0.65, Point(10, 0)), NULL);
		Sequence* OD_player = Sequence::create(O_player, CallFunc::create(CC_CALLBACK_0(player::ani_pause, this)), NULL);
		_player->runAction(OD_player);

		break;
	}
	case UMOVE:
	{
		_player->stopAllActions();
		_player->setFlipX(RL_filp);
		_player_anime = Animation::create();
		_player_anime->setDelayPerUnit(0.15f);

		_player_anime->addSpriteFrameWithFile("U0.png");
		_player_anime->addSpriteFrameWithFile("U1.png");
		_player_anime->addSpriteFrameWithFile("U2.png");
		_player_anime->addSpriteFrameWithFile("U3.png");
		_player_anime->addSpriteFrameWithFile("U4.png");
		_player_anime->addSpriteFrameWithFile("U5.png");

		_player_animat = Animate::create(_player_anime);

		_player_UD_anime = Animation::create();
		_player_UD_anime->setDelayPerUnit(0.1f);

		_player_UD_anime->addSpriteFrameWithFile("ue0.png");
		_player_UD_anime->addSpriteFrameWithFile("ue1.png");
		_player_UD_anime->addSpriteFrameWithFile("ue2.png");
		_player_UD_anime->addSpriteFrameWithFile("ue3.png");
		_player_UD_anime->addSpriteFrameWithFile("ue4.png");
		

		_player_UD_animat = Animate::create(_player_UD_anime);

		_player_E_anime = Animation::create();
		_player_E_anime->setDelayPerUnit(0.1f);

		_player_E_anime->addSpriteFrameWithFile("ue5.png");
		_player_E_anime->addSpriteFrameWithFile("ue6.png");
		_player_E_anime->addSpriteFrameWithFile("ue7.png");
		_player_E_anime->addSpriteFrameWithFile("ue8.png");

		_player_E_animat = Animate::create(_player_E_anime);		

		Spawn* U_player = Spawn::create(_player_animat, MoveBy::create(0.9, Point(0, 65)), NULL);		
		Spawn* E_player = Spawn::create(_player_E_animat, MoveBy::create(0.4, Point(0, 55)), NULL);

		Sequence* UE_player = Sequence::create(U_player, _player_UD_animat, E_player, CallFunc::create(CC_CALLBACK_0(player::ani_pause, this)), NULL);

		_player->runAction(UE_player);
		break;
	}		
	default:
		break;
	}
	
	/*state ���� ����ġ��*/
	//return true
	return true;
}

Rect player::getRect()
{
	//���� üũ�� Rect ����
	return _player->getBoundingBox();
}

void player::set_RL_filp(bool RL)
{
	RL_filp = RL;
}

bool player::get_RL_filp()
{
	return RL_filp;
}
