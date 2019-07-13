#pragma once
#include "cocos2d.h"
#include "UIManager.h"
#include "../proj.win32/Enum_collection.h"
#include "SimpleAudioEngine.h"

#include "../proj.win32/ShadowLayer.h"
USING_NS_CC;
using namespace CocosDenshion;

class player:public Node
{
public:

	CREATE_FUNC(player);
	~player();
	virtual bool init();

	UIManager* _UIM;

	bool all_stop;
	bool src_check;
	bool atk_check;

	void ani_pause();
	void ani_move();

	bool RL_filp;

	int atk_ran;
	void make_atk_ani();
	
	void Joy_move_check(float _firstPos, float _lastPos);
	
	
	//테스트
	virtual void onPress(EventKeyboard::KeyCode key);
	virtual void onRelease(EventKeyboard::KeyCode key);	

	Camera* _camera;
	void checkFur();
	bool getCheckFur();

	//void afterImage(float dt);'

	//가구서치시 애니메이션 설정<<이거 안해도 됨
	void set_RL_filp(bool RL);
	bool get_RL_filp();

	/*GAME MANAGER에서 사용하는 함수*/
	//방관련
	//player가 위치한 방 번호 받아오기
	int getRoomNum();
	//player 방 번호 setting
	void setRoomNum(int roomNum);
	//위치한 층
	int getFloor();
	void setFloor(int floor);
	//플레이어 State 관련
	player_Move_enum getState();
	bool setState(player_Move_enum state);//세팅 성공시 true 반환
	float getPlayerSprPositionX();
	void setPlayerSprPositionX(float posX);
	//인접한 문 스프라이트 주소 받아오기
	void setContactDoorSpr(Sprite* contactDoor);
	//충돌 체크 관련
	Rect getRect();

private : 

	ShadowLayer* _shadowLayer;
	Rect _playerRect;

	bool keyUp, keyDown, keyLeft, keyRight;
	int speed;
	float delayAfterimg;
	bool oncheck;
	bool check_fur;
	Size win_size;
	Size plyer_size;
	Rect rc;

	Sprite* _player;
	Vec2 player_animetion_move;
	int player_fs_move;
	
	Animate* _player_animat;
	Animation* _player_anime;

	Animate* _player_UD_animat;
	Animation* _player_UD_anime;

	Animate* _player_E_animat;
	Animation* _player_E_anime;

	RepeatForever* rep_player;

	Spawn* p_f_atk;

	player_Move_enum playerState;

	//player가 현재 위치한 방 번호
	int _roomNum;
	int _floor;//위치한 층
	//빛 크기
	float lightSize;
	//인접한 방문 스프라이트 주소
	Sprite* _door;

	//함수
	void returnDoorTexture();

};

