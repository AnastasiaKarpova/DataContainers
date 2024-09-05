#pragma once
#include <iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "\n------------------------------------\n"

template<typename T> class List
{
	class Element
	{
		T Data;
		Element* pNext;
		Element* pPrev;
	public:
		Element(T Data, Element* pNext = nullptr, Element* pPrev = nullptr);
		~Element();
		friend class List;
	}*Head, * Tail;
	size_t size;
	class ConstBaseIterator
	{
	protected:
		Element* Temp;
	public:
		ConstBaseIterator(Element* Temp = nullptr);
		~ConstBaseIterator();
		bool operator==(const ConstBaseIterator& other)const;
		bool operator!=(const ConstBaseIterator& other)const;
		const T& operator*()const;
	};
public:
	class ConstIterator :public ConstBaseIterator
	{
	public:
		ConstIterator(Element* Temp = nullptr);
		~ConstIterator(); 
		ConstIterator& operator++(); //Prefix increment
		ConstIterator operator++(int); //Postfix increment
		ConstIterator& operator--();
		ConstIterator operator--(int);
		// Comparison operators:

		//Dereference operators:
	};
	class ConstReverseIterator :public ConstBaseIterator
	{
	public:
		ConstReverseIterator(Element* Temp = nullptr);
		~ConstReverseIterator();
		// Incremento/Decremento
		ConstReverseIterator& operator++();
		ConstReverseIterator operator++(int);
		ConstReverseIterator& operator--();
		ConstReverseIterator operator--(int);
		// Comparison operators:

		// Dereference operators:


	};
	class Iterator :public ConstIterator
	{
	public:
		Iterator(Element* Temp = nullptr) : ConstIterator(Temp) {}
		~Iterator() {}
		T& operator*();
	};
	class ReverseIterator : public ConstReverseIterator
	{
	public:
		ReverseIterator(Element* Temp = nullptr) : ConstReverseIterator(Temp) {}
		~ReverseIterator() {}
		T& operator*();
	};
	
	ConstIterator begin()const;
	ConstIterator end()const;
	ConstReverseIterator rbegin()const;
	ConstReverseIterator rend()const;
	Iterator begin();
	Iterator end();
	ReverseIterator rbegin();
	ReverseIterator rend();

	//Constructors:
	List();
	List(const std::initializer_list<T>& il);
	List(const List<T>& other);
	~List();

	//Operators
	List<T>& operator= (const List<T>& other);

	// Adding element
	void push_front(T Data);
	void push_back(T Data);

	//Methods:
	void print()const;
	void reverse_print()const;

	//Removing elements:

	void pop_front();
	void pop_back();
	void insert(T Data, int index);
	void erase(int index);
};

//////////////////////////////////////////////////////////////
///////////// List members ///////////////////////////////////
//ConstIterator begin()const;
//ConstIterator end()const;
//ConstReverseIterator rbegin()const;
//ConstReverseIterator rend()const;
//Iterator begin();
//Iterator end();
//ReverseIterator rbegin();
//ReverseIterator rend();
//
////Constructors:
//List();
//List(const std::initializer_list<T>& il);
//List(const List<T>& other);
//~List();
//
////Operators
//List<T>& operator= (const List<T>& other);
//
//// Adding element
//void push_front(T Data);
//void push_back(T Data);
//
////Methods:
//void print()const;
//void reverse_print()const;

//Removing elements:
//
//void pop_front();
//void pop_back();
//void insert(T Data, int index);
//void erase(int index);
//////////////////////////////////////////////////////////////
///////////// List members ///////////////////////////////////
 

template<typename T>List<T> operator+(const List<T>& left, const List<T>& right)
{
	List<T> buffer = left; //CopyConstructor
	for (typename List<T>::ConstIterator it = right.begin(); it != right.end(); ++it)
	{
		buffer.push_back(*it);
		//*it *= 10;
	}
	return buffer;
}
template<typename T>void Grow(List<T>& list)
{
	for (typename List<T>::Iterator it = list.begin(); it != list.end(); ++it)
		*it *= 10;
}
