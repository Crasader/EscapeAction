#pragma once
#include "cocos2d.h"

USING_NS_CC;

class player:public Node
{
public:

	CREATE_FUNC(player);
	~player();
	virtual bool init();

	void onPress(EventKeyboard::KeyCode key);
	void onRelease(EventKeyboard::KeyCode key);

	void update(float dt);

	player* player_db;
	void set_player(player* p);
	player* get_player();

private : 
	bool keyUp, keyDown, keyLeft, keyRight;
	int speed;
	Size win_size;
	Sprite* plyer;
	Size plyer_size;
};

