#include "LayerGame.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

bool LayerGame::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

	win_size = Director::getInstance()->getWinSize();

	//플레이어 생성
	player = Sprite::create("CloseNormal.png");
	player->setPosition(Point(win_size.width * 0.5, win_size.height * 0.5));
	this->addChild(player);
	
	//키보드 입력 생성
	auto keyboard_lis = EventListenerKeyboard::create();
	keyboard_lis->onKeyPressed = CC_CALLBACK_1(LayerGame::onPress, this);
	keyboard_lis->onKeyReleased = CC_CALLBACK_1(LayerGame::onRelease, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboard_lis, this);

	//버튼 생성
	Button = Sprite::create("CloseNormal.png");
	Button->setPosition(Point(win_size.width * 0.05, win_size.height * 0.5));
	this->addChild(Button);

	//this is Player branch!
	/*
	auto joystick1 = Sprite::create("noname.png");
	joystick1->setPosition(win_size.width * 0.8, win_size.height *0.2);
	//sprite->setScale(1);
	joystick1->setOpacity(100);
	_joystickPad = joystick1;
	this->addChild(joystick1);

	auto joystick2 = Sprite::create("noname.png");
	joystick2->setPosition(win_size.width * 0.8, win_size.height * 0.2);
	//joystick2->setScale(PADSIZE);
	joystick2->setOpacity(150);
	_joystick = joystick2;
	this->addChild(joystick2);
	

	_startPoint = Point(win_size.width * 0.8, win_size.height * 0.2);
	_joystickTouched = false;*/

    return true;
}

void LayerGame::onPress(EventKeyboard::KeyCode code)
{
	switch (code)
	{
	case cocos2d::EventKeyboard::KeyCode::KEY_A:
		this->schedule(schedule_selector(LayerGame::Move_L), 0.005);
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_D:
		this->schedule(schedule_selector(LayerGame::Move_R), 0.005);
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_S:
		this->schedule(schedule_selector(LayerGame::Move_D), 0.005);
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_W:
		this->schedule(schedule_selector(LayerGame::Move_U), 0.005);
		break;
	default:
		break;
	}
}

void LayerGame::onRelease(EventKeyboard::KeyCode code)
{
	switch (code)
	{
	case cocos2d::EventKeyboard::KeyCode::KEY_A:
		this->unschedule(schedule_selector(LayerGame::Move_L));
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_D:
		this->unschedule(schedule_selector(LayerGame::Move_R));
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_S:
		this->unschedule(schedule_selector(LayerGame::Move_D));
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_W:
		this->unschedule(schedule_selector(LayerGame::Move_U));
		break;
	default:
		break;
	}
}

void LayerGame::Move_R(float dt)
{
	if (player->getPosition().x + player->getContentSize().width * 0.5 >= win_size.width) //화면 안나가게
		return;
	Point temp_pos = Point(player->getPosition().x + 1, player->getPosition().y);
	player->setPosition(temp_pos);
}

void LayerGame::Move_L(float dt)
{
	if (player->getPosition().x - player->getContentSize().width * 0.5 <= 0) //화면 안나가게
		return;
	Point temp_pos = Point(player->getPosition().x - 1, player->getPosition().y);
	player->setPosition(temp_pos);
}

void LayerGame::Move_U(float dt)
{
	if (player->getPosition().y + player->getContentSize().height * 0.5 >= win_size.height) //화면 안나가게
		return;
	Point temp_pos = Point(player->getPosition().x, player->getPosition().y + 1);
	player->setPosition(temp_pos);
}

void LayerGame::Move_D(float dt)
{
	if (player->getPosition().y - player->getContentSize().height * 0.5 <= 0) //화면 안나가게
		return;
	Point temp_pos = Point(player->getPosition().x, player->getPosition().y - 1);
	player->setPosition(temp_pos);
}
void LayerGame::createButton()
{
	//auto nomalButton;
}
/*
void LayerGame::initPad()
{
}

void LayerGame::create(Layer* layer, Point point)
{
}

Point LayerGame::getDPoint()
{
	_joystickPoint = _joystick->getPosition();
	_dPoint.x = (_joystickPoint.x - _startPoint.x) / ((_joystickPad->getContentSize().width / 2));
	_dPoint.y = (_joystickPoint.y - _startPoint.y) / ((_joystickPad->getContentSize().width / 2));
	return _dPoint;
}

float LayerGame::getDLength()
{
	_joystickPoint = _joystick->getPosition();

	return _dLength = sqrtf((_startPoint.x - _joystickPoint.x) * (_startPoint.x - _joystickPoint.x) + (_startPoint.y - _joystickPoint.y) * (_startPoint.y - _joystickPoint.y)) / ((_joystickPad->getContentSize().width / 2));
}

void LayerGame::TouchesBegan(const std::vector<Touch*>& touches, Event* unused_event)
{
	std::vector<Touch*>::const_iterator it = touches.begin();
	Touch* touch;
	Point tap;

	for (int i = 0; i < touches.size(); i++) {
		touch = (Touch*)(*it);
		if (touch) {
			tap = touch->getLocation();

			if (_joystickPad->getBoundingBox().containsPoint(tap) && _joystickTouched == false) {

				_joystick->setPosition(touch->getLocation());
				_joystickTouched = true;
			}
		}
		it++;
	}
}

void LayerGame::TouchesMoved(const std::vector<Touch*>& touches, Event* unused_event)
{
	std::vector<Touch*>::const_iterator it = touches.begin();
	Touch* touch;
	Point tap;
	Point ntap;

	if (_joystickTouched) {

		for (int i = 0; i < touches.size(); i++) {

			touch = (Touch*)(*it);
			if (touch) {
				tap = touch->getLocation();

				if (tap.x > _startPoint.x + (_joystickPad->getContentSize().width / 2)  ) {
					ntap.x = _startPoint.x + (_joystickPad->getContentSize().width / 2)  ;
				}
				else if (tap.x < _startPoint.x - (_joystickPad->getContentSize().width / 2) ) {
					ntap.x = _startPoint.x - (_joystickPad->getContentSize().width / 2) ;
				}
				else {
					ntap.x = tap.x;
				}



				if (tap.y > _startPoint.y + (_joystickPad->getContentSize().height / 2) ) {
					ntap.y = _startPoint.y + (_joystickPad->getContentSize().height / 2) ;
				}
				else if (tap.y < _startPoint.y - (_joystickPad->getContentSize().height / 2)) {
					ntap.y = _startPoint.y - (_joystickPad->getContentSize().height / 2) ;
				}
				else {
					ntap.y = tap.y;
				}


				_joystick->setPosition(ntap);



			}
			it++;
		}
	}
}

void LayerGame::TouchesEnded(const std::vector<Touch*>& touches, Event* unused_event)
{
	_joystick->setPosition(_startPoint);
	_joystickTouched = false;
}

void LayerGame::TouchesCancelled(const std::vector<Touch*>& touches, Event* unused_event)
{
	_joystick->setPosition(_startPoint);
	_joystickTouched = false;
}
*/