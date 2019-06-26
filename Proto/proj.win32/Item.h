#ifndef __ITEM_H__
#define __ITEM_H__

#include "cocos2d.h"

USING_NS_CC;
//190626
class Item : public Node
{
public:

	//������ ���� : ����, ����, ��ź
	bool weapon;
	bool key;
	bool trap;


	~Item();

	bool init();

	bool save_item; //������ ���� ���� ���� ����
	void Save_ItemData(); //������ ����(����)�ϴ� �Լ�


	CREATE_FUNC(Item);
};


#endif