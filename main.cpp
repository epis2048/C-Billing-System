#include <iostream>
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
	//初始化当前管理账户变量
	int nowAdminID = 0;
	//初始化各种MaxID，用于自增
	int adminMaxID = 0;
	int billStdMaxID = 0;
	int cardMaxID = 100000;
	/*
	初始化，逐步改为读取配置文件
	*/
	
	billStdList* head_billStdList = NULL;
	cardList* end_cardList = NULL;
	billList* end_billList = NULL;
	billUnfinishedList* head_billUnfinishedList = NULL;
	chargeList* end_chargeList = NULL;
	/*
	读取配置文件
	*/
	adminList* head_adminList = read_auth_adminList(&adminMaxID);
	//初始化admin/123456的用户
	char in_al_un[20] = "admin";
	char in_al_rn[1000] = "Admin";
	char in_al_pw[50] = "asdfghjkl;'";
	//head_adminList = auth_do_addAdmin(head_adminList, in_al_un, in_al_rn, in_al_pw, 1, &adminMaxID, 0);
	//初始化一条0.1/s的计费标准
	char in_bsl_n[50] = "默认标准";
	head_billStdList = billstd_do_addBillStd(head_billStdList, in_bsl_n, 's', 10, &billStdMaxID, nowAdminID);
	/*
	主程序开始
	*/
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
