#ifndef __LAYER_GAME_H__
#define __LAYER_GAME_H__

#include "cocos2d.h"
#include "Room.h"
USING_NS_CC;

class LayerGame : public cocos2d::Layer
{
public:
    virtual bool init();

	virtual void onPress(EventKeyboard::KeyCode key);
	virtual void onRelease(EventKeyboard::KeyCode key);


    CREATE_FUNC(LayerGame);
private:
	Room* back;
};

#endif // __HELLOWORLD_SCENE_H__
