#pragma once

#include "external/json/document.h"
#include "external/json/filereadstream.h"//������ �����������
#include <cstdio>
#include "cocos2d.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
using namespace std;
using namespace rapidjson;;
class DrawFurniture :public Node
{
public:
	CREATE_FUNC(DrawFurniture);
	virtual bool init();
	void checkFur(Rect player, int roomNum);
	~DrawFurniture();
	bool getCheck();//üũ ������ Ȯ��
	float getCheckPos();
	void setCheckFalse();
private:
	int _checkFurNum;//üũ���� ���� ��ȣ. �ƴҶ��� -1
	vector<int> v_furCnt;//���� ���� ����
	Vector<Sprite*> v_spr;
	Vector<ui::Button*> v_btn;
	Vector<ProgressTimer*> v_pro;
	float check_furpos;

	void clickBtn(int num);
	void endCheck();
};

