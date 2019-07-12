#pragma once
#include "external/json/document.h"
#include "external/json/filereadstream.h"//파일을 열어오기위함
#include <cstdio>
#include "cocos2d.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
using namespace std;
using namespace rapidjson;
class FurnitureUI:public Node
{
public:
	CREATE_FUNC(FurnitureUI);
	virtual bool init();
	void setBtnVisible(int num, bool setbool);
	bool checkSearch();//탐색중인지 확인
	float getPos();//서치 중일시 위치 받아오기
	void setStart();
	void setCancle();//캐릭터 이동시 탐색 중지
	~FurnitureUI();
private:
	Vector<ui::Button*> v_btn;
	Vector<ProgressTimer*> v_pro;
	int check_furNum;//체크중인 가구 번호, -1이면 체크 x
	bool startSearch;
	//함수
	void clickBtn(int num);
	void schedule_clickBtn(float dt);

};

