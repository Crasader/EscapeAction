#include "JSONtest.h"

bool JSONtest::init()
{
	setData();
	return true;
}

JSONtest::~JSONtest()
{
}
void JSONtest::setData()
{
/*	FILE* fp = fopen("fieldData.json", "r");
	jsonDoc->SetObject();
	rapidjson::Document::AllocatorType& allocator = jsonDoc->GetAllocator();
	char readBuffer[500];
	rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));
	jsonDoc->ParseStream(is);
	const rapidjson::Value& a = (*jsonDoc)["room"];
	//log("%s", );
	//log("%s",(*jsonDoc)["room"].GetString());
	fclose(fp);*/

	FILE* fp = fopen("fieldData.json", "rb");
	char readBuffer[500];
	FileReadStream is(fp, readBuffer, sizeof(readBuffer));

	field.ParseStream(is);

	fclose(fp);
	
}
