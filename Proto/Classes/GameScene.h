#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "LayerGame.h"
#include "LayerUI.h"
USING_NS_CC;

class GameScene: public cocos2d::Scene
{
public:
    virtual bool init();

    CREATE_FUNC(GameScene);
};

#endif // __GAME_SCENE_H__
