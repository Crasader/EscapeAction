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
	static RandomDeco* create(int cnt);
	virtual bool init();
	virtual bool init(int cnt);
	CREATE_FUNC(RandomDeco);
	~RandomDeco();

	string getDecoName(int index);
	int getDecoCnt();
private:
	vector<int> deco_res;
	vector<string> deco_name;
	int _cnt;
};

