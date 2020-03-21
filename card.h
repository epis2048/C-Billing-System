#pragma once
#include <ctime>
#include "billstd.h"
#include "auth.h"
typedef struct card {
	int id;//�����ÿ��ţ�ʵ������
	char showID[7];//��ʾ�����뿨�ţ���λ������6λǰ�油0
	char password[50];//������
	int balance;//����λ�Ƿ֣�һ��Ǯ100
	int billStd;//�˿��ļƷѱ�׼
	int totalCharge = 0;//�ۼ�����Ǯ������λ�Ƿ֣�һ��Ǯ100
	int totalChargeTime = 0;//�ۼ����Ѵ���
	time_t creatTime;//����ʱ��
	int adduid;//��������ԱID
	time_t recentBillTime;//�ϴ�����ʱ�䣬�Խ���ʱ�����
	time_t recentChargeTime;//�ϴγ�ֵʱ��
	bool isDel = false;
	struct card* prev;//����
} cardList;


//���˵�
cardList* card_showMainMenu(cardList* end_cardList, billStdList* head_billStdList, adminList* head_adminList, int* cardMaxID, int nowAdminID);
//��ӿ�
cardList* card_do_addCard(cardList* end_cardList, char password[50], int balance, int billStd, int* cardMaxID, int nowAdminID);
cardList* card_addCard(cardList* end_cardList, billStdList* head_billStdList, int* cardMaxID, int nowAdminID);
//��ѯ��
cardList* card_queryCardList(cardList* end_cardList, billStdList* head_billStdList, adminList* head_adminList, int nowAdminID);
cardList* card_queryCardDetail(cardList* end_cardList, billStdList* head_billStdList, adminList* head_adminList, int nowAdminID);
//�༭��
cardList* card_editCard(cardList* end_cardList, billStdList* head_billStdList, int nowAdminID);
//ע����