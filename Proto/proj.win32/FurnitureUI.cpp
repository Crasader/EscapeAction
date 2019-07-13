#include "FurnitureUI.h"
#include "GameManager.h"

bool FurnitureUI::init()
{
	//���� �ʱ�ȭ
	v_chekcBtn.clear();
	v_btn.clear();
	v_pro.clear();

	//���� ������ �ҷ�����
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
				//���� sprite, ������ �޾ƿ��� �뵵
				Sprite* furni = Sprite::create(fur["name"].GetString());
				Size furni_size = furni->getContentSize();
				//��ư ����
				ui::Button* btn = ui::Button::create("fur_button.png");
				btn->setPosition(Vec2(fur["pos"].GetFloat()*wid, hgt*fl + furni_size.height*0.5));
				btn->setScale(0.4);
				btn->setTag(furCnt);
				btn->addClickEventListener(CC_CALLBACK_0(FurnitureUI::clickBtn, this, btn->getTag()));
				btn->setVisible(false);
				this->addChild(btn);
				v_btn.pushBack(btn);
				//���α׷��� �� ����
				ProgressTimer* progress = ProgressTimer::create(Sprite::create("fur_button_prgress.png"));
				progress->setPosition(Vec2(fur["pos"].GetFloat()*wid, hgt*fl + furni_size.height*0.5));
				progress->setType(ProgressTimer::Type::RADIAL);
				progress->setPercentage(0);
				progress->setVisible(false);
				progress->setScale(0.4);
				this->addChild(progress);
				v_pro.pushBack(progress);
				furCnt++;
			}
		}
		fl++;
	}

	return true;
}

void FurnitureUI::setBtnVisible(int num, bool setbool)
{
	ui::Button* btn = v_btn.at(num);
	if (setbool == true) {
		for (auto v : v_chekcBtn) {
			if (v->getTag() == btn->getTag()) {
				btn->setVisible(false);
				return;
			}
		}
	}
	btn->setVisible(setbool);
}

void FurnitureUI::clearCheckBtnVector()
{
	v_chekcBtn.clear();
}

FurnitureUI::~FurnitureUI()
{
}

void FurnitureUI::clickBtn(int num)
{
	ui::Button* button = v_btn.at(num);
	float distance = button->getPositionX()-GameManager::getInstance()->getPlayerPositionX();//���� ui�� �÷��̾� ��ġ ����
	bool changeState = false;
	if (distance < 0) {
		changeState = GameManager::getInstance()->setState(LMOVE);
	}
	else if(distance > 0){
		changeState = GameManager::getInstance()->setState(RMOVE);
	}
	else {
		GameManager::getInstance()->setState(NONE);//changeState�� true�� �ǵ��� ���¸� �ѹ� �ٲ��ش�.
		changeState = GameManager::getInstance()->setState(IDLE);
	}
	if (changeState) {//�÷��̾� ���°� ��ȭ�� ��쿡�� ����
		for (auto v : v_chekcBtn) {//�̹� üũ�� ��ư�� ��� stop
			if (v == button) {
				return;
			}
		}
		_checkfurNum = num;//��ġ�� ���� ��ȣ ����
		this->schedule(schedule_selector(FurnitureUI::schedule_gotoBtn));
	}
	else if(GameManager::getInstance()->getPlayerState()==SEARCH&& _checkfurNum==num) {//���� �� ��ư Ŭ���� �ۼ�Ʈ �� ���� ��
		ProgressTimer* progress = v_pro.at(num);
		float percent = progress->getPercentage();

		progress->setPercentage(percent + 5);
	}
}

void FurnitureUI::schedule_gotoBtn(float dt)
{
	ui::Button* button = v_btn.at(_checkfurNum);
	float distance = button->getPositionX() - GameManager::getInstance()->getPlayerPositionX();//���� ui�� �÷��̾� ��ġ ����
	player_Move_enum state = IDLE;
	if (distance < 0) {
		state = LMOVE;
	}
	else if (distance > 0) {
		state = RMOVE;
	}
	if (state != GameManager::getInstance()->getPlayerState()) {
		this->unscheduleAllSelectors();
		return;
	}

	if(abs(distance) <=10){
		GameManager::getInstance()->setPlayerPositionX(button->getPositionX()); //�÷��̾� ������ ��ư ��ġ�� �̵�
		this->unscheduleAllSelectors();

		if (GameManager::getInstance()->setState(SEARCH)) {//�÷��̾� ���� ��ȭ �����Ҷ���
			ProgressTimer* progress = v_pro.at(_checkfurNum);

			float percent = progress->getPercentage();

			//���α׷��� �׼�
			TintTo* tint = TintTo::create(0.2, Color3B(0, 255, 255));
			TintTo* tint2 = TintTo::create(0.2, Color3B::WHITE);
			Sequence* sq = Sequence::create(tint, tint2, NULL);
			RepeatForever* rf = RepeatForever::create(sq);
			progress->setPercentage(0);
			progress->setVisible(true);
			progress->runAction(rf);
			//��ư �׼�
			TintTo* btn_tint = TintTo::create(0.2, Color3B(0, 255, 255));
			TintTo* btn_tint2 = TintTo::create(0.2, Color3B::WHITE);
			Sequence* btn_sq = Sequence::create(btn_tint, btn_tint2, NULL);
			RepeatForever* btn_rf = RepeatForever::create(btn_sq);
			button->runAction(btn_rf);

			this->schedule(schedule_selector(FurnitureUI::schedule_search));
		}
		else {
			this->unscheduleAllSelectors();
		}
	}
}

void FurnitureUI::schedule_search(float dt)
{
	if (GameManager::getInstance()->getPlayerState() == SEARCH) {
		ProgressTimer* progress = v_pro.at(_checkfurNum);
		int speed = 30;
		float percent = progress->getPercentage();
		float nextPercent = percent + speed * dt;
		progress->setPercentage(nextPercent);
		if (nextPercent >= 100) {
			//�÷��̾� ���� ����
			GameManager::getInstance()->playerEndLoopAni();
			//���� Ž�� �Ϸ�!
			ui::Button* btn = v_btn.at(_checkfurNum);
			btn->setColor(Color3B::WHITE);
			btn->stopAllActions();
			progress->stopAllActions();
			progress->setVisible(false);
			v_chekcBtn.pushBack(btn);
			this->unscheduleAllSelectors();
		}
	}
	else {//�߰��� cancle �� ���
		ProgressTimer* progress = v_pro.at(_checkfurNum);
		float percent = progress->getPercentage();

		ui::Button* btn = v_btn.at(_checkfurNum);
		btn->setColor(Color3B::WHITE);
		btn->stopAllActions();
		progress->stopAllActions();
		progress->setVisible(false);
		if (percent >= 100) {//percent�� 100�� �Ѿ�����
			//���� Ž�� �Ϸ�!
			v_chekcBtn.pushBack(btn);
		}
		else {
			progress->setPercentage(0);//���� ���α׷�����
		}
		this->unscheduleAllSelectors();
	}
}
