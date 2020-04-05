#include <iostream>
#include <iomanip>
#include <conio.h>
#include "query.h"
#include "billstd.h"
#include "auth.h"

using namespace std;


void query_billUnfinishedList(billUnfinishedList* head_billUnfinishedList, billStdList* head_billStdList, adminList* head_adminList)
{
	system("cls");
	cout << "�����ϻ��Ŀ���" << endl;
	billUnfinishedList* p = head_billUnfinishedList;
	char showID[7];
	int i;
	int c;
	char q_bul_sut[25];
	struct tm* ttime;
	cout << setw(6) << "����" << setw(26) << "�Ʒѱ�׼" << setw(26) << "�ϻ�ʱ��" << setw(26) << "�ϻ�����Ա" << endl;
	while (1) {
		if (p == NULL) break;
		c = p->cardID;
		//ѭ�����showID
		for (i = 5; i >= 0; i--) {
			if (c > 0) {
				showID[i] = c % 10 + '0';
				c /= 10;
			}
			else {
				showID[i] = '0';
			}
		}
		showID[6] = '\0';
		ttime = localtime(&p->upTime);
		strftime(q_bul_sut, sizeof(q_bul_sut), "%Y��%m��%d�� %H:%M:%S", ttime);
		cout << setw(6) << showID << setw(26) << billstd_query_nameAndStd(head_billStdList, p->stdID) << setw(26) << q_bul_sut << setw(26) << auth_query_getRealnameByID(head_adminList, p->upAdminID) << endl;
		p = p->next;
	}
	system("pause");
}

void query_billList(billList* end_billList, billStdList* head_billStdList, adminList* head_adminList)
{
	system("cls");
	cout << "�ϻ���¼��" << endl;
	billList* p = end_billList;
	char showID[7];
	int i;
	int c;
	char c_qbl_ut[25];
	char c_qbl_dt[25];
	struct tm* ttime;
	cout << setw(8) << "����" << setw(20) << "�Ʒѱ�׼" << setw(6) << "����" << setw(26) << "�ϻ�ʱ��" << setw(12) << "�ϻ�������" << setw(26) << "�»�ʱ��" << setw(12) << "�»�������" << endl;
	while (1) {
		if (p == NULL) break;
		c = p->cardID;
		//ѭ�����showID
		for (i = 5; i >= 0; i--) {
			if (c > 0) {
				showID[i] = c % 10 + '0';
				c /= 10;
			}
			else {
				showID[i] = '0';
			}
		}
		showID[6] = '\0';
		ttime = localtime(&p->upTime);
		ttime = localtime(&p->upTime);
		strftime(c_qbl_ut, sizeof(c_qbl_ut), "%Y��%m��%d�� %H:%M:%S", ttime);
		ttime = localtime(&p->downTime);
		strftime(c_qbl_dt, sizeof(c_qbl_dt), "%Y��%m��%d�� %H:%M:%S", ttime);
		cout << setw(8) << showID << setw(20) << billstd_query_nameAndStd(head_billStdList, p->stdID) << setw(6) << p->cost * 1.0 / 100 << setw(26) << c_qbl_ut << setw(12) << auth_query_getRealnameByID(head_adminList, p->upAdminID) << setw(26) << c_qbl_dt << setw(12) << auth_query_getRealnameByID(head_adminList, p->downAdminID) << endl;
		p = p->prev;
	}
	system("pause");
}

void query_chargeList(cardList* end_cardList, chargeList* end_chargeList, adminList* head_adminList)
{
	system("cls");
	cout << "�ϻ���¼��" << endl;
	char showID[7];
	int i;
	int c;
	char cl_s_rct[25];
	struct tm* ttime;
	chargeList* q = end_chargeList;
	char ot[10];
	cout << setw(4) << "ID" << setw(8) << "����" << setw(6) << "����" << setw(10) << "�仯��" << setw(12) << "������" << setw(26) << "����ʱ��" << endl;
	while (1) {
		if (q == NULL) break;
		if (q->chargeType == 1) strcpy(ot, "��ֵ");
		else strcpy(ot, "�˷�");
		ttime = localtime(&q->time);
		strftime(cl_s_rct, sizeof(cl_s_rct), "%Y��%m��%d�� %H:%M:%S", ttime);
		cout << setw(4) << q->id << setw(6) << ot << setw(8) << q->cardShowID << setw(10) << q->charge * 1.0 / 100 << setw(12) << auth_query_getRealnameByID(head_adminList, q->adminID) << setw(26) << cl_s_rct << endl;
		q = q->prev;
	}
	system("pause");
}

void query_recentData(adminList* head_adminList, billStdList* head_billStdList, cardList* end_cardList, billList* end_billList, billUnfinishedList* head_billUnfinishedList, chargeList* end_chargeList)
{
	system("cls");
	int cd;
	cout << "��ѯͳ��" << endl;
	cout << "������Ҫ��ѯ��������";
	cin >> cd;
	time_t tnow = time(0);
	time_t tstart = tnow - (time_t)cd * 60 * 60 * 24;
	system("cls");
	cout << "��ѯ��� " << cd << " ��" << endl;
	char qcd_t_st[25];
	char qcd_t_et[25];
	struct tm* ttime;
	ttime = localtime(&tstart);
	strftime(qcd_t_st, sizeof(qcd_t_st), "%Y��%m��%d�� %H:%M:%S", ttime);
	ttime = localtime(&tnow);
	strftime(qcd_t_et, sizeof(qcd_t_et), "%Y��%m��%d�� %H:%M:%S", ttime);
	cout << "��ʼʱ�䣺" << qcd_t_st << endl << "����ʱ�䣺" << qcd_t_et << endl;
	int count_charge = 0;
	int count_bill = 0;
	int count_balance = 0;
	//ͳ��count_charge

	//ͳ��count_bill

	//ͳ��count_balance

	system("pause");
}

void query_showMainMenu(adminList* head_adminList, billStdList* head_billStdList, cardList* end_cardList, billList* end_billList, billUnfinishedList* head_billUnfinishedList, chargeList* end_chargeList)
{
	system("cls");
	int c;
	while (1) {
		cout << "��ѯ�˵���" << endl;
		cout << "1. ��ѯ�����ϻ��Ŀ�" << endl;
		cout << "2. ��ѯ�����ϻ���¼" << endl;
		cout << "3. ��ѯ���г�ֵ�˷Ѽ�¼" << endl;
		cout << "4. ��ѯ�����ͳ������" << endl;
		cout << "0. �����ϼ�" << endl;
		cout << "��ѡ��";
		cin >> c;
		switch (c) {
		case 1:
			query_billUnfinishedList(head_billUnfinishedList, head_billStdList, head_adminList);
			system("cls");
			break;
		case 2:
			query_billList(end_billList, head_billStdList, head_adminList);
			system("cls");
			break;
		case 3:
			query_chargeList(end_cardList, end_chargeList, head_adminList);
			system("cls");
			break;
		case 4:
			query_recentData(head_adminList, head_billStdList, end_cardList, end_billList, head_billUnfinishedList, end_chargeList);
			system("cls");
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
	return;
}