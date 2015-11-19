#ifndef EQUIPMENT_MANAGER_INCLUDED  
#define EQUIPMENT_MANAGER_INCLUDED

#include "Equipment.h"
#include <map>

/*! EquipmentManager manages prototypes.
 *
 *  Use EquipmentManager to register new prototypes, initialize instances, and access any information regarding the registered prototypes.
 */
class EquipmentManager
{
private:	
	std::map<std::string, Equipment*> prototypes;
public:
	/// When the equipment manager is destroyed, have all equipment destroy itself also
	virtual ~EquipmentManager();
	/// Register a prototype so subsequent equipment can be cloned
	void registerPrototype(const std::string& key, Equipment* prototype);
	/// Have the requested equipment type clone itself
	Equipment* getPrototype(const std::string& key);
	/// Print the name of all available prototypes
	std::ostream& printAvailablePrototypes(std::ostream& os) const;
};

std::ostream& operator<< (std::ostream& os, const EquipmentManager& s);

#endif