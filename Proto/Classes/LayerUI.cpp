#include "LayerUI.h"
#include "SimpleAudioEngine.h"
#include "UIManager.h"


USING_NS_CC;

bool LayerUI::init()
{
	//아이템 버튼 생성
	Button_Ui* pl = Button_Ui::create();
	this->addChild(pl);
	//조이스틱 생성
	Joystick* js = Joystick::create();
	this->addChild(js);


	//UIManager에 4개의 버튼 세팅
	UIManager::getInstance()->setAtkBtn((ui::Button*)pl->getChildByName("btn1"));
	UIManager::getInstance()->setKeyBtn((ui::Button*)pl->getChildByName("btn2"));
	UIManager::getInstance()->setTrapBtn((ui::Button*)pl->getChildByName("btn3"));

	//UIManager에 joystick 세팅
	UIManager::getInstance()->setJoystick(js);

	UIManager::getInstance()->set_btn_ui(pl);



	return true;
}
LayerUI::~LayerUI(){
}
