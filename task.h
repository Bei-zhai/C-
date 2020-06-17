#pragma once
#include<string>
#include"mytime.h"
#include"skilllist.h"
using namespace std;

class task
{public:
	//开始时间
	mytime* start;
	//结束时间
	mytime* end;
	//任务名字
	string taskname;
	//日常任务持续时间
	int tasktime;
	//打印用的将时间格式化
	string stringtime;
	//该任务的技能
	skill myskill;
	//该任务的类型，目前只有日常任务和打卡任务两种
	string type;
	//标志是否完成
	string finishtag;
	//打卡任务的总天数
	int totalday;
	//已打卡天数
	int alreadyday;
	//上一次打卡日期
	mytime lasttime;

	//构造函数
	task();
	//初始化日常任务
	void init(int,skill);
	//初始化打卡任务
	void init(int);
	//任务开始
	void taskstart();
	//得到任务时间的格式化转换表示
	void getstringtime();

	void setchecktask(task& t);

};

