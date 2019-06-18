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

	Label* back;
	Sprite* background;
	Sprite* door_n;
	Sprite* door_w;
	Sprite* door_e;
	Sprite* door_s;

	Label* nDoor;
	Label* wDoor;
	Label* eDoor;
	Label* sDoor;

	RoomInfo* escRoom;
	RoomInfo* now;
	void RoomSetting(int roomCnt);
	void RoomInfoSet();
	void DrawBack();
	void FirstRoomSet();


};

