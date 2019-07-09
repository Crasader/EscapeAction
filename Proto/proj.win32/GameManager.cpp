#include "GameManager.h"
static GameManager* pGameManager = NULL;



GameManager::GameManager()
{
	//초기화
	_player = NULL;
}


GameManager::~GameManager()
{
}

GameManager * GameManager::getInstance()
{
	if (pGameManager == NULL) {
		pGameManager = new GameManager;
	}
	return pGameManager;
}

bool GameManager::setPlayer(player * player)
{
	if (_player == NULL) {
		_player = player;
		return true;
	}
	return false;
}

player_Move_enum GameManager::getPlayerState()
{
	return _player->getState();
}

bool GameManager::setState(player_Move_enum state)
{
	return _player->setState(state);//state가 제대로 들어갔을때 true 반환
}

