#include "DrawField.h"

bool DrawField::init()
{
	Size win_size = Director::getInstance()->getWinSize();
	Sprite* _wall = Sprite::create("wall/Wall1.png");
	_wall->retain();
	Size wall_size = _wall->getContentSize();
	_wall->release();
	//���� ���� �ҷ�����
	FILE* fp = fopen("fieldData.json", "rb");
	char readBuffer[500];
	FileReadStream is(fp, readBuffer, sizeof(readBuffer));
	field.ParseStream(is);
	fclose(fp);

	int rm_tag = 0;

	assert(field.IsObject());//Ÿ�� Ȯ��

	assert(field.HasMember("info"));
	int hgt = field["info"]["height"].GetInt();
	int wid = field["info"]["width"].GetInt();

	assert(field.HasMember("room"));//�޾ƿ;� �� ������ �ִ��� Ȯ��
	for (auto& rm : field["room"].GetArray()) {
		assert(rm.IsObject());
		assert(rm.HasMember("wall"));

		float i = rm["firstX"].GetDouble()*wid;
		for (auto& wl : rm["wall"].GetArray()) {
			assert(wl.IsString());
			//�� ��������Ʈ ����
			Sprite* wall = Sprite::create(wl.GetString());
			wall->setAnchorPoint(Vec2::ZERO);
			wall->setPosition(i, hgt*rm["floor"].GetInt());
			this->addChild(wall);
			i += wall->getContentSize().width;
		}
	}
	return true;
}

void DrawField::setJSON(rapidjson::Document * d)
{
}

DrawField::~DrawField()
{
}
