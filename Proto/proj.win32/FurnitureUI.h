#pragma once
#include "external/json/document.h"
#include "external/json/filereadstream.h"//������ �����������
#include <cstdio>
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "UIManager.h"
USING_NS_CC;
using namespace std;
using namespace rapidjson;
class FurnitureUI:public Node
{
public:
	CREATE_FUNC(FurnitureUI);
	virtual bool init();
	void setBtnVisible(int num, bool setbool);
	void clearCheckBtnVector();
	~FurnitureUI();
private:
	Vector<ui::Button*> v_chekcBtn;//�÷��̾ ��ġ�� ��ȿ��� �̹� üũ�� ���� ����
	Vector<ui::Button*> v_btn;
	Vector<ProgressTimer*> v_pro;
	int _checkfurNum;
	//�Լ�
	void clickBtn(int num);
	void schedule_gotoBtn(float dt);//�÷��̾ ��ġ �ϱ����� �̵�
	void schedule_search(float dt);//�÷��̾� ��ġ

};

