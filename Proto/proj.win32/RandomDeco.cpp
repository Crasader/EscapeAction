#include "RandomDeco.h"



bool RandomDeco::init()
{
	Document name_deco;
	FILE* fp = fopen("jsonData/name/nameDeco.json", "rb");
	char readBuffer[5000];
	FileReadStream is(fp, readBuffer, sizeof(readBuffer));
	name_deco.ParseStream(is);
	fclose(fp);

	assert(name_deco.IsArray());
	int resCnt = -1;
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

string RandomDeco::getDecoName()
{
	return deco;
}
