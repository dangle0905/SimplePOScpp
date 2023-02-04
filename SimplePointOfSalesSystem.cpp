#include <iostream>
#include <stdlib.h>
#include <vector>
#include <ios>
#include <iomanip>
#include <thread>
#include <chrono>
#include <map>
#include "item.h"
#include "readRetailStoreItemDataFile.h"
#include "login.h"
#include "POSMenu.h"

using namespace std;

int main(void)
{

	map<string, Item> inventory;
	//pass by ref
	readRetailStoreItemDataFile(inventory);

	map <string, map<string,int>> transactions;

	string username = "user";
	string password = "password";

	string usernameInput;
	string userPasswordInput;

	int numIncorrect = 0;
	bool exit = false;
	while (exit == false)
	{

		if (login())
		{
			//join it now because we got the log in already
			
			POSMenu(inventory, transactions);
			exit = true;
		}
		else
		{

			numIncorrect++;
			if (numIncorrect == 3)
			{
				cout << "Program Exiting, too many failed attemps " << endl;
				break;
			}
		}

	}

	return 0;
}





// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
