#include "player.h"

player::~player()
{
}

bool player::init()
{
	check_fur = false;
	_camera = NULL;
	delayAfterimg = 0;
	_floor = 0;
	_roomNum = 0;/*캐릭터 초기 위치 받아오기*/
	playerState = IDLE;
	_door = NULL;
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

	_player->setPosition(0,0);

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

	SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/background_rain.mp3", true);
	Point Lightpos = win_size * 0.5*0.5;
	Lightpos.y -= _player->getContentSize().height*0.5;
	_shadowLayer = ShadowLayer::create();
	_shadowLayer->setAnchorPoint(Vec2(0.5, 0.5));
	_shadowLayer->setLightPosition(Lightpos);
	lightSize = _player->getContentSize().height*1.9;
	_shadowLayer->setLightSize(fabs(lightSize));
	this->addChild(_shadowLayer);
	return true;
}

void player::ani_pause()
{
	playerState = NONE;
	setState(IDLE);
	log("ani_pause %d", playerState);
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

void player::Joy_move_check(float _firstPos, float _lastPos)
{
	
	if (playerState != player_Move_enum::OPEN) {//캐릭터가 문여는 상태 아닐때, 방 못나가게
		if (_player->getPositionX() > _lastPos - (plyer_size.width*0.5) - 6) {
			_player->setPositionX(_lastPos - (plyer_size.width*0.5) - 6);
		}
		else if (_player->getPositionX() < _firstPos + (plyer_size.width*0.5) + 6) {
			_player->setPositionX(_firstPos + (plyer_size.width*0.5) + 6);
		}
	}
	//shadowLayer 이동
	_shadowLayer->setPosition(Vec2(_player->getPositionX()- (win_size.width*0.5), _player->getPositionY()- (win_size.height*0.5)));
	//player_animetion_move = UIManager::getInstance()->get_Player_m_p2() * 3;

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
		setState(UMOVE);
	}
	if (key == EventKeyboard::KeyCode::KEY_A)
	{
		_shadowLayer->setLightSize(fabs(1000));
	}

}

void player::onRelease(EventKeyboard::KeyCode key)
{
	if (key == EventKeyboard::KeyCode::KEY_A)
	{
		_shadowLayer->setLightSize(fabs(lightSize));
	}
}

//void player::afterImage(float dt)
//{
//	if (playerState != LMOVE) {
//		delayAfterimg = 0;
//		unscheduleAllSelectors();
//		return;
//	}else if (_player_anime->getDelayPerUnit()<=delayAfterimg) {
//		delayAfterimg = 0;
//		Sprite* spr = Sprite::createWithSpriteFrame(_player->getDisplayFrame());
//		spr->setAnchorPoint(Vec2(0, 0));
//		spr->setPosition(_player->getPosition());
//		spr->setFlipX(true);
//		//action
//		float time = 0.5;
//		DelayTime* delay = DelayTime::create(time);
//		FadeOut* fade = FadeOut::create(time);
//		RemoveSelf* remove = RemoveSelf::create();
//		Spawn* spw = Spawn::create(delay, fade, NULL);
//		Sequence* seq = Sequence::create(spw, remove, NULL);
//		this->addChild(spr,-1);
//		spr->runAction(seq);
//		spr->setCameraMask(_camera->getCameraMask());
//	}
//	else {
//		delayAfterimg += dt*2;
//	}
//}

int player::getRoomNum()
{
	return _roomNum;
}

void player::setRoomNum(int roomNum)
{
	_roomNum = roomNum;
}

int player::getFloor()
{
	return _floor;
}

void player::setFloor(int floor)
{
	_floor = floor;
}
player_Move_enum player::getState()
{
	return playerState;
}

bool player::setState(player_Move_enum state)
{
	/*조건문*/
	//현재 state가 바껴도 되는 state인가?
	//이미 실행중인 state는 아닌가?
	//그렇다면 return false;
	//위 조건이 아니라면 아래로 진행
	
	if (playerState == state)
	{
		return false;
	}
	if (playerState != RMOVE && playerState != LMOVE && playerState != IDLE&&playerState!=NONE) {

		return false;
	}
	playerState = state;
	log("state %d", playerState);
	SimpleAudioEngine::getInstance()->stopAllEffects();
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
	{
		RL_filp = true;
		_player->stopAllActions();
		_player->setFlipX(RL_filp);
		ani_move();
		Spawn* A_player = Spawn::create(_player_animat, MoveBy::create(0.75, Point(-80, 0)), NULL);
		rep_player = RepeatForever::create(A_player);
		_player->runAction(rep_player);
		SimpleAudioEngine::getInstance()->playEffect("sound/walking_sound.wav",true);
		break;
	}
	case RMOVE:
	{
		log("rMove");
		RL_filp = false;
		_player->stopAllActions();
		_player->setFlipX(RL_filp);
		ani_move();
		Spawn* A_player = Spawn::create(_player_animat, MoveBy::create(0.75, Point(80, 0)), NULL);
		rep_player = RepeatForever::create(A_player);
		_player->runAction(rep_player);
		auto walk = SimpleAudioEngine::getInstance()->playEffect("sound/walking_sound.wav", true);
		break;
	}
	case ATTACK:
	{
		atk_ran = RandomHelper::random_int(0, 2);
		if (atk_ran == 0)
		{
			make_atk_ani();

			Sequence* A_player = Sequence::create(p_f_atk, CallFunc::create(CC_CALLBACK_0(player::ani_pause, this)), NULL);

			_player->runAction(A_player);

			SimpleAudioEngine::getInstance()->playEffect("sound/attak1.mp3");
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
			SimpleAudioEngine::getInstance()->playEffect("sound/attak2.mp3");
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
			SimpleAudioEngine::getInstance()->playEffect("sound/attak3.mp3");
			break;
		}
	}
	case SEARCH:
	{
		SimpleAudioEngine::getInstance()->playEffect("sound/Sreach_sound.mp3", true);
		//SimpleAudioEngine::getInstance()->playEffect("sound/Sreach_sound1.mp3", true);
		SimpleAudioEngine::getInstance()->playEffect("sound/Sreach_sound2.mp3", true);
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
		SimpleAudioEngine::getInstance()->playEffect("sound/opendoor.mp3", true);
		_player->stopAllActions();
		

		_player_anime = Animation::create();
		_player_anime->setDelayPerUnit(0.15f);

		_player_anime->addSpriteFrameWithFile("op0.png");
		_player_anime->addSpriteFrameWithFile("op1.png");
		_player_anime->addSpriteFrameWithFile("op2.png");
		_player_anime->addSpriteFrameWithFile("op3.png");
		_player_anime->addSpriteFrameWithFile("op2.png");
		_player_anime->addSpriteFrameWithFile("op1.png");
		
		/*_player_anime->addSpriteFrameWithFile("op4.png");
		_player_anime->addSpriteFrameWithFile("op5.png");
		_player_anime->addSpriteFrameWithFile("op6.png");
		_player_anime->addSpriteFrameWithFile("op7.png");
		_player_anime->addSpriteFrameWithFile("op8.png");*/
		//문 텍스처 바꾸기
		_door->setTexture("door/door2.png");
		float distance = _door->getPositionX() - _player->getPositionX();
		distance = distance > 0 ? 20 : -20;
		RL_filp = distance > 0 ? false : true;//true 왼쪽
		//문쪽을 향하도록 filp
		_door->setFlipX(RL_filp);
		_player->setFlipX(RL_filp);

		_player_animat = Animate::create(_player_anime);
		Spawn* O_player = Spawn::create(_player_animat, MoveTo::create(1,Vec2(_door->getPositionX()+distance,_player->getPositionY())), NULL);
		CallFunc* closeDoor = CallFunc::create(CC_CALLBACK_0(player::returnDoorTexture, this));
		Sequence* OD_player = Sequence::create(O_player, closeDoor, CallFunc::create(CC_CALLBACK_0(player::ani_pause, this)), NULL);
		_player->runAction(OD_player);

		break;
	}
	case UMOVE:
	{
		SimpleAudioEngine::getInstance()->playEffect("sound/UDsound.mp3", true);
		UIManager::getInstance()->setEnable_AtkBtn(false);
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
	case DMOVE:
	{

		UIManager::getInstance()->setEnable_AtkBtn(false);
		_player->stopAllActions();
		_player->setFlipX(RL_filp);
		_player_anime = Animation::create();
		_player_anime->setDelayPerUnit(0.15f);

		_player_anime->addSpriteFrameWithFile("U5.png");
		_player_anime->addSpriteFrameWithFile("U4.png");
		_player_anime->addSpriteFrameWithFile("U3.png");
		_player_anime->addSpriteFrameWithFile("U2.png");
		_player_anime->addSpriteFrameWithFile("U1.png");
		_player_anime->addSpriteFrameWithFile("U0.png");

		_player_animat = Animate::create(_player_anime);

		_player_UD_anime = Animation::create();
		_player_UD_anime->setDelayPerUnit(0.12f);

		_player_UD_anime->addSpriteFrameWithFile("ue1.png");
		_player_UD_anime->addSpriteFrameWithFile("ue0.png");

		_player_UD_animat = Animate::create(_player_UD_anime);

		_player_E_anime = Animation::create();
		_player_E_anime->setDelayPerUnit(0.1f);

		//_player_E_anime->addSpriteFrameWithFile("ue8copy.png");
		//_player_E_anime->addSpriteFrameWithFile("ue7copy.png");
		//_player_E_anime->addSpriteFrameWithFile("ue6copy.png");
		_player_E_anime->addSpriteFrameWithFile("ue5.png");
		_player_E_anime->addSpriteFrameWithFile("ue4.png");
		_player_E_anime->addSpriteFrameWithFile("ue3.png");
		_player_E_anime->addSpriteFrameWithFile("ue2.png");

		_player_E_animat = Animate::create(_player_E_anime);

		Spawn* U_player = Spawn::create(_player_animat, MoveBy::create(0.9, Point(0, -65)), NULL);
		Spawn* E_player = Spawn::create(_player_E_animat, MoveBy::create(0.5, Point(0, -55)), NULL);

		Sequence* UE_player = Sequence::create(E_player, _player_UD_animat, U_player, CallFunc::create(CC_CALLBACK_0(player::ani_pause, this)), NULL);

		_player->runAction(UE_player);
		break;
	}
	default:
		break;
	}
	
	/*state 관련 스위치문*/
	//return true
	return true;
}

float player::getPlayerSprPositionX()
{
	return _player->getPositionX();
}

void player::setPlayerSprPositionX(float posX)
{
	_player->setPositionX(posX);
}

void player::setContactDoorSpr(Sprite * contactDoor)
{
	_door = contactDoor;
}

Rect player::getRect()
{
	//가구 체크할 Rect 설정
	return _player->getBoundingBox();
}

void player::returnDoorTexture()
{
	_door->setTexture("door/door.png");
}

void player::set_RL_filp(bool RL)
{
	RL_filp = RL;
}

bool player::get_RL_filp()
{
	return RL_filp;
}
