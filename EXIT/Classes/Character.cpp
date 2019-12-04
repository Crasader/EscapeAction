#include "Character.h"

USING_NS_CC;

bool Character::init()
{
	_state = ChaState::IDLE;
	initCharacter();

	return true;
}

void Character::initCharacter()
{
	_sprite = Sprite::create("character/idle/I0.png");
	_sprite->setAnchorPoint(Vec2(0.5, 0));

	this->addChild(_sprite);

	auto idleAni = Animation::create();
	addFrame(idleAni, 2, "character/idle/I%d.png");
}
void addFrame(Animation* anim, int cnt, const char* format) {
	for (int i = 0; i < cnt; i++) {
		anim->addSpriteFrameWithFile(StringUtils::format
		(format, i));}
}
ChaState Character::getState()
{
	return _state;
}
void Character::setState(ChaState state)
{
	_state = state;
}
