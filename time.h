#pragma once
#include <iostream>
#include <fstream>
using namespace std;
class Time
{
private:
	int Day;
	int Hour;
public:
	Time(int A,int B) //call this in PT-ET
	{
		Day=A;
		Hour=B;
	}
	Time(int A) //call this Load/Unload Time
	{
		Day=0;
		Hour=A;
	}
	Time()
	{
		Day=0;
		Hour=0;
	}
	void SetDay(int D)
	{
		Day=D;
	}
	void SetHour(int H)
	{
		if(!Day)
		{
			Hour=H;
			Day=0;
		}
		else
			Hour=H;
	}
	int GetDay()
	{ return Day; }
	int GetHour()
	{return Hour;}
	bool operator == (const Time t)
	{
		if(t.Day==this->Day &&t.Hour==this->Hour)
			return true;
		else
			return false;
	}
	Time operator + (const Time t)
	{
		Time x;
		x.Day=this->Day+t.Day;
		x.Hour=this->Hour+t.Hour;
		if (x.Hour>23)
		{
			x.Hour=x.Hour-24;
			x.Day++;
		}
		return x;
	}
	Time operator +(const int y)
	{
		Time x;
		x.Day=this->Day;
		x.Hour=this->Hour + y;
		if (x.Hour>23)
		{
			x.Hour=x.Hour-24;
			x.Day++;
		}
		return x;
	}
	Time operator - (const Time t)
	{
		Time x;
		int sumx;
		int sum;
		x.Day = this->Day;
		x.Hour = this->Hour;
		sumx = t.Day * 24 + t.Hour;
		sum = x.Day * 24 + x.Hour;
		if (sumx >= sum)
		{
			x.Day = 0;
			x.Hour = 0;
			return x;
		}
		else
		{
			x.Day = (sum - sumx) / 24;
			x.Hour = (sum - sumx) % 24;
			return x;
		}
	}
	Time operator = (const int t)
	{
		Time x;
		x.Day=0;
		x.Hour=t;
		while(x.Hour>23)
		{
			x.Hour=x.Hour-24;
			x.Day++;
		}
		return x;
	}
	bool operator > (const Time T)
	{
		if(this->Day>T.Day)
			return true;
		else if(this->Day<T.Day)
			return false;
		else
		{
			if(this->Hour>T.Hour)
				return true;
			else
				return false;
		}
	}
	bool operator >= (const Time T)
	{
		if(this->Day>T.Day)
			return true;
		else if(this->Day<T.Day)
			return false;
		else
		{
			if(this->Hour>=T.Hour)
				return true;
			else
				return false;
		}
	}

	float operator - ()
	{
		return (0-(Day*24 + Hour)); 
	}


	friend ofstream& operator<<(ofstream& fs, Time &T)
	{

		fs << T.GetDay()<<":"<<T.GetHour() ;
		return fs;

	}

};