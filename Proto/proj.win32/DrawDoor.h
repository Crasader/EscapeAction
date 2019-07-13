#pragma once
#include "external/json/document.h"
#include "external/json/filereadstream.h"//������ �����������
//������ ���� ��������
#include "external/json/writer.h"
#include "external/json/filewritestream.h"
//c����� FILE ���
#include <iostream>
#include <cstdio>

#include "cocos2d.h"
#include "DoorUI.h"

USING_NS_CC;
using namespace rapidjson;
using namespace std;
class DrawDoor:public Node
{
public:
	CREATE_FUNC(DrawDoor);
	virtual bool init();
	void checkDoor();
	void setDoorUI(DoorUI* du);
	~DrawDoor();
private:
	int _floor;
	DoorUI* _du;
	vector<int> v_doorCnt;
	Vector<Sprite*> v_spr;
};

