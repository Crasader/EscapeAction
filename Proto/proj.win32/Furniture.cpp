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
	auto fnt_wall1 = Sprite::create("panda.png"); //���� ���� ��������Ʈ ����
	auto fnt_wall2 = Sprite::create("panda.png"); //���� ���� ��������Ʈ ����
	auto fnt_middle1 = Sprite::create("panda.png"); //�� ��� ���� ��������Ʈ ����
	auto fnt_middle2 = Sprite::create("panda.png"); //�� ��� ���� ��������Ʈ ����
	//�� �濡 ���� �� 4�� ����

	//�� �������� �±� ����
	fnt_wall1->setTag(1);
	fnt_wall2->setTag(2);
	fnt_middle1->setTag(3);
	fnt_middle2->setTag(4);

	int wall_x = 50 + ((rand() % (int)win_size.width*0.5)); //�� x��ǥ ����(���� �� �־��)
	int wall_y = 50 + ((rand() % (int)win_size.height*0.5)); //�� y��ǥ ����(���� �� �־��)

	int middle_x = 50 + ((rand() % (int)win_size.width*0.5)); //�� ��� x��ǥ ����(���� �� �־��)
	int middle_y = 50 + ((rand() % (int)win_size.height*0.5)); //�� ��� y��ǥ ����(���� �� �־��)

	fnt_wall1->setPosition(Point(wall_x, wall_y));
	fnt_wall2->setPosition(Point(wall_x, wall_y));
	fnt_middle1->setPosition(Point(middle_x, middle_y));
	fnt_middle2->setPosition(Point(middle_x, middle_y));
	//���� ������ �������� ��ġ(���� ���� ��ġ�� �ʴ� �ڵ� �߰��� ��)

	this->addChild(fnt_wall1);
	this->addChild(fnt_wall2);
	this->addChild(fnt_middle1);
	this->addChild(fnt_middle2);
	//���� ��ġ �� ���
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
