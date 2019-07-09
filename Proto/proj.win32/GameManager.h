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

	// ���� ������ true ��ȯ
	bool setPlayer(player* player);
	
	//�÷��̾� state
	player_Move_enum getPlayerState();
	bool setState(player_Move_enum state);//state ���� ������ true ��ȯ
};

