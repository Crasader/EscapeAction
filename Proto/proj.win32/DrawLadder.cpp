#include "DrawLadder.h"
#include "GameManager.h"
bool DrawLadder::init()
{
	_lu = NULL;
	_floor = 0;
	v_ladderCnt.clear();
	v_spr.clear();

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
	int ladder_cnt = 0;
	for (auto& floor : trans_ladder.GetArray()) {
		for (auto& dr : floor.GetArray()) {
			float i = dr["pos"].GetInt()*wid;
			Sprite* ladder = Sprite::create("door/ladder_goup.png");
			ladder->setAnchorPoint(Vec2(0.5,0));
			ladder->setPosition(i, hgt*fl);
			this->addChild(ladder);
			v_spr.pushBack(ladder);
			ladder_cnt++;
		}
		v_ladderCnt.push_back(ladder_cnt);
		fl++;
	}
	return true;
}

DrawLadder::~DrawLadder()
{
}

void DrawLadder::checkLadder()
{
	int playerFloor = GameManager::getInstance()->getPlayerFloor();
	Rect playerRect = GameManager::getInstance()->getPlayerRect();
	//�÷��̾� ���� ��ٸ� ���� �ٸ���, �� ���� �̵��� ���
	if (playerFloor != _floor) {
		//�̵� �� ���� ��ư �Ⱥ��̰�!
		int fir;
		if (_floor == 0) {
			fir = 0;
		}
		else {
			fir = v_ladderCnt.at(_floor - 1);
		}
		int last = v_ladderCnt.at(_floor);
		for (int i = fir; i < last; i++) {
			_lu->setBtnVisible(i, false);
		}

		_floor = playerFloor;
		//�̵��� ���� �Ʒ��� ��ư �ű��
		int hgt = 120;
		if (_floor == 0) {
			fir = 0;
			last = 0;
		}
		else if (_floor == 1) {
			fir = 0;
			last = v_ladderCnt.at(0);
		}
		else {
			fir = v_ladderCnt.at(_floor - 2);
			last = v_ladderCnt.at(_floor);
		}
		for (int i = fir; i < last; i++) {
			_lu->setBtnPositionY(i, hgt*_floor+(0.1*hgt));
		}
		//�̵��� �� ��ư �ű��
		if (_floor == 0) {
			fir = 0;
		}
		else {
			fir = v_ladderCnt.at(_floor - 1);
		}
		last = v_ladderCnt.at(_floor);
		for (int i = fir; i < last; i++) {
			_lu->setBtnPositionY(i, hgt*_floor + (0.3*hgt));
		}
	}
	int fir;
	if (_floor <= 1) {
		fir = 0;
	}
	else {
		fir = v_ladderCnt.at(_floor - 2);
	}
	int last = v_ladderCnt.at(_floor);
	//�ش����� �Ʒ����� ��ٸ� �˻�
	for (int i = fir; i < last; i++) {
		Sprite* spr = v_spr.at(i);
		Rect spr_rc = spr->getBoundingBox();
		if (playerRect.intersectsRect(spr_rc)) {
			_lu->setBtnVisible(i, true);
		}
		else {
			_lu->setBtnVisible(i, false);
		}

	}
}

void DrawLadder::setLadderUI(LadderUI * lu)
{
	if (_lu == NULL) {
		_lu = lu;
	}
}
