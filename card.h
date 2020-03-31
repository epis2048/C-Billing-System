#pragma once
#include <ctime>
#include "data.h"

//���˵�
cardList* card_showMainMenu(cardList* end_cardList, billStdList* head_billStdList, billList* end_billList, chargeList* end_chargeList, adminList* head_adminList, int* cardMaxID, int nowAdminID);
//���ӿ�
cardList* card_do_addCard(cardList* end_cardList, char password[50], int balance, int billStd, int* cardMaxID, int nowAdminID);
cardList* card_addCard(cardList* end_cardList, billStdList* head_billStdList, int* cardMaxID, int nowAdminID);
//��ѯ��
cardList* card_queryCardList(cardList* end_cardList, billStdList* head_billStdList, adminList* head_adminList, int nowAdminID);
cardList* card_queryCardDetail(cardList* end_cardList, billStdList* head_billStdList, adminList* head_adminList, int nowAdminID);
//�༭��
cardList* card_editCard(cardList* end_cardList, billStdList* head_billStdList, int nowAdminID);
//ע����
cardList* card_do_delCard(cardList* end_cardList, int cid, int nowAdminID);
cardList* card_delCard(cardList* end_cardList, int nowAdminID);
//��ѯ����¼
void card_query_chargeList(cardList* end_cardList, chargeList* end_chargeList, adminList* head_adminList);
void card_query_billList(cardList* end_cardList, billList* end_billList);