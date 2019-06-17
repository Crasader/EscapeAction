#include "Furniture.h"


Furniture::~Furniture()
{
}

bool Furniture::init()
{
	/*if (!Layer::init())
	{
		return false;
	}*/

	win_size = Director::getInstance()->getWinSize();

	srand(time(NULL));

	return true;
}

void Furniture::Create_Fnt()
{
	auto fnt_wall1 = Sprite::create("panda.png"); //벽쪽 가구 스프라이트 생성
	auto fnt_wall2 = Sprite::create("panda.png"); //벽쪽 가구 스프라이트 생성
	auto fnt_middle1 = Sprite::create("panda.png"); //방 가운데 가구 스프라이트 생성
	auto fnt_middle2 = Sprite::create("panda.png"); //방 가운데 가구 스프라이트 생성
	//한 방에 가구 총 4개 생성

	//각 가구마다 태그 붙임
	fnt_wall1->setTag(1);
	fnt_wall2->setTag(2);
	fnt_middle1->setTag(3);
	fnt_middle2->setTag(4);

	int wall_x = 50 + ((rand() % (int)win_size.width*0.5)); //벽 x좌표 랜덤(임의 값 넣어둠)
	int wall_y = 50 + ((rand() % (int)win_size.height*0.5)); //벽 y좌표 랜덤(임의 값 넣어둠)

	int middle_x = 50 + ((rand() % (int)win_size.width*0.5)); //방 가운데 x좌표 랜덤(임의 값 넣어둠)
	int middle_y = 50 + ((rand() % (int)win_size.height*0.5)); //방 가운데 y좌표 랜덤(임의 값 넣어둠)

	fnt_wall1->setPosition(Point(wall_x, wall_y));
	fnt_wall2->setPosition(Point(wall_x, wall_y));
	fnt_middle1->setPosition(Point(middle_x, middle_y));
	fnt_middle2->setPosition(Point(middle_x, middle_y));
	//가구 포지션 랜덤으로 배치(차후 서로 겹치지 않는 코드 추가할 것)

	this->addChild(fnt_wall1);
	this->addChild(fnt_wall2);
	this->addChild(fnt_middle1);
	this->addChild(fnt_middle2);
	//최종 배치 후 출력
}

void Furniture::Touch_React()
{
	//플레이어의 렉트와 가구의 렉트가 충돌상태에서 조사 버튼이 활성화. 버튼 입력시 반응 출력 함수
	Sprite* ftn_wall1 = (Sprite*)this->getChildByTag(1);
	Sprite* ftn_wall2 = (Sprite*)this->getChildByTag(2);
	Sprite* ftn_middle1 = (Sprite*)this->getChildByTag(3);
	Sprite* ftn_middle2 = (Sprite*)this->getChildByTag(4);

	Rect wall1 = ftn_wall1->getBoundingBox();
	Rect wall2 = ftn_wall2->getBoundingBox();
	Rect middle2 = ftn_middle1->getBoundingBox();
	Rect middle1 = ftn_middle2->getBoundingBox();

	//아래는 if문 작성할 것...
}
