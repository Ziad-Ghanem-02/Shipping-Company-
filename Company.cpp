#include "Company.h"

//constructors and distructors
Company::Company()
{
	AutoPromoted = 0;
	Clock.SetDay(1);
	Clock.SetHour(0);
	Interface->PrintInitializing();
}
Company::Company(string A)
{
	AutoPromoted = 0;
	if (!ReadFile.is_open())
		SetFileName(A);
	else
	{
		ReadFile.close();
		SetFileName(A);

	}


}
Company :: ~Company()
{

	if (ReadFile.is_open())
		ReadFile.close();
}
//Reading from file functions
void Company::SetFileName(string A)
{
	ReadFile.open(A + ".txt", ios::in);
	OutputFile.open(A + "OUTPUT" + ".txt", ios::out);
}
char Company::ReadCharacter()
{
	char R;
	if (ReadFile.is_open())
	{
		ReadFile >> R;
	}
	return R;
}
int Company::ReadInteger()
{
	int R;
	if (ReadFile.is_open())
	{
		ReadFile >> R;
	}
	return R;
}
Time Company::ReadEventTime()
{
	int x;
	char y;
	int z;
	Time t;
	if (ReadFile.is_open())
	{
		ReadFile >> x;
		ReadFile >> y;
		ReadFile >> z;
	}
	if (x && z)
	{
		t.SetDay(x);
		t.SetHour(z);
	}
	return t;
}

//private functions
void Company::SetSpeedOfTrucks(LinkedQueue<Truck*>& T, int speed)
{
	Truck* x;
	LinkedQueue<Truck*> temp;
	{
		while (T.peek(x))
		{
			T.dequeue(x);
			x->SetSpeed(speed);
			temp.enqueue(x);
		}
		while (!temp.isEmpty())
		{
			temp.dequeue(x);
			T.enqueue(x);
		}
	}
}


void Company::SetCapacityOfTrucks(LinkedQueue<Truck*>& T, int capacity)
{
	Truck* x;
	LinkedQueue<Truck*> temp;
	{
		while (T.peek(x))
		{
			T.dequeue(x);
			x->SetCapacity(capacity);
			temp.enqueue(x);
		}
		while (!temp.isEmpty())
		{
			temp.dequeue(x);
			T.enqueue(x);
		}
	}
}

void Company::SetCheckupOfTrucks(LinkedQueue<Truck*>& T, int j, int checkup)
{
	Truck* x;
	LinkedQueue<Truck*> temp;
	{
		while (T.peek(x))
		{
			T.dequeue(x);
			x->SetMaintenanceDuration(checkup);
			x->SetJ(j);
			temp.enqueue(x);
		}
		while (!temp.isEmpty())
		{
			temp.dequeue(x);
			T.enqueue(x);
		}
	}
}

//Assigning trucks function
void Company::AssignTrucks()
{
	int x;
	int id = 1;
	x = ReadInteger();
	for (int i = 0; i < x; i++)
	{
		Truck* T = new Truck('N');
		T->SetID(id);
		NormalTrucks.enqueue(T);
		id++;
	}
	int y = ReadInteger();
	for (int i = 0; i < y; i++)
	{
		Truck* T = new Truck('S');
		T->SetID(id);
		SpecialTrucks.enqueue(T);
		id++;
	}
	int z = ReadInteger();
	for (int i = 0; i < z; i++)
	{
		Truck* T = new Truck('V');
		T->SetID(id);
		VIPTrucks.enqueue(T);
		id++;
	}
	int w = ReadInteger();
	for (int i = 0; i < x; i++)
	{
		SetSpeedOfTrucks(NormalTrucks, w);
	}
	w = ReadInteger();
	for (int i = 0; i < y; i++)
	{
		SetSpeedOfTrucks(SpecialTrucks, w);
	}
	w = ReadInteger();
	for (int i = 0; i < z; i++)
	{
		SetSpeedOfTrucks(VIPTrucks, w);
	}
	w = ReadInteger();
	for (int i = 0; i < x; i++)
	{
		SetCapacityOfTrucks(NormalTrucks, w);
		NormalTruckCapacity = w;
	}
	w = ReadInteger();
	for (int i = 0; i < y; i++)
	{
		SetCapacityOfTrucks(SpecialTrucks, w);
		SpecialTruckCapacity = w;
	}
	w = ReadInteger();
	for (int i = 0; i < z; i++)
	{
		SetCapacityOfTrucks(VIPTrucks, w);
		VIPTruckCapacity = w;
	}
	int j = ReadInteger();
	w = ReadInteger();
	for (int i = 0; i < x; i++)
	{
		SetCheckupOfTrucks(NormalTrucks, j, w);
	}
	w = ReadInteger();
	for (int i = 0; i < y; i++)
	{
		SetCheckupOfTrucks(SpecialTrucks, j, w);
	}
	w = ReadInteger();
	for (int i = 0; i < z; i++)
	{
		SetCheckupOfTrucks(VIPTrucks, j, w);
	}
}
//Assign Events Function
void Company::AssignEvents()
{
	AutoPromote.SetDay(ReadInteger());
	MaxWTime = ReadInteger();
	int x = ReadInteger();
	char y;
	for (int i = 0; i < x; i++)
	{
		y = ReadCharacter();
		switch (y)
		{
		case('R'):
			ReadReadyEvent();
			break;
		case('P'):
			ReadPromoteEvent();
			break;
		case('X'):
			ReadCancelEvent();
			break;
		}
	}

}

void Company::ReadInputFile()
{
	AssignTrucks();
	AssignEvents();
}

void Company::ReadReadyEvent()
{
	Event* R = new ReadyEvent;
	Cargo* c = new Cargo;
	c->SetType(ReadCharacter());
	R->SetET(ReadEventTime());
	c->setPrepTime(R->GetET());
	c->SetID(ReadInteger());
	c->SetDistance(ReadInteger());
	c->SetLT(ReadInteger());
	c->SetCost(ReadInteger());
	R->setcargoptr(c);
	if (c->GetCargoType() == Normal)
		c->SetAutoPromote(R->GetET() + AutoPromote);
	EQ.enqueue(R);

}
void Company::ReadCancelEvent()
{
	Event* R = new CancelEvent;
	Cargo* c = new Cargo;
	R->SetET(ReadEventTime());
	c->SetID(ReadInteger());
	R->setcargoptr(c);
	EQ.enqueue(R);


}
void Company::ReadPromoteEvent()
{
	Event* R = new PromoteEvent;
	Cargo* c = new Cargo;
	R->SetET(ReadEventTime());
	c->SetID(ReadInteger());
	c->SetCost(ReadInteger());
	R->setcargoptr(c);
	EQ.enqueue(R);


}


UI* Company::GetUI()
{
	return Interface;
}

void Company::SimpleMode(int mode)
{
	Event* E;
	int count = 0;
	bool breaker = false;
	while (!EQ.isEmpty() || !breaker)
	{
		EQ.peek(E);
		if (E->GetET() == Clock)
		{
			E->Execute(WaitingListNormal, WaitingListVip, WaitingListSpecial);
			EQ.dequeue(E);
		}
		if (count == 5)
		{
			Cargo* C;
			if (!WaitingListNormal.is_Empty())
			{
				DeliveredNormalCargos.enqueue(WaitingListNormal.DeleteFirst());
			}
			if (!WaitingListVip.isEmpty())
			{
				WaitingListVip.dequeue(C);
				DeliveredVIPCargos.enqueue(C);
			}
			if (!WaitingListSpecial.isEmpty())
			{
				WaitingListSpecial.dequeue(C);
				DeliveredSpecialCargos.enqueue(C);
			}
			count = 0;
		}

		if (mode == 1 || mode == 2)
		{
			Interface->PrintSimpleMode(Clock, WaitingListNormal, WaitingListVip, WaitingListSpecial, DeliveredNormalCargos, DeliveredVIPCargos, DeliveredSpecialCargos, NormalTrucks, VIPTrucks, SpecialTrucks, LoadingNormalTrucks, LoadingVIPTrucks, LoadingSpecialTrucks, MovingTrucks, Maintenance, BackTrucks);
			switch (mode)
			{
			case (1):
				system("pause");
				break;
			case(2):
				Sleep(1000);
				break;
			}
			if (EQ.isEmpty() && WaitingListNormal.is_Empty() && WaitingListVip.isEmpty() && WaitingListSpecial.isEmpty())
				breaker = true;
			count++;
			Clock = Clock + 1;
		}
	}
}
void Company::Phase2(int mode)
{
	Event* E;
	bool breaker = false;
	while (!breaker)
	{
		if (!EQ.isEmpty())
		{
			while (EQ.peek(E) && Clock >= E->GetET())
			{
				E->Execute(WaitingListNormal, WaitingListVip, WaitingListSpecial);
				EQ.dequeue(E);
			}
		}
		AutoPromoteNormalCargos(Clock);
		LoadCargosToTrucks(Clock);
		FromLoadToMove(Clock);
		CargosFromTruckToDelivered(Clock);
		FromMoveToAvailable(Clock);
		FromMoveToMaintenance(Clock);
		FromMaintenanceToAvailable(Clock);
		LastVIPCargos(Clock);
		if (mode == 1 || mode == 2)
		{
			Interface->PrintSimpleMode(Clock, WaitingListNormal, WaitingListVip, WaitingListSpecial, DeliveredNormalCargos, DeliveredVIPCargos, DeliveredSpecialCargos, NormalTrucks, VIPTrucks, SpecialTrucks, LoadingNormalTrucks, LoadingVIPTrucks, LoadingSpecialTrucks, MovingTrucks, Maintenance, BackTrucks);
			switch (mode)
			{
			case (1):
				system("pause");
				break;
			case(2):
				Sleep(1000);
				break;
			}
		}
		if (EQ.isEmpty() && WaitingListNormal.is_Empty() && WaitingListVip.isEmpty() && WaitingListSpecial.isEmpty() && MovingTrucks.isEmpty() && LoadingNormalTrucks.isEmpty() && LoadingVIPTrucks.isEmpty() && LoadingSpecialTrucks.isEmpty() && BackTrucks.isEmpty())
			breaker = true;
		Clock = Clock + 1;
	}





	CargosInOutputFile();




}
void Company::LoadCargosToTrucks(Time T)
{
	Truck* CurrentTruck = nullptr;
	Cargo* Cargoptr;
	bool Z;
	if (LoadingVIPCheck())
	{
		if (WaitingListVip.GetCount() >= VIPTruckCapacity)
		{
			if (!VIPTrucks.isEmpty())
			{
				VIPTrucks.dequeue(CurrentTruck);
				for (int i = 0; i < VIPTruckCapacity; i++)
				{
					WaitingListVip.dequeue(Cargoptr);
					Cargoptr->SetTID(CurrentTruck->GetID());
					CurrentTruck->AddCargo(Cargoptr);
				}
			}
			else if (!NormalTrucks.isEmpty())
			{
				NormalTrucks.dequeue(CurrentTruck);
				for (int i = 0; i < NormalTruckCapacity; i++)
				{

					WaitingListVip.dequeue(Cargoptr);
					Cargoptr->SetTID(CurrentTruck->GetID());
					CurrentTruck->AddCargo(Cargoptr);
				}
			}
			else if (!SpecialTrucks.isEmpty())
			{
				SpecialTrucks.dequeue(CurrentTruck);
				for (int i = 0; i < SpecialTruckCapacity; i++)
				{
					WaitingListVip.dequeue(Cargoptr);
					Cargoptr->SetTID(CurrentTruck->GetID());
					CurrentTruck->AddCargo(Cargoptr);
				}
			}
			/*else if (!VIPTrucks.isEmpty() && WaitingListVip.GetCount() >= VIPTruckCapacity)
			{
			VIPTrucks.dequeue(CurrentTruck);
			}*/
			if (CurrentTruck)
			{
				CurrentTruck->SetSumUnloadTime();
				CurrentTruck->setCargosDelivered(CurrentTruck->GetCargoList().GetCount());
				//CurrentTruck->incJourneyCount();
				if (T.GetHour() > 5 && T.GetHour() <= 23)
					CurrentTruck->DepTime = (T + CurrentTruck->GetSumUnloadTime());
				else
				{
					Time T2((T.GetDay()), 6);
					CurrentTruck->DepTime = (T2 + CurrentTruck->GetSumUnloadTime());
				}
				CurrentTruck->SetDI();
				CurrentTruck->ArrTime = (CurrentTruck->DepTime + CurrentTruck->GetDI());
				CurrentTruck->SetCargosCDT();
				if (CurrentTruck->GetTruckType() == VIP)
				{
					LoadingVIPTrucks.enqueue(CurrentTruck);
				}
				else if (CurrentTruck->GetTruckType() == Normal)
				{
					LoadingNormalTrucks.enqueue(CurrentTruck);
				}
				else if (CurrentTruck->GetTruckType() == Special)
				{
					LoadingSpecialTrucks.enqueue(CurrentTruck);
				}
			}
		}
	}
	CurrentTruck = nullptr;

	///////////////////////////////////////////////

	Z = MaxWaitN();

	if ((LoadingNormalCheck() && WaitingListNormal.GetNItems() >= NormalTruckCapacity) || (WaitingListNormal.GetNItems() < NormalTruckCapacity && Z && !WaitingListNormal.is_Empty()))
	{
		if (!NormalTrucks.isEmpty())
		{
			NormalTrucks.dequeue(CurrentTruck);
			for (int i = 0; i < NormalTruckCapacity; i++)
			{
				if (Cargoptr = WaitingListNormal.DeleteFirst())
				{
					Cargoptr->SetTID(CurrentTruck->GetID());
					CurrentTruck->AddCargo(Cargoptr);
				}
			}
		}
		else if (!VIPTrucks.isEmpty())
		{
			VIPTrucks.dequeue(CurrentTruck);
			for (int i = 0; i < VIPTruckCapacity; i++)
			{
				if (Cargoptr = WaitingListNormal.DeleteFirst())
				{
					Cargoptr->SetTID(CurrentTruck->GetID());
					CurrentTruck->AddCargo(Cargoptr);
				}
			}
		}
		if (CurrentTruck)
		{
			CurrentTruck->SetSumUnloadTime();
			CurrentTruck->setCargosDelivered(CurrentTruck->GetCargoList().GetCount());
			//CurrentTruck->incJourneyCount();
			if (T.GetHour() > 5 && T.GetHour() <= 23)
				CurrentTruck->DepTime = (T + CurrentTruck->GetSumUnloadTime());
			else
			{
				Time T2((T.GetDay()), 6);
				CurrentTruck->DepTime = (T2 + CurrentTruck->GetSumUnloadTime());
			}
			CurrentTruck->SetDI();
			CurrentTruck->ArrTime = (CurrentTruck->DepTime + CurrentTruck->GetDI());
			CurrentTruck->SetCargosCDT();

			if (CurrentTruck->GetTruckType() == Normal)
			{
				LoadingNormalTrucks.enqueue(CurrentTruck);
			}
			else if (CurrentTruck->GetTruckType() == VIP)
			{
				LoadingVIPTrucks.enqueue(CurrentTruck);
			}
		}
	}
	////////////////////////////////////////////
	CurrentTruck = nullptr;
	bool G = MaxWaitS();

	if ((LoadingSpecialCheck() && WaitingListSpecial.GetCount() >= SpecialTruckCapacity) || (WaitingListSpecial.GetCount() < SpecialTruckCapacity && G && !WaitingListSpecial.isEmpty()))
	{
		if (!SpecialTrucks.isEmpty())
			SpecialTrucks.dequeue(CurrentTruck);
		if (CurrentTruck)
		{
			for (int i = 0; i < SpecialTruckCapacity; i++)
			{
				if (WaitingListSpecial.dequeue(Cargoptr))
				{
					Cargoptr->SetTID(CurrentTruck->GetID());
					CurrentTruck->AddCargo(Cargoptr);
				}
			}
			CurrentTruck->SetSumUnloadTime();
			CurrentTruck->setCargosDelivered(CurrentTruck->GetCargoList().GetCount());
			//CurrentTruck->incJourneyCount();
			if (T.GetHour() > 5 && T.GetHour() <= 23)
				CurrentTruck->DepTime = (T + CurrentTruck->GetSumUnloadTime());
			else
			{
				Time T2((T.GetDay()), 6);
				CurrentTruck->DepTime = (T2 + CurrentTruck->GetSumUnloadTime());

			}
			CurrentTruck->SetDI();
			CurrentTruck->ArrTime = (CurrentTruck->DepTime + CurrentTruck->GetDI());
			CurrentTruck->SetCargosCDT();
			LoadingSpecialTrucks.enqueue(CurrentTruck);
		}
	}
}


void Company::FromLoadToMove(Time Clock)
{
	Truck* T;
	if (!LoadingNormalTrucks.isEmpty())
	{
		while (LoadingNormalTrucks.peek(T) && Clock >= T->DepTime)
		{
			LoadingNormalTrucks.dequeue(T);
			Cargo* x;
			T->GetCargoList().peek(x);
			MovingTrucks.enqueue(T, -x->GetCDT());
		}
	}
	T = nullptr;
	if (!LoadingVIPTrucks.isEmpty())
	{

		while (LoadingVIPTrucks.peek(T) && Clock >= T->DepTime)
		{
			LoadingVIPTrucks.dequeue(T);
			Cargo* x;
			T->GetCargoList().peek(x);
			MovingTrucks.enqueue(T, -x->GetCDT());
		}
	}

	T = nullptr;

	if (!LoadingSpecialTrucks.isEmpty())
	{

		while (LoadingSpecialTrucks.peek(T) && T->DepTime == Clock)
		{
			LoadingSpecialTrucks.dequeue(T);
			Cargo* x;
			T->GetCargoList().peek(x);
			MovingTrucks.enqueue(T, -x->GetCDT());

		}
	}
}
void Company::FromMoveToAvailable(Time Clock)
{
	Truck* T;
	if (!BackTrucks.isEmpty())
	{

		while (BackTrucks.peek(T) && Clock >= T->ArrTime)
		{
			if (T->TripCount < T->GetJ())
			{
				T->TripCount++;
				BackTrucks.dequeue(T);
				//CargosFromTruckToDelivered(T);
				if (T->GetTruckType() == Normal)
					NormalTrucks.enqueue(T);
				else if (T->GetTruckType() == VIP)
					VIPTrucks.enqueue(T);
				else if (T->GetTruckType() == Special)
					SpecialTrucks.enqueue(T);
			}
		}
	}
}
void Company::FromMoveToMaintenance(Time Clock)
{
	Truck* T;
	if (!BackTrucks.isEmpty())
	{

		while (BackTrucks.peek(T) && T->TripCount == T->GetJ())
		{
			BackTrucks.dequeue(T);
			T->TripCount = 0;
			//CargosFromTruckToDelivered(T);
			T->BackAfterMaintenance = T->ArrTime + T->GetMaintenanceDuration();
			Maintenance.enqueue(T, -T->BackAfterMaintenance);
		}
	}
}
void Company::CargosFromTruckToDelivered(Time Clock)
{
	Cargo* x;
	Truck* T;
	if (MovingTrucks.peek(T))
	{
		T->GetCargoList().peek(x);
		if (Clock >= x->GetCDT()) //wrong
		{
			T->RemoveFirstCargo(x);
			x->setMoveTime(T->DepTime);
			if (x->GetCargoType() == Normal)
			{
				Cargo* y = new Cargo;
				//y->SetCDT(x->GetCDT());
				//y->SetID(x->GetID());
				//y->SetDistance(T->GetID());

				//y->SetCost(x->GetCost());
				//y->SetType(x->GetCargoType());
				//y->SetLT(x->getMoveTime() - x->getPrepTime());
				//y->SetAutoPromote(x->GetAutoPromote());
				/*OP.enqueue(y, -y->GetCDT());*/
				DeliveredNormalCargos.enqueue(x);
			}
			else if (x->GetCargoType() == VIP)
			{
				DeliveredVIPCargos.enqueue(x);
			}
			else if (x->GetCargoType() == Special)
			{
				Cargo* y = new Cargo;
				DeliveredSpecialCargos.enqueue(x);
			}

			if (T->GetCargoList().peek(x))
			{
				MovingTrucks.dequeue(T);
				MovingTrucks.enqueue(T, -x->GetCDT());
			}
			else
			{
				MovingTrucks.dequeue(T);
				BackTrucks.enqueue(T, -T->ArrTime);
			}
		}
	}
}
void Company::FromMaintenanceToAvailable(Time Clock)
{
	Truck* x;
	while (Maintenance.peek(x) && x->BackAfterMaintenance == Clock)
	{
		MovingTrucks.dequeue(x);
		if (x->GetTruckType() == Normal)
			NormalTrucks.enqueue(x);
		else if (x->GetTruckType() == VIP)
			VIPTrucks.enqueue(x);
		else if (x->GetTruckType() == Special)
			SpecialTrucks.enqueue(x);
	}

}

void Company::AutoPromoteNormalCargos(Time Clock)
{
	Cargo* x;
	if (!WaitingListNormal.is_Empty())
	{
		while (WaitingListNormal.peek(x) && x->GetAutoPromote() == Clock)
		{
			AutoPromoted++;
			x = WaitingListNormal.DeleteFirst();
			WaitingListVip.enqueue(x, x->GetCost());
		}
	}
}

bool Company::MaxWaitS()
{
	Time Max;
	Max = Max + MaxWTime;
	Truck* peeker;
	SpecialTrucks.peek(peeker);
	if (MaxS != peeker && !WaitingListSpecial.isEmpty())
	{
		SpecialTrucks.peek(MaxS);
		//MaxWS = MaxWS + 1;
	}
	else if (MaxS == peeker && !WaitingListSpecial.isEmpty())
	{
		MaxWS = MaxWS + 1;
		if (MaxWS == Max)
		{
			MaxWS.SetDay(0);
			MaxWS.SetHour(0);
			return true;
		}
	}
	return false;
}

bool Company::MaxWaitN()
{
	Time Max;
	Max = Max + MaxWTime;
	Truck* peeker;
	NormalTrucks.peek(peeker);
	if (MaxN != peeker && !WaitingListNormal.is_Empty())
	{
		NormalTrucks.peek(MaxN);
		//MaxWN = MaxWN + 1;
	}
	else if (MaxN == peeker && !WaitingListNormal.is_Empty())
	{
		MaxWN = MaxWN + 1;
		if (MaxWN == Max)
		{
			MaxWN.SetDay(0);
			MaxWN.SetHour(0);
			return true;
		}
	}
	return false;
}

//Time Company::getClock()
//{
//	return Clock;
//}
int Company::AvgActive()
{
	float total = 0; float avg; int sumTrucks; int countN = 0; int countS = 0; int countV = 0;
	Truck* T;
	int TnumN = NormalTrucks.GetCount();
	int TnumS = SpecialTrucks.GetCount();
	int TnumV = VIPTrucks.GetCount();

	sumTrucks = TnumN + TnumS + TnumV;
	while (!NormalTrucks.isEmpty() && countN < TnumN)
	{
		NormalTrucks.dequeue(T);
		avg = -(T->getActive()) / -(Clock);
		avg = avg * 100;
		total = total + avg;
		NormalTrucks.enqueue(T);
		countN++;
	}
	while (!VIPTrucks.isEmpty() && countV < TnumV)
	{
		VIPTrucks.dequeue(T);
		avg = -(T->getActive()) / -(Clock);
		avg = avg * 100;
		total = total + avg;
		VIPTrucks.enqueue(T);
		countV++;
	}
	while (!SpecialTrucks.isEmpty() && countS < TnumS)
	{
		SpecialTrucks.dequeue(T);
		avg = -(T->getActive()) / -(Clock);
		avg = avg * 100;
		total = total + avg;
		SpecialTrucks.enqueue(T);
		countS++;
	}
	total = total / sumTrucks;
	return total;
}

int Company::TruckUtilization()
{
	float total = 0; int sum = 0; float tDC = 0; float TC = 0; float N = 0; float tAT = 0; float TSim = 0;
	Truck* T;
	int TnumN = NormalTrucks.GetCount();
	int TnumS = SpecialTrucks.GetCount();
	int TnumV = VIPTrucks.GetCount();
	int sumTrucks = TnumN + TnumS + TnumV;
	while (!NormalTrucks.isEmpty())
	{
		NormalTrucks.dequeue(T);
		tDC = T->getCargosDelivered();
		TC = T->GetCapacity();
		N = T->TripCount;
		tAT = -(T->getActive());
		TSim = -(Clock);
		if (N == 0)
			sum = 0;
		else
			sum = 100 * (tDC / (TC * N)) * (tAT / TSim);
		total = total + sum;
	}
	while (!VIPTrucks.isEmpty())
	{
		VIPTrucks.dequeue(T);
		tDC = T->getCargosDelivered();
		TC = T->GetCapacity();
		N = T->TripCount;
		tAT = -(T->getActive());
		TSim = -(Clock);
		if (N == 0)
			sum = 0;
		else
			sum = 100 * (tDC / (TC * N)) * (tAT / TSim);
		total = total + sum;
	}
	while (!SpecialTrucks.isEmpty())
	{
		SpecialTrucks.dequeue(T);
		tDC = T->getCargosDelivered();
		TC = T->GetCapacity();
		N = T->TripCount;
		tAT = -(T->getActive());
		TSim = -(Clock);
		if (N == 0)
			sum = 0;
		else
			sum = 100 * (tDC / (TC * N)) * (tAT / TSim);
		total = total + sum;
	}
	return total / sumTrucks;
}

void Company::CargosInOutputFile()
{
	int CnumN = DeliveredNormalCargos.GetCount();
	int CnumS = DeliveredSpecialCargos.GetCount();
	int CnumV = DeliveredVIPCargos.GetCount();
	int sumC = CnumN + CnumS + CnumV;
	int TnumN = NormalTrucks.GetCount();
	int TnumS = SpecialTrucks.GetCount();
	int TnumV = VIPTrucks.GetCount();
	int sumT = TnumN + TnumS + TnumV;
	PriQ<Cargo*> Cargos;
	Time TotalWaitTime;

	Cargo* C;

	while (!DeliveredNormalCargos.isEmpty())
	{
		DeliveredNormalCargos.dequeue(C);
		Cargos.enqueue(C, -C->GetCDT());
	}
	while (!DeliveredSpecialCargos.isEmpty())
	{
		DeliveredSpecialCargos.dequeue(C);
		Cargos.enqueue(C, -C->GetCDT());
	}
	while (!DeliveredVIPCargos.isEmpty())
	{
		DeliveredVIPCargos.dequeue(C);
		Cargos.enqueue(C, -C->GetCDT());
	}
	OutputFile << "CDT" << "\t" << "CID" << "\t" << "PT" << "\t" << "WT" << "\t" << "TID" << endl;
	while (!Cargos.isEmpty())
	{
		Cargos.dequeue(C);
		TotalWaitTime = TotalWaitTime + (C->getMoveTime() - C->getPrepTime());
		OutputFile << C->GetCDT() << "\t";
		OutputFile << C->GetID() << "\t";
		OutputFile << C->getPrepTime() << "\t";
		OutputFile << C->getMoveTime() - C->getPrepTime() << "\t";
		OutputFile << C->getTID() << endl;
	}
	OutputFile << endl << "Cargos:" << sumC << "\t" << "[N:" << CnumN << ",S:" << CnumS << ",V:" << CnumV << "]" << endl << endl;
	int TW = -TotalWaitTime;
	TW = ceil(-TW / sumC);
	Time AvgWT = TW;
	OutputFile << "Average Wait Time: ";
	OutputFile << AvgWT << endl;
	OutputFile << "Auto-promoted cargos:\t" << 100 * (AutoPromoted / sumC) << "%" << endl;
	OutputFile << endl << "Trucks:" << sumT << "\t" << "[N:" << TnumN << ",S:" << TnumS << ",V:" << TnumV << "]" << endl << endl;
	int ActivePerc = AvgActive();
	OutputFile << "Avg Active Time:\t" << ActivePerc << "%" << endl;
	int Utilization = TruckUtilization();
	OutputFile << "Avg Utilization=\t" << Utilization << "%" << endl;
}


bool Company::LoadingNormalCheck()
{
	Truck* T;
	Cargo* c;
	if (!LoadingNormalTrucks.isEmpty())
	{
		LoadingNormalTrucks.peek(T);
		T->GetCargoList().peek(c);
		if (c->GetCargoType() == Normal)
		{
			return false;
		}
	}
	else if (!LoadingVIPTrucks.isEmpty())
	{
		LoadingVIPTrucks.peek(T);
		T->GetCargoList().peek(c);
		if (c->GetCargoType() == Normal)
		{
			return false;
		}
	}
	return true;
}
bool Company::LoadingVIPCheck()
{
	Truck* T;
	Cargo* C;
	if (!LoadingVIPTrucks.isEmpty())
	{
		LoadingVIPTrucks.peek(T);
		T->GetCargoList().peek(C);
		if (C->GetCargoType() == VIP)
			return false;
	}
	else if (!LoadingNormalTrucks.isEmpty())
	{
		LoadingNormalTrucks.peek(T);
		T->GetCargoList().peek(C);
		if (C->GetCargoType() == VIP)
			return false;
	}
	else if (!LoadingSpecialTrucks.isEmpty())
	{
		LoadingSpecialTrucks.peek(T);
		T->GetCargoList().peek(C);
		if (C->GetCargoType() == VIP)
			return false;
	}
	return true;
}
bool Company::LoadingSpecialCheck()
{
	Truck* T;
	Cargo* c;
	bool x;
	x = LoadingSpecialTrucks.isEmpty();
	if (!x)
	{
		LoadingSpecialTrucks.peek(T);
		T->GetCargoList().peek(c);
		if (c->GetCargoType() == Special)
		{
			return false;
		}
	}
	return true;
}

void Company::LastVIPCargos(Time T)
{
	if (EQ.isEmpty() && MovingTrucks.isEmpty() && LoadingNormalTrucks.isEmpty() && LoadingVIPTrucks.isEmpty() && LoadingSpecialTrucks.isEmpty() && WaitingListNormal.is_Empty() && WaitingListSpecial.isEmpty() && !WaitingListVip.isEmpty())
	{
		Truck* CurrentTruck;
		Cargo* Cargoptr;
		if (!VIPTrucks.isEmpty())
		{
			VIPTrucks.dequeue(CurrentTruck);
			for (int i = 0; i < WaitingListVip.GetCount(); i++)
			{
				WaitingListVip.dequeue(Cargoptr);
				Cargoptr->SetTID(CurrentTruck->GetID());
				CurrentTruck->AddCargo(Cargoptr);
			}
		}
		else if (!NormalTrucks.isEmpty())
		{
			NormalTrucks.dequeue(CurrentTruck);
			for (int i = 0; i < WaitingListVip.GetCount(); i++)
			{

				WaitingListVip.dequeue(Cargoptr);
				Cargoptr->SetTID(CurrentTruck->GetID());
				CurrentTruck->AddCargo(Cargoptr);
			}
		}
		else if (!SpecialTrucks.isEmpty())
		{
			SpecialTrucks.dequeue(CurrentTruck);
			for (int i = 0; i < WaitingListVip.GetCount(); i++)
			{
				WaitingListVip.dequeue(Cargoptr);
				Cargoptr->SetTID(CurrentTruck->GetID());
				CurrentTruck->AddCargo(Cargoptr);
			}
		}
		if (CurrentTruck)
		{
			CurrentTruck->SetSumUnloadTime();
			CurrentTruck->setCargosDelivered(CurrentTruck->GetCargoList().GetCount());
			if (T.GetHour() > 5 && T.GetHour() <= 23)
				CurrentTruck->DepTime = (T + CurrentTruck->GetSumUnloadTime());
			else
			{
				Time T2((T.GetDay()), 6);
				CurrentTruck->DepTime = (T2 + CurrentTruck->GetSumUnloadTime());
			}
			CurrentTruck->SetDI();
			CurrentTruck->ArrTime = (CurrentTruck->DepTime + CurrentTruck->GetDI());
			CurrentTruck->SetCargosCDT();
			if (CurrentTruck->GetTruckType() == VIP)
			{
				LoadingVIPTrucks.enqueue(CurrentTruck);
			}
			else if (CurrentTruck->GetTruckType() == Normal)
			{
				LoadingNormalTrucks.enqueue(CurrentTruck);
			}
			else if (CurrentTruck->GetTruckType() == Special)
			{
				LoadingSpecialTrucks.enqueue(CurrentTruck);
			}
		}
	}
}