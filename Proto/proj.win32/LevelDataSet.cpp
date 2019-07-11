#include "LevelDataSet.h"

bool LevelDataSet::init()
{
	//�ʱ�ȭ
	testLevel = 5;
	int bal = (int)((float)testLevel *0.2);//�뷱���� ����
	fl_maxRm = 3+bal;//�� ���� �� �� �ִ� �ִ� �氹�� = 5
	fl_maxWl = fl_maxRm * 6;//�� ���� �� �� �ִ� �ִ� ������, �ִ� �氹��*���� totalũ�� �ִ�
	fl_minRm = 2+bal;// �� ���� �� �� �ִ� �ּ� �氹�� = 2(������ �� ����)
	//Document �ʱ�ȭ
	draw_wall = NULL;

	//������ ����
	setRoomCnt(testLevel);
	setWallData();
	setDoorData();
	setLadderData();
	setFurData();
	setStructData();
	setDeco();

	return true;
}

LevelDataSet::~LevelDataSet()
{
	delete[] floor_rm;
	delete[] escRmfl;
	delete[] escRmNum;
	delete[] ladfl;
}

void LevelDataSet::setRoomCnt(int level)
{
	//�� ����
	const int rmCnt = (level * 2) + 2;//1���� �ö󰥶����� ��+2, 1Level : 4��, 2Level: 6��...
	
	//���ʽ� ��, �ϴ� ��ŵ
	//int bonus_rmCnt = RandomHelper::random_int((int)rmCnt / 3, (int)rmCnt / 2);

	//Ż�� �� ���� :: �氹�� 10���� Ż�� �� +1
	const int escRmCnt = (int)(rmCnt / 10)+1;

	//���� ����
	int minfl = (int)(rmCnt / fl_maxRm);//�ø�, �ּ� ��
	if (rmCnt % fl_maxRm != 0) {
		minfl++;
	}
	int maxfl = (int)(rmCnt / fl_minRm);//����. �ִ� ��
	int floor = RandomHelper::random_int(minfl, maxfl);

	//���� �� �� ���� ����
	floor_rm = new int[floor];
	int noSet_rmCnt = rmCnt;//���� �ȵ� �� ����
	for (int i = 0; i < floor-1; i++) {
		int max = noSet_rmCnt - ((floor - i - 2) * fl_minRm + 1);//���� ���� �� �� �ִ� �ִ� �� ����
		max = max > fl_maxRm ? fl_maxRm : max;
		int min = noSet_rmCnt - ((floor - i - 1)*fl_maxRm);
		min = min < fl_minRm ? fl_minRm : min;
		floor_rm[i] = RandomHelper::random_int(min, max);
		noSet_rmCnt -= floor_rm[i];
	}
	floor_rm[floor - 1] = noSet_rmCnt;//������ ���� ���� �氹���� ����
	
	//Ż��� ����
	escRmfl = new int[escRmCnt];
	escRmNum = new int[escRmCnt];
	escRm = new int[escRmCnt];
	int rm_dis = rmCnt / escRmCnt;

	for (int i = 0; i < escRmCnt; i++) {
		int min = rm_dis * i;
		int max;
		if (i == escRmCnt - 1) {//������ for�� �϶�
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
				escRmfl[i] = j;//���� ����
				escRmNum[i] = esc_rm - pre_flRm;//�ش� ���� ��ȣ ����
				escRm[i] = esc_rm + i;
				break;
			}
		}
	}
	//���� ��ٸ� ���� ���� �Ҵ�, �ʱ�ȭ
	ladfl = new int[floor];
	for (int i = 0; i < floor; i++) {
		ladfl[i] = 0;
	}
}

void LevelDataSet::setWallData()
{
	/*������ ����
	draw_wall[floor][rm]{	"tile" : [Ÿ�� �̸�::String],
		   					"pos" : ù ����	��ġ::Int,
                            "size" : �� ũ��::Int
							"esc" : Ż��� ����::Bool  }
	*/

	Document::AllocatorType& dw_a = draw_wall.GetAllocator();
	draw_wall.SetArray();

	const int floor = _msize(floor_rm) / sizeof(int);//����
	const int escRnCnt = _msize(escRmfl) / sizeof(int);//Ż�� �� ����
	int noset_escR = 0;//���� ���� Ż�� ��

	for (int fl = 0; fl < floor; fl++) {
		//���� �պκ� ��ġ ���̸� ����
		int startPos = 0;
		int startPos_dis = 2;
		if (floor_rm[fl] == fl_maxRm) {//�� ������ �ִ�� �պκ��� ������ Ƣ�����
			startPos = RandomHelper::random_int(0, startPos_dis) - startPos_dis;
		}
		else if (floor_rm[fl] == fl_minRm) {//�� ������ �ּҸ� �պκ��� �ڷ� ����
			startPos = RandomHelper::random_int(0, startPos_dis);
		}
		else {
			startPos = RandomHelper::random_int(0, startPos_dis*2) - startPos_dis;
		}

		rapidjson::Value dw_fl(kArrayType);//�� ������ �� ���� �� arr

		for (int rm = 0; rm < floor_rm[fl]; rm++) {//�� ��
									   
			//Ż��� ����
			while (noset_escR < escRnCnt) {
				if (escRmfl[noset_escR] == fl&&escRmNum[noset_escR]==rm) {
					int escRm_size = 2;
					rapidjson::Value dw_esc(kObjectType);//Ż��� �� ����

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
			
			//�ּ� �� ����
			int wl_min = fl_maxWl % floor_rm[fl] == 0 ? fl_maxWl / floor_rm[fl] : fl_maxWl / floor_rm[fl] + 1;
			int wl_max = (fl_maxWl / fl_minRm) + 1;
	
			//�� ũ��
			int rmSize = RandomHelper::random_int(wl_min, wl_min + 2);
			rmSize = rmSize > wl_max ? wl_max : rmSize;

			//Value set
			rapidjson::Value dw_rm(kObjectType);//�� ���� �� ����

			rapidjson::Value dw_tile(kArrayType);//"tile"
			rapidjson::Value dw_pos(startPos);//"pos"
			rapidjson::Value dw_size(rmSize + 1);//"size"
			rapidjson::Value dw_esc(false);//"esc"

			//�������� �� �޾ƿ���
			RandomWall* wall_name = RandomWall::create();
			
			//���� ����
			dw_tile.PushBack(rapidjson::Value().SetString((wall_name->getWallEdgeName()).c_str(), dw_a), dw_a);
			//�� �߾Ӻ� 
			for (int setwall = 0; setwall < rmSize; setwall++) {
				dw_tile.PushBack(rapidjson::Value().SetString((wall_name->getWallName()).c_str(), dw_a), dw_a);
			}
			//�� ������
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
	//���� �� ������ esc rm ���� ���ϱ�
	for (int i = 0; i < escRnCnt; i++) {
		floor_rm[escRmfl[i]]++;
	}
	//�� �׸��� ������ ���� ����
	strcat(writeBuffer, "");
	fp = fopen("jsonData/draw/drawWall.json", "wb");
	FileWriteStream wall_os(fp, writeBuffer, sizeof(writeBuffer));
	Writer<FileWriteStream> wall_writer(wall_os);
	draw_wall.Accept(wall_writer);
	fclose(fp);
}

void LevelDataSet::setDoorData()
{
	/*������ ����
	trans_door[fl][door]{  "pos" : �߾����� ��ġ::Int,		
						   "lock" : ��� ����::Bool,
						   "esc" : Ż������� ���ϴ� �� ���� :: Bool,
						   "left" : ���� �� ��ȣ:: Int,
						   "right" : ������ ���ȣ:: Int,
						   "hp" : ���� hp ::Int
					 }
	*/
	Document::AllocatorType& td_a = trans_door.GetAllocator();
	trans_door.SetArray();

	int roomNum = 0;

	for (auto& fl : draw_wall.GetArray()) {
		rapidjson::Value td_fl(kArrayType);
		bool firstCheck = true;//ù��° ������ üũ
		bool check_esc = false;//���� ���� Ż������� ���ϴ� ������ üũ
		for (auto& rm : fl.GetArray()) {
			if (!firstCheck) {
				rapidjson::Value td_door(kObjectType);

				td_door.AddMember("pos", rapidjson::Value().SetInt(rm["pos"].GetInt()), td_a);
				td_door.AddMember("lock", true, td_a);
				td_door.AddMember("left", roomNum - 1, td_a);
				td_door.AddMember("right", roomNum, td_a);
				td_door.AddMember("esc", check_esc||rm["esc"].GetBool()?true:false , td_a);//���� �� or ���� ���� Ż����̸� true
				td_door.AddMember("hp", rapidjson::Value().SetInt(100), td_a);

				td_fl.PushBack(td_door, td_a);
			}
			check_esc = rm["esc"].GetBool();
			roomNum++;
			firstCheck = false;
		}
		trans_door.PushBack(td_fl, td_a);
	}

	//��  ������ ���� ����
	strcat(writeBuffer, "");
	fp = fopen("jsonData/trans/transDoor.json", "wb");
	FileWriteStream door_os(fp, writeBuffer, sizeof(writeBuffer));
	Writer<FileWriteStream> door_writer(door_os);
	trans_door.Accept(door_writer);
	fclose(fp);
}

void LevelDataSet::setLadderData()
{
	/*������ ����
	trans_door[fl][ladder]{  "pos" : �߾����� ��ġ::Int,
						     "lock" : ��� ����::Bool,
						     "up" : �� �� ��ȣ:: Int,
						     "down" : �Ʒ� �� ��ȣ:: Int,
						     "hp" : ���� hp ::Int
						 }
	*/
	Document::AllocatorType& tl_a = trans_ladder.GetAllocator();
	trans_ladder.SetArray();

	int roomNum = 0;

	int floorCnt = draw_wall.GetArray().Size();//����

	int floor = 0;//���� ����
	int upRmNum = 0;//���� ù �� ��ȣ
	for (auto& fl : draw_wall.GetArray()) {
		rapidjson::Value tl_fl(kArrayType);
		if (floor == floorCnt - 1) {
			trans_ladder.PushBack(tl_fl, tl_a);
			break;//������ ���̸� for�� stop
		}
		upRmNum += fl.GetArray().Size();
		bool haveLadder = false;//�ش����� ��ٸ��� 1�� �̻� �ִ°�?
		for (auto& rm : fl.GetArray()) {
			//���� ���� Ż�� ���̸� ��ٸ� ������ ����
			if (rm["esc"].GetBool()) {
				continue;
			}
			int minNow = rm["pos"].GetInt();
			int maxNow = rm["size"].GetInt()+minNow;
			minNow++;
			maxNow--;
			//���� ���
			int i = -1;
			for (auto& upRm : draw_wall[floor + 1].GetArray()) {
				i++;
				//���� ���� Ż�� ���̶�� ��ٸ� ������ ����
				if (upRm["esc"].GetBool()) {
					continue;
				}
				int minSet = upRm["pos"].GetInt();
				int maxSet = upRm["size"].GetInt() + minSet;
				minSet++;
				maxSet--;
				//��ġ�� ���� �ʴ� ���
				if (minNow > maxSet) {//���� ���� ���� ���� �տ� ��ġ
					continue;
				}
				else if (maxNow < minSet) {//���� ���� ���� ���� �ڿ� ��ġ
					break;
				}
				else {
					minSet = minNow > minSet ? minNow : minSet;
					maxSet = maxNow < maxSet ? maxNow : maxSet;
					if (haveLadder&&RandomHelper::random_int(0, 1) == 1) {
						break;
					}
					haveLadder = true;
					//ladder ���� ����
					int ladder_pos = RandomHelper::random_int(minSet, maxSet);
					rapidjson::Value tl_la(kObjectType);

					tl_la.AddMember("pos", ladder_pos, tl_a);
					tl_la.AddMember("lock", true, tl_a);
					tl_la.AddMember("up", upRmNum + i, tl_a);
					tl_la.AddMember("down", roomNum, tl_a);
					tl_la.AddMember("hp", 100, tl_a);

					tl_fl.PushBack(tl_la, tl_a);
					break;//�� �濡 ��ٸ� 1��
				}

			}
			roomNum++;
		}
		trans_ladder.PushBack(tl_fl, tl_a);
		floor++;
	}

	//��  ������ ���� ����
	strcat(writeBuffer, "");
	fp = fopen("jsonData/trans/transLadder.json", "wb");
	FileWriteStream door_os(fp, writeBuffer, sizeof(writeBuffer));
	Writer<FileWriteStream> door_writer(door_os);
	trans_ladder.Accept(door_writer);
	fclose(fp);
}

void LevelDataSet::setFurData()
{
	/*������ ����
	draw_fur[floor][rm][fur]{"name" : ���� �̸�::String,
							 "pos" : �߾� ���� ��ġ::Double,
							 "size" : ���� ũ��::Int}
	*/
	Document::AllocatorType& df_a = draw_fur.GetAllocator();
	draw_fur.SetArray();

	Document::AllocatorType& cb_a = draw_fur.GetAllocator();
	check_blank.SetArray();//deco ���� ���� Ȯ��
	//��ٸ��� ���� ���� ����
	int floor = 0;//���� ��
	int roomNum = 0;//��ü �濡���� �� ��ȣ
	for (auto& fl : draw_wall.GetArray()) {
		rapidjson::Value df_fl(kArrayType);//�� ���� ����
		rapidjson::Value cb_fl(kArrayType);//�� ���� blank
		for (auto& rm : fl.GetArray()) {
			rapidjson::Value df_rm(kArrayType);//�� ���� ����
			rapidjson::Value cb_rm(kArrayType);//�� ���� blank

			//Ż�� ���̸� ���� ���� ����
			if (rm["esc"].GetBool()) {
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

			//���� ����
			Furniture* furni_name = Furniture::create(left, right, have_ladder);
			int prePos = 1;
			for (auto v : furni_name->v_FntData) {
				rapidjson::Value df_fur(kObjectType);//�� ����
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

	//���� �׸��� ������ ���� ����
	strcat(writeBuffer, "");
	fp = fopen("jsonData/draw/drawFur.json", "wb");
	FileWriteStream fur_os(fp, writeBuffer, sizeof(writeBuffer));
	Writer<FileWriteStream> fur_writer(fur_os);
	draw_fur.Accept(fur_writer);
	fclose(fp);

}

void LevelDataSet::setStructData()
{
	/*������ ����
	draw_struct[floor]{	"startPos"  : ù ��ġ::Int(Anchor 0.5,0),
						"lastPos" : ������ ��ġ::Int(Anchor 0.5,0),
						"ladder" : [��ٸ� ��ġ::Int],
						"door" : [�� ��ġ :: Int],
						"wall" : [�� ��ġ :: Int]
						  }
	*/
	
	draw_struct.SetArray();
	Document::AllocatorType& ds_a = draw_struct.GetAllocator();

	//������ ����
	int floor= 0;//���� ��
	int prePos = 3;//���� ���� ���� ��
	int prePos_l = -3;//���� ���� �� ��
	for (auto& fl : draw_wall.GetArray()) {
		//�� ���� �ش��ϴ� ����
		rapidjson::Value ds_fl(kObjectType);
		//"startPos"
		const int startPos = fl[0]["pos"].GetInt() + 1;
		prePos = startPos > prePos ? prePos : startPos;
		ds_fl.AddMember("startPos", rapidjson::Value().SetInt(prePos), ds_a);
		prePos = startPos;
		//"lastPos"
		int frc = floor_rm[floor]-1;//�ش� ���� ������ ��
		const int lastPos = fl[frc]["pos"].GetInt() + fl[frc]["size"].GetInt()-1;
		prePos_l = lastPos < prePos_l ? prePos_l : lastPos;
		ds_fl.AddMember("lastPos", rapidjson::Value().SetInt(prePos_l), ds_a);
		prePos_l = lastPos;
		//�� ��ġ ���� "door"
		rapidjson::Value ds_door(kArrayType);
		for (auto& dor : trans_door[floor].GetArray()) {
			ds_door.PushBack(dor["pos"].GetInt(), ds_a);
		}
		ds_fl.AddMember("door", ds_door, ds_a);
		//��ٸ� ��ġ ���� "ladder"
		rapidjson::Value ds_ladder(kArrayType);
		if (floor != 0) {
			for (auto& lad : trans_ladder[floor - 1].GetArray()) {
				ds_ladder.PushBack(lad["pos"].GetInt(), ds_a);
			}
		}
		ds_fl.AddMember("ladder", ds_ladder, ds_a);
		//�� ��ġ ���� "wall"
		rapidjson::Value ds_wall(kArrayType);
		ds_wall.PushBack(rapidjson::Value().SetInt(startPos -1), ds_a);
		ds_wall.PushBack(rapidjson::Value().SetInt(lastPos +1), ds_a);
		ds_fl.AddMember("wall", ds_wall, ds_a);

		draw_struct.PushBack(ds_fl, ds_a);
		floor++;
	}
	//��� struct
	rapidjson::Value ds_top(kObjectType);
	ds_top.AddMember("startPos", prePos, ds_a);
	ds_top.AddMember("lastPos", prePos_l, ds_a);
	ds_top.AddMember("door", rapidjson::Value().SetArray(), ds_a);
	ds_top.AddMember("ladder", rapidjson::Value().SetArray(), ds_a);
	ds_top.AddMember("wall", rapidjson::Value().SetArray(), ds_a);
	draw_struct.PushBack(ds_top, ds_a);

	//����  ������ ���� ����
	strcat(writeBuffer, "");
	fp = fopen("jsonData/draw/drawStruct.json", "wb");
	FileWriteStream struct_os(fp, writeBuffer, sizeof(writeBuffer));
	Writer<FileWriteStream> struct_writer(struct_os);
	draw_struct.Accept(struct_writer);
	fclose(fp);
}

void LevelDataSet::setDeco()
{
	/*������ ����
	draw_deco[floor][deco]{"name" : ���� �̸�::String,
						   "pos" : �߾� ���� ��ġ::int}
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
				//pos�� array ��ȣ. ������ 0~blank-1���� ����
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

	//��� �׸��� ������ ���� ����
	strcat(writeBuffer, "");
	fp = fopen("jsonData/draw/drawDeco.json", "wb");
	FileWriteStream deco_os(fp, writeBuffer, sizeof(writeBuffer));
	Writer<FileWriteStream> deco_writer(deco_os);
	draw_deco.Accept(deco_writer);
	fclose(fp);
	

}
