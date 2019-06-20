#ifndef __LAYER_UI_H__
#define __LAYER_UI_H__

#include "cocos2d.h"
#include "Button_Ui.h"
#include "Joystick.h"

USING_NS_CC;

class LayerUI : public cocos2d::Layer
{
public:
	
	virtual bool init();
    CREATE_FUNC(LayerUI);
};

#endif // __LAYER_UI_H__
