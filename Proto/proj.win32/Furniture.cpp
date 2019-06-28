#include "Furniture.h"


Furniture::~Furniture()
{
}
//190626
bool Furniture::init()
{
	win_size = Director::getInstance()->getWinSize();

	srand(time(NULL));
	
	//������ Ŭ���� ����
	It = Item::create();
	this->addChild(It);

	CCLOG("Furniture OK"); //�۴��� Ŭ���� ����� ������ ����Ǵ��� Ȯ��

	//==============================���� ������ ����======================================
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

	//���� Ž�� bool �ʱ�ȭ
	Sfnt->search = false;

	//���� ������ ���� ����
	std::vector<FntData*>::iterator v = v_FntData.begin();

	//���� ���� �������� ����
	Sfnt->fnt_num = rand() % 5 + 1;

	CCLOG("fnt_num : %d", Sfnt->fnt_num);

	//���� ������ŭ ���� ������ ���ͷ� push
	for (int i = 0; i < Sfnt->fnt_num; i++)
	{
		v_FntData.push_back(Sfnt);
	}
	
	CCLOG("vector fntdata size : %d", v_FntData.size());

	//==============================���� ������ ����======================================
	

	//���� ���� �þ�� ��������Ʈ �� �߰���
	Sprite* fnt_wall1 = Sprite::create("button1.png");
	Sprite* fnt_wall2 = Sprite::create("button2.png");

	Sprite* searchbutton = Sprite::create("buttonB.png");



	//==========================================================================�Ʒ��� �����ڵ�
	/*

	//=============���� ��ġ �׽�Ʈ
	select = NULL;
	isselect = false;
	//=============���� ��ġ �׽�Ʈ

	//���� ���� �� 4��(�ϼ�����)
	Sprite* fnt_wall1 = Sprite::create("button1.png"); 
	Sprite* fnt_wall2 = Sprite::create("button2.png"); 
	Sprite* fnt_wall3 = Sprite::create("buttonA.png"); 
	Sprite* fnt_wall4 = Sprite::create("buttonB.png"); 

	//�� ��� ���� �� 2��
	Sprite* fnt_middle1 = Sprite::create("buttonA.png"); 
	Sprite* fnt_middle2 = Sprite::create("buttonB.png"); 	

	//��-����
	Ary_fnt_wall_pos[0] = Vec2(win_size.width*0.28, win_size.height*0.906);
	Ary_fnt_wall_pos[1] = Vec2(win_size.width*0.72, win_size.height*0.906);
	
	//��-����
	Ary_fnt_wall_pos[2] = Vec2(win_size.width*0.06, win_size.height*0.3);
	Ary_fnt_wall_pos[3] = Vec2(win_size.width*0.06, win_size.height*0.703);

	//��-����
	Ary_fnt_wall_pos[4] = Vec2(win_size.width*0.941, win_size.height*0.3);
	Ary_fnt_wall_pos[5] = Vec2(win_size.width*0.941, win_size.height*0.703);

	//��-����
	Ary_fnt_wall_pos[6] = Vec2(win_size.width*0.28, win_size.height*0.093);
	Ary_fnt_wall_pos[7] = Vec2(win_size.width*0.72, win_size.height*0.093);

	//�� ���� �±�
	fnt_wall1->setName("Furniture_wall1");
	fnt_wall2->setName("Furniture_wall2");
	fnt_wall3->setName("Furniture_wall3");
	fnt_wall4->setName("Furniture_wall4");

	//�� ��� ���� �±�
	fnt_middle1->setName("Furniture_middle1");
	fnt_middle2->setName("Furniture_middle2");

	this->addChild(fnt_wall1);
	this->addChild(fnt_wall2);
	this->addChild(fnt_wall3);
	this->addChild(fnt_wall4);

	this->addChild(fnt_middle1);
	this->addChild(fnt_middle2);

	fnt_wall1->setVisible(false);
	fnt_wall2->setVisible(false);
	fnt_wall3->setVisible(false);
	fnt_wall4->setVisible(false);

	*/

	//==================��ġ �׽�Ʈ
	auto listner = EventListenerTouchOneByOne::create();
	listner->onTouchBegan = CC_CALLBACK_2(Furniture::onTouchBegan, this);
	listner->onTouchEnded = CC_CALLBACK_2(Furniture::onTouchEnded, this);

	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listner, 1);


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

}

//������ġ ���� �� �Ǵ��� �׽�Ʈ
bool Furniture::onTouchBegan(Touch * touch, Event * unused_event) 
{
	/*Sprite* spr = (Sprite*)this->getChildByName("Furniture_wall1");
	Rect rect1 = spr->getBoundingBox();

	if (rect1.containsPoint(touch->getLocation()))
	{
		isselect = true;
		select = (Sprite*)this->getChildByName("Furniture_wall1");
		CCLOG("TOUCH TOUCH TOUCH");
	}
	else
	{ }*/

	return true;
}

void Furniture::onTouchEnded(Touch * touch, Event * unused_event)
{
	
}

