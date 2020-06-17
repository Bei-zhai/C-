#include "smallRoutine.h"
#include<iostream>
#include"mytime.h"
#include<windows.h>
#include"skilllist.h"
#include"task.h"
#include"tasklist.h"
#include<sstream>
#include"colorprint.h"


using namespace std;

smallRoutine::	smallRoutine() {
	//设置颜色
		colorprint::yellowprint("欢迎来到小日常~     作者：201830120207   sw\n") ;
		myskilllist.init();
		mytasklist.init ();
		handleMenu();
	}

void smallRoutine:: handleMenu()
	{
		while (1)
		{
			cout << "----------------------------" << endl;
			cout << "请选择下列操作序号⑧~~       |" << endl;
			cout << "1.查看当前任务               |" << endl;
			cout << "2.添加一项计时任务           |" << endl;
			cout << "3.添加一项技能               |"<< endl;
			cout << "4.添加一项每日打卡任务       |" << endl;
			cout << "5.修改一项任务设置           |" << endl;
			cout << "6.查看本周总结               |" << endl;
			cout << "7.查看本月总结               |" << endl;
			cout << "8.查看一年总结               |" << endl;
			cout << "9.查看所有技能               |" << endl;
			cout << "10.删除任务记录              |" << endl;
			cout << "11.打卡                      |" << endl;
			cout << "----------------------------" << endl;
			int choice = menuSelect();
			switch (choice)
			{
			case 1: {display_records();break;}
			case 2: {add_time_record();break;}
			case 3: {add_skill();break;}
			case 4: {add_everyday_record();break;}
			case 5: {modify_record();break;}
			case 6: {see_week();break;}
			case 7: {see_month();break;}
			case 8: {see_year();break;}
			case 9: {see_skill();break;}
			case 10: {delete_record();break;}
			case 11: {ding_record();break;}
			default:
				colorprint::redprint("\n请选择上面已有的序号哦~~\n");
			}

		}
	}
	int  smallRoutine:: menuSelect()
	{
		//防止输入的不是数字
		string n;
		cin >> n;
		int num = atoi(n.c_str());
		return num;
	}
	void smallRoutine:: display_records()
	{
		mytasklist.print_check();
		mytasklist.print_everyday();
	}
	void smallRoutine:: add_time_record()
	{
		skill tempskill;
		tempskill.name = "";
		tempskill.totaltime = 0;
		mytime* nowtimer = new mytime();
		nowtimer->init(0);
		nowtimer->printtime();
		/** 拿来作对比用的
		SYSTEMTIME now;
		GetLocalTime(&now);
		cout << "当前系统时间：" << now.wYear << "年" << now.wMonth<< "月"
			<< now.wDay << "日" << now.wHour<< "时"
			<< now.wMinute << "分" << now.wSecond<< "秒" << endl;**/
		string name;
		cout << "\n输入专注任务的名字吧 \n";
		cin >> name;
		//goto语句实现循环
		L1:cout << "\n设置任务专注时长吧~ \n" << "1.  15 分钟 \n"
			<< "2.  25 分钟 \n" << "3.  45 分钟 \n" 
			<< "4.  60 分钟 \n" << "5.  5 秒 \n";
		int timechoice = menuSelect();
		int tasktime;
		switch (timechoice) {
		case 1:tasktime = 15 * 60;break;
		case 2:tasktime = 25 * 60;break;
		case 3:tasktime = 45 * 60;break;
		case 4:tasktime = 60 * 60;break;
		case 5:tasktime = 5;break;
			//防止系统崩溃
		default: 
			colorprint::redprint( "\n之前的输入不符合规范，请重新输入您的选择吧~\n");
			goto L1;
		}
		cout << "\n现在的已有技能：\n";
	    bool hasskill=myskilllist.Print();

		//goto语句
		L2:
			cout << "\n需要为任务新建一个技能吗？  Y/N\n";
		string newskill = "";
		cin >> newskill;
		if (newskill != "Y" && newskill != "N") {
			colorprint::redprint("请输入Y/N哦！\n");
			goto L2;
		}
		if (newskill == "Y") {
			tempskill=add_skill();
		}
		else if (hasskill) {
			L3:
			cout << "\n那在上面选择一项技能序号⑧，如果不需要则输入0吧...\n";
			//输入选项,同时有防护措施
			int choice = menuSelect();
			if (choice<0||choice > myskilllist.Length()) {
				colorprint::redprint("请输入上面有的选项呢！！\n");
				goto L3;
			}	
			if (choice != 0)
				tempskill = myskilllist.getskill(choice);
		}

		cout << "----------任务现在开始了哦---------- \n";
		task mytask;
		mytask.init(tasktime,tempskill);
		mytask.taskname = name;
		mytask.type = "日常任务";
		mytask.taskstart();
		myskilllist.settitaltime(tempskill, tasktime);
		mytasklist.Insert(mytask);
	}
	skill  smallRoutine::add_skill()
	{   
		skill tempskill;
		cout << "输入新建的技能名字吧\n";
		cin >> tempskill.name;
		tempskill.totaltime = 0;
		myskilllist.Insert(tempskill.name);
		return tempskill;
	}
	void smallRoutine::add_everyday_record()
	{   
		task temptask;	
		cout << "\n请输入打卡任务的名字吧\n";
		cin >> temptask.taskname;		
        L4:
		cout << "\n请选择打卡周期吧~(天数)\n";
		//防护措施
		int td=menuSelect();
		if (td<=0) {
			colorprint::redprint("请输入一个正数代表打卡天数哦！！");
			goto L4;
		}
		temptask.init(td);
		temptask.type = "打卡任务";
		mytasklist.Insert(temptask);
		mytasklist.seteverydayno();
	}
	void smallRoutine::modify_record()
	{
		if (mytasklist.Length() == 0){
			cout << "\n目前任务表还没有任务哦~\n";
			return;
		}
		L5:
		cout << "\n请输入要修改的任务的序号吧\n" << endl;
		int choice1 = menuSelect();
		if (choice1 <= 0 || choice1 > mytasklist.Length()) {
			colorprint::redprint("\n输入的选择超出序号范围哦~\n");
			goto L5;
		}
		if (mytasklist.gettask(choice1).type == "日常任务") {
		L6:
			cout << "要修改哪项内容呢？\n1.任务名字\n2.任务技能\n";
			int choice2 = menuSelect();
			if (choice2 != 1 && choice2 != 2) {
				colorprint::redprint("输入的选项不符合范围哦~\n");
				goto L6;
			}
			else {
				switch (choice2) {
				case 1:cout << "输入新的名字吧\n";
					cin >> mytasklist.Findtask(choice1).taskname;
					break;
				case 2: myskilllist.Print();
				L7:
					cout << "输入选择要绑定的技能序号吧！\n";
					int skillchoice = 0;
					skillchoice = menuSelect();
					if (skillchoice <= 0 || skillchoice > myskilllist.Length()) {
						colorprint::redprint("没有输入范围内的序号范围诶\n");
						goto L7;
					}
					else {
						skill tempskill = myskilllist.getskill(skillchoice);
						mytasklist.Findtask(choice1).myskill = tempskill;
						cout << "技能修改成功啦!\n";
					}
					break;
				}
			}
		}
		else {
			string tempname="";
			cout << "输入新的任务名字吧\n";
			cin >> mytasklist.Findtask(choice1).taskname;
		}


	}
	void smallRoutine::see_month()
	{

	}
	void smallRoutine::see_week()
	{

	}
	void smallRoutine::see_year()
	{

	}
	void smallRoutine::see_skill() {
		myskilllist.Print();
	}
	//方法一：用ASCLL码值判断
	bool smallRoutine::AllisNum(string str)
	{

		for (int i = 0; i < str.size(); i++)
		{
			int tmp = (int)str[i];
			if (tmp >= 48 && tmp <= 57)
			{
				continue;
			}
			else
			{
				return false;
			}
		}
		return true;
	}
	void smallRoutine::delete_record()
	{
	}
	void smallRoutine::ding_record()
	{
		mytasklist.print_check();
		if (mytasklist.geteverydayno() == 0) {
			return;
		}
		L9:
		cout << "输入您选择的打卡序号吧！！\n";
		int choice = -1;choice= menuSelect();
		if (choice <= 0 || choice > mytasklist.geteverydayno()) {
			colorprint::redprint("选择的序号不在范围之内哦~\n");
			goto L9;
		}
		else if (!mytasklist.check(mytasklist.gettask(choice))) {
			colorprint::redprint("选择的打卡任务已经结束了哦！！\n");
			goto L9;
		}
		else { 
			//对象引用
			 mytasklist.gettask(choice).setchecktask(mytasklist.gettask(choice));
		}
	}
	//方法二，用stringstream判断

	bool isNum(string str)
	{
		stringstream sin(str);
		double d;
		char c;
		if (!(sin >> d))
		{
			/*解释：
				sin>>t表示把sin转换成double的变量（其实对于int和float型的都会接收），
				如果转换成功，则值为非0，如果转换不成功就返回为0
			*/
			return false;
		}
		if (sin >> c)
		{
			/*解释：
			此部分用于检测错误输入中，数字加字符串的输入形式（例如：34.f），在上面的的部分（sin>>t）
			已经接收并转换了输入的数字部分，在stringstream中相应也会把那一部分给清除，
			此时接收的是.f这部分，所以条件成立，返回false
			  */
			return false;
		}
		return true;
	}
