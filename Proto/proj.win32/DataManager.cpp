#include "DataManager.h"

static DataManager* pDataManager = NULL;


DataManager::DataManager()
{
	//벽 리소스 데이터 
	FILE* fp = fopen("jsonData/name/nameWall.json", "rb");
	char readBuffer[5000];
	FileReadStream wall_is(fp, readBuffer, sizeof(readBuffer));
	name_wall.ParseStream(wall_is);
	fclose(fp);
	//장식 리소스 데이터
	strcat(readBuffer, "");
	fp = fopen("jsonData/name/nameDeco.json", "rb");
	FileReadStream deco_is(fp, readBuffer, sizeof(readBuffer));
	name_deco.ParseStream(deco_is);
	fclose(fp);
	//가구 리소스 데이터
	strcat(readBuffer, "");
	fp = fopen("jsonData/name/nameFur.json", "rb");
	FileReadStream fur_is(fp, readBuffer, sizeof(readBuffer));
	name_fur.ParseStream(fur_is);
	fclose(fp);

}


DataManager::~DataManager()
{
}

DataManager * DataManager::getInstance()
{
	if (pDataManager == NULL) {
		pDataManager = new DataManager();
	}
	return pDataManager;
}

Document * DataManager::getWallData()
{
	return &name_wall;
}

Document * DataManager::getDecoData()
{
	return &name_deco;
}

Document * DataManager::getFurData()
{
	return &name_fur;
}
