#include "FurnitureUI.h"


bool FurnitureUI::init()
{
	//���� �ʱ�ȭ
	v_chekcBtn.clear();
	v_btn.clear();
	v_pro.clear();
	check_furNum = -1;
	startSearch = false;

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

bool FurnitureUI::checkSearch()
{
	if (check_furNum == -1) {
		return false;
	}
	else {
		return true;
	}
}

float FurnitureUI::getPos()
{
	return v_btn.at(check_furNum)->getPositionX();
}

void FurnitureUI::setStart()
{
	startSearch = true;
}

void FurnitureUI::setCancle()
{
	this->unscheduleAllSelectors();
	ProgressTimer* progress = v_pro.at(check_furNum);
	progress->stopAllActions();
	progress->setVisible(false);
	check_furNum = -1;
	startSearch = false;
}

void FurnitureUI::changeRm()
{
	v_chekcBtn.clear();
}

FurnitureUI::~FurnitureUI()
{
}

void FurnitureUI::clickBtn(int num)
{
	ProgressTimer* progress = v_pro.at(num);

	if (check_furNum == -1) {//üũ���� ������ ������
		TintTo* tint = TintTo::create(0.2, Color3B(0, 255, 255));
		TintTo* tint2 = TintTo::create(0.2, Color3B::WHITE);
		Sequence* sq = Sequence::create(tint, tint2, NULL);
		RepeatForever* rf = RepeatForever::create(sq);

		progress->setPercentage(0);
		progress->setVisible(true);
		progress->setPercentage(0);
		progress->runAction(rf);
		check_furNum = num;
		this->schedule(schedule_selector(FurnitureUI::schedule_clickBtn));

		TintTo* btn_tint = TintTo::create(0.2, Color3B(0, 255, 255));
		TintTo* btn_tint2 = TintTo::create(0.2, Color3B::WHITE);
		Sequence* btn_sq = Sequence::create(btn_tint, btn_tint2, NULL);
		RepeatForever* btn_rf = RepeatForever::create(btn_sq);
		ui::Button* btn = v_btn.at(num);
		btn->runAction(btn_rf);
		log("click!");
	}
	else if (check_furNum == num) {//Ŭ���ϸ� �� ���� Ž��
		float percent = progress->getPercentage();
		progress->setPercentage(percent + 5);
	}
}

void FurnitureUI::schedule_clickBtn(float dt)
{
	if (check_furNum == -1) {
		this->unscheduleAllSelectors();
		return;
	}
	else if (startSearch) {
		ProgressTimer* progress = v_pro.at(check_furNum);
		int speed = 30;
		float percent = progress->getPercentage();
		float nextPercent = percent + speed * dt;
		progress->setPercentage(nextPercent);
		if (nextPercent >= 100) {
			//���� Ž�� �Ϸ�!
			ui::Button* btn = v_btn.at(check_furNum);
			btn->setColor(Color3B::WHITE);
			btn->stopAllActions();
			v_chekcBtn.pushBack(btn);
			progress->stopAllActions();
			progress->setVisible(false);
			check_furNum = -1;
			startSearch = false;
		}
	}
}
