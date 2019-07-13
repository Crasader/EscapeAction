#include "GameManager.h"
#include "UIManager.h"

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
	if (_player != NULL) {
		return _player->getState();
	}
	return NONE;
}

bool GameManager::setState(player_Move_enum state)
{
	if (_player != NULL) {
		return _player->setState(state);
	}//state가 제대로 들어갔을때 true 반환
	return false;
}

void GameManager::playerEndLoopAni()
{
	_player->ani_pause();
}

int GameManager::getPlayerRoomNum()
{
	if (_player != NULL) {
		return _player->getRoomNum();
	}
	return NULL;
}

void GameManager::setPlayerRoomNum(int num)
{
	if (_player != NULL) {
		_player->setRoomNum(num);
	}
}

Rect GameManager::getPlayerRect()
{
	if (_player != NULL) {
		return _player->getRect();
	}
	return Rect::ZERO;
}

int GameManager::getPlayerFloor()
{
	if (_player != NULL) {
		return _player->getFloor();
	}
}

void GameManager::setPlayerFloor(int floor)
{
	if (_player != NULL) {
		_player->setFloor(floor);
	}
}

float GameManager::getPlayerPositionX()
{
	if (_player != NULL) {
		return _player->getPlayerSprPositionX();
	}
	return NULL;
}

void GameManager::setPlayerPositionX(float posX)
{
	if (_player != NULL) {
		_player->setPlayerSprPositionX(posX);
	}
}

void GameManager::setContactDoorWithPlayer(Sprite * doorSpr)
{
	if (_player != NULL) {
		_player->setContactDoorSpr(doorSpr);
	}
}