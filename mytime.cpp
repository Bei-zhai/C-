#include "mytime.h"
#include<ctime>
#include <iostream>
mytime::mytime() {
	time_t nowtime = time(0);
	mytime::nowtime = nowtime;
	mytime::year = 0;
	mytime::month = 0;
	mytime::day= 0;
	mytime::hour = 0;
	mytime::minite = 0;
	mytime::second= 0;
}
mytime::mytime(int t,mytime* m) {
	mytime::nowtime = m->nowtime+t;
	mytime::year = 0;
	mytime::month = 0;
	mytime::day = 0;
	mytime::hour = 0;
	mytime::minite = 0;
	mytime::second = 0;
}
void mytime::init(int type)
{
	const int anhour = 60 * 60;
	const int aday = 24 * anhour;
	mytime::year = 1970;
	int time=0;
	if (type == 0) {
		//����ʱ��Ա��ҵ�����汾��vs������ǵ�1970��1��1��8ʱ����ʱ��
		time = nowtime + 8 * anhour;
	}
	else {
		//ͨ��ֱ�Ӹ�������ֵʱ��
		nowtime = type;
		time = type + 8 * anhour;
	}
        
	for ( ;;) {
		if (this->isryear()) {
			if (time - 366 * aday >= 0)
			{
				time -= 366 * aday;
				mytime::year++;
				continue;
			}
		}
		else if (time - 365 * aday >= 0)
		{
			time -= 365 * aday;
			mytime::year++;
			continue;
		}
		break;
	}
	mytime::day = 0;
	for (;time >= aday;mytime::day++)
		time -= aday;
	
	//���·�
	mytime::month = 1;
	int rmonth[] = { 31,29,31,30,31,30,31,31,30,31,30,31 };
	int month[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	for (int y = 1970;y <= mytime::year;y++) {
		if (this->isryear(y)) {
			for (int i = 0;;i++) {
				if (mytime::day - rmonth[i] > 0) {
					mytime::day -= rmonth[i];
					mytime::month++;
					continue;
				}
				else
					break;
			}

		}
		else {
			for (int i = 0;;i++) {
				if (mytime::day - month[i] > 0) {
					mytime::day -= month[i];
					mytime::month++;
					continue;
				}
				else
					break;
			}
			mytime::hour = time / anhour;
			mytime::minite = (time % anhour) / 60;
			mytime::second = (time % anhour) % 60;

		}
	}
}

bool mytime::isryear()
{
	
	if (mytime::year % 4 != 0) return false;
	else {
		if (mytime::year % 100 == 0 && mytime::year % 400 != 0) return false;
		if (mytime::year % 3200 == 0) return false;

		return true;
	}
}

bool mytime::isryear(int t)
{
	if (t % 4 != 0) return false;
	else {
		if (t % 100 == 0 &&t % 400 != 0) return false;
		if (t % 3200 == 0) return false;

		return true;
	}
}

void mytime::printtime()
{
	std::cout <<  mytime::year << "��" << mytime::month << "��"
		<< mytime::day << "��" << mytime::hour << "ʱ"
		<< mytime::minite << "��" << mytime::second << "��" << std::endl;
}
