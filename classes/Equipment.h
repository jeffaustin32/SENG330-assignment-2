#ifndef EQUIPMENT_INCLUDED  
#define EQUIPMENT_INCLUDED
#include <string>
#include <iostream>

/*! \Equipment Prototype.
 *         Virtual base class for all equipment.	
 *
 */
 /*! Equipment Prototype */
class Equipment{	
protected:
	std::string brand; 
public:
	/// Create a clone of this piece of equipment at the same state
	virtual Equipment* clone() const = 0;
	/// Return a string representation of this piece of equipment
	virtual std::string toString() const = 0;
	/// Serialize the equipment as JSON
  	virtual void serialize(std::ostream& os) const = 0; 
  	/// Set the brand
	virtual ~Equipment() {};
	virtual void setBrand(std::string inBrand);
  	virtual std::string getBrand();
};

std::ostream& operator<< (std::ostream& os, const Equipment& s);

#endif