#include <iostream>
using namespace std;

int main(){

	cout << "Jeff Austin's Gym" << endl;
	cout << "------------------------------" << endl;

		while (true){
		cout << "Menu: Select item number" << endl;
		cout << "1) Add equipment" << endl;
		cout << "2) Remove equipment" << endl;
		cout << "3) Import equipment" << endl;
		cout << "4) Export equipment" << endl;
		cout << "5) Print list of equipment" << endl;
		cout << "6) Exit" << endl;
		cout << "------------------------------" << endl;

		int menuSelection;
		cout << "Selection: "; 
		cin >> menuSelection;

		cout << "" << endl;

		switch(menuSelection) {
			case 1: 
				cout << "Chose to add equipment" << endl;
				break;
			case 2:
				cout << "Chose to remove equipment" << endl;
				break;
			case 3:
				cout << "Chose to import equipment" << endl;
				break;
			case 4:
				cout << "Chose to export equipment" << endl;
				break;
			case 5:
				cout << "Chose to print list of equipment" << endl;
				break;
			case 6:
				cout << "Chose to exit" << endl;
				return 0;
			default:
				cout << "Invalid selection" << endl;
		}
		
		cout << "" << endl;
	}

	return 0;
}