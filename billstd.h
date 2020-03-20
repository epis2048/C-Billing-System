#pragma once
#include <ctime>

typedef struct billstd {
	int id;//ID��ʵ������
	char stdName[50];//�Ʒѱ�׼����
	time_t stdCreateTime;//����ʱ��
	char stdUnit;//�Ʒѵ�λ(�룺s���֣�m��ʱ��h)
	int stdUnitCost;//ÿ��λ����Ǯ, ��λ�Ƿ֣�1Ԫ��100
	bool isDel = false;
	struct billstd* next = NULL;
}billStdList;

//��ʾ�Ʒѱ�׼�˵�
billStdList* billstd_showMainMenu(billStdList* head_billStdList, int* billStdMaxID, int nowAdminID);
//��ӼƷѱ�׼
billStdList* billstd_do_addBillStd(billStdList* head_billStdList, char stdName[50], char stdUnit, int stdUnitCost, int* billStdMaxID, int nowAdminID);
billStdList* billstd_addBillStd(billStdList* head_billStdList, int* billStdMaxID, int nowAdminID);
//�༭�Ʒѱ�׼
billStdList* billstd_editBillStd(billStdList* head_billStdList, int nowAdminID);
//ɾ���Ʒѱ�׼
billStdList* billstd_do_delBillStd(billStdList* head_billStdList, int delID, int nowAdminID);
billStdList* billstd_delBillStd(billStdList* head_billStdList, int nowAdminID);
//API���
bool billstd_query_isValid(billStdList* head_billStdList, int stdID);//��ѯ�Ʒѱ�׼�Ƿ���Ч