#pragma once
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iomanip>
using namespace std;

struct Order{
    int orderNumber;
    char clientName[100] = "undefined";
    char** dishList = nullptr;
    int dishQuantity = 0;
    double cash = 0;
    bool isCompleted = false;

    void showOrder(){
        cout << "Order #" << orderNumber << "\n";
        cout << "Client: " << clientName << "\n";
        cout << "Dishes: \n";
        for(int i = 0; i < dishQuantity; i++){
            cout << " - " << dishList[i] << "\n";
        }
        cout << fixed;
        cout.precision(2);
        cout << "Summary: " << cash << " uah\n";
        cout << "Status: ";
        if(isCompleted){cout << "Done";}
        else{cout << "New";}
        cout << "\n";
    }

    void newOrder(int orderNum){
        orderNumber = orderNum;
        cout << "Enter the name of the client: ";
        cin.getline(clientName, 100);

        const int menuSize = 3;
        const char* menuNames[menuSize] = {"Hamburger", "Potato free", "Apple juice"};
        const double menuPrices[menuSize] = {219.00, 59.99, 29.99};

        const int maxdishes = 100;
        char tmpDishName[100];
        char** tmpDishes = new char*[maxdishes];
        int count = 0;

        cout << "\nMenu:\n";
        for(int i = 0; i < menuSize; i++){
            cout << " - " << menuNames[i] << " : " << menuPrices[i] << " uah\n";
        }
        cout << "\nEnter names of the dishes by one. To finish - press Enter on empty row\n";

        while (true){
            cout << "Dish #" << (count + 1) << ": ";
            cin.getline(tmpDishName, 100);
            if(strlen(tmpDishName) == 0) break;

            int menuIndex = -1;
            for(int i = 0; i < menuSize; i++){
                if(strcmp(tmpDishName, menuNames[i]) == 0){
                    menuIndex = i;
                    break;
                }
            }
            if(menuIndex == -1){cout << "Wrong input\t";}
            else{
                tmpDishes[count] = new char[strlen(tmpDishName) + 1];
                strcpy(tmpDishes[count], tmpDishName);
                cash += menuPrices[menuIndex];
                count++;
            }
        }
        dishQuantity = count;
        dishList = new char*[dishQuantity];
        for(int i = 0; i < dishQuantity; i++){
            dishList[i] = tmpDishes[i];
        }
        delete[] tmpDishes;
        isCompleted = false;
    }

    void completeOrder(){
        if(isCompleted){cout << "The order is completed\n";}
        else{isCompleted = true; cout << "The order #" << orderNumber << "is completed\n";}
    };

    void saveToBinaryFile(FILE* file){
        fwrite(&orderNumber, sizeof(orderNumber), 1, file);
        fwrite(clientName, sizeof(clientName), 1, file);
        fwrite(&dishQuantity, sizeof(dishQuantity), 1, file);

        for(int i = 0; i < dishQuantity; i++){
            int len = strlen(dishList[i]) + 1;
            fwrite(&len, sizeof(len), 1, file);
            fwrite(dishList[i], sizeof(char), len, file);
        }

        fwrite(&cash, sizeof(cash), 1, file);
        fwrite(&isCompleted, sizeof(isCompleted), 1, file);
    }

    void loadFromBinaryFile(FILE* file){
        fread(&orderNumber, sizeof(orderNumber), 1, file);
        fread(clientName, sizeof(clientName), 1, file);
        fread(&dishQuantity, sizeof(dishQuantity), 1, file);

        dishList = new char*[dishQuantity];
        for(int i = 0; i < dishQuantity; i++){
            int len = 0;
            fread(&len, sizeof(len), 1, file);
            dishList[i] = new char[len];
            fread(dishList[i], sizeof(char), len, file);
        }

        fread(&cash, sizeof(cash), 1, file);
        fread(&isCompleted, sizeof(isCompleted), 1, file);
    }
};