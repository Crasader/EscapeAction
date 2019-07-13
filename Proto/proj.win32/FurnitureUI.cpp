#include "FurnitureUI.h"
#include "GameManager.h"

bool FurnitureUI::init()
{
	//변수 초기화
	v_chekcBtn.clear();
	v_btn.clear();
	v_pro.clear();

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
	float distance = button->getPositionX()-GameManager::getInstance()->getPlayerPositionX();//가구 ui와 플레이어 위치 차이
	bool changeState = false;
	if (distance < 0) {
		changeState = GameManager::getInstance()->setState(LMOVE);
	}
	else if(distance > 0){
		changeState = GameManager::getInstance()->setState(RMOVE);
	}
	else {
		GameManager::getInstance()->setState(NONE);//changeState가 true가 되도록 상태를 한번 바꿔준다.
		changeState = GameManager::getInstance()->setState(IDLE);
	}
	if (changeState) {//플레이어 상태가 변화한 경우에만 실행
		for (auto v : v_chekcBtn) {//이미 체크한 버튼인 경우 stop
			if (v == button) {
				return;
			}
		}
		_checkfurNum = num;//서치할 가구 번호 저장
		this->schedule(schedule_selector(FurnitureUI::schedule_gotoBtn));
	}
	else if(GameManager::getInstance()->getPlayerState()==SEARCH&& _checkfurNum==num) {//수색 중 버튼 클릭시 퍼센트 더 빨리 참
		ProgressTimer* progress = v_pro.at(num);
		float percent = progress->getPercentage();

		progress->setPercentage(percent + 5);
	}
}

void FurnitureUI::schedule_gotoBtn(float dt)
{
	ui::Button* button = v_btn.at(_checkfurNum);
	float distance = button->getPositionX() - GameManager::getInstance()->getPlayerPositionX();//가구 ui와 플레이어 위치 차이
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
		GameManager::getInstance()->setPlayerPositionX(button->getPositionX()); //플레이어 포지션 버튼 위치로 이동
		this->unscheduleAllSelectors();

		if (GameManager::getInstance()->setState(SEARCH)) {//플레이어 상태 변화 가능할때만
			ProgressTimer* progress = v_pro.at(_checkfurNum);

			float percent = progress->getPercentage();

			//프로그래스 액션
			TintTo* tint = TintTo::create(0.2, Color3B(0, 255, 255));
			TintTo* tint2 = TintTo::create(0.2, Color3B::WHITE);
			Sequence* sq = Sequence::create(tint, tint2, NULL);
			RepeatForever* rf = RepeatForever::create(sq);
			progress->setPercentage(0);
			progress->setVisible(true);
			progress->runAction(rf);
			//버튼 액션
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
			//플레이어 상태 변경
			GameManager::getInstance()->playerEndLoopAni();
			//가구 탐색 완료!
			ui::Button* btn = v_btn.at(_checkfurNum);
			btn->setColor(Color3B::WHITE);
			btn->stopAllActions();
			progress->stopAllActions();
			progress->setVisible(false);
			v_chekcBtn.pushBack(btn);
			this->unscheduleAllSelectors();
		}
	}
	else {//중간에 cancle 된 경우
		ProgressTimer* progress = v_pro.at(_checkfurNum);
		float percent = progress->getPercentage();

		ui::Button* btn = v_btn.at(_checkfurNum);
		btn->setColor(Color3B::WHITE);
		btn->stopAllActions();
		progress->stopAllActions();
		progress->setVisible(false);
		if (percent >= 100) {//percent가 100을 넘었을때
			//가구 탐색 완료!
			v_chekcBtn.pushBack(btn);
		}
		else {
			progress->setPercentage(0);//리셋 프로그래스바
		}
		this->unscheduleAllSelectors();
	}
}
