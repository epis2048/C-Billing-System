#include <iostream>
#include <iomanip>
#include <conio.h>
#include "billstd.h"
using namespace std;

billStdList* billstd_do_addBillStd(billStdList* head_billStdList, char stdName[50], char stdUnit, int stdUnitCost, int* billStdMaxID, int nowAdminID)
{
	billStdList* p;
	billStdList* q;
	p = (billStdList*)malloc(sizeof(billStdList));//�����ڴ�
	if (p == NULL) {
		cout << "���ʧ�ܣ�" << endl;
		system("pause");
		return head_billStdList;
	}
	//��ʼ������
	(*billStdMaxID)++;
	std::time_t t = std::time(0);
	strcpy(p->stdName, stdName);
	p->id = *billStdMaxID;
	p->stdCreateTime = t;
	p->stdUnit = stdUnit;
	p->stdUnitCost = stdUnitCost;
	p->next = NULL;
	//�����������
	if (head_billStdList == NULL) {
		head_billStdList = p;
	}
	else {
		q = head_billStdList;
		while (q->next != NULL) {
			q = q->next;
		}
		q->next = p;
	}
	return head_billStdList;
}

billStdList* billstd_addBillStd(billStdList* head_billStdList, int* billStdMaxID, int nowAdminID)
{
	system("cls");
	char billStdName[50];
	char stdUnit;
	float stdUnitCostInput;
	int stdUnitCost;
	int sb;//scanf��Ҫ����ֵ����
	cout << "��ӼƷѱ�׼" << endl;
	cout << "�Ʒѱ�׼���ƣ�";
	cin >> billStdName;
	cout << "�Ʒѱ�׼(һëǮһ���ʽ��0.1/s���Ʒѵ�λs,m,h����";
	sb = scanf("%f/%c", &stdUnitCostInput, &stdUnit);
	stdUnitCostInput *= 100;
	stdUnitCost = (int)stdUnitCostInput;
	head_billStdList = billstd_do_addBillStd(head_billStdList, billStdName, stdUnit, stdUnitCost, billStdMaxID, nowAdminID);
	system("cls");
	cout << "��ӳɹ���" << endl;
	return head_billStdList;
}

billStdList* billstd_showMainMenu(billStdList* head_billStdList, int* billStdMaxID, int nowAdminID)
{
	int c = 0;
	system("cls");
	char bl_s_ct[25];
	struct tm* ttime;
	while (1) {
		cout << "�Ʒѱ�׼�б�" << endl;
		cout << setw(6) << "ID" << setw(12) << "����" << setw(26) << "����ʱ��" << setw(6) << "    ��׼" << endl;
		billStdList* p = head_billStdList;
		while (1) {
			if (p == NULL) break;
			ttime = localtime(&p->stdCreateTime);
			strftime(bl_s_ct, sizeof(bl_s_ct), "%Y��%m��%d�� %H:%M:%S", ttime);
			cout << setw(6) << p->id << setw(12) << p->stdName << setw(26) << bl_s_ct << setw(6) << p->stdUnitCost*1.0/100 << "/" << p->stdUnit << endl;
			p = p->next;
		}
		cout << "������" << endl;
		cout << "1.��ӼƷѱ�׼" << endl;
		cout << "2.�༭�Ʒѱ�׼" << endl;
		cout << "3.ɾ���Ʒѱ�׼" << endl;
		cout << "0.�������˵�" << endl;
		cout << "��ѡ��";
		cin >> c;
		switch (c) {
		case 1:
			head_billStdList = billstd_addBillStd(head_billStdList, billStdMaxID, nowAdminID);
			break;
		case 2:
			break;
		case 3:
			break;
		case 0:
			break;
		default:
			cout << "��ѡ����ȷ��ѡ�" << endl;
			system("pause");
			system("cls");
			break;
		}
		if (c == 0) {
			break;
		}
	}
	return head_billStdList;
}