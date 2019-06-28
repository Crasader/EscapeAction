#ifndef __LAYER_GAME_H__
#define __LAYER_GAME_H__

#include "cocos2d.h"
#include "cocos-ext.h"

#include "player.h"
#include "Room.h"
#include "UIManager.h"

#include "../proj.win32/Enum_collection.h"
#include "../proj.win32/JSONtest.h"
#include "../proj.win32/DrawField.h"

USING_NS_CC;

class LayerGame : public cocos2d::Layer
{
public:
	virtual bool init();
    CREATE_FUNC(LayerGame);
private:
	Room* rm;
	player* pyer;
	Camera* camera;

	Vec2 win_size;
	Vec2 pos;
	//스케쥴 업데이트
	void update(float dt);

	player_Move_enum playerState_move_camera;
	bool camera_check;
	Vec2 camera_move;
	JSONtest* jt;
};

#endif // __HELLOWORLD_SCENE_H__
