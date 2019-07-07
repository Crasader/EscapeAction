#include "LayerGame.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

bool LayerGame::init()
{


	//LevelDataSet 클래스 생성, addChild 필요 없음
	LevelDataSet* levelData = LevelDataSet::create();

	//drawField
	DrawField* df = DrawField::create();
	this->addChild(df);
	//draw 장식
	DrawDeco* ddeco = DrawDeco::create();
	this->addChild(ddeco);
	//draw 가구
	dfur = DrawFurniture::create();
	this->addChild(dfur);
	//draw 구조
	DrawStruct* ds = DrawStruct::create();
	this->addChild(ds,10);
	/*
	//JSONtest 클래스 생성
	jt = JSONtest::create();
	this->addChild(jt);
	*/
	pyer = player::create();
	this->addChild(pyer);

	//가구 ui 생성
	fu = FurnitureUI::create();
	this->addChild(fu);
	dfur->setFurUI(fu);

	Size winSize = Director::getInstance()->getWinSize();
	camera = Camera::createPerspective(60, (GLfloat)winSize.width / winSize.height, 1, 1000);
	camera->setCameraFlag(CameraFlag::USER1);
	camera->setName("camera_main");
	this->addChild(camera);
	camera->setPosition3D(Vec3(0, 0,200));

	this->setCameraMask((unsigned short)CameraFlag::USER1, true);
	pyer->_camera = camera;
	camera_move = Vec2(0, 0);


	//스케쥴 실행
	this->scheduleUpdate();

    return true;
}

void LayerGame::update(float dt)
{
	pos = pyer->getChildByName("player_ani")->getPosition();
	//가구 버튼 test
	dfur->checkFur(pyer->getRect(), 0);
	if (fu->checkSearch()) {
		float posX = fu->getPos();
		float dis_pb = pos.x - posX;
		if (dis_pb==0) {
			fu->setStart();
			pyer->checkFur();
		}else if(dis_pb<3&&dis_pb>-3){
			pyer->getChildByName("player_ani")->setPositionX(posX);
		}
		else {
			int i = dis_pb > 0 ? 1 : -1;
			pyer->getChildByName("player_ani")->setPositionX(pos.x-(i*3));
		}
	}
	int move = 5;
	pyer->Joy_move_check();
	/*if (!pyer->getCheckFur() && fu->checkSearch()) {
		fu->setCancle();//가구 체크 취소
	}*/
	auto camera_m = this->getChildByName("camera_main");

	camera->setPosition(pos.x, pos.y+60);
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


