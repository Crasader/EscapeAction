#include "LayerUI.h"
#include "SimpleAudioEngine.h"
#include "UIManager.h"


USING_NS_CC;

bool LayerUI::init()
{
	//������ ��ư ����
	Button_Ui* pl = Button_Ui::create();
	this->addChild(pl);
	//���̽�ƽ ����
	Joystick* js = Joystick::create();
	this->addChild(js);

	//UIManager�� 4���� ��ư ����
	UIManager::getInstance()->setAtkBtn((ui::Button*)pl->getChildByName("btn1"));
	UIManager::getInstance()->setSearchBtn((ui::Button*)pl->getChildByName("btn2"));
	UIManager::getInstance()->setKeyBtn((ui::Button*)pl->getChildByName("btn3"));
	UIManager::getInstance()->setTrapBtn((ui::Button*)pl->getChildByName("btn4"));

	//UIManager�� joystick ����
	UIManager::getInstance()->setJoystick(js);

	UIManager::getInstance()->set_btn_ui(pl);



	return true;
}
