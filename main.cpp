﻿#include <iostream>
#include <ctime>
using namespace std;

#include "menu.h"
#include "auth.h"
#include "billstd.h"
#include "card.h"
#include "bill.h"
#include "charge.h"
#include "query.h"
#include "service.h"

int main()
{
	cout << "欢迎使用计费管理系统！" << endl << "系统正在初始化..." << endl;
	//初始化当前管理账户变量
	int nowAdminID = 0;
	/*
	初始化各种MaxID，用于自增，读取配置文件的时候也会修改这些ID
	*/
	int adminMaxID = 0;
	int billStdMaxID = 0;
	int cardMaxID = 0;
	/*
	初始化，逐步改为读取配置文件
	*/
	billList* end_billList = NULL;
	billUnfinishedList* head_billUnfinishedList = NULL;
	chargeList* end_chargeList = NULL;
	/*
	读取配置文件
	*/
	adminList* head_adminList = read_auth_adminList(&adminMaxID);
	billStdList* head_billStdList = read_billStd_billStdList(&billStdMaxID);
	cardList* end_cardList = read_card_cardList(&cardMaxID);
	//卡是倒叙的，所以读完了保存一遍再读能修正顺序问题，再保存一边来保证文件内顺序没问题
	//有点蛋疼......但是实现起来比直接倒叙链表省事
	if (save_card_cardList(end_cardList)) end_cardList = read_card_cardList(&cardMaxID);
	if (save_card_cardList(end_cardList));


	/*
	主程序开始
	*/
	system("cls");
	int userChoose = 0;
	while (1) {
		if (auth_checkStatus(head_adminList, nowAdminID) != 0) {
			userChoose = showMenu(head_adminList, nowAdminID);
			switch (userChoose){
			case 1:
				break;
			case 2:
				break;
			case 3:
				break;
			case 4:
				break;
			case 5:
				if (auth_checkHasAuth(head_adminList, nowAdminID, 3)) end_cardList = card_showMainMenu(end_cardList, head_billStdList, head_adminList, &cardMaxID, nowAdminID);
				system("cls");
				break;
			case 6:
				if (auth_checkHasAuth(head_adminList, nowAdminID, 4)) head_billStdList = billstd_showMainMenu(head_billStdList, &billStdMaxID, nowAdminID);
				system("cls"); 
				break;
			case 7:
				break;
			case 8:
				if (auth_checkHasAuth(head_adminList, nowAdminID, 0)) head_adminList = auth_showMainMenu(head_adminList, &adminMaxID, nowAdminID);
				system("cls");
				break;
			case 9:
				save_showMainMenu(head_adminList, head_billStdList, end_cardList, end_billList, head_billUnfinishedList, end_chargeList);
				system("cls");
				break;
			case 0:
				break;
			default:
				cout << "请选择正确的选项！" << endl;
				system("pause");
				system("cls");
				break;
			}
			if (userChoose == 0) {
				system("cls");
				nowAdminID = 0;
			}
		}
		else {
			nowAdminID = auth_login(head_adminList);
			if (nowAdminID < 0) break;
		}
	}
	return 0;
}
