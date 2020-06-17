#include "skilllist.h"
#include <iostream>
#include<sstream>
using namespace std;

//构造函数
skilllist::skilllist()
{
	init();
}

void skilllist::init()
{	
	head = NULL;
	length = 0;
}

//析构函数
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

//得到链表长度
int skilllist::Length()
{
	return length;
}
//插入结点
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

//删除结点
void skilllist::Remove(string sname)
{
	int pos = Find(sname);
	if (pos == -1)
	{
		cout << "没找到这个技能诶~~" << endl;
		return;
	}
	if (pos == 1)
	{
		head = head->next;
		length--;
		cout << "该技能已删除" << endl;
		return;
	}
	int index = 2;
	Node* temp = head;
	while (index < pos)
		temp = temp->next;
	temp->next = temp->next->next;
	length--;
}

//查找结点位置
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
	return -1; //不存在返回-1
}

//打印链表
bool skilllist::Print()
{
	cout << "技能序号         "<<"技能名字"<<"          技能总时长(s)" << endl;
	if (head == NULL)
	{
		cout << "暂时没有已有技能诶" << endl;
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
			//按道理是不会走到这里的，因为序号已经严格限制在范围之内
			break;
	}
}

void skilllist::getstringtime(skill& s)
{
	//获取打印时间
	int hour = s.totaltime / (60 * 60);
	int minite = (s.totaltime % 3600) / 60;
	int second = s.totaltime % 60;
	if (hour != 0) {
		stringstream ss;
		//用到了stream流来将数字转换为字符串
		ss << hour;
		ss >> s.stringtotaltime;
		s.stringtotaltime += "时";
	}
	else if (minite != 0) {
		stringstream ss;
		//用到了stream流来将数字转换为字符串
		ss << minite;
		ss >> s.stringtotaltime;
		s.stringtotaltime += "分";
	}
	stringstream ss;
	//用到了stream流来将数字转换为字符串
	ss << second;
	ss >> s.stringtotaltime;
	s.stringtotaltime += "秒";
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
