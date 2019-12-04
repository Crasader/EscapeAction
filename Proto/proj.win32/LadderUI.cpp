#include "LadderUI.h"
#include "GameManager.h"

bool LadderUI::init()
{
	v_btn.clear();
	v_up.clear();
	v_down.clear();
	_usingLadder = -1;

	//파일 내용 불러오기
	FILE* fp = fopen("jsonData/draw/drawLadder.json", "rb");
	char readBuffer[5000];
	FileReadStream is(fp, readBuffer, sizeof(readBuffer));
	trans_ladder.ParseStream(is);
	fclose(fp);

	/*값 받아 오는 걸로 수정*/
	int hgt = 120;
	int wid = 48;

	assert(trans_ladder.IsArray());//타입 확인

	int fl = 0;
	int ladder_cnt = 0;
	for (auto& floor : trans_ladder.GetArray()) {
		for (auto& lad : floor.GetArray()) {
			//버튼 생성
			ui::Button* btn = ui::Button::create("fur_button.png");
			btn->setPosition(Vec2(lad["pos"].GetInt()*wid, hgt*fl + (hgt*0.3)));
			v_up.push_back(lad["up"].GetInt());
			v_down.push_back(lad["down"].GetInt());
			btn->setScale(0.4);
			btn->setTag(ladder_cnt);
			btn->addClickEventListener(CC_CALLBACK_0(LadderUI::clickBtn, this, btn->getTag()));
			btn->setVisible(false);
			this->addChild(btn);
			v_btn.pushBack(btn);
			ladder_cnt++;
		}
		fl++;
	}
	return true;
}

void LadderUI::clickBtn(int num)
{
	ui::Button* button = v_btn.at(num);
	float distance = button->getPositionX() - GameManager::getInstance()->getPlayerPositionX();//ladder ui와 플레이어 위치 차이
	bool changeState = false;
	if (distance < 0) {
		changeState = GameManager::getInstance()->setState(LMOVE);
	}
	else if(distance > 0){
		changeState = GameManager::getInstance()->setState(RMOVE);
	}
	else {
		GameManager::getInstance()->setState(NONE);//changeState값이 true가 되도록 상태를 한번 바꿔준다.
		changeState = GameManager::getInstance()->setState(IDLE);
	}
	if (changeState) {//플레이어 상태가 변화한 경우에만 실행
		log(changeState);
		_usingLadder = num;//사다리 번호 저장
		log("_usinLadder : %d", num);
		this->schedule(schedule_selector(LadderUI::schedule_gotoLadder));
	}
}

void LadderUI::schedule_gotoLadder(float dt)
{
	ui::Button* button = v_btn.at(_usingLadder);
	float distance = button->getPositionX() - GameManager::getInstance()->getPlayerPositionX();//가구 ui와 플레이어 위치 차이
	if (abs(distance) <= 10) {
		GameManager::getInstance()->setPlayerPositionX(button->getPositionX()); //플레이어 포지션 버튼 위치로 이동
		this->unscheduleAllSelectors();
		if (GameManager::getInstance()->getPlayerRoomNum() == v_down.at(_usingLadder)) {//현재 방번호 == 사다리 아래 방
			if (GameManager::getInstance()->setState(UMOVE)) {//윗층으로!
				int playerFloor = GameManager::getInstance()->getPlayerFloor();
				int roomNum = v_up.at(_usingLadder);
				GameManager::getInstance()->setPlayerFloor(playerFloor + 1);
				GameManager::getInstance()->setPlayerRoomNum(roomNum);
			}
		}
		else {
			if (GameManager::getInstance()->setState(DMOVE)) {//아래층으로!
				int playerFloor = GameManager::getInstance()->getPlayerFloor();
				int roomNum = v_down.at(_usingLadder);
				GameManager::getInstance()->setPlayerFloor(playerFloor - 1);
				GameManager::getInstance()->setPlayerRoomNum(roomNum);
			}
		}
	}
}

void LadderUI::setBtnVisible(int num, bool setBool)
{
	v_btn.at(num)->setVisible(setBool);
}

void LadderUI::setBtnPositionY(int num, float posY)
{
	v_btn.at(num)->setPositionY(posY);
}

LadderUI::~LadderUI()
{
}
