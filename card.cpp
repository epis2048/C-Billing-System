#include <iostream>
#include "billstd.h"
#include "auth.h"
#include "card.h"


cardList* card_showMainMenu(cardList* end_cardList, billStdList* head_billStdList, adminList* head_adminList, int* cardMaxID, int nowAdminID)
{
	int c = 0;
	system("cls");
	while (1) {
		cout << "������" << endl;
		cout << "1. ����" << endl;
		cout << "2. ע����" << endl;
		cout << "3. ��ѯ���б�" << endl;
		cout << "4. ��ѯ������" << endl;
		cout << "0. ����" << endl;
		cout << "��ѡ��" ;
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
			cout << "��������ȷ��ѡ�" << endl;
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