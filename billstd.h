#pragma once
#include <ctime>

typedef struct billstd {
	int id;//ID��ʵ������
	char stdName[50];//�Ʒѱ�׼����
	time_t stdCreateTime;//����ʱ��
	char stdUnit;//�Ʒѵ�λ(�룺s���֣�m��ʱ��h)
	int stdUnitCost;//ÿ��λ����Ǯ, ��λ�Ƿ֣�1Ԫ��100
	struct billstd* next;
}billStdList;

//��ʾ�Ʒѱ�׼�˵�
billStdList* billstd_showMainMenu(billStdList* head_billStdList, int* billStdMaxID, int nowAdminID);
//���ӼƷѱ�׼
billStdList* billstd_do_addBillStd(billStdList* head_billStdList, char stdName[50], char stdUnit, int stdUnitCost, int* billStdMaxID, int nowAdminID);
billStdList* billstd_addBillStd(billStdList* head_billStdList, int* billStdMaxID, int nowAdminID);