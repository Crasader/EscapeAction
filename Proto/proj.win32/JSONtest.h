#pragma once
#include "cocos2d.h"
//JSON������ ����� �����ϱ� ���� ���
#include "external/json/document.h"
//JSON���� ����ȭ�� ���� ���
#include "external/json/writer.h"
#include "external/json/stringbuffer.h"
#include "external/json/filereadstream.h"//������ �����������
#include <stdio.h>
USING_NS_CC;

class JSONtest : public Node
{
public:
	CREATE_FUNC(JSONtest);
	virtual bool init();
	~JSONtest();
	rapidjson::Document* getJSON();
private:
	rapidjson::Document* jsonDoc;
	void setData();
};

