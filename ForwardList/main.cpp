﻿#include<iostream>
using namespace std;

#define tab "\t"

class Element
{
protected:
	int Data; //значение элемента
	Element* pNext; //указатель на следующий элемент
	static int count;
public:
	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
	{
		count++;
#ifdef DEBUG
		cout << "EConstructor:\t" << this << endl;
#endif // DEBUG
	}
	~Element()
	{
		count--;
#ifdef DEBUG
		cout << "EDestructor:\t" << this << endl;
#endif // DEBUG
	}
	friend class ForwardList;
	friend class ConstIterator;
	friend class Stack;
};
int Element::count = 0;

class ConstIterator
{
	Element* Temp;
public:
	ConstIterator(Element* Temp = nullptr) : Temp(Temp)
	{
#ifdef DEBUG
		cout << "ItConstructor:\t" << this << endl;
#endif //DEBUG

	}
	~ConstIterator()
	{
		cout << "ItDestructor:\t" << this << endl;
	}
	ConstIterator& operator++()
	{
		Temp = Temp->pNext;
		return *this;
	}
	bool operator!=(const ConstIterator& other)const
	{
		return this->Temp != other.Temp;
	}

	int operator*()
	{
		return Temp->Data;
	}
};

class ForwardList
{
protected:
	Element* Head;
	unsigned int size; 
public:
	ConstIterator begin()
	{
		return Head;
	}
	ConstIterator end()
	{
		return nullptr;
	}
	ForwardList()
	{
		Head = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	ForwardList(const ForwardList& other):ForwardList()
	{
		/*for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_back(Temp->Data);*/
		*this = other; //здесь просто вызываем CopyAssignment
		cout << "LCopyConstructor:\t" << this << endl;
	}
	ForwardList(ForwardList&& other)noexcept : ForwardList()
	{
		this->Head = other.Head;
		this->size = other.size;
		other.Head = nullptr;
		other.size = 0;
		cout << "MoveConstructor: " << this << endl;
	}

	ForwardList(const std::initializer_list<int>& il):ForwardList()
	{
		//initializer_list - это контейнер.
		cout << typeid(il.begin()).name() << endl;
		for (int const* it = il.begin(); it != il.end(); it++)
		{
			push_back(*it);
		}
	}

	/*ForwardList* begin()
	{
		return &Head;
	}*/
	/*ForwardList* end()
	{
		return begin() + size;
	}*/

	~ForwardList()
	{
		//while (Head)pop_front();
		while (Head)pop_back();
		//pop_front();
		//pop_back();
		cout << "LDestructor:\t" << this << endl;
	}
	// Operators:
	ForwardList& operator=(const ForwardList& other)
	{
		if (this == &other)return *this;
		while (Head)pop_front();
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_front(Temp->Data);
		reverse();
		cout << "LCopyAssignment:\t" << endl;
		return *this;
	}
	ForwardList& operator=(ForwardList&& other)noexcept
	{
		if (this == &other)return *this;
		//delete[] this->Head;
		while (Head) pop_front();
		this->Head = other.Head;
		this->size = other.size;
		other.Head = nullptr;
		other.size = 0;
		cout << "MoveAssignment: " << this << endl;
		return *this;
	}

	// Adding elements:

	void push_front(int Data) //добавление в начало
	{
		////1) Создаем новый элемент:
		//Element* New = new Element(Data);
		////2) Включаем новый элемент в список
		//New->pNext = Head;
		////3) Переводим Head на новый элемент
		//Head = New;

		Head = new Element(Data, Head);

		size++;
	}
	void push_back(int Data) //Добавление в конец списка
	{
		/*if (Head == nullptr)return;
		if (Head->pNext == nullptr) return pop_front();*/
		if (Head == nullptr)return push_front(Data);
		//if (Head == nullptr || Head->pNext == nullptr)return pop_front();
		//1) Доходим до конца списка
		Element* Temp = Head;
		while (Temp->pNext)
		{
			Temp = Temp->pNext;
		}
		////2) Создаем новый элемент
		//Element* New = new Element(Data);

		////3)Включаем новый элемент в список
		////New->pNext = nullptr;
		//Temp->pNext = New;

		//Element* New = new Element(Data);
		Temp->pNext = new Element(Data);

		size++;
	}

	//void pop_front() //удаление начального элемента списка
	//{
	//	Element* Temp = Head;
	//	Head = Head->pNext;
	//	delete Temp;
	//}

	//void pop_back() //удаление последнего элемента списка
	//{
	//	Element* Temp = Head;
	//	while (Temp->pNext)
	//	{
	//		Temp = Temp->pNext;
	//	}
	//	delete Temp;
	//}

	//void insert(int index, int Data) //вставляет значение в список по указанному индексу
	//{
	//	Element* Temp = Head;
	//	for (int i = 0; i < index; i++)
	//	{
	//		Temp = Temp->pNext; 
	//	}
	//	Element* New = new Element(Data);
	//	
	//}

	//void erase(int index) //удаляет элемент из списка по указанному индексу
	//{
	//
	//}

	//Removing elements:
	void pop_front()
	{
		if (Head == nullptr)return;
		Element* erased = Head; //1) Запоминаем адрес удаляемого элемента
		Head = Head->pNext; //2)Смещаем Голову на следующий элемент (исключаем элемент из списка)
		delete erased; //3)Удаляем элемент из памяти
		size--;
	}

	void pop_back()
	{
		//1) Доходим до предпоследного элемента списка:
		Element* Temp = Head;
		while (Temp->pNext->pNext)
		{
			Temp = Temp->pNext; 
		}
		//2) Удаляем последний элемент из памяти:

		delete Temp->pNext;

		//3) Зануляем указатель на последний элемент
		Temp->pNext = nullptr;
		size--;
	}

	void insert(int Data, int index)
	{
		if (index > Head->count)return;
		if (index == 0) return push_front(Data);
		//1) Доходим до нужного элемента:
		Element* Temp = Head;
		for (int i = 0; i < index-1; i++)
		{
			Temp = Temp->pNext;
		}

		//// 2) Создаем новый элемент
		//Element* New = new Element(Data);
		//// 3) Включаем элемент в список:
		//while (Temp)
		//{
		//	New->pNext = Temp->pNext;
		//	Temp->pNext = New;
		//}

		Temp->pNext = new Element(Data, Temp->pNext);
		 
		size++;
	}
		
	void erase(int index)
	{
		if (index >= size)return;
		if (index == 0) return pop_front();
		//1) Доходим до элемента перед удаляемым:
		Element* Temp = Head;
		for (int i = 0; i < index - 1; i++) Temp = Temp->pNext;
		//2) Запоминаем адрес удаляемого элемента:
		Element* erased = Temp->pNext;
		//3) Исключаем удаляемый элемент из списка:
		Temp->pNext = Temp->pNext->pNext;
		//4) Удаляем элемент из памяти:
		delete erased;
		size--;
	}

	// Methods:

	void reverse()
	{
		ForwardList buffer;
		while (Head)
		{
			buffer.push_front(Head->Data);
			pop_front();
		}
		this->Head = buffer.Head;
		this->size = buffer.size;
		buffer.Head = nullptr;
	}

	void print()const
	{
		cout << "Head:\t" << Head << endl;
		//Element* Temp = Head;  //Temp - это итератор
		////Итератор - это указатель, при помощи которого можно перебирать элементы структуры данных
		//while (Temp)
		//{
		//	cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		//	Temp = Temp->pNext; //Переход на следующий элемент
		//}
		for(Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Количество элементов списка: " << size << endl;
		//cout << "Общее количество элементов списка: " << Head->count << endl;
		cout << "Общее количество элементов списка: " << Element::count << endl;
	}
	
};

class Stack :ForwardList 
{
public:
	const int& top()const
	{
		return Head->Data;
	}
	int& top() // позволяет изменить вершину стека
	{
		return Head->Data;
	}
	int push(int Data)
	{
		push_front(Data);
		return Head->Data;
	}
	int pop()
	{
		int Data = Head->Data;
		pop_front();
		return Data;
	}
	int size()const
	{
		return ForwardList::size;
	}
	bool empty()const
	{
		return Head == nullptr;
	}
	void swap(Stack& other)
	{
		Element* bufferHead = this->Head;
		this->Head = other.Head;
		other.Head = bufferHead;

		int bufferSize = this->size();
		this->ForwardList::size = other.size();
		other.ForwardList::size = bufferSize;
	}
	void info()const
	{
		cout << "\n---------------------------------\n";
		cout << this << ":\n";
		cout << "Size: " << size() << endl;
		for (int i : ForwardList(*this))cout << i << tab; cout << endl;
		cout << "\n---------------------------------\n";
	}
};

void Print(int arr[])
{
	/*for (int i : arr)
	{
		cout << i << tab;
	}
	cout << endl;*/
	cout << typeid(arr).name() << endl;
	cout << sizeof(arr) << endl;
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		cout << arr[i] << tab;
	}
	cout << endl;
}

//#define BASE_CHECK;
//#define COUNT_CHECK;
//#define PERFORMANCE_CHECK;
//#define RANGE_BASED_FOR_ARRAY;
//#define RANGE_BASED_FOR_LIST;

void main()
{
	setlocale(LC_ALL, "");

#ifdef BASE_CHECK
	int n;
	cout << "Введите количество элементов:"; cin >> n;
	ForwardList list;

	for (int i = 0; i < n; i++)
	{
		list.push_back(rand() % 100);
		//list.push_front(rand() % 100);
	}
	list.print();
	/*list.push_back(123);
	list.print();*/
	/*list.pop_front();
	list.print();*/
	/*list.pop_back();
	list.print();*/
	int index;
	int value;
	cout << "Введите индекс нового элемента: "; cin >> index;
	cout << "Введите значение нового элемента: "; cin >> value;
	list.insert(value, index);
	list.print();
	cout << "Введите индекс удаляемого элемента: "; cin >> index;
	list.erase(index);
	list.print();
	//Element element(5);
#endif //BASE_CHECK

#ifdef COUNT_CHECK 
	ForwardList list1;
	list1.push_back(3);
	list1.push_back(5);
	list1.push_back(8);
	list1.push_back(13);
	list1.push_back(21);
	list1.print();

	ForwardList list2;
	list2.push_back(34);
	list2.push_back(55);
	list2.push_back(89);
	list2.print();

#endif //COUNT_CHECK 

#ifdef PERFORMANCE_CHECK
	int n;
	cout << "Введите количество элементов:"; cin >> n;
	ForwardList list;

	for (int i = 0; i < n; i++)
	{
		list.push_front(rand() % 100);
		//list.push_front(rand() % 100);
	}
	cout << "List filled" << endl;
	//list.print();
	ForwardList list2 = list; //CopyConstructor
	//ForwardList list2;
	//list2 = list;
	//list2.print();
	//ForwardList list3;
	//list3 = std::move(list2);
	//list3.print();
	cout << "Copy DONE" << endl;
#endif // PERFORMANCE_CHECK
	
#ifdef RANGE_BASED_FOR_ARRAY 
	int arr[] = { 3, 5, 8, 13, 21, 34, 55, 89, 144 };
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		cout << arr[i] << tab;
	}
	cout << endl;
	//Range-based for:
	//Range (диапозон) в данном контексте понимается как контейнер.
	for (int i : arr)
	{
		cout << i << tab;
	}
	cout << endl;

	Print(arr);
#endif // RANGE_BASED_FOR_ARRAY 

#ifdef RANGE_BASED_FOR_LIST
	ForwardList list = { 3, 5, 8, 13, 21 };
	//list.print();

	for (int i : list)
	{
		cout << i << tab;
	}
	cout << endl;
#endif // RANGE_BASED_FOR_LIST

	Stack stack;
	stack.push(3);
	stack.push(5);
	stack.push(8);
	stack.push(13);
	stack.push(21);
	cout << stack.size() << endl;
	
	/*while (!stack.empty())
	{
		cout << stack.pop() << tab;
	}
	cout << endl;*/

	Stack stack2;
	stack2.push(34);
	stack2.push(55);
	stack2.push(89);
	
	stack.info();
	stack2.info();

	stack.swap(stack2);

	stack.info();
	stack2.info();

}