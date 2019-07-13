#include "DrawDoor.h"
#include "GameManager.h"
bool DrawDoor::init()
{
	//초기화
	int _roomNum = 0;
	v_doorCnt.clear();
	v_spr.clear();
	_du = NULL;
	_floor = 0;
	//파일 내용 불러오기
	Document trans_door;
	FILE* fp = fopen("jsonData/trans/transDoor.json", "rb");
	char readBuffer[5000];
	FileReadStream is(fp, readBuffer, sizeof(readBuffer));
	trans_door.ParseStream(is);
	fclose(fp);

/*값 받아 오는 걸로 수정*/
	int hgt = 120;
	int wid = 48;

	assert(trans_door.IsArray());//타입 확인

	int fl = 0;
	int door_cnt = 0;
	for (auto& floor : trans_door.GetArray()) {
		for (auto& dr : floor.GetArray()) {
			float i = dr["pos"].GetInt()*wid;
			log("%f", i);
			Sprite* door = Sprite::create("door/door.png");
			door->setAnchorPoint(Vec2(0.5,0));
			door->setPosition(i, hgt*fl);
			this->addChild(door);
			v_spr.pushBack(door);
			door_cnt++;
		}
		v_doorCnt.push_back(door_cnt);
		fl++;
	}
	return true;
}

void DrawDoor::checkDoor()
{
	int playerFloor = GameManager::getInstance()->getPlayerFloor();
	Rect playerRect = GameManager::getInstance()->getPlayerRect();
	//플레이어 층과 문 층이 다를때
	if (playerFloor != _floor) {
		int fir;
		if (_floor == 0) {
			fir = 0;
		}
		else {
			fir = v_doorCnt.at(_floor - 1);
		}
		int last = v_doorCnt.at(_floor);
		for (int i = fir; i < last; i++) {
			_du->setBtnVisible(i, false);
		}
		
		_floor = playerFloor;
	}
	int fir;
	if (_floor == 0) {
		fir = 0;
	}
	else {
		fir = v_doorCnt.at(_floor-1);
	}
	int last = v_doorCnt.at(_floor);
	for (int i = fir; i < last; i++) {
		Sprite* spr = v_spr.at(i);
		Rect spr_rc = spr->getBoundingBox();
		if (playerRect.intersectsRect(spr_rc)) {
			GameManager::getInstance()->setContactDoorWithPlayer(spr);
			_du->setBtnVisible(i, true);
		}
		else {
			_du->setBtnVisible(i,false);
		}
		
	}
}

void DrawDoor::setDoorUI(DoorUI* du)
{
	_du = du;
}

DrawDoor::~DrawDoor()
{
}
