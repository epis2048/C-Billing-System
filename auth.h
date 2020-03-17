#pragma once
#include <ctime>

typedef struct admin{
	int id;
	char username[20];//�û�������½��
	char realname[100];//��ʵ��������ʾ��
	char password[50];//���룬������md5�洢
	time_t recentLoginTime;//�����½ʱ�䣬�洢Ϊʱ���
	time_t createTime;//�˻�����ʱ�䣬�洢Ϊʱ���
	int authList[6] = { 0, 0, 0, 0, 0, 0 };//Ȩ���б�
	struct admin* next = NULL;
} adminList;
/*
AuthList˵��
0 ��������Ա
1 ���»�
2 ��ֵ�˷�
3 ������
4 �Ʒѱ�׼����
5 ��־��ѯ
*/

//����ʱ��������
void inputPassword(char password[50], int size);
//��ȡ��½״̬
int auth_checkStatus(adminList* head_adminList, int nowAdminID);
//��¼
int auth_login(adminList* head_adminList);
//����Ƿ���ĳ���Ȩ��
int auth_checkHasAuth(adminList* head_adminList, int nowAdminID, int authID);

//��ʾȨ�޹������˵�
adminList* auth_showMainMenu(adminList* head_adminList, int* adminMaxID, int nowAdminID);
//��ѯ����Ա
int auth_queryAdminDetail(adminList* head_adminList);
//��ӹ���Ա
adminList* auth_do_addAdmin(adminList* head_adminList, char username[20], char realname[100], char password[50], int isSuperAdmin, int* adminMaxID, int nowAdminID);
adminList* auth_addAdmin(adminList* head_adminList, int* adminMaxID, int nowAdminID);
//�༭����Ա
adminList* auth_editAdmin(adminList* head_adminList, int nowAdminID);
//ɾ������Ա
adminList* auth_do_delAdmin(adminList* head_adminList, int delID, int nowAdminID);
adminList* auth_delAdmin(adminList* head_adminList, int nowAdminID);


