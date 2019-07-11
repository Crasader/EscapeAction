#include "RandomWall.h"
#include "DataManager.h"

bool RandomWall::init()
{
	int resCnt = DataManager::getInstance()->getWallData()->GetArray().Size();
	
	int rand = RandomHelper::random_int(0, resCnt-1);
	wall = DataManager::getInstance()->getWallData()->GetArray()[rand]["tile_name"].GetString();
	wallEdge = DataManager::getInstance()->getWallData()->GetArray()[rand]["edge_name"].GetString();

	return true;
}

RandomWall::~RandomWall()
{
}

string RandomWall::getWallName()
{
	return wall;
}

string RandomWall::getWallEdgeName()
{
	return wallEdge;
}
