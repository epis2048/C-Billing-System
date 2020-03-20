#pragma once
#include <ctime>
#include "billstd.h"
#include "auth.h"
typedef struct card {
	int id;//程序用卡号，实现自增
	char showID[10];//显示和输入卡号，六位，不足6位前面补0
	char password[50];//卡密码
	int balance;//余额，单位是分，一块钱100
	int totalCharge;//累计消费钱数，单位是分，一块钱100
	int totalChargeTime;//累计消费次数
	time_t creatTime;//开卡时间
	int adduid;//开卡管理员ID
	time_t recentChargeTime;//上次消费时间，以结束时间计算
	bool isDel = false;
	struct card* prev;//倒挂
} cardList;


//主菜单
cardList* card_showMainMenu(cardList* end_cardList, billStdList* head_billStdList, adminList* head_adminList, int* cardMaxID, int nowAdminID);
//添加卡
//查询卡(列表)
//注销卡