#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "ui/UIButton.h"
#include "cocos-ext.h"

using namespace std;
using namespace	cocos2d;

class player_Item : public Node
{
public:
    virtual bool init();

	Size win_size;

	bool check; //�浹üũ
	bool search; //Ž��üũ

	bool atk_on;
	int key_count;
	int trap_count;

	void atkobj();
	void searchobj();
	void keyobj();
	void trapobj();

	void update(float dt);
   
    CREATE_FUNC(player_Item);
};

#endif // __HELLOWORLD_SCENE_H__
