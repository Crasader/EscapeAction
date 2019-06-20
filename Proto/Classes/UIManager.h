#pragma once
#include "cocos2d.h"
#include <iostream>
#include "Button_Ui.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

class UIManager
{
private:
	UIManager();
	~UIManager();

	ui::Button* _atk;
	ui::Button* _search;
	ui::Button* _key;
	ui::Button* _trap;

public:
	static UIManager* getInstance();

	//return false�� �̹� ��ư�� set�� ����
	//��ư�� NULL�϶��� set
	bool setAtkBtn(ui::Button* atk);
	bool setSearchBtn(ui::Button* search);
	bool setKeyBtn(ui::Button* key);
	bool setTrapBtn(ui::Button* trap);


	//��ư�� setEnable
	void setEnable_AtkBtn(bool enable);
	void setEnable_SearchBtn(bool enable);
	void setEnable_KeyBtn(bool enable);
	void setEnable_TrapBtn(bool enable);


};

