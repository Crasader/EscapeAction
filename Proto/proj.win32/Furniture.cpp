#include "Furniture.h"


Furniture::~Furniture()
{

}
//190701
bool Furniture::init()
{
	//�ʱ�ȭ
	totalLeft = 0;
	totalRight = 0;
	Document fur_name;
	//���� ���� & �Ľ�
	FILE* fp = fopen("jsonData/name/nameFur.json", "rb");
	char readBuffer[5000];
	FileReadStream is(fp, readBuffer, sizeof(readBuffer));
	fur_name.ParseStream(is);
	fclose(fp);

	srand(time(NULL));
	win_size = Director::getInstance()->getWinSize();
	
	int total_fntSize = 0;
	CCLOG("Furniture OK"); //�۴��� Ŭ���� ����� ������ ����Ǵ��� Ȯ��

	//���� ������ ���� ����
	vector<FntData*>::iterator v = v_FntData.begin();

	//���� ���� �������� ����
	int fnt_num = RandomHelper::random_int(2, 5);


	//���� ������ŭ ���� ������ ���ͷ� push
	for (int i = 0; i < fnt_num; i++)
	{
	
		//������ Ŭ���� ����
		Item* It=Item::create();

		FntData* Sfnt = new FntData;
		//Sfnt->F_ItemData = It->itm; //������ ������ ����ü ����

		//�� ������ ������ true Ȯ��
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

		//���� ��������
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
		if (total_fntSize + Sfnt->fnt_size > 5) {//�濡 ��� �� �� �ִ� ���� total ũ�� �ִ� = 5;
			CCLOG("fnt_num : %d", i);
			break;
		}
		assert(fur_name[fur_rand].HasMember("deco"));
		assert(fur_name[fur_rand]["deco"].IsBool());
		Sfnt->deco = fur_name[fur_rand]["deco"].GetBool();

		total_fntSize += Sfnt->fnt_size;
		//���� Ž�� bool �ʱ�ȭ
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
	//�ʱ�ȭ
	v_FntData_l.clear();
	v_FntData_r.clear();
	v_fntKind.clear();
	Document fur_name;
	//���� ���� & �Ľ�
	FILE* fp = fopen("jsonData/name/nameFur.json", "rb");
	char readBuffer[5000];
	FileReadStream is(fp, readBuffer, sizeof(readBuffer));
	fur_name.ParseStream(is);
	fclose(fp);

	//srand(time(NULL));
	win_size = Director::getInstance()->getWinSize();

	CCLOG("Furniture OK"); //�۴��� Ŭ���� ����� ������ ����Ǵ��� Ȯ��

	//���� ������ ���� ����
	//vector<FntData*>::iterator v = v_FntData.begin();
	//���� ��������
	assert(fur_name.IsArray());
	const int arr_count = fur_name.GetArray().Size();//���� ���� ����
	for (int i = 0; i < arr_count; i++) {
		v_fntKind.push_back(i);
	}

	for (int cnt = 0; cnt < 2; cnt++) {//0�϶� left, 1�϶� right
		//���� ���� �������� ����
		int maxCnt = v_fntKind.size() > 5 ? 5 : v_fntKind.size();
		int blank_cnt = cnt == 0 ? left : right;
		log("%d %d", blank_cnt, maxCnt);
		maxCnt = blank_cnt < maxCnt ? blank_cnt : maxCnt;
		if (maxCnt == 0) {//�� �̻� ������ ������ ���� ���
			continue;
		}
		int min = 1;
		if (left == 0 || right == 0) {
			min = 3;
		}
		int fnt_num = RandomHelper::random_int(min, maxCnt);

		//���� ������ŭ ���� ������ ���ͷ� push
		for (int i = 0; i < fnt_num; i++)
		{
			//������ Ŭ���� ����
			Item* It = Item::create();

			FntData* Sfnt = new FntData;

			//�� ������ ������ true Ȯ��
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
			if (nowSize + Sfnt->fnt_size > fur_max) {//�濡 ��� �� �� �ִ� ���� total ũ�� �ִ�;
				break;
			}
			v_fntKind.erase(v_fntKind.begin() + order);

			assert(fur_name[fur_rand].HasMember("name"));
			assert(fur_name[fur_rand]["name"].IsString());
			Sfnt->fnt_img = fur_name[fur_rand]["name"].GetString();

			Sfnt->deco = fur_name[fur_rand]["deco"].GetBool();
			//���� Ž�� bool �ʱ�ȭ
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
	//pos ����
	int preFurPos = 0;//���� ���� �� ��ġ
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

//��ġ ���� �� �Ǵ��� �׽�Ʈ
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

