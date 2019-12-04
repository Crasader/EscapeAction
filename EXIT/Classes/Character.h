#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "cocos2d.h"
#include "EnumCollection.h"

class Character : public cocos2d::Node
{
public:
	virtual bool init();
	void initCharacter();
	CREATE_FUNC(Character);
	ChaState getState();
	void setState(ChaState state);

private:
	ChaAniState _aniState;
	ChaState _state;
	Sprite* _sprite;
	Animate* _animate;
	int test[];
};

#endif
