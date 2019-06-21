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

	//���� ���� �� 8��
	Sprite* fnt_wall1 = Sprite::create("button1.png"); 
	Sprite* fnt_wall2 = Sprite::create("button2.png"); 
	Sprite* fnt_wall3 = Sprite::create("buttonA.png"); 
	Sprite* fnt_wall4 = Sprite::create("buttonB.png"); 
	Sprite* fnt_wall5 = Sprite::create("button1.png"); 
	Sprite* fnt_wall6 = Sprite::create("button2.png"); 
	Sprite* fnt_wall7 = Sprite::create("buttonA.png"); 
	Sprite* fnt_wall8 = Sprite::create("buttonB.png"); 

	//�� ��� ���� �� 2��
	Sprite* fnt_middle1 = Sprite::create("buttonA.png"); 
	Sprite* fnt_middle2 = Sprite::create("buttonB.png"); 

	//��-����
	fnt_wall1->setPosition(win_size.width*0.28, win_size.height*0.906);
	fnt_wall2->setPosition(win_size.width*0.72, win_size.height*0.906);
	
	//��-����
	fnt_wall3->setPosition(win_size.width*0.06, win_size.height*0.3);
	fnt_wall4->setPosition(win_size.width*0.06, win_size.height*0.703);

	//��-����
	fnt_wall5->setPosition(win_size.width*0.941, win_size.height*0.3);
	fnt_wall6->setPosition(win_size.width*0.941, win_size.height*0.703);

	//��-����
	fnt_wall7->setPosition(win_size.width*0.28, win_size.height*0.093);
	fnt_wall8->setPosition(win_size.width*0.72, win_size.height*0.093);

	//�� ���� �±�
	fnt_wall1->setTag(1);
	fnt_wall2->setTag(2);
	fnt_wall3->setTag(3);
	fnt_wall4->setTag(4);
	fnt_wall5->setTag(5);
	fnt_wall6->setTag(6);
	fnt_wall7->setTag(7);
	fnt_wall8->setTag(8);

	//�� ��� ���� �±�
	fnt_middle1->setTag(9);
	fnt_middle2->setTag(10);

	/*this->addChild(fnt_wall1);
	this->addChild(fnt_wall2);
	this->addChild(fnt_wall3);
	this->addChild(fnt_wall4);
	this->addChild(fnt_wall5);
	this->addChild(fnt_wall6);
	this->addChild(fnt_wall7);
	this->addChild(fnt_wall8);*/
	this->addChild(fnt_middle1);
	this->addChild(fnt_middle2);


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


	//�±� ��ȣ �������(�õ��ϴ� ������)
	int randomnum = 1 + (rand() % 7);

	if (0 < randomnum < 9)
		CCLOG("KKKKKKKKKKKKKKKKKKKKKKKKKK");

	if (randomnum == 1)
	{
		Sprite* fnt_wall_random = (Sprite*)this->getChildByTag(randomnum);
		this->addChild(fnt_wall_random);
	}
	else if (randomnum == 2)
	{
		Sprite* fnt_wall_random = (Sprite*)this->getChildByTag(randomnum);
		this->addChild(fnt_wall_random);
	}
	else if (randomnum == 3)
	{
		Sprite* fnt_wall_random = (Sprite*)this->getChildByTag(randomnum);
		this->addChild(fnt_wall_random);
	}
	else if (randomnum == 4)
	{
		Sprite* fnt_wall_random = (Sprite*)this->getChildByTag(randomnum);
		this->addChild(fnt_wall_random);
	}
	else if (randomnum == 5)
	{
		Sprite* fnt_wall_random = (Sprite*)this->getChildByTag(randomnum);
		this->addChild(fnt_wall_random);
	}
	else if (randomnum == 6)
	{
		Sprite* fnt_wall_random = (Sprite*)this->getChildByTag(randomnum);
		this->addChild(fnt_wall_random);
	}
	else if (randomnum == 7)
	{
		Sprite* fnt_wall_random = (Sprite*)this->getChildByTag(randomnum);
		this->addChild(fnt_wall_random);
	}
	else if (randomnum == 8)
	{
		Sprite* fnt_wall_random = (Sprite*)this->getChildByTag(randomnum);
		this->addChild(fnt_wall_random);
	}
	else
		CCLOG("�Ф�");

	/*
	Sprite* fnt_wall_random = (Sprite*)this->getChildByTag(randomnum);
	this->addChild(fnt_wall_random);
	*/

}

void Furniture::Touch_React()
{
	//�÷��̾��� ��Ʈ�� ������ ��Ʈ�� �浹���¿��� ���� ��ư�� Ȱ��ȭ. ��ư �Է½� ���� ��� �Լ�
	Sprite* ftn_wall1 = (Sprite*)this->getChildByTag(1);
	Sprite* ftn_wall2 = (Sprite*)this->getChildByTag(2);
	Sprite* ftn_middle1 = (Sprite*)this->getChildByTag(3);
	Sprite* ftn_middle2 = (Sprite*)this->getChildByTag(4);

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

