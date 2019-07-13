#pragma once
#include <iostream>
#include "cocos2d.h"
#include "player.h"

USING_NS_CC;
class GameManager
{
	/*플레이어 관련 정보를 제어하는 Manager*/
private:
	GameManager();
	~GameManager();

	player* _player;

public:
	static GameManager* getInstance();

	// 플레이어 세팅,  세팅 성공시 true 반환
	bool setPlayer(player* player);
	
	//플레이어 state
	player_Move_enum getPlayerState();
	bool setState(player_Move_enum state);//state 세팅 성공시 true 반환
	void playerEndLoopAni();
	//플레이어 방
	int getPlayerRoomNum();
	void setPlayerRoomNum(int num);
	//플레이어 rect
	Rect getPlayerRect();
	//플레이어 층
	int getPlayerFloor();
	void setPlayerFloor(int floor);
	//플레이어 위치
	float getPlayerPositionX();
	void setPlayerPositionX(float posX);
	//플레이어와 인접한 문
	void setContactDoorWithPlayer(Sprite* doorSpr);
};

