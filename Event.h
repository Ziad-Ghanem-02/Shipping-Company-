#pragma once
#include "LinkedList.h"
#include "PriorityQ.h"
#include "LinkedQueue.h"
#include "Cargo.h"
class Company;
class Event
{
public:

	Event()
	{

	}
	virtual void Execute(LinkedList<Cargo*>& NormalCargoList, PriQ<Cargo*>& VIPCargoList, LinkedQueue<Cargo*>& SpecialCargoList) = 0;
	virtual void SetET(Time T) = 0;
	virtual Time GetET() = 0;
	virtual void setcargoptr(Cargo* p) = 0;
};

