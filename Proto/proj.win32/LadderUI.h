#pragma once
#include "external/json/document.h"
#include "external/json/filereadstream.h"//파일을 열어오기위함
#include <cstdio>
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "UIManager.h"
#include "GameManager.h"
USING_NS_CC;
using namespace std;
using namespace rapidjson;
class LadderUI : public Node
{
public:
	CREATE_FUNC(LadderUI);
	virtual bool init();
	void setBtnVisible(int num, bool setBool );
	void setBtnPositionY(int num, float posY);
	~LadderUI();
private:
	Document trans_ladder;
	Vector<ui::Button*> v_btn;
	vector<int> v_up;
	vector<int> v_down;
	int _usingLadder;//사용중인 사다리 번호
	//함수
	void clickBtn(int num);
	void schedule_gotoLadder(float dt);
};

