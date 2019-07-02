#pragma once
#include "cocos2d.h"
//JSON문서를 만들고 조작하기 위한 헤더
#include "external/json/document.h"
//JSON문서 직렬화를 위한 헤더
#include "external/json/filewritestream.h"
#include "external/json/writer.h"
#include "external/json/stringbuffer.h"
#include "external/json/filereadstream.h"//파일을 열어오기위함
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
	int testLevel;//테스트를 위한 레벨, 클라이언트에서 레벨을 받았다고 가정
	int rmCnt;//방 갯수
	int bonusRmCnt;//보너스 방 갯수

	Document field;//field 데이터 파싱하기위한 document
	Document map_data;//맵 데이터 파싱하기위한 document
	Document res_name;//리소스 이름 읽어오기 위한 document
	void parse_resName();
	void setData();
	void parse_mapData();////맵 데이터 set, 파싱
};

