#include "Item.h"

Item::~Item()
{
}
//190627
bool Item::init()
{

	return true;
}

void Item::Save_ItemData()
{
	ItemData* item = new ItemData;
	item->weapon = false;
	item->key = false;
	item->trap = false;
	item->no_item = false;

	if (rand() % 1 == 1)
	{
		save_item = true;
		if (save_item == true)
		{
			switch (rand() % 3) //rand�� �� �Դ´ٸ� ���� �߰��ؼ� �����Ұ�
			{
			case 0:
				item->weapon = true;
				break;
			case 1:
				item->key = true;
				break;
			case 2:
				item->trap = true;
				break;
			case 3:
				item->no_item = true;
				break;
			}
		}
	}
	else
		return;
}
