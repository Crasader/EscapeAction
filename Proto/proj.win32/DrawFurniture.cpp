#include "DrawFurniture.h"




bool DrawFurniture::init()
{
	FILE* fp = fopen("fieldData.json", "rb");
	char readBuffer[500];
	FileReadStream is(fp, readBuffer, sizeof(readBuffer));
	field.ParseStream(is);
	fclose(fp);

	assert(field.IsObject());//Ÿ�� Ȯ��

	assert(field.HasMember("info"));
	int hgt = field["info"]["height"].GetInt();
	int wid = field["info"]["width"].GetInt();

	assert(field.HasMember("room"));//�޾ƿ;� �� ������ �ִ��� Ȯ��
	for (auto& rm : field["room"].GetArray()) {
		assert(rm.IsObject());
		assert(rm.HasMember("furniture"));

		for (auto& fur : rm["furniture"].GetArray()) {;
			//�� ��������Ʈ ����
			Sprite* furni = Sprite::create(fur["img"].GetString());
			furni->setAnchorPoint(Vec2(0.5,0));
			furni->setPosition(fur["pos"].GetInt()*wid, hgt*rm["floor"].GetInt());
			this->addChild(furni);
		}
	}

	return true;
}

DrawFurniture::~DrawFurniture()
{
}
