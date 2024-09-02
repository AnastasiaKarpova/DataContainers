#include <iostream>
#include "List.h"

#define tab "\t"
#define delimiter "\n------------------------------------\n"

//#define BASE_CHECK
//#define BASE_CHECK_INT 

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

#ifdef BASE_CHECK_INT
	//List list = { 3, 5, 8, 13, 21 };
	List<int> list1 = { 3, 5, 8, 13, 21 };
	List<int> list2 = { 34, 55, 89 };
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
	/*list3.print();
	list3.reverse_print();*/
#endif // BASE_CHECK_INT

	List<double> list1 = { 2.4, 5.7, 11.3, 15.9 };
	for (double i : list1)cout << i << tab; cout << endl;
	for (List<double>::Iterator it = list1.begin(); it != list1.end(); it++)
	{
		cout << *it << tab;
	}
	for (List<double>::ReverseIterator it = list1.rbegin(); it != list1.rend(); it++)
	{
		cout << *it << tab;
	}
	list1.print();
	
	List<std::string> list2 = { "Красота", "-", "это", "бесконечность,", "выраженная", "в", "законченной", "форме"};
	for (std::string i : list2)cout << i << tab; cout << endl;
	for (List<std::string>::Iterator it = list2.begin(); it != list2.end(); it++)
	{
		cout << *it << tab;
	}
	for (List<std::string>::ReverseIterator it = list2.rbegin(); it != list2.rend(); it++)
	{
		cout << *it << tab;
	}
}