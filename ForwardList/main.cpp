#include<iostream>
#include "ForwardList.h"
#include "ForwardList.cpp"

//#define BASE_CHECK
//#define COUNT_CHECK
//#define PERFORMANCE_CHECK
//#define RANGE_BASED_FOR_ARRAY
#define RANGE_BASED_FOR_LIST

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