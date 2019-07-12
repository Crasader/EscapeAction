#ifndef __FURNITURE_H__
#define __FURNITURE_H__

#include "cocos2d.h"
#include "Item.h"
#include <vector>
#include <iostream>
#include "external/json/document.h"
#include "external/json/filereadstream.h"//파일을 열어오기위함
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
	//int fnt_sprite; //가구 종류 랜덤 지정
	//ItemData* F_ItemData; //아이템 클래스에서 데이터 받아옴
	int item_num; //각각 저장된 아이템 번호(0:weapon, 1:key, 2:trap, 3:no_item)

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
	//int fnt_num; //가구 개수(방 크기 결정)
};

#endif // __FURNITURE_H__
