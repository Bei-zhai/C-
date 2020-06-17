#include "tasklist.h"
#include <iostream>
#include<windows.h>
#include"colorprint.h"
//using namespace std;


tasklist::tasklist()
{
	init();
}

void tasklist::init()
{head = NULL;
	length = 0;
	no = 1;
	everydayno = 0;
}

//��������
tasklist::~tasklist()
{
	Node* temp;
	for (int i = 0;i < length;i++)
	{
		temp = head;
		head = head->next;
		delete temp;
	}
}

//�õ�������
int tasklist::Length()
{
	return length;
}

//������
void tasklist::Insert(task t)
{
	Node* temp = head;
	Node* node = new Node(t);
	if (head == NULL) {
		head=node;	
		length++;
		return;
	}
	for (;temp->next != NULL;temp = temp->next);
	temp->next = node;
	node->next = NULL;
	length++;
}

//ɾ�����
void tasklist::Remove(task t)
{
	int pos = Find(t);
	if (pos == -1)
	{
		cout << "\nû�ҵ����������~~" << endl;
		return;
	}
	if (pos != 1)
	{
		head = head->next;
		length--;
		cout << "\n��������ɾ��" << endl;
		return;
	}
	int index = 2;
	Node* temp = head;
	while (index < pos)
		temp = temp->next;
	temp->next = temp->next->next;
	length--;
}

//���ҽ��λ��
int tasklist::Find(task t)
{
	Node* temp = head;
	int index = 0;
	while (head != NULL)
	{   
		index++;
		task tm = temp->val;
		if (t.taskname==tm.taskname)
			return index;
		if (temp->next != NULL) {
			temp = temp->next;
		}
		else
			return -1;
	}
	return -1; //�����ڷ���-1
}

task& tasklist::Findtask(int num)
{
	//����Ǵ�1��ʼ�������Ǵ�0��ʼ
	Node* temp = head;
	for (int i = 0;i < num;i++) {
		if (i == (num - 1))
			return temp->val;
		else
			temp = temp->next;
	}
}
//���������ȴ�ӡ
void tasklist::print_check()
{
	//ÿ�ν����ȳ�ʼ��
	no= 1;
	if (head == NULL)
	{
		cout << "\n��ʱû�������¼Ŷ\n" << endl;
		return;
	}
	Node* temp = head;
	//�����Ϣ�ı�ͷ
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
	cout << "\n�������" << "  ��������" << "     ������ʱ��" << "      ��������" << "      ���״̬" << "        ��ʼʱ��\n" << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

	cout << "------------------------------------------------------------------" << endl;
	while (1) {
		if (temp->val.type == "������") {
			if (check(temp->val)) {
				cout << no << ". " << temp->val.taskname << "            " << temp->val.totalday << "��       "
					<< temp->val.type << "    �Ѵ������� " << temp->val.alreadyday << "     ";
				temp->val.start->printtime();
			}
			else {
				cout <<no<<".  "<< temp->val.taskname << "            " << temp->val.totalday << "��       "
					<< temp->val.type << "    �����,�������� " << temp->val.alreadyday << "      ";
				temp->val.start->printtime();
			}

			no++;
		}
		if (temp->next == NULL)
				break;
			else 
				temp = temp->next;
	}
}

//��ӡ�ճ���������
void tasklist::print_everyday()
{
	//��ֹ�ظ����
	if (head == NULL)
		return;
	Node* temp = head;
	while (1)
	{
		if (temp->val.type == "�ճ�����") {
			cout << no << ". " << temp->val.taskname << "            " << temp->val.stringtime << "        "
				<< temp->val.type << "        " << temp->val.finishtag << "     ";
			temp->val.start->printtime(); 
			no++;
		}
		if (temp->next == NULL)
				break;
		else 
			temp = temp->next;		
	}
	cout << endl;
}

bool tasklist::check(task t)
{
	//��õ�ǰ����
	mytime mychecktime;
	mychecktime.init(0);
	//���Ƚ�
	bool ischeck =((t.start->day+t.totalday)>=mychecktime.day);
	if (ischeck) {//��������
		return true;
	}
	return false;
}

task& tasklist::gettask(int index)
{
	//����˳����ʵ�Ǵ��������ȣ��ճ�������ں��棬�������ֱ��˳��ͬ�������ֱ��˳�������񴴽�˳��
	Node* temp = head;
	//i�������ʵ���б������ͬ
	int i = 1;
	//���Ȳ�ѯһ�������
	while (1) {
		if (temp->val.type == "������") {
			if (i == index)
				return temp->val;
			else if (i < index && temp->next != NULL) {
				temp = temp->next;
				i++;
			}
			else
				//����ŷ�Χ���ƣ���ʵ��һ���ҵõ���
				break;
		}
		else if (temp->next != NULL)
			temp = temp->next;
		else
			break;
	}
	//��ѯһ���ճ�����
	temp = head;
	while (1) {
		if (temp->val.type == "�ճ�����") {
			if (i == index)
				return temp->val;
			else if(i<index&&temp->next != NULL) {
				temp = temp->next;
				i++;
			}
			else
				//����ŷ�Χ���ƣ���ʵ��һ���ҵõ���
				break;
		}
		else if (temp->next != NULL)
			temp = temp->next;
		else
			break;
	}
	return temp->val;
}

void tasklist::seteverydayno()
{
	everydayno++;
}

int tasklist::geteverydayno()
{
	return everydayno;
}

