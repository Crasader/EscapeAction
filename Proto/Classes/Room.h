#pragma once
#include "cocos2d.h"
#include <string>

using namespace std;
USING_NS_CC;
struct RoomInfo {
	int num;
	int n;//if -1, no door. or p_roomCnt = escapeDoor
	int w;
	int e;
	int s;
	RoomInfo* p_next;
};
class Room
{
public:
	Room(int level, Layer* ly);
	~Room();

	int GetRoonCnt();
	bool MoveRoom(int dir);

private:
	int p_level;
	int p_roomCnt; 
	int p_room[4][4];//room position setting. if -1 no room
	int p_escDoor;
	Size win_size;

	Label* back;
	Label* nDoor;
	Label* wDoor;
	Label* eDoor;
	Label* sDoor;

	Layer* p_ly;
	RoomInfo* escRoom;
	RoomInfo* now;
	void RoomSetting(int roomCnt);
	void RoomInfoSet();
	void DrawBack();
	void FirstRoomSet();

};

