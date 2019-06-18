#pragma once
#include "cocos2d.h"
#include <string>

using namespace std;
USING_NS_CC;

struct RoomInfo {
	int num;
	int door[4];//0:n 1:w 2:e 3:s if -1 no door/have door = room number, p_roomCnt = escapeDoor
	RoomInfo* p_next;
	int color;
};

class Room : public Node
{
public:
	CREATE_FUNC(Room);
	bool init();
	~Room();
	int GetRoonCnt();
	bool MoveRoom(int dir);

private:
	int p_level;
	int p_roomCnt; 
	int p_room[4][4];//room position setting. if -1 no room
	int p_escDoor;
	Size win_size;

	Sprite* background;
	Sprite* door_sp[4];
	
	RoomInfo* escRoom;
	RoomInfo* now;
	void RoomSetting(int roomCnt);
	void RoomInfoSet();
	void ChangeRoomByNum(int roomNum);
	void DrawBack();
	void FirstRoomSet();
	void TestLabelDraw();
	void TestLabelUpdate();
	Label* back;
	Label* door_lab[4];

};

