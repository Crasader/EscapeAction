#include "DrawField.h"

bool DrawField::init()
{
	Size win_size = Director::getInstance()->getWinSize();
	Sprite* _wall = Sprite::create("wall/Wall1.png");
	_wall->retain();
	Size wall_size = _wall->getContentSize();
	_wall->release();
	int posX = 0;
	int posY = 0;
	//���� ���� �ҷ�����
	FILE* fp = fopen("fieldData.json", "rb");
	char readBuffer[500];
	FileReadStream is(fp, readBuffer, sizeof(readBuffer));
	field.ParseStream(is);
	fclose(fp);


	assert(field.IsObject());//Ÿ�� Ȯ��
	assert(field.HasMember("room"));//�޾ƿ;� �� ������ �ִ��� Ȯ��
	rapidjson::Value& rm = field["room"];
	assert(rm.IsArray());
	for (auto& ecR : rm.GetArray()) {
		assert(ecR.IsObject());
		assert(ecR.HasMember("Wall"));
		rapidjson::Value& wall = ecR["Wall"];
		assert(wall.IsArray());
		posX = 0;
		for (auto& ecW : wall.GetArray()) {
			assert(ecW.IsString());
			//�� ��������Ʈ ����
			Sprite* wall = Sprite::create(ecW.GetString());
			//wall->setAnchorPoint(Vec2::ZERO);
			wall->setPosition(wall_size.width*posX, (wall_size.height)*posY+20);
			this->addChild(wall);
			log("%s", ecW.GetString());
			posX++;
		}
		posY++;
	}
	return true;
}

void DrawField::setJSON(rapidjson::Document * d)
{
}

DrawField::~DrawField()
{
}
