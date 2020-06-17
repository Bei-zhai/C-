#pragma once
#include <string>
using namespace std;

	struct skill
	{
		string name;	//技能名字
		int totaltime;		//技能累计时长
		string stringtotaltime;//用来打印时长

	};
	//链表定义
	struct Node
	{
		skill val;
		Node* next;
		Node(skill x) :val(x), next(NULL) {
		}
	};

	class skilllist
	{
	public:

		//构造函数
		skilllist();
		//初始化
		void init();
		//插入结点
		void Insert(string name);
		//删除结点
		void Remove(string name);
		//得到链表长度
		int Length();
		//查找结点位置
		int Find(string name);
		//打印链表
		bool Print();
		//获取列表的第几个技能
		skill getskill(int);
		//获取打印时长
		void getstringtime(skill& s);
		//设置技能时长
		void settitaltime(skill s,int t);
		//析构函数
		~skilllist();
	private:
		Node* head;
		int length;
	};


