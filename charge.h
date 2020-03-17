#pragma once
#include <ctime>
typedef struct charge {
	int id;//ID，实现自增
	int cardID;//卡号
	int chargeType;//变化形式 1是充值，2是退费
	int charge;//变化了了多少钱，单位是分，一元100
	int adminID;//管理员ID
	time_t time;//操作时间
	struct bill* prev;
} chargeList;
