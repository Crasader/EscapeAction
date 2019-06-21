#include "Furniture.h"


Furniture::~Furniture()
{
}

bool Furniture::init()
{
	win_size = Director::getInstance()->getWinSize();

	srand(time(NULL));

	//=============가구 터치 테스트
	select = NULL;
	isselect = false;
	//=============가구 터치 테스트

	//벽쪽 가구 총 4개(북서동남)
	Sprite* fnt_wall1 = Sprite::create("button1.png"); 
	Sprite* fnt_wall2 = Sprite::create("button2.png"); 
	Sprite* fnt_wall3 = Sprite::create("buttonA.png"); 
	Sprite* fnt_wall4 = Sprite::create("buttonB.png"); 

	//방 가운데 가구 총 2개
	Sprite* fnt_middle1 = Sprite::create("buttonA.png"); 
	Sprite* fnt_middle2 = Sprite::create("buttonB.png"); 	

	//벽-북쪽
	Ary_fnt_wall_pos[0] = Vec2(win_size.width*0.28, win_size.height*0.906);
	Ary_fnt_wall_pos[1] = Vec2(win_size.width*0.72, win_size.height*0.906);
	
	//벽-서쪽
	Ary_fnt_wall_pos[2] = Vec2(win_size.width*0.06, win_size.height*0.3);
	Ary_fnt_wall_pos[3] = Vec2(win_size.width*0.06, win_size.height*0.703);

	//벽-동쪽
	Ary_fnt_wall_pos[4] = Vec2(win_size.width*0.941, win_size.height*0.3);
	Ary_fnt_wall_pos[5] = Vec2(win_size.width*0.941, win_size.height*0.703);

	//벽-남쪽
	Ary_fnt_wall_pos[6] = Vec2(win_size.width*0.28, win_size.height*0.093);
	Ary_fnt_wall_pos[7] = Vec2(win_size.width*0.72, win_size.height*0.093);

	//벽 가구 태그
	fnt_wall1->setTag(Furniture_wall1);
	fnt_wall2->setTag(Furniture_wall2);
	fnt_wall3->setTag(Furniture_wall3);
	fnt_wall4->setTag(Furniture_wall4);

	//방 가운데 가구 태그
	fnt_middle1->setTag(Furniture_middle1);
	fnt_middle2->setTag(Furniture_middle2);

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

	//==================터치 테스트
	auto listner = EventListenerTouchOneByOne::create();
	listner->onTouchBegan = CC_CALLBACK_2(Furniture::onTouchBegan, this);
	listner->onTouchEnded = CC_CALLBACK_2(Furniture::onTouchEnded, this);

	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listner, 1);


	return true;
}

void Furniture::Create_Furniture()
{
	/*
	//가구 포지션 랜덤으로 배치(차후 서로 겹치지 않는 코드, 문앞에 생기지 않는 코드 추가할 것)
	//생각중인 건 8개로 쪼개서 배치하거나...(너무 복잡한가)
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

	////랜드함수 수치에 따른 가구 랜덤 출력
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
	//태그 번호 랜덤출력(시도하다 망했음)
	int randomnum = 1 + (rand() % 7);

	Sprite* fnt_wall_random = (Sprite*)this->getChildByTag(randomnum);
	this->addChild(fnt_wall_random);
	*/

	//방 가운데 가구 배치
	Sprite* fnt_middle1 = (Sprite*)this->getChildByTag(Furniture_middle1);
	Rect Rec_middle1 = fnt_middle1->getBoundingBox();
	fnt_middle1->setPosition(100 + rand() % (int)win_size.width*0.5, 150 + rand() % (int)win_size.height*0.5);
	
	Sprite* fnt_middle2 = (Sprite*)this->getChildByTag(Furniture_middle1);
	Rect Rec_middle2 = fnt_middle2->getBoundingBox();
	fnt_middle2->setPosition(400 + rand() % (int)win_size.width*0.5, 250 + rand() % (int)win_size.height*0.5);

	//==================rand에 따른 벽 가구 배치 6가지의 경우의 수=======================
	int randnum = rand() % 6;

	//벽-북쪽 가구 배치
	Sprite* fnt_wall1 = (Sprite*)this->getChildByTag(Furniture_wall1);
	Rect Rec_wall1 = fnt_wall1->getBoundingBox();
	fnt_wall1->setPosition(Ary_fnt_wall_pos[rand() % 2]);

	//벽-서쪽 가구 배치
	Sprite* fnt_wall2 = (Sprite*)this->getChildByTag(Furniture_wall12);
	Rect Rec_wall2 = fnt_wall2->getBoundingBox();
	fnt_wall2->setPosition(Ary_fnt_wall_pos[rand() % 2 + 2]);

	//벽-동쪽 가구 배치
	Sprite* fnt_wall3 = (Sprite*)this->getChildByTag(Furniture_wall3);
	Rect Rec_wall3 = fnt_wall3->getBoundingBox();
	fnt_wall3->setPosition(Ary_fnt_wall_pos[rand() % 2 + 4]);

	//벽-남쪽 가구 배치
	Sprite* fnt_wall4 = (Sprite*)this->getChildByTag(Furniture_wall4);
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
	//==================rand에 따른 벽 가구 배치 6가지의 경우의 수=======================
}

void Furniture::Touch_React()
{
	//플레이어의 렉트와 가구의 렉트가 충돌상태에서 조사 버튼이 활성화. 버튼 입력시 반응 출력 함수
	Sprite* ftn_wall1 = (Sprite*)this->getChildByTag(Furniture_wall1);
	Sprite* ftn_wall2 = (Sprite*)this->getChildByTag(Furniture_wall2);
	Sprite* ftn_middle1 = (Sprite*)this->getChildByTag(Furniture_middle1);
	Sprite* ftn_middle2 = (Sprite*)this->getChildByTag(Furniture_middle1);

	Rect wall1 = ftn_wall1->getBoundingBox();
	Rect wall2 = ftn_wall2->getBoundingBox();
	Rect middle2 = ftn_middle1->getBoundingBox();
	Rect middle1 = ftn_middle2->getBoundingBox();

	//아래는 if문 작성할 것...

}

//가구터치 반응 잘 되는지 테스트
bool Furniture::onTouchBegan(Touch * touch, Event * unused_event) 
{
	Sprite* spr = (Sprite*)this->getChildByTag(Furniture_wall1);
	Rect rect1 = spr->getBoundingBox();

	if (rect1.containsPoint(touch->getLocation()))
	{
		isselect = true;
		select = (Sprite*)this->getChildByTag(Furniture_wall1);
		CCLOG("TOUCH TOUCH TOUCH");
	}
	else
	{ }

	return true;
}

void Furniture::onTouchEnded(Touch * touch, Event * unused_event)
{
}

