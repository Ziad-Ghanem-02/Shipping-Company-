#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include "Cargo.h"
#include "Truck.h"
#include "Time.h"
#include "LinkedQueue.h"
#include "PriorityQ.h"
#include "LinkedList.h"
#include "ReadyEvent.h"
#include "CancelEvent.h"
#include "PromoteEvent.h"
#include "Event.h"
#include "UI.h"

using namespace std;

class Company
{
private:
	UI *Interface;
	Time Clock;
	ifstream ReadFile;
	ofstream OutputFile;
	Time AutoPromote;
	int MaxWTime;
	void SetSpeedOfTrucks(LinkedQueue<Truck*> &T, int speed);
	void SetCapacityOfTrucks(LinkedQueue<Truck*> &T, int capacity);
	void SetCheckupOfTrucks(LinkedQueue<Truck*> &T, int j, int checkup);	
	LinkedQueue<Event*> EQ;
	int AutoPromoted;

	int NormalTruckCapacity;
	int VIPTruckCapacity;
	int SpecialTruckCapacity;




	LinkedList<Cargo*> WaitingListNormal;
	PriQ<Cargo*> WaitingListVip;
	LinkedQueue<Cargo*> WaitingListSpecial;


	LinkedQueue<Truck*> NormalTrucks;
	LinkedQueue<Truck*> VIPTrucks;
	LinkedQueue<Truck*>SpecialTrucks;

	LinkedQueue<Cargo*> DeliveredNormalCargos;
	LinkedQueue<Cargo*> DeliveredVIPCargos;
	LinkedQueue<Cargo*> DeliveredSpecialCargos;

	LinkedQueue<Truck*> LoadingNormalTrucks;
	LinkedQueue<Truck*> LoadingVIPTrucks;
	LinkedQueue<Truck*> LoadingSpecialTrucks;

	//LinkedQueue<Truck*>MovingNormalTrucks;
	//LinkedQueue<Truck*>MovingVIPTrucks;
	//LinkedQueue<Truck*>MovingSpecialTrucks;
	PriQ<Truck*> MovingTrucks;

	PriQ<Truck*> BackTrucks;

	PriQ<Truck*> Maintenance;
	/*PriQ<Cargo*> OP;*/
	Time MaxWN;
	Time MaxWS;
	Truck* MaxS;
	Truck* MaxN;

public:
	Company();
	Company(string A);
	void AssignTrucks();
	void AssignEvents();
	void ReadInputFile();
	void ReadReadyEvent();
	void ReadCancelEvent();
	void ReadPromoteEvent();
	void SetFileName(string A);
	char ReadCharacter();
	int ReadInteger();
	Time ReadEventTime();
	void AddToWaitingNormal(Cargo*ptr);
	void AddToWaitingSpecial(Cargo* ptr);
	void AddToWaitingVIP(Cargo* ptr);
	UI* GetUI();
	void SimpleMode(int mode);
	void Phase2(int mode);
	void LoadCargosToTrucks(Time);
	void FromLoadToMove(Time);
	void FromMoveToAvailable(Time);
	void FromMoveToMaintenance(Time);
	void CargosFromTruckToDelivered(Time);
	void FromMaintenanceToAvailable(Time);
	void AutoPromoteNormalCargos(Time);
	bool MaxWaitS();
    bool MaxWaitN();
	bool LoadingNormalCheck();
	bool LoadingVIPCheck();
	bool LoadingSpecialCheck();
	int AvgActive();
	void CargosInOutputFile();
	/*Time getClock();*/
	int TruckUtilization();

	void LastVIPCargos(Time);

	~Company();

};
