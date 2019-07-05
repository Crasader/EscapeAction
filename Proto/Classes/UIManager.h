#pragma once
#include "cocos2d.h"
#include <iostream>
#include "Button_Ui.h"
#include "ui/CocosGUI.h"
#include "Joystick.h"

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
	Joystick* _joystick;
	Button_Ui* _btn_ui;
	
public:
	static UIManager* getInstance();
	Point get_Player_m_p1();
	Vec2 get_Player_m_p2();	

	//return false�� �̹� ��ư�� set�� ����
	//��ư�� NULL�϶��� set
	bool setAtkBtn(ui::Button* atk);
	bool setSearchBtn(ui::Button* search);
	bool setKeyBtn(ui::Button* key);
	bool setTrapBtn(ui::Button* trap);
	//���̽�ƽ set
	bool setJoystick(Joystick* joystick);

	//��ư�� setEnable
	void setEnable_AtkBtn(bool enable);
	void setEnable_SearchBtn(bool enable);
	void setEnable_KeyBtn(bool enable);
	void setEnable_TrapBtn(bool enable);

	void set_btn_ui(Button_Ui* btn_ui);

	void set_atk_btn(bool atk);
	bool get_atk_btn();
	void set_src_btn(bool src);
	bool get_src_btn();

};

