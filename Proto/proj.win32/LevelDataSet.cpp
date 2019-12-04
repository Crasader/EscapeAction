#include "LevelDataSet.h"

bool LevelDataSet::init()
{
	//초기화
	testLevel = 5;
	int bal = (int)((float)testLevel *0.2);//밸런스를 위함
	fl_maxRm = 3+bal;//한 층에 올 수 있는 최대 방갯수 = 5
	fl_maxWl = fl_maxRm * 6;//한 층에 올 수 있는 최대 벽갯수, 최대 방갯수*가구 total크기 최댓값
	fl_minRm = 2+bal;// 한 층에 올 수 있는 최소 방갯수 = 2(마지막 층 제외)
	//Document 초기화
	draw_wall = NULL;

	//데이터 세팅
	setRoomCnt(testLevel);
	setWallData();
	setDoorData();
	setLadderData();
	setFurData();
	setStructData();
	setDecoData();
	setItemData();
	setDefaultInfo();

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

	const int floor = _msize(floor_rm) / sizeof(int);//층수
	const int escRnCnt = _msize(escRmfl) / sizeof(int);//탈출 방 갯수
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
		draw_wall.PushBack(dw_fl, dw_a);
	}
	//층당 방 갯수에 esc rm 갯수 더하기
	for (int i = 0; i < escRnCnt; i++) {
		floor_rm[escRmfl[i]]++;
	}
	//벽 그리기 데이터 파일 쓰기
	strcat(writeBuffer, "");
	fp = fopen("jsonData/draw/drawWall.json", "wb");
	FileWriteStream wall_os(fp, writeBuffer, sizeof(writeBuffer));
	Writer<FileWriteStream> wall_writer(wall_os);
	draw_wall.Accept(wall_writer);
	fclose(fp);
}

void LevelDataSet::setDoorData()
{
	/*데이터 구조
	trans_door[fl][door]{  "pos" : 중앙지점 위치::Int,		
						   "lock" : 잠김 여부::Bool,
						   "esc" : 탈출방으로 향하는 문 여부 :: Bool,
						   "left" : 왼쪽 방 번호:: Int,
						   "right" : 오른쪽 방번호:: Int,
						   "hp" : 문의 hp ::Int
					 }
	*/
	Document::AllocatorType& td_a = trans_door.GetAllocator();
	trans_door.SetArray();

	int roomNum = 0;

	for (auto& fl : draw_wall.GetArray()) {
		rapidjson::Value td_fl(kArrayType);
		bool firstCheck = true;//첫번째 방인지 체크
		bool check_esc = false;//이전 방이 탈출방으로 향하는 문인지 체크
		for (auto& rm : fl.GetArray()) {
			if (!firstCheck) {
				rapidjson::Value td_door(kObjectType);

				td_door.AddMember("pos", rapidjson::Value().SetInt(rm["pos"].GetInt()), td_a);
				td_door.AddMember("lock", true, td_a);
				td_door.AddMember("left", roomNum - 1, td_a);
				td_door.AddMember("right", roomNum, td_a);
				td_door.AddMember("esc", check_esc||rm["esc"].GetBool()?true:false , td_a);//이전 방 or 현재 방이 탈출방이면 true
				td_door.AddMember("hp", rapidjson::Value().SetInt(100), td_a);

				td_fl.PushBack(td_door, td_a);
			}
			check_esc = rm["esc"].GetBool();
			roomNum++;
			firstCheck = false;
		}
		trans_door.PushBack(td_fl, td_a);
	}

	//문  데이터 파일 쓰기
	strcat(writeBuffer, "");
	fp = fopen("jsonData/trans/transDoor.json", "wb");
	FileWriteStream door_os(fp, writeBuffer, sizeof(writeBuffer));
	Writer<FileWriteStream> door_writer(door_os);
	trans_door.Accept(door_writer);
	fclose(fp);
}

void LevelDataSet::setLadderData()
{
	/*데이터 구조
	trans_door[fl][ladder]{  "pos" : 중앙지점 위치::Int,
						     "up" : 위 방 번호:: Int,
						     "down" : 아래 방 번호:: Int,
						     "hp" : 문의 hp ::Int
						 }
	*/
	Document::AllocatorType& tl_a = trans_ladder.GetAllocator();
	trans_ladder.SetArray();

	int roomNum = 0;

	int floorCnt = draw_wall.GetArray().Size();//층수

	int floor = 0;//현재 층수
	int upRmNum = 0;//위층 첫 방 번호
	for (auto& fl : draw_wall.GetArray()) {
		rapidjson::Value tl_fl(kArrayType);
		if (floor == floorCnt - 1) {
			trans_ladder.PushBack(tl_fl, tl_a);
			break;//마지막 층이면 for문 stop
		}
		upRmNum += fl.GetArray().Size();
		bool haveLadder = false;//해당층에 사다리가 1개 이상 있는가?
		for (auto& rm : fl.GetArray()) {
			//현재 방이 탈출 방이면 사다리 만들지 않음
			if (rm["esc"].GetBool()) {
				roomNum++;
				continue;
			}
			int minNow = rm["pos"].GetInt();
			int maxNow = rm["size"].GetInt()+minNow;
			minNow++;
			maxNow--;
			//위층 방들
			int i = -1;
			for (auto& upRm : draw_wall[floor + 1].GetArray()) {
				i++;
				//위층 방이 탈출 방이라면 사다리 만들지 않음
				if (upRm["esc"].GetBool()) {
					continue;
				}
				int minSet = upRm["pos"].GetInt();
				int maxSet = upRm["size"].GetInt() + minSet;
				minSet++;
				maxSet--;
				//위치가 맞지 않는 경우
				if (minNow > maxSet) {//위층 방이 현재 방의 앞에 위치
					continue;
				}
				else if (maxNow < minSet) {//위층 방이 현재 방의 뒤에 위치
					break;
				}
				else {
					minSet = minNow > minSet ? minNow : minSet;
					maxSet = maxNow < maxSet ? maxNow : maxSet;
					if (haveLadder&&RandomHelper::random_int(0, 1) == 1) {
						break;
					}
					haveLadder = true;
					//ladder 세팅 가능
					int ladder_pos = RandomHelper::random_int(minSet, maxSet);
					rapidjson::Value tl_la(kObjectType);

					tl_la.AddMember("pos", ladder_pos, tl_a);
					tl_la.AddMember("up", upRmNum + i, tl_a);
					tl_la.AddMember("down", roomNum, tl_a);
					tl_la.AddMember("hp", 100, tl_a);

					tl_fl.PushBack(tl_la, tl_a);
					break;//한 방에 사다리 1개
				}

			}
			roomNum++;
		}
		trans_ladder.PushBack(tl_fl, tl_a);
		floor++;
	}

	//문  데이터 파일 쓰기
	strcat(writeBuffer, "");
	fp = fopen("jsonData/draw/drawLadder.json", "wb");
	FileWriteStream door_os(fp, writeBuffer, sizeof(writeBuffer));
	Writer<FileWriteStream> door_writer(door_os);
	trans_ladder.Accept(door_writer);
	fclose(fp);
}

void LevelDataSet::setFurData()
{
	/*데이터 구조
	draw_fur[floor][rm][fur]{"name" : 가구 이름::String,
							 "pos" : 중앙 지점 위치::Double,
							 "size" : 가구 크기::Int}
	*/
	Document::AllocatorType& df_a = draw_fur.GetAllocator();
	draw_fur.SetArray();

	Document::AllocatorType& cb_a = draw_fur.GetAllocator();
	check_blank.SetArray();//deco 넣을 공간 확인
	//사다리를 피해 가구 세팅
	int floor = 0;//현재 층
	int roomNum = 0;//전체 방에대한 방 번호
	for (auto& fl : draw_wall.GetArray()) {
		rapidjson::Value df_fl(kArrayType);//각 층의 가구
		rapidjson::Value cb_fl(kArrayType);//각 층의 blank
		for (auto& rm : fl.GetArray()) {
			rapidjson::Value df_rm(kArrayType);//각 방의 가구
			rapidjson::Value cb_rm(kArrayType);//각 방의 blank

			//탈출 방이면 가구 세팅 안함
			if (rm["esc"].GetBool()) {
				roomNum++;
				df_fl.PushBack(df_rm, df_a);
				cb_fl.PushBack(cb_rm, cb_a);
				continue;
			}

			int left = rm["size"].GetInt() - 1;
			int right = 0;
			bool have_ladder = false;
			int lad_pos = 0;
				for (auto& lad : trans_ladder[floor].GetArray()) {
					if (roomNum == lad["down"].GetInt()) {
						const int ladPos = lad["pos"].GetInt() - rm["pos"].GetInt();
						lad_pos = ladPos;
						right = left - ladPos;
						left = ladPos - 1;
						have_ladder = true;
						log("ladder %d", lad_pos);
						break;
					}
				}
			//가구 정보
			Furniture* furni_name = Furniture::create(left, right, have_ladder);
			int prePos = 1;
			for (auto v : furni_name->v_FntData) {
				rapidjson::Value df_fur(kObjectType);//각 가구
				df_fur.AddMember("name", rapidjson::Value().SetString((v->fnt_img).c_str(), df_a), df_a);
				float fur_pos = (float)v->pos + (float)(v->fnt_size - 1)*0.5f + (float)rm["pos"].GetInt();
				df_fur.AddMember("pos", fur_pos, df_a);
				df_fur.AddMember("size", v->fnt_size, df_a);
				df_rm.PushBack(df_fur, df_a);
				for (int pos = prePos; pos < v->pos; pos++) {
					if (pos != lad_pos) {
						cb_rm.PushBack(pos, cb_a);
					}
				}
				if (v->deco) {
					for (int pos = v->pos; pos < v->pos + v->fnt_size; pos++) {
						cb_rm.PushBack(pos, cb_a);
					}
				}
				prePos = v->pos + v->fnt_size;
			}
			int lastPos = rm["size"].GetInt();
			for (int pos = prePos; pos < lastPos; pos++) {
				if (pos != lad_pos) {
					cb_rm.PushBack(pos, cb_a);
				}
			}
			cb_fl.PushBack(cb_rm, cb_a);
			roomNum++;
			//room++;
			df_fl.PushBack(df_rm, df_a);
		}
		check_blank.PushBack(cb_fl, cb_a);

		draw_fur.PushBack(df_fl, df_a);
		floor++;
	}

	//가구 그리기 데이터 파일 쓰기
	strcat(writeBuffer, "");
	fp = fopen("jsonData/draw/drawFur.json", "wb");
	FileWriteStream fur_os(fp, writeBuffer, sizeof(writeBuffer));
	Writer<FileWriteStream> fur_writer(fur_os);
	draw_fur.Accept(fur_writer);
	fclose(fp);

}

void LevelDataSet::setStructData()
{
	/*데이터 구조
	draw_struct[floor]{	"startPos"  : 첫 위치::Int(Anchor 0.5,0),
						"lastPos" : 마지막 위치::Int(Anchor 0.5,0),
						"ladder" : [사다리 위치::Int],
						"door" : [문 위치 :: Int],
						"wall" : [벽 위치 :: Int]
						  }
	*/
	
	draw_struct.SetArray();
	Document::AllocatorType& ds_a = draw_struct.GetAllocator();

	//데이터 세팅
	int floor= 0;//현재 층
	int prePos = 3;//이전 층의 시작 점
	int prePos_l = -3;//이전 층의 끝 점
	for (auto& fl : draw_wall.GetArray()) {
		//한 층에 해당하는 구조
		rapidjson::Value ds_fl(kObjectType);
		//"startPos"
		const int startPos = fl[0]["pos"].GetInt() + 1;
		prePos = startPos > prePos ? prePos : startPos;
		ds_fl.AddMember("startPos", rapidjson::Value().SetInt(prePos), ds_a);
		prePos = startPos;
		//"lastPos"
		int frc = floor_rm[floor]-1;//해당 층의 마지막 방
		const int lastPos = fl[frc]["pos"].GetInt() + fl[frc]["size"].GetInt()-1;
		prePos_l = lastPos < prePos_l ? prePos_l : lastPos;
		ds_fl.AddMember("lastPos", rapidjson::Value().SetInt(prePos_l), ds_a);
		prePos_l = lastPos;
		//문 위치 세팅 "door"
		rapidjson::Value ds_door(kArrayType);
		for (auto& dor : trans_door[floor].GetArray()) {
			ds_door.PushBack(dor["pos"].GetInt(), ds_a);
		}
		ds_fl.AddMember("door", ds_door, ds_a);
		//사다리 위치 세팅 "ladder"
		rapidjson::Value ds_ladder(kArrayType);
		if (floor != 0) {
			for (auto& lad : trans_ladder[floor - 1].GetArray()) {
				ds_ladder.PushBack(lad["pos"].GetInt(), ds_a);
			}
		}
		ds_fl.AddMember("ladder", ds_ladder, ds_a);
		//벽 위치 세팅 "wall"
		rapidjson::Value ds_wall(kArrayType);
		ds_wall.PushBack(rapidjson::Value().SetInt(startPos -1), ds_a);
		ds_wall.PushBack(rapidjson::Value().SetInt(lastPos +1), ds_a);
		ds_fl.AddMember("wall", ds_wall, ds_a);

		draw_struct.PushBack(ds_fl, ds_a);
		floor++;
	}
	//상단 struct
	rapidjson::Value ds_top(kObjectType);
	ds_top.AddMember("startPos", prePos, ds_a);
	ds_top.AddMember("lastPos", prePos_l, ds_a);
	ds_top.AddMember("door", rapidjson::Value().SetArray(), ds_a);
	ds_top.AddMember("ladder", rapidjson::Value().SetArray(), ds_a);
	ds_top.AddMember("wall", rapidjson::Value().SetArray(), ds_a);
	draw_struct.PushBack(ds_top, ds_a);

	//구조  데이터 파일 쓰기
	strcat(writeBuffer, "");
	fp = fopen("jsonData/draw/drawStruct.json", "wb");
	FileWriteStream struct_os(fp, writeBuffer, sizeof(writeBuffer));
	Writer<FileWriteStream> struct_writer(struct_os);
	draw_struct.Accept(struct_writer);
	fclose(fp);
}

void LevelDataSet::setDecoData()
{
	/*데이터 구조
	draw_deco[floor][deco]{"name" : 가구 이름::String,
						   "pos" : 중앙 지점 위치::int}
	*/

	draw_deco.SetArray();
	Document::AllocatorType& dd_a = draw_deco.GetAllocator();
	
	int floor = 0;
	for (auto& fl : check_blank.GetArray()) {
		rapidjson::Value dd_fl(kArrayType);
		int room = 0;
		for (auto& rm : fl.GetArray()) {
			int startPos = draw_wall[floor][room]["pos"].GetInt();
			const int blank = rm.GetArray().Size();
			int min = (int)(blank*0.5);
			int cnt = RandomHelper::random_int(min, blank);
			RandomDeco* rand_deco = RandomDeco::create(cnt);
			int prePos = 0;
			cnt = rand_deco->getDecoCnt();
			for (int i = 0; i < cnt; i++) {
				rapidjson::Value dd_deco(kObjectType);
				//pos는 array 번호. 때문에 0~blank-1까지 존재
				int pos = RandomHelper::random_int(prePos, blank - cnt + i);
				dd_deco.AddMember("pos", rm[pos].GetInt()+ startPos, dd_a);
				dd_deco.AddMember("name"
					,rapidjson::Value().SetString(rand_deco->getDecoName(i).c_str(), dd_a), dd_a);
				prePos = pos + 1;
				dd_fl.PushBack(dd_deco, dd_a);
			}
			room++;
		}
		draw_deco.PushBack(dd_fl, dd_a);
		floor++;
	}

	//장식 그리기 데이터 파일 쓰기
	strcat(writeBuffer, "");
	fp = fopen("jsonData/draw/drawDeco.json", "wb");
	FileWriteStream deco_os(fp, writeBuffer, sizeof(writeBuffer));
	Writer<FileWriteStream> deco_writer(deco_os);
	draw_deco.Accept(deco_writer);
	fclose(fp);
	

}

void LevelDataSet::setItemData()
{
	/*데이터 구조
	trans_item[가구번호][아이템::int형 Array]
	*/
	trans_item.SetArray();
	Document::AllocatorType& ti_a = trans_item.GetAllocator();

	int fntCnt = 0; //총 가구 갯수
	for (auto& fl : draw_fur.GetArray()) {
		for (auto& rm : draw_fur.GetArray()) {
			fntCnt+=rm.GetArray().Size();
		}
	}
	log("fntCnt %d", fntCnt);
	//각 물품 갯수 결정
	int key = 0;//탈출 방 아닌 방문 갯수
	for (auto& fl : trans_door.GetArray()) {

	}
	//아이템 데이터 파일 쓰기
	strcat(writeBuffer, "");
	fp = fopen("jsonData/trans/transItem.json", "wb");
	FileWriteStream item_os(fp, writeBuffer, sizeof(writeBuffer));
	Writer<FileWriteStream> item_writer(item_os);
	draw_deco.Accept(item_writer);
	fclose(fp);

}

void LevelDataSet::setDefaultInfo()
{
	/*데이터 구조
	default_info{
		"startRoom" : [첫방 정보::int 형 Array],
	}*/
	default_Info.SetObject();
	Document::AllocatorType& dd_a = draw_deco.GetAllocator();
	
	//첫 방 정보

	//캐릭터 정보 데이터 파일 쓰기
	strcat(writeBuffer, "");
	fp = fopen("jsonData/DefaultInfo.json", "wb");
	FileWriteStream deco_os(fp, writeBuffer, sizeof(writeBuffer));
	Writer<FileWriteStream> deco_writer(deco_os);
	draw_deco.Accept(deco_writer);
	fclose(fp);
}
