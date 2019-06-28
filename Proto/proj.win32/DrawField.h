#pragma once
#include "external/json/document.h"
#include "cocos2d.h"
USING_NS_CC;

class DrawField : public Node
{
public:
	CREATE_FUNC(DrawField);
	virtual bool init();
	void setJSON(rapidjson::Document* d);
	~DrawField();
private:
	rapidjson::Document* _d;
};

