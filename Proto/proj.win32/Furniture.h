#ifndef __FURNITURE_H__
#define __FURNITURE_H__

#include "cocos2d.h"

USING_NS_CC;

class Furniture : public Layer
{
public:

	virtual bool init();

	Size win_size;

	void Create_Fnt(); //가구 생성

	void Touch_React(); //가구 터치시 반응

	CREATE_FUNC(Furniture);
};

#endif // __FURNITURE_H__
