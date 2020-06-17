#pragma once
#include<string>
#include"tasklist.h"
#include "skilllist.h"
using namespace std;
class smallRoutine {
public:
	//构造函数
	smallRoutine();
	//记录所有的技能
	skilllist myskilllist;
	//记录所有的任务
	tasklist mytasklist ;
	//调用相应方法
	void handleMenu();
	//解决输入选项必须为数字，可复用
	int menuSelect();
	//展示所有记录
	void display_records();
	//添加日常任务
	void add_time_record();
	//添加技能
	skill add_skill();
	//添加打卡任务
	void add_everyday_record();
	//修改任务记录，包括名字和技能
	void modify_record();
	//展示一周记录
	void see_week();
	//展示一个月的记录
	void see_month();
	//展示一年的记录
	void see_year();
	//展示所有技能的专注时间
	void see_skill();
	//限制只能输入数字的备用方法
	bool AllisNum(string);
	//删除某条记录
	void delete_record();
	//打卡
	void ding_record();
};