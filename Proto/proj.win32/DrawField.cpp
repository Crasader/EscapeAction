#include "DrawField.h"

bool DrawField::init()
{

	Document field;
	//���� ���� �ҷ�����
	FILE* fp = fopen("jsonData/draw/drawWall.json", "rb");
	char readBuffer[5000];
	FileReadStream is(fp, readBuffer, sizeof(readBuffer));
	field.ParseStream(is);
	fclose(fp);

	int rm_tag = 0;

	assert(field.IsArray());//Ÿ�� Ȯ��

	/*�� �޾� ���� �ɷ� ����*/
	int hgt = 120;
	int wid = 48;

	int fl = 0;
	for (auto& floor : field.GetArray()) {

		for (auto& rm : floor.GetArray()) {
			float i = rm["pos"].GetDouble()*wid;
			for (auto& wl : rm["tile"].GetArray()) {
				Sprite* wall = Sprite::create(wl.GetString());
				wall->setAnchorPoint(Vec2::ZERO);
				wall->setPosition(i, hgt*fl);
				this->addChild(wall);
				i += wall->getContentSize().width;
			}
		}
		fl++;
	}
	return true;
}
DrawField::~DrawField()
{
}
