#pragma once
#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;

//Заповнити масив випадковими числами від 1 до 10
template <typename T>
void randArray(T arr[], int size, int a = 1, int b = 10){
	for (int i = 0; i < size; i++)	{
		arr[i] = rand() % (b - a + 1) + a;
	}
}

//Виведення масиву на екран
template <typename T>
void printArray(T arr[], int size, int w_cout = 5){
	for (int i = 0; i < size; i++)	{
		cout.width(w_cout);
		cout << arr[i];
	}
	cout << endl;
}

// Функція, яка додає новий елемент масиву в кінець
template <typename T>
void addItemBack(T*& arr, int& size, T value){
    //1 - Створюємо масив на одну клітинку більше
    T* tmp = new T[size + 1];

    //2 - Перенесимо дані зі старого масиву до нового
    for (int i = 0; i < size; i++){
        tmp[i] = arr[i];
    }

    //3 - Видаляємо старий масив
    delete[] arr;

    //4 - Оновлюємо розміру масиву
    size++;

    //5 - Вносимо значення в останню клітинку
    tmp[size - 1] = value;

    //6 - Переприв'язуємо покажчик на новий масив
    arr = tmp;
}

// Функція, яка додає новий елемент масиву в початок
template <typename T>
void addItemFront(T*&arr, int& size, T value){
    //1 - Створюємо масив на одну клітинку більше
    T* tmp = new T[size + 1];

    //2 - Перенесимо дані зі старого масиву до нового
    for (int i = 0; i < size; i++){
        tmp[i + 1] = arr[i];
    }

    //3 - Видаляємо старий масив
    delete[] arr;

    //4 - Оновлюємо розміру масиву
    size++;

    //5 - Вносимо значення в останню клітинку
    tmp[0] = value;

    //6 - Переприв'язуємо покажчик на новий масив
    arr = tmp;
}

// Функція, яка видаляє K елемент масиву.
template <typename T>
void delItem(T*&arr, int& size, T k){
    if (k < 0 || k >= size){
        return;
    }
    T* tmp = new T[size - 1];
    for (int i = 0, j = 0; i < size; i++){
        if(i != k){
            tmp[j] = arr[i];
            j++;
        }
    }
    delete[] arr;

    size--;

    arr = tmp;
}

// Функція, яка видаляє перший парний елемент
template <typename T>
void delFirstEvenItem(T*& arr, int& size){
    int index = -1;

    for (int i = 0; i < size; i++){
        if(arr[i] % 2 == 0){
            index = i;
            break;
        }
    }
    if (index == -1) return;

    T* tmp = new T[size - 1];

    for (int i = 0, j = 0; i < size; i++){
        if(i != index){
            tmp[j++] = arr[i];
        }
    }
    delete[] arr;

    size--;

    arr = tmp;
}

// функція, яка визначає кількість елементів масиву за критерієм, наприклад: чи додатнє число
template <typename T>
int myCountIf(T* arr, int size, bool(*pFunc)(T))
{
    int amount = 0;

    for (int i = 0; i < size; i++)
    {
        if(pFunc(arr[i]) == true)
            amount++;
    }

    return amount;
}

// функція, яка визначає суму елементів масиву за критерієм
template <typename T>
T mySumIf(T* arr, int size, bool(*pFunc)(T))
{
    T sum = 0;

    for (int i = 0; i < size; i++)
    {
        if(pFunc(arr[i]))
            sum += arr[i];
    }

    return sum;
}

//функція, яка знаходить Індекс першого елемента масиву за критерієм
template <typename T>
int myFindIf(T* arr, int size, bool(*pFunc)(T))
{
    for (int i = 0; i < size; i++)
    {
        if(pFunc(arr[i]))
            return i;
    }
    return -1;
}

//функція, яка в масиві замінює елементи за критерієм на значення value
template <typename T>
void myReplaceIf(T* arr, int size, bool(*pFunc)(T), T value)
{
    for (int i = 0; i < size; i++)
    {
        if(pFunc(arr[i]))
            arr[i] = value;
    }
}

//функція, яка в масиві видаляє елементи за критерієм
//template <typename T>
//void myRemoveIf(T*& arr, int& size, bool(*pFunc)(T))
//{
//    for (int i = 0; i < size; i++)
//    {
//        if(pFunc(arr[i]))
//            delItem(arr, size, i);
//            i--;
//    }
//}


//функція знаходження мінімального або максимального числа в масиві
template <typename T>
int findMinMax(T* arr, int size, bool(*pFunc)(T, T))
{
    T m = arr[0];
    int index = 0;
    for (int i = 1; i < size; i++)
    {
        if (pFunc(arr[i], m))
        {
            m = arr[i];
            index = i;
        }
    }
    return index;
}


char randchar()
{
    bool A = rand() % 2;
    if (A == 1)
        return rand() % 26 + 'A';
    else
        return rand() % 26 + 'a';
}

int calc(const char* math)
{
    int result = math[0] - '0';

    for(int i = 1; i < strlen(math); i++)
    {
        if(math[i] == '+') result += math[i + 1] - '0';
        if(math[i] == '-') result -= math[i + 1] - '0';
    }
    return result;
}