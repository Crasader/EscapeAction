#include "FurnitureUI.h"


bool FurnitureUI::init()
{
	//변수 초기화
	v_chekcBtn.clear();
	v_btn.clear();
	v_pro.clear();
	check_furNum = -1;
	startSearch = false;

	//가구 데이터 불러오기
	Document draw_fur;
	FILE* fp = fopen("jsonData/draw/drawFur.json", "rb");
	char readBuffer[5000];
	FileReadStream is(fp, readBuffer, sizeof(readBuffer));
	draw_fur.ParseStream(is);
	fclose(fp);

	assert(draw_fur.IsArray());//타입 확인

	/*나중에 변수로 수정하기*/
	int hgt = 120;
	int wid = 48;

	int fl = 0;
	int furCnt = 0;
	for (auto& floor : draw_fur.GetArray()) {
		for (auto& rm : floor.GetArray()) {
			for (auto& fur : rm.GetArray()) {
				//가구 sprite, 사이즈 받아오는 용도
				Sprite* furni = Sprite::create(fur["name"].GetString());
				Size furni_size = furni->getContentSize();
				//버튼 생성
				ui::Button* btn = ui::Button::create("fur_button.png");
				btn->setPosition(Vec2(fur["pos"].GetFloat()*wid, hgt*fl + furni_size.height*0.5));
				btn->setScale(0.4);
				btn->setTag(furCnt);
				btn->addClickEventListener(CC_CALLBACK_0(FurnitureUI::clickBtn, this, btn->getTag()));
				btn->setVisible(false);
				this->addChild(btn);
				v_btn.pushBack(btn);
				//프로그래스 바 생성
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
	for (auto v : v_btn) {
		v->setVisible(false);
	}
	v_chekcBtn.clear();
}

FurnitureUI::~FurnitureUI()
{
}

void FurnitureUI::clickBtn(int num)
{
	ui::Button* btn = v_btn.at(num);
	ProgressTimer* progress = v_pro.at(num);
	float percent = progress->getPercentage();
	if (check_furNum == -1) {//체크중인 가구가 없으면
		for (auto v : v_chekcBtn) {
			if (v == btn) {
				return;
			}
		}
		//플레이어 상태 변경
		GameManager::getInstance()->setState(SEARCH);

		TintTo* tint = TintTo::create(0.2, Color3B(0, 255, 255));
		TintTo* tint2 = TintTo::create(0.2, Color3B::WHITE);
		Sequence* sq = Sequence::create(tint, tint2, NULL);
		RepeatForever* rf = RepeatForever::create(sq);

		progress->setPercentage(0);
		progress->setVisible(true);
		progress->runAction(rf);
		check_furNum = num;
		this->schedule(schedule_selector(FurnitureUI::schedule_clickBtn));

		TintTo* btn_tint = TintTo::create(0.2, Color3B(0, 255, 255));
		TintTo* btn_tint2 = TintTo::create(0.2, Color3B::WHITE);
		Sequence* btn_sq = Sequence::create(btn_tint, btn_tint2, NULL);
		RepeatForever* btn_rf = RepeatForever::create(btn_sq);
		btn->runAction(btn_rf);
		log("click!");
	}
	else if (check_furNum == num &&percent<100) {//클릭하면 더 빨리 탐색
		progress->setPercentage(percent + 5);
	}
}

void FurnitureUI::schedule_clickBtn(float dt)
{
	if (check_furNum == -1) {
		this->unscheduleAllSelectors();
		UIManager::getInstance()->setEnable_AtkBtn(true);
		//플레이어 상태 변경
		GameManager::getInstance()->setState(IDLE);
		return;
	}
	else if (startSearch) {
		ProgressTimer* progress = v_pro.at(check_furNum);
		int speed = 30;
		float percent = progress->getPercentage();
		log("%f", percent);
		float nextPercent = percent + speed * dt;
		progress->setPercentage(nextPercent);
		if (nextPercent >= 100) {
			//플레이어 상태 변경
			GameManager::getInstance()->setState(IDLE);
			//가구 탐색 완료!
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
