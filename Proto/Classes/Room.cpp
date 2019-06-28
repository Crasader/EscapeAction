#include "Room.h"


Room::~Room()
{
}

bool Room::init()
{
	int level = 5;
	float scale = 1.5;
	win_size = Director::getInstance()->getWinSize();

	background = Sprite::create("Background.png");
	//background->setPosition(Point(win_size.width*0.5f, win_size.height*0.5));
	background->setScale(scale);
	Size bgSize = background->getContentSize();
	r = background->getBoundingBox();
	r = Rect(bgSize.width*scale*0.06+r.getMinX(), bgSize.height*scale*0.095+r.getMinY()
		, bgSize.width*scale*0.88, bgSize.height*scale*0.81);

	for (int i = 0; i < 4;i++) {
		door_sp[i] = Sprite::create("Door.png");
		door_sp[i]->setAnchorPoint(Vec2(0.5, 0));
		door_sp[i]->setColor(Color3B::BLACK);
		door_sp[i]->setScale(scale);
	}

	door_sp[0]->setPosition(Point(win_size.width*0.5,r.getMaxY()));//ºÏ

	door_sp[1]->setRotation(-90);
	door_sp[1]->setPosition(Point(r.getMinX(), win_size.height*0.5));//¼­

	door_sp[2] ->setRotation(90);
	door_sp[2]->setPosition(Point(r.getMaxX(), win_size.height*0.5));//µ¿

	door_sp[3]->setRotation(-180);
	door_sp[3]->setPosition(Point(win_size.width*0.5, r.getMinY()));//³²

	p_escDoor = 0;
	p_level = level;
	p_roomCnt = level * 2 + 2;
	RoomSetting(p_roomCnt);
	RoomInfoSet();
	DrawBack();
	TestLabelDraw();
	FirstRoomSet();

	//Furniture* ft;
	//ft.setRoomRect(r);
	Rect r2 = background->getBoundingBox();
	Furniture* funt = Furniture::create();
	funt->Create_Furniture();
	funt->setPosition(r2.getMinX(), r2.getMinY());
	funt->setScale(scale);
	this->addChild(funt);
	this->scheduleUpdate();
	
	return true;
}

int Room::GetRoonCnt()
{
	return p_roomCnt;
}

bool Room::MoveRoom(int dir)
{
	int moveNum = -1;//if -1 , no Move;
	
	moveNum = now->door[dir];

	if (moveNum == p_roomCnt) {
		exit(0);
	}

	if (moveNum >= 0) {
		ChangeRoomByNum(moveNum);
	}
	return true;
}

Rect Room::GetBackRect()
{
	return r;
}

void Room::RoomSetting(int roomCnt)
{
	//p_room[][] reset to -1
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
		//set random color
		cursor->color =p_roomCnt-roomNum-1;

		cursor->num = roomNum;
		cursor->p_next = NULL;
		for (int i = 0; i < 4;i++) {
			cursor->door[i] = -1;
		}

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
			cursor->door[0] = p_room[i - 1][j];
		}
		if (j-1>=0) {
			cursor->door[1] = p_room[i][j - 1];
		}
		if (j+1<colSize) {
			cursor->door[2] = p_room[i][j + 1];
		}
		if (i + 1 < rowSize) {
			cursor->door[3] = p_room[i + 1][j];
		}

		roomNum++;
	}
	escRoom->door[p_escDoor] = p_roomCnt;

}

void Room::ChangeRoomByNum(int roomNum)
{
	RoomInfo* cursor = escRoom;

	for (int i = 0; i < roomNum; i++) {
		cursor = cursor->p_next;
	}
	now = cursor;
	background->setColor(Color3B(255, now->color * 20, now->color * 20));
	for (int i = 0;i < 4;i++) {
		door_sp[i]->setVisible(now->door[i] >= 0 ? true : false);
	}
	if (now->door[p_escDoor] == p_roomCnt) {
		door_sp[p_escDoor]->setColor(Color3B::BLUE);
	}
	else {
		door_sp[p_escDoor]->setColor(Color3B::BLACK);
	}
	TestLabelUpdate();
}

void Room::DrawBack()
{
	this->addChild(background);
	for (int i = 0;i < 4;i++) {
		this->addChild(door_sp[i]);
	}

}

void Room::FirstRoomSet()
{
	int nowRoom = RandomHelper::random_int(1,p_roomCnt-1);
	ChangeRoomByNum(nowRoom);
}

void Room::TestLabelDraw()
{
	back = Label::createWithTTF("0", "fonts/arial.ttf", 20);
	back->setPosition(Point(win_size.width*0.5, win_size.height*0.5));

	for (int i = 0; i < 4;i++) {
		door_lab[i] = Label::createWithTTF("0", "fonts/arial.ttf", 20);
	}
	door_lab[0]->setPosition(Point(win_size.width*0.5,r.getMaxY()));

	door_lab[1]->setPosition(Point(r.getMinX(), win_size.height*0.5));

	door_lab[2]->setPosition(Point(r.getMaxX(), win_size.height*0.5));

	door_lab[3]->setPosition(Point(win_size.width*0.5, r.getMinY()));

	this->addChild(back,1);
	for (int i = 0;i < 4;i++) {
		this->addChild(door_lab[i],1);
	}
}

void Room::TestLabelUpdate()
{
	back->setString(to_string(now->num));
	for (int i = 0;i < 4;i++) {
		door_lab[i]->setString(to_string(now->door[i]));
	}
}

void Room::update(float dt)
{
	/*Vec2 move = UIManager::getInstance()->get_Player_m_p2() * 8;

	Vec2 pos = this->getPosition();
	float wid = background->getContentSize().width*background->getScale()*0.5f;
	float hei = background->getContentSize().height*background->getScale()*0.5f;
	
	if (move.x > 0 &&pos.x+wid+win_size.width*0.5<= win_size.width) {
		move.setPoint(0, move.y);
	}else if (move.x<0 && pos.x -wid + win_size.width*0.5 >= 0) {
		move.setPoint(0, move.y);
	}

	if (move.y > 0 && pos.y + hei + win_size.height*0.5 <= win_size.height) {
		move.setPoint(move.x, 0);
	}
	else if (move.y < 0 && pos.y - hei + win_size.height*0.5 >= 0) {
		move.setPoint(move.x, 0);
	}
	
	this->setPosition(pos.x-move.x, pos.y-move.y);*/
}
