#pragma once
#include <ctime>
typedef struct charge {
	int id;//ID��ʵ������
	int cardID;//����
	int chargeType;//�仯��ʽ 1�ǳ�ֵ��2���˷�
	int charge;//�仯���˶���Ǯ����λ�Ƿ֣�һԪ100
	int adminID;//����ԱID
	time_t time;//����ʱ��
	struct bill* prev;
} chargeList;
