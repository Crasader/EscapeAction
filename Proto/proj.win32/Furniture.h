#ifndef __FURNITURE_H__
#define __FURNITURE_H__

#include "cocos2d.h"
#include "Item.h"
#include <vector>
#include <iostream>
#include "external/json/document.h"
#include "external/json/filereadstream.h"//������ �����������
#include <cstdio>
using namespace std;
using namespace rapidjson;
USING_NS_CC;

//190701

struct FurnitureData
{
	const char* fnt_img;
	int fnt_size;
	//int fnt_sprite; //���� ���� ���� ����
	
	ItemData* F_ItemData; //������ Ŭ�������� ������ �޾ƿ�
	int item_num; //���� ����� ������ ��ȣ(0:weapon, 1:key, 2:trap, 3:no_item)
	bool search; //Ž�� ����(true: Ž������ / false: Ž�� �� ����)

}typedef FntData;



class Furniture : public Node
{
public:
	int fnt_num; //���� ����(�� ũ�� ����)
	~Furniture();

	bool init();
	
	vector<FntData*> v_FntData;
	
	Size win_size;

	//Vec2 Ary_fnt_wall_pos[8]; //Vec2 ��ġ�� ���� �迭 <�Ⱦ�

	void Create_Furniture(); //���� ����
	void Touch_React(); //���� ��ġ�� ����

	virtual bool onTouchBegan(Touch* touch, Event* unused_event);
	virtual void onTouchEnded(Touch* touch, Event* unused_event);
	bool isselect;
	Sprite* select;

	CREATE_FUNC(Furniture);

private:
	Document fur_name;
};

#endif // __FURNITURE_H__
