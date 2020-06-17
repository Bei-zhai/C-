#include "task.h"
#include<ctime>
#include <iostream>
#include<sstream>
#include<windows.h>
#include"colorprint.h"
task::task()
{
	taskname = "";
	tasktime = 0;
	start = new mytime();
	myskill.name="";
	myskill.totaltime = 0;
	finishtag = "未完成";
	type = "";
	//打卡任务用到的参数
	totalday = 0;
	 stringtime = "";
}

void task::init( int t,skill s)
{  
	//日常任务初始化的地方
		myskill.name = s.name;
		myskill.totaltime += t;
		tasktime += t;
		stringtime = "";
		start->init(0);
		start->printtime();	
		type = "日常任务";

}
void task::init(int t)
{
	//打卡任务初始化的地方
	myskill.name = "";
	myskill.totaltime = 0;
	totalday = t;
	alreadyday = 0;
	start->init(0);
	lasttime.init(start->nowtime);
	start->printtime();
	type = "打卡任务";
	stringtime = "";
}
//日常任务开始倒计时
void task::taskstart() {
	end = new mytime(tasktime,start);
	end->init(0);
	//个性化颜色
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
	std::cout << "\n任务正在倒计时，请专心完成自己的任务吧！！\n";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	while (true) {
		time_t temp= time(0);
		int t = temp;
		if (t > tasktime + start->nowtime)
			break;
	}
	finishtag = "已完成";
	//为什么这样加时间是加不上去的呢？
	//myskill.totaltime += tasktime;
	  
	 getstringtime();
	 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
	 std::cout << "\n恭喜你！，任务结束啦！！\n";
	 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	end->printtime();
}

void task::getstringtime()
{
	//获取打印时间
	int hour = tasktime / ( 60 * 60);	
	int minite = (tasktime % 3600) / 60;
	int second = tasktime % 60;
	if (hour != 0) {
		stringstream ss;
		//用到了stream流来将数字转换为字符串
		ss << hour;
		ss >> stringtime;
		stringtime += "时";
	}
	else if (minite != 0) {
		stringstream ss;
		//用到了stream流来将数字转换为字符串
		ss << minite;
		ss >> stringtime;
		stringtime += "分";
	}
	stringstream s;
	//用到了stream流来将数字转换为字符串
	s << second;
	s >> stringtime;
	stringtime += "秒";	
}
 void task::setchecktask(task & t)
{
	//获取当前时间
	mytime temp;
	temp.init(0);
	if (t.lasttime.nowtime == t.start->nowtime) {
		//第一次打卡
		t.lasttime.init(temp.nowtime);
		cout << "打卡任务的名字："<< t.taskname;
		cout << "当前时间：\n";
		t.alreadyday++;
		cout << "今日打卡已成功！！\n";
		return;
	}
	else if (t.lasttime.year <= temp.year)
		if (t.lasttime.month <= temp.month)
			if (t.lasttime.day < temp.day) {
				lasttime.init(0);
				alreadyday++;
				cout << "今日打卡已成功啦！！\n";
				return;
			}
			else if (t.lasttime.day == temp.day)
				colorprint::redprint("\n今天已经打过卡了哦！！\n");
}

