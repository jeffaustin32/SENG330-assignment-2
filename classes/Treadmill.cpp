#include "Treadmill.h"
#include "Equipment.h"

Treadmill::Treadmill(std::string inBrand)
{
	brand = inBrand;
}	

/// Create a clone of this piece of equipment at the same state
Treadmill* Treadmill::clone() const
{ 
		return new Treadmill(this->brand);
}

/// Return a string representation of this piece of equipment, in this case 'Treadmill'
std::string Treadmill::toString() const
{
	return "Treadmill";
}

/// Serialize this piece of equipment as JSON 
void Treadmill::serialize(std::ostream& os) const 
{
    os << "{\n\t\t\"type\": \"Treadmill\",\n\t\t\"brand\": \"" << brand << "\"\n\t}";
}