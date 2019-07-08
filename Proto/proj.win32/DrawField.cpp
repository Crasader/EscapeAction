#include "DrawField.h"

bool DrawField::init()
{
	//초기화
	v_first.clear();
	v_last.clear();

	Document field;
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

	int fl = 0;
	for (auto& floor : field.GetArray()) {

		for (auto& rm : floor.GetArray()) {
			float i = rm["pos"].GetDouble()*wid;
			v_first.push_back(i);
			for (auto& wl : rm["tile"].GetArray()) {
				Sprite* wall = Sprite::create(wl.GetString());
				wall->setAnchorPoint(Vec2::ZERO);
				wall->setPosition(i, hgt*fl);
				this->addChild(wall);
				i += wall->getContentSize().width;
			}
			v_last.push_back(i);
		}
		fl++;
	}
	return true;
}
float DrawField::getFirst(int num)
{
	return v_first.at(num);
}
float DrawField::getLast(int num)
{
	return v_last.at(num);
}
DrawField::~DrawField()
{
}
