#include "RandomDeco.h"



bool RandomDeco::init(int cnt)
{
	Document draw_deco;
	FILE* fp = fopen("jsonData/name/nameDeco.json", "rb");
	char readBuffer[5000];
	FileReadStream is(fp, readBuffer, sizeof(readBuffer));
	draw_deco.ParseStream(is);
	fclose(fp);

	int resCnt = draw_deco.GetArray().Size();
	for (int i = 0; i < resCnt; i++) {
		deco_res.push_back(i);
	}
	//cnt = 개수
	cnt = cnt > resCnt ? resCnt : cnt;//전체 리소스 개수보다 cnt가 적은 경우
	_cnt = cnt;
	for (int i = 0; i < cnt; i++) {
		int max = deco_res.size() - 1;
		int index = RandomHelper::random_int(0, max);
		int rand_res = deco_res.at(index);
		deco_res.erase(deco_res.begin() + index);//데이터 삭제
		deco_name.push_back(draw_deco[rand_res].GetString());
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
