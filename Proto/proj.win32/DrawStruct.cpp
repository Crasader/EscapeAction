#include "DrawStruct.h"


bool DrawStruct::init()
{
	Document draw_struct;
	//파일 내용 불러오기
	FILE* fp = fopen("jsonData/draw/drawStruct.json", "rb");
	char readBuffer[5000];
	FileReadStream is(fp, readBuffer, sizeof(readBuffer));
	draw_struct.ParseStream(is);
	fclose(fp);

	assert(draw_struct.IsArray());//타입 확인
	/*나중에 데이터로 받아와 넣기 수정*/
	int hgt = 120;
	int wid = 48;

	int floor = 0;
	for (auto& fl : draw_struct.GetArray()) {
		Color3B color(50, 50, 50);
		//벽 구조 그리기
		for (auto& wal : fl["wall"].GetArray()) {
			Sprite* wall = Sprite::create("struct/frame.png");
			wall->setAnchorPoint(Vec2(0.5, 0));
			wall->setPosition(Vec2(wal.GetInt()*wid, hgt * floor));
			wall->setColor(color);
			this->addChild(wall);
		}
		//문 구조 그리기
		for (auto& dor : fl["door"].GetArray()) {
			Sprite* door = Sprite::create("struct/frame_door.png");
			door->setAnchorPoint(Vec2(0.5, 0));
			door->setPosition(Vec2(dor.GetInt()*wid, hgt * floor));
			door->setColor(color);
			this->addChild(door);
		}
		//바닥 구조 그리기
		for (int i = fl["startPos"].GetInt(); i <= fl["lastPos"].GetInt(); i++) {
			bool ladPos = false;
			for (auto& lad : fl["ladder"].GetArray()) {
				if (i == lad.GetInt()) {
					ladPos = true;
					break;
				}
			}
			if (ladPos) {
				continue;
			}
			Sprite* grd = Sprite::create("struct/floor.png");
			grd->setAnchorPoint(Vec2(0.5, 1));
			grd->setPosition(Vec2(i*wid, hgt * floor));
			grd->setColor(color);
			this->addChild(grd);
		}
		//바닥 끝부분 그림, 왼쪽끝
		Sprite* floor_edge1 = Sprite::create("struct/floor_edge.png");
		floor_edge1->setAnchorPoint(Vec2(1, 1));
		floor_edge1->setPosition(Vec2((fl["startPos"].GetInt()-0.5)*wid, hgt * floor));
		floor_edge1->setColor(color);
		this->addChild(floor_edge1);
		//오른쪽 끝
		Sprite* floor_edge2 = Sprite::create("struct/floor_edge.png");
		floor_edge2->setAnchorPoint(Vec2(0, 1));
		floor_edge2->setPosition(Vec2((fl["lastPos"].GetInt()+0.5)*wid, hgt * floor));
		floor_edge2->setColor(color);
		this->addChild(floor_edge2);
		floor++;
	}
	/*int fl = 0;
	for (auto& floor : draw_struct.GetArray()) {
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

	}*/

	return true;
}

DrawStruct::~DrawStruct()
{
}
