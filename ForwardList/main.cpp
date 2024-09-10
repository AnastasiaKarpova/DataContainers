#include<iostream>
#include "ForwardList.h"
#include "ForwardList.cpp"

//#define BASE_CHECK
//#define COUNT_CHECK
//#define PERFORMANCE_CHECK
//#define RANGE_BASED_FOR_ARRAY
#define RANGE_BASED_FOR_LIST

	//void insert(int index, int Data) //��������� �������� � ������ �� ���������� �������
	//{
	//	Element* Temp = Head;
	//	for (int i = 0; i < index; i++)
	//	{
	//		Temp = Temp->pNext; 
	//	}
	//	Element* New = new Element(Data);
	//	
	//}

	//void erase(int index) //������� ������� �� ������ �� ���������� �������
	//{
	//
	//}

	//Removing elements:
	void pop_front()
	{
		if (Head == nullptr)return;
		Element* erased = Head; //1) ���������� ����� ���������� ��������
		Head = Head->pNext; //2)������� ������ �� ��������� ������� (��������� ������� �� ������)
		delete erased; //3)������� ������� �� ������
		size--;
	}

	void pop_back()
	{
		//1) ������� �� �������������� �������� ������:
		Element* Temp = Head;
		while (Temp->pNext->pNext)
		{
			Temp = Temp->pNext; 
		}
		//2) ������� ��������� ������� �� ������:

		delete Temp->pNext;

		//3) �������� ��������� �� ��������� �������
		Temp->pNext = nullptr;
		size--;
	}

	void insert(int Data, int index)
	{
		if (index > Head->count)return;
		if (index == 0) return push_front(Data);
		//1) ������� �� ������� ��������:
		Element* Temp = Head;
		for (int i = 0; i < index-1; i++)
		{
			Temp = Temp->pNext;
		}

		//// 2) ������� ����� �������
		//Element* New = new Element(Data);
		//// 3) �������� ������� � ������:
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
		//1) ������� �� �������� ����� ���������:
		Element* Temp = Head;
		for (int i = 0; i < index - 1; i++) Temp = Temp->pNext;
		//2) ���������� ����� ���������� ��������:
		Element* erased = Temp->pNext;
		//3) ��������� ��������� ������� �� ������:
		Temp->pNext = Temp->pNext->pNext;
		//4) ������� ������� �� ������:
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
		//Element* Temp = Head;  //Temp - ��� ��������
		////�������� - ��� ���������, ��� ������ �������� ����� ���������� �������� ��������� ������
		//while (Temp)
		//{
		//	cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		//	Temp = Temp->pNext; //������� �� ��������� �������
		//}
		for(Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "���������� ��������� ������: " << size << endl;
		//cout << "����� ���������� ��������� ������: " << Head->count << endl;
		cout << "����� ���������� ��������� ������: " << Element::count << endl;
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
#define RANGE_BASED_FOR_LIST;

void main()
{
	setlocale(LC_ALL, "");

#ifdef BASE_CHECK
	int n;
	cout << "������� ���������� ���������:"; cin >> n;
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
	cout << "������� ������ ������ ��������: "; cin >> index;
	cout << "������� �������� ������ ��������: "; cin >> value;
	list.insert(value, index);
	list.print();
	cout << "������� ������ ���������� ��������: "; cin >> index;
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
	cout << "������� ���������� ���������:"; cin >> n;
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
	//Range (��������) � ������ ��������� ���������� ��� ���������.
	for (int i : arr)
	{
		cout << i << tab;
	}
	cout << endl;

	Print(arr);
#endif // RANGE_BASED_FOR_ARRAY 

#ifdef RANGE_BASED_FOR_LIST
	ForwardList<int> list = { 3, 5, 8, 13, 21 };
	//list.print();

	for (int i : list)
	{
		cout << i << tab;
	}
	cout << endl;

	ForwardList<double> list1 = { 1.4, 5.6, 3.12, 13.7, 22.3 };
	for (double i : list1)
	{
		cout << i << tab;
	}
	cout << endl;

	ForwardList<std::string> list2 = { "�������", "-", "���", "�������������,", "����������", "�", "�����������", "�����" };
	for (std::string i : list2)
	{
		cout << i << tab;
	}
	cout << endl;
#endif // RANGE_BASED_FOR_LIST

}