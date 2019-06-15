#include "LayerUI.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;


bool LayerUI::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

	// �÷��̾� ���� start
	bool player_move::init()

	{
		if (!Layer::init()) //�ʿ����� ��Ȯ�� �𸣰��� Ȯ���ؾ��� ����
		{
			return false;
		}

		win_size = Director::getInstance()->getWinSize();
		
		player = Sprite::create("player.png"); //�÷��̾� ��������Ʈ
		player->setPosition(Point(win_size.width * 0.5, win_size.height * 0.5)); // ������ġ�� ����� ���� ����, ���� ���Ա��� ������ ���� �����ؾ���
		this->addChild(player);

		auto keyboard_lis = EventListenerKeyboard::create();
		keyboard_lis->onKeyPressed = CC_CALLBACK_1(player_move::onPress, this);
		keyboard_lis->onKeyReleased = CC_CALLBACK_1(player_move::onRelease, this);
		Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboard_lis, this);
																		// withscene�� �ƴ϶� �ٸ��� ����ؾ� �ҵ�
		this->schedule(schedule_selector(player_move::Check_Player));

		return true;
	}

	void player_move::onPress(EventKeyboard::KeyCode code)
	{
		switch (code)
		{
		case cocos2d::EventKeyboard::KeyCode::KEY_A:
			this->schedule(schedule_selector(player_move::Move_L), 0.005);
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_D:
			this->schedule(schedule_selector(player_move::Move_R), 0.005);
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_S:
			this->schedule(schedule_selector(player_move::Move_D), 0.005);
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_W:
			this->schedule(schedule_selector(player_move::Move_U), 0.005);
			break;
		default:
			break;
		}
	}

	void player_move::onRelease(EventKeyboard::KeyCode code)
	{
		switch (code)
		{
		case cocos2d::EventKeyboard::KeyCode::KEY_A:
			this->unschedule(schedule_selector(player_move::Move_L));
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_D:
			this->unschedule(schedule_selector(player_move::Move_R));
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_S:
			this->unschedule(schedule_selector(player_move::Move_D));
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_W:
			this->unschedule(schedule_selector(player_move::Move_U));
			break;
		default:
			break;
		}
	}

	void player_move::Move_R(float dt)
	{
		if (player->getPosition().x + player->getContentSize().width * 0.5 >= win_size.width) //ȭ�� �ȳ�����
			return;
		Point temp_pos = Point(player->getPosition().x + 1, player->getPosition().y);
		player->setPosition(temp_pos);
	}

	void player_move::Move_L(float dt)
	{
		if (player->getPosition().x - player->getContentSize().width * 0.5 <= 0) //ȭ�� �ȳ�����
			return;
		Point temp_pos = Point(player->getPosition().x - 1, player->getPosition().y);
		player->setPosition(temp_pos);
	}

	void player_move::Move_U(float dt)
	{
		if (player->getPosition().y + player->getContentSize().height * 0.5 >= win_size.height) //ȭ�� �ȳ�����
			return;
		Point temp_pos = Point(player->getPosition().x, player->getPosition().y + 1);
		player->setPosition(temp_pos);
	}

	void player_move::Move_D(float dt)
	{
		if (player->getPosition().y - player->getContentSize().height * 0.5 <= 0) //ȭ�� �ȳ�����
			return;
		Point temp_pos = Point(player->getPosition().x, player->getPosition().y - 1);
		player->setPosition(temp_pos);
	}
	//�÷��̾� ���� end
    return true;

}
