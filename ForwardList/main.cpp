#include<iostream>
#include "ForwardList.h"
#include "ForwardList.cpp"

//#define BASE_CHECK
//#define COUNT_CHECK
//#define PERFORMANCE_CHECK
//#define RANGE_BASED_FOR_ARRAY
#define RANGE_BASED_FOR_LIST

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

	ForwardList<std::string> list2 = { "Красота", "-", "это", "бесконечность,", "выраженная", "в", "законченной", "форме" };
	for (std::string i : list2)
	{
		cout << i << tab;
	}
	cout << endl;
#endif // RANGE_BASED_FOR_LIST

}