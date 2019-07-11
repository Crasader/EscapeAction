#ifndef __LAYER_GAME_H__
#define __LAYER_GAME_H__

#include "cocos2d.h"
#include "cocos-ext.h"

#include "player.h"
#include "UIManager.h"

#include "../proj.win32/Enum_collection.h"
#include "../proj.win32/DrawFurniture.h"
#include "../proj.win32/LevelDataSet.h"
#include "../proj.win32/DrawField.h"
#include "../proj.win32/DrawStruct.h"
#include "../proj.win32/DrawDeco.h"
#include "../proj.win32/DrawDoor.h"
#include "../proj.win32/AudioManager.h"

USING_NS_CC;

class LayerGame : public cocos2d::Layer
{
public:
	virtual bool init();
    CREATE_FUNC(LayerGame);
private:
	//draw
	DrawFurniture* dfur;
	FurnitureUI* fu;
	DrawField* df;
	DrawDoor* ddor;
	DoorUI* du;
	AudioManager* audio;

	int _roomNum;


	player* pyer;
	Camera* camera;

	Size win_size;
	Vec2 pos;
	bool pos_RL;
	//������ ������Ʈ
	void update(float dt);

	//player_Move_enum playerState_move_camera;
	bool camera_check;
	Vec2 camera_move;
	//����
	int Thunder_ran;

//JSONtest* jt;
};

#endif // __LAYER_GAME_H__
