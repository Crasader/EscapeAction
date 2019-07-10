#include "DoorUI.h"


bool DoorUI::init()
{
	moveRoom = false;//방 번호
	v_left.clear();
	v_right.clear();
	btnNum = 0;
	//문 데이터 불러오기
	FILE* fp = fopen("jsonData/trans/transDoor.json", "rb");
	char readBuffer[5000];
	FileReadStream is(fp, readBuffer, sizeof(readBuffer));
	trans_door.ParseStream(is);
	fclose(fp);

	assert(trans_door.IsArray());//타입 확인

	/*나중에 변수로 수정하기*/
	int hgt = 120;
	int wid = 48;

	int fl = 0;
	int furCnt = 0;
	for (auto& floor : trans_door.GetArray()) {
		for (auto& dr : floor.GetArray()) {
			//버튼 생성
			ui::Button* btn = ui::Button::create("fur_button.png");
			btn->setPosition(Vec2(dr["pos"].GetInt()*wid, hgt*fl+(hgt*0.3)));
			v_left.push_back(dr["left"].GetInt());
			v_right.push_back(dr["right"].GetInt());
			btn->setScale(0.4);
			btn->setTag(furCnt);
			btn->addClickEventListener(CC_CALLBACK_0(DoorUI::clickBtn, this, btn->getTag()));
			btn->setVisible(false);
			this->addChild(btn);
			v_btn.pushBack(btn);
			furCnt++;
		}
		fl++;
	}
	return true;
}

void DoorUI::clickBtn(int num)
{
/*	if (v_right.at(num) == _nowRoom) {
		_nowRoom = v_left.at(num);
	}
	else if (v_left.at(num) == _nowRoom) {
		_nowRoom = v_right.at(num);
	}*/
	moveRoom = true;
	btnNum = num;
}

void DoorUI::setBtnVisible(int num, bool setBool)
{
	v_btn.at(num)->setVisible(setBool);
}

bool DoorUI::moveDoor()
{
	return moveRoom;
}

int DoorUI::getNextRoom(int nowRoom)
{
	if (v_right.at(btnNum) == nowRoom) {
		nowRoom = v_left.at(btnNum);
	}
	else if (v_left.at(btnNum) == nowRoom) {
		nowRoom = v_right.at(btnNum);
	}
	return nowRoom;
}

void DoorUI::setUnMove()
{
	moveRoom = false;
}

DoorUI::~DoorUI()
{
}
