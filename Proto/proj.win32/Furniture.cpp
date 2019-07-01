#include "Furniture.h"


Furniture::~Furniture()
{
}
//190701
bool Furniture::init()
{
	win_size = Director::getInstance()->getWinSize();

	srand(time(NULL));
	
	//아이템 클래스 생성
	It = Item::create();
	this->addChild(It);

	CCLOG("Furniture OK"); //퍼니쳐 클래스 제대로 씬에서 실행되는지 확인

	//==============================가구 데이터 생성======================================
	FntData* Sfnt = new FntData;
	Sfnt->F_ItemData = It->itm; //아이템 데이터 구조체 연결

	//각 아이템 데이터 true 확인
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

	//가구 탐색 bool 초기화
	Sfnt->search = false;

	//가구 데이터 벡터 접근
	vector<FntData*>::iterator v = v_FntData.begin();

	//가구 개수 랜덤으로 지정
	Sfnt->fnt_num = rand() % 5 + 1;

	CCLOG("fnt_num : %d", Sfnt->fnt_num);

	//가구 개수만큼 가구 데이터 벡터로 push
	for (int i = 0; i < Sfnt->fnt_num; i++)
	{
		v_FntData.push_back(Sfnt);
	}
	
	CCLOG("vector fntdata size : %d", v_FntData.size());

	//==============================가구 데이터 생성======================================
	

	//가구 종류 늘어나면 스프라이트 더 추가됨
	Sprite* fnt_wall1 = Sprite::create("button1.png");
	fnt_wall1->setPosition(500, 500);
	fnt_wall1->setName("Fnt_wall1");

	Sprite* fnt_wall2 = Sprite::create("button2.png");
	fnt_wall2->setPosition(600, 500);
	fnt_wall2->setName("Fnt_wall2");

	//탐색 버튼
	Sprite* searchbutton = Sprite::create("buttonB.png");
	searchbutton->setPosition(300, 500);
	searchbutton->setName("Searchbutton");

	this->addChild(searchbutton, 10);


	//가구 종류 스프라이트 랜덤 지정
	Sfnt->fnt_sprite = rand() % 1;
	if(Sfnt->fnt_sprite==0)
		this->addChild(fnt_wall1, 1);
	if(Sfnt->fnt_sprite==1)
		this->addChild(fnt_wall2, 1);


	//==========================================================================아래로 옛날코드
	/*

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
	fnt_wall1->setName("Furniture_wall1");
	fnt_wall2->setName("Furniture_wall2");
	fnt_wall3->setName("Furniture_wall3");
	fnt_wall4->setName("Furniture_wall4");

	//방 가운데 가구 태그
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
	//방 가운데 가구 배치
	Sprite* fnt_middle1 = (Sprite*)this->getChildByName("Furniture_middle1");
	Rect Rec_middle1 = fnt_middle1->getBoundingBox();
	fnt_middle1->addComponent(It->Save_ItemData());
	fnt_middle1->setPosition(100 + rand() % (int)win_size.width*0.5, 150 + rand() % (int)win_size.height*0.5);
	
	Sprite* fnt_middle2 = (Sprite*)this->getChildByName("Furniture_middle2");
	Rect Rec_middle2 = fnt_middle2->getBoundingBox();
	fnt_middle2->setPosition(400 + rand() % (int)win_size.width*0.5, 250 + rand() % (int)win_size.height*0.5);

	//==================rand에 따른 벽 가구 배치 6가지의 경우의 수=======================
	int randnum = rand() % 6;

	//벽-북쪽 가구 배치
	Sprite* fnt_wall1 = (Sprite*)this->getChildByName("Furniture_wall1");
	Rect Rec_wall1 = fnt_wall1->getBoundingBox();
	fnt_wall1->setPosition(Ary_fnt_wall_pos[rand() % 2]);

	//벽-서쪽 가구 배치
	Sprite* fnt_wall2 = (Sprite*)this->getChildByName("Furniture_wall2");
	Rect Rec_wall2 = fnt_wall2->getBoundingBox();
	fnt_wall2->setPosition(Ary_fnt_wall_pos[rand() % 2 + 2]);

	//벽-동쪽 가구 배치
	Sprite* fnt_wall3 = (Sprite*)this->getChildByName("Furniture_wall3");
	Rect Rec_wall3 = fnt_wall3->getBoundingBox();
	fnt_wall3->setPosition(Ary_fnt_wall_pos[rand() % 2 + 4]);

	//벽-남쪽 가구 배치
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
	//==================rand에 따른 벽 가구 배치 6가지의 경우의 수=======================
	*/

}

void Furniture::Touch_React()
{
	/*
	//플레이어의 렉트와 가구의 렉트가 충돌상태에서 조사 버튼이 활성화. 버튼 입력시 반응 출력 함수
	Sprite* ftn_wall1 = (Sprite*)this->getChildByName("Furniture_wall1");
	Sprite* ftn_wall2 = (Sprite*)this->getChildByName("Furniture_wall2");
	Sprite* ftn_middle1 = (Sprite*)this->getChildByName("Furniture_middle1");
	Sprite* ftn_middle2 = (Sprite*)this->getChildByName("Furniture_middle1");


	Rect wall1 = ftn_wall1->getBoundingBox();
	Rect wall2 = ftn_wall2->getBoundingBox();
	Rect middle2 = ftn_middle1->getBoundingBox();
	Rect middle1 = ftn_middle2->getBoundingBox();

	//아래는 if문 작성할 것...

	//플레이어가 무슨 가구를 탐색하는지 체크 필요(현재 충돌 중인 가구)

	//가구에 아이템이 있을/없을 경우
	if (It->save_item == true)
	{
		if (It->weapon == true)
		{
			//UI매니저 쪽에 weapon(_atk) 활성화 및 ++;
			It->weapon = false;
		}
		else if (It->key == true)
		{
			//UI매니저 쪽에 key(_key) 활성화 및 ++;
			It->key = false;
		}
		else if (It->trap == true)
		{
			//UI매니저 쪽에 trap(_trap) 활성화 및 ++;
			It->trap = false;
		}
	}
	else
	{
		//아무것도 없음
	}
	*/

	CCLOG("Touch React OK");

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
		Sfnt->F_ItemData->trap = false;
}

//터치 반응 잘 되는지 테스트
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

