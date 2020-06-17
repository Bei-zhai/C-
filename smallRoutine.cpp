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
	//������ɫ
		colorprint::yellowprint("��ӭ����С�ճ�~     ���ߣ�201830120207   sw\n") ;
		myskilllist.init();
		mytasklist.init ();
		handleMenu();
	}

void smallRoutine:: handleMenu()
	{
		while (1)
		{
			cout << "----------------------------" << endl;
			cout << "��ѡ�����в�����Ţ�~~       |" << endl;
			cout << "1.�鿴��ǰ����               |" << endl;
			cout << "2.���һ���ʱ����           |" << endl;
			cout << "3.���һ���               |"<< endl;
			cout << "4.���һ��ÿ�մ�����       |" << endl;
			cout << "5.�޸�һ����������           |" << endl;
			cout << "6.�鿴�����ܽ�               |" << endl;
			cout << "7.�鿴�����ܽ�               |" << endl;
			cout << "8.�鿴һ���ܽ�               |" << endl;
			cout << "9.�鿴���м���               |" << endl;
			cout << "10.ɾ�������¼              |" << endl;
			cout << "11.��                      |" << endl;
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
				colorprint::redprint("\n��ѡ���������е����Ŷ~~\n");
			}

		}
	}
	int  smallRoutine:: menuSelect()
	{
		//��ֹ����Ĳ�������
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
		/** �������Ա��õ�
		SYSTEMTIME now;
		GetLocalTime(&now);
		cout << "��ǰϵͳʱ�䣺" << now.wYear << "��" << now.wMonth<< "��"
			<< now.wDay << "��" << now.wHour<< "ʱ"
			<< now.wMinute << "��" << now.wSecond<< "��" << endl;**/
		string name;
		cout << "\n����רע��������ְ� \n";
		cin >> name;
		//goto���ʵ��ѭ��
		L1:cout << "\n��������רעʱ����~ \n" << "1.  15 ���� \n"
			<< "2.  25 ���� \n" << "3.  45 ���� \n" 
			<< "4.  60 ���� \n" << "5.  5 �� \n";
		int timechoice = menuSelect();
		int tasktime;
		switch (timechoice) {
		case 1:tasktime = 15 * 60;break;
		case 2:tasktime = 25 * 60;break;
		case 3:tasktime = 45 * 60;break;
		case 4:tasktime = 60 * 60;break;
		case 5:tasktime = 5;break;
			//��ֹϵͳ����
		default: 
			colorprint::redprint( "\n֮ǰ�����벻���Ϲ淶����������������ѡ���~\n");
			goto L1;
		}
		cout << "\n���ڵ����м��ܣ�\n";
	    bool hasskill=myskilllist.Print();

		//goto���
		L2:
			cout << "\n��ҪΪ�����½�һ��������  Y/N\n";
		string newskill = "";
		cin >> newskill;
		if (newskill != "Y" && newskill != "N") {
			colorprint::redprint("������Y/NŶ��\n");
			goto L2;
		}
		if (newskill == "Y") {
			tempskill=add_skill();
		}
		else if (hasskill) {
			L3:
			cout << "\n��������ѡ��һ�����Ţ࣬�������Ҫ������0��...\n";
			//����ѡ��,ͬʱ�з�����ʩ
			int choice = menuSelect();
			if (choice<0||choice > myskilllist.Length()) {
				colorprint::redprint("�����������е�ѡ���أ���\n");
				goto L3;
			}	
			if (choice != 0)
				tempskill = myskilllist.getskill(choice);
		}

		cout << "----------�������ڿ�ʼ��Ŷ---------- \n";
		task mytask;
		mytask.init(tasktime,tempskill);
		mytask.taskname = name;
		mytask.type = "�ճ�����";
		mytask.taskstart();
		myskilllist.settitaltime(tempskill, tasktime);
		mytasklist.Insert(mytask);
	}
	skill  smallRoutine::add_skill()
	{   
		skill tempskill;
		cout << "�����½��ļ������ְ�\n";
		cin >> tempskill.name;
		tempskill.totaltime = 0;
		myskilllist.Insert(tempskill.name);
		return tempskill;
	}
	void smallRoutine::add_everyday_record()
	{   
		task temptask;	
		cout << "\n���������������ְ�\n";
		cin >> temptask.taskname;		
        L4:
		cout << "\n��ѡ������ڰ�~(����)\n";
		//������ʩ
		int td=menuSelect();
		if (td<=0) {
			colorprint::redprint("������һ���������������Ŷ����");
			goto L4;
		}
		temptask.init(td);
		temptask.type = "������";
		mytasklist.Insert(temptask);
		mytasklist.seteverydayno();
	}
	void smallRoutine::modify_record()
	{
		if (mytasklist.Length() == 0){
			cout << "\nĿǰ�����û������Ŷ~\n";
			return;
		}
		L5:
		cout << "\n������Ҫ�޸ĵ��������Ű�\n" << endl;
		int choice1 = menuSelect();
		if (choice1 <= 0 || choice1 > mytasklist.Length()) {
			colorprint::redprint("\n�����ѡ�񳬳���ŷ�ΧŶ~\n");
			goto L5;
		}
		if (mytasklist.gettask(choice1).type == "�ճ�����") {
		L6:
			cout << "Ҫ�޸����������أ�\n1.��������\n2.������\n";
			int choice2 = menuSelect();
			if (choice2 != 1 && choice2 != 2) {
				colorprint::redprint("�����ѡ����Ϸ�ΧŶ~\n");
				goto L6;
			}
			else {
				switch (choice2) {
				case 1:cout << "�����µ����ְ�\n";
					cin >> mytasklist.Findtask(choice1).taskname;
					break;
				case 2: myskilllist.Print();
				L7:
					cout << "����ѡ��Ҫ�󶨵ļ�����Űɣ�\n";
					int skillchoice = 0;
					skillchoice = menuSelect();
					if (skillchoice <= 0 || skillchoice > myskilllist.Length()) {
						colorprint::redprint("û�����뷶Χ�ڵ���ŷ�Χ��\n");
						goto L7;
					}
					else {
						skill tempskill = myskilllist.getskill(skillchoice);
						mytasklist.Findtask(choice1).myskill = tempskill;
						cout << "�����޸ĳɹ���!\n";
					}
					break;
				}
			}
		}
		else {
			string tempname="";
			cout << "�����µ��������ְ�\n";
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
	//����һ����ASCLL��ֵ�ж�
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
		cout << "������ѡ��Ĵ���Űɣ���\n";
		int choice = -1;choice= menuSelect();
		if (choice <= 0 || choice > mytasklist.geteverydayno()) {
			colorprint::redprint("ѡ�����Ų��ڷ�Χ֮��Ŷ~\n");
			goto L9;
		}
		else if (!mytasklist.check(mytasklist.gettask(choice))) {
			colorprint::redprint("ѡ��Ĵ������Ѿ�������Ŷ����\n");
			goto L9;
		}
		else { 
			//��������
			 mytasklist.gettask(choice).setchecktask(mytasklist.gettask(choice));
		}
	}
	//����������stringstream�ж�

	bool isNum(string str)
	{
		stringstream sin(str);
		double d;
		char c;
		if (!(sin >> d))
		{
			/*���ͣ�
				sin>>t��ʾ��sinת����double�ı�������ʵ����int��float�͵Ķ�����գ���
				���ת���ɹ�����ֵΪ��0�����ת�����ɹ��ͷ���Ϊ0
			*/
			return false;
		}
		if (sin >> c)
		{
			/*���ͣ�
			�˲������ڼ����������У����ּ��ַ�����������ʽ�����磺34.f����������ĵĲ��֣�sin>>t��
			�Ѿ����ղ�ת������������ֲ��֣���stringstream����ӦҲ�����һ���ָ������
			��ʱ���յ���.f�ⲿ�֣�������������������false
			  */
			return false;
		}
		return true;
	}
