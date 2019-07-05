#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "ui/UIButton.h"
#include "cocos-ext.h"

using namespace std;
using namespace	cocos2d;

class Button_Ui : public Node
{
public:
    virtual bool init();

	Size win_size;

	bool atk_on;
	bool search_on;

	int key_count;
	int trap_count;

	void atkobj();
	void searchobj();
	void keyobj();
	void trapobj();

    CREATE_FUNC(Button_Ui);
};

#endif // __HELLOWORLD_SCENE_H__
