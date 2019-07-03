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

	void Joy_move_check();
	
	void pause_ani();
	bool s_check;
	bool atk_check;

	player_Move_enum _playerState;

	UIManager* _UIM;

private : 
	int speed;

	bool oncheck;
	bool RL_Flip;

	Size win_size;
	Size plyer_size;
	Rect rc;

	Vec2 Move_joy_player;

	Sprite* _player;
	Animation* _player_anime;
	Animate* _player_animat;
	RepeatForever* rep_player;
};

