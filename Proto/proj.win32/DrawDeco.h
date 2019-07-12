#pragma once
#include "external/json/document.h"
#include "external/json/filereadstream.h"//파일을 열어오기위함
#include <cstdio>
#include "cocos2d.h"
USING_NS_CC;
using namespace rapidjson;
using namespace std;
class DrawDeco : public Node
{
public:
	CREATE_FUNC(DrawDeco);
	virtual bool init();
	~DrawDeco();
private:
	Document draw_deco;
};

