#ifndef GYM_INCLUDED  
#define GYM_INCLUDED

#include <vector>
#include <fstream>
#include <windows.h>

#include "Equipment.h"
#include "Treadmill.h"
#include "Bowflex.h"
#include "EquipmentManager.h"

/*! \Gym.
 *         A class to handle all Gym related functionality:
 *			- Adding, Removing, Importing, Exporting, Printing gym equipment.	
 *
 */
 /*! Gym */
class Gym
{
private:
	std::vector<Equipment*> equipment;
	EquipmentManager* equipmentManager;
	HANDLE hstdin;
	HANDLE hstdout;
	void setFontTheme(std::string theme) const;
public:
	/// Create a new instance of a Gym
	Gym();
	/// Add equipment to this gym
	bool addEquipment();
	/// Remove equipment from this gym
	bool removeEquipment();
	/// Import gym equipment from an Equipment.JSON file
	bool importEquipment();
	/// Export gym equipment to Equipment.JSON file
	bool exportEquipment();
	/// Stream out operator overload to print all equipment in the gym
	std::ostream& printEquipment(std::ostream& os) const;
};

std::ostream& operator<< (std::ostream& os, const Gym* gym);

#endif