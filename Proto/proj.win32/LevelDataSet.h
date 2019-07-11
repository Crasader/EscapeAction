#pragma once
#include "cocos2d.h"
//데이터 parse
#include "external/json/document.h"
//데이터 파일 내보내기
#include "external/json/writer.h"
#include "external/json/filewritestream.h"
//c언어의 FILE 사용
#include <cstdio>
#include <iostream>
//Resource 이름을 받아오기 위함
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
	FILE* fp;
	char writeBuffer[5000];

	//함수
	void setRoomCnt(int level);//방, 층 갯수 설정, 탈출 방 위치 설정
	void setWallData();
	void setDoorData();
	void setLadderData();
	void setFurData();
	void setStructData();
	void setDeco();
	//void setData();
	//변수
	int testLevel;  ///*실제 레벨 받아오는 걸로 변경!*///
	int* floor_rm;//층수당 방 갯수
	int fl_maxWl;//층수당 최대 벽 갯수
	int fl_maxRm;//층수당 최대 방갯수
	int fl_minRm;//층수당 최소 방갯수

	int* escRmfl;//탈출방 층수
	int* escRmNum;//해당 층에서 탈출방 번호
	int* escRm;//모든 방중 탈출방 번호

	int* ladfl;//층당 사다리 갯수

	//Documents
	Document draw_wall;
	Document draw_fur;
	Document draw_struct;
	Document draw_deco;

	Document trans_item;
	Document trans_door;
	Document trans_ladder;

	Document check_blank;
	
};

