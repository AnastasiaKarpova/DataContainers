#pragma once
#include <iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"

template<typename T>class ForwardList
{
	class Element
	{
	protected:
		T Data; //значение элемента
		Element* pNext; //указатель на следующий элемент
		static int count;
	public:
		Element(T Data, Element* pNext = nullptr);
		~Element();
		friend class ForwardList;
		//friend class ConstIterator;
	} *Head;

	int Element::count = 0;

	unsigned int size;
	class ConstBaseIterator
	{
	protected:
		Element* Temp;
	public:
		ConstBaseIterator(Element* Temp = nullptr) :Temp(Temp) {}
		~ConstBaseIterator() {}
		bool operator==(const ConstBaseIterator& other)const;
		bool operator!=(const ConstBaseIterator& other)const;
		const T& operator*()const;
	};
public:
	class ConstIterator : public ConstBaseIterator
	{
	public:
		ConstIterator(Element* Temp = nullptr) : ConstBaseIterator(Temp)
		{
			cout << "ItConstructor:\t" << this << endl;
		}
		~ConstIterator()
		{
			cout << "ItDestructor:\t" << this << endl;
		}
		ConstIterator& operator++();
		/*ConstIterator& operator++(int)
		{
			ConstIterator old = *this;
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
			return old;
		}*/
	};
	class Iterator :public ConstIterator
	{
	public:
		Iterator(Element* Temp = nullptr) :ConstIterator(Temp) {}
		~Iterator() {}
		T& operator*();
	};
	ConstIterator begin()const;
	ConstIterator end()const;
	Iterator begin();
	Iterator end();
	ForwardList();
	ForwardList(const ForwardList<T>& other);
	ForwardList(ForwardList<T>&& other)noexcept;

	ForwardList(const std::initializer_list<T>& il);

	/*ForwardList(const ForwardList<T>& other) :ForwardList()
	{
		*this = other;
		cout << "CopyConstructor:" << this << endl;
	}*/

	/*ForwardList* begin()
	{
		return &Head;
	}*/
	/*ForwardList* end()
	{
		return begin() + size;
	}*/

	~ForwardList();
	// Operators:
	ForwardList<T>& operator=(const ForwardList& other);
	ForwardList<T>& operator=(ForwardList&& other)noexcept;

	// Adding elements:

	void push_front(T Data);
	void push_back(T Data);

	//Removing elements:
	void pop_front();

	void pop_back();

	void insert(T Data, int index);

	void erase(T index);

	// Methods:

	void reverse();

	void print()const;
};

template <typename T>void Print(T arr[]);
