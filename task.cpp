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
	finishtag = "δ���";
	type = "";
	//�������õ��Ĳ���
	totalday = 0;
	 stringtime = "";
}

void task::init( int t,skill s)
{  
	//�ճ������ʼ���ĵط�
		myskill.name = s.name;
		myskill.totaltime += t;
		tasktime += t;
		stringtime = "";
		start->init(0);
		start->printtime();	
		type = "�ճ�����";

}
void task::init(int t)
{
	//�������ʼ���ĵط�
	myskill.name = "";
	myskill.totaltime = 0;
	totalday = t;
	alreadyday = 0;
	start->init(0);
	lasttime.init(start->nowtime);
	start->printtime();
	type = "������";
	stringtime = "";
}
//�ճ�����ʼ����ʱ
void task::taskstart() {
	end = new mytime(tasktime,start);
	end->init(0);
	//���Ի���ɫ
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
	std::cout << "\n�������ڵ���ʱ����ר������Լ�������ɣ���\n";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	while (true) {
		time_t temp= time(0);
		int t = temp;
		if (t > tasktime + start->nowtime)
			break;
	}
	finishtag = "�����";
	//Ϊʲô������ʱ���ǼӲ���ȥ���أ�
	//myskill.totaltime += tasktime;
	  
	 getstringtime();
	 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
	 std::cout << "\n��ϲ�㣡���������������\n";
	 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	end->printtime();
}

void task::getstringtime()
{
	//��ȡ��ӡʱ��
	int hour = tasktime / ( 60 * 60);	
	int minite = (tasktime % 3600) / 60;
	int second = tasktime % 60;
	if (hour != 0) {
		stringstream ss;
		//�õ���stream����������ת��Ϊ�ַ���
		ss << hour;
		ss >> stringtime;
		stringtime += "ʱ";
	}
	else if (minite != 0) {
		stringstream ss;
		//�õ���stream����������ת��Ϊ�ַ���
		ss << minite;
		ss >> stringtime;
		stringtime += "��";
	}
	stringstream s;
	//�õ���stream����������ת��Ϊ�ַ���
	s << second;
	s >> stringtime;
	stringtime += "��";	
}
 void task::setchecktask(task & t)
{
	//��ȡ��ǰʱ��
	mytime temp;
	temp.init(0);
	if (t.lasttime.nowtime == t.start->nowtime) {
		//��һ�δ�
		t.lasttime.init(temp.nowtime);
		cout << "����������֣�"<< t.taskname;
		cout << "��ǰʱ�䣺\n";
		t.alreadyday++;
		cout << "���մ��ѳɹ�����\n";
		return;
	}
	else if (t.lasttime.year <= temp.year)
		if (t.lasttime.month <= temp.month)
			if (t.lasttime.day < temp.day) {
				lasttime.init(0);
				alreadyday++;
				cout << "���մ��ѳɹ�������\n";
				return;
			}
			else if (t.lasttime.day == temp.day)
				colorprint::redprint("\n�����Ѿ��������Ŷ����\n");
}

