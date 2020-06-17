#pragma once
#include"task.h"
class tasklist
{
	struct Node
	{
		task val;
		Node* next;
		Node(task x) :val(x), next(NULL) {};
		Node() :val(), next(NULL) {};
	};

public:
	
	//���캯��
	tasklist();
	//��ʼ��
	void init();
	//������
	void Insert(task val);
	//ɾ�����
	void Remove(task val);
	//�õ�������
	int Length();
	//���ҽ��λ��
	int Find(task val);
	//����ĳ��λ�õ�Ԫ��
	task& Findtask(int num);
	//��ӡ�������б�
	void print_check();
	//��ӡ�ճ���������
	void print_everyday();
	//ȷ�ϴ�������Ȼ��Ч
	bool check(task );
	//��������
	task& gettask(int index);
	void seteverydayno();
	int geteverydayno();
	//��������
	~tasklist();
private:
	Node* head;
	int length;
	//���������
	int no;
	//����������
	int everydayno;
};

