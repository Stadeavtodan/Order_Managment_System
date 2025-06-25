#include <iostream>
#include "Order.h"
#include "ArrayTemplate.h"
#define CREATE_LOAD 0 // 1 - create, 0 - load

int main()
{
    srand(time(0));
    FILE* file = nullptr;

    int NClients = 0;
    Order* arr = nullptr;

    //============================== CREATE OR LOAD ==================================
#if CREATE_LOAD == 1
    cout << "HI";
#else
    fopen_s(&file, "order.bin", "rb");
    if(file != nullptr){
        fscanf_s(file, "%d", &NClients);
        arr = new Order[NClients];
        for(int i = 0; i < NClients; i++){
            arr[i].loadFromBinaryFile(file);
        }
        fclose(file);
        cout << "Loaded!\n";
    }
#endif


    //================================== MENU ========================================

    int menu = 0;
    int tmpOrderNumber;
    int id = -1;
    do{
        cout << "\n-------------------------------------\n";
        cout << "\t MENU:\n\n";
        cout << "-------------------------------------\n";
        cout << "0 - Exit and save\n";
        cout << "1 - Show all orders\n";
        cout << "2 - New order\n";
        cout << "3 - Complete order\n";
        cout << "4 - Find by new\n";
        cout << "5 - Find by done\n";
        cout << "6 - Sort by cash\n";
        cout << "7 - Sort by name\n";
        cout << "8 - Sort by number of the order\n";
        cout << "9 - Delete order\n";
        cout << "10 - Edit order\n";

        cout << "Enter: ";
        cin >> menu;
        switch (menu) {
            default: cout << "Error!\n"; break;
            case 0: cout << "Bye\n"; break;
            case 1:
                if(NClients == 0){cout << "There is no any order\n";}
                else{
                    for(int i = 0; i < NClients; i++){
                        arr[i].showOrder();
                        cout << "==================================\n";
                    }
                }
                break;
            case 2: {
                cin.ignore();
                Order *tmp = new Order[NClients + 1];

                for (int i = 0; i < NClients; i++) { tmp[i] = arr[i]; }

                delete[] arr;
                arr = tmp;

                arr[NClients].newOrder(NClients + 1);
                NClients++;
                cout << "Added!\n";
                break;
            }
            case 3:
                if(NClients == 0){cout << "There is no any order\n"; break;}
                cout << "Enter the number of the order: ";
                cin >> tmpOrderNumber;
                cin.ignore();
                if(tmpOrderNumber < 1 || tmpOrderNumber > NClients){cout << "Wrong number!";}
                else{arr[tmpOrderNumber - 1].completeOrder();}
                break;
            case 4:
                for(int i = 0; i < NClients; i++){
                    if(arr[i].isCompleted == false){
                        cout << "==================================\n";
                        arr[i].showOrder();
                        cout << "==================================\n";
                    }
                }
                break;
            case 5:
                for(int i = 0; i < NClients; i++){
                    if(arr[i].isCompleted == true){
                        cout << "==================================\n";
                        arr[i].showOrder();
                        cout << "==================================\n";
                    }
                }
                break;
            case 6:
                mySort<Order>(arr, NClients, [](Order a, Order b){return b.cash > a.cash;});
                for(int i = 0; i < NClients; i++){
                    arr[i].showOrder();
                }
                break;
            case 7:
                mySort<Order>(arr, NClients, [](Order a, Order b){return strcmp(a.clientName, b.clientName) > 0;});
                for(int i = 0; i < NClients; i++){
                    arr[i].showOrder();
                }
                break;
            case 8:
                mySort<Order>(arr, NClients, [](Order a, Order b){return b.orderNumber < a.orderNumber;});
                for(int i = 0; i < NClients; i++){
                    arr[i].showOrder();
                }
                break;
            case 9:
                cout << "Input the number of an order: ";
                cin >> tmpOrderNumber;

                id = -1;
                for(int i = 0; i < NClients; i++){
                    if(arr[i].orderNumber == tmpOrderNumber){id = i; break;}
                }
                if(id == -1) cout << "Not found!\n";
                else{
                    delItem2(arr, NClients, id);
                    cout << "The order was deleted";
                }
            case 10:
                if(NClients == 0){cout << "There is no any order\n"; break;}
                cout << "Enter order number to edit: ";
                cin >> tmpOrderNumber;
                cin.ignore();
                if(tmpOrderNumber < 1 || tmpOrderNumber > NClients){cout << "Wrong number!\n";}
                else{arr[tmpOrderNumber - 1].editOrder();}
                break;
        }
    } while (menu != 0);

    //================================== SAVE ========================================

    fopen_s(&file, "order.bin", "wb");
    if(file != nullptr){
        fprintf(file, "%d", NClients);
        for(int i = 0; i < NClients; i++){
            arr[i].saveToBinaryFile(file);
        }
        fclose(file);
        cout << "Saved!\n";
    }
}