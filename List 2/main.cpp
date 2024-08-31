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
			Element(int Data, Element* pNext = nullptr, Element* pPrev = nullptr) :Data(Data), pNext(pNext), pPrev(pPrev)
			{
				cout << "EConstructor:\t" << this << endl;
			}
			~Element()
			{
				cout << "EDestructor:\t" << this << endl;
			}
			friend class List;
		}*Head, * Tail;
		size_t size;
		class ConstBaseIterator
		{
		protected:
			Element* Temp;
		public:
			ConstBaseIterator(Element* Temp = nullptr) :Temp(Temp) {}
			~ConstBaseIterator() {}
			bool operator==(const ConstBaseIterator& other)const
			{
				return this->Temp == other.Temp;
			}
			bool operator!=(const ConstBaseIterator& other)const
			{
				return this->Temp != other.Temp;
			}
			const T& operator*()const
			{
				return Temp->Data;
			}
		};
	public:
		class ConstIterator :public ConstBaseIterator
		{
		public:
			ConstIterator(Element* Temp = nullptr) :ConstBaseIterator(Temp)
			{
				cout << "ItConstructor:\t" << this << endl;
			}
			~ConstIterator()
			{
				cout << "ItDestructor:\t" << this << endl;
			}
			ConstIterator& operator++() //Prefix increment
			{
				ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
				return *this;
			}
			ConstIterator operator++(int) //Postfix increment
			{
				ConstIterator old = *this;
				ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
				return old;
			}
			ConstIterator& operator--()
			{
				ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
				return *this;
			}
			ConstIterator operator--(int)
			{
				ConstIterator old = *this;
				ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
				return old;
			}

			// Comparison operators:

			/*bool operator==(const ConstIterator& other)const
			{
				return this->Temp == other.Temp;
			}
			bool operator!=(const ConstIterator& other)const
			{
				return this->Temp != other.Temp;
			}*/

			//Dereference operators:
			/*const int& operator*()const
			{
				return Temp->Data;
			}*/
			/*int& operator*()
			{
				return Temp->Data;
			}*/
		};
		class ConstReverseIterator :public ConstBaseIterator
		{
		public:
			ConstReverseIterator(Element* Temp = nullptr) :ConstBaseIterator(Temp)
			{
				cout << "RItConstructor:\t" << this << endl;
			}
			~ConstReverseIterator()
			{
				cout << "RItDestructor:\t" << this << endl;
			}

			// Incremento/Decremento
			ConstReverseIterator& operator++()
			{
				ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
				return *this;
			}
			ConstReverseIterator operator++(int)
			{
				ConstReverseIterator old = *this;
				ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
				return old;
			}
			ConstReverseIterator& operator--()
			{
				ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext; 
				return *this;
			}
			ConstReverseIterator& operator--(int)
			{
				ConstReverseIterator old = *this;
				ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
				return old;
			}

			// Comparison operators:
			/*bool operator==(const ConstReverseIterator& other)const
			{
				return this->Temp == other.Temp;
			}
			bool operator!=(const ConstReverseIterator& other)const
			{
				return this->Temp != other.Temp;
			}*/

			// Dereference operators:
			/*const int& operator*()const
			{
				return Temp->Data;
			}*/
			/*int& operator*()
			{
				return Temp->Data;
			}*/

		};
		class Iterator :public ConstIterator
		{
		public:
			Iterator(Element* Temp = nullptr) :ConstIterator(Temp) {}
			~Iterator() {}
			T& operator*()
			{
				return ConstBaseIterator::Temp->Data; 
			}
		};
		class ReverseIterator : public ConstReverseIterator
		{
		public:
			ReverseIterator(Element* Temp = nullptr) : ConstReverseIterator(Temp) {}
			~ReverseIterator() {}
			T& operator*()
			{
				return ConstBaseIterator::Temp->Data; 
			}
		};
		ConstIterator begin()const
		{
			return Head;
		}
		ConstIterator end()const
		{
			return nullptr;
		}
		ConstReverseIterator rbegin()const
		{
			return Tail;
		}
		ConstReverseIterator rend()const
		{
			return nullptr;
		}
		Iterator begin()
		{
			return Head;
		}
		Iterator end()
		{
			return nullptr;
		}
		ReverseIterator rbegin()
		{
			return Tail;
		}
		ReverseIterator rend()
		{
			return nullptr;
		}

		//Constructors:
		List()
		{
			Head = Tail = nullptr;
			size = 0;
			cout << "LConstructor:\t" << this << endl;
		}
		List(const std::initializer_list<T>& il) : List()
		{
			for (T const* it = il.begin(); it != il.end(); it++)
			{
				push_back(*it);
			}
		}
		List(const List<T> & other) :List()
		{
			*this = other;
			cout << "CopyConstructor:" << this << endl;
		}
		~List()
		{
			//while (Head)pop_front();
			while (Tail)pop_back();
			cout << "LDestructor:\t" << this << endl;
		}

		//Operators
		List<T>& operator= (const List<T>& other)
		{
			if (this == &other)return *this;
			while (Head)pop_front();
			for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)push_back(Temp->Data);
			cout << "CopyAssigment:\t" << this << endl;
			return *this;
		}

		// Adding element
		void push_front(T Data)
		{
			if (Head == nullptr && Tail == nullptr)
			{
				Head = Tail = new Element(Data);
			}
			else
			{
				/*Element* New = new Element(Data);
				New->pNext = Head;
				Head->pPrev = New;
				Head = New;*/
				Head = new Element(Data, Head);
			}
			size++;
		}
		void push_back(T Data)
		{
			if (Head == nullptr && Tail == nullptr)
			{
				Head = Tail = new Element(Data);
			}
			else
			{
				/*Element* New = new Element(Data);
				New->pPrev = Tail;
				Tail->pNext = New;
				Tail = New;*/
				Tail->pPrev = new Element(Data);
			}
			size++;
		}


		//Methods:
		void print()const
		{
			cout << delimiter << endl;
			cout << "Head:\t" << Head << endl;
			for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			{
				cout << Temp->pPrev << tab
					<< Temp << tab
					<< Temp->Data << tab
					<< Temp->pNext << endl;
			}
			cout << "Tail:\t" << Tail << endl;
			cout << "Количество элементов списка: " << size << endl;
			cout << delimiter << endl;
		}
		void reverse_print()const
		{
			cout << delimiter << endl;
			cout << "Tail:\t" << Tail << endl;
			for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
			{
				cout << Temp->pPrev << tab
					<< Temp << tab
					<< Temp->Data << tab
					<< Temp->pNext << endl;
			}
			cout << "Head:\t" << Head << endl;
			cout << delimiter << endl;
		}

		//Removing elements:

		void pop_front()
		{
			if (Head == nullptr && Tail == nullptr)return;
			if (Head == Tail)
			{
				delete Head;
				Head = Tail = nullptr;
			}
			else
			{
				Head = Head->pNext;
				delete Head->pPrev;
				Head->pPrev = nullptr;
			}
			size--;
		}

		void pop_back()
		{
			if (Head == nullptr && Tail == nullptr)return;
			if (Head == Tail)
			{
				delete Tail;
				Head = Tail = nullptr;
			}
			else
			{
				Tail = Tail->pPrev;
				delete Tail->pNext;
				Tail->pNext = nullptr;
			}
			size--;
		}
		void insert(T Data, int index)
		{
			if (index < 0 || index > size) return;
			if (index == 0) push_front(Data);
			if (index == size) push_back(Data);
			Element* Temp;
			if (index < size / 2)
			{
				Temp = Head;
				for (int i = 0; i < index; i++)
				{
					Temp = Temp->pNext;
				}
			}
			else
			{
				Temp = Tail;
				for (int i = index; i < size - 1; i++)
				{
					Temp = Temp->pPrev;
				}
			}
			Element* New = new Element(Data);
			New->pNext = Temp;
			New->pPrev = Temp->pPrev;
			Temp->pPrev->pNext = New;
			Temp->pPrev = New;
			size++;
		}
		void erase(int index)
		{
			if (index <0 || index > size) return;
			Element* Temp;
			if (index < size / 2)
			{
				Temp = Head;
				for (T i = 0; i < index; i++)
				{
					Temp = Temp->pNext;
				}
			}
			else
			{
				Temp = Tail;
				for (T i = size - 1; i > index; i--)
				{
					Temp = Temp->pPrev;
				}
			}
			Temp->pPrev->pNext = Temp->pNext;
			if (Temp->pNext != nullptr)
			{
				Temp->pNext->pPrev = Temp->pPrev;
			}
			delete Temp;
			size--;
		}
	};


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
	

//#define BASE_CHECK

void main()
{
	setlocale(LC_ALL, "");
	
#ifdef BASE_CHECK
	int n;
	cout << "Введите количество элементов: "; cin >> n;
	List list;
	for (int i = 0; i < n; i++)
	{
		//list.push_front(rand() % 100);
		list.push_back(rand() % 100);
	}
	list.print();
	list.reverse_ptint();
	for (int i = 0; i < 100; i++)list.pop_back();
	list.reverse_ptint();
#endif // BASE_CHECK

	//List list = { 3, 5, 8, 13, 21 };
	List<int> list1 = { 3, 5, 8, 13, 21 };
	List<int> list2 = {34, 55, 89}; 
	List<int> list3 = list1 + list2; 
	//List list4 = list3 - list2;
	//List list2 = { 32, 37, 43, 49, 55 };
	//List list3 = list1 + list2;
	//list.print();
	//list.reverse_print();
	for (int i : list1)cout << i << tab; cout << endl;
	for (int i : list2)cout << i << tab; cout << endl;
	for (int i : list3)cout << i << tab; cout << endl;
	Grow(list3);
	for (int i : list3)cout << i << tab; cout << endl;
	//for (int i : list4)cout << i << tab; cout << endl;
	/*for (List::ReverseIterator it = list3.rbegin(); it != list3.rend(); it++)
	{
		cout << *it << tab;
	}
	cout << endl;*/
	/*ist3.print();
	list3.reverse_print();*/
}