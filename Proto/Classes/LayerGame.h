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
#include "../proj.win32/DrawLadder.h"
#include "../proj.win32/DrawStruct.h"
#include "../proj.win32/DrawFurniture.h"
#include "../proj.win32/DrawDeco.h"
#include "../proj.win32/LadderUI.h"

USING_NS_CC;

class LayerGame : public cocos2d::Layer
{
public:
	virtual bool init();
    CREATE_FUNC(LayerGame);
private:
	//map �׸���
	DrawFurniture* dfur;
	DrawField* df;
	DrawDoor* ddor;
	DrawLadder* dlad;
	//ui �׸���
	FurnitureUI* fu;
	DoorUI* du;
	LadderUI* lu;
	//�÷��̾�
	player* pyer;
	//ī�޶�
	Camera* camera;

	//������ ������Ʈ
	void update(float dt);
};

#endif // __LAYER_GAME_H__
