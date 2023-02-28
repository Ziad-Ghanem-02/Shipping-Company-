#include "Time.h"
#include <fstream>
#include "DEFS.h"
#include <iostream>
using namespace std;

#ifndef Cargo_Class
#define Cargo_Class

class Cargo
{
private:
	int ID;
	Time CDT;
	Time PrepTime;
	Time MoveTime;
	int TID;
	Type CargoType;
	Time LoadTime;
	int Cost;
	int DelDistance;
	
	Time AutoPromoteForN; //for normal cargos only
public:
	Cargo();
	Cargo(int id,char type,Time loadTime,int cost,int del);
	void SetType(char c);
	void SetID(int id);
	void SetTID(int id);
	int getTID();
	void SetCost(int cost);
	void SetDistance(int del);
	void SetLT(Time t);
	void SetCDT(Time T);
	void SetAutoPromote(Time T);
	void setMoveTime(Time T);
	Time getMoveTime();
	void setPrepTime(Time T);
	Time getPrepTime();
	Time GetCDT();
	Type GetCargoType();
	Time GetLT();
	int GetCost();
	int GetDistance();
	int GetID();
	Time GetAutoPromote();

	bool operator ==(const Cargo& x)
	{
		return x.ID==this->ID;
	}



	friend ostream& operator<<(ostream& os, const Cargo* C)
	{

		os << C->ID;
		return os;

	}
};


#endif