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
	button1->setEnabled(true);
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
	auto btn = (ui::Button*) this->getChildByName("btn1");
	if (atk_on)
	{
		btn->setEnabled(true);
	}
	else;

	/*_player_B = Sprite::create("s0.png");
	this->addChild(_player_B);
	_player_B->setName("player_ani");
	_player_B->setPosition(Vec2(win_size.width*0.5f, win_size.height*0.5f));
	_player_B->setScale(3.5);

	_player_anime_B = Animation::create();
	_player_anime_B->setDelayPerUnit(0.2f);
	_player_anime_B->addSpriteFrameWithFile("s0.png");
	_player_anime_B->addSpriteFrameWithFile("s1.png");
	_player_anime_B->addSpriteFrameWithFile("s2.png");

	_player_animat_B = Animate::create(_player_anime_B);
	_player_B->runAction(_player_animat_B);*/
}

void player_Item::searchobj()
{
	auto player_p = (Sprite*) this->getChildByName("p_name")->getChildByName("player_move");
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
		btn->setEnabled(false);
}
void player_Item::keyobj()
{
	auto btn = (ui::Button*) this->getChildByName("btn3");
	if (key_count > 0)
	{
		btn->setEnabled(true);
	}
	else;
}

void player_Item::trapobj()
{
	auto btn = (ui::Button*) this->getChildByName("btn4");
	if (trap_count > 0)
	{
		btn->setEnabled(true);
	}
	else;
}

