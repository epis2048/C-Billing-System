#pragma once
#include <ctime>
#include "billstd.h"
#include "auth.h"
typedef struct card {
	int id;//�����ÿ��ţ�ʵ������
	char showID[10];//��ʾ�����뿨�ţ���λ������6λǰ�油0
	char password[50];//������
	int balance;//����λ�Ƿ֣�һ��Ǯ100
	int totalCharge;//�ۼ�����Ǯ������λ�Ƿ֣�һ��Ǯ100
	int totalChargeTime;//�ۼ����Ѵ���
	time_t creatTime;//����ʱ��
	int adduid;//��������ԱID
	time_t recentChargeTime;//�ϴ�����ʱ�䣬�Խ���ʱ�����
	bool isDel = false;
	struct card* prev;//����
} cardList;


//���˵�
cardList* card_showMainMenu(cardList* end_cardList, billStdList* head_billStdList, adminList* head_adminList, int* cardMaxID, int nowAdminID);
//��ӿ�
//��ѯ��(�б�)
//ע����