#ifndef __LAYER_GAME_H__
#define __LAYER_GAME_H__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;

class LayerGame : public cocos2d::Layer
{
public:
    virtual bool init();

	Sprite* player;
	Sprite* Button;

	Size win_size;

	void onPress(EventKeyboard::KeyCode code);
	void onRelease(EventKeyboard::KeyCode code);

	void Move_R(float dt);
	void Move_L(float dt);
	void Move_U(float dt);
	void Move_D(float dt);
	/*
	//pad
	void initPad();
	void create(Layer* layer, Point point);

	Point _startPoint;
	Point _joystickPoint;
	Sprite* _joystick;
	Sprite* _joystickPad;

	bool _joystickTouched;

	//--------handle direct
	Point _dPoint;
	float _dLength;

	Point getDPoint();
	float getDLength();

	//--------touch events
	virtual void TouchesBegan(const std::vector<Touch*>& touches, Event* unused_event);
	virtual void TouchesMoved(const std::vector<Touch*>& touches, Event* unused_event);
	virtual void TouchesEnded(const std::vector<Touch*>& touches, Event* unused_event);
	virtual void TouchesCancelled(const std::vector<Touch*>& touches, Event* unused_event);
	*/

	void createButton();

    CREATE_FUNC(LayerGame);
};

#endif // __HELLOWORLD_SCENE_H__
