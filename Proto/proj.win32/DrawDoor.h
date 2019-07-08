#pragma once
#include "external/json/document.h"
#include "external/json/filereadstream.h"//파일을 열어오기위함
//데이터 파일 내보내기
#include "external/json/writer.h"
#include "external/json/filewritestream.h"
//c언어의 FILE 사용
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
	void checkDoor(Rect player, int floor);//현재 층, 방번호
	void setDoorUI(DoorUI* du);
	~DrawDoor();
private:
	DoorUI* _du;
	Document trans_door;
	vector<int> v_doorCnt;
	Vector<Sprite*> v_spr;
};

