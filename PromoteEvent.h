#pragma once
#include "Event.h"
#include "Company.h"
class Company;
class PromoteEvent : public Event
{
private:
	Time ET;
	Cargo* cargoptr;
public:
	PromoteEvent();
	void Execute(LinkedList<Cargo*>& NormalCargoList, PriQ<Cargo*>& VIPCargoList, LinkedQueue<Cargo*>& SpecialCargoList);
	void SetET(Time T);
	Time GetET();
	void setcargoptr(Cargo* p);
};