#pragma once
#include <ctime>
typedef struct bill {
	int id;//ID��ʵ������
	int stdID;//�Ʒѱ�׼ID
	int cardID;//����
	int cost;//�����˶���Ǯ����λ�Ƿ֣�һԪ100
	int upAdminID;//�ϻ�����ԱID
	time_t upTime;//�ϻ�ʱ��
	int downAdminID;//�»�����ԱID
	time_t downTime;//�»�ʱ��
	struct bill* prev;
} billList;

typedef struct billunfinish {
	int stdID;//�Ʒѱ�׼ID
	int cardID;//����
	int upAdminID;//�ϻ�����ԱID
	time_t upTime;//�ϻ�ʱ��
	struct billunfinish* next;
} billUnfinishedList;