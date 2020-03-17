#pragma once
#include <ctime>

typedef struct admin{
	int id;
	char username[20];//用户名，登陆用
	char realname[100];//真实姓名，显示用
	char password[50];//密码，后期以md5存储
	time_t recentLoginTime;//最近登陆时间，存储为时间戳
	time_t createTime;//账户创建时间，存储为时间戳
	int authList[6] = { 0, 0, 0, 0, 0, 0 };//权限列表
	struct admin* next = NULL;
} adminList;
/*
AuthList说明
0 超级管理员
1 上下机
2 充值退费
3 卡管理
4 计费标准管理
5 日志查询
*/

//输入时隐藏密码
void inputPassword(char password[50], int size);
//获取登陆状态
int auth_checkStatus(adminList* head_adminList, int nowAdminID);
//登录
int auth_login(adminList* head_adminList);
//检查是否有某项的权限
int auth_checkHasAuth(adminList* head_adminList, int nowAdminID, int authID);

//显示权限管理主菜单
adminList* auth_showMainMenu(adminList* head_adminList, int* adminMaxID, int nowAdminID);
//查询管理员
int auth_queryAdminDetail(adminList* head_adminList);
//添加管理员
adminList* auth_do_addAdmin(adminList* head_adminList, char username[20], char realname[100], char password[50], int isSuperAdmin, int* adminMaxID, int nowAdminID);
adminList* auth_addAdmin(adminList* head_adminList, int* adminMaxID, int nowAdminID);
//编辑管理员
adminList* auth_editAdmin(adminList* head_adminList, int nowAdminID);
//删除管理员
adminList* auth_do_delAdmin(adminList* head_adminList, int delID, int nowAdminID);
adminList* auth_delAdmin(adminList* head_adminList, int nowAdminID);


