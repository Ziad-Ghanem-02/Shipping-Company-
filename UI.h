#pragma once
#include <iostream>
#include <string>
#include <Windows.h>
#include "Time.h"
#include "LinkedList.h"
#include "PriorityQ.h"
#include "LinkedQueue.h"
using namespace std;


class UI
{
private:

public:
	UI()
	{}
	string ReadStringFromUser()
	{
		string A;
		cin>>A;
		return A;

	}
	int ReadIntFromUser()
	{
		int A;
		cin>>A;
		return A;
	}
	char ReadCharFromUser()
	{
		char A;
		cin>>A;
		return A;
	}
	void PrintEmptyTrucks(LinkedQueue<Truck*>& Normal,LinkedQueue<Truck*>& VIP,LinkedQueue<Truck*>& Special)
	{
		cout<<Normal.GetCount()+VIP.GetCount()+Special.GetCount()<<" Empty Trucks:[";
		Normal.PrintQueue();
		cout<<"] ";
		cout<<"(";
		Special.PrintQueue();
		cout<<") ";
		cout<<"{";
		VIP.PrintQueue();
		cout<<"}"<<endl<<"-------------------------------------------------------"<<endl;
	}

	void PrintWaitingCargos(LinkedList<Cargo*>& NormalCargoList, PriQ<Cargo*>& VIPCargoList, LinkedQueue<Cargo*>& SpecialCargoList)
	{
		cout<<NormalCargoList.GetNItems()+VIPCargoList.GetCount()+SpecialCargoList.GetCount()<<" ";
		cout<<"Waiting Cargos:[";
		NormalCargoList.PrintList();
		cout<<"] ";
		cout<<"(";
		SpecialCargoList.PrintQueue();
		cout<<") ";
		cout<<"{";
		VIPCargoList.PrintPriorityQ();
		cout<<"}"<<endl<<"-------------------------------------------------------"<<endl;

	}
	void PrintInitializing()
	{
		cout<<"Welcome to the shipping Company"<<endl;
		Sleep(500);
		cout<<"please read instructions carefully"<<endl;
		Sleep(500);
		cout<<"Firstly:you will be asked to type the loadfile"<<endl;
		Sleep(500);
		cout<<"Secondly:you will be asked to choose mode from one of the following three modes."<<endl;
		Sleep(500);
		cout<<"1-interaction mode"<<endl<<"2-active mode"<<endl<<"3-silent mode"<<endl;
		Sleep(500);
		cout<<"Now let's start ,Have a good experience!"<<endl<<endl<<endl;
		Sleep(500);
		cout<<"Please Enter loadfile name , then choose the mode:"<<endl;
	}
	void PrintDeliveredCargos(LinkedQueue<Cargo*> & DeliveredNormal,LinkedQueue<Cargo*> & DeliveredVIP,LinkedQueue<Cargo*> & DeliveredSpecial)
	{
		cout<<DeliveredNormal.GetCount()+DeliveredSpecial.GetCount()+DeliveredVIP.GetCount()<<" "<<"Delivered Cargos: [" ;
		DeliveredNormal.PrintQueue();
		cout<<"] ";
		cout<<"(";
		DeliveredSpecial.PrintQueue();
		cout<<") ";
		cout<<"{";
		DeliveredVIP.PrintQueue();
		cout<<"}"<<endl<<"-------------------------------------------------------"<<endl;

	}
	void PrintSimpleMode(Time & t ,LinkedList<Cargo*>& NormalCargoList, PriQ<Cargo*>& VIPCargoList, LinkedQueue<Cargo*>& SpecialCargoList,LinkedQueue<Cargo*> & DeliveredNormal,LinkedQueue<Cargo*> & DeliveredVIP,LinkedQueue<Cargo*> & DeliveredSpecial,LinkedQueue<Truck*>& Normal,LinkedQueue<Truck*>& VIP,LinkedQueue<Truck*>& Special,LinkedQueue<Truck*>LN,LinkedQueue<Truck*>LV , LinkedQueue<Truck*>LS,PriQ<Truck*>MT,PriQ<Truck*>&CUT , PriQ<Truck*> &BT)
	{
		PrintCurrentTime(t);
		PrintEmptyTrucks( Normal, VIP, Special);
		PrintWaitingCargos(NormalCargoList,VIPCargoList,SpecialCargoList);
		PrintDeliveredCargos(DeliveredNormal,DeliveredVIP,DeliveredSpecial);
		PrintLoadingTrucks(LN,LV,LS);
		PrintMovingTrucks(MT,BT);
		PrintInCheckUp(CUT);
	}
	void PrintCurrentTime(Time & t)
	{
		cout<<"Current Time (Day:Hour) : ("<<t.GetDay()<<":"<<t.GetHour()<<")"<<endl;
	}
	~UI()
	{}

	void PrintLoadingTrucks(LinkedQueue<Truck*>LN,LinkedQueue<Truck*>LV , LinkedQueue<Truck*>LS )
	{
		Truck* x;
		//cout<<(LN.GetCount()+LV.GetCount()+LS.GetCount())<<" ";
		cout<<"Loading Trucks:";
		while(!LN.isEmpty())
		{
			LN.dequeue(x);
			PrintTruckWithCargoList(x);
		}
		while(!LV.isEmpty())
		{
			LV.dequeue(x);
			PrintTruckWithCargoList(x);
		}
		while(!LS.isEmpty())
		{
			LS.dequeue(x);
			PrintTruckWithCargoList(x);
		}
		cout<<endl<<"-------------------------------------------------------"<<endl;
	}
	void PrintTruckWithCargoList(Truck* TRUCK)
	{
		Cargo* x;
		cout<<TRUCK->GetID();
		if(	TRUCK->GetCargoList().peek(x))
		{
			if (x->GetCargoType()==Normal)
			{
				cout<<"[";
				TRUCK->GetCargoList().PrintPriorityQ();
				cout<<"], ";
			}
			else if(x->GetCargoType()==VIP)
			{
				cout<<"{";
				TRUCK->GetCargoList().PrintPriorityQ();
				cout<<"}, ";
			}
			else if(x->GetCargoType()==Special)
			{
				cout<<"(";
				TRUCK->GetCargoList().PrintPriorityQ();
				cout<<"),";
			}		
		}
		cout<<" ";
	}
	void PrintMovingTrucks(PriQ<Truck*> MT , PriQ<Truck*> &BT)
	{
		Truck* x;
		cout<<(MT.GetCount()+BT.GetCount())<<" ";
		cout<<"Moving Cargos:";
		while(!MT.isEmpty())
		{
			MT.dequeue(x);
			PrintTruckWithCargoList(x);
		}
		cout<<endl<<"-------------------------------------------------------"<<endl;
		cout<<BT.GetCount()<<" Trucks Coming Back After Delivery:";
		BT.PrintPriorityQ();
		cout<<endl<<"-------------------------------------------------------"<<endl;
	}
	void PrintInCheckUp(PriQ<Truck*>& CUT)
	{
		cout<<(CUT.GetCount())<<" ";
		cout<<"In-CheckUp trucks:";
		CUT.PrintPriorityQ();
		cout<<endl<<"-------------------------------------------------------"<<endl<<endl;
	}
};