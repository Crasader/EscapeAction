#pragma once
#include "external/json/document.h"
#include "external/json/filereadstream.h"//������ �����������
#include <cstdio>
#include "cocos2d.h"
USING_NS_CC;
using namespace rapidjson;
using namespace std;
class DrawField : public Node
{
public:
	CREATE_FUNC(DrawField);
	virtual bool init();
	void setJSON(rapidjson::Document* d);
	~DrawField();
private:
	rapidjson::Document field;
};

