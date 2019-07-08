#include "RandomWall.h"


bool RandomWall::init()
{
	Document name_wall;
	FILE* fp = fopen("jsonData/name/nameWall.json", "rb");
	char readBuffer[5000];
	FileReadStream is(fp, readBuffer, sizeof(readBuffer));
	name_wall.ParseStream(is);
	fclose(fp);

	assert(name_wall.IsArray());
	int resCnt = -1;
	for (auto& wl : name_wall.GetArray()) {
		resCnt++;
	}
	
	int rand = RandomHelper::random_int(0, resCnt);
	assert(name_wall[rand].HasMember("tile_name"));
	wall = name_wall[rand]["tile_name"].GetString();
	assert(name_wall[rand].HasMember("edge_name"));
	wallEdge = name_wall[rand]["edge_name"].GetString();

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
