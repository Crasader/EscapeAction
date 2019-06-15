#include "Room.h"


Room::Room(int level)
{
	p_level = level;
	p_roomCnt = level * 2 + 2;
	RoomSetting(p_roomCnt);
}

Room::~Room()
{
}

int Room::GetRoonCnt()
{
	return p_roomCnt;
}

void Room::RoomSetting(int roomCnt)
{
	//p_room[][] reset to 0
	int col = sizeof(p_room[0]) / sizeof(int);
	int row = sizeof(p_room) / sizeof(p_room[0]);

	for (int i = 0; i < row;i++) {
		for (int j = 0; j < col; j++) {
			p_room[i][j] = 0;
		}
	}

	int makeRoom = 0;//now room Cnt

	//escape Room setting
	int escRoomPos[2];//col.row
	int escDoor = RandomHelper::random_int(0, 3);//escape door direction. 0~3 : n,w,e,s
	if (escDoor < 2) {
		p_room[0][0] = 1;
		escRoomPos[0] = 0;
		escRoomPos[1] = 0;
	}
	else {
		p_room[col-1][row-1] = 1;
		escRoomPos[0] = col-1;
		escRoomPos[1] = row-1;
	}
	makeRoom++;

	while (makeRoom < roomCnt) {
		int newCnt = RandomHelper::random_int(1, 3);
		makeRoom++;

	}

}
