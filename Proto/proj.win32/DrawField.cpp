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
	//파일 내용 불러오기
	FILE* fp = fopen("fieldData.json", "rb");
	char readBuffer[500];
	FileReadStream is(fp, readBuffer, sizeof(readBuffer));
	field.ParseStream(is);
	fclose(fp);


	assert(field.IsObject());//타입 확인
	assert(field.HasMember("room"));//받아와야 할 데이터 있는지 확인
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
			//벽 스프라이트 생성
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
