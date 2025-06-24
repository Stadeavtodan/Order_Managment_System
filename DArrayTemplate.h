#pragma once
#include <iostream>
using namespace std;
#include <cstdlib>
#include <ctime>

template <typename T>
void createMemory(T**& matr, int row, int col)
{
    // 1 - Виділення динамічної памяті
    // 1.1 - Створюємо масив покажчиків (масив одновимірних масивів)
    matr = new T* [row];
    cout << "DArray: " << matr << endl;
    // 1.2 До кожної адреси привязуємо масив значень
    for (int i = 0; i < row; i++)
    {
        matr[i] = new T[col];
        cout << "int Array: " << matr[i] << endl;
    }
    cout << "-------------------------\n\n";
}

template <typename T>
void randArray(T** matr, int row, int col, int A = 1, int B = 10)
{
    for (int i = 0; i < row; i++){
        for (int j = 0; j < col; j++){
            matr[i][j] = rand() % (B - A + 1) + A;
        }
    }
}

template <typename T>
void printArray(T** matr, int row, int col, int w_out = 4)
{
    for (int i = 0; i < row; i++){
        for (int j = 0; j < col; j++){
            cout.width(w_out);
            cout << matr[i][j];
        }
        cout << endl;
    }
    cout << "----------------------------\n\n";
}

template <typename T>
void freeMemory(T**& matr, int& row, int& col){
    // 3 - звільнення памяті
    // 3.1 - звільнюємо по черзі масиви значень
    for (int i = 0; i < row; i++)
    {
        cout << "Delete int array: " << matr[i] << endl;
        delete[] matr[i];
    }
    // 3.2 - звільняємо масив покажчиків
    cout << "Delete Darray: " << matr << endl;
    delete[] matr;

    matr = nullptr;
    row = col = 0;
}

template <typename T>
void addRow(T**& matr, int& row, int col, int n){
    if(n < 0 || n > row){return;}
    T** temp = new T*[row + 1];
    for (int i = 0; i < row + 1; i++){
        if(i < n){temp[i] = matr[i];}
        else if(i == n){temp[i] = new T[col]{0};}
        else{temp[i] = matr[i - 1];}
    }
    delete[] matr;
    matr = temp;
    row++;
}

template <typename T>
void addCOl(T**& matr, int row, int& col, int n){
    if (n < 0 || n > col){return;}
    for (int i = 0; i < row; i++){
        T* line = new T[col + 1];
        for (int j = 0; j < col + 1; j++){
            if (j < n){line[j] = matr[i][j];}
            else if (j == n){line[j] = 0;}
            else{line[j] = matr[i][j + 1];}
        }
        delete[] matr[i];
        matr[i] = line;
    }
    col++;
}

template <typename T>
void moveRow(T** matr, int row, int col){
    for (int i = row - 1; i > 0; i--){
        swap(matr[i], matr[i - 1]);
    }
}

template <typename T>
void moveRow2(T** matr, int row, int col){
    for (int i = row - 1; i > 0; i--){
        swap(matr[i], matr[i - 1]);
    }
}


//template <typename T>
//void delRow(T**& matr, int& row, int col, int n){
//    if(n < 0 || n >= row){return;}
//
//    delete[] matr[n];
//
//    T** temp = new T*[row - 1];
//
//    for (int i = 0; i < row + 1; i++){
//        if(i == n){continue;}
//        temp[i++] = matr[i];
//    }
//    delete[] matr;
//    matr = temp;
//    row--;
//}