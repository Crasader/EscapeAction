#pragma once
#include "cocos2d.h"
//������ parse
#include "external/json/document.h"
//������ ���� ��������
#include "external/json/writer.h"
#include "external/json/filewritestream.h"
//c����� FILE ���
#include <cstdio>
#include <iostream>
//Resource �̸��� �޾ƿ��� ����
#include "Furniture.h"
#include "RandomWall.h"
#include "RandomDeco.h"
#include <string>
USING_NS_CC;
using namespace std;
using namespace rapidjson;
class LevelDataSet : public Node
{
public:
	CREATE_FUNC(LevelDataSet);
	virtual bool init();
	~LevelDataSet();
private:
	//�Լ�
	void setRoomCnt(int level);//��, �� ���� ����, Ż�� �� ��ġ ����
	void setWallData();
	//void setData();
	//����
	int testLevel;  ///*���� ���� �޾ƿ��� �ɷ� ����!*///
	int* floor_rm;//������ �� ����
	int fl_maxWl;//������ �ִ� �� ����
	int fl_maxRm;//������ �ִ� �氹��
	int fl_minRm;//������ �ּ� �氹��

	int* escRmfl;//Ż��� ����
	int* escRmNum;//Ż��� ��ġ
	
	//Documents
	Document draw_wall;
};

