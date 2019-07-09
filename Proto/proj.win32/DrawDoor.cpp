#include "DrawDoor.h"

bool DrawDoor::init()
{
	v_doorCnt.clear();
	v_spr.clear();
	_du = NULL;

	//파일 내용 불러오기
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

void DrawDoor::checkDoor(Rect player, int floor)
{
	int fir;
	if (floor == 0) {
		fir = 0;
	}
	else {
		fir = v_doorCnt.at(floor-1);
	}
	int last = v_doorCnt.at(floor);
	for (int i = fir; i < last; i++) {
		Sprite* spr = v_spr.at(i);
		Rect spr_rc = spr->getBoundingBox();
		if (player.intersectsRect(spr_rc)) {
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
