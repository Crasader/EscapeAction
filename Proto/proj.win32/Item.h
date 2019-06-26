#ifndef __ITEM_H__
#define __ITEM_H__

#include "cocos2d.h"

USING_NS_CC;
//190626
class Item : public Node
{
public:

	//아이템 종류 : 무기, 열쇠, 폭탄
	bool weapon;
	bool key;
	bool trap;


	~Item();

	bool init();

	bool save_item; //아이템 저장 여부 묻는 변수
	void Save_ItemData(); //아이템 저장(새로)하는 함수


	CREATE_FUNC(Item);
};


#endif