#pragma once
#include "cocos2d.h"
#include "UIManager.h"
#include "../proj.win32/Enum_collection.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

class player:public Node
{
public:

	CREATE_FUNC(player);
	~player();
	virtual bool init();
	void setRect(Rect back_rc);

	UIManager* _UIM;

	bool all_stop;
	bool src_check;
	bool atk_check;

	void ani_pause();
	void ani_forward();

	bool RL_filp;

	int atk_ran;
	void make_atk_ani();
	
	void Joy_move_check();
	//Å×½ºÆ®
	virtual void onPress(EventKeyboard::KeyCode key);
	virtual void onRelease(EventKeyboard::KeyCode key);	

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

	Spawn* p_f_atk;

	player_Move_enum playerState;

};

