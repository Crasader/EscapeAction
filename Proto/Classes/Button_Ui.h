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

	ui::Button* button1;//어택
	ui::Button* button2;//탐색
	ui::Button* button3;//키
	ui::Button* button4;//아이템

	bool check; //충돌체크
	bool search_on; //탐색체크
	bool atk_on; //어택체크

	int key_count;
	int trap_count;

	void atkobj();
	void searchobj();
	void keyobj();
	void trapobj();

	CREATE_FUNC(Button_Ui);
};

#endif // __HELLOWORLD_SCENE_H__
