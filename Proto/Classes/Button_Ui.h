#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "ui/UIButton.h"
#include "cocos-ext.h"
#include "LayerGame.h"
#include "player.h"

using namespace std;
using namespace	cocos2d;

class player_Item : public Node
{
public:
    virtual bool init();
	
	player* p_data;

	Size win_size;

	bool check; //충돌체크
	bool search; //탐색체크

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
