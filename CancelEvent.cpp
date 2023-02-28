#include "CancelEvent.h"
#include "Company.h"

CancelEvent::CancelEvent()
{

}
void CancelEvent::Execute(LinkedList<Cargo*>& NormalCargoList, PriQ<Cargo*>& VIPCargoList, LinkedQueue<Cargo*>& SpecialCargoList)
{
	NormalCargoList.DeleteID(cargoptr);	
}
void CancelEvent::SetET(Time T)
{
	ET = T;
}
Time CancelEvent::GetET()
{
	return ET;
}
void CancelEvent::setcargoptr(Cargo* p)
{
	cargoptr = p;
}