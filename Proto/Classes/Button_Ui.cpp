#include "Button_Ui.h"
#include "../proj.win32/GameManager.h"

USING_NS_CC;

using namespace std;

bool Button_Ui::init()
{
	win_size = Director::getInstance()->getWinSize();

	auto button1 = ui::Button::create("Swordon.png", "Swordpush.png", "Swordoff.png");
	button1->setScale(1.5);
	button1->setPosition(Point(win_size.width*0.05,win_size.height*0.65));
	button1->addClickEventListener(CC_CALLBACK_0(Button_Ui::atkobj, this));
	button1->setName("btn1");
	this->addChild(button1);

	auto button2 = ui::Button::create("Keyon.png", "Keypush.png", "Keyoff.png");
	button2->setScale(1.5);
	button2->setPosition(Point(win_size.width*0.05, win_size.height*0.5));
	button2->addClickEventListener(CC_CALLBACK_0(Button_Ui::keyobj, this));
	button2->setName("btn2");
	button2->setEnabled(false);
	this->addChild(button2);

	auto button3 = ui::Button::create("Trapon1.png", "Trappush1.png", "Trapoff1.png");
	button3->setScale(1.5);
	button3->setPosition(Point(win_size.width*0.05, win_size.height*0.35));
	button3->addClickEventListener(CC_CALLBACK_0(Button_Ui::trapobj, this));
	button3->setName("btn3");
	button3->setEnabled(false);
	this->addChild(button3);

	this->scheduleUpdate();

    return true;
}

void Button_Ui::atkobj()
{
	if (GameManager::getInstance()->getPlayerState() == IDLE) {
		GameManager::getInstance()->setState(ATTACK);
		UIManager::getInstance()->setEnable_AtkBtn(false);
	}
}

void Button_Ui::searchobj()
{
	search_on = true;
}
void Button_Ui::keyobj()
{
	auto btn = (ui::Button*) this->getChildByName("btn2");
	if (key_count > 0)
	{
		btn->setEnabled(true);
	}
	else;
}

void Button_Ui::trapobj()
{
	auto btn = (ui::Button*) this->getChildByName("btn3");
	if (trap_count > 0)
	{
		btn->setEnabled(true);
	}
	else;
}

