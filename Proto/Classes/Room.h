#pragma once
#include "cocos2d.h"

USING_NS_CC;

class Room
{
public:
	Room(int level);
	~Room();

	int GetRoonCnt();
	

private:
	int p_level;
	int p_roomCnt; 
	int p_room[4][4];//room position setting. if 0 no room
	void RoomSetting(int roomCnt);

};

