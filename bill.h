#pragma once
#include <ctime>
typedef struct bill {
	int id;//ID，实现自增
	int stdID;//计费标准ID
	int cardID;//卡号
	int cost;//花费了多少钱，单位是分，一元100
	int upAdminID;//上机管理员ID
	time_t upTime;//上机时间
	int downAdminID;//下机管理员ID
	time_t downTime;//下机时间
	struct bill* prev;
} billList;

typedef struct billunfinish {
	int stdID;//计费标准ID
	int cardID;//卡号
	int upAdminID;//上机管理员ID
	time_t upTime;//上机时间
	struct billunfinish* next;
} billUnfinishedList;