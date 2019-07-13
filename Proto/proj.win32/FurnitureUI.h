#pragma once
#include "external/json/document.h"
#include "external/json/filereadstream.h"//파일을 열어오기위함
#include <cstdio>
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "UIManager.h"
USING_NS_CC;
using namespace std;
using namespace rapidjson;
class FurnitureUI:public Node
{
public:
	CREATE_FUNC(FurnitureUI);
	virtual bool init();
	void setBtnVisible(int num, bool setbool);
	void clearCheckBtnVector();
	~FurnitureUI();
private:
	Vector<ui::Button*> v_chekcBtn;//플레이어가 위치한 방안에서 이미 체크한 가구 모음
	Vector<ui::Button*> v_btn;
	Vector<ProgressTimer*> v_pro;
	int _checkfurNum;
	//함수
	void clickBtn(int num);
	void schedule_gotoBtn(float dt);//플레이어가 서치 하기위해 이동
	void schedule_search(float dt);//플레이어 서치

};

