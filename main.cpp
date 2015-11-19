#include "classes/Gym.h"

using namespace std;

// Enumeration of menu selection
enum Selection { ADD = 1, REMOVE, IMPORT, EXPORT, PRINT, EXIT };

int main()
{
	// Define my gym
	Gym* gym = new Gym();

	cout << "Jeff Austin's Gym" << endl;
	cout << "------------------------------" << endl;

	int menuSelection;
	while (menuSelection != 6)
	{
		// Display menu for user
		cout << endl << "Menu: Select item number" << endl;
		cout << "1) Add equipment" << endl;
		cout << "2) Remove equipment" << endl;
		cout << "3) Import equipment" << endl;
		cout << "4) Export equipment" << endl;
		cout << "5) Print list of equipment" << endl;
		cout << "6) Exit" << endl;
		cout << "------------------------------" << endl;

		// Prompt user to choose an action
		cout << "Selection: "; 
		cin >> menuSelection;
		cout << endl;

		if (menuSelection == ADD)
		{ 
			while(gym->addEquipment() == false);
		}
		else if (menuSelection == REMOVE)
		{		
			while(gym->removeEquipment() == false);	
		} 
		else if (menuSelection == IMPORT)
		{		
			while(gym->importEquipment() == false);	
		}
		else if (menuSelection == EXPORT)
		{
			while(gym->exportEquipment() == false);	
		}
		else if (menuSelection == PRINT)
		{
			cout << gym;
		}
		else if (menuSelection == EXIT)
		{	
			cout << "Goodbye!" << endl;
		}
		else
		{
			cout << "Invalid selection" << endl;

			if (! std::cin.good())
			{
				cout << "Please enter a number!" << endl;
				cin.clear(); 
				cin.sync();
			}
		}
	}

	return 0;
}