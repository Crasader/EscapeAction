#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

using namespace std;

Scene* player_Item::createScene()
{
    return player_Item::create();
}

bool player_Item::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

	auto button1 = ui::Button::create("Button_Disable.png", "Button_Normal.png", "Button_Press.png");
	button1->setTitleText("Button Text");
	button1->setPosition(Point(100, 250));
	button1->addClickEventListener(CC_CALLBACK_0(player_Item::atkobj, this));
	button1->setName("btn1");
	button1->setEnabled(false);
	this->addChild(button1);

	auto button2 = ui::Button::create("Button_Disable.png", "Button_Normal.png", "Button_Press.png");
	button2->setTitleText("Button Text");
	button2->setPosition(Point(100, 200));
	button2->addClickEventListener(CC_CALLBACK_0(player_Item::searchobj, this));
	button2->setName("btn2");
	button2->setEnabled(false);
	this->addChild(button2);

	auto button3 = ui::Button::create("Button_Disable.png", "Button_Normal.png", "Button_Press.png");
	button3->setTitleText("Button Text");
	button3->setPosition(Point(100, 150));
	button3->addClickEventListener(CC_CALLBACK_0(player_Item::keyobj, this));
	button3->setName("btn3");
	button3->setEnabled(false);
	this->addChild(button3);

	auto button4 = ui::Button::create("Button_Disable.png", "Button_Normal.png", "Button_Press.png");
	button4->setTitleText("Button Text");
	button4->setPosition(Point(100, 100));
	button4->addClickEventListener(CC_CALLBACK_0(player_Item::trapobj, this));
	button4->setName("btn4");
	button4->setEnabled(false);
	this->addChild(button4);

	player* pPlayer = player::create();
	this->addChild(pPlayer);
	pPlayer->setPosition(200, 200);


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
}

void player_Item::searchobj()
{
	auto btn = (ui::Button*) this->getChildByName("btn2");
	if (check)//�浹üũ
	{
		if (search)//Ž��üũ
		{
			btn->setEnabled(true);
		}
		else
		{
			return;
		}
	}
	else
	{
		return;
	}
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

void player_Item::update(float dt)
{
}
