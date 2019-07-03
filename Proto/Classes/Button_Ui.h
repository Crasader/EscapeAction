#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "ui/UIButton.h"
#include "cocos-ext.h"
#include "../proj.win32/Enum_collection.h"

using namespace std;
using namespace	cocos2d;


class Button_Ui : public Node
{
public:
    virtual bool init();

	Size win_size;

	ui::Button* button1;//����
	ui::Button* button2;//Ž��
	ui::Button* button3;//Ű
	ui::Button* button4;//������

	bool check; //�浹üũ
	bool search_on; //Ž��üũ
	bool atk_on; //����üũ

	int key_count;
	int trap_count;

	void atkobj();
	void searchobj();
	void keyobj();
	void trapobj();

	CREATE_FUNC(Button_Ui);
};

#endif // __HELLOWORLD_SCENE_H__
