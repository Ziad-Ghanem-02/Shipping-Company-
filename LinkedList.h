#pragma once
#include "Node.h"
#include "Cargo.h"
template <typename T>
class LinkedList
{
private:
	Node<T> *Head;	//Pointer to the head of the list
	//You can add tail pointer too (depending on your problem)
	int count;
public:


	LinkedList()
	{
		Head = nullptr;
		count=0;
	}

	//List is being desturcted ==> delete all items in the list
	~LinkedList()
	{
		DeleteAll(); 
	}
	////////////////////////////////////////////////////////////////////////
	/*
	* Function: PrintList.
	* prints the values of all nodes in a linked list.
	*/
	void PrintList()	const
	{		
		Node<T> *p = Head;

		while(p)
		{
			cout << p->getItem() << " ";
			p = p->getNext();
		}
	}
	////////////////////////////////////////////////////////////////////////
	/*
	* Function: InsertBeg.
	* Creates a new node and adds it to the beginning of a linked list.
	* 
	* Parameters:
	*	- data : The value to be stored in the new node.
	*/
	void InsertBeg(const T &data)
	{
		Node<T> *R = new Node<T>(data);
		R->setNext(Head);
		Head = R;
		count++;
	}
	void Insert(const T& Item)
	{
		Node<T>* R = new Node<T>(Item);
		R->setNext(nullptr);
		Node<T>* p = Head;
		if (p)
		{
			while (p->getNext())
				p = p->getNext();
			p->setNext(R);

		}
		else
		{
			Head = R;
		}
		count++;
	}
	bool insertsorted(LinkedList& L, T val)
	{
		Node<T>* LL = L.Head;
		//Node<T>* temp;
		Node<T>* ptr = new Node<T>(val);
		while (LL)
		{
			if (LL->getNext() == NULL && val > LL->getItem())
			{
				ptr->setNext(LL->getNext());
				LL->setNext(ptr);
				return true;
			}
			else if ((LL->getItem() < val) && (LL->getNext()->getItem() > val))
			{
				//temp = LL;
				ptr->setNext(LL->getNext());
				LL->setNext(ptr);
				return true;
			}

			{
				LL = LL->getNext();
			}
		}
		return false;
	}
	////////////////////////////////////////////////////////////////////////
	/*
	* Function: DeleteAll.
	* Deletes all nodes of the list.
	*/
	void DeleteAll()
	{
		Node<T> *P = Head;
		while (Head)
		{
			P = Head->getNext();
			delete Head;
			Head = P;
		}
	}

	int GetNItems()
	{
		int counter=0;
		Node<T>* p=Head;
		while(p)
		{
			counter++;
			p=p->getNext();
		}
		return counter;
	}

	bool Find(T Key)
	{
		Node<T>* f = Head;
		while (f)
		{
			if (f->getItem() == Key)
				return true;
			else f = f->getNext();
		}
		return false;
	}
	//[4] DeleteFirst
	//Deletes the first node in the list
	T DeleteFirst()
	{
		T x;
		Node<T>* temp = Head;
		if(temp!=nullptr)
		{
			x=Head->getItem();
			Head = Head->getNext();
			delete temp;
			return x;
		}
		else
			return false;
	}
	//[5] DeleteLast
	//Deletes the last node in the list
	void DeleteLast()
	{
		Node<T>* ptr = Head;
		Node <T>* temp;
		while (ptr->getNext() && Head != NULL)
		{
			temp = ptr;
			ptr = ptr->getNext();
		}
		delete ptr;
		temp->setNext(NULL);
	}

	//[6] DeleteNode
	//deletes the first node with the given value (if found) and returns true
	//if not found, returns false
	//Note: List is not sorted
	bool DeleteNode(const T& value)
	{
		Node<T>* ptr = Head;
		Node <T>* prev = Head;
		Node <T>* Nextp;
		while (ptr)
		{
			Nextp = ptr->getNext();
			if (Nextp == NULL)
			{
				DeleteLast();
				return true;
			}
			else if (Head->getItem() == value)
			{
				DeleteFirst();
				return true;
			}
			else if (ptr->getItem() == value)
			{
				prev->setNext(Nextp);
				delete ptr;
				return true;
			}
			prev = ptr;
			ptr = ptr->getNext();
		}
		return false;
	}
	/*T DeleteID( T value)
	{
	T x;
	Node<T>* ptr = Head;
	Node <T>* prev = Head;
	Node <T>* Nextp;
	while (ptr)
	{
	Nextp = ptr->getNext();

	if (Head->getItem() == value)
	{
	x = Head->getItem();
	DeleteFirst();
	return x;
	}
	else if (ptr->getItem() == value)
	{
	prev->setNext(Nextp);
	x = ptr->getItem();
	delete ptr;
	return x;
	}
	prev = ptr;
	ptr = ptr->getNext();
	}
	return false;
	}*/
	Cargo* DeleteID(Cargo* value)
	{
		Cargo* x;
		Node<Cargo*>* ptr = Head;
		Node <Cargo*>* prev = Head;
		Node <Cargo*>* Nextp;
		while (ptr)
		{
			Nextp = ptr->getNext();
			if(Head->getItem()->GetID()==value->GetID())
			{

				x = Head->getItem();
				DeleteFirst();
				count--;
				return x;
			}
			else if (ptr->getItem()->GetID() == value->GetID())
			{
				prev->setNext(Nextp);
				x = ptr->getItem();
				delete ptr;
				count--;
				return x;
			}
			prev = ptr;
			ptr = ptr->getNext();
		}
		return false;
	}

	bool is_Empty()
	{
		return Head==nullptr;
	}
	bool peek(T& Data) 
	{
		if (is_Empty())
			return false;
		Data = Head->getItem();
		return true;
	}

};
