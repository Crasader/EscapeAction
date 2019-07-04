#include "DrawFurniture.h"




bool DrawFurniture::init()
{
	FILE* fp = fopen("jsonData/draw/drawFur.json", "rb");
	char readBuffer[5000];
	FileReadStream is(fp, readBuffer, sizeof(readBuffer));
	field.ParseStream(is);
	fclose(fp);

	assert(field.IsArray());//Ÿ�� Ȯ��
	
	/*���߿� ������ �����ϱ�*/
	int hgt = 120;
	int wid = 48;


	int fl = 0;
	for (auto& floor : field.GetArray()) {
		for (auto& rm : floor.GetArray()) {
			for (auto& fur : rm.GetArray()) {
				Sprite* furni = Sprite::create(fur["name"].GetString());
				furni->setAnchorPoint(Vec2(0.5,0));
				furni->setPosition(fur["pos"].GetFloat()*wid, hgt*fl);
				this->addChild(furni);
			}
		}
		fl++;
	}

	return true;
}

DrawFurniture::~DrawFurniture()
{
}
