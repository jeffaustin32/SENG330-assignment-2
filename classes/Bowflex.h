#ifndef BOWFLEX_INCLUDED  
#define BOWFLEX_INCLUDED

#include "Equipment.h"

class Bowflex : public Equipment
{
public:
	Bowflex(std::string inBrand);
	/// Create a clone of this piece of equipment at the same state
	Bowflex* clone() const;
	/// Return a string representation of this piece of equipment, in this case 'Treadmill'
	std::string toString() const;
	/// Serialize this piece of equipment as JSON 
	virtual void serialize(std::ostream& os) const;
};

#endif