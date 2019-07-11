#include "RandomDeco.h"
#include "DataManager.h"


bool RandomDeco::init(int cnt)
{
	int resCnt = DataManager::getInstance()->getDecoData()->GetArray().Size();
	for (int i = 0; i < resCnt; i++) {
		deco_res.push_back(i);
	}
	//cnt = ����
	cnt = cnt > resCnt ? resCnt : cnt;//��ü ���ҽ� �������� cnt�� ���� ���
	_cnt = cnt;
	for (int i = 0; i < cnt; i++) {
		int max = deco_res.size() - 1;
		int index = RandomHelper::random_int(0, max);
		int rand_res = deco_res.at(index);
		deco_res.erase(deco_res.begin() + index);//������ ����
		deco_name.push_back(DataManager::getInstance()->getDecoData()->GetArray()[rand_res].GetString());
	}
	return true;

}

RandomDeco::~RandomDeco()
{
}

string RandomDeco::getDecoName(int index)
{
	return deco_name.at(index);
}

int RandomDeco::getDecoCnt()
{
	return _cnt;
}

RandomDeco * RandomDeco::create(int cnt)
{
	RandomDeco* deco = new(std::nothrow) RandomDeco();
	if (deco&&deco->init(cnt)) {
		deco->autorelease();
		return deco;
	}
	CC_SAFE_DELETE(deco);
	return nullptr;
}

bool RandomDeco::init()
{
	return false;
}
