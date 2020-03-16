#include <iostream>
#include <ctime>
using namespace std;

#include "menu.h"
#include "auth.h"


int main()
{
	/*
	初始化，先用链表，后期读取配置文件
	*/
	adminList* head_adminList = NULL;
	int nowAdminID = 0;
	//初始化admin/123456的用户
	char in_al_un[20] = "admin";
	char in_al_rn[1000] = "Admin";
	char in_al_pw[50] = "asdfghjkl;'";
	head_adminList = auth_do_addAdmin(head_adminList, in_al_un, in_al_rn, in_al_pw, 1, 0);
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
				break;
			case 6:
				break;
			case 7:
				break;
			case 8:
				if (auth_checkHasAuth(head_adminList, nowAdminID, 0)) head_adminList = auth_showMainMenu(head_adminList, nowAdminID);
				system("cls");
				break;
			case 9:
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
