#include <iostream>
using namespace std;
//this file is copied from tutorial materials

#ifndef _NODE
#define _NODE

//First let's declare a single node in the list
template<typename T>
class Node
{
private :
	T item;	// A data item (can be any complex sturcture)
	Node<T>* next;	// Pointer to next node
	int priority;  //used in priorityQ
public :

	Node( ) //default constructor
	{
		next= nullptr;
		//P=Normal;
	} 

	Node( T newItem) //non-default constructor
	{
		item = newItem;
		next= nullptr;
		//P=Normal;
	}
	Node( T newItem,int p) //non-default constructor used in priority Queue Only
	{
		item = newItem;
		next= nullptr;
		priority = p;
	}

	void setItem( T newItem)
	{
		item = newItem;
	} // end setItem

	void setNext(Node<T>* nextNodePtr)
	{
		next = nextNodePtr;
	} // end setNext
	T getItem() const
	{
		return item;
	} // end getItem

	Node<T>* getNext() const
	{
		return next;
	}

	//functions related to priority queue only
	int GetPriority()
	{
		return priority;
	}
	void SetPriority(int p)
	{
		priority=p;
	}
}; // end Node

#endif	
