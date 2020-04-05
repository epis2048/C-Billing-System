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
	cout << "正在上机的卡：" << endl;
	billUnfinishedList* p = head_billUnfinishedList;
	char showID[7];
	int i;
	int c;
	char q_bul_sut[25];
	struct tm* ttime;
	cout << setw(6) << "卡号" << setw(26) << "计费标准" << setw(26) << "上机时间" << setw(26) << "上机管理员" << endl;
	while (1) {
		if (p == NULL) break;
		c = p->cardID;
		//循环填充showID
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
		strftime(q_bul_sut, sizeof(q_bul_sut), "%Y年%m月%d日 %H:%M:%S", ttime);
		cout << setw(6) << showID << setw(26) << billstd_query_nameAndStd(head_billStdList, p->stdID) << setw(26) << q_bul_sut << setw(26) << auth_query_getRealnameByID(head_adminList, p->upAdminID) << endl;
		p = p->next;
	}
	system("pause");
}

void query_billList(billList* end_billList, billStdList* head_billStdList, adminList* head_adminList)
{
	system("cls");
	cout << "上机记录：" << endl;
	billList* p = end_billList;
	char showID[7];
	int i;
	int c;
	char c_qbl_ut[25];
	char c_qbl_dt[25];
	struct tm* ttime;
	cout << setw(8) << "卡号" << setw(20) << "计费标准" << setw(6) << "花费" << setw(26) << "上机时间" << setw(12) << "上机操作者" << setw(26) << "下机时间" << setw(12) << "下机操作者" << endl;
	while (1) {
		if (p == NULL) break;
		c = p->cardID;
		//循环填充showID
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
		strftime(c_qbl_ut, sizeof(c_qbl_ut), "%Y年%m月%d日 %H:%M:%S", ttime);
		ttime = localtime(&p->downTime);
		strftime(c_qbl_dt, sizeof(c_qbl_dt), "%Y年%m月%d日 %H:%M:%S", ttime);
		cout << setw(8) << showID << setw(20) << billstd_query_nameAndStd(head_billStdList, p->stdID) << setw(6) << p->cost * 1.0 / 100 << setw(26) << c_qbl_ut << setw(12) << auth_query_getRealnameByID(head_adminList, p->upAdminID) << setw(26) << c_qbl_dt << setw(12) << auth_query_getRealnameByID(head_adminList, p->downAdminID) << endl;
		p = p->prev;
	}
	system("pause");
}

void query_chargeList(cardList* end_cardList, chargeList* end_chargeList, adminList* head_adminList)
{
	system("cls");
	cout << "上机记录：" << endl;
	char showID[7];
	int i;
	int c;
	char cl_s_rct[25];
	struct tm* ttime;
	chargeList* q = end_chargeList;
	char ot[10];
	cout << setw(4) << "ID" << setw(8) << "卡号" << setw(6) << "操作" << setw(10) << "变化量" << setw(12) << "操作者" << setw(26) << "操作时间" << endl;
	while (1) {
		if (q == NULL) break;
		if (q->chargeType == 1) strcpy(ot, "充值");
		else strcpy(ot, "退费");
		ttime = localtime(&q->time);
		strftime(cl_s_rct, sizeof(cl_s_rct), "%Y年%m月%d日 %H:%M:%S", ttime);
		cout << setw(4) << q->id << setw(6) << ot << setw(8) << q->cardShowID << setw(10) << q->charge * 1.0 / 100 << setw(12) << auth_query_getRealnameByID(head_adminList, q->adminID) << setw(26) << cl_s_rct << endl;
		q = q->prev;
	}
	system("pause");
}

void query_recentData(adminList* head_adminList, billStdList* head_billStdList, cardList* end_cardList, billList* end_billList, billUnfinishedList* head_billUnfinishedList, chargeList* end_chargeList)
{
	system("cls");
	int cd;
	cout << "查询统计" << endl;
	cout << "请输入要查询的天数：";
	cin >> cd;
	time_t tnow = time(0);
	time_t tstart = tnow - (time_t)cd * 60 * 60 * 24;
	system("cls");
	cout << "查询最近 " << cd << " 天" << endl;
	char qcd_t_st[25];
	char qcd_t_et[25];
	struct tm* ttime;
	ttime = localtime(&tstart);
	strftime(qcd_t_st, sizeof(qcd_t_st), "%Y年%m月%d日 %H:%M:%S", ttime);
	ttime = localtime(&tnow);
	strftime(qcd_t_et, sizeof(qcd_t_et), "%Y年%m月%d日 %H:%M:%S", ttime);
	cout << "开始时间：" << qcd_t_st << endl << "结束时间：" << qcd_t_et << endl;
	int count_charge = 0;
	int count_bill = 0;
	int count_balance = 0;
	//统计count_charge

	//统计count_bill

	//统计count_balance

	system("pause");
}

void query_showMainMenu(adminList* head_adminList, billStdList* head_billStdList, cardList* end_cardList, billList* end_billList, billUnfinishedList* head_billUnfinishedList, chargeList* end_chargeList)
{
	system("cls");
	int c;
	while (1) {
		cout << "查询菜单：" << endl;
		cout << "1. 查询正在上机的卡" << endl;
		cout << "2. 查询所有上机记录" << endl;
		cout << "3. 查询所有充值退费记录" << endl;
		cout << "4. 查询最近的统计数据" << endl;
		cout << "0. 返回上级" << endl;
		cout << "请选择：";
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
			cout << "请选择正确的选项！" << endl;
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