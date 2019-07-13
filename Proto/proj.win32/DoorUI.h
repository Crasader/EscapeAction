#pragma once
#include "external/json/document.h"
#include "external/json/filereadstream.h"//������ �����������
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
	void setBtnVisible(int num, bool setBool);
	~DoorUI();
private:
	Document trans_door;
	Vector<ui::Button*> v_btn;
	vector<int> v_left;
	vector<int> v_right;
	vector<bool> v_lock;
	//�Լ�
	void clickBtn(int num);
};

