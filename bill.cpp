#include <iostream>
#include <ctime>
#include "bill.h"

using namespace std;

billUnfinishedList* bill_up(billUnfinishedList* head_billUnfinishedList, cardList* end_cardList, int nowAdminID)
{
	int cid;
	bool hasFoundCard = false;
	cardList* pcl = end_cardList;
	billUnfinishedList* p;
	billUnfinishedList* q;
	system("cls");
	cout << "�ϻ�" << endl;
	cout << "�����뿨�ţ�";
	cin >> cid;
	while (1) {
		if (pcl == NULL) break;
		if (pcl->id == cid) {
			hasFoundCard = true;
			break;
		}
		pcl = pcl->prev;
	}
	if (hasFoundCard) {
		if (bill_query_isUp(head_billUnfinishedList, cid)) {
			cout << "�ÿ������ϻ���" << endl;
		}
		else {
			char cpw[50];
			cout << "�����뿨���룺";
			cin >> cpw;
			if (strcmp(cpw, pcl->password) == 0) {
				system("cls");
				p = (billUnfinishedList*)malloc(sizeof(billUnfinishedList));//�����ڴ�
				if (p == NULL) {
					cout << "�ϻ�ʧ�ܣ�" << endl;
				}
				else {
					std::time_t t = std::time(0);
					p->cardID = pcl->id;
					p->stdID = pcl->billStd;
					p->upAdminID = nowAdminID;
					p->upTime = t;
					p->next = NULL;
					//�����������
					if (head_billUnfinishedList == NULL) {
						head_billUnfinishedList = p;
					}
					else {
						q = head_billUnfinishedList;
						while (q->next != NULL) {
							q = q->next;
						}
						q->next = p;
					}
					cout << "�ϻ��ɹ���" << endl;
				}
			}
			else {
				cout << "���������" << endl;
			}
		}
	}
	else {
		cout << "û���ҵ��ÿ���" << endl;
	}
	system("pause");
	system("cls");
	return head_billUnfinishedList;
}

bool bill_query_isUp(billUnfinishedList* head_billUnfinishedList, int cardID)
{
	bool isUp = false;
	billUnfinishedList* p = head_billUnfinishedList;
	while (1) {
		if (p == NULL) break;
		if (p->cardID == cardID) {
			isUp = true;
			break;
		}
		p = p->next;
	}
	return isUp;
}