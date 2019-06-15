#ifndef __LAYER_GAME_H__
#define __LAYER_GAME_H__

#include "cocos2d.h"

USING_NS_CC;

class LayerGame : public cocos2d::Layer
{
public:
    virtual bool init();

	Sprite* player;

	Size win_size;

	void onPress(EventKeyboard::KeyCode code);
	void onRelease(EventKeyboard::KeyCode code);

	void Move_R(float dt);
	void Move_L(float dt);
	void Move_U(float dt);
	void Move_D(float dt);

    CREATE_FUNC(LayerGame);
};

#endif // __HELLOWORLD_SCENE_H__
