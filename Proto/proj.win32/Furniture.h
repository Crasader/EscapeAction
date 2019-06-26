#ifndef __FURNITURE_H__
#define __FURNITURE_H__

#include "cocos2d.h"
#include "Item.h"

USING_NS_CC;

//190626
class Furniture : public Layer
{
public:

	~Furniture();

	bool init();

	Size win_size;

	Vec2 Ary_fnt_wall_pos[8]; //Vec2 위치값 저장 배열

	void Create_Furniture(); //가구 생성
	void Touch_React(); //가구 터치시 반응

	virtual bool onTouchBegan(Touch* touch, Event* unused_event);
	virtual void onTouchEnded(Touch* touch, Event* unused_event);
	bool isselect;
	Sprite* select;

	CREATE_FUNC(Furniture);

private:
	Item* It;
};

#endif // __FURNITURE_H__
