#include "ForwardList.h"

template<typename T>ForwardList<T>::Element::Element(T Data, Element* pNext) :Data(Data), pNext(pNext)
{
	count++;
#ifdef DEBUG
	cout << "EConstructor:\t" << this << endl;
#endif // DEBUG
}
template<typename T>ForwardList<T>::Element::~Element()
{
	count--;
#ifdef DEBUG
	cout << "EDestructor:\t" << this << endl;
#endif // DEBUG
}
template<typename T>bool ForwardList<T>::ConstBaseIterator::operator==(const ConstBaseIterator& other)const
{
	return this->Temp == other.Temp;
}
template<typename T>bool ForwardList<T>::ConstBaseIterator::operator!=(const ConstBaseIterator& other)const
{
	return this->Temp != other.Temp;
}
template<typename T>const T& ForwardList<T>::ConstBaseIterator::operator*() const
{
	return Temp->Data;
}

template<typename T>typename ForwardList<T>::ConstIterator& ForwardList<T>::ConstIterator:: operator++()
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return *this;
}

template<typename T>T& ForwardList<T>::Iterator::operator*()
{
	return ConstBaseIterator::Temp->Data;
}

template<typename T>typename ForwardList<T>::ConstIterator ForwardList<T>::begin() const
{
	return Head;
}
template<typename T>typename ForwardList<T>::ConstIterator ForwardList<T>::end() const
{
	return nullptr;
}
template<typename T>typename ForwardList<T>::Iterator ForwardList<T>::begin()
{
	return Head;
}
template<typename T>typename ForwardList<T>::Iterator ForwardList<T>::end()
{
	return nullptr;
}

template<typename T>ForwardList<T>::ForwardList()
{
	Head = nullptr;
	size = 0;
	cout << "LConstructor:\t" << this << endl;
}
template<typename T>ForwardList<T>::ForwardList(const ForwardList<T>& other) :ForwardList()
{
	/*for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
		push_back(Temp->Data);*/
	*this = other; //здесь просто вызываем CopyAssignment
	cout << "LCopyConstructor:\t" << this << endl;
}
template<typename T>ForwardList<T>::ForwardList(ForwardList<T>&& other)noexcept : ForwardList()
{
	this->Head = other.Head;
	this->size = other.size;
	other.Head = nullptr;
	other.size = 0;
	cout << "MoveConstructor: " << this << endl;
}
template<typename T>ForwardList<T>::ForwardList(const std::initializer_list<T>& il) :ForwardList()
{
	//initializer_list - это контейнер.
	//cout << typeid(il.begin()).name() << endl;
	for (T const* it = il.begin(); it != il.end(); it++)
	{
		push_back(*it);
	}
}
template<typename T>ForwardList<T>::~ForwardList()
{
	//while (Head)pop_front();
	while (Head)pop_back();
	//pop_front();
	//pop_back();
	cout << "LDestructor:\t" << this << endl;
}

template<typename T>ForwardList<T>& ForwardList<T>::operator=(const ForwardList& other)
{
	if (this == &other)return *this;
	while (Head)pop_front();
	for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
		push_front(Temp->Data);
	reverse();
	cout << "LCopyAssignment:\t" << endl;
	return *this;
}
template<typename T>ForwardList<T>& ForwardList<T>::operator=(ForwardList&& other) noexcept
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

template<typename T>void ForwardList<T>::push_front(T Data)
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
template<typename T>void ForwardList<T>::push_back(T Data)
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

template<typename T>void ForwardList<T>::pop_front()
{
	if (Head == nullptr)return;
	Element* erased = Head; //1) Запоминаем адрес удаляемого элемента
	Head = Head->pNext; //2)Смещаем Голову на следующий элемент (исключаем элемент из списка)
	delete erased; //3)Удаляем элемент из памяти
	size--;
}
template<typename T>void ForwardList<T>::pop_back()
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

template<typename T>void ForwardList<T>::insert(T Data, int index)
{
	if (index > Head->count)return;
	if (index == 0) return push_front(Data);
	//1) Доходим до нужного элемента:
	Element* Temp = Head;
	for (int i = 0; i < index - 1; i++)
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
template<typename T>void ForwardList<T>::erase(T index)
{
	if (index >= size)return;
	if (index == 0) return pop_front();
	//1) Доходим до элемента перед удаляемым:
	Element* Temp = Head;
	for (T i = 0; i < index - 1; i++) Temp = Temp->pNext;
	//2) Запоминаем адрес удаляемого элемента:
	Element* erased = Temp->pNext;
	//3) Исключаем удаляемый элемент из списка:
	Temp->pNext = Temp->pNext->pNext;
	//4) Удаляем элемент из памяти:
	delete erased;
	size--;
}

template<typename T>void ForwardList<T>::reverse()
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

template<typename T>void ForwardList<T>::print() const
{
	cout << "Head:\t" << Head << endl;
	//Element* Temp = Head;  //Temp - это итератор
	////Итератор - это указатель, при помощи которого можно перебирать элементы структуры данных
	//while (Temp)
	//{
	//	cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
	//	Temp = Temp->pNext; //Переход на следующий элемент
	//}
	for (Element* Temp = Head; Temp; Temp = Temp->pNext)
		cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
	cout << "Количество элементов списка: " << size << endl;
	//cout << "Общее количество элементов списка: " << Head->count << endl;
	cout << "Общее количество элементов списка: " << Element::count << endl;
}

template<typename T>void Print(T arr[])
{
	/*for (int i : arr)
	{
		cout << i << tab;
	}
	cout << endl;*/
	cout << typeid(arr).name() << endl;
	cout << sizeof(arr) << endl;
	for (T i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		cout << arr[i] << tab;
	}
	cout << endl;
}