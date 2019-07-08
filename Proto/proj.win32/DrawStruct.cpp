#include "DrawStruct.h"


bool DrawStruct::init()
{
		Document field;
	//���� ���� �ҷ�����
	FILE* fp = fopen("jsonData/draw/drawStruct.json", "rb");
	char readBuffer[5000];
	FileReadStream is(fp, readBuffer, sizeof(readBuffer));
	field.ParseStream(is);
	fclose(fp);

	assert(field.IsArray());//Ÿ�� Ȯ��
	/*���߿� �����ͷ� �޾ƿ� �ֱ� ����*/
	int hgt = 120;
	int wid = 48;

	int fl = 0;
	for (auto& floor : field.GetArray()) {
		Color3B color(50,50,50);
		//���� �ִ� �� �׸�
		assert(floor.HasMember("door"));
		for (auto& dr : floor["door"].GetArray()) {
			Sprite* door = Sprite::create("struct/frame_door.png");
			door->setAnchorPoint(Vec2(0.5, 0));
			door->setPosition(Vec2(dr.GetDouble()*wid, hgt * fl));
			door->setColor(color);
			this->addChild(door);
		}
		//�� �׸�
		assert(floor.HasMember("wall"));
		for (auto& wl : floor["wall"].GetArray()) {
			Sprite* wall = Sprite::create("struct/frame.png");
			wall->setAnchorPoint(Vec2(0.5, 0));
			wall->setPosition(Vec2(wl.GetDouble()*wid, hgt * fl));
			wall->setColor(color);
			this->addChild(wall);
		}
		assert(floor.HasMember("count"));
		//�ٴ� �׸�
		for (int i = 0; i < floor["count"].GetInt(); i++) {
			Sprite* tile = Sprite::create("struct/floor.png");
			tile->setAnchorPoint(Vec2(0, 1));
			tile->setPosition(Vec2((floor["startPos"].GetInt()+ i)*wid, hgt*fl));
			tile->setColor(color);
			this->addChild(tile);
		}
		//�ٴ� ���κ� �׸�, ���ʳ�
		Sprite* floor_edge1 = Sprite::create("struct/floor_edge.png");
		floor_edge1->setAnchorPoint(Vec2(1, 1));
		floor_edge1->setPosition(Vec2(floor["startPos"].GetInt()*wid, hgt * fl));
		floor_edge1->setColor(color);
		this->addChild(floor_edge1);
		//������ ��
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
