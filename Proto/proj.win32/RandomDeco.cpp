#include "RandomDeco.h"



bool RandomDeco::init()
{
	name_deco;
	FILE* fp = fopen("jsonData/name/nameDeco.json", "rb");
	char readBuffer[5000];
	FileReadStream is(fp, readBuffer, sizeof(readBuffer));
	name_deco.ParseStream(is);
	fclose(fp);

	assert(name_deco.IsArray());
	resCnt = -1;
	for (auto& wl : name_deco.GetArray()) {
		resCnt++;
	}
	int rand = RandomHelper::random_int(0, resCnt);
	assert(name_deco[rand].IsString());
	deco = name_deco[rand].GetString();

	return true;
}

RandomDeco::~RandomDeco()
{
}

int RandomDeco::getDecoCount()
{
	return resCnt+1;
}

string RandomDeco::getDecoName()
{
	return deco;
}

void RandomDeco::randDecoAgain()
{
	int rand = RandomHelper::random_int(0, resCnt);
	assert(name_deco[rand].IsString());
	deco = name_deco[rand].GetString();
}
