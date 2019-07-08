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
	float getFirst(int num);
	float getLast(int num);
	~DrawField();
private:
	vector<float> v_first;//�� ���� first pos
	vector<float> v_last;//last pos
};

