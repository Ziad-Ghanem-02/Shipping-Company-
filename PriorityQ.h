//Needs modification -Khaled
//Modified 

#include "Node.h"
#ifndef PriQ_Class
#define PriQ_Class

template <typename T>
class PriQ
{
private:
	Node<T>* Head;
	int count;
public:
	//Constructor
	PriQ()
	{
		Head = nullptr; 
		count=0;
	}
	void PrintPriorityQ()	const
	{
		Node<T>* p = Head;

		while (p)
		{
			cout << p->getItem() << " ";
			p = p->getNext();
		}
	}
	//Function that enqueues the elemtents sorted according to the key
	bool enqueue(T& newEntry,  float newKey)
	{
		//Creating the new node to be inserted 
		Node<T>* temp = new Node<T>(newEntry, newKey);
		Node<T>* ptr;

		//If the entry is in the first place or the list is empty
		if (Head == nullptr || (temp->GetPriority() > Head->GetPriority()))
		{
			temp->setNext(Head);
			Head = temp;
		}
		//General Case
		else
		{
			ptr = Head;
			while (ptr->getNext() != nullptr && ptr->getNext()->GetPriority() >= temp->GetPriority())
				ptr = ptr->getNext();

			temp->setNext(ptr->getNext());
			ptr->setNext(temp);
		}
		count++;
		return true;
	}

	//Function the takes out elements out of the queue
	bool dequeue(T &temp)
	{
		if (isEmpty())
			return false;

		temp = Head->getItem();
		Head = Head->getNext();
		count--;
		return true;

	}

	//Function the checks the first element.
	bool peek(T& frntEntry)  
	{
		if(isEmpty())
			return false;

		frntEntry = Head->getItem();
		return true;

	}

	//Function that checks whether the queue is empty or not
	int GetCount()
	{
		return count;
	}
	bool isEmpty()
	{
		return (Head == NULL);
	}

};
#endif