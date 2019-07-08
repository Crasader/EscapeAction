#include "DrawStruct.h"


bool DrawStruct::init()
{
		Document field;
	//파일 내용 불러오기
	FILE* fp = fopen("jsonData/draw/drawStruct.json", "rb");
	char readBuffer[5000];
	FileReadStream is(fp, readBuffer, sizeof(readBuffer));
	field.ParseStream(is);
	fclose(fp);

	assert(field.IsArray());//타입 확인
	/*나중에 데이터로 받아와 넣기 수정*/
	int hgt = 120;
	int wid = 48;

	int fl = 0;
	for (auto& floor : field.GetArray()) {
		Color3B color(50,50,50);
		//문이 있는 벽 그림
		assert(floor.HasMember("door"));
		for (auto& dr : floor["door"].GetArray()) {
			Sprite* door = Sprite::create("struct/frame_door.png");
			door->setAnchorPoint(Vec2(0.5, 0));
			door->setPosition(Vec2(dr.GetDouble()*wid, hgt * fl));
			door->setColor(color);
			this->addChild(door);
		}
		//벽 그림
		assert(floor.HasMember("wall"));
		for (auto& wl : floor["wall"].GetArray()) {
			Sprite* wall = Sprite::create("struct/frame.png");
			wall->setAnchorPoint(Vec2(0.5, 0));
			wall->setPosition(Vec2(wl.GetDouble()*wid, hgt * fl));
			wall->setColor(color);
			this->addChild(wall);
		}
		assert(floor.HasMember("count"));
		//바닥 그림
		for (int i = 0; i < floor["count"].GetInt(); i++) {
			Sprite* tile = Sprite::create("struct/floor.png");
			tile->setAnchorPoint(Vec2(0, 1));
			tile->setPosition(Vec2((floor["startPos"].GetInt()+ i)*wid, hgt*fl));
			tile->setColor(color);
			this->addChild(tile);
		}
		//바닥 끝부분 그림, 왼쪽끝
		Sprite* floor_edge1 = Sprite::create("struct/floor_edge.png");
		floor_edge1->setAnchorPoint(Vec2(1, 1));
		floor_edge1->setPosition(Vec2(floor["startPos"].GetInt()*wid, hgt * fl));
		floor_edge1->setColor(color);
		this->addChild(floor_edge1);
		//오른쪽 끝
		Sprite* floor_edge2 = Sprite::create("struct/floor_edge.png");
		floor_edge2->setAnchorPoint(Vec2(0, 1));
		floor_edge2->setPosition(Vec2((floor["startPos"].GetInt() + floor["count"].GetInt()) * 48, hgt * fl));
		floor_edge2->setColor(color);
		this->addChild(floor_edge2);
		fl++;
	}

	return true;
}

DrawStruct::~DrawStruct()
{
}
