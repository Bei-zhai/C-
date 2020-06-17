#include "skilllist.h"
#include <iostream>
#include<sstream>
using namespace std;

//���캯��
skilllist::skilllist()
{
	init();
}

void skilllist::init()
{	
	head = NULL;
	length = 0;
}

//��������
skilllist::~skilllist()
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
int skilllist::Length()
{
	return length;
}
//������
void skilllist::Insert(string sname)
{
	skill tempskill;
	tempskill.name = sname;
	tempskill.totaltime = 0;
	Node* headtemp =new  Node(tempskill);
	if (head == NULL) {
		head =headtemp ;
		length++;
		return;
	}
	Node* temp = head;
	for (;temp->next != NULL;temp = temp->next);
	temp->next = headtemp;
	headtemp->next = NULL;
	length++;
}

//ɾ�����
void skilllist::Remove(string sname)
{
	int pos = Find(sname);
	if (pos == -1)
	{
		cout << "û�ҵ����������~~" << endl;
		return;
	}
	if (pos == 1)
	{
		head = head->next;
		length--;
		cout << "�ü�����ɾ��" << endl;
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
int skilllist::Find(string sname)
{
	Node* temp = head;
	int index = 1;
	while (temp != NULL)
	{
		if (temp->val.name == sname )
			return index;
		temp = temp->next;
		index++;
	}
	return -1; //�����ڷ���-1
}

//��ӡ����
bool skilllist::Print()
{
	cout << "�������         "<<"��������"<<"          ������ʱ��(s)" << endl;
	if (head == NULL)
	{
		cout << "��ʱû�����м�����" << endl;
		return false;
	}
	Node* temp = head;
	int t = 0;
	while (temp != NULL)
	{
		t++;
		cout << t << ". " << temp->val.name << "        ";
		getstringtime(temp->val);
		temp = temp->next;
	}
	cout << endl;
	return true;
}

skill skilllist::getskill(int i)
{
	Node* temp = head;
	for (int t = 0;t <i;t++) {
		if (t == (i - 1)) {
			return temp->val;
		}
		else if (temp->next != NULL)
			temp = temp->next;
		else
			//�������ǲ����ߵ�����ģ���Ϊ����Ѿ��ϸ������ڷ�Χ֮��
			break;
	}
}

void skilllist::getstringtime(skill& s)
{
	//��ȡ��ӡʱ��
	int hour = s.totaltime / (60 * 60);
	int minite = (s.totaltime % 3600) / 60;
	int second = s.totaltime % 60;
	if (hour != 0) {
		stringstream ss;
		//�õ���stream����������ת��Ϊ�ַ���
		ss << hour;
		ss >> s.stringtotaltime;
		s.stringtotaltime += "ʱ";
	}
	else if (minite != 0) {
		stringstream ss;
		//�õ���stream����������ת��Ϊ�ַ���
		ss << minite;
		ss >> s.stringtotaltime;
		s.stringtotaltime += "��";
	}
	stringstream ss;
	//�õ���stream����������ת��Ϊ�ַ���
	ss << second;
	ss >> s.stringtotaltime;
	s.stringtotaltime += "��";
	cout << s.stringtotaltime << endl;
}

 void skilllist::settitaltime(skill s,int t)
{
	 Node* temp = head;
	while (true) {
		if (temp->val.name == s.name) {
			temp->val.totaltime += t;
			return;
		}
		else
			temp = temp->next;
	}
}
