#include <iostream>
using namespace std;

#define tab "\t"

class Element
{
protected:
	int Data;
	Element* pNext;
	Element* pPrev;
	static int count;
public:
	Element(int Data, Element* pNext = nullptr, Element* pPrev = nullptr) :Data(Data), pNext(pNext), pPrev(pPrev)
	{
		count++;
		cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		count--;
		cout << "EDestructor:\t" << this << endl;
	}
	friend class DoubleLinkedList;
};
int Element::count = 0;

class DoubleLinkedList
{
	Element* Head;
	Element* Tail;
	unsigned int size;
public:
	DoubleLinkedList()
	{
		Head = nullptr;
		Tail = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	DoubleLinkedList(const DoubleLinkedList& other) :DoubleLinkedList()
	{
		*this = other;
		cout << "LCopyConstructor:\t" << this << endl;
	}
	~DoubleLinkedList()
	{
		//while (Head)pop_front();
		//while (Head)pop_back();
		//pop_front();
		//pop_back();
		cout << "LDestructor:\t" << this << endl;
	}

	void push_front(int Data) 
	{
		Element* New = new Element(Data);
		
		New->pNext = Head;
		if (Head != NULL) Head->pPrev = New;
		if (Tail == NULL) Tail = New;
		Head = New;

		size++;
	}

	void push_back(int Data)
	{
		if (Head == nullptr)return push_front(Data);
		
		Element* New = new Element(Data);

		New->pPrev = Tail;
		if (Tail != NULL) Tail->pNext = New;
		if (Head == NULL)Head = New;
		Tail = New;
				
		size++;
	}

	void pop_front()
	{
		if (Head == nullptr)return;
		Element* erased = Head;
		Head = Head->pNext;
		if (erased != NULL) erased->pPrev = NULL;
		else Tail = NULL;
		delete erased;
		size--;
	}

	void pop_back()
	{
		if (Tail == NULL) return;
		Element* New = Tail->pPrev;
		if (New != NULL) New->pNext = NULL;
		else Head = NULL;
		delete Tail;
		Tail = New;
		size--;
	}

	void insert(int Data, int index)
	{
		

		size++;
	}

	void erase(int index)
	{
		
		size--;
	}

	void print()const
	{
		cout << "Head:\t" << Head << endl;
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Количество элементов списка: " << size << endl;
		cout << "Общее количество элементов списка: " << Element::count << endl;
	}
};

void main()
{
	setlocale(LC_ALL, "");
	int n;
	cout << "Введите количество элементов:"; cin >> n;
	DoubleLinkedList list;

	for (int i = 0; i < n; i++)
	{
		list.push_back(rand() % 100);
		//list.push_front(rand() % 100);
	}
	list.print();
	//list.push_back(77);
	//list.print();
	/*list.pop_front();
	list.print();*/
	/*list.pop_back();
	list.print();*/
	/*int index;
	int value;
	cout << "Введите индекс нового элемента: "; cin >> index;
	cout << "Введите значение нового элемента: "; cin >> value;
	list.insert(value, index);
	list.print();
	cout << "Введите индекс удаляемого элемента: "; cin >> index;
	list.erase(index);
	list.print();*/
}