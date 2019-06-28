#include "Item.h"

Item::~Item()
{
}
//190627
bool Item::init()
{
	itm = new ItemData;

	srand(time(NULL));

	Save_ItemData();
	return true;
}

void Item::Save_ItemData()
{
	itm->weapon = false;
	itm->key = false;
	itm->trap = false;
	itm->no_item = false;

	switch (rand() % 4) //rand로 안 먹는다면 변수 추가해서 대입할것
	{
	case 0:
		itm->weapon = true;
		break;
	case 1:
		itm->key = true;
		break;
	case 2:
		itm->trap = true;
		break;
	case 3:
		itm->no_item = true;
		break;
	}


	return;
}
