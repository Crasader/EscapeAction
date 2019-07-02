#include "JSONtest.h"

bool JSONtest::init()
{
	testLevel = 5;
	rmCnt = (testLevel * 2) + 2;//1���� �ö󰥶����� ��+2, 1Level : 4��, 2Level: 6��...
	bonusRmCnt = RandomHelper::random_int((int)rmCnt/3, (int)rmCnt/2);//���ʽ� ��
	parse_resName();//���ҽ� �̸� ���� open, res_name�� 

	parse_mapData();
	setData();
	return true;
}
void JSONtest::setData()//fieldData ���Ͽ� setData
{
	FILE* fp = fopen("fieldData.json", "rb");
	char readBuffer[500];
	FileReadStream is(fp, readBuffer, sizeof(readBuffer));

	field.ParseStream(is);

	fclose(fp);
	
}

void JSONtest::parse_mapData()
{
	
	map_data = NULL;
	map_data.SetObject();
	Document::AllocatorType& a = map_data.GetAllocator();
	
	//"info" ����
	rapidjson::Value info(kObjectType);
	info.AddMember("height", rapidjson::Value().SetInt(120), a);
	info.AddMember("width", rapidjson::Value().SetInt(48), a);
	map_data.AddMember("info",info, a);

	//"struct" (����)����
	rapidjson::Value sct(kArrayType);
	rapidjson::Value fl(kArrayType);
	


	FILE* fp = fopen("mapDataTest.json", "wb");
	char wirteBuffer[500];
	FileWriteStream os(fp, wirteBuffer, sizeof(wirteBuffer));
	Writer<FileWriteStream> writer(os);
	map_data.Accept(writer);
	fclose(fp);

}


void JSONtest::parse_resName()
{
	FILE* fname = fopen("ResourceName.json", "rb");
	char readBuffer_fname[500];
	FileReadStream name_s(fname, readBuffer_fname, sizeof(readBuffer_fname));
	res_name.ParseStream(name_s);
	fclose(fname);
}
JSONtest::~JSONtest()
{
}