#include "PromoteEvent.h"
#include "Company.h"

PromoteEvent::PromoteEvent()
{

}
void PromoteEvent::Execute(LinkedList<Cargo*>& NormalCargoList, PriQ<Cargo*>& VIPCargoList, LinkedQueue<Cargo*>& SpecialCargoList)
{
	Cargo* x = NormalCargoList.DeleteID(cargoptr);
	if(x!=nullptr)
	{
		x->SetCost(x->GetCost()+cargoptr->GetCost());
		VIPCargoList.enqueue(x,x->GetCost());
	}
	
}
void PromoteEvent::SetET(Time T)
{
	ET = T;
}
Time PromoteEvent::GetET()
{
	return ET;
}
void PromoteEvent::setcargoptr(Cargo* p)
{
	cargoptr = p;
}