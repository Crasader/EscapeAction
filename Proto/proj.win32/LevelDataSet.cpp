#include "LevelDataSet.h"

bool LevelDataSet::init()
{
	//초기화
	testLevel = 5;
	int bal = (int)((float)testLevel *0.2);//밸런스를 위함
	fl_maxRm = 3+bal;//한 층에 올 수 있는 최대 방갯수 = 5
	fl_maxWl = fl_maxRm * 5;//한 층에 올 수 있는 최대 벽갯수, 최대 방갯수*가구 total크기 최댓값
	fl_minRm = 2+bal;// 한 층에 올 수 있는 최소 방갯수 = 2(마지막 층 제외)
	//Document 초기화
	draw_wall = NULL;

	//데이터 세팅
	setRoomCnt(testLevel);
	setWallData();
	//setData();

	return true;
}

LevelDataSet::~LevelDataSet()
{
	delete[] floor_rm;
	delete[] escRmfl;
	delete[] escRmNum;
}

void LevelDataSet::setRoomCnt(int level)
{
	//방 갯수
	const int rmCnt = (level * 2) + 2;//1레벨 올라갈때마다 방+2, 1Level : 4개, 2Level: 6개...
	
	//보너스 방, 일단 스킵
	//int bonus_rmCnt = RandomHelper::random_int((int)rmCnt / 3, (int)rmCnt / 2);

	//탈출 방 갯수 :: 방갯수 10마다 탈출 방 +1
	const int escRmCnt = (int)(rmCnt / 10)+1;

	//층수 설정
	int minfl = (int)(rmCnt / fl_maxRm);//올림, 최소 층
	if (rmCnt % fl_maxRm != 0) {
		minfl++;
	}
	int maxfl = (int)(rmCnt / fl_minRm);//내림. 최대 층
	int floor = RandomHelper::random_int(minfl, maxfl);

	//층수 당 방 갯수 설정
	floor_rm = new int[floor];
	int noSet_rmCnt = rmCnt;//세팅 안된 방 갯수
	for (int i = 0; i < floor-1; i++) {
		int max = noSet_rmCnt - ((floor - i - 2) * fl_minRm + 1);//현재 층에 들어갈 수 있는 최대 방 갯수
		max = max > fl_maxRm ? fl_maxRm : max;
		int min = noSet_rmCnt - ((floor - i - 1)*fl_maxRm);
		min = min < fl_minRm ? fl_minRm : min;
		floor_rm[i] = RandomHelper::random_int(min, max);
		noSet_rmCnt -= floor_rm[i];
	}
	floor_rm[floor - 1] = noSet_rmCnt;//마지막 층은 남은 방갯수로 설정
	
	//탈출방 설정
	escRmfl = new int[escRmCnt];
	escRmNum = new int[escRmCnt];
	int rm_dis = rmCnt / escRmCnt;
	for (int i = 0; i < escRmCnt; i++) {
		int min = rm_dis * i;
		int max;
		if (i == escRmCnt - 1) {//마지막 for문 일때
			max = rmCnt-1;
		}
		else {
			max = rm_dis * (i + 1);
		}
		int esc_rm = RandomHelper::random_int(min,max);
		int flRm = 0;
		for (int j = 0; j < floor; j++) {
			int pre_flRm = flRm;
			flRm += floor_rm[j];
			if (esc_rm < flRm) {
				escRmfl[i] = j;//층수 대입
				escRmNum[i] = esc_rm - pre_flRm;//해당 층에 번호 대입
				break;
			}
		}
	}
}
/*
void LevelDataSet::setData()
{
	Document draw_struct;
	Document draw_wall;
	Document draw_fur;
	Document draw_door;
	Document draw_deco;

	Document trans_door;
	Document item;

	//draw_wall 구조 설정
	Document::AllocatorType& dw_a = draw_wall.GetAllocator();
	draw_wall.SetArray();
	//draw_fur 구조 설정
	Document::AllocatorType& df_a = draw_fur.GetAllocator();
	draw_fur.SetArray();
	//draw_struct 구조 설정
	draw_struct.SetArray();
	Document::AllocatorType& ds_a = draw_struct.GetAllocator();
	//draw_deco 구조 설정
	draw_deco.SetArray();
	Document::AllocatorType& dc_a = draw_deco.GetAllocator();
	//trans_door 구조 설정
	trans_door.SetArray();
	Document::AllocatorType& td_a = trans_door.GetAllocator();
	//데이터 세팅
	int floor = _msize(floor_rm) / sizeof(int);//층수
	int flStartPos = 0;
	int preStartPos = 3;
	int preEndPos = 0;
	int roomNum = 0;
	log("floor %d", floor);
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
		
		//한 층에 해당하는 구조
		rapidjson::Value ds_fl(kObjectType);
		if (preStartPos > startPos) {
			flStartPos = startPos;
		}
		else {
			flStartPos = preStartPos;
		}
		ds_fl.AddMember("startPos", rapidjson::Value().SetInt(flStartPos), ds_a);
		preStartPos = startPos;
		
		rapidjson::Value ds_door(kArrayType);
		rapidjson::Value ds_wall(kArrayType);
		rapidjson::Value ds_flDoor(kArrayType);
		int flDoorCnt = floor_rm[fl] / 2;
		flDoorCnt = floor_rm[fl] % 2 != 0 ? flDoorCnt + 1 : flDoorCnt;//올림

		ds_wall.PushBack(rapidjson::Value().SetInt(startPos), ds_a);//바깥쪽 벽

		//데코레이션 set
		rapidjson::Value dc_fl(kArrayType);//한 층에 해당하는 장식물 "name", "pos"
		vector<const char*> v_dc;
		v_dc.clear();

		//한 층에 해당하는 문
		rapidjson::Value td_fl(kArrayType);

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
			//가구 배치&데코 배치
			int backPos = startPos;//이전 가구의 끝 위치
			int noSet_fur = furni_name->getTotalFntSize();//배치해야할 총 가구 크기
			for (auto v : furni_name->v_FntData) {
				rapidjson::Value df_fur(kObjectType);
				log("fl : %d rm : %d v_FntData : %d", fl, floor_rm[fl], furni_name->v_FntData.size());
				int frontPos = RandomHelper::random_int(backPos +1, startPos+rmSize-noSet_fur+1);//가구의 앞 위치
				/*-----------------(deco set)------------------------*/
				//backPos : 이전 가구의 뒤 위치, frontPos : 현재 가구의 앞 
				
/*				int blank = frontPos - backPos;//여백 크기
				for (int bp = 1; bp < blank; bp++) {
					if (RandomHelper::random_int(0, 1) == 0) {
						rapidjson::Value dc_deco(kObjectType);
						RandomDeco* deco_name = RandomDeco::create();
						if (deco_name->getDecoCount() == v_dc.size()) {
							break;
						}
						//장식물이 겹치지 않도록 조치
					    Vector<const char*>::iterator iter;
						for (iter = v_dc.begin(); iter != v_dc.end();++iter) {
							if (*iter == deco_name->getDecoName().c_str()) {
								deco_name->randDecoAgain();
								iter = v_dc.begin();
							}
						}
						dc_deco.AddMember("pos", rapidjson::Value().SetInt(backPos + bp),dc_a);
						dc_deco.AddMember("name", rapidjson::Value().SetString(deco_name->getDecoName().c_str(), dc_a), dc_a);
						v_dc.push_back(deco_name->getDecoName().c_str());
						dc_fl.PushBack(dc_deco, dc_a);

					}
				}
				/*------------------(/deco set)-----------------------*/
/*				backPos = frontPos + v->fnt_size - 1; 
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
			if (rm == floor_rm[fl] - 1) {
				//해당 층의 마지막 방
			}
			else {
				ds_door.PushBack(rapidjson::Value().SetInt(startPos), ds_a);
				rapidjson::Value td_door(kObjectType);
				td_door.AddMember("lock", rapidjson::Value().SetBool(true), td_a);
				td_door.AddMember("leftRoom", rapidjson::Value().SetInt(roomNum), td_a);
				td_door.AddMember("rightRoom", rapidjson::Value().SetInt(roomNum + 1), td_a);
				td_door.AddMember("pos", rapidjson::Value().SetInt(startPos), td_a);
				td_fl.PushBack(td_door, td_a);
			}
			
			//방번호 up
			roomNum++;
		}

		draw_fur.PushBack(df_fl,df_a);

		draw_wall.PushBack(dw_fl, dw_a);

		if (preEndPos < startPos) {
			ds_fl.AddMember("count", rapidjson::Value().SetInt(startPos - flStartPos), ds_a);//한 층 너비 구하기 위함
		}
		else {
			ds_fl.AddMember("count", rapidjson::Value().SetInt(preEndPos - flStartPos), ds_a);//한 층 너비 구하기 위함
		}
		ds_wall.PushBack(rapidjson::Value().SetInt(startPos), ds_a);//바깥쪽 벽
		preEndPos = startPos;

		ds_fl.AddMember("wall", ds_wall, ds_a);
		ds_fl.AddMember("door", ds_door, ds_a);
		draw_struct.PushBack(ds_fl, ds_a);

		draw_deco.PushBack(dc_fl, dc_a);

		//문 array
		trans_door.PushBack(td_fl, td_a);
	}
	rapidjson::Value ds_top(kObjectType);
	ds_top.AddMember("startPos", rapidjson::Value().SetInt(preStartPos), ds_a);
	ds_top.AddMember("count", rapidjson::Value().SetInt(preEndPos - preStartPos), ds_a);
	ds_top.AddMember("wall", rapidjson::Value().SetArray(), ds_a);
	ds_top.AddMember("door", rapidjson::Value().SetArray(), ds_a);
	draw_struct.PushBack(ds_top, ds_a);

	//벽 그리기 데이터 파일 쓰기
	FILE* fp = fopen("jsonData/draw/drawWall.json", "wb");
	char writeBuffer[5000];
	FileWriteStream wall_os(fp, writeBuffer, sizeof(writeBuffer));
	Writer<FileWriteStream> wall_writer(wall_os);
	draw_wall.Accept(wall_writer);
	fclose(fp);

	//가구 그리기 데이터 파일 쓰기
	strcat(writeBuffer, "");//버퍼 비우기
	fp = fopen("jsonData/draw/drawFur.json", "wb");
	FileWriteStream fur_os(fp, writeBuffer, sizeof(writeBuffer));
	Writer<FileWriteStream> fur_writer(fur_os);
	draw_fur.Accept(fur_writer);
	fclose(fp);

	//구조 그리기 데이터 파일 쓰기
	strcat(writeBuffer, "");//버퍼 비우기
	fp = fopen("jsonData/draw/drawStruct.json", "wb");
	FileWriteStream sct_os(fp, writeBuffer, sizeof(writeBuffer));
	Writer<FileWriteStream> sct_writer(sct_os);
	draw_struct.Accept(sct_writer);
	fclose(fp);

	//장식 그리기 데이터 파일 쓰기
	strcat(writeBuffer, "");//버퍼 비우기
	fp = fopen("jsonData/draw/drawDeco.json", "wb");
	FileWriteStream deco_os(fp, writeBuffer, sizeof(writeBuffer));
	Writer<FileWriteStream> deco_writer(deco_os);
	draw_deco.Accept(deco_writer);
	fclose(fp);

	//문  데이터 파일 쓰기
	strcat(writeBuffer, "");//버퍼 비우기
	fp = fopen("jsonData/trans/transDoor.json", "wb");
	FileWriteStream door_os(fp, writeBuffer, sizeof(writeBuffer));
	Writer<FileWriteStream> door_writer(door_os);
	trans_door.Accept(door_writer);
	fclose(fp);
}
*/

void LevelDataSet::setWallData()
{
	/*데이터 구조
	draw_wall[floor][rm]{	"tile" : [타일 이름::String],
		   					"pos" : 첫 지점	위치::Int,
                            "size" : 방 크기::Int
							"esc" : 탈출방 여부::Bool  }
	*/

	Document::AllocatorType& dw_a = draw_wall.GetAllocator();
	draw_wall.SetArray();

	int floor = _msize(floor_rm) / sizeof(int);//층수
	int escRnCnt = _msize(escRmfl) / sizeof(int);//탈출 방 갯수
	int noset_escR = 0;//세팅 안한 탈출 방

	for (int fl = 0; fl < floor; fl++) {
		//층의 앞부분 위치 차이를 위해
		int startPos = 0;
		int startPos_dis = 2;
		if (floor_rm[fl] == fl_maxRm) {//방 갯수가 최대면 앞부분이 앞으로 튀어나오게
			startPos = RandomHelper::random_int(0, startPos_dis) - startPos_dis;
		}
		else if (floor_rm[fl] == fl_minRm) {//방 갯수가 최소면 앞부분이 뒤로 들어가게
			startPos = RandomHelper::random_int(0, startPos_dis);
		}
		else {
			startPos = RandomHelper::random_int(0, startPos_dis*2) - startPos_dis;
		}

		rapidjson::Value dw_fl(kArrayType);//한 층에서 각 방의 벽 arr

		for (int rm = 0; rm < floor_rm[fl]; rm++) {//각 방
									   
			//탈출방 세팅
			while (noset_escR < escRnCnt) {
				if (escRmfl[noset_escR] == fl&&escRmNum[noset_escR]==rm) {
					int escRm_size = 2;
					rapidjson::Value dw_esc(kObjectType);//탈출방 벽 정보

					rapidjson::Value dw_escTile(kArrayType);//"tile"
					rapidjson::Value dw_escPos(startPos);//"pos"
					rapidjson::Value dw_escSize(escRm_size);//"size"
					rapidjson::Value dw_escEsc(true);//"esc"

					dw_escTile.PushBack(rapidjson::Value().SetString("wall/Wallesc_edge.png",dw_a), dw_a);
					dw_escTile.PushBack(rapidjson::Value().SetString("wall/Wallesc.png", dw_a), dw_a);
					dw_escTile.PushBack(rapidjson::Value().SetString("wall/Wallesc_edge.png", dw_a), dw_a);

					dw_esc.AddMember("tile", dw_escTile, dw_a);
					dw_esc.AddMember("pos", dw_escPos, dw_a);
					dw_esc.AddMember("size", dw_escSize, dw_a);
					dw_esc.AddMember("esc", dw_escEsc, dw_a);

					dw_fl.PushBack(dw_esc, dw_a);

					startPos += escRm_size;
					noset_escR++;
				}
				else {
					break;
				}
			}
			
			//최소 벽 갯수
			int wl_min = fl_maxWl % floor_rm[fl] == 0 ? fl_maxWl / floor_rm[fl] : fl_maxWl / floor_rm[fl] + 1;
			int wl_max = (fl_maxWl / fl_minRm) + 1;
	
			//방 크기
			int rmSize = RandomHelper::random_int(wl_min, wl_min + 2);
			rmSize = rmSize > wl_max ? wl_max : rmSize;

			//Value set
			rapidjson::Value dw_rm(kObjectType);//한 방의 벽 정보

			rapidjson::Value dw_tile(kArrayType);//"tile"
			rapidjson::Value dw_pos(startPos);//"pos"
			rapidjson::Value dw_size(rmSize + 1);//"size"
			rapidjson::Value dw_esc(false);//"esc"

			//랜덤으로 벽 받아오기
			RandomWall* wall_name = RandomWall::create();
			
			//방의 왼쪽
			dw_tile.PushBack(rapidjson::Value().SetString((wall_name->getWallEdgeName()).c_str(), dw_a), dw_a);
			//방 중앙부 
			for (int setwall = 0; setwall < rmSize; setwall++) {
				dw_tile.PushBack(rapidjson::Value().SetString((wall_name->getWallName()).c_str(), dw_a), dw_a);
			}
			//방 오른쪽
			dw_tile.PushBack(rapidjson::Value().SetString((wall_name->getWallEdgeName()).c_str(), dw_a), dw_a);

			dw_rm.AddMember("tile", dw_tile, dw_a);
			dw_rm.AddMember("pos", dw_pos, dw_a);
			dw_rm.AddMember("size", dw_size, dw_a);
			dw_rm.AddMember("esc", dw_esc, dw_a);

			dw_fl.PushBack(dw_rm, dw_a);

			startPos += rmSize + 1;
		}
	}

	//벽 그리기 데이터 파일 쓰기
	FILE* fp = fopen("jsonData/draw/drawWall.json", "wb");
	char writeBuffer[5000];
	FileWriteStream wall_os(fp, writeBuffer, sizeof(writeBuffer));
	Writer<FileWriteStream> wall_writer(wall_os);
	draw_wall.Accept(wall_writer);
	fclose(fp);
}