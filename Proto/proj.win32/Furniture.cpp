#include "Furniture.h"


Furniture::~Furniture()
{

}
//190701
bool Furniture::init()
{
	//초기화
	totalLeft = 0;
	totalRight = 0;
	Document fur_name;
	//파일 오픈 & 파싱
	FILE* fp = fopen("jsonData/name/nameFur.json", "rb");
	char readBuffer[5000];
	FileReadStream is(fp, readBuffer, sizeof(readBuffer));
	fur_name.ParseStream(is);
	fclose(fp);

	srand(time(NULL));
	win_size = Director::getInstance()->getWinSize();
	
	int total_fntSize = 0;
	CCLOG("Furniture OK"); //퍼니쳐 클래스 제대로 씬에서 실행되는지 확인

	//가구 데이터 벡터 접근
	vector<FntData*>::iterator v = v_FntData.begin();

	//가구 개수 랜덤으로 지정
	int fnt_num = RandomHelper::random_int(2, 5);


	//가구 개수만큼 가구 데이터 벡터로 push
	for (int i = 0; i < fnt_num; i++)
	{
	
		//아이템 클래스 생성
		Item* It=Item::create();

		FntData* Sfnt = new FntData;
		//Sfnt->F_ItemData = It->itm; //아이템 데이터 구조체 연결

		//각 아이템 데이터 true 확인
		if (It->itm->weapon)
		{
			Sfnt->item_num = 0;
			//CCLOG("Weapon True");
		}
		if (It->itm->key)
		{
			Sfnt->item_num = 1;
			//CCLOG("Key True");
		}
		if (It->itm->trap)
		{
			Sfnt->item_num = 2;
			//CCLOG("Trap True");
		}
		if (It->itm->no_item)
		{
			Sfnt->item_num = 3;
			//CCLOG("No_Item True");
		}

		//가구 랜덤설정
		assert(fur_name.IsArray());
		int arr_count = -1;
		for (auto& fur : fur_name.GetArray()) {
			arr_count++;
		}

		int fur_rand = RandomHelper::random_int(0, arr_count);
		//log("fur_rand : %d", fur_rand);
		assert(fur_name[fur_rand].HasMember("name"));
		assert(fur_name[fur_rand]["name"].IsString());
		Sfnt->fnt_img = fur_name[fur_rand]["name"].GetString();
		bool retry = false;
		for (auto v : v_FntData) {
			if(Sfnt->fnt_img==v->fnt_img){
				retry = true;
				break;
			}
		}
		if (retry) {
			i--;
			continue;
		}

		assert(fur_name[fur_rand].HasMember("size"));
		assert(fur_name[fur_rand]["size"].IsInt());
		Sfnt->fnt_size = fur_name[fur_rand]["size"].GetInt();
		if (total_fntSize + Sfnt->fnt_size > 5) {//방에 들어 갈 수 있는 가구 total 크기 최댓값 = 5;
			CCLOG("fnt_num : %d", i);
			break;
		}
		assert(fur_name[fur_rand].HasMember("deco"));
		assert(fur_name[fur_rand]["deco"].IsBool());
		Sfnt->deco = fur_name[fur_rand]["deco"].GetBool();

		total_fntSize += Sfnt->fnt_size;
		//가구 탐색 bool 초기화
//		Sfnt->search = false;
		v_FntData.push_back(Sfnt);
	}
	int i = 0;
	for (auto v : v_FntData) {
		//log("%d item : %d", i, v->item_num);
		i++;
	}
	//log("rand_fnt : %d", fnt_num);
	log("v_fnt : %d", v_FntData.size());
	//CCLOG("vector fntdata size : %d", v_FntData.size());

	//auto listner = EventListenerTouchOneByOne::create();
	//listner->onTouchBegan = CC_CALLBACK_2(Furniture::onTouchBegan, this);
	//listner->onTouchEnded = CC_CALLBACK_2(Furniture::onTouchEnded, this);

	//Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listner, 2);


	return true;
}

bool Furniture::init(int left, int right)
{
	//초기화
	v_FntData_l.clear();
	v_FntData_r.clear();
	v_fntKind.clear();
	Document fur_name;
	//파일 오픈 & 파싱
	FILE* fp = fopen("jsonData/name/nameFur.json", "rb");
	char readBuffer[5000];
	FileReadStream is(fp, readBuffer, sizeof(readBuffer));
	fur_name.ParseStream(is);
	fclose(fp);

	//srand(time(NULL));
	win_size = Director::getInstance()->getWinSize();

	CCLOG("Furniture OK"); //퍼니쳐 클래스 제대로 씬에서 실행되는지 확인

	//가구 데이터 벡터 접근
	//vector<FntData*>::iterator v = v_FntData.begin();
	//가구 랜덤설정
	assert(fur_name.IsArray());
	const int arr_count = fur_name.GetArray().Size();//가구 종류 갯수
	for (int i = 0; i < arr_count; i++) {
		v_fntKind.push_back(i);
	}

	for (int cnt = 0; cnt < 2; cnt++) {//0일때 left, 1일때 right
		//가구 개수 랜덤으로 지정
		int maxCnt = v_fntKind.size() > 5 ? 5 : v_fntKind.size();
		int blank_cnt = cnt == 0 ? left : right;
		log("%d %d", blank_cnt, maxCnt);
		maxCnt = blank_cnt < maxCnt ? blank_cnt : maxCnt;
		if (maxCnt == 0) {//더 이상 세팅할 가구가 없는 경우
			continue;
		}
		int min = 1;
		if (left == 0 || right == 0) {
			min = 3;
		}
		int fnt_num = RandomHelper::random_int(min, maxCnt);

		//가구 개수만큼 가구 데이터 벡터로 push
		for (int i = 0; i < fnt_num; i++)
		{
			//아이템 클래스 생성
			Item* It = Item::create();

			FntData* Sfnt = new FntData;

			//각 아이템 데이터 true 확인
			if (It->itm->weapon)
			{
				Sfnt->item_num = 0;
				//CCLOG("Weapon True");
			}
			if (It->itm->key)
			{
				Sfnt->item_num = 1;
				//CCLOG("Key True");
			}
			if (It->itm->trap)
			{
				Sfnt->item_num = 2;
				//CCLOG("Trap True");
			}
			if (It->itm->no_item)
			{
				Sfnt->item_num = 3;
				//CCLOG("No_Item True");
			}
			int furKindCnt = v_fntKind.size();
			int order = RandomHelper::random_int(0, furKindCnt-1);
			int fur_rand = v_fntKind.at(order);

			assert(fur_name[fur_rand].HasMember("size"));
			assert(fur_name[fur_rand]["size"].IsInt());
			Sfnt->fnt_size = fur_name[fur_rand]["size"].GetInt();
			int fur_max = cnt == 0 ? left : right;
			int nowSize = cnt == 0 ? totalLeft : totalRight;
			if (nowSize + Sfnt->fnt_size > fur_max) {//방에 들어 갈 수 있는 가구 total 크기 최댓값;
				break;
			}
			v_fntKind.erase(v_fntKind.begin() + order);

			assert(fur_name[fur_rand].HasMember("name"));
			assert(fur_name[fur_rand]["name"].IsString());
			Sfnt->fnt_img = fur_name[fur_rand]["name"].GetString();

			Sfnt->deco = fur_name[fur_rand]["deco"].GetBool();
			//가구 탐색 bool 초기화
			//Sfnt->search = false;
			
			if (cnt == 0) {
				totalLeft += Sfnt->fnt_size;
				v_FntData_l.push_back(Sfnt);
			}
			else {
				totalRight += Sfnt->fnt_size;
				v_FntData_r.push_back(Sfnt);
			}
		}
	}
	//pos 지정
	int preFurPos = 0;//이전 가구 끝 위치
	for (auto& fur_l : v_FntData_l) {
		int max = left - totalLeft+1;
		int pos = RandomHelper::random_int(preFurPos + 1, max);
		fur_l->pos = (float)(fur_l->fnt_size - 1)*0.5+pos;
		preFurPos = pos+ fur_l->fnt_size-1;
		totalLeft -= fur_l->fnt_size;
		log("left : %s  pos : %f", fur_l->fnt_img.c_str(), fur_l->pos);
	}
	preFurPos = 0;
	for (auto& fur_r : v_FntData_r) {
		int max = right - totalRight + 1;
		int pos = RandomHelper::random_int(preFurPos + 1, max);
		fur_r->pos = (float)(fur_r->fnt_size - 1)*0.5 + pos;
		preFurPos = pos + fur_r->fnt_size - 1;
		totalRight -= fur_r->fnt_size;
		log("right : %s  pos : %f", fur_r->fnt_img.c_str(), fur_r->pos);
	}
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

Furniture * Furniture::create(int left, int right)
{
	Furniture* fur = new(std::nothrow) Furniture();
	if(fur&&fur->init(left,right)){
		fur->autorelease();
		return fur;
	}
	CC_SAFE_DELETE(fur);
	return nullptr;
}

//터치 반응 잘 되는지 테스트
//bool Furniture::onTouchBegan(Touch * touch, Event * unused_event) 
//{
//	Sprite* spr = (Sprite*)this->getChildByName("Searchbutton");
//	Rect rect1 = spr->getBoundingBox();
//
//	if (rect1.containsPoint(touch->getLocation()))
//	{
//		isselect = true;
//		select = (Sprite*)this->getChildByName("Searchbutton");
//		CCLOG("TOUCH TOUCH TOUCH");
//		Touch_React();
//	}
//	else
//
//	return true;
//}
//
//void Furniture::onTouchEnded(Touch * touch, Event * unused_event)
//{
//	
//}

