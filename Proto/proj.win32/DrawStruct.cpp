#include "DrawStruct.h"


bool DrawStruct::init()
{
	//���� ���� �ҷ�����
	FILE* fp = fopen("fieldData.json", "rb");
	char readBuffer[500];
	FileReadStream is(fp, readBuffer, sizeof(readBuffer));
	field.ParseStream(is);
	fclose(fp);

	assert(field.IsObject());//Ÿ�� Ȯ��
	
	assert(field.HasMember("info"));
	int hgt = field["info"]["height"].GetInt();
	int wid = field["info"]["width"].GetInt();

	assert(field.HasMember("struct"));//�޾ƿ;� �� ������ �ִ��� Ȯ��
	assert(field["struct"].IsArray());
	for (auto& st : field["struct"].GetArray()) {
		assert(st.HasMember("floor"));
		assert(st["floor"].IsArray());
		int y = 0;
		for (auto& fl : st["floor"].GetArray()) {
			//���� �ִ� �� �׸�
			assert(fl.HasMember("door"));
			for (auto& dr : fl["door"].GetArray()) {
				Sprite* door = Sprite::create("struct/frame_door.png");
				door->setAnchorPoint(Vec2(0.5, 0));
				door->setPosition(Vec2(dr.GetDouble()*wid, hgt * y));
				door->setColor(Color3B::GRAY);
				this->addChild(door);
			}
			//�� �׸�
			assert(fl.HasMember("wall"));
			for (auto& wl : fl["wall"].GetArray()) {
				Sprite* wall = Sprite::create("struct/frame.png");
				wall->setAnchorPoint(Vec2(0.5, 0));
				wall->setPosition(Vec2(wl.GetDouble()*wid, hgt * y));
				wall->setColor(Color3B::GRAY);
				this->addChild(wall);
			}
			assert(fl.HasMember("count"));
			//�ٴ� �׸�
			for (int i = 0; i < fl["count"].GetInt(); i++) {
				Sprite* floor = Sprite::create("struct/floor.png");
				floor->setAnchorPoint(Vec2(0, 1));
				floor->setPosition(Vec2((fl["firstX"].GetDouble()+i)*wid, hgt*y));
				floor->setColor(Color3B::GRAY);
				this->addChild(floor);
			}
			//�ٴ� ���κ� �׸�, ���ʳ�
			Sprite* floor_edge1 = Sprite::create("struct/floor_edge.png");
			floor_edge1->setAnchorPoint(Vec2(1, 1));
			floor_edge1->setPosition(Vec2(fl["firstX"].GetDouble()*wid, hgt * y));
			floor_edge1->setColor(Color3B::GRAY);
			this->addChild(floor_edge1);
			//������ ��
			Sprite* floor_edge2 = Sprite::create("struct/floor_edge.png");
			floor_edge2->setAnchorPoint(Vec2(0, 1));
			floor_edge2->setPosition(Vec2((fl["firstX"].GetDouble()+ fl["count"].GetInt())*48, hgt * y));
			floor_edge2->setColor(Color3B::GRAY);
			this->addChild(floor_edge2);
			y++;
		}
	}
	return true;
}

DrawStruct::~DrawStruct()
{
}
