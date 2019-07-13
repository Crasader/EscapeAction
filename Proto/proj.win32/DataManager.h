#pragma once
#include "cocos2d.h"
#include "external/json/document.h"
#include "external/json/filereadstream.h"//파일을 열어오기위함
#include <cstdio>
using namespace rapidjson;
using namespace std;
USING_NS_CC;
class DataManager
{
	/*첫 게임 실행 이후 바뀌지 않는 데이터*/
private:
	DataManager();
	~DataManager();
	Document name_wall;
	Document name_deco;
	Document name_fur;
public:
	static DataManager* getInstance();
	Document* getWallData();
	Document* getDecoData();
	Document* getFurData();
};

