#pragma once
#include <iostream>
#include "cocos2d.h"
#include "player.h"

USING_NS_CC;
class GameManager
{
private:
	GameManager();
	~GameManager();

	player* _player;

public:
	static GameManager* getInstance();

	// 세팅 성공시 true 반환
	bool setPlayer(player* player);
	
	//플레이어 state
	player_Move_enum getPlayerState();
	bool setState(player_Move_enum state);//state 세팅 성공시 true 반환
};

