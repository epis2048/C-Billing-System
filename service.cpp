#include <iostream>
#include <iomanip>
#include <conio.h>
#include <sstream>
#include "service.h"
constexpr auto File_adminList = "data/adminList.dat";
constexpr auto File_billStdList = "data/billStdList.dat";
constexpr auto File_cardList = "data/cardList.dat";
using namespace std;

adminList* read_auth_adminList(int* adminMaxID)
{
	adminList* head_adminList = NULL;
	adminList* p;
	adminList* q;
	int id;
	char username[20];
	char realname[100];
	char password[50];
	time_t rlt;
	time_t ct;
	int authList[6] = { 0, 0, 0, 0, 0, 0 };
	//读取数据
	FILE* fp;
	int i;
	if ((fp = fopen(File_adminList, "r")) == NULL) {
		return false;
	}
	while (1) {
		//读取
		fscanf(fp, "%d", &id);
		if (id < 0) break;
		*(adminMaxID) = id;
		fscanf(fp, "%s", username);
		fscanf(fp, "%s", realname);
		fscanf(fp, "%s", password);
		fscanf(fp, "%lld", &rlt);
		fscanf(fp, "%lld", &ct);
		for (i = 0; i <= 5; i++) fscanf(fp, "%d", &authList[i]);
		//存链表
		p = (adminList*)malloc(sizeof(adminList));//申请内存
		if (p == NULL) {
			cout << "初始化失败！" << endl;
			system("pause");
			return NULL;
		}
		strcpy(p->username, username);
		strcpy(p->realname, realname);
		strcpy(p->password, password);
		p->id = id;
		p->createTime = ct;
		p->recentLoginTime = rlt;
		for (i = 0; i <= 5; i++) p->authList[i] = authList[i];
		p->next = NULL;
		//链表里插数据
		if (head_adminList == NULL) {
			head_adminList = p;
		}
		else {
			q = head_adminList;
			while (q->next != NULL) {
				q = q->next;
			}
			q->next = p;
		}
	}
	fclose(fp);
	return head_adminList;
}

billStdList* read_billStd_billStdList(int* billStdMaxID)
{
	billStdList* head_billStdList = NULL;
	billStdList* p;
	billStdList* q;
	int id;
	char stdName[50];
	time_t stdCreateTime;
	char stdUnit;
	int stdUnitCost;
	int delInt;
	bool isDel = false;
	//读取数据
	FILE* fp;
	int i;
	if ((fp = fopen(File_billStdList, "r")) == NULL) {
		cout << "初始化失败！" << endl;
		system("pause");
		return NULL;
	}
	while (1) {
		//读取
		fscanf(fp, "%d", &id);
		if (id < 0) break;
		*(billStdMaxID) = id;
		fscanf(fp, "%s", stdName);
		fscanf(fp, "%lld", &stdCreateTime);
		fscanf(fp, "%c", &stdUnit);//不吃回车是什么毛病
		fscanf(fp, "%c", &stdUnit);
		fscanf(fp, "%d", &stdUnitCost);
		fscanf(fp, "%d", &delInt);
		if (delInt == 1) isDel = true;
		else isDel = false;
		//存链表
		p = (billStdList*)malloc(sizeof(billStdList));//申请内存
		if (p == NULL) {
			cout << "初始化失败！" << endl;
			system("pause");
			return NULL;
		}
		strcpy(p->stdName, stdName);
		p->id = id;
		p->stdCreateTime = stdCreateTime;
		p->stdUnit = stdUnit;
		p->stdUnitCost = stdUnitCost;
		p->isDel = isDel;
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
	}
	fclose(fp);
	return head_billStdList;
}

cardList* read_card_cardList(int* cardMaxID)
{
	cardList* end_cardList = NULL;
	cardList* p;
	int id;//程序用卡号，实现自增
	char showID[7];//显示和输入卡号，六位，不足6位前面补0
	char password[50];//卡密码
	int balance;//余额，单位是分，一块钱100
	int billStd;//此卡的计费标准
	int totalCharge = 0;//累计消费钱数，单位是分，一块钱100
	int totalChargeTime = 0;//累计消费次数
	time_t creatTime;//开卡时间
	int adduid;//开卡管理员ID
	time_t recentBillTime;//上次消费时间，以结束时间计算
	time_t recentChargeTime;//上次充值时间
	int delInt;
	bool isDel = false;
	//读取数据
	FILE* fp;
	int i;
	if ((fp = fopen(File_cardList, "r")) == NULL) {
		cout << "初始化失败！" << endl;
		system("pause");
		return NULL;
	}
	while (1) {
		//读取
		fscanf(fp, "%d", &id);
		if (id < 0) break;
		if(id > * (cardMaxID)) *(cardMaxID) = id;
		fscanf(fp, "%s", showID);
		fscanf(fp, "%s", password);
		fscanf(fp, "%d", &balance);
		fscanf(fp, "%d", &billStd);
		fscanf(fp, "%d", &totalCharge);
		fscanf(fp, "%d", &totalChargeTime);
		fscanf(fp, "%lld", &creatTime);
		fscanf(fp, "%d", &adduid);
		fscanf(fp, "%lld", &recentBillTime);
		fscanf(fp, "%lld", &recentChargeTime);
		fscanf(fp, "%d", &delInt);
		if (delInt == 1) isDel = true;
		else isDel = false;
		//存链表
		p = (cardList*)malloc(sizeof(cardList));//申请内存
		if (p == NULL) {
			cout << "初始化失败！" << endl;
			system("pause");
			return NULL;
		}
		strcpy(p->showID, showID);
		strcpy(p->password, password);
		p->id = id;
		p->balance = balance;
		p->billStd = billStd;
		p->totalCharge = totalCharge;
		p->creatTime = creatTime;
		p->totalChargeTime = totalChargeTime;
		p->adduid = adduid;
		p->recentBillTime = recentBillTime;
		p->recentChargeTime = recentChargeTime;
		p->isDel = isDel;
		//链表里插数据
		p->prev = end_cardList;
		end_cardList = p;
	}
	fclose(fp);
	return end_cardList;
}

bool save_auth_adminList(adminList* head_adminList) {
	adminList* p = head_adminList;
	FILE* fp;
	int i;
	if ((fp = fopen(File_adminList, "w+")) == NULL) {
		return false;
	}
	while (1) {
		if (p == NULL) break;
		fprintf(fp, "%d\n", p->id);
		fprintf(fp, "%s\n", p->username);
		fprintf(fp, "%s\n", p->realname);
		fprintf(fp, "%s\n", p->password);
		fprintf(fp, "%lld\n", p->recentLoginTime);
		fprintf(fp, "%lld\n", p->createTime);
		for(i=0;i<=5;i++) fprintf(fp, "%d\n", p->authList[i]);
		p = p->next;
	}
	fprintf(fp, "-1\n");
	fclose(fp);
	return true;
}

bool save_billStd_billStdList(billStdList* head_billStdList) {
	billStdList* p = head_billStdList;
	FILE* fp;
	int i;
	if ((fp = fopen(File_billStdList, "w+")) == NULL) {
		return false;
	}
	while (1) {
		if (p == NULL) break;
		fprintf(fp, "%d\n", p->id);
		fprintf(fp, "%s\n", p->stdName);
		fprintf(fp, "%lld\n", p->stdCreateTime);
		fprintf(fp, "%c\n", p->stdUnit);
		fprintf(fp, "%d\n", p->stdUnitCost);
		fprintf(fp, "%d\n", p->isDel);
		p = p->next;
	}
	fprintf(fp, "-1\n");
	fclose(fp);
	return true;
}

bool save_card_cardList(cardList* end_cardList) {
	cardList* p = end_cardList;
	FILE* fp;
	int i;
	if ((fp = fopen(File_cardList, "w+")) == NULL) {
		return false;
	}
	while (1) {
		if (p == NULL) break;
		fprintf(fp, "%d\n", p->id);
		fprintf(fp, "%s\n", p->showID);
		fprintf(fp, "%s\n", p->password);
		fprintf(fp, "%d\n", p->balance);
		fprintf(fp, "%d\n", p->billStd);
		fprintf(fp, "%d\n", p->totalCharge);
		fprintf(fp, "%d\n", p->totalChargeTime);
		fprintf(fp, "%lld\n", p->creatTime);
		fprintf(fp, "%d\n", p->adduid);
		fprintf(fp, "%lld\n", p->recentBillTime);
		fprintf(fp, "%lld\n", p->recentChargeTime);
		fprintf(fp, "%d\n", p->isDel);
		p = p->prev;
	}
	fprintf(fp, "-1\n");
	fclose(fp);
	return true;
}

void save_showMainMenu(adminList* head_adminList, billStdList* head_billStdList, cardList* end_cardList, billList* end_billList, billUnfinishedList* head_billUnfinishedList, chargeList* end_chargeList)
{
	system("cls");
	cout << "数据保存：" << endl;
	//adminList
	cout << "保存adminList...";
	if (save_auth_adminList(head_adminList)) cout << " 成功！" << endl;
	else cout << " 失败！" << endl;
	//billStdList
	cout << "保存billStdList...";
	if (save_billStd_billStdList(head_billStdList)) cout << " 成功！" << endl;
	else cout << " 失败！" << endl;
	//cardList
	cout << "保存cardList...";
	if (save_card_cardList(end_cardList)) cout << " 成功！" << endl;
	else cout << " 失败！" << endl;
	//Finish
	cout << "保存完成！" << endl;
	system("pause");
}