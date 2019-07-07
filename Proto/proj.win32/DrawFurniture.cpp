#include "DrawFurniture.h"




bool DrawFurniture::init()
{
//�ʱ�ȭ
	_fu = NULL;
	v_spr.clear();

	Document draw_fur;
	FILE* fp = fopen("jsonData/draw/drawFur.json", "rb");
	char readBuffer[5000];
	FileReadStream is(fp, readBuffer, sizeof(readBuffer));
	draw_fur.ParseStream(is);
	fclose(fp);

	assert(draw_fur.IsArray());//Ÿ�� Ȯ��

	/*���߿� ������ �����ϱ�*/
	int hgt = 120;
	int wid = 48;

	int fl = 0;
	int furCnt = 0;
	for (auto& floor : draw_fur.GetArray()) {
		for (auto& rm : floor.GetArray()) {
			for (auto& fur : rm.GetArray()) {
				//���� sprite ����
				Sprite* furni = Sprite::create(fur["name"].GetString());
				if (RandomHelper::random_int(0, 1) == 1) {
					furni->setFlipX(true);
				}
				furni->setAnchorPoint(Vec2(0.5, 0));
				furni->setPosition(fur["pos"].GetFloat()*wid, hgt*fl);
				this->addChild(furni);
				v_spr.pushBack(furni);
				furCnt++;
			}
			v_furCnt.push_back(furCnt);
		}
		fl++;
	}

	return true;
}

void DrawFurniture::checkFur(Rect player,int roomNum)
{
	int fir;
	if (roomNum == 0) {
		fir = 0;
	}
	else {
		fir = v_furCnt.at(roomNum - 1);
	}
	int last = v_furCnt.at(roomNum);
	Vector<Sprite*>::iterator iter = v_spr.begin()+fir;
	//���� ���� ������ player�� ��ġ���� üũ
	for (iter; iter != v_spr.begin() + last; iter++) {
		Rect fur_rect = v_spr.at(fir)->getBoundingBox();
		if (player.intersectsRect(fur_rect)) {
			_fu->setBtnVisible(fir, true);
		}
		else {
			_fu->setBtnVisible(fir, false);
		}
		fir++;
	}
}

DrawFurniture::~DrawFurniture()
{
}

void DrawFurniture::setFurUI(FurnitureUI * fu)
{
	_fu = fu;
}

/*
bool DrawFurniture::getCheck()
{
	if (_checkFurNum != -1) {
		return true;
	}
	else {
		return false;
	}
}

float DrawFurniture::getCheckPos()
{
	return check_furpos;
}

void DrawFurniture::setCheckFalse()
{
	ProgressTimer* progress = v_pro.at(_checkFurNum);
	progress->setVisible(false);
	_checkFurNum = -1;
}

void DrawFurniture::clickBtn(int num)
{
	if (_checkFurNum == -1) {
		int time = 2;
		ProgressTimer* progress = v_pro.at(num);
		progress->setVisible(true);
		ProgressFromTo* fromTo = ProgressFromTo::create(time, 0.0, 100.0);
		TintTo* tint = TintTo::create(time*0.1,Color3B::GRAY);
		TintTo* tint2 = TintTo::create(time*0.1,Color3B::WHITE);
		Sequence* tintSq = Sequence::create(tint, tint2, NULL);
		Repeat* re = Repeat::create(tintSq, 5);
		Spawn* sp = Spawn::create(fromTo, re,NULL);
		CallFunc* callF = CallFunc::create(CC_CALLBACK_0(DrawFurniture::endCheck,this));
		Sequence* sq = Sequence::create(sp, callF, NULL);
		check_furpos = progress->getPositionX();
		progress->runAction(sq);
		_checkFurNum = num;
		log("click!");
	}
}

void DrawFurniture::endCheck()
{
	ProgressTimer* progress = v_pro.at(_checkFurNum);
	progress->setVisible(false);
	_checkFurNum = -1;
}*/
