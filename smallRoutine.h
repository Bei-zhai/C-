#pragma once
#include<string>
#include"tasklist.h"
#include "skilllist.h"
using namespace std;
class smallRoutine {
public:
	//���캯��
	smallRoutine();
	//��¼���еļ���
	skilllist myskilllist;
	//��¼���е�����
	tasklist mytasklist ;
	//������Ӧ����
	void handleMenu();
	//�������ѡ�����Ϊ���֣��ɸ���
	int menuSelect();
	//չʾ���м�¼
	void display_records();
	//����ճ�����
	void add_time_record();
	//��Ӽ���
	skill add_skill();
	//��Ӵ�����
	void add_everyday_record();
	//�޸������¼���������ֺͼ���
	void modify_record();
	//չʾһ�ܼ�¼
	void see_week();
	//չʾһ���µļ�¼
	void see_month();
	//չʾһ��ļ�¼
	void see_year();
	//չʾ���м��ܵ�רעʱ��
	void see_skill();
	//����ֻ���������ֵı��÷���
	bool AllisNum(string);
	//ɾ��ĳ����¼
	void delete_record();
	//��
	void ding_record();
};