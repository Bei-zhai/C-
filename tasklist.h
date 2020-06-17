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
	
	//构造函数
	tasklist();
	//初始化
	void init();
	//插入结点
	void Insert(task val);
	//删除结点
	void Remove(task val);
	//得到链表长度
	int Length();
	//查找结点位置
	int Find(task val);
	//查找某个位置的元素
	task& Findtask(int num);
	//打印打卡任务列表
	void print_check();
	//打印日常任务链表
	void print_everyday();
	//确认打卡任务仍然有效
	bool check(task );
	//返回引用
	task& gettask(int index);
	void seteverydayno();
	int geteverydayno();
	//析构函数
	~tasklist();
private:
	Node* head;
	int length;
	//任务总序号
	int no;
	//打卡任务数量
	int everydayno;
};

