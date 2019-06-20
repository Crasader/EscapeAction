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
	ui::Button* _weapon;
public:
	static UIManager* getInstance();

	void setEnableWBtn(bool setEnable);
	void setWeaponBtn(ui::Button* weapon);

	ui::Button* getReserchBtn();
	void getReserchBtn(ui::Button* reserch);
};

