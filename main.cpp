#include <iostream>
#include <fstream>
#include <map>
#include <vector>

using namespace std;

/*! \Equipment Prototype.
 *         Virtual base class for all equipment.	
 *
 */
 /*! Equipment Prototype */
class Equipment
{
protected:
	string brand; 
public:
	/// Create a clone of this piece of equipment at the same state
	virtual Equipment* clone() const = 0;
	/// Return a string representation of this piece of equipment
	virtual string toString() const = 0;
	/// Serialize the equipment as JSON
  	virtual void serialize(std::ostream& os) const = 0; 
  	/// Set the brand
	virtual ~Equipment() {};
  	virtual void setBrand(string inBrand)
  	{
  		brand = inBrand;
  	}
  	virtual string getBrand(){
  		return brand;
  	}
};

std::ostream& operator<< (std::ostream& os, const Equipment& s) {
  s.serialize(os);
  return os;
}

/*! EquipmentManager manages prototypes.
 *
 *  Use EquipmentManager to register new prototypes, initialize instances, and access any information regarding the registered prototypes.
 */
class EquipmentManager
{
private:
	map<string, Equipment*> prototypes;
public:
	/// When the equipment manager is destroyed, have all equipment destroy itself also
	virtual ~EquipmentManager()
 	{
   		while(!prototypes.empty())
   		{
     		map<string, Equipment*>::iterator it = prototypes.begin();
     		delete it->second;
     		prototypes.erase(it);
   		}
 	}
	/// Register a prototype so subsequent equipment can be cloned
	void registerPrototype(const string& key, Equipment* prototype)
	{
		prototypes[key] = prototype;
	}
	/// Have the requested equipment type clone itself
	Equipment* getPrototype(const string& key)
	{
		if (prototypes.count(key) == 0){
			return NULL;
		}
		return prototypes[key]->clone();
	}
	/// Print the name of all available prototypes
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
	Treadmill(string inBrand)
	{
		brand = inBrand;
	}	
	/// Create a clone of this piece of equipment at the same state
	Treadmill* clone() const
	{ 
   		return new Treadmill(this->brand);
	}
	/// Return a string representation of this piece of equipment, in this case 'Treadmill'
	string toString() const
	{
		return "Treadmill";
	}
	/// Serialize this piece of equipment as JSON 
	virtual void serialize(std::ostream& os) const {
	    os << "{\n\t\t\"type\": \"Treadmill\",\n\t\t\"brand\": \"" << brand << "\"\n\t}";
  	}
};

class Bowflex : public Equipment
{
public:
	Bowflex(string inBrand)
	{
		brand = inBrand;
	}	
	/// Create a clone of this piece of equipment at the same state
	Bowflex* clone() const
	{ 
   		return new Bowflex(this->brand);
	}
	/// Return a string representation of this piece of equipment, in this case 'Bowflex'
	string toString() const
	{
		return "Bowflex";
	}
	/// Serialize this piece of equipment as JSON
	virtual void serialize(std::ostream& os) const {
	    os << "{\n\t\t\"type\": \"Bowflex\",\n\t\t\"brand\": \"" << brand << "\"\n\t}";
  	}
};

int main(){
	// Register all prototypes
	EquipmentManager* equipmentManager = new EquipmentManager();
	equipmentManager->registerPrototype("Treadmill", new Treadmill("Forest Gump Inc"));
	equipmentManager->registerPrototype("Bowflex", new Bowflex("Macho Man Limited"));

	// Keep track of all equipment
	vector<Equipment*> gymEquipment; 

	cout << "Jeff Austin's Gym" << endl;
	cout << "------------------------------" << endl;

		while (true){
		cout << endl << "Menu: Select item number" << endl;
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
			if (gymEquipment.size() == 0){
				cout << "There is no equipment to remove!" << endl;
				continue;
			}

			// Print out a list of all the current equipment
			cout << "Here is all the current gym equipment:" << endl;
			for(vector<Equipment*>::iterator it = gymEquipment.begin(); it != gymEquipment.end(); ++it) {
			    cout << "  " << distance(gymEquipment.begin(), it) + 1 << ": " << (*it)->toString() << endl;
			}
			// Let user pick which to remove
			cout << "Enter the number of the equipment you'd like to remove: ";

			int equipmentIndex;
			cin >> equipmentIndex;

			if (equipmentIndex <= 0){
				cout << "Selection must be atleast 1!" << endl;
				continue;
			}

			if (equipmentIndex > gymEquipment.size()){
				cout << "Your selection does not correspond to an equipment!" << endl;
				continue;
			}

			gymEquipment.erase(gymEquipment.begin() + equipmentIndex - 1);
			cout << "Equipment removed" << endl;			
		} 
		else if (menuSelection == 3)
		{		
			// Define the file stream
		  	std::fstream fs;
			fs.open ("equipment.JSON", fstream::in);

			string line;

			size_t typeIndexStart;
			size_t typeIndexEnd;

			size_t brandIndexStart;
			size_t brandIndexEnd;

			string typeDelimiter = "\"type\": \"";
			string brandDelimiter = "\"brand\": \"";

			int importCount = 0;

			// Go through all lines in the file
			while (std::getline(fs, line)) {
				// Found the 'type' keyword
				if (typeIndexStart = line.find(typeDelimiter) != string::npos){
					// Get the type
					line.erase(0, typeIndexStart + typeDelimiter.length() + 1);
					typeIndexEnd = line.find("\"");
					string equipmentType = line.substr(0, typeIndexEnd);

					// Get the brand
					std::getline(fs, line);
					brandIndexStart = line.find(brandDelimiter);
					line.erase(0, brandIndexStart + brandDelimiter.length());
					brandIndexEnd = line.find("\"");
					string equipmentBrand = line.substr(0, brandIndexEnd);

					// Get a new prototype and set the brand
					Equipment* newEquipment = equipmentManager->getPrototype(equipmentType);
					newEquipment->setBrand(equipmentBrand);

					// Add it to the gym's equipment
					gymEquipment.push_back(newEquipment);
					cout << "Added \"" << equipmentBrand << "\" brand " << equipmentType << endl; 

					importCount ++;
				}
			}

			fs.close();

			cout << "Imported " << importCount << " items!" << endl;
		}
		else if (menuSelection == 4)
		{
			// Define the file stream
		  	std::fstream fs;
			fs.open ("equipment.JSON", fstream::out);

			fs << "{\n\t\"equipment\": [";
			for(vector<Equipment*>::iterator it = gymEquipment.begin(); it != gymEquipment.end(); ++it) {
			    fs << (*(*it));
			    // Determine if this is the last item
			    bool last_iteration = it == (--gymEquipment.end());

				// If not, add a comma
				if (! last_iteration){
					fs << ", ";
				} 			
			}
			fs << "]\n}";

			fs.close();
		}
		else if (menuSelection == 5)
		{
			if (gymEquipment.size() == 0){
				cout << "There is no equipment to display!" << endl;
				continue;
			}

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
	}

	return 0;
}