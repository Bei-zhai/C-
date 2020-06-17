#pragma once

class mytime
{
public:
    int year;
    int month;
    int day;
    int hour;
    int minite;
    int second;
    int nowtime;

    mytime();
	mytime(int t,mytime*);
    void init(int type);
    bool isryear();
    bool isryear(int );
    void printtime();


};

