#include "DrawField.h"

bool DrawField::init()
{
	Size win_size = Director::getInstance()->getWinSize();
	Sprite* _wall = Sprite::create("wall/Wall1.png");
	_wall->retain();
	Size wall_size = _wall->getContentSize();
	_wall->release();
	//파일 내용 불러오기
	FILE* fp = fopen("jsonData/draw/drawWall.json", "rb");
	char readBuffer[5000];
	FileReadStream is(fp, readBuffer, sizeof(readBuffer));
	field.ParseStream(is);
	fclose(fp);

	int rm_tag = 0;

	assert(field.IsArray());//타입 확인

	/*값 받아 오는 걸로 수정*/
	int hgt = 120;
	int wid = 48;
	/*
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
	}*/
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
