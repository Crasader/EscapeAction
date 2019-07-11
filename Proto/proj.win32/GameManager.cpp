#include "GameManager.h"
#include "UIManager.h"

static GameManager* pGameManager = NULL;

GameManager::GameManager()
{
	//�ʱ�ȭ
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
	if (_player != NULL) {
		return _player->getState();
	}
	return NONE;
}

bool GameManager::setState(player_Move_enum state)
{
	if (_player != NULL) {
		return _player->setState(state);
	}//state�� ����� ������ true ��ȯ
	return false;
}
