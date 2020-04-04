#pragma once
#include <ctime>
#include "data.h"

//ио╩З
billUnfinishedList* bill_up(billUnfinishedList* head_billUnfinishedList, cardList* end_cardList, int nowAdminID);

//API
bool bill_query_isUp(billUnfinishedList* head_billUnfinishedList, int cardID);