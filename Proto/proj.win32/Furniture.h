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

	void Create_Furniture(); //���� ����
	bool Check(); //Ž���� ���� ���� Ȯ��
	void Touch_React(); //���� ��ġ�� ����

	virtual bool onTouchBegan(Touch* touch, Event* unused_event);
	virtual bool onTouchEnded(Touch* touch, Event* unused_event);

	CREATE_FUNC(Furniture);
};

#endif // __FURNITURE_H__
