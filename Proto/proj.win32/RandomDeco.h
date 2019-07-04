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

	string getDecoName();
private:
	string deco;
};

