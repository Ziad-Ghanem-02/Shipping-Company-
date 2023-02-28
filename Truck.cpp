#include "Truck.h"

Truck :: Truck(char k)
{
	//NJourneys = 0;
	TruckActiveTime = 0;
	TotalCargosDelivered = 0;
	TripCount=0;
	MaxDel=0;
	SetTruckType(k);
}
Truck ::Truck()
{
	//NJourneys = 0;
	TotalCargosDelivered = 0;
	TruckActiveTime = 0;
	TripCount=0;
	MaxDel=0;
}
void Truck ::SetTruckType(char c)
{
	if(c=='N')
		TruckType=Normal;
	else if (c=='V')
		TruckType=VIP;
	else if(c=='S')
		TruckType=Special;
}
void Truck:: SetCapacity(int c)
{
	Capacity=c;
}
void Truck :: SetSpeed(int c)
{
	speed=c;
}
int Truck :: GetCapacity()
{
	return Capacity;
}

bool Truck:: AddCargo(Cargo *c)
{
	int x=CargoList.GetCount();
	if(x<Capacity)
	{
		CargoList.enqueue(c,-(c->GetDistance()));
		return true;
	}
	else
		return false;
}
void Truck :: SetDI()
{
	SetSumUnloadTime();
	SetMaxDelDistance();
	setActive();
	int x=2*(GetMaxDelDistance()/speed);
	DI.SetHour(x+SumUnloadTime.GetHour());
}
Time Truck :: GetDI()
{
	return DI;
}
int Truck :: GetMaxDelDistance()
{
	return MaxDel;
}
void Truck :: SetMaxDelDistance()
{
	Cargo* X;
	CargoList.peek(X);
	int dist=X->GetDistance();
	LinkedQueue<Cargo*> temp;
	while(CargoList.peek(X))
	{
		if(X->GetDistance()>dist)
			dist=X->GetDistance();
		CargoList.dequeue(X);
		temp.enqueue(X);
	}
	while(!temp.isEmpty())
	{
		temp.dequeue(X);
		CargoList.enqueue(X,1/X->GetDistance());
	}
	MaxDel=dist;
}
void Truck :: SetSumUnloadTime()
{
	Cargo  *x;
	LinkedQueue<Cargo*> temp ;
	while(CargoList.peek(x))
	{
		SumUnloadTime=SumUnloadTime+x->GetLT();
		CargoList.dequeue(x);
		temp.enqueue(x);
	}
	while(!temp.isEmpty())
	{
		temp.dequeue(x);
		CargoList.enqueue(x,1/x->GetDistance());
	}

}
Time Truck :: GetSumUnloadTime()
{
	return SumUnloadTime;
}
int Truck :: GetJ()
{
	return j;
}
void Truck :: SetJ(int J)
{
	j=J;
}
void Truck :: SetMaintenanceDuration(int x)
{
	MaintenanceDuration=x;
}
int Truck :: GetMaintenanceDuration()

{
	return MaintenanceDuration;
}
int Truck :: GetID()
{
	return ID;
}
void Truck :: SetID(int id)
{
	ID=id;
}
void Truck::SetMaxUnloadTime()
{
	Cargo* X;
	CargoList.peek(X);
	Time MLT=X->GetLT();
	LinkedQueue<Cargo*> temp;
	while(CargoList.peek(X))
	{
		if(X->GetLT()>MLT)
			MLT=X->GetLT();
		CargoList.dequeue(X);
		temp.enqueue(X);
	}
	while(!temp.isEmpty())
	{
		temp.dequeue(X);
		CargoList.enqueue(X,1/X->GetDistance());
	}
	MaxLoadTime=MLT;
}
Time Truck :: GetMaxUnloadTime()
{
	return MaxLoadTime;
}

PriQ<Cargo*> Truck :: GetCargoList()
{
	return CargoList;
}

void Truck :: SetCargosCDT()
{
	Time UnloadTime;
	Cargo * x;
	LinkedQueue<Cargo*> temp;
	while (!CargoList.isEmpty())
	{
		CargoList.dequeue(x);
		UnloadTime = UnloadTime + x->GetLT();
		x->SetCDT(DepTime + UnloadTime + (x->GetDistance() / speed));
		temp.enqueue(x);
	}
	while(!temp.isEmpty())
	{
		temp.dequeue(x);
		AddCargo(x);
	}
}
bool Truck :: RemoveFirstCargo(Cargo*C)
{
	if(CargoList.isEmpty())
		return false;
	CargoList.dequeue(C);
	return true;
}

void Truck::setActive()
{
	TruckActiveTime = TruckActiveTime + SumUnloadTime + (MaxDel / speed);
}

Time Truck::getActive()
{
	return TruckActiveTime;
}

void Truck :: setCargosDelivered(int n)
{
	TotalCargosDelivered = TotalCargosDelivered + n;
}

int Truck :: getCargosDelivered()
{
	return TotalCargosDelivered;
}

//void Truck:: incJourneyCount()
//{
//	NJourneys++;
//}