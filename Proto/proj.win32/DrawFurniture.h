#pragma once

#include "external/json/document.h"
#include "external/json/filereadstream.h"//������ �����������
#include <cstdio>
#include "cocos2d.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
using namespace std;
using namespace rapidjson;

class DrawFurniture :public Node
{
public:
	CREATE_FUNC(DrawFurniture);
	virtual bool init();
	~DrawFurniture();
private:
	Document field;
};

