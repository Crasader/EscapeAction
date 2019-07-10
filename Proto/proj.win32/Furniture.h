#ifndef __FURNITURE_H__
#define __FURNITURE_H__

#include "cocos2d.h"
#include "Item.h"
#include <vector>
#include <iostream>
#include "external/json/document.h"
#include "external/json/filereadstream.h"//������ �����������
#include <cstdio>
#include <string>

using namespace std;
using namespace rapidjson;
USING_NS_CC;

//190701

struct FurnitureData
{
	string fnt_img;
	int fnt_size;
	float pos;
	bool deco;
	//int fnt_sprite; //���� ���� ���� ����
	//ItemData* F_ItemData; //������ Ŭ�������� ������ �޾ƿ�
	int item_num; //���� ����� ������ ��ȣ(0:weapon, 1:key, 2:trap, 3:no_item)
	//bool search; //Ž�� ����(true: Ž������ / false: Ž�� �� ����)

}typedef FntData;



class Furniture : public Node
{
public:
	static Furniture* create(int left, int right);
	~Furniture();

	virtual bool init();
	virtual bool init(int left, int right);
	vector<FntData*> v_FntData;
	vector<int> v_fntKind;
	vector<FntData*> v_FntData_l;
	vector<FntData*> v_FntData_r;

	Size win_size;

	//Vec2 Ary_fnt_wall_pos[8]; //Vec2 ��ġ�� ���� �迭 <�Ⱦ�
	void Create_Furniture(); //���� ����
	void Touch_React(); //���� ��ġ�� ����
	//virtual bool onTouchBegan(Touch* touch, Event* unused_event);
	//virtual void onTouchEnded(Touch* touch, Event* unused_event);
	bool isselect;
	Sprite* select;
	
	CREATE_FUNC(Furniture);

private:
	//int fnt_num; //���� ����(�� ũ�� ����)
	int totalLeft;
	int totalRight;
};

#endif // __FURNITURE_H__
