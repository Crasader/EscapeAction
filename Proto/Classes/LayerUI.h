#ifndef __LAYER_UI_H__
#define __LAYER_UI_H__

#include "cocos2d.h"

USING_NS_CC;

class LayerUI : public cocos2d::Layer
{
public:
    virtual bool init();

    CREATE_FUNC(LayerUI);

	//player Move start
	static cocos2d::Layer* createLayer(); // Snece 가 아닌 Layer형식으로 생성 정확한 명령어 확인 필요

	virtual bool init();

	Sprite* player; // 플레이어 스프라이트

	Size win_size; // 화면사이즈

	void onPress(EventKeyboard::KeyCode code); // 키 입력 push
	void onRelease(EventKeyboard::KeyCode code); // 키 입력 end

	void Move_R(float dt);
	void Move_L(float dt);
	void Move_U(float dt);
	void Move_D(float dt);
	//player Move end
};

#endif // __LAYER_UI_H__
