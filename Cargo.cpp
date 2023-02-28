#include "Cargo.h"

Cargo :: Cargo()
{
}

Cargo :: Cargo(int id,char type,Time loadTime,int cost,int del)
{
	SetID(id);
	SetType(type);
	SetLT(loadTime);
	SetCost(cost);
	SetDistance(del);

}

void Cargo :: SetType(char c)
{
	if(c=='N')
		CargoType=Normal;
	else if (c=='V')
		CargoType=VIP;
	else if(c=='S')
		CargoType=Special;
}

void Cargo :: SetID(int id)
{
	ID=id;
}

void Cargo :: SetCost(int cost)
{
	Cost=cost;
}

void Cargo :: SetDistance(int del)
{
	DelDistance=del;

}

void Cargo :: SetLT(Time t)
{
	LoadTime=t;
}

Type Cargo :: GetCargoType()
{
	return CargoType;
}

Time Cargo :: GetLT()
{
	return LoadTime;
}

int Cargo :: GetCost()
{
	return Cost;
}

int Cargo :: GetDistance()
{
	return DelDistance;
}

int Cargo :: GetID()
{
	return ID;
}

void Cargo :: SetCDT(Time T)
{
	CDT=T;
}
Time Cargo :: GetCDT()
{
	return CDT;
}
void Cargo :: SetAutoPromote(Time T)
{
	AutoPromoteForN = T;
}
Time Cargo :: GetAutoPromote()
{
	return AutoPromoteForN;
}

void Cargo::setPrepTime(Time T)
{
	PrepTime = T;
}

Time Cargo::getPrepTime()
{
	return PrepTime;
}
void Cargo::setMoveTime(Time T)
{
	MoveTime = T;
}

Time Cargo::getMoveTime()
{
	return MoveTime;
}
void Cargo::SetTID(int id)
{
	TID = id;
}
int Cargo::getTID()
{
	return TID;
}