#include "Gym.h"

Gym::Gym()
{
	equipmentManager = new EquipmentManager();
	equipmentManager->registerPrototype("Treadmill", new Treadmill());
	equipmentManager->registerPrototype("Bowflex", new Bowflex());

	hstdin  = GetStdHandle( STD_INPUT_HANDLE  );
	hstdout = GetStdHandle( STD_OUTPUT_HANDLE );
}

void Gym::setFontTheme(std::string theme) const
{
	// Color codes: http://ss64.com/nt/color.html
	// Success: green on black
	if (theme == "success")
	{
		SetConsoleTextAttribute(hstdout, 0x02);
	}
	// Error: red on black
	else if (theme == "error")
	{
		SetConsoleTextAttribute(hstdout, 0x0C);
	}
	// Emphasis: bright white on black
	else if (theme == "emphasis")
	{
		SetConsoleTextAttribute(hstdout, 0x0F);
	}
	// Default: white on black
	else
	{
		SetConsoleTextAttribute(hstdout, 0x07);
	}
}

bool Gym::addEquipment()
{
	// Used for creating new equipment
	std::string equipmentSelection;

	// Display available equipment types
	std::cout << "Available equipment types are: " << std::endl;	
	setFontTheme("emphasis");
	std::cout << *equipmentManager << std::endl;
	setFontTheme("default");
	std::cout << "Or type cancel to return to main menu" << std::endl;

	// Prompt user to enter a type
	std::cout << "Enter the name of the equipment to add: ";

	// Clear the input buffer
	std::cin.clear(); 
	std::cin.sync();

	// Get the users choice of equipment
	std::getline(std::cin, equipmentSelection);

	// Cancel creating equipment
	if (equipmentSelection == "cancel") 
	{
		return true;
	}

	// Try to create the new prototype
	Equipment* newEquipment = equipmentManager->getPrototype(equipmentSelection);

	// User's input was invalid
	if (newEquipment == NULL)
	{
		setFontTheme("error");
		std::cout << "\nInvalid equipment type\n" << std::endl;
		setFontTheme("default");
		return false;
	} 

	// Prompt user to enter a brand
	std::cout << "Enter the brand of " << equipmentSelection << ": ";

	// Clear the input buffer
	std::cin.clear(); 
	std::cin.sync();

	// Get the brand
	std::string equipmentBrand;
	std::getline(std::cin, equipmentBrand);

	if (equipmentBrand.empty()) 
	{
		equipmentBrand = "No Name";
	}

	// Set the brand
	newEquipment->setBrand(equipmentBrand);

	// Add the new equipment
	equipment.push_back(newEquipment);
	setFontTheme("success");
	std::cout << "\nAdded new " << equipmentBrand << " brand " << equipmentSelection << "!" << std::endl; 
	setFontTheme("default");
	return true;
}

bool Gym::removeEquipment()
{
	// Gym has no equipment
	if (equipment.size() == 0){
		setFontTheme("error");
		std::cout << "There is no equipment to remove!" << std::endl;
		setFontTheme("default");
		return true;
	}

	// Print out a list of all the current equipment
	std::cout << "Here is all the current gym equipment:" << std::endl;
	for(std::vector<Equipment*>::iterator it = equipment.begin(); it != equipment.end(); ++it) {
		setFontTheme("emphasis");
	    std::cout << "  " << distance(equipment.begin(), it) + 1 << ": " << (*it)->toString() << std::endl;
		setFontTheme("default");
	}
	// Let user pick which to remove
	std::cout << "Enter the number beside the equipment you'd like to remove: ";

	int equipmentIndex;
	// Clear the input buffer
	std::cin.clear(); 
	std::cin.sync();
	std::cin >> equipmentIndex;

	if (! std::cin.good())
	{
		setFontTheme("error");
		std::cout << "\nMust choose a number!\n" << std::endl;
		setFontTheme("default");
		return false;
	}

	if (equipmentIndex <= 0){
		std::cout << "\nSelection must be atleast 1!\n" << std::endl;
		return false;
	}

	if (equipmentIndex > equipment.size()){
		setFontTheme("error");
		std::cout << "\nYour selection does not correspond to an equipment!\n" << std::endl;
		setFontTheme("default");
		return false;
	}

	equipment.erase(equipment.begin() + equipmentIndex - 1);
	setFontTheme("success");
	std::cout << "\nEquipment removed!" << std::endl;	
	setFontTheme("default");
	return true;
}

bool Gym::importEquipment()
{
	// Define the file stream
  	std::fstream fs;
	fs.open ("equipment.JSON", std::fstream::in);

	std::string line;

	size_t typeIndexStart, typeIndexEnd;

	size_t brandIndexStart, brandIndexEnd;

	std::string typeDelimiter = "\"type\": \"";
	std::string brandDelimiter = "\"brand\": \"";

	int importCount = 0;

	// Go through all lines in the file
	while (std::getline(fs, line)) 
	{
		// Found the 'type' keyword
		if (typeIndexStart = line.find(typeDelimiter) != std::string::npos)
		{
			// Get the type
			line.erase(0, typeIndexStart + typeDelimiter.length() + 1);
			typeIndexEnd = line.find("\"");
			std::string equipmentType = line.substr(0, typeIndexEnd);

			// Get the brand
			std::getline(fs, line);
			brandIndexStart = line.find(brandDelimiter);
			line.erase(0, brandIndexStart + brandDelimiter.length());
			brandIndexEnd = line.find("\"");
			std::string equipmentBrand = line.substr(0, brandIndexEnd);

			// Get a new prototype and set the brand
			Equipment* newEquipment = equipmentManager->getPrototype(equipmentType);
			newEquipment->setBrand(equipmentBrand);

			// Add it to the gym's equipment
			equipment.push_back(newEquipment);
			setFontTheme("success");
			std::cout << "Added \"" << equipmentBrand << "\" brand " << equipmentType << std::endl; 
			setFontTheme("default");

			importCount ++;
		}
	}

	fs.close();

	if (importCount == 0)
	{
		setFontTheme("error");
		std::cout << "No items to import!" << std::endl;
		setFontTheme("default");
	} 
	else
	{
		setFontTheme("success");
		std::cout << "Imported " << importCount << " items!" << std::endl;
		setFontTheme("default");
	}

	return true;
}

bool Gym::exportEquipment()
{
	// Define the file stream
  	std::fstream fs;
	fs.open ("equipment.JSON", std::fstream::out);

	int exportCount = 0;

	fs << "{\n\t\"equipment\": [";
	for(std::vector<Equipment*>::iterator it = equipment.begin(); it != equipment.end(); ++it) 
	{
	    fs << (*(*it));
	    // Determine if this is the last item
	    bool last_iteration = it == (--equipment.end());

		// If not, add a comma
		if (! last_iteration)
		{
			fs << ", ";
		} 		

		exportCount ++;	
	}
	fs << "]\n}";

	fs.close();

	if (exportCount == 0)
	{
		setFontTheme("error");
		std::cout << "No items to Export!" << std::endl;
		setFontTheme("default");
	} 
	else
	{
		setFontTheme("success");
		std::cout << "Exported " << exportCount << " items!" << std::endl;
		setFontTheme("default");
	}

	return true;
}

std::ostream& Gym::printEquipment(std::ostream& os) const
{
	if (equipment.size() == 0){
		setFontTheme("error");
		os << "There is no equipment to display!" << std::endl;
		setFontTheme("default");
	}
	else 
	{
		os << "Here is all the current gym equipment:" << std::endl;

		// Define iterator
		std::vector<Equipment*>::const_iterator it;

		setFontTheme("emphasis");
		// Print out a list of all the current equipment
		for(it = equipment.begin(); it != equipment.end(); ++it) {
			os << "  " << distance(equipment.begin(), it) + 1 << ": " << (*it)->toString() << std::endl;
		}
		setFontTheme("default");
	}

	return os;
}

std::ostream& operator<< (std::ostream& os, const Gym* gym) {
  	return gym->printEquipment(os);
}