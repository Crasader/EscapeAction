#include "LevelDataSet.h"

bool LevelDataSet::init()
{
	testLevel = 5;
	setRoomCnt(testLevel);
	setData();

	return true;
}

LevelDataSet::~LevelDataSet()
{
}

void LevelDataSet::setRoomCnt(int level)
{
	//방 갯수
	int rmCnt = (level * 2) + 2;//1레벨 올라갈때마다 방+2, 1Level : 4개, 2Level: 6개...

	//보너스 방
	int bonus_rmCnt = RandomHelper::random_int((int)rmCnt / 3, (int)rmCnt / 2);

	//층수 설정
	fl_maxRm = 3;//한 층에 올 수 있는 최대 방갯수 = 5
	fl_maxWl = fl_maxRm * 5;//한 층에 올 수 있는 최대 벽갯수, 최대 방갯수*가구 total크기 최댓값
	fl_minRm = 2;// 한 층에 올 수 있는 최소 방갯수 = 2(마지막 층 제외)
	int minfl = (int)(rmCnt / fl_maxRm);//올림, 최소 층
	if (rmCnt % fl_maxRm != 0) {
		minfl++;
	}
	int maxfl = (int)(rmCnt / fl_minRm);//내림. 최대 층
	int floor = RandomHelper::random_int(minfl, maxfl);
	log("floor : %d", floor);
	//층수 당 방 갯수 설정
	floor_rm = new int[floor];
	int noSet_rmCnt = rmCnt;//세팅 안된 방 갯수
	for (int i = 0; i < floor; i++) {
		int max = noSet_rmCnt - ((floor - i - 2) * fl_minRm - 1);//현재 층에 들어갈 수 있는 최대 방 갯수
		max = max > fl_maxRm ? fl_maxRm : max;
		int min = noSet_rmCnt / (floor - i) > fl_minRm ? noSet_rmCnt / (floor - i) : fl_minRm;
		if (i==floor-1) {
			floor_rm[i] = noSet_rmCnt;
		}
		else {
			floor_rm[i] = RandomHelper::random_int(min, max);
		}
		noSet_rmCnt -= floor_rm[i];
		log("floor_rm : %d", floor_rm[i]);
	}
	//delete[] floor_rm;
}

void LevelDataSet::setData()
{
	Document draw_struct;
	Document draw_wall;
	Document draw_fur;
	Document draw_door;

	Document trans_door;
	Document item;


	//draw_wall 구조 설정
	Document::AllocatorType& dw_a = draw_wall.GetAllocator();
	draw_wall.SetArray();
	//draw_fur 구조 설정
	Document::AllocatorType& df_a = draw_fur.GetAllocator();
	draw_fur.SetArray();

	//데이터 세팅
	int floor = _msize(floor_rm) / sizeof(int);//층수
	for (int fl = 0; fl < floor; fl++) {
		int startPos = 0;//층의 앞부분 위치 차이를 위해
		if (floor_rm[fl] == fl_maxRm) {
			startPos = RandomHelper::random_int(0, 2) - 2;
		}
		else if (floor_rm[fl] == fl_minRm) {
			startPos = RandomHelper::random_int(0, 2);
		}
		rapidjson::Value dw_fl(kArrayType);//한 층에 해당하는 벽 arr
		rapidjson::Value df_fl(kArrayType);//한 층에 해당하는 가구 arr
		for (int rm = 0; rm < floor_rm[fl]; rm++) {//각 방 생성
			//가구 정보
			Furniture* furni_name = Furniture::create();

			int wl_min = fl_maxWl % floor_rm[fl] == 0 ? fl_maxWl / floor_rm[fl] : fl_maxWl / floor_rm[fl] + 1;
			int wl_max = (fl_maxWl / fl_minRm)+1;
			
			//방 크기
			int rmSize = RandomHelper::random_int(wl_min, wl_min+2);
			rmSize = rmSize > wl_max ? wl_max : rmSize;

			//가구 데이터
			rapidjson::Value df_ecR(kArrayType);
			//가구 배치
			int backPos = startPos;//이전 가구의 끝 위치
			int noSet_fur = furni_name->getTotalFntSize();//배치해야할 총 가구 크기
			for (auto v : furni_name->v_FntData) {
				rapidjson::Value df_fur(kObjectType);
				log("fl : %d rm : %d v_FntData : %d", fl, floor_rm[fl], furni_name->v_FntData.size());
				int frontPos = RandomHelper::random_int(backPos +1, startPos+rmSize-noSet_fur+1);//가구의 앞 위치
				backPos = frontPos + v->fnt_size - 1; 
				noSet_fur -= v->fnt_size;
				float furPos = (float)frontPos + ((float)(v->fnt_size - 1) / 2.0);
				df_fur.AddMember("name", rapidjson::Value().SetString((v->fnt_img).c_str(), df_a), df_a);
				df_fur.AddMember("pos", rapidjson::Value().SetFloat(furPos), df_a);
				df_ecR.PushBack(df_fur, df_a);
			}
			df_fl.PushBack(df_ecR, df_a);
			
			//벽 정보
			RandomWall* wall_name = RandomWall::create();
			rapidjson::Value dw_ecR(kObjectType);
			rapidjson::Value dw_pos(startPos);
			//방 1개의 벽 resource Array
			rapidjson::Value dw_rm(kArrayType);
			//방의 왼쪽
			dw_rm.PushBack(rapidjson::Value().SetString((wall_name->getWallEdgeName()).c_str(), dw_a), dw_a);
			//방 중앙부 
			for (int setwall = 0; setwall < rmSize; setwall++) {
				dw_rm.PushBack(rapidjson::Value().SetString((wall_name->getWallName()).c_str(), dw_a), dw_a);
			}
			//방 오른쪽
			dw_rm.PushBack(rapidjson::Value().SetString((wall_name->getWallEdgeName()).c_str(), dw_a), dw_a);

			dw_ecR.AddMember("tile", dw_rm, dw_a);
			dw_ecR.AddMember("pos", dw_pos , dw_a);
			dw_fl.PushBack(dw_ecR, dw_a);
			startPos += rmSize + 1;
		}
		draw_fur.PushBack(df_fl,df_a);
		draw_wall.PushBack(dw_fl, dw_a);
		
	}
	//벽 그리기 데이터 파일 쓰기
	FILE* fp = fopen("jsonData/draw/drawWall.json", "wb");
	char writeBuffer[5000];
	FileWriteStream wall_os(fp, writeBuffer, sizeof(writeBuffer));
	Writer<FileWriteStream> wall_writer(wall_os);
	draw_wall.Accept(wall_writer);
	fclose(fp);

	//가구 그리기 데이터 파일 쓰기
	strcat(writeBuffer, "test");//버퍼 비우기
	fp = fopen("jsonData/draw/drawFur.json", "wb");
	FileWriteStream fur_os(fp, writeBuffer, sizeof(writeBuffer));
	Writer<FileWriteStream> fur_writer(fur_os);
	draw_fur.Accept(fur_writer);
	fclose(fp);

}
