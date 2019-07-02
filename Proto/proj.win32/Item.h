#ifndef __ITEM_H__
#define __ITEM_H__

#include "cocos2d.h"

USING_NS_CC;
//190627

struct ItemData
{
	//������ ���� : ����, ����, ��ź, ����
	bool weapon;
	bool key;
	bool trap;
	bool no_item;
};

class Item : public Node
{
public:
	ItemData* itm;
	~Item();

	bool init();

	CREATE_FUNC(Item);

	void Save_ItemData(); //������ ����(����)�ϴ� �Լ�
};


#endif