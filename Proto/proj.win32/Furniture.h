#ifndef __FURNITURE_H__
#define __FURNITURE_H__

#include "cocos2d.h"
#include <spine/spine-cocos2dx.h>
#include <random>

USING_NS_CC;

class Furniture : public Layer
{
public:

	~Furniture();

	bool init();

	Size win_size;

	void Create_Furniture(); //가구 생성
	bool Check(); //탐색시 가능 여부 확인
	void Touch_React(); //가구 터치시 반응

	virtual bool onTouchBegan(Touch* touch, Event* unused_event);
	virtual bool onTouchEnded(Touch* touch, Event* unused_event);

	CREATE_FUNC(Furniture);
};

#endif // __FURNITURE_H__
