#include "Cargo.h"
#include "PriorityQ.h"
#include "LinkedQueue.h"
#ifndef Truck_class
#define Truck_class
class Truck
{
private:
	int ID;
	//int NJourneys;
	Time TruckActiveTime;
	Type TruckType;
	int Capacity;
	int speed;
	float MaxDel; //maximum distance
	Time MaxLoadTime;
	int j; //Trips Before Maintenance;
	int MaintenanceDuration;
	Time DI; //delivery interval
	PriQ<Cargo*> CargoList;
	Time SumUnloadTime;
	void SetMaxDelDistance();
	int TotalCargosDelivered;

public:
	int TripCount;
	Time DepTime;
	Time ArrTime;
	Time BackAfterMaintenance;
	//Truck(int c,char t,int s)
	//{
	//	SetCapacity(c);
	//	SetSpeed(s);
	//	SetTruckType(t);
	//	TripCount=0;
	//	SumUnloadTime=0;
	//	MaxDel=0;
	//}
	Truck(char k);
	Truck();
	void SetTruckType(char c);
	void SetCapacity(int c);
	void SetSpeed(int c);
	void SetJ(int J);
	void SetDI();
	void SetMaintenanceDuration(int x);
	void SetID(int id);
	void SetMaxUnloadTime();
	void SetSumUnloadTime();
	void setActive();
	void setCargosDelivered(int n);
	//void incJourneyCount();

	int getCargosDelivered();
	Time getActive();
	int GetCapacity();
	Time GetDI();
	int GetMaxDelDistance();
	Time GetSumUnloadTime();
	int GetJ();
	int GetMaintenanceDuration();
	int GetID();
	bool AddCargo(Cargo *c);
	bool RemoveFirstCargo(Cargo*);
	Time GetMaxUnloadTime();
	PriQ<Cargo*> GetCargoList();
	Type GetTruckType()
	{
		return TruckType;
	}
	void SetCargosCDT();


	friend ostream& operator<<(ostream& os, const Truck* C)
	{

		os << C->ID;
		return os;

	}

};

#endif