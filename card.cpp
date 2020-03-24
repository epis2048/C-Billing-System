#include <iostream>
#include <iomanip>
#include <conio.h>
#include <ctime>
#include "billstd.h"
#include "auth.h"
#include "card.h"

cardList* card_do_addCard(cardList* end_cardList, char password[50], int balance, int billStd, int* cardMaxID, int nowAdminID)
{
	cardList* p;
	p = (cardList*)malloc(sizeof(cardList));//申请内存
	if (p == NULL) {
		cout << "开卡失败！" << endl;
		system("pause");
		return end_cardList;
	}
	(*cardMaxID)++;
	p->id = *cardMaxID;
	int c = p->id;
	int i;
	//循环填充showID
	for (i = 5; i >= 0; i--) {
		if (c > 0) {
			p->showID[i] = c % 10 + '0';
			c /= 10;
		}
		else {
			p->showID[i] = '0';
		}
	}
	p->showID[6] = '\0';
	strcpy(p->password, password);
	p->balance = balance;
	p->billStd = billStd;
	std::time_t t = std::time(0);
	p->creatTime = t;
	p->adduid = nowAdminID;
	//进行一些没用的初始化，鬼知道为什么定义里写了不管用
	p->totalCharge = 0;
	p->isDel = false;
	p->totalChargeTime = 0;
	//这里倒挂插链表, 为什么比正着简单这么多...
	p->prev = end_cardList;
	end_cardList = p;
	return end_cardList;
}

cardList* card_do_delCard(cardList* end_cardList, int cid, int nowAdminID) {
	bool hasFound = false;
	cardList* p = end_cardList;
	while (1) {
		if (p == NULL) break;
		if (p->id == cid) {
			hasFound = true;
			p->isDel = true;
			break;
		}
		p = p->prev;
	}
	if (hasFound) cout << "注销成功！" << endl;
	else cout << "未找到该卡！" << endl;
	return end_cardList;
}

cardList* card_addCard(cardList* end_cardList, billStdList* head_billStdList, int* cardMaxID, int nowAdminID)
{
	system("cls");
	int i;
	int c = *cardMaxID;
	//计算一下下一张卡的卡号
	char showID[7];
	c++;
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
	char password[50];
	cout << "开卡" << endl;
	cout << "卡号：" << showID << endl;
	cout << "密码：";
	cin >> password;
	//cout << password << endl;
	float inputBalance;
	int balance;
	cout << "初始金额：";
	cin >> inputBalance;
	inputBalance *= 100;
	balance = (int)inputBalance;
	int billStd = 0;
	//显示计费标准
	char bl_s_ct[25];
	struct tm* ttime;
	adc_showbstd:system("cls");//这有一个标签
	cout << "计费标准列表：" << endl;
	cout << setw(6) << "ID" << setw(12) << "名称" << setw(26) << "创建时间" << setw(6) << "    标准" << endl;
	billStdList* p = head_billStdList;
	while (1) {
		if (p == NULL) break;
		if (p->isDel == true) {
			p = p->next;
			continue;
		}
		ttime = localtime(&p->stdCreateTime);
		strftime(bl_s_ct, sizeof(bl_s_ct), "%Y年%m月%d日 %H:%M:%S", ttime);
		cout << setw(6) << p->id << setw(12) << p->stdName << setw(26) << bl_s_ct << setw(6) << p->stdUnitCost * 1.0 / 100 << "/" << p->stdUnit << endl;
		p = p->next;
	}
	cout << "请选择计费标准ID：";
	cin >> billStd;
	p = head_billStdList;
	if (!billstd_query_isValid(head_billStdList, billStd)) goto adc_showbstd;//看看输入的ID存不存在
	end_cardList = card_do_addCard(end_cardList, password, balance, billStd, cardMaxID, nowAdminID);
	cout << "开卡成功！" << endl;
	system("pause");
	system("cls");
	return end_cardList;
}

cardList* card_queryCardList(cardList* end_cardList, billStdList* head_billStdList, adminList* head_adminList, int nowAdminID)
{
	system("cls");
	cardList* p = end_cardList;
	string str_billStd;
	char c_s_t[25];
	struct tm* ttime;
	cout << "卡列表：" << endl;
	cout << setw(6) << "卡号" << setw(6) << "余额" << setw(26) << "计费标准" << setw(26) << "最近使用时间" << endl;
	while (1) {
		if (p == NULL) break;
		if (p->isDel) { 
			p = p->prev;
			continue; 
		}
		if(p->recentBillTime < 0){
			strcpy(c_s_t, "暂无记录");
		}
		else {
			ttime = localtime(&p->recentBillTime);
			strftime(c_s_t, sizeof(c_s_t), "%Y年%m月%d日 %H:%M:%S", ttime);
		}
		str_billStd = billstd_query_nameAndStd(head_billStdList, p->billStd);
		cout << setw(6) << p->showID << setw(6) << p->balance*1.0/100 << setw(26) << str_billStd << setw(26) << c_s_t << endl;
		p = p->prev;
	}
	system("pause");
	system("cls");
	return end_cardList;
}

cardList* card_queryCardDetail(cardList* end_cardList, billStdList* head_billStdList, adminList* head_adminList, int nowAdminID)
{
	cardList* p = end_cardList;
	int cid;
	bool hasFound = false;
	char c_qcd_ta[25];
	struct tm* ttime;
	system("cls");
	cout << "查询卡详情" << endl;
	cout << "请输入卡号：";
	cin >> cid;
	while (1) {
		if (p == NULL) break;
		if (p->id == cid) {
			hasFound = true;
			break;
		}
		p = p->prev;
	}
	if (hasFound) {
		system("cls");
		cout << "查询成功！" << endl;
		cout << setw(12) << "Name" << setw(26) << "Value" << endl;
		cout << setw(12) << "ID" << setw(26) << p->showID << endl;
		cout << setw(12) << "余额" << setw(26) << p->balance*1.0/100 << endl;
		cout << setw(12) << "计费标准" << setw(26) << billstd_query_nameAndStd(head_billStdList, p->billStd )<< endl;
		cout << setw(12) << "累计消费次数" << setw(26) << p->totalChargeTime << endl;
		cout << setw(12) << "累计消费金额" << setw(26) << p->totalCharge << endl;
		if (p->recentBillTime < 0) strcpy(c_qcd_ta, "暂无");
		else {
			ttime = localtime(&p->recentBillTime);
			strftime(c_qcd_ta, sizeof(c_qcd_ta), "%Y年%m月%d日 %H:%M:%S", ttime);
		}
		cout << setw(12) << "上次消费时间" << setw(26) << c_qcd_ta << endl;
		if (p->recentChargeTime < 0) strcpy(c_qcd_ta, "暂无");
		else {
			ttime = localtime(&p->recentChargeTime);
			strftime(c_qcd_ta, sizeof(c_qcd_ta), "%Y年%m月%d日 %H:%M:%S", ttime);
		}
		cout << setw(12) << "上次充值时间" << setw(26) << c_qcd_ta << endl;
		if (p->creatTime < 0) strcpy(c_qcd_ta, "暂无");
		else {
			ttime = localtime(&p->creatTime);
			strftime(c_qcd_ta, sizeof(c_qcd_ta), "%Y年%m月%d日 %H:%M:%S", ttime);
		}
		cout << setw(12) << "开卡时间" << setw(26) << c_qcd_ta << endl;
		cout << setw(12) << "开卡人" << setw(26) << auth_query_getRealnameByID(head_adminList, p->adduid) << endl;
		if (p->isDel) strcpy(c_qcd_ta, "否");
		else strcpy(c_qcd_ta, "是");
		cout << setw(12) << "是否有效" << setw(26) << c_qcd_ta << endl;
	}
	else {
		cout << "未找到此卡！" << endl;
	}
	system("pause");
	system("cls");
	return end_cardList;
}

cardList* card_editCard(cardList* end_cardList, billStdList* head_billStdList, int nowAdminID)
{
	int cid, c;
	cardList* p = end_cardList;
	billStdList* q = head_billStdList;
	bool hasFound = false;
	char newPw[50];
	char bl_s_ct[25];
	struct tm* ttime;
	int newBS;
	cout << "请输入卡ID：";
	cin >> cid;
	while (1) {
		if (p == NULL) break;
		if (p->id == cid && !p->isDel) {
			hasFound = true;
			break;
		}
		p = p->prev;
	}
	if (hasFound) {
		while (1) {
			system("cls");
			cout << "卡号：" << p->showID << endl;
			cout << "1. 修改卡密码" << endl;
			cout << "2. 修改卡计费标准" << endl;
			cout << "0. 修改完成" << endl;
			cout << "请选择：";
			cin >> c;
			switch (c)
			{
			case 1:
				cout << "请输入新密码：";
				cin >> newPw;
				strcpy(p->password, newPw);
				cout << "修改成功！" << endl;
				break;
			case 2:
				adc_showbstd:system("cls");//这有一个标签
				cout << "计费标准列表：" << endl;
				cout << setw(6) << "ID" << setw(12) << "名称" << setw(26) << "创建时间" << setw(6) << "    标准" << endl;
				while (1) {
					if (q == NULL) break;
					if (q->isDel == true) {
						q = q->next;
						continue;
					}
					ttime = localtime(&q->stdCreateTime);
					strftime(bl_s_ct, sizeof(bl_s_ct), "%Y年%m月%d日 %H:%M:%S", ttime);
					cout << setw(6) << q->id << setw(12) << q->stdName << setw(26) << bl_s_ct << setw(6) << q->stdUnitCost * 1.0 / 100 << "/" << q->stdUnit << endl;
					q = q->next;
				}
				cout << "请选择计费标准ID：";
				cin >> newBS;
				q = head_billStdList;
				if (!billstd_query_isValid(head_billStdList, newBS)) goto adc_showbstd;//看看输入的ID存不存在
				p->billStd = newBS;
				cout << "修改成功！" << endl;
				break;
			case 0:
				break;
			default:
				cout << "请选择正确的选项！" << endl;
				break;
			}
			if (c == 0) break;
			system("pause");
		}
	}
	else {
		cout << "未找到卡或卡已被注销!" << endl;
		system("pause");
	}
	system("cls");
	return end_cardList;
}

cardList* card_delCard(cardList* end_cardList, int nowAdminID)
{
	int cid;
	system("cls");
	cout << "请输入要注销的卡号：";
	cin >> cid;
	end_cardList = card_do_delCard(end_cardList, cid, nowAdminID);
	system("pause");
	system("cls");
	return end_cardList;
}

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
		cout << "5. 修改卡密码/计费标准" << endl;
		cout << "0. 返回" << endl;
		cout << "请选择：" ;
		cin >> c;
		switch (c) {
		case 1:
			end_cardList = card_addCard(end_cardList, head_billStdList, cardMaxID, nowAdminID);
			break;
		case 2:
			end_cardList = card_delCard(end_cardList, nowAdminID);
			break;
		case 3:
			end_cardList = card_queryCardList(end_cardList, head_billStdList, head_adminList, nowAdminID);
			break;
		case 4:
			end_cardList = card_queryCardDetail(end_cardList, head_billStdList, head_adminList, nowAdminID);
			break;
		case 5:
			end_cardList = card_editCard(end_cardList, head_billStdList, nowAdminID);
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