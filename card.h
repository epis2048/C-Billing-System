#pragma once
#include <ctime>
#include "billstd.h"
#include "auth.h"
typedef struct card {
	int id;//程序用卡号，实现自增
	char showID[7];//显示和输入卡号，六位，不足6位前面补0
	char password[50];//卡密码
	int balance;//余额，单位是分，一块钱100
	int billStd;//此卡的计费标准
	int totalCharge = 0;//累计消费钱数，单位是分，一块钱100
	int totalChargeTime = 0;//累计消费次数
	time_t creatTime;//开卡时间
	int adduid;//开卡管理员ID
	time_t recentBillTime;//上次消费时间，以结束时间计算
	time_t recentChargeTime;//上次充值时间
	bool isDel = false;
	struct card* prev;//倒挂
} cardList;


//主菜单
cardList* card_showMainMenu(cardList* end_cardList, billStdList* head_billStdList, adminList* head_adminList, int* cardMaxID, int nowAdminID);
//添加卡
cardList* card_do_addCard(cardList* end_cardList, char password[50], int balance, int billStd, int* cardMaxID, int nowAdminID);
cardList* card_addCard(cardList* end_cardList, billStdList* head_billStdList, int* cardMaxID, int nowAdminID);
//查询卡
cardList* card_queryCardList(cardList* end_cardList, billStdList* head_billStdList, adminList* head_adminList, int nowAdminID);
cardList* card_queryCardDetail(cardList* end_cardList, billStdList* head_billStdList, adminList* head_adminList, int nowAdminID);
//编辑卡
cardList* card_editCard(cardList* end_cardList, billStdList* head_billStdList, int nowAdminID);
//注销卡