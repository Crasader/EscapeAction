#ifndef __LAYER_GAME_H__
#define __LAYER_GAME_H__

#include "cocos2d.h"
#include "cocos-ext.h"

#include "player.h"
#include "UIManager.h"

#include "../proj.win32/Enum_collection.h"
#include "../proj.win32/LevelDataSet.h"
#include "../proj.win32/DrawField.h"
#include "../proj.win32/DrawDoor.h"
/*#include "../proj.win32/DrawFurniture.h"
#include "../proj.win32/DrawStruct.h"
#include "../proj.win32/DrawDeco.h"
*/

USING_NS_CC;

class LayerGame : public cocos2d::Layer
{
public:
	virtual bool init();
    CREATE_FUNC(LayerGame);
private:
	//draw
/*	DrawFurniture* dfur;
	FurnitureUI* fu;
	
	DoorUI* du;
	;*/
	DrawField* df;
	DrawDoor* ddor;
	int _roomNum;

	player* pyer;
	Camera* camera;

	Size win_size;
	Vec2 pos;
	bool pos_RL;
	//스케쥴 업데이트
	void update(float dt);

	//player_Move_enum playerState_move_camera;
	bool camera_check;
	Vec2 camera_move;
//JSONtest* jt;
};

#endif // __LAYER_GAME_H__
