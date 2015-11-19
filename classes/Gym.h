#ifndef GYM_INCLUDED  
#define GYM_INCLUDED

#include <vector>
#include <fstream>
#include <windows.h>

#include "Equipment.h"
#include "Treadmill.h"
#include "Bowflex.h"
#include "EquipmentManager.h"

class Gym
{
private:
	std::vector<Equipment*> equipment;
	EquipmentManager* equipmentManager;
	HANDLE hstdin;
	HANDLE hstdout;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	void setFontTheme(std::string theme) const;
public:
	Gym();
	bool addEquipment();
	bool removeEquipment();
	bool importEquipment();
	bool exportEquipment();
	std::ostream& printEquipment(std::ostream& os) const;
};

std::ostream& operator<< (std::ostream& os, const Gym* gym);

#endif