#pragma once
#include "auth.h"
#include "billstd.h"
#include "card.h"
#include "bill.h"
#include "charge.h"
//Ö÷½çÃæ
void save_showMainMenu(adminList* head_adminList, billStdList* head_billStdList, cardList* end_cardList, billList* end_billList, billUnfinishedList* head_billUnfinishedList, chargeList* end_chargeList);
//adminList
bool save_auth_adminList(adminList* head_adminList);
adminList* read_auth_adminList(int* adminMaxID);
//billStdList
bool save_billStd_billStdList(billStdList* head_billStdList);
billStdList* read_billStd_billStdList(int* billStdMaxID);
//cardList
bool save_card_cardList(cardList* end_cardList);
cardList* read_card_cardList(int* cardMaxID);