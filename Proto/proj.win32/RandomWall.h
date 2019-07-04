#pragma once
#include "cocos2d.h"

#include "external/json/document.h"
#include "external/json/filereadstream.h"
#include <string>
USING_NS_CC;
using namespace std;
using namespace rapidjson;

class RandomWall:public Node
{
public:
	CREATE_FUNC(RandomWall);
	virtual bool init();
	~RandomWall();

	string getWallName();
	string getWallEdgeName();
private:
	string wall;
	string wallEdge;
};

