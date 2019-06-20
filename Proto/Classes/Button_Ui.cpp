#include "Button_Ui.h"

USING_NS_CC;

using namespace std;

bool player_Item::init()
{
	win_size = Director::getInstance()->getWinSize();

	auto button1 = ui::Button::create("Button_Disable.png", "Button_Normal.png", "Button_Press.png");
	button1->setTitleText("Button Text");
	button1->setPosition(Point(win_size.width*0.05,win_size.height*0.7));
	button1->addClickEventListener(CC_CALLBACK_0(player_Item::atkobj, this));
	button1->setName("btn1");
	button1->setEnabled(false);
	this->addChild(button1);

	auto button2 = ui::Button::create("Button_Disable.png", "Button_Normal.png", "Button_Press.png");
	button2->setTitleText("Button Text");
	button2->setPosition(Point(win_size.width*0.05, win_size.height*0.6));
	button2->addClickEventListener(CC_CALLBACK_0(player_Item::searchobj, this));
	button2->setName("btn2");
	button2->setEnabled(false);
	this->addChild(button2);

	auto button3 = ui::Button::create("Button_Disable.png", "Button_Normal.png", "Button_Press.png");
	button3->setTitleText("Button Text");
	button3->setPosition(Point(win_size.width*0.05, win_size.height*0.5));
	button3->addClickEventListener(CC_CALLBACK_0(player_Item::keyobj, this));
	button3->setName("btn3");
	button3->setEnabled(false);
	this->addChild(button3);

	auto button4 = ui::Button::create("Button_Disable.png", "Button_Normal.png", "Button_Press.png");
	button4->setTitleText("Button Text");
	button4->setPosition(Point(win_size.width*0.05, win_size.height*0.4));
	button4->addClickEventListener(CC_CALLBACK_0(player_Item::trapobj, this));
	button4->setName("btn4");
	button4->setEnabled(false);
	this->addChild(button4);

	this->scheduleUpdate();

    return true;
}

void player_Item::atkobj()
{
	CCLOG("atkobj");
}

void player_Item::searchobj()
{
	CCLOG("searchobj");
}
void player_Item::keyobj()
{
	CCLOG("keyobj");
}

void player_Item::trapobj()
{
	CCLOG("trapobj");
}

