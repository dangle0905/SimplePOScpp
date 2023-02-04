#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <map>
#include <thread>
#include "Item.h"
#include <random>
#include <iomanip>



void newSaleMenu(map<string, Item>& inventory, map<string, map<string, int>>& transactions);
bool goBackToMainMenu();
int generate_unique_random_number();
void returnItemMenu(map<string, Item>& inventory, map<string, map<string, int>>& transactions);
void returnSingleItem(map<string, Item>& inventory, map<string, map<string, int>>& transactions, string& userTransactionID);
void returnItemFromList(map<string, Item>& inventory, map<string, int>& list_of_items);
void returnAllItems(map<string, Item>& inventory, map<string, map<string, int>>& transactions, string& userTransactionID);
void backRoomMenu(map<string, Item>& inventory, map<string, map<string, int>>& transactions);
void inventoryReport(map<string, Item>& inventory);
void itemsSoldTodayReport(map<string, Item>& inventory, map<string, map<string, int>>& transactions);

using namespace std;

void POSMenu(map<string, Item>& inventory, map<string,map<string,int>>& transactions)
{
    bool validEntry = true;
    int userOptionsInput;
    bool exitMenu = false;
    while (!exitMenu)
    {

        cout << "Please select your options" << endl;
        cout << "1 = New Sale, 2 = Return Item/s, 3 = Backroom Operations, 4 = Exit Application" << endl;
        cin >> userOptionsInput;


        switch (userOptionsInput)
        {
            case 1:
                system("CLS");
                cout << "You selected New Sale" << endl;
                newSaleMenu(inventory, transactions);
                break;
            case 2:
                system("CLS");
                cout << "Return Item/s" << endl;
                returnItemMenu(inventory, transactions);
                break;
            case 3:
                system("CLS");
                backRoomMenu(inventory, transactions);
                break;
            case 4:
                cout << "Exit Application" << endl;
                exitMenu = true;
                break;
            default:
                cout << "Please enter a Valid Entry" << endl;
        }

     

    }
}

void backRoomMenu(map<string, Item>& inventory, map<string, map<string, int>>& transactions)
{
    int userSelection;
    cout << "1 = Inventory, 2 = Today's Sales Report, 3 = Main Menu" << endl;
    cin >> userSelection;

    switch (userSelection)
    {
        case 1:
            inventoryReport(inventory);
        case 2:
            itemsSoldTodayReport(inventory, transactions);
        case 3:
            break;
        default:
            cout << "Invalid Input" << endl;
            break;
    }
}
void inventoryReport(map<string, Item>& inventory)
{

    cout << "Inventory Report" << endl;
    cout << "UPC-------Description---------------------------------------Item-Max-Qty---Order-Threshold-----Replenishment-Order-Quantity-----Item-On-Hand---Unit-Price" << endl << endl;
    {
        for (auto item : inventory)
        {
            cout << left << setw(10) << item.first << left << setw(50)<< item.second.description << left << setw(15) << item.second.itemMaxQuantity << left << setw(20) << item.second.orderThreshold << left << setw(33) << item.second.replenishmentOrderQuantity << left << setw(15) << item.second.itemOnHand << left << setw(1) << "$" << left << setw(9) << item.second.unitPrice << endl;
        }
    }
}
void itemsSoldTodayReport(map<string, Item>& inventory, map<string, map<string, int>>& transactions)
{
    double total = 0;
    cout << "---------------------------------------Today's-Sales-Report--------------------------------------" << endl;

    {
        for (auto transaction : transactions)
        {
            cout << "Transaction ID: " << transaction.first << endl;
            cout << "UPC-------Description---------------------------------------Quantity-Sold---Total-Sold-Of-Product" << endl;
            for (auto item : transactions[transaction.first])
            {
                cout << left << setw(10) << item.first << left << setw(50) << inventory[item.first].description << left << setw(16) << item.second << left << setw(22) << (inventory[item.first].unitPrice * item.second) << endl;
                total = total + ((inventory[item.first].unitPrice) * item.second);
            }
            cout << endl;
        }
        cout << "Total sales today: $" << total << endl << endl;

    }
}



void newSaleMenu(map<string, Item>& inventory, map<string, map<string,int>>& transactions) 
{
    string userInput;
    int userQuantity;
    
    bool newSaleOption = true;
    map<string,int> list_of_items;

    //generate a trascation id
    int transcationID = generate_unique_random_number();
    //so we can make it a key
    string stringTranscationID = to_string(transcationID);

    double total = 0;
    while (newSaleOption)
    {
        cout << "Please enter the UPC: ";
        cin >> userInput;

        if (inventory[userInput].itemOnHand == 0 || inventory.find(userInput) == inventory.end())
        {
            if (inventory[userInput].itemOnHand == 0)
            {
                cout << "We are out of this item: " << inventory[userInput].description << endl;
            }
            else
            {
                cout << "This UPC doesn't exist." << endl;
            }

            if (goBackToMainMenu())
            {
                //goes back to main menu
                newSaleOption = false;
            }
            
        }
        else
        {
      
            cout << "You entered: " << userInput << endl << endl;
            cout << "-------------------Description-------------------" << "-Quanity-On-Hand-----Price--" << endl;
            cout << left << setw(50) << inventory[userInput].description;
            cout << left << setw(20) << inventory[userInput].itemOnHand << "$";
            printf("%.2f", inventory[userInput].unitPrice);
            cout << endl;
            cout << "Enter quantity: ";
            cin >> userQuantity;

            if (inventory[userInput].itemOnHand - userQuantity < 0)
            {
                cout << "We only have " << inventory[userInput].itemOnHand << ". We do not have enough please enter a different amount" << endl;
            }
            else
            {

                cout << "The price is: $";
                printf("%.2f", userQuantity * inventory[userInput].unitPrice);
                cout << endl << endl;

                //new sale                    
                inventory[userInput].UpdateUnitOnHand(-userQuantity);

                list_of_items.insert({ userInput, userQuantity });


  

                bool userSelectionLoop = true;
                while (userSelectionLoop)
                {
                    cout << "1 = Sell another item, 2 Return Item/s from list, 9 = Complete Sale" << endl;
                    cout << "Please select your option: ";

                    int userSelection;
                    cin >> userSelection;

                    switch (userSelection)
                    {
                    case 1:
                        system("CLS");
                        cout << "Sell another item" << endl;
                        userSelectionLoop = false;
                        break;
                    case 2:
                        system("CLS");
                        returnItemFromList(inventory, list_of_items);
                        break;
                    case 9:
                        system("CLS");
                        cout << "Complete Sale" << endl;
                        cout << "-------------------Description-------------------" << "-Price---" << "------Quanity-Bought---" << endl;
                        for (auto eachItem : list_of_items)
                        {

                            cout << left << setw(50) << inventory[eachItem.first].description;
                            cout << left << setw(1) << "$";
                            cout << left << setw(10) << printf("%.1f", inventory[eachItem.first].unitPrice);
                            cout << left << setw(5) << eachItem.second << endl;
                            total = total + (inventory[eachItem.first].unitPrice * eachItem.second);
                        }
                        cout << "---------------------------------------------------------------------------------" << endl;
                        cout << "The receipt number is: " << stringTranscationID << endl;
                        cout << "You total is: ";
                        printf("$%.2f", total);
                        cout << endl;

                        //adds to transaction
                        transactions.insert({ stringTranscationID, list_of_items });
                        list_of_items.clear();


                        //generate the information on the sale total and the receipt number
                        userSelectionLoop = false;
                        newSaleOption = false; //exit the loop and removes from stack and goes back to POS menu
                        system("pause");
                        system("CLS");
                        break;
                    default:
                        cout << "Please enter a valid selection:" << endl;
                        break;
                    }
                }
       
            }

        }

    }
   
}
void returnItemFromList(map<string, Item>& inventory, map<string, int>& list_of_items)
{
    cout << "Return Item from List" << endl;
    string userUPC;
    bool removeItemFromList = true;
    while (removeItemFromList)
    {
        if (list_of_items.size() == 0)
        {
            cout << "Nothing to return" << endl;
            removeItemFromList = false;
        }
        else
        {
            bool returnItemLoop = true;
            while (returnItemLoop)
            {
                cout << "Items currently in basket" << endl;
                cout << "UPC-------------------Description-------------------" << "-Price---" << "------Quanity-Bought---" << endl;
                for (auto eachItem : list_of_items)
                {

                    cout << left << setw(10) << inventory[eachItem.first].UPC;
                    cout << left << setw(40) << inventory[eachItem.first].description;
                    cout << left << setw(10) << inventory[eachItem.first].unitPrice;
                    cout << setw(5) << eachItem.second << endl;

                }
                cout << "---------------------------------------------------------------------------------" << endl;
                cout << "Enter Item UPC to remove: ";
                cin >> userUPC;

                if (list_of_items.find(userUPC) != list_of_items.end())
                {
                    cout << list_of_items[userUPC] << " " << inventory[userUPC].description << ", has been removed from list." << endl;
                    list_of_items.erase(userUPC); //remove the item from the transaction

                    cout << "Do you want to remove more items from the list? (y/n): ";
                    string userInput;
                    cin >> userInput;
                    if (userInput == "Y" || userInput == "y")
                    {
                        returnItemLoop = true;
                        system("CLS");
                    }
                    else if (userInput == "N" || userInput == "n") {
                        returnItemLoop = false;
                        removeItemFromList = false;
                        system("ClS");
                    }
                    else
                    {
                        cout << "Invalid UPC." << endl;
                    }
                }
                else
                {
                    cout << "Invalid UPC." << endl;

                    if (goBackToMainMenu())
                    {
                        returnItemLoop = false;
                    }
                }
            }

        }
    }

}

void returnItemMenu(map<string, Item>& inventory, map<string, map<string,int>>& transactions)
{
    string userTransactionID;
    string userInput;
    int userSelection;
    bool returnLoop = true;
    double total = 0;

    if (transactions.empty() == true)
    {
        cout << "There are currently no transactions." << endl;
    }
    else
    {

        while (returnLoop)
        {
            cout << "-------------------Transactions--------------------" << endl;
            cout << "Transaction-ID-------------------------------------" << endl;
            for (auto transaction : transactions)
            {
                cout << transaction.first << endl;
            }
            cout << "Select which transaction to return: ";
            cin >> userTransactionID;

            if (transactions.find(userTransactionID) != transactions.end())
            {
                cout << "1 - Return Single Item" << " 2 - Return All Items" << endl;
                cin >> userSelection;

                switch (userSelection)
                {
                case 1:
                    system("CLS");
                    returnSingleItem(inventory, transactions, userTransactionID);
                    returnLoop = false;
                    break;
                case 2:
                    system("CLS");
                    returnAllItems(inventory, transactions, userTransactionID);
                    returnLoop = false;
                    break;
                default:
                    cout << "Select a valid Input" << endl;
                    break;
                }
            }
            else
            {
                cout << "Invalid transaction ID" << endl;
                if (goBackToMainMenu())
                {
                    system("CLS");
                    returnLoop = false;
                }

            }
        }

    }
  
}


bool goBackToMainMenu()
{

    bool loop = true;
    while (loop)
    {
        string userInput;
        cout << "Do you want to go back to the main menu? (y/n): ";
        cin >> userInput;

        if (userInput == "Y" || userInput == "y")
        {
            return true;
        }
        else if (userInput == "N" || userInput == "n")
        {
            return false;
        }
        else
        {
            cout << "Please enter a valid input." << endl;
            system("CLS");
        }
    }

}

void returnSingleItem(map<string,Item>& inventory, map<string, map<string,int>>& transactions, string& userTransactionID)
{
    double total = 0;
    string userUPC;
    string userQuantity;
    bool removeMoreItems = true;
    while (removeMoreItems)
    {
        cout << "Return Single Item" << endl;
        cout << "Transaction ID: " << userTransactionID << endl;
        cout << "UPC----------------Description-------------------" << "-Price---" << "------Quanity-Bought---" << endl;
        for (auto item : transactions[userTransactionID])
        {
            cout << left << setw(10) << inventory[item.first].UPC;
            cout << left << setw(40) << inventory[item.first].description;
            cout << setw(10) << printf("$%.1f", inventory[item.first].unitPrice);
            cout << setw(5) << item.second << endl;
            total = total + (inventory[item.first].unitPrice * item.second);
        }

    
        cout << "Enter UPC of item to return: ";
        cin >> userUPC;

        if (transactions[userTransactionID].find(userUPC) != transactions[userTransactionID].end())
        {
            cout << transactions[userTransactionID][userUPC] << " " << inventory[userUPC].description << ", has been removed from transaction and added back into inventory." << endl;
            inventory[userUPC].UpdateUnitOnHand(transactions[userTransactionID][userUPC]); //add the item back into the inventory
            transactions[userTransactionID].erase(userUPC); //remove the item from the transaction
            if (transactions[userTransactionID].size()==0)
            {
                transactions.erase(userTransactionID);
            }

            cout << "Do you want to remove more items?: ";
            string userInput;
            cin >> userInput;
            if (userInput == "Y" || userInput == "y")
            {
                removeMoreItems = true;
                system("CLS");
            }
            else if (userInput == "N" || userInput == "n") {
                removeMoreItems = false;
                system("ClS");
            }
            
        }
        else
        {
            cout << "Invalid UPC." << endl;
        }
    }
}

void returnAllItems(map<string, Item>& inventory, map<string, map<string, int>>& transactions, string& userTransactionID)
{
    double total = 0;
    string userInput;
    string userQuantity;
    bool removeAllItemsLoop = true;
    while (removeAllItemsLoop)
    {
        cout << "Return All Items" << endl;
        cout << "Transaction ID: " << userTransactionID << endl;
        cout << "UPC----------------Description-------------------" << "-Price---" << "------Quanity-Bought---" << endl;
        for (auto item : transactions[userTransactionID])
        {
            cout << left << setw(10) << inventory[item.first].UPC;
            cout << left << setw(40) << inventory[item.first].description;
            cout << setw(10) << printf("$%.1f", inventory[item.first].unitPrice);
            cout << setw(5) << item.second << endl;
        }


        cout << "Are you sure you want to return all items? (y/n): ";
        cin >> userInput;

        if (userInput == "Y" || userInput == "y")
        {

            for (auto item : transactions[userTransactionID])
            {
                inventory[item.first].UpdateUnitOnHand(item.second);
                
            }
            cout << "All Items returned" << endl;
            transactions.erase(userTransactionID);
            removeAllItemsLoop = false;

        }
        else if (userInput == "N" || userInput == "n")
        {
            removeAllItemsLoop = false;
        }
        else
        {
            cout << "Invalid input." << endl;
        }
    }
}
int generate_unique_random_number() {
    random_device rd;
    mt19937 engine(rd());
    uniform_int_distribution<int> dist(10000000, 90000000);

    return dist(engine);
}