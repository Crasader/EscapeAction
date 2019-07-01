#pragma once
#include "external/json/document.h"
#include "external/json/filereadstream.h"//파일을 열어오기위함
#include <cstdio>
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
using namespace rapidjson;

class DrawStruct:public Node
{
public:
	CREATE_FUNC(DrawStruct);
	virtual bool init();
	~DrawStruct();
private:
	Document field;
};

