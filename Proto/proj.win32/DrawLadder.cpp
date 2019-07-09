#include "DrawLadder.h"

bool DrawLadder::init()
{
	Document trans_ladder;

	//���� ���� �ҷ�����
	FILE* fp = fopen("jsonData/trans/transLadder.json", "rb");
	char readBuffer[5000];
	FileReadStream is(fp, readBuffer, sizeof(readBuffer));
	trans_ladder.ParseStream(is);
	fclose(fp);

/*�� �޾� ���� �ɷ� ����*/
	int hgt = 120;
	int wid = 48;

	assert(trans_ladder.IsArray());//Ÿ�� Ȯ��

	int fl = 0;
	int door_cnt = 0;
	for (auto& floor : trans_ladder.GetArray()) {
		for (auto& dr : floor.GetArray()) {
			float i = dr["pos"].GetInt()*wid;
			Sprite* ladder = Sprite::create("door/ladder_goup.png");
			ladder->setAnchorPoint(Vec2(0.5,0));
			ladder->setPosition(i, hgt*fl);
			this->addChild(ladder);
			door_cnt++;
		}
		fl++;
	}
	return true;
}

DrawLadder::~DrawLadder()
{
}
