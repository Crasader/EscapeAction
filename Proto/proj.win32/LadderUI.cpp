#include "LadderUI.h"
#include "GameManager.h"

bool LadderUI::init()
{
	v_btn.clear();
	v_up.clear();
	v_down.clear();
	_usingLadder = -1;

	//���� ���� �ҷ�����
	FILE* fp = fopen("jsonData/draw/drawLadder.json", "rb");
	char readBuffer[5000];
	FileReadStream is(fp, readBuffer, sizeof(readBuffer));
	trans_ladder.ParseStream(is);
	fclose(fp);

	/*�� �޾� ���� �ɷ� ����*/
	int hgt = 120;
	int wid = 48;

	assert(trans_ladder.IsArray());//Ÿ�� Ȯ��

	int fl = 0;
	int ladder_cnt = 0;
	for (auto& floor : trans_ladder.GetArray()) {
		for (auto& lad : floor.GetArray()) {
			//��ư ����
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
	float distance = button->getPositionX() - GameManager::getInstance()->getPlayerPositionX();//ladder ui�� �÷��̾� ��ġ ����
	bool changeState = false;
	if (distance < 0) {
		changeState = GameManager::getInstance()->setState(LMOVE);
	}
	else if(distance > 0){
		changeState = GameManager::getInstance()->setState(RMOVE);
	}
	else {
		GameManager::getInstance()->setState(NONE);//changeState���� true�� �ǵ��� ���¸� �ѹ� �ٲ��ش�.
		changeState = GameManager::getInstance()->setState(IDLE);
	}
	if (changeState) {//�÷��̾� ���°� ��ȭ�� ��쿡�� ����
		log(changeState);
		_usingLadder = num;//��ٸ� ��ȣ ����
		log("_usinLadder : %d", num);
		this->schedule(schedule_selector(LadderUI::schedule_gotoLadder));
	}
}

void LadderUI::schedule_gotoLadder(float dt)
{
	ui::Button* button = v_btn.at(_usingLadder);
	float distance = button->getPositionX() - GameManager::getInstance()->getPlayerPositionX();//���� ui�� �÷��̾� ��ġ ����
	if (abs(distance) <= 10) {
		GameManager::getInstance()->setPlayerPositionX(button->getPositionX()); //�÷��̾� ������ ��ư ��ġ�� �̵�
		this->unscheduleAllSelectors();
		if (GameManager::getInstance()->getPlayerRoomNum() == v_down.at(_usingLadder)) {//���� ���ȣ == ��ٸ� �Ʒ� ��
			if (GameManager::getInstance()->setState(UMOVE)) {//��������!
				int playerFloor = GameManager::getInstance()->getPlayerFloor();
				int roomNum = v_up.at(_usingLadder);
				GameManager::getInstance()->setPlayerFloor(playerFloor + 1);
				GameManager::getInstance()->setPlayerRoomNum(roomNum);
			}
		}
		else {
			if (GameManager::getInstance()->setState(DMOVE)) {//�Ʒ�������!
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
