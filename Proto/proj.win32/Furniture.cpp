#include "Furniture.h"
#include "DataManager.h"

Furniture::~Furniture()
{

}
//190712
bool Furniture::init()
{
	
	/*srand(time(NULL));
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

	*/
	return true;
}

bool Furniture::init(int left, int right, bool ladder)
{
	//초기화
	v_FntData.clear();
	v_fntKind.clear();

	win_size = Director::getInstance()->getWinSize();

	CCLOG("Furniture OK"); //퍼니쳐 클래스 제대로 씬에서 실행되는지 확인

	int totalLeft = 0;
	int totalRight = 0;
	vector<FntData*> v_FntData_l;
	vector<FntData*> v_FntData_r;
	v_FntData_l.clear();
	v_FntData_r.clear();

	const int arr_count = DataManager::getInstance()->getFurData()->GetArray().Size();//가구 종류 갯수
	for (int i = 0; i < arr_count; i++) {
		v_fntKind.push_back(i);
	}
	//가구 랜덤설정
	for (int cnt = 0; cnt < 2; cnt++) {//0일때 left, 1일때 right
		//가구 개수 랜덤으로 지정
		int maxCnt = v_fntKind.size() > 5 ? 5 : v_fntKind.size();//최대 가구 갯수가 5개 
		int blank_cnt = cnt == 0 ? left : right;

		maxCnt = blank_cnt < maxCnt ? blank_cnt : maxCnt;//최대 가구 갯수보가 빈공간 크기가 적은 경우 
		if (maxCnt == 0) {//더 이상 세팅할 가구가 없는 경우
			continue;
		}
		int min = 1;
		if (left == 0 || right == 0) {//사다리가 한쪽에 몰려있거나 없는 경우 가구는 적어도 3개
			min = 3;
		}
		int fnt_num = RandomHelper::random_int(min, maxCnt);

		//가구 개수만큼 가구 데이터 벡터로 push
		for (int i = 0; i < fnt_num; i++)
		{
			//아이템 클래스 생성
			Item* It = Item::create();

			FntData* Sfnt = new FntData;

			It->v_item.clear();

			//각 아이템 데이터 true 확인
			if (It->itm->weapon)
			{
				Sfnt->item_num = 0;
				It->v_item.push_back(0);
				CCLOG("Weapon True");
			}
			if (It->itm->key)
			{
				Sfnt->item_num = 1;
				It->v_item.push_back(1);
				CCLOG("Key True");
			}
			if (It->itm->trap)
			{
				Sfnt->item_num = 2;
				It->v_item.push_back(2);
				CCLOG("Trap True");
			}
			if (It->itm->no_item)
			{
				Sfnt->item_num = 3;
				It->v_item.push_back(3);
				CCLOG("No_Item True");
			}
		

			int furKindCnt = v_fntKind.size();
			int order = RandomHelper::random_int(0, furKindCnt-1);
			int fur_rand = v_fntKind.at(order);

			Sfnt->fnt_size = DataManager::getInstance()->getFurData()->GetArray()[fur_rand]["size"].GetInt();
			int fur_max = cnt == 0 ? left : right;
			int nowSize = cnt == 0 ? totalLeft : totalRight;
			if (nowSize + Sfnt->fnt_size > fur_max) {//방에 들어 갈 수 있는 가구 total 크기 최댓값;
				break;
			}
			v_fntKind.erase(v_fntKind.begin() + order);


			Sfnt->fnt_img = DataManager::getInstance()->getFurData()->GetArray()[fur_rand]["name"].GetString();

			Sfnt->deco = DataManager::getInstance()->getFurData()->GetArray()[fur_rand]["deco"].GetBool();
			
			
			if (cnt == 0) {
				totalLeft += Sfnt->fnt_size;
				v_FntData_l.push_back(Sfnt);
			}
			else {
				totalRight += Sfnt->fnt_size;
				v_FntData_r.push_back(Sfnt);
			}
			CCLOG("vector back : %d", It->v_item.back());
			CCLOG("v_item size : %d", It->v_item.size());
		}
		
	}

	

	//pos 지정
	int preFurPos = 0;//이전 가구 끝 위치
	for (auto& fur_l : v_FntData_l) {
		int max = left - totalLeft+1;
		fur_l->pos = RandomHelper::random_int(preFurPos + 1, max);
		preFurPos = fur_l->pos+ fur_l->fnt_size-1;
		totalLeft -= fur_l->fnt_size;
		v_FntData.push_back(fur_l);
	}
	
	preFurPos = 0;

	for (auto& fur_r : v_FntData_r) {
		int max = right - totalRight + 1;
		int pos = RandomHelper::random_int(preFurPos + 1, max);
		int startPos = left;
		if (ladder) {
			startPos++;
		}
		fur_r->pos = pos + startPos;
		preFurPos = pos + fur_r->fnt_size - 1;
		totalRight -= fur_r->fnt_size;
		v_FntData.push_back(fur_r);
	}

	return true;
}

Furniture * Furniture::create(int left, int right, bool ladder)
{
	Furniture* fur = new(std::nothrow) Furniture();
	if(fur&&fur->init(left,right, ladder)){
		fur->autorelease();
		return fur;
	}
	CC_SAFE_DELETE(fur);
	return nullptr;
}
