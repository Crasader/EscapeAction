#pragma once
#include "cocos2d.h"
//JSON������ ����� �����ϱ� ���� ���
#include "external/json/document.h"
//JSON���� ����ȭ�� ���� ���
#include "external/json/filewritestream.h"
#include "external/json/writer.h"
#include "external/json/stringbuffer.h"
#include "external/json/filereadstream.h"//������ �����������
#include <cstdio>
#include "Furniture.h"

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
	int testLevel;//�׽�Ʈ�� ���� ����, Ŭ���̾�Ʈ���� ������ �޾Ҵٰ� ����
	int rmCnt;//�� ����
	int bonusRmCnt;//���ʽ� �� ����
	int floor;

	Document field;//field ������ �Ľ��ϱ����� document
	Document map_data;//�� ������ �Ľ��ϱ����� document
	Document res_name;//���ҽ� �̸� �о���� ���� document
	void parse_resName();
	void setData();
	void parse_mapData();////�� ������ set, �Ľ�
};

