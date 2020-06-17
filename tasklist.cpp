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

//析构函数
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

//得到链表长度
int tasklist::Length()
{
	return length;
}

//插入结点
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

//删除结点
void tasklist::Remove(task t)
{
	int pos = Find(t);
	if (pos == -1)
	{
		cout << "\n没找到这个任务诶~~" << endl;
		return;
	}
	if (pos != 1)
	{
		head = head->next;
		length--;
		cout << "\n该任务已删除" << endl;
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
	return -1; //不存在返回-1
}

task& tasklist::Findtask(int num)
{
	//序号是从1开始，索引是从0开始
	Node* temp = head;
	for (int i = 0;i < num;i++) {
		if (i == (num - 1))
			return temp->val;
		else
			temp = temp->next;
	}
}
//打卡任务优先打印
void tasklist::print_check()
{
	//每次进来先初始化
	no= 1;
	if (head == NULL)
	{
		cout << "\n暂时没有任务记录哦\n" << endl;
		return;
	}
	Node* temp = head;
	//输出信息的表头
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
	cout << "\n任务序号" << "  任务名字" << "     任务总时长" << "      任务类型" << "      完成状态" << "        起始时间\n" << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

	cout << "------------------------------------------------------------------" << endl;
	while (1) {
		if (temp->val.type == "打卡任务") {
			if (check(temp->val)) {
				cout << no << ". " << temp->val.taskname << "            " << temp->val.totalday << "天       "
					<< temp->val.type << "    已打卡天数： " << temp->val.alreadyday << "     ";
				temp->val.start->printtime();
			}
			else {
				cout <<no<<".  "<< temp->val.taskname << "            " << temp->val.totalday << "天       "
					<< temp->val.type << "    已完成,总天数： " << temp->val.alreadyday << "      ";
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

//打印日常任务链表
void tasklist::print_everyday()
{
	//防止重复输出
	if (head == NULL)
		return;
	Node* temp = head;
	while (1)
	{
		if (temp->val.type == "日常任务") {
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
	//获得当前日期
	mytime mychecktime;
	mychecktime.init(0);
	//作比较
	bool ischeck =((t.start->day+t.totalday)>=mychecktime.day);
	if (ischeck) {//更新数据
		return true;
	}
	return false;
}

task& tasklist::gettask(int index)
{
	//排列顺序其实是打卡任务优先，日常任务跟在后面，和链表的直接顺序不同，链表的直接顺序是任务创建顺序
	Node* temp = head;
	//i的序号其实和列表序号相同
	int i = 1;
	//优先查询一遍打卡任务
	while (1) {
		if (temp->val.type == "打卡任务") {
			if (i == index)
				return temp->val;
			else if (i < index && temp->next != NULL) {
				temp = temp->next;
				i++;
			}
			else
				//有序号范围限制，其实是一定找得到的
				break;
		}
		else if (temp->next != NULL)
			temp = temp->next;
		else
			break;
	}
	//查询一遍日常任务
	temp = head;
	while (1) {
		if (temp->val.type == "日常任务") {
			if (i == index)
				return temp->val;
			else if(i<index&&temp->next != NULL) {
				temp = temp->next;
				i++;
			}
			else
				//有序号范围限制，其实是一定找得到的
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

