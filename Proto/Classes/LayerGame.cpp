#include "LayerGame.h"
#include "SimpleAudioEngine.h"
#include "../proj.win32/GameManager.h"

bool LayerGame::init()
{
	Size winSize = Director::getInstance()->getWinSize();

	//LevelDataSet 클래스 생성, addChild 필요 없음
	LevelDataSet* levelData = LevelDataSet::create();
	
	//drawField
	df = DrawField::create();
	this->addChild(df);
	//draw 문
	ddor = DrawDoor::create();
	this->addChild(ddor);

	//draw 문
	dlad = DrawLadder::create();
	this->addChild(dlad);

	//draw 가구
	dfur = DrawFurniture::create();
	this->addChild(dfur);

	//draw 장식
	DrawDeco* ddeco = DrawDeco::create();
	this->addChild(ddeco);

	//draw 구조
	DrawStruct* ds = DrawStruct::create();
	this->addChild(ds);

	//player 생성
	pyer = player::create();
	this->addChild(pyer);

	//ui 위치는 플레이어 보다 위에 있음
	//가구 ui 생성
	fu = FurnitureUI::create();
	this->addChild(fu);
	dfur->setFurUI(fu);
	//문 ui 생성
	du = DoorUI::create();
	this->addChild(du);
	ddor->setDoorUI(du);
	//사다리 ui 생성
	lu = LadderUI::create();
	this->addChild(lu);
	dlad->setLadderUI(lu);

	//카메라
	camera = Camera::createPerspective(60, (GLfloat)winSize.width / winSize.height, 1, 1000);
	camera->setCameraFlag(CameraFlag::USER1);
	camera->setName("camera_main");
	this->addChild(camera);
	int cameraZ_val = 500;
	camera->setPosition3D(Vec3(0, 0,200));

	this->setCameraMask((unsigned short)CameraFlag::USER1, true);
	pyer->_camera = camera;

	//GameManager 세팅
	GameManager::getInstance()->setPlayer(pyer);

	//스케쥴 실행
	this->scheduleUpdate();

    return true;
}

void LayerGame::update(float dt)
{
	//캐릭터 방밖으로 나가는지 체크 및 light 위치 설정
	int rmNum = pyer->getRoomNum();
	pyer->Joy_move_check(df->getFirst(rmNum), df->getLast(rmNum));

	//충돌 체크
	dfur->checkFur();
	ddor->checkDoor();
	dlad->checkLadder();

	//카메라는 캐릭터를 따라 이동
	Vec2 pos = pyer->getChildByName("player_ani")->getPosition();//캐릭터 위치
	camera->setPosition(pos.x, pos.y+60);

}


