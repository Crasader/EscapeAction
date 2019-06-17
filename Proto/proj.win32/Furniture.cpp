#include "Furniture.h"


Furniture::~Furniture()
{
}

bool Furniture::init()
{
	if (!Layer::init())
	{
		return false;
	}

	win_size = Director::getInstance()->getWinSize();

	srand(time(NULL));

	return true;
}

void Furniture::Create_Fnt()
{
	auto fnt = Sprite::create("panda.png"); //���� ��������Ʈ ����

	int x = 50 + ((rand() % (int)win_size.width*0.5)); //x��ǥ ����(���� �� �־��)
	int y = 50 + ((rand() % (int)win_size.height*0.5)); //y��ǥ ����(���� �� �־��)

	fnt->setPosition(Point(x, y));

	this->addChild(fnt);
}

void Furniture::React()
{

}
