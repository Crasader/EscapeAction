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
	Camera* _camera;
	void check();
	
	void Joy_move_check();
	//테스트
	virtual void onPress(EventKeyboard::KeyCode key);
	virtual void onRelease(EventKeyboard::KeyCode key);
	void afterImage(float dt);

	//player가 위치한 방 번호 받아오기
	int getRoomNum();
	//player 방 번호 setting
	void setRoomNum(int roomNum);

	Rect getRect();

private : 
	Rect _playerRect;

	bool keyUp, keyDown, keyLeft, keyRight;
	int speed;
	float delayAfterimg;
	bool oncheck;

	Size win_size;
	Size plyer_size;
	Rect rc;

	Vec2 Move_joy_player;

	Sprite* _player;
	
	Animate* _player_animat;
	Animation* _player_anime;
	RepeatForever* rep_player;

	player_Move_enum playerState;

	//player가 현재 위치한 방 번호
	int _roomNum;

};

