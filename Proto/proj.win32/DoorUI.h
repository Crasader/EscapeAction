#pragma once
#include "external/json/document.h"
#include "external/json/filereadstream.h"//파일을 열어오기위함
#include <cstdio>
#include "cocos2d.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
using namespace std;
using namespace rapidjson;
class DoorUI : public Node
{
public:
	CREATE_FUNC(DoorUI);
	virtual bool init();
	void clickBtn(int num);
	void setBtnVisible(int num, bool setBool);
	bool moveDoor();
	int getNextRoom(int nowRoom);
	void setUnMove();

	~DoorUI();
private:
	Document trans_door;
	Vector<ui::Button*> v_btn;
	vector<int> v_left;
	vector<int> v_right;
	vector<bool> v_lock;
	int btnNum;
	bool moveRoom;
	
};

