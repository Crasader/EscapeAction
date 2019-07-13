#pragma once

#include "external/json/document.h"
#include "external/json/filereadstream.h"//파일을 열어오기위함
#include <cstdio>
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "FurnitureUI.h"

USING_NS_CC;
using namespace std;
using namespace rapidjson;
class DrawFurniture :public Node
{
public:
	CREATE_FUNC(DrawFurniture);
	virtual bool init();
	void checkFur();
	~DrawFurniture();

	void setFurUI(FurnitureUI* fu);

private:
	int _roomNum;
	vector<int> v_furCnt;//가구 갯수 누적
	Vector<Sprite*> v_spr;
	FurnitureUI* _fu;
};

