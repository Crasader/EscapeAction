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
	static cocos2d::Layer* createLayer(); // Snece �� �ƴ� Layer�������� ���� ��Ȯ�� ��ɾ� Ȯ�� �ʿ�

	virtual bool init();

	Sprite* player; // �÷��̾� ��������Ʈ

	Size win_size; // ȭ�������

	void onPress(EventKeyboard::KeyCode code); // Ű �Է� push
	void onRelease(EventKeyboard::KeyCode code); // Ű �Է� end

	void Move_R(float dt);
	void Move_L(float dt);
	void Move_U(float dt);
	void Move_D(float dt);
	//player Move end
};

#endif // __LAYER_UI_H__
