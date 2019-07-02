#ifndef __FURNITURE_H__
#define __FURNITURE_H__

#include "cocos2d.h"
#include "Item.h"
#include <vector>
#include <iostream>
#include "external/json/document.h"
#include "external/json/filereadstream.h"//파일을 열어오기위함
#include <cstdio>
using namespace std;
using namespace rapidjson;
USING_NS_CC;

//190701

struct FurnitureData
{
	const char* fnt_img;
	int fnt_size;
	//int fnt_sprite; //가구 종류 랜덤 지정
	
	ItemData* F_ItemData; //아이템 클래스에서 데이터 받아옴
	int item_num; //각각 저장된 아이템 번호(0:weapon, 1:key, 2:trap, 3:no_item)
	bool search; //탐색 여부(true: 탐색했음 / false: 탐색 안 했음)

}typedef FntData;



class Furniture : public Node
{
public:
	int fnt_num; //가구 개수(방 크기 결정)
	~Furniture();

	bool init();
	
	vector<FntData*> v_FntData;
	
	Size win_size;

	//Vec2 Ary_fnt_wall_pos[8]; //Vec2 위치값 저장 배열 <안씀

	void Create_Furniture(); //가구 생성
	void Touch_React(); //가구 터치시 반응

	virtual bool onTouchBegan(Touch* touch, Event* unused_event);
	virtual void onTouchEnded(Touch* touch, Event* unused_event);
	bool isselect;
	Sprite* select;

	CREATE_FUNC(Furniture);

private:
	Document fur_name;
};

#endif // __FURNITURE_H__
