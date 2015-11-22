#include "EquipmentManager.h"

/// When the equipment manager is destroyed, have all equipment destroy itself also
EquipmentManager::~EquipmentManager()
{
	while(!prototypes.empty())
	{
 		std::map<std::string, Equipment*>::iterator it = prototypes.begin();
 		delete it->second;
 		prototypes.erase(it);
	}
}

/// Register a prototype so subsequent equipment can be cloned
void EquipmentManager::registerPrototype(const std::string& key, Equipment* prototype)
{
   // prototypes.insert ( std::pair<std::string, Equipment*>(key, prototype) );
	prototypes[key] = prototype;
}

/// Have the requested equipment type clone itself
Equipment* EquipmentManager::getPrototype(const std::string& key)
{
	if (prototypes.count(key) == 0){
		return NULL;
	}

	return prototypes[key]->clone();
}	

/// Number of prototypes registered
int EquipmentManager::prototypeCount()
{
    return prototypes.size();
}

/// Print the name of all available prototypes
std::ostream& EquipmentManager::printAvailablePrototypes(std::ostream& os) const
{
	// Declare an iterator
	std::map<std::string, Equipment*>::const_iterator it; 
	// Assign it to the start of the map
    it = prototypes.begin(); 

    // Loop through entire prototypes map
    while (it != prototypes.end()) 
    {
    	// Add this prototype's name to the stream
        os << "  "  << it->first;
        // Increment the iterator
        it++; 

        // For all but the last prototype, add a comma afterwards
        if (it != prototypes.end())
        {
        	os << ",";
        }
    }

    return os;
}

std::ostream& operator<< (std::ostream& os, const EquipmentManager& s) {
  	return s.printAvailablePrototypes(os);
}