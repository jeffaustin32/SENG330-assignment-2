#include <iostream>
#include <map>
#include <vector>

using namespace std;

/*! \Equipment Prototype.
 *         Base class for all equipment.
 *
 */
 /*! Equipment Prototype */
class Equipment
{
public:
	virtual Equipment* clone() const = 0; //!< All derived classes must implement a clone operation.
	virtual void store() const = 0; //!< All derived classes must implement the ability to serialize themselves.
	virtual ~Equipment() {}; //!< Virtual destructor.
	virtual string toString() const = 0;
};

/*! \ Prototype Manager
 *         Manage prototype creation.
 *
 *  Can register new prototypes and initialize new instances of new ones.
 */
class EquipmentManager
{
private:
	map<string, Equipment*> prototypes;
public:
	EquipmentManager(){
		prototypes;
	}
	virtual ~EquipmentManager()
 	{
   		while(!prototypes.empty())
   		{
     		map<string, Equipment*>::iterator it = prototypes.begin();
     		delete it->second;
     		prototypes.erase(it);
   		}
 	}
	void registerPrototype(const string& key, Equipment* prototype)
	{
		prototypes[key] = prototype;
	}
	Equipment* getPrototype(const string& key)
	{
		if (prototypes.count(key) == 0){
			cout << "Invalid option";
			return NULL;
		}
		return prototypes[key]->clone();
	}
	void printAvailablePrototypes()
	{
		for (map<string, Equipment*>::iterator it = prototypes.begin(); it != prototypes.end(); ++it)
		{
		 	cout << "  " << distance(prototypes.begin(), it) + 1 << ") " << it->first << endl;
		}
	}
};

class Treadmill : public Equipment
{
public:
	Treadmill(){}	
	Treadmill* clone() const
	{ 
   		return new Treadmill();
	}
	void store() const
	{ 
		// Temp, will later return serialized version of Treadmill
		cout << "Treadmill" << endl; 
	}
	string toString() const
	{
		return "Treadmill";
	}
};

class Bowflex : public Equipment
{
public:
	Bowflex(){}	
	Bowflex* clone() const
	{ 
   		return new Bowflex();
	}
	void store() const
	{ 
		// Temp, will later return serialized version of Bowflex
		cout << "Bowflex" << endl; 
	}
	string toString() const
	{
		return "Bowflex";
	}
};

int main(){
	// Register all prototypes
	EquipmentManager* equipmentManager = new EquipmentManager();
	equipmentManager->registerPrototype("Treadmill", new Treadmill());
	equipmentManager->registerPrototype("Bowflex", new Bowflex());

	// Keep track of all equipment
	vector<Equipment*> gymEquipment; 

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
				
		// Clear the input buffer
		cin.clear(); 
		cin.sync();

		cout << "" << endl;

		if (menuSelection == 1)
		{ 
			// Used for creating new equipment
			string equipmentSelection;

			// Display available equipment types
			cout << "Available equipment types are: " << endl;
			equipmentManager->printAvailablePrototypes();

			// Prompt user to enter a type
			cout << "Enter the equipment type: ";
			getline(cin, equipmentSelection);

			// Try to create the new prototype
			Equipment* newEquipment = equipmentManager->getPrototype(equipmentSelection);

			// User's input was invalid
			if (newEquipment == NULL)
			{
				cout << "Invalid equipment type" << endl;
			} 
			else 
			{
				// Add the new equipment
				gymEquipment.push_back(newEquipment);
				cout << "Added new " << equipmentSelection << "!" << endl; 
			}
		}
		else if (menuSelection == 2)
		{
			cout << "Chose to remove equipment" << endl;
			// Print list of all equipment
			// Let user pick which to remove
			
		} 
		else if (menuSelection == 3)
		{		
			cout << "Chose to import equipment" << endl;
		}
		else if (menuSelection == 4)
		{
			cout << "Chose to export equipment" << endl;
		}
		else if (menuSelection == 5)
		{
			// Print out a list of all the current equipment
			cout << "Here is all the current gym equipment:" << endl;
			for(vector<Equipment*>::iterator it = gymEquipment.begin(); it != gymEquipment.end(); ++it) {
			    cout << "  " << distance(gymEquipment.begin(), it) + 1 << ": " << (*it)->toString() << endl;
			}
		}			
		else if (menuSelection == 6)
		{
			cout << "Chose to exit" << endl;
			return 0;
		}
		else
		{
			cout << "Invalid selection" << endl;
		}

		cout << endl;
	}

	return 0;
}