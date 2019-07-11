#include "Furniture.h"


Furniture::~Furniture()
{

}
//190701
bool Furniture::init()
{
	
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

bool Furniture::init(int left, int right, bool ladder)
{
	//�ʱ�ȭ
	v_FntData.clear();
	v_fntKind.clear();

	//���� ���� & �Ľ�
	Document fur_name;
	FILE* fp = fopen("jsonData/name/nameFur.json", "rb");
	char readBuffer[5000];
	FileReadStream is(fp, readBuffer, sizeof(readBuffer));
	fur_name.ParseStream(is);
	fclose(fp);

	win_size = Director::getInstance()->getWinSize();

	CCLOG("Furniture OK"); //�۴��� Ŭ���� ����� ������ ����Ǵ��� Ȯ��

	int totalLeft = 0;
	int totalRight = 0;
	vector<FntData*> v_FntData_l;
	vector<FntData*> v_FntData_r;
	v_FntData_l.clear();
	v_FntData_r.clear();

	assert(fur_name.IsArray());
	const int arr_count = fur_name.GetArray().Size();//���� ���� ����
	for (int i = 0; i < arr_count; i++) {
		v_fntKind.push_back(i);
	}
	//���� ��������
	for (int cnt = 0; cnt < 2; cnt++) {//0�϶� left, 1�϶� right
		//���� ���� �������� ����
		int maxCnt = v_fntKind.size() > 5 ? 5 : v_fntKind.size();//�ִ� ���� ������ 5�� 
		int blank_cnt = cnt == 0 ? left : right;

		maxCnt = blank_cnt < maxCnt ? blank_cnt : maxCnt;//�ִ� ���� �������� ����� ũ�Ⱑ ���� ��� 
		if (maxCnt == 0) {//�� �̻� ������ ������ ���� ���
			continue;
		}
		int min = 1;
		if (left == 0 || right == 0) {//��ٸ��� ���ʿ� �����ְų� ���� ��� ������ ��� 3��
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
