#include "LayerGame.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

bool LayerGame::init()
{


	//LevelDataSet Ŭ���� ����, addChild �ʿ� ����
	LevelDataSet* levelData = LevelDataSet::create();

	//drawField
	df = DrawField::create();
	this->addChild(df);
	//draw ���
	DrawDeco* ddeco = DrawDeco::create();
	this->addChild(ddeco);
	//draw ����
	dfur = DrawFurniture::create();
	this->addChild(dfur);
	//draw ����
	DrawStruct* ds = DrawStruct::create();
	this->addChild(ds,10);
	/*
	//JSONtest Ŭ���� ����
	jt = JSONtest::create();
	this->addChild(jt);
	*/
	pyer = player::create();
	this->addChild(pyer);
	_roomNum = 0;
	pyer->setRoomNum(_roomNum);
	pyer->setFirst(df->getFirst(_roomNum));
	pyer->setLast(df->getLast(_roomNum));

	//���� ui ����
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


	//������ ����
	this->scheduleUpdate();

    return true;
}

void LayerGame::update(float dt)
{
	pos = pyer->getChildByName("player_ani")->getPosition();
	//���� ��ư test
	dfur->checkFur(pyer->getRect(), _roomNum);

	if (pyer->getRoomNum() != _roomNum) {
		pyer->setFirst(df->getFirst(_roomNum));
		pyer->setLast(df->getLast(_roomNum));
	}

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
		fu->setCancle();//���� üũ ���
	}*/
	auto camera_m = this->getChildByName("camera_main");

	camera->setPosition(pos.x, pos.y+60);

}


