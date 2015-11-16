#include <iostream>
#include <map>
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
		cout << "Treadmill\n"; 
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
		cout << "Bowflex\n"; 
	}
};

int main(){
	EquipmentManager* equipmentManager = new EquipmentManager();
	equipmentManager->registerPrototype("Treadmill", new Treadmill());
	equipmentManager->registerPrototype("Bowflex", new Bowflex());

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