#ifndef TREADMILL_INCLUDED  
#define TREADMILL_INCLUDED

#include "Equipment.h"

class Treadmill : public Equipment
{
public:
	Treadmill(std::string inBrand);
	/// Create a clone of this piece of equipment at the same state
	Treadmill* clone() const;
	/// Return a string representation of this piece of equipment, in this case 'Treadmill'
	std::string toString() const;
	/// Serialize this piece of equipment as JSON 
	virtual void serialize(std::ostream& os) const;
};

#endif