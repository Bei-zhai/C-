#pragma once
#include<string>
#include"mytime.h"
#include"skilllist.h"
using namespace std;

class task
{public:
	//��ʼʱ��
	mytime* start;
	//����ʱ��
	mytime* end;
	//��������
	string taskname;
	//�ճ��������ʱ��
	int tasktime;
	//��ӡ�õĽ�ʱ���ʽ��
	string stringtime;
	//������ļ���
	skill myskill;
	//����������ͣ�Ŀǰֻ���ճ�����ʹ���������
	string type;
	//��־�Ƿ����
	string finishtag;
	//�������������
	int totalday;
	//�Ѵ�����
	int alreadyday;
	//��һ�δ�����
	mytime lasttime;

	//���캯��
	task();
	//��ʼ���ճ�����
	void init(int,skill);
	//��ʼ��������
	void init(int);
	//����ʼ
	void taskstart();
	//�õ�����ʱ��ĸ�ʽ��ת����ʾ
	void getstringtime();

	void setchecktask(task& t);

};

