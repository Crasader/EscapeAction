#include "Furniture.h"


Furniture::~Furniture()
{
}

bool Furniture::init()
{
	win_size = Director::getInstance()->getWinSize();

	srand(time(NULL));

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
	fnt_wall1->setTag(1);
	fnt_wall2->setTag(2);
	fnt_wall3->setTag(3);
	fnt_wall4->setTag(4);

	//�� ��� ���� �±�
	fnt_middle1->setTag(5);
	fnt_middle2->setTag(6);

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
	//���� ������ �������� ��ġ(���� ���� ��ġ�� �ʴ� �ڵ�, ���տ� ������ �ʴ� �ڵ� �߰��� ��)
	//�������� �� 8���� �ɰ��� ��ġ�ϰų�...(�ʹ� �����Ѱ�)
	Sprite* fnt_wall1 = (Sprite*)this->getChildByTag(1);
	Sprite* fnt_wall2 = (Sprite*)this->getChildByTag(2);
	Sprite* fnt_middle1 = (Sprite*)this->getChildByTag(3);
	Sprite* fnt_middle2 = (Sprite*)this->getChildByTag(4);

	
	if (rand() % 100 >= 50)
	{
		fnt_wall1->setPosition((rand() % (int)win_size.width*0.94), win_size.height*0.905);
		fnt_wall2->setPosition(win_size.width*0.94, ((rand() % (int)win_size.height*0.9)));
		CCLOG("HELP HELP HELP");
	}
	else
	{
		fnt_wall1->setPosition(((rand() % (int)win_size.width*0.94)), win_size.height*0.095);
		fnt_wall2->setPosition(win_size.width*0.06, (rand() % (int)win_size.height*0.9));
		CCLOG("WANT GO TO HOME");
	}

	fnt_middle1->setPosition(200 + rand() % (int)win_size.width*0.5, 100 + rand() % (int)win_size.height*0.5);
	fnt_middle2->setPosition(200 + rand() % (int)win_size.width*0.5, 100 + rand() % (int)win_size.height*0.5);
	*/

	////�����Լ� ��ġ�� ���� ���� ���� ���
	//if (0 <= rand() % 100 <= 12)
	//{
	//	Sprite* fnt_wall1 = (Sprite*)this->getChildByTag(1);
	//}
	//else if (13 <= rand() % 100 <= 38)
	//{
	//	Sprite* fnt_wall2 = (Sprite*)this->getChildByTag(2);
	//}
	//else if (39 <= rand() % 100 <= 64)
	//{
	//	Sprite* fnt_wall3 = (Sprite*)this->getChildByTag(3);	
	//}
	//else
	//{
	//	Sprite* fnt_wall4 = (Sprite*)this->getChildByTag(4);
	//}

	/*
	//�±� ��ȣ �������(�õ��ϴ� ������)
	int randomnum = 1 + (rand() % 7);

	Sprite* fnt_wall_random = (Sprite*)this->getChildByTag(randomnum);
	this->addChild(fnt_wall_random);
	*/

	//�� ��� ���� ��ġ
	Sprite* fnt_middle1 = (Sprite*)this->getChildByTag(5);
	Rect Rec_middle1 = fnt_middle1->getBoundingBox();
	fnt_middle1->setPosition(100 + rand() % (int)win_size.width*0.5, 150 + rand() % (int)win_size.height*0.5);
	
	Sprite* fnt_middle2 = (Sprite*)this->getChildByTag(6);
	Rect Rec_middle2 = fnt_middle2->getBoundingBox();
	fnt_middle2->setPosition(400 + rand() % (int)win_size.width*0.5, 250 + rand() % (int)win_size.height*0.5);

	//==================rand�� ���� �� ���� ��ġ 6������ ����� ��=======================
	int randnum = rand() % 6;

	//��-���� ���� ��ġ
	Sprite* fnt_wall1 = (Sprite*)this->getChildByTag(1);
	Rect Rec_wall1 = fnt_wall1->getBoundingBox();
	fnt_wall1->setPosition(Ary_fnt_wall_pos[rand() % 2]);

	//��-���� ���� ��ġ
	Sprite* fnt_wall2 = (Sprite*)this->getChildByTag(2);
	Rect Rec_wall2 = fnt_wall2->getBoundingBox();
	fnt_wall2->setPosition(Ary_fnt_wall_pos[rand() % 2 + 2]);

	//��-���� ���� ��ġ
	Sprite* fnt_wall3 = (Sprite*)this->getChildByTag(3);
	Rect Rec_wall3 = fnt_wall3->getBoundingBox();
	fnt_wall3->setPosition(Ary_fnt_wall_pos[rand() % 2 + 4]);

	//��-���� ���� ��ġ
	Sprite* fnt_wall4 = (Sprite*)this->getChildByTag(4);
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
}

void Furniture::Touch_React()
{
	//�÷��̾��� ��Ʈ�� ������ ��Ʈ�� �浹���¿��� ���� ��ư�� Ȱ��ȭ. ��ư �Է½� ���� ��� �Լ�
	Sprite* ftn_wall1 = (Sprite*)this->getChildByTag(1);
	Sprite* ftn_wall2 = (Sprite*)this->getChildByTag(2);
	Sprite* ftn_middle1 = (Sprite*)this->getChildByTag(5);
	Sprite* ftn_middle2 = (Sprite*)this->getChildByTag(6);

	Rect wall1 = ftn_wall1->getBoundingBox();
	Rect wall2 = ftn_wall2->getBoundingBox();
	Rect middle2 = ftn_middle1->getBoundingBox();
	Rect middle1 = ftn_middle2->getBoundingBox();

	//�Ʒ��� if�� �ۼ��� ��...

}

//������ġ ���� �� �Ǵ��� �׽�Ʈ
bool Furniture::onTouchBegan(Touch * touch, Event * unused_event) 
{
	Sprite* spr = (Sprite*)this->getChildByTag(1);
	Rect rect1 = spr->getBoundingBox();

	if (rect1.containsPoint(touch->getLocation()))
	{
		isselect = true;
		select = (Sprite*)this->getChildByTag(1);
		CCLOG("TOUCH TOUCH TOUCH");
	}
	else
	{ }

	return true;
}

void Furniture::onTouchEnded(Touch * touch, Event * unused_event)
{
}

