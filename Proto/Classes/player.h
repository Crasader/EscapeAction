#pragma once
#include "cocos2d.h"
#include "UIManager.h"
#include "../proj.win32/Enum_collection.h"
#include "../proj.win32/AudioManager.h"

USING_NS_CC;

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
	
	void Joy_move_check();
	
	
	//�׽�Ʈ
	virtual void onPress(EventKeyboard::KeyCode key);
	virtual void onRelease(EventKeyboard::KeyCode key);	



	Camera* _camera;
	void checkFur();
	bool getCheckFur();

	void afterImage(float dt);

	//�����
	//player�� ��ġ�� �� ��ȣ �޾ƿ���
	int getRoomNum();
	//player �� ��ȣ setting
	void setRoomNum(int roomNum);
	void setFirst(float first);
	void setLast(float last);
	
	//�÷��̾� State ���� :: GameManager���� ����� ��
	player_Move_enum getState();
	bool setState(player_Move_enum state);//���� ������ true ��ȯ
	
	//���� ����
	Rect getRect();

	//������ġ�� �ִϸ��̼� ����
	void set_RL_filp(bool RL);
	bool get_RL_filp();

private : 
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

	//player�� ���� ��ġ�� �� ��ȣ
	int _roomNum;
	//�� ũ��
	float _firstPos;
	float _lastPos;

};

