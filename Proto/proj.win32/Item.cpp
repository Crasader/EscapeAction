#include "Item.h"

Item::~Item()
{
}
//190626
bool Item::init()
{
	/*ItemData* weapon = false;
	ItemData* key = false;
	ItemData* trap = false;*/

	weapon = false;
	key = false;
	trap = false;

	return true;
}

void Item::Save_ItemData()
{
	if (rand() % 1 == 1)
	{
		save_item = true;
		if (save_item == true)
		{
			switch (rand() % 2) //rand�� �� �Դ´ٸ� ���� �߰��ؼ� �����Ұ�
			{
			case 0:
				weapon = true;
				break;
			case 1:
				key = true;
				break;
			case 2:
				trap = true;
				break;
			}
		}
	}
	else
		return;
}
