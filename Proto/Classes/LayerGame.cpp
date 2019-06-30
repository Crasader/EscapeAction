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

	rm = Room::create();
	this->addChild(rm);
	//JSONtest 클래스 생성
	jt = JSONtest::create();
	this->addChild(jt);
	//drawField
	DrawField* df = DrawField::create();
	this->addChild(df);

	pyer = player::create();
	this->addChild(pyer);

	Size winSize = Director::getInstance()->getWinSize();
	camera = Camera::createPerspective(60, (GLfloat)winSize.width / winSize.height, 1, 1000);
	camera->setCameraFlag(CameraFlag::USER1);
	camera->setName("camera_main");
	this->addChild(camera);
	camera->setPosition3D(Vec3(0, 0, 200));

	this->setCameraMask((unsigned short)CameraFlag::USER1, true);

	camera_move = Vec2(0, 0);
	//스케쥴 실행
	this->scheduleUpdate();

    return true;
}

void LayerGame::update(float dt)
{
	int move = 5;
	pyer->Joy_move_check();

	pos = pyer->getChildByName("player_ani")->getPosition();
	auto camera_m = this->getChildByName("camera_main");

//	CCLOG("%f %f", camera_move.x,pos.x);
	camera->setPosition(pos);
	/*if (camera_move.x > 0)
	{
		if (playerState_move_camera != RMOVE)
		{
			playerState_move_camera = RMOVE;
			camera_check = true;
		}
		if (camera->getPositionX() < win_size.x*0.17)
		{
			if (pos.x > -220)
			camera->setPosition(camera->getPosition() + (Point(move, 0)));
		}
		else
		{
			
		}
	}
	else if (camera_move.x < 0)
	{
		if (playerState_move_camera != LMOVE)
		{
			playerState_move_camera = LMOVE;
			camera_check = true;
		}
		if (camera->getPositionX() > -win_size.x*0.17)
		{
			if(pos.x < 220)
			camera->setPosition(camera->getPosition() - (Point(move, 0)));
		}
		else
		{
			
		}
	}
	else
	{
		if (playerState_move_camera != IDLE)
		{
			playerState_move_camera = IDLE;
			camera_check = true;
		}
	}
	/*if (camera->getPositionX() > win_size.x*0.3)
	{
		pyer->setPosition(pyer->getPosition() - (Point(10, 0)));
	}
	else if (camera->getPositionX() < win_size.x*0.7)
	{
		pyer->setPosition(pyer->getPosition() + (Point(10, 0)));
	}*/


	//camera_move = UIManager::getInstance()->get_Player_m_p1();
}


