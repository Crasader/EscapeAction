#include "LayerGame.h"
#include "SimpleAudioEngine.h"
#include "../proj.win32/GameManager.h"

bool LayerGame::init()
{
	Size winSize = Director::getInstance()->getWinSize();

	//LevelDataSet Ŭ���� ����, addChild �ʿ� ����
	LevelDataSet* levelData = LevelDataSet::create();
	
	//drawField
	df = DrawField::create();
	this->addChild(df);
	//draw ��
	ddor = DrawDoor::create();
	this->addChild(ddor);

	//draw ��
	dlad = DrawLadder::create();
	this->addChild(dlad);

	//draw ����
	dfur = DrawFurniture::create();
	this->addChild(dfur);

	//draw ���
	DrawDeco* ddeco = DrawDeco::create();
	this->addChild(ddeco);

	//draw ����
	DrawStruct* ds = DrawStruct::create();
	this->addChild(ds);

	//player ����
	pyer = player::create();
	this->addChild(pyer);

	//ui ��ġ�� �÷��̾� ���� ���� ����
	//���� ui ����
	fu = FurnitureUI::create();
	this->addChild(fu);
	dfur->setFurUI(fu);
	//�� ui ����
	du = DoorUI::create();
	this->addChild(du);
	ddor->setDoorUI(du);
	//��ٸ� ui ����
	lu = LadderUI::create();
	this->addChild(lu);
	dlad->setLadderUI(lu);

	//ī�޶�
	camera = Camera::createPerspective(60, (GLfloat)winSize.width / winSize.height, 1, 1000);
	camera->setCameraFlag(CameraFlag::USER1);
	camera->setName("camera_main");
	this->addChild(camera);
	int cameraZ_val = 500;
	camera->setPosition3D(Vec3(0, 0,200));

	this->setCameraMask((unsigned short)CameraFlag::USER1, true);
	pyer->_camera = camera;

	//GameManager ����
	GameManager::getInstance()->setPlayer(pyer);

	//������ ����
	this->scheduleUpdate();

    return true;
}

void LayerGame::update(float dt)
{
	//ĳ���� ������� �������� üũ �� light ��ġ ����
	int rmNum = pyer->getRoomNum();
	pyer->Joy_move_check(df->getFirst(rmNum), df->getLast(rmNum));

	//�浹 üũ
	dfur->checkFur();
	ddor->checkDoor();
	dlad->checkLadder();

	//ī�޶�� ĳ���͸� ���� �̵�
	Vec2 pos = pyer->getChildByName("player_ani")->getPosition();//ĳ���� ��ġ
	camera->setPosition(pos.x, pos.y+60);

}


