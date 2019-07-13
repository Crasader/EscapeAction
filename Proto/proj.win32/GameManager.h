#pragma once
#include <iostream>
#include "cocos2d.h"
#include "player.h"

USING_NS_CC;
class GameManager
{
	/*�÷��̾� ���� ������ �����ϴ� Manager*/
private:
	GameManager();
	~GameManager();

	player* _player;

public:
	static GameManager* getInstance();

	// �÷��̾� ����,  ���� ������ true ��ȯ
	bool setPlayer(player* player);
	
	//�÷��̾� state
	player_Move_enum getPlayerState();
	bool setState(player_Move_enum state);//state ���� ������ true ��ȯ
	void playerEndLoopAni();
	//�÷��̾� ��
	int getPlayerRoomNum();
	void setPlayerRoomNum(int num);
	//�÷��̾� rect
	Rect getPlayerRect();
	//�÷��̾� ��
	int getPlayerFloor();
	void setPlayerFloor(int floor);
	//�÷��̾� ��ġ
	float getPlayerPositionX();
	void setPlayerPositionX(float posX);
	//�÷��̾�� ������ ��
	void setContactDoorWithPlayer(Sprite* doorSpr);
};

