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

	pyer = player::create();
	this->addChild(pyer);

	Size winSize = Director::getInstance()->getWinSize();
	camera = Camera::createPerspective(60, (GLfloat)winSize.width / winSize.height, 1, 1000);
	camera->setCameraFlag(CameraFlag::USER1);
	camera->setName("camera_main");
	this->addChild(camera);
	pos = pyer->getChildByName("player_ani")->getPosition();
	camera->setPosition3D(Vec3(pos.x, pos.y, 800));

	this->setCameraMask((unsigned short)CameraFlag::USER1, true);

	camera_move = Vec2(0, 0);
	//½ºÄÉÁì ½ÇÇà
	this->scheduleUpdate();

	
    return true;
}

void LayerGame::update(float dt)
{
	pyer->Joy_move_check();

	auto camera_m = this->getChildByName("camera_main");

	if (camera_move.x > 0)
	{
		if (playerState_move_camera != RMOVE)
		{
			playerState_move_camera = RMOVE;
			camera_check = true;
		}
		if (camera->getPositionX() < win_size.x*0.7)
		{
			camera->setPosition(camera->getPosition() + (Point(10, 0)));
		}

	}
	else if (camera_move.x < 0)
	{
		if (playerState_move_camera != LMOVE)
		{
			playerState_move_camera = LMOVE;
			camera_check = true;
		}
		if (camera->getPositionX() > win_size.x*0.3)
		{
			camera->setPosition(camera->getPosition() - (Point(10, 0)));
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
	camera_move = UIManager::getInstance()->get_Player_m_p1();
}


