#ifndef __LAYER_GAME_H__
#define __LAYER_GAME_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Room.h"
#include "player.h"

USING_NS_CC;

class LayerGame : public cocos2d::Layer
{
public:
	virtual bool init();
    CREATE_FUNC(LayerGame);
private:
	Room* rm;
	player* pyer;
};

#endif // __HELLOWORLD_SCENE_H__
