#include "DrawField.h"

bool DrawField::init()
{
	Size win_size = Director::getInstance()->getWinSize();
	Sprite* _wall = Sprite::create("wall/Wall1.png");
	_wall->retain();
	Size wall_size = _wall->getContentSize();
	_wall->release();
	//파일 내용 불러오기
	FILE* fp = fopen("fieldData.json", "rb");
	char readBuffer[500];
	FileReadStream is(fp, readBuffer, sizeof(readBuffer));
	field.ParseStream(is);
	fclose(fp);

	int rm_tag = 0;

	assert(field.IsObject());//타입 확인

	assert(field.HasMember("info"));
	int hgt = field["info"]["height"].GetInt();
	int wid = field["info"]["width"].GetInt();

	assert(field.HasMember("room"));//받아와야 할 데이터 있는지 확인
	for (auto& rm : field["room"].GetArray()) {
		assert(rm.IsObject());
		assert(rm.HasMember("wall"));

		float i = rm["firstX"].GetDouble()*wid;
		for (auto& wl : rm["wall"].GetArray()) {
			assert(wl.IsString());
			//벽 스프라이트 생성
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
