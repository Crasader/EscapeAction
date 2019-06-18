#pragma once
#include "cocos2d.h"
USING_NS_CC;

class player:public Node
{
public:

	CREATE_FUNC(player);
	~player();
	virtual bool init();
	void setRect(Rect back_rc);
	void onPress(EventKeyboard::KeyCode key);
	void onRelease(EventKeyboard::KeyCode key);

	void update(float dt);

private : 
	bool keyUp, keyDown, keyLeft, keyRight;
	int speed;
	Size win_size;
	Sprite* plyer;
	Size plyer_size;
	Rect rc;

};

