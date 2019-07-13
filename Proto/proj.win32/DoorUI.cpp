#include "DoorUI.h"
#include "GameManager.h"

bool DoorUI::init()
{
	v_left.clear();
	v_right.clear();
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
	if (GameManager::getInstance()->setState(player_Move_enum::OPEN)) {
		int playerRoomNum = GameManager::getInstance()->getPlayerRoomNum();
		if (v_right.at(num) == playerRoomNum) {
			playerRoomNum = v_left.at(num);
		}
		else if (v_left.at(num) == playerRoomNum) {
			playerRoomNum = v_right.at(num);
		}
		GameManager::getInstance()->setPlayerRoomNum(playerRoomNum);
	}
}

void DoorUI::setBtnVisible(int num, bool setBool)
{
	v_btn.at(num)->setVisible(setBool);
}
DoorUI::~DoorUI()
{
}
