#pragma once
#include <ctime>

typedef struct billstd {
	int id;//ID，实现自增
	char stdName[50];//计费标准名称
	time_t stdCreateTime;//创建时间
	char stdUnit;//计费单位(秒：s、分：m、时：h)
	int stdUnitCost;//每单位多少钱, 单位是分，1元是100
	bool isDel = false;
	struct billstd* next = NULL;
}billStdList;

//显示计费标准菜单
billStdList* billstd_showMainMenu(billStdList* head_billStdList, int* billStdMaxID, int nowAdminID);
//添加计费标准
billStdList* billstd_do_addBillStd(billStdList* head_billStdList, char stdName[50], char stdUnit, int stdUnitCost, int* billStdMaxID, int nowAdminID);
billStdList* billstd_addBillStd(billStdList* head_billStdList, int* billStdMaxID, int nowAdminID);
//编辑计费标准
billStdList* billstd_editBillStd(billStdList* head_billStdList, int nowAdminID);
//删除计费标准
billStdList* billstd_do_delBillStd(billStdList* head_billStdList, int delID, int nowAdminID);
billStdList* billstd_delBillStd(billStdList* head_billStdList, int nowAdminID);
//API相关
bool billstd_query_isValid(billStdList* head_billStdList, int stdID);//查询计费标准是否有效