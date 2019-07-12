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

//190712

struct FurnitureData
{
	string fnt_img;
	int fnt_size;
	int pos;
	bool deco;
	//int fnt_sprite; //���� ���� ���� ����
	//ItemData* F_ItemData; //������ Ŭ�������� ������ �޾ƿ�
	int item_num; //���� ����� ������ ��ȣ(0:weapon, 1:key, 2:trap, 3:no_item)

}typedef FntData;



class Furniture : public Node
{
public:
	static Furniture* create(int left, int right, bool ladder);
	~Furniture();

	virtual bool init();
	virtual bool init(int left, int right, bool ladder);

	vector<FntData*> v_FntData;
	vector<int> v_fntKind;

	Size win_size;

	bool isselect;
	Sprite* select;
	
	CREATE_FUNC(Furniture);

private:
	//int fnt_num; //���� ����(�� ũ�� ����)
};

#endif // __FURNITURE_H__
