#include "Treadmill.h"
#include "Equipment.h"

Treadmill::Treadmill(){}

/// Construct a treadmill with a brand
Treadmill::Treadmill(std::string inBrand)
{
	brand = inBrand;
}	

/// Create a clone of this piece of equipment at the same state
Treadmill* Treadmill::clone() const
{ 
	Treadmill* clone = new Treadmill();

	if (! this->brand.empty())
	{
		clone->setBrand(this->brand);
	}
		
	return clone;
}


/// Return a string representation of this piece of equipment, in this case 'Treadmill'
std::string Treadmill::toString() const
{
	return brand + " brand Treadmill";
}

/// Serialize this piece of equipment as JSON 
void Treadmill::serialize(std::ostream& os) const 
{
    os << "{\n\t\t\"type\": \"Treadmill\",\n\t\t\"brand\": \"" << brand << "\"\n\t}";
}

/// Use the equipment
void Treadmill::use() const
{
	std::cout << "You ran 2km!" << std::endl;
}