#include "Room.h"


Room::~Room()
{
}

bool Room::init()
{
	int level = 5;

	win_size = Director::getInstance()->getWinSize();

	background = Sprite::create("Background.png");
	background->setPosition(Point(win_size.width*0.5f, win_size.height*0.5));

	door_n = Sprite::create("Door.png");
	door_n->setAnchorPoint(Vec2(0.5,0));
	door_n->setPosition(Point(win_size.width*0.5, win_size.height*0.905));

	door_w = Sprite::create("Door.png");
	door_w->setAnchorPoint(Vec2(0.5, 0));
	door_w->setRotation(-90);
	door_w->setPosition(Point(win_size.width*0.06, win_size.height*0.5));


	door_e = Sprite::create("Door.png");
	door_e->setAnchorPoint(Vec2(0.5, 0));
	door_e->setRotation(90);
	door_e->setPosition(Point(win_size.width*0.94, win_size.height*0.5));

	door_s = Sprite::create("Door.png");
	door_s->setAnchorPoint(Vec2(0.5, 0));
	door_s->setRotation(-180);
	door_s->setPosition(Point(win_size.width*0.5, win_size.height*0.095));

	back = Label::createWithTTF("0", "fonts/arial.ttf", 20);
	back->setPosition(Point(win_size.width*0.5, win_size.height*0.5));

	nDoor = Label::createWithTTF("0", "fonts/arial.ttf", 20);
	nDoor->setPosition(Point(win_size.width*0.5, win_size.height*0.95));

	wDoor = Label::createWithTTF("0", "fonts/arial.ttf", 20);
	wDoor->setPosition(Point(win_size.width*0.05, win_size.height*0.5));

	eDoor = Label::createWithTTF("0", "fonts/arial.ttf", 20);
	eDoor->setPosition(Point(win_size.width*0.95, win_size.height*0.5));

	sDoor = Label::createWithTTF("0", "fonts/arial.ttf", 20);
	sDoor->setPosition(Point(win_size.width*0.5, win_size.height*0.05));


	p_escDoor = 0;
	p_level = level;
	p_roomCnt = level * 2 + 2;
	RoomSetting(p_roomCnt);
	RoomInfoSet();
	FirstRoomSet();
	DrawBack();

	return true;
}

int Room::GetRoonCnt()
{
	return p_roomCnt;
}

bool Room::MoveRoom(int dir)
{
	RoomInfo* cursor = escRoom;
	int moveNum = -1;//if -1 , no Move;
	switch (dir)
	{
	case 0:
		moveNum = now->n;
		break;
	case 1:
		moveNum = now->w;
		break;
	case 2:
		moveNum = now->e;
		break;
	case 3:
		moveNum = now->s;
		break;
	default:
		break;
	}

	if (moveNum == p_roomCnt) {
		exit(0);
	}

	if (moveNum >= 0) {

		for (int i = 0; i < moveNum; i++) {
			cursor = cursor->p_next;
		}

		now = cursor;
		back->setString(to_string(now->num));
		nDoor->setString(to_string(now->n));
		wDoor->setString(to_string(now->w));
		eDoor->setString(to_string(now->e));
		sDoor->setString(to_string(now->s));

		door_n->setVisible(now->n >= 0 ? true : false);
		door_w->setVisible(now->w >= 0 ? true : false);
		door_e->setVisible(now->e >= 0 ? true : false);
		door_s->setVisible(now->s >= 0 ? true : false);
	}
	return true;
}

void Room::RoomSetting(int roomCnt)
{
	//p_room[][] reset to 0
	int colSize = sizeof(p_room[0]) / sizeof(int);
	int rowSize = sizeof(p_room) / sizeof(p_room[0]);

	if (roomCnt > colSize*rowSize) {
		roomCnt = colSize * rowSize;
	}

	for (int i = 0; i < rowSize;i++) {
		for (int j = 0; j < colSize; j++) {
			p_room[i][j] = -1;
		}
	}


	int num = 0;//room number, 0 is escape room

	int preColMin = 0;
	int preColMax = colSize - 1;

	//first row
	for (int row = 0; row < rowSize;row++) {
		int col = RandomHelper::random_int(preColMin, preColMax);
		int colMinCnt = (int)((roomCnt - num) / (rowSize - row));//1~
		int colMaxCnt = (roomCnt - num) > colSize ? colSize : (roomCnt - num);
		p_room[row][col] = num;
		num++;
		preColMin = col;
		preColMax = col;

		int colCnt = RandomHelper::random_int(colMinCnt,colMaxCnt);// room count when row = i, 1~
		int a = 1;
		for (int i = 0; i < colCnt - 1;i++) {
			if (col + a < 0) {//a<0
				a = -a;
				a++;
			}
			else if (col + a >= colSize) {//a>0
				a = -a;
			}

			if (a > 0) {
				preColMax = col + a;
			}
			else {
				preColMin = col + a;
			}
			p_room[row][col + a] = num;
			num++;
			a = -a;
			if (a > 0) {
				a++;
			}
		}
	
		if (num >= roomCnt) {
			break;
		}
	}
	
	//rotate escape door 
	p_escDoor = RandomHelper::random_int(0, 3);//0~3 : nwes

	//only sqaure matrix, if not sqaure matrix make tmp_save[][] in header and edit code
	if (rowSize == colSize) {
		int** save = new int*[rowSize];
		for (int i = 0; i < rowSize; i++) {
			save[i] = new int[colSize];
		}
		switch (p_escDoor)
		{
		case 1://w
			for (int i = 0; i < rowSize; i++) {
				for (int j = 0; j < colSize; j++) {
					save[j][i] = p_room[i][j];
				}
			}
			for (int i = 0; i < rowSize; i++) {
				for (int j = 0; j < colSize; j++) {
					p_room[i][j] = save[i][j];
				}
			}
			break;
		case 2://e
			for (int i = 0; i < rowSize; i++) {
				for (int j = 0; j < colSize; j++) {
					save[j][rowSize - 1 - i] = p_room[i][j];
				}
			}
			for (int i = 0; i < rowSize; i++) {
				for (int j = 0; j < colSize; j++) {
					p_room[i][j] = save[i][j];
				}
			}
			break;
		case 3://s
			for (int i = 0; i < rowSize; i++) {
				for (int j = 0; j < colSize; j++) {
					save[rowSize - 1 - i][j] = p_room[i][j];
				}
			}
			for (int i = 0; i < rowSize; i++) {
				for (int j = 0; j < colSize; j++) {
					p_room[i][j] = save[i][j];
				}
			}
			break;
		default:
			break;
		}
	}
	
	//print log.
	for (int i = 0; i < rowSize; i++) {
		for (int j = 0; j < colSize; j++) {
			CCLOG("%d",p_room[i][j]);
		}
		CCLOG("\n");
	}


}

void Room::RoomInfoSet()
{
	int colSize = sizeof(p_room[0]) / sizeof(int);
	int rowSize = sizeof(p_room) / sizeof(p_room[0]);
	
	int roomNum = 0;
	RoomInfo* cursor;
	while (roomNum < p_roomCnt) {

		if (roomNum == 0) {
			escRoom = new RoomInfo;
			cursor = escRoom;
		}
		else {
			cursor->p_next = new RoomInfo;
			cursor = cursor->p_next;
		}
		cursor->num = roomNum;
		cursor->p_next = NULL;
		cursor->n = -1;
		cursor->w = -1;
		cursor->e = -1;
		cursor->s = -1;

		bool breakFor = false;
		int i = 0;
		int j = 0;
		for (i = 0; i < rowSize; i++) {
			for (j = 0; j < colSize; j++) {
				if (p_room[i][j] == roomNum) {
					breakFor = true;
					break;
				}
			}
			if (breakFor) {
				break;
			}
		}

		if (i - 1 >= 0) {
			cursor->n = p_room[i - 1][j];
		}
		if (j-1>=0) {
			cursor->w = p_room[i][j - 1];
		}
		if (j+1<colSize) {
			cursor->e = p_room[i][j + 1];
		}
		if (i + 1 < rowSize) {
			cursor->s = p_room[i + 1][j];
		}

		roomNum++;
	}

	switch (p_escDoor) {
	case 0:
		escRoom->n = p_roomCnt;
		break;
	case 1:
		escRoom->w = p_roomCnt;
		break;
	case 2:
		escRoom->e = p_roomCnt;
		break;
	case 3:
		escRoom->s = p_roomCnt;
		break;
	default:
		break;
	
	}
}

void Room::DrawBack()
{
	this->addChild(background);
	this->addChild(door_n);
	this->addChild(door_w);
	this->addChild(door_e);
	this->addChild(door_s);

	this->addChild(back);
	this->addChild(nDoor);
	this->addChild(wDoor);
	this->addChild(eDoor);
	this->addChild(sDoor);

}

void Room::FirstRoomSet()
{
	int nowRoom = RandomHelper::random_int(1,p_roomCnt-1);
	RoomInfo* cursor = escRoom;
	for (int i = 0; i < nowRoom; i++) {
		cursor = cursor->p_next;
	}
	now = cursor;
	back->setString(to_string(now->num));
	nDoor->setString(to_string(now->n));
	wDoor->setString(to_string(now->w));
	eDoor->setString(to_string(now->e));
	sDoor->setString(to_string(now->s));

	
	door_n->setVisible(now->n >= 0 ? true : false);
	door_w->setVisible(now->w >= 0 ? true : false);
	door_e->setVisible(now->e >= 0 ? true : false);
	door_s->setVisible(now->s >= 0 ? true : false);

}
