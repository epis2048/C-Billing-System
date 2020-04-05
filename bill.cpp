#include <iostream>
#include <ctime>
#include "bill.h"
#include "billstd.h"

using namespace std;

billUnfinishedList* bill_up(billUnfinishedList* head_billUnfinishedList, cardList* end_cardList, int nowAdminID)
{
	int cid;
	bool hasFoundCard = false;
	cardList* pcl = end_cardList;
	billUnfinishedList* p;
	billUnfinishedList* q;
	system("cls");
	cout << "上机" << endl;
	cout << "请输入卡号：";
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
			cout << "该卡正在上机！" << endl;
		}
		else {
			char cpw[50];
			cout << "请输入卡密码：";
			cin >> cpw;
			if (strcmp(cpw, pcl->password) == 0) {
				system("cls");
				if (pcl->balance < 0) {
					cout << "该卡余额不足！" << endl;
				}
				else {
					p = (billUnfinishedList*)malloc(sizeof(billUnfinishedList));//申请内存
					if (p == NULL) {
						cout << "上机失败！" << endl;
					}
					else {
						std::time_t t = std::time(0);
						p->cardID = pcl->id;
						p->stdID = pcl->billStd;
						p->upAdminID = nowAdminID;
						p->upTime = t;
						p->next = NULL;
						//链表里插数据
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
						cout << "上机成功！" << endl;
					}
				}
			}
			else {
				cout << "卡密码错误！" << endl;
			}
		}
	}
	else {
		cout << "没有找到该卡！" << endl;
	}
	system("pause");
	system("cls");
	return head_billUnfinishedList;
}

billList* bill_down(billList* end_billList, billUnfinishedList** head_billUnfinishedList, cardList* end_cardList, billStdList* head_billStdList, int nowAdminID, int* billMaxID)
{
	int cid;
	system("cls");
	cout << "下机" << endl << "请输入卡号：";
	cin >> cid;
	//查询该卡的上机记录
	bool hasFoundBul = false;
	billUnfinishedList* bul = *head_billUnfinishedList;
	while (1) {
		if (bul == NULL) break;
		if (bul->cardID == cid) {
			hasFoundBul = true;
			break;
		}
		bul = bul->next;
	}
	//查询卡
	bool hasFoundCard = false;
	cardList* cl = end_cardList;
	while (1)
	{
		if (cl == NULL) break;
		if (cl->id == cid) {
			hasFoundCard = true;
			break;
		}
		cl = cl->prev;
	}
	if (hasFoundBul && hasFoundCard) {
		//输入密码
		char inpw[50];
		cout << "请输入卡密码：";
		cin >> inpw;
		if (strcmp(inpw, cl->password) == 0) {
			system("cls");
			char b_bd_st[25];
			struct tm* ttime;
			time_t tnow = time(0);
			//获取当前时间
			ttime = localtime(&bul->upTime);
			strftime(b_bd_st, sizeof(b_bd_st), "%Y年%m月%d日 %H:%M:%S", ttime);
			cout << "上机时间：" << b_bd_st << endl;
			ttime = localtime(&tnow);
			strftime(b_bd_st, sizeof(b_bd_st), "%Y年%m月%d日 %H:%M:%S", ttime);
			cout << "当前时间：" << b_bd_st << endl;
			//计算上机时长
			long sec;
			float min;
			float hour;
			sec = tnow - bul->upTime;
			min = sec * 1.0 / 60;
			hour = min / 60;
			cout << "您一共上了 " << (int)hour << "小时" << (int)(min - ((int)hour) * 60) << "分" << (int)(sec - ((int)min) * 60) << "秒" << endl;
			//获取计费标准
			billStdList* bsl = head_billStdList;
			bool hasFoundBsl = false;
			while (1) {
				if (bsl == NULL) break;
				if (bsl->id == bul->stdID) {
					hasFoundBsl = true;
					break;
				}
				bsl = bsl->next;
			}
			if (hasFoundBsl) {
				billList* p;
				p = (billList*)malloc(sizeof(billList));//申请内存
				if (p == NULL) {
					cout << "下机失败！" << endl;
				}
				else {
					string showBsl;
					showBsl = bsl->stdName;
					showBsl = showBsl + ": ";
					showBsl = showBsl + intTranStr(bsl->stdUnitCost * 1.0 / 100) + '/' + bsl->stdUnit;
					if (bsl->isDel) showBsl = showBsl + " (已失效)";
					cout << "您的计费标准是：" << showBsl << endl;
					//扣费
					int cost;
					if (bsl->stdUnit == 'm') {
						cost = min * bsl->stdUnitCost;
					}
					else if (bsl->stdUnit == 'h') {
						cost = hour * bsl->stdUnitCost;
					}
					else {
						cost = sec * bsl->stdUnitCost;
					}
					cout << "扣费前余额：" << cl->balance * 1.0 / 100 << endl;
					cout << "根据您的计费标准，您本次花费了：" << cost * 1.0 / 100 << endl;
					cl->balance -= cost;
					cout << "扣费后余额：" << cl->balance * 1.0 / 100 << endl;
					if (cl->balance < 0) {
						cout << "该卡已欠费！" << endl;
					}
					//保存记录
					cl->recentBillTime = tnow;
					cl->totalCharge += cost;
					cl->totalChargeTime++;
					p->cardID = cid;
					p->cost = cost;
					p->downAdminID = nowAdminID;
					p->downTime = tnow;
					p->stdID = bsl->id;
					p->stdUnit = bsl->stdUnit;
					p->stdUnitCost = bsl->stdUnitCost;
					p->upAdminID = bul->upAdminID;
					p->upTime = bul->upTime;
					(*billMaxID)++;
					p->id = *billMaxID;
					p->prev = end_billList;
					end_billList = p;
					//删除正在上机的记录
					billUnfinishedList* q = *head_billUnfinishedList;
					billUnfinishedList* t = *head_billUnfinishedList;
					if (q != NULL) {
						if (q->cardID == cid) *head_billUnfinishedList = q->next;
						else {
							while (1) {
								if (q->cardID == cid) {
									break;
								}
								else {
									t = q;
								}
								q = q->next;
							}
							t->next = q->next;
							free(q);
						}
					}
				}
			}
			else {
				cout << "找不到计费标准！" << endl;
			}
		}
		else {
			cout << "卡密码错误！" << endl;
		}
	}
	else {
		cout << "卡号不存在或者该卡不在上机" << endl;
	}
	system("pause");
	system("cls");
	return end_billList;
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