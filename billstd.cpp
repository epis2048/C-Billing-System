#include <iostream>
#include <iomanip>
#include <conio.h>
#include "billstd.h"
using namespace std;

billStdList* billstd_do_addBillStd(billStdList* head_billStdList, char stdName[50], char stdUnit, int stdUnitCost, int* billStdMaxID, int nowAdminID)
{
	billStdList* p;
	billStdList* q;
	p = (billStdList*)malloc(sizeof(billStdList));//申请内存
	if (p == NULL) {
		cout << "添加失败！" << endl;
		system("pause");
		return head_billStdList;
	}
	//初始化数据
	(*billStdMaxID)++;
	std::time_t t = std::time(0);
	strcpy(p->stdName, stdName);
	p->id = *billStdMaxID;
	p->stdCreateTime = t;
	p->stdUnit = stdUnit;
	p->stdUnitCost = stdUnitCost;
	p->next = NULL;
	//链表里插数据
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
	int sb;//scanf非要返回值。。
	cout << "添加计费标准" << endl;
	cout << "计费标准名称：";
	cin >> billStdName;
	cout << "计费标准(一毛钱一秒格式：0.1/s、计费单位s,m,h）：";
	sb = scanf("%f/%c", &stdUnitCostInput, &stdUnit);
	stdUnitCostInput *= 100;
	stdUnitCost = (int)stdUnitCostInput;
	head_billStdList = billstd_do_addBillStd(head_billStdList, billStdName, stdUnit, stdUnitCost, billStdMaxID, nowAdminID);
	system("cls");
	cout << "添加成功！" << endl;
	return head_billStdList;
}

billStdList* billstd_showMainMenu(billStdList* head_billStdList, int* billStdMaxID, int nowAdminID)
{
	int c = 0;
	system("cls");
	char bl_s_ct[25];
	struct tm* ttime;
	while (1) {
		cout << "计费标准列表：" << endl;
		cout << setw(6) << "ID" << setw(12) << "名称" << setw(26) << "创建时间" << setw(6) << "    标准" << endl;
		billStdList* p = head_billStdList;
		while (1) {
			if (p == NULL) break;
			ttime = localtime(&p->stdCreateTime);
			strftime(bl_s_ct, sizeof(bl_s_ct), "%Y年%m月%d日 %H:%M:%S", ttime);
			cout << setw(6) << p->id << setw(12) << p->stdName << setw(26) << bl_s_ct << setw(6) << p->stdUnitCost*1.0/100 << "/" << p->stdUnit << endl;
			p = p->next;
		}
		cout << "操作：" << endl;
		cout << "1.添加计费标准" << endl;
		cout << "2.编辑计费标准" << endl;
		cout << "3.删除计费标准" << endl;
		cout << "0.返回主菜单" << endl;
		cout << "请选择：";
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
			cout << "请选择正确的选项！" << endl;
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