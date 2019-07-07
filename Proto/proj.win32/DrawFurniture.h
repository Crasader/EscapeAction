#pragma once

#include "external/json/document.h"
#include "external/json/filereadstream.h"//파일을 열어오기위함
#include <cstdio>
#include "cocos2d.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
using namespace std;
using namespace rapidjson;;
class DrawFurniture :public Node
{
public:
	CREATE_FUNC(DrawFurniture);
	virtual bool init();
	void checkFur(Rect player, int roomNum);
	~DrawFurniture();
	bool getCheck();//체크 중인지 확인
	float getCheckPos();
	void setCheckFalse();
private:
	int _checkFurNum;//체크중인 가구 번호. 아닐때는 -1
	vector<int> v_furCnt;//가구 갯수 누적
	Vector<Sprite*> v_spr;
	Vector<ui::Button*> v_btn;
	Vector<ProgressTimer*> v_pro;
	float check_furpos;

	void clickBtn(int num);
	void endCheck();
};

