#include "Furniture.h"


Furniture::~Furniture()
{
}
//190701
bool Furniture::init()
{

	//���� ���� & �Ľ�
	FILE* fp = fopen("furnitureName.json", "rb");
	char readBuffer[500];
	FileReadStream is(fp, readBuffer, sizeof(readBuffer));
	fur_name.ParseStream(is);
	fclose(fp);

	srand(time(NULL));
	win_size = Director::getInstance()->getWinSize();
	
	CCLOG("Furniture OK"); //�۴��� Ŭ���� ����� ������ ����Ǵ��� Ȯ��

	//==============================���� ������ ����======================================
	//FntData* Sfnt = new FntData;
	//Sfnt->F_ItemData = It->itm; //������ ������ ����ü ����

	////�� ������ ������ true Ȯ��
	//if (Sfnt->F_ItemData->weapon)
	//{
	//	Sfnt->item_num = 0;
	//	CCLOG("Weapon True");
	//}
	//if (Sfnt->F_ItemData->key)
	//{
	//	Sfnt->item_num = 1;
	//	CCLOG("Key True");
	//}
	//if (Sfnt->F_ItemData->trap)
	//{
	//	Sfnt->item_num = 2;
	//	CCLOG("Trap True");
	//}
	//if (Sfnt->F_ItemData->no_item)
	//{
	//	Sfnt->item_num = 3;
	//	CCLOG("No_Item True");
	//}

	////���� Ž�� bool �ʱ�ȭ
	//Sfnt->search = false;

	//���� ������ ���� ����
	vector<FntData*>::iterator v = v_FntData.begin();

	//���� ���� �������� ����
	fnt_num = rand() % 5 + 1;

	CCLOG("fnt_num : %d",fnt_num);

	//���� ������ŭ ���� ������ ���ͷ� push
	for (int i = 0; i < fnt_num; i++)
	{
	
		//������ Ŭ���� ����
		Item* It=Item::create();

		FntData* Sfnt = new FntData;
		Sfnt->F_ItemData = It->itm; //������ ������ ����ü ����

		//�� ������ ������ true Ȯ��
		if (Sfnt->F_ItemData->weapon)
		{
			Sfnt->item_num = 0;
			CCLOG("Weapon True");
		}
		if (Sfnt->F_ItemData->key)
		{
			Sfnt->item_num = 1;
			CCLOG("Key True");
		}
		if (Sfnt->F_ItemData->trap)
		{
			Sfnt->item_num = 2;
			CCLOG("Trap True");
		}
		if (Sfnt->F_ItemData->no_item)
		{
			Sfnt->item_num = 3;
			CCLOG("No_Item True");
		}

		//���� ��������
		assert(fur_name.IsArray());
		int arr_count = -1;
		for (auto& fur : fur_name.GetArray()) {
			arr_count++;
		}

		int fur_rand = RandomHelper::random_int(0, arr_count);
		log("fur_rand : %d", fur_rand);
		assert(fur_name[fur_rand].HasMember("name"));
		assert(fur_name[fur_rand]["name"].IsString());
		Sfnt->fnt_img = fur_name[fur_rand]["name"].GetString();

		assert(fur_name[fur_rand].HasMember("size"));
		assert(fur_name[fur_rand]["size"].IsInt());
		Sfnt->fnt_size = fur_name[fur_rand]["size"].GetInt();

		//���� Ž�� bool �ʱ�ȭ
		Sfnt->search = false;
		v_FntData.push_back(Sfnt);
	}
	int i = 0;
	for (auto v : v_FntData) {
		log("%d item : %d", i, v->item_num);
		i++;
	}
	
	CCLOG("vector fntdata size : %d", v_FntData.size());
	//==============================���� ������ ����======================================
	
	/*
	//���� ���� �þ�� ��������Ʈ �� �߰���
	Sprite* fnt_wall1 = Sprite::create("button1.png");
	fnt_wall1->setPosition(500, 500);
	fnt_wall1->setName("Fnt_wall1");

	Sprite* fnt_wall2 = Sprite::create("button2.png");
	fnt_wall2->setPosition(600, 500);
	fnt_wall2->setName("Fnt_wall2");

	//Ž�� ��ư
	Sprite* searchbutton = Sprite::create("buttonB.png");
	searchbutton->setPosition(300, 500);
	searchbutton->setName("Searchbutton");

	this->addChild(searchbutton, 10);


	//���� ���� ��������Ʈ ���� ����
	Sfnt->fnt_sprite = rand() % 1;
	if(Sfnt->fnt_sprite==0)
		this->addChild(fnt_wall1, 1);
	if(Sfnt->fnt_sprite==1)
		this->addChild(fnt_wall2, 1);
*/
	auto listner = EventListenerTouchOneByOne::create();
	listner->onTouchBegan = CC_CALLBACK_2(Furniture::onTouchBegan, this);
	listner->onTouchEnded = CC_CALLBACK_2(Furniture::onTouchEnded, this);

	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listner, 2);


	return true;
}

void Furniture::Create_Furniture()
{
	/*
	//�� ��� ���� ��ġ
	Sprite* fnt_middle1 = (Sprite*)this->getChildByName("Furniture_middle1");
	Rect Rec_middle1 = fnt_middle1->getBoundingBox();
	fnt_middle1->addComponent(It->Save_ItemData());
	fnt_middle1->setPosition(100 + rand() % (int)win_size.width*0.5, 150 + rand() % (int)win_size.height*0.5);
	
	Sprite* fnt_middle2 = (Sprite*)this->getChildByName("Furniture_middle2");
	Rect Rec_middle2 = fnt_middle2->getBoundingBox();
	fnt_middle2->setPosition(400 + rand() % (int)win_size.width*0.5, 250 + rand() % (int)win_size.height*0.5);

	//==================rand�� ���� �� ���� ��ġ 6������ ����� ��=======================
	int randnum = rand() % 6;

	//��-���� ���� ��ġ
	Sprite* fnt_wall1 = (Sprite*)this->getChildByName("Furniture_wall1");
	Rect Rec_wall1 = fnt_wall1->getBoundingBox();
	fnt_wall1->setPosition(Ary_fnt_wall_pos[rand() % 2]);

	//��-���� ���� ��ġ
	Sprite* fnt_wall2 = (Sprite*)this->getChildByName("Furniture_wall2");
	Rect Rec_wall2 = fnt_wall2->getBoundingBox();
	fnt_wall2->setPosition(Ary_fnt_wall_pos[rand() % 2 + 2]);

	//��-���� ���� ��ġ
	Sprite* fnt_wall3 = (Sprite*)this->getChildByName("Furniture_wall3");
	Rect Rec_wall3 = fnt_wall3->getBoundingBox();
	fnt_wall3->setPosition(Ary_fnt_wall_pos[rand() % 2 + 4]);

	//��-���� ���� ��ġ
	Sprite* fnt_wall4 = (Sprite*)this->getChildByName("Furniture_wall4");
	Rect Rec_wall4 = fnt_wall4->getBoundingBox();
	fnt_wall4->setPosition(Ary_fnt_wall_pos[rand() % 2 + 6]);

	if (randnum == 0)
	{
		fnt_wall1->setVisible(true);
		fnt_wall2->setVisible(true);
	}
	else if (randnum == 1)
	{
		fnt_wall1->setVisible(true);
		fnt_wall3->setVisible(true);
	}
	else if (randnum == 2)
	{
		fnt_wall1->setVisible(true);
		fnt_wall4->setVisible(true);
	}
	else if (randnum == 3)
	{
		fnt_wall2->setVisible(true);
		fnt_wall3->setVisible(true);
	}
	else if (randnum == 4)
	{
		fnt_wall2->setVisible(true);
		fnt_wall4->setVisible(true);
	}
	else if (randnum == 5)
	{
		fnt_wall3->setVisible(true);
		fnt_wall4->setVisible(true);
	}
	//==================rand�� ���� �� ���� ��ġ 6������ ����� ��=======================
	*/

}

void Furniture::Touch_React()
{
	/*
	//�÷��̾��� ��Ʈ�� ������ ��Ʈ�� �浹���¿��� ���� ��ư�� Ȱ��ȭ. ��ư �Է½� ���� ��� �Լ�
	Sprite* ftn_wall1 = (Sprite*)this->getChildByName("Furniture_wall1");
	Sprite* ftn_wall2 = (Sprite*)this->getChildByName("Furniture_wall2");
	Sprite* ftn_middle1 = (Sprite*)this->getChildByName("Furniture_middle1");
	Sprite* ftn_middle2 = (Sprite*)this->getChildByName("Furniture_middle1");


	Rect wall1 = ftn_wall1->getBoundingBox();
	Rect wall2 = ftn_wall2->getBoundingBox();
	Rect middle2 = ftn_middle1->getBoundingBox();
	Rect middle1 = ftn_middle2->getBoundingBox();

	//�Ʒ��� if�� �ۼ��� ��...

	//�÷��̾ ���� ������ Ž���ϴ��� üũ �ʿ�(���� �浹 ���� ����)

	//������ �������� ����/���� ���
	if (It->save_item == true)
	{
		if (It->weapon == true)
		{
			//UI�Ŵ��� �ʿ� weapon(_atk) Ȱ��ȭ �� ++;
			It->weapon = false;
		}
		else if (It->key == true)
		{
			//UI�Ŵ��� �ʿ� key(_key) Ȱ��ȭ �� ++;
			It->key = false;
		}
		else if (It->trap == true)
		{
			//UI�Ŵ��� �ʿ� trap(_trap) Ȱ��ȭ �� ++;
			It->trap = false;
		}
	}
	else
	{
		//�ƹ��͵� ����
	}
	*/

	/*CCLOG("Touch React OK");

	Sprite* spr = (Sprite*)this->getChildByName("Searchbutton");
	spr->setVisible(false);

	FntData* Sfnt = new FntData;
	Sfnt->F_ItemData = It->itm;

	Sfnt->search = true;
	Sfnt->F_ItemData->no_item = true;

	if (Sfnt->F_ItemData->key)
		Sfnt->F_ItemData->key = false;

	if (Sfnt->F_ItemData->weapon)
		Sfnt->F_ItemData->weapon = false;

	if (Sfnt->F_ItemData->trap)
		Sfnt->F_ItemData->trap = false;*/
}

//��ġ ���� �� �Ǵ��� �׽�Ʈ
bool Furniture::onTouchBegan(Touch * touch, Event * unused_event) 
{
	Sprite* spr = (Sprite*)this->getChildByName("Searchbutton");
	Rect rect1 = spr->getBoundingBox();

	if (rect1.containsPoint(touch->getLocation()))
	{
		isselect = true;
		select = (Sprite*)this->getChildByName("Searchbutton");
		CCLOG("TOUCH TOUCH TOUCH");
		Touch_React();
	}
	else

	return true;
}

void Furniture::onTouchEnded(Touch * touch, Event * unused_event)
{
	
}

