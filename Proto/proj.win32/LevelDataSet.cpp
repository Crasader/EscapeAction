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
	//�� ����
	int rmCnt = (level * 2) + 2;//1���� �ö󰥶����� ��+2, 1Level : 4��, 2Level: 6��...

	//���ʽ� ��
	int bonus_rmCnt = RandomHelper::random_int((int)rmCnt / 3, (int)rmCnt / 2);

	//���� ����
	fl_maxRm = 3;//�� ���� �� �� �ִ� �ִ� �氹�� = 5
	fl_maxWl = fl_maxRm * 5;//�� ���� �� �� �ִ� �ִ� ������, �ִ� �氹��*���� totalũ�� �ִ�
	fl_minRm = 2;// �� ���� �� �� �ִ� �ּ� �氹�� = 2(������ �� ����)
	int minfl = (int)(rmCnt / fl_maxRm);//�ø�, �ּ� ��
	if (rmCnt % fl_maxRm != 0) {
		minfl++;
	}
	int maxfl = (int)(rmCnt / fl_minRm);//����. �ִ� ��
	int floor = RandomHelper::random_int(minfl, maxfl);
	log("floor : %d", floor);
	//���� �� �� ���� ����
	floor_rm = new int[floor];
	int noSet_rmCnt = rmCnt;//���� �ȵ� �� ����
	for (int i = 0; i < floor; i++) {
		int max = noSet_rmCnt - ((floor - i - 2) * fl_minRm - 1);//���� ���� �� �� �ִ� �ִ� �� ����
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


	//draw_wall ���� ����
	Document::AllocatorType& dw_a = draw_wall.GetAllocator();
	draw_wall.SetArray();
	//draw_fur ���� ����
	Document::AllocatorType& df_a = draw_fur.GetAllocator();
	draw_fur.SetArray();

	//������ ����
	int floor = _msize(floor_rm) / sizeof(int);//����
	for (int fl = 0; fl < floor; fl++) {
		int startPos = 0;//���� �պκ� ��ġ ���̸� ����
		if (floor_rm[fl] == fl_maxRm) {
			startPos = RandomHelper::random_int(0, 2) - 2;
		}
		else if (floor_rm[fl] == fl_minRm) {
			startPos = RandomHelper::random_int(0, 2);
		}
		rapidjson::Value dw_fl(kArrayType);//�� ���� �ش��ϴ� �� arr
		rapidjson::Value df_fl(kArrayType);//�� ���� �ش��ϴ� ���� arr
		for (int rm = 0; rm < floor_rm[fl]; rm++) {//�� �� ����
			//���� ����
			Furniture* furni_name = Furniture::create();

			int wl_min = fl_maxWl % floor_rm[fl] == 0 ? fl_maxWl / floor_rm[fl] : fl_maxWl / floor_rm[fl] + 1;
			int wl_max = (fl_maxWl / fl_minRm)+1;
			
			//�� ũ��
			int rmSize = RandomHelper::random_int(wl_min, wl_min+2);
			rmSize = rmSize > wl_max ? wl_max : rmSize;

			//���� ������
			rapidjson::Value df_ecR(kArrayType);
			//���� ��ġ
			int backPos = startPos;//���� ������ �� ��ġ
			int noSet_fur = furni_name->getTotalFntSize();//��ġ�ؾ��� �� ���� ũ��
			for (auto v : furni_name->v_FntData) {
				rapidjson::Value df_fur(kObjectType);
				log("fl : %d rm : %d v_FntData : %d", fl, floor_rm[fl], furni_name->v_FntData.size());
				int frontPos = RandomHelper::random_int(backPos +1, startPos+rmSize-noSet_fur+1);//������ �� ��ġ
				backPos = frontPos + v->fnt_size - 1; 
				noSet_fur -= v->fnt_size;
				float furPos = (float)frontPos + ((float)(v->fnt_size - 1) / 2.0);
				df_fur.AddMember("name", rapidjson::Value().SetString((v->fnt_img).c_str(), df_a), df_a);
				df_fur.AddMember("pos", rapidjson::Value().SetFloat(furPos), df_a);
				df_ecR.PushBack(df_fur, df_a);
			}
			df_fl.PushBack(df_ecR, df_a);
			
			//�� ����
			RandomWall* wall_name = RandomWall::create();
			rapidjson::Value dw_ecR(kObjectType);
			rapidjson::Value dw_pos(startPos);
			//�� 1���� �� resource Array
			rapidjson::Value dw_rm(kArrayType);
			//���� ����
			dw_rm.PushBack(rapidjson::Value().SetString((wall_name->getWallEdgeName()).c_str(), dw_a), dw_a);
			//�� �߾Ӻ� 
			for (int setwall = 0; setwall < rmSize; setwall++) {
				dw_rm.PushBack(rapidjson::Value().SetString((wall_name->getWallName()).c_str(), dw_a), dw_a);
			}
			//�� ������
			dw_rm.PushBack(rapidjson::Value().SetString((wall_name->getWallEdgeName()).c_str(), dw_a), dw_a);

			dw_ecR.AddMember("tile", dw_rm, dw_a);
			dw_ecR.AddMember("pos", dw_pos , dw_a);
			dw_fl.PushBack(dw_ecR, dw_a);
			startPos += rmSize + 1;
		}
		draw_fur.PushBack(df_fl,df_a);
		draw_wall.PushBack(dw_fl, dw_a);
		
	}
	//�� �׸��� ������ ���� ����
	FILE* fp = fopen("jsonData/draw/drawWall.json", "wb");
	char writeBuffer[5000];
	FileWriteStream wall_os(fp, writeBuffer, sizeof(writeBuffer));
	Writer<FileWriteStream> wall_writer(wall_os);
	draw_wall.Accept(wall_writer);
	fclose(fp);

	//���� �׸��� ������ ���� ����
	strcat(writeBuffer, "test");//���� ����
	fp = fopen("jsonData/draw/drawFur.json", "wb");
	FileWriteStream fur_os(fp, writeBuffer, sizeof(writeBuffer));
	Writer<FileWriteStream> fur_writer(fur_os);
	draw_fur.Accept(fur_writer);
	fclose(fp);

}
