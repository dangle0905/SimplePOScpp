#include <string>
#include <map>
#include <iostream>
#include <thread>
using namespace std;


bool login()
{
	string usernameInput;
	string userPasswordInput;
	string username = "user";
	string password = "password";

	cout << "Welcome to the Point Of Sale System" << endl;
	cout << "Please enter your username: ";
	cin >> usernameInput;
	cout << "Please enter your password: ";
	cin >> userPasswordInput;

	if (usernameInput == username && userPasswordInput == password)
	{
		cout << "Access Granted" << endl << endl;

		//pause before clearning
		chrono::seconds pause(1);
		this_thread::sleep_for(pause);
		system("CLS");

		return true;
	}
	else
	{
		cout << "Access Denied" << endl;
		//pause before clearning
		chrono::seconds pause(1);
		this_thread::sleep_for(pause);

		system("CLS");

		return false;
	}
	return false;
}