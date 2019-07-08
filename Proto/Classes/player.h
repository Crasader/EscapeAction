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
	Camera* _camera;
	void checkFur();
	bool getCheckFur();
	void Joy_move_check();
	//테스트
	virtual void onPress(EventKeyboard::KeyCode key);
	virtual void onRelease(EventKeyboard::KeyCode key);
	void afterImage(float dt);

	//방관련
	//player가 위치한 방 번호 받아오기
	int getRoomNum();
	//player 방 번호 setting
	void setRoomNum(int roomNum);
	void setFirst(float first);
	void setLast(float last);
	
	//가구 관련
	Rect getRect();

private : 
	Rect _playerRect;

	bool keyUp, keyDown, keyLeft, keyRight;
	int speed;
	float delayAfterimg;
	bool oncheck;
	bool check_fur;
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
	//방 크기
	float _firstPos;
	float _lastPos;

};

