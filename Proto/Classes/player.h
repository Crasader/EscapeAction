#pragma once
#include "cocos2d.h"
#include "UIManager.h"
#include "../proj.win32/Enum_collection.h"

USING_NS_CC;

class player:public Node
{
public:

	CREATE_FUNC(player);
	~player();
	virtual bool init();
	void setRect(Rect back_rc);

	void check();
	
	void Joy_move_check();
	

private : 
	bool keyUp, keyDown, keyLeft, keyRight;
	int speed;

	bool oncheck;

	Size win_size;
	Size plyer_size;
	Rect rc;

	Vec2 Move_joy_player;

	Sprite* _player;
	Animation* _player_anime;
	Animate* _player_animat;
	RepeatForever* rep_player;

	player_Move_enum playerState;

};

