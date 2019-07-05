#pragma once
#include "cocos2d.h"

#include "external/json/document.h"
#include "external/json/filereadstream.h"
#include <string>
USING_NS_CC;
using namespace std;
using namespace rapidjson;

class RandomDeco : public Node
{
public:
	CREATE_FUNC(RandomDeco);
	virtual bool init();
	~RandomDeco();

	int getDecoCount();//장식 리소스 갯수 반환
	string getDecoName();
	void randDecoAgain();
private:
	Document name_deco;

	int resCnt;
	string deco;
};

