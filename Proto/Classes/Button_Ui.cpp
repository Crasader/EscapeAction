#include "Button_Ui.h"

USING_NS_CC;

using namespace std;

bool Button_Ui::init()
{
	win_size = Director::getInstance()->getWinSize();

	button1 = ui::Button::create("Button_Disable.png", "Button_Normal.png", "Button_Press.png");
	button1->setTitleText("Button Text");
	button1->setPosition(Point(win_size.width*0.05,win_size.height*0.8));
	button1->addClickEventListener(CC_CALLBACK_0(Button_Ui::atkobj, this));
	button1->setName("btn1");
	button1->setEnabled(true);
	this->addChild(button1);

	button2 = ui::Button::create("Button_Disable.png", "Button_Normal.png", "Button_Press.png");
	button2->setTitleText("Button Text");
	button2->setPosition(Point(win_size.width*0.05, win_size.height*0.6));
	button2->addClickEventListener(CC_CALLBACK_0(Button_Ui::searchobj, this));
	button2->setName("btn2");
	button2->setEnabled(true);
	this->addChild(button2);

	button3 = ui::Button::create("Button_Disable.png", "Button_Normal.png", "Button_Press.png");
	button3->setTitleText("Button Text");
	button3->setPosition(Point(win_size.width*0.05, win_size.height*0.4));
	button3->addClickEventListener(CC_CALLBACK_0(Button_Ui::keyobj, this));
	button3->setName("btn3");
	button3->setEnabled(false);
	this->addChild(button3);

	button4 = ui::Button::create("Button_Disable.png", "Button_Normal.png", "Button_Press.png");
	button4->setTitleText("Button Text");
	button4->setPosition(Point(win_size.width*0.05, win_size.height*0.2));
	button4->addClickEventListener(CC_CALLBACK_0(Button_Ui::trapobj, this));
	button4->setName("btn4");
	button4->setEnabled(false);
	this->addChild(button4);

    return true;
}

void Button_Ui::atkobj()
{
	atk_on = true;
}

void Button_Ui::searchobj()
{
	search_on = true;

	/*auto player_p = (Sprite*) this->getChildByName("p_name")->getChildByName("player_move");
	auto obj_p = (Sprite*)this->getChildByName("btn1");
	auto btn = (ui::Button*) this->getChildByName("btn2");

	Rect rect_r = player_p -> getBoundingBox();
	Rect obj_r = obj_p -> getBoundingBox();

	if (rect_r.intersectsRect(obj_r)==true) {
		if (btn->isEnabled() == false){
			btn->setEnabled(true);			
		}
	}
	else
		btn->setEnabled(false);*/
}
void Button_Ui::keyobj()
{
	auto btn = (ui::Button*) this->getChildByName("btn3");
	if (key_count > 0)
	{
		btn->setEnabled(true);
	}
	else;
}

void Button_Ui::trapobj()
{
	auto btn = (ui::Button*) this->getChildByName("btn4");
	if (trap_count > 0)
	{
		btn->setEnabled(true);
	}
	else;
}