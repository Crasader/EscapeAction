#include "DrawFurniture.h"
#include "GameManager.h"



bool DrawFurniture::init()
{
//�ʱ�ȭ
	_roomNum = 0;
	_fu = NULL;
	v_spr.clear();

	Document draw_fur;
	FILE* fp = fopen("jsonData/draw/drawFur.json", "rb");
	char readBuffer[5000];
	FileReadStream is(fp, readBuffer, sizeof(readBuffer));
	draw_fur.ParseStream(is);
	fclose(fp);

	assert(draw_fur.IsArray());//Ÿ�� Ȯ��

	/*���߿� ������ �����ϱ�*/
	int hgt = 120;
	int wid = 48;

	int fl = 0;
	int furCnt = 0;
	for (auto& floor : draw_fur.GetArray()) {
		for (auto& rm : floor.GetArray()) {
			for (auto& fur : rm.GetArray()) {
				//���� sprite ����
				Sprite* furni = Sprite::create(fur["name"].GetString());
				if (RandomHelper::random_int(0, 1) == 1) {
					furni->setFlipX(true);
				}
				furni->setAnchorPoint(Vec2(0.5, 0));
				furni->setPosition(fur["pos"].GetFloat()*wid, hgt*fl);
				this->addChild(furni);
				v_spr.pushBack(furni);
				furCnt++;
			}
			v_furCnt.push_back(furCnt);
		}
		fl++;
	}
	return true;
}

void DrawFurniture::checkFur()// ���� ���̾� update���� ���� ����
{
	int playerRoomNum = GameManager::getInstance()->getPlayerRoomNum();
	Rect playerRect = GameManager::getInstance()->getPlayerRect();

	//player�� ��ġ�� ��� ���� �� �ٸ���
	if (playerRoomNum != _roomNum) {
		_fu->clearCheckBtnVector();
		int fir;
		if (_roomNum == 0) {
			fir = 0;
		}
		else {
			fir = v_furCnt.at(_roomNum - 1);
		}
		int last = v_furCnt.at(_roomNum);
		Vector<Sprite*>::iterator iter = v_spr.begin() + fir;
		Vector<Sprite*>::iterator iter_last = v_spr.begin() + last;
		//���� �� ui ���� false
		for (iter; iter != iter_last; iter++) {
			log("all false");
			_fu->setBtnVisible(fir, false);
			fir++;
		}
		_roomNum = playerRoomNum;
	}
	//��� ���� �˻�
	int fir;
	if (_roomNum == 0) {
		fir = 0;
	}
	else {
		fir = v_furCnt.at(_roomNum - 1);
	}
	int last = v_furCnt.at(_roomNum);
	Vector<Sprite*>::iterator iter = v_spr.begin() + fir;
	Vector<Sprite*>::iterator iter_last = v_spr.begin() + last;
	//���� ���� ������ player�� ��ġ���� üũ
	for (iter; iter != iter_last; iter++) {
		Rect fur_rect = v_spr.at(fir)->getBoundingBox();
		if (playerRect.intersectsRect(fur_rect)) {
			_fu->setBtnVisible(fir, true);
		}
		else {
			_fu->setBtnVisible(fir, false);
		}
		fir++;
	}
}
DrawFurniture::~DrawFurniture()
{
}
void DrawFurniture::setFurUI(FurnitureUI * fu)//�ʱ⿡ ��������
{
	if (_fu == NULL) {
		_fu = fu;
	}
}
