#ifndef __ITEM_H__
#define __ITEM_H__

#include "cocos2d.h"
#include <vector>
#include <iostream>

USING_NS_CC;
using namespace std;

//190712

struct ItemData
{
	//아이템 종류 : 무기, 열쇠, 폭탄, 없음
	bool weapon;
	bool key;
	bool trap;
	bool no_item;
};

class Item : public Node
{
public:
	ItemData* itm;

	vector <int> v_item;

	~Item();

	bool init();

	CREATE_FUNC(Item);

	void Save_ItemData(); //아이템 저장(새로)하는 함수
	
};


#endif