#pragma once
#include "external/json/document.h"
#include "external/json/filereadstream.h"//������ �����������
//������ ���� ��������
#include "external/json/writer.h"
#include "external/json/filewritestream.h"
//c����� FILE ���
#include <iostream>
#include <cstdio>

#include "cocos2d.h"

USING_NS_CC;
using namespace rapidjson;
using namespace std;
class DrawLadder :public Node
{
public:
	CREATE_FUNC(DrawLadder);
	virtual bool init();
	~DrawLadder();
private:
	
};

