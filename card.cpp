#include <iostream>
#include "billstd.h"
#include "auth.h"
#include "card.h"


cardList* card_showMainMenu(cardList* end_cardList, billStdList* head_billStdList, adminList* head_adminList, int* cardMaxID, int nowAdminID)
{
	int c = 0;
	system("cls");
	while (1) {
		cout << "卡管理" << endl;
		cout << "1. 开卡" << endl;
		cout << "2. 注销卡" << endl;
		cout << "3. 查询卡列表" << endl;
		cout << "4. 查询卡详情" << endl;
		cout << "0. 返回" << endl;
		cout << "请选择：" ;
		cin >> c;
		switch (c) {
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 0:
			break;
		default:
			cout << "请输入正确的选项！" << endl;
			system("pause");
			system("cls");
			break;
		}
		if (c == 0) {
			break;
		}
	}
	return end_cardList;
}