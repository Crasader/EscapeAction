#include "DrawDeco.h"


bool DrawDeco::init()
{
	FILE* fp = fopen("jsonData/draw/drawDeco.json", "rb");
	char readBuffer[5000];
	FileReadStream is(fp, readBuffer, sizeof(readBuffer));
	draw_deco.ParseStream(is);
	fclose(fp);

	assert(draw_deco.IsArray());//타입 확인

	/*나중에 변수로 수정하기*/
	int hgt = 120;
	int wid = 48;


	int fl = 0;
	for (auto& floor : draw_deco.GetArray()) {
			for (auto& deco : floor.GetArray()) {
				Sprite* decoration = Sprite::create(deco["name"].GetString());
				decoration->setAnchorPoint(Vec2(0.5, 0));
				decoration->setPosition(deco["pos"].GetFloat()*wid, hgt*fl);
				this->addChild(decoration);
			}
		fl++;
	}
	return true;
}

DrawDeco::~DrawDeco()
{
}
