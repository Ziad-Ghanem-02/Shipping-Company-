#include "ReadyEvent.h"
#include "Company.h"

ReadyEvent::ReadyEvent()
{

}
void ReadyEvent :: Execute(LinkedList<Cargo*>& NormalCargoList, PriQ<Cargo*>& VIPCargoList, LinkedQueue<Cargo*>& SpecialCargoList )
{
	switch (cargoptr->GetCargoType())
	{
	case 0:
		NormalCargoList.Insert(cargoptr);
		break;
	case 1:
		VIPCargoList.enqueue(cargoptr, cargoptr->GetCost());
		break;
	case 2:
		SpecialCargoList.enqueue(cargoptr);
		break;
	}
}
void ReadyEvent :: SetET(Time T)
{
	ET = T;
}
Time ReadyEvent :: GetET()
{
	return ET;
}
void ReadyEvent::setcargoptr(Cargo* p)
{
	cargoptr = p;
}