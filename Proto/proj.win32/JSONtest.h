#pragma once
#include "cocos2d.h"
//JSON������ ����� �����ϱ� ���� ���
#include "external/json/document.h"
//JSON���� ����ȭ�� ���� ���
//#include "external/json/writer.h"
//#include "external/json/stringbuffer.h"
#include "external/json/filereadstream.h"//������ �����������
#include <cstdio>
USING_NS_CC;
using namespace rapidjson;
using namespace std;
class JSONtest : public Node
{
public:
	CREATE_FUNC(JSONtest);
	virtual bool init();
	~JSONtest();
private:
	Document field;
	void setData();
};

