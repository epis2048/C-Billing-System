#include <iostream>
#include <iomanip>
#include <conio.h>
#include <sstream>
#include "service.h"
#define File_adminList "data/adminList.txt"
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

void save_showMainMenu(adminList* head_adminList, billStdList* head_billStdList, cardList* end_cardList, billList* end_billList, billUnfinishedList* head_billUnfinishedList, chargeList* end_chargeList)
{
	system("cls");
	cout << "数据保存：" << endl;
	//adminList
	cout << "保存adminList...";
	if (save_auth_adminList(head_adminList)) cout << " 成功！" << endl;
	else cout << " 失败！" << endl;
	//billStdList
	//Finish
	cout << "保存完成！" << endl;
	system("pause");
}