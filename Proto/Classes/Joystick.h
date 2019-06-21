#define __HELLOWORLD_SCENE_H__

#pragma once

#include "cocos2d.h"
#include <string>

USING_NS_CC;
using namespace std;

class Joystick : public Node
{
public :
	virtual bool init();
	~Joystick();

	bool _touchCheck;

	Sprite* _MoveJoy;
	Sprite* _UnMoveJoy;
	Size Win_size;
	Vec2 Mj_Touch_p;
	Vec2 Umj_Touch_p;
	Vec2 Move_p_joy;


	bool onTouchBegan(Touch *touch, Event *unused_event);
	void onTouchMoved(Touch *touch, Event *unused_event);
	void onTouchEnded(Touch *touch, Event *unused_event);

	CREATE_FUNC(Joystick);
};