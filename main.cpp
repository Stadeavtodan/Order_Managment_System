#include <iostream>
#include "Order.h"
//#define CREATE_LOAD 1 // 1 - create, 0 - load

int main()
{
    srand(time(0));
    FILE* file = nullptr;

    int NClients = 0;
    Order* arr = nullptr;

    //============================== CREATE OR LOAD ==================================
//#if CREATE_LOAD == 1
//    cout << "HI";
//#else
//    fopen_s(&file, "order.bin", "rb")
//    if(file != nullptr){
//        fscanf_s(file,)
//    }
//#endif


    //================================== MENU ========================================

    int menu = 0;
    Order tmp_order;
    char text[100];
    int tmp_orderNumber;
    double tmp_cash = 0;
    int id = -1;
    bool isCompleted;

    do{
        cout << "-------------------------------------\n";
        cout << "\t MENU:\n\n";
        cout << "-------------------------------------\n";
        cout << "0 - Exit and save\n";
        cout << "1 - Show all orders\n";
        cout << "2 - New order\n";

        cout << "Enter: ";
        cin >> menu;
        switch (menu) {
            default: cout << "Error!\n"; break;
            case 0: cout << "Bye\n"; break;
            case 1:
                if(NClients == 0){cout << "There is no any order\n";}
                else{
                    for(int i = 0; i < NClients; i++){
                        arr[i].showOrders();
                        cout << "===================================";
                    }
                }
                break;
            case 2:
                cin.ignore();
                Order* tmp = new Order[NClients + 1];

                for(int i = 0; i < NClients; i++){tmp[i] = arr[i];}

                delete[] arr;
                arr = tmp;

                arr[NClients].newOrder(NClients + 1);
                NClients++;
                cout << "Added!\n";
                break;
        }
    } while (menu != 0);

    //================================== SAVE ========================================

//    fopen_s(&file, "order.bin", "wb");
//    if(file != nullptr){
//
//    }
}