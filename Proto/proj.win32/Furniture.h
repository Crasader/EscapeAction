#ifndef __FURNITURE_H__
#define __FURNITURE_H__

#include "cocos2d.h"
#include "Item.h"
#include <../base/CCVector.h>
#include <vector>


USING_NS_CC;

//190627

struct FurnitureData
{
	//�������� �ʿ��� �� ������...

	int fnt_num; //���� ����(�� ũ�� ����)
	ItemData* F_ItemData; //������ Ŭ�������� ������ �޾ƿ�
	int item_num; //���� ����� ������ ��ȣ(0:weapon, 1:key, 2:trap, 3:no_item)
	bool search; //Ž�� ����

}typedef FntData;

std::vector<FntData*> v_FntData;

class Furniture : public Node
{
public:

	~Furniture();

	bool init();

	Size win_size;

	Vec2 Ary_fnt_wall_pos[8]; //Vec2 ��ġ�� ���� �迭

	void Create_Furniture(); //���� ����
	void Touch_React(); //���� ��ġ�� ����

	virtual bool onTouchBegan(Touch* touch, Event* unused_event);
	virtual void onTouchEnded(Touch* touch, Event* unused_event);
	bool isselect;
	Sprite* select;

	CREATE_FUNC(Furniture);

	Item* It;

};

#endif // __FURNITURE_H__
