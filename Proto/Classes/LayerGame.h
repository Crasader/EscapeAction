#ifndef __LAYER_GAME_H__
#define __LAYER_GAME_H__

#include "cocos2d.h"
#include "Room.h"
USING_NS_CC;

class LayerGame : public cocos2d::Layer
{
public:
    virtual bool init();

    CREATE_FUNC(LayerGame);
};

#endif // __HELLOWORLD_SCENE_H__
