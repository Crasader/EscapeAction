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
	bool checkSearch();//Ž�������� Ȯ��
	float getPos();//��ġ ���Ͻ� ��ġ �޾ƿ���
	void setStart();
	void setCancle();//ĳ���� �̵��� Ž�� ����
	void changeRm();
	~FurnitureUI();
private:
	Vector<ui::Button*> v_chekcBtn;
	Vector<ui::Button*> v_btn;
	Vector<ProgressTimer*> v_pro;
	int check_furNum;//üũ���� ���� ��ȣ, -1�̸� üũ x
	bool startSearch;
	//�Լ�
	void clickBtn(int num);
	void schedule_clickBtn(float dt);

};

