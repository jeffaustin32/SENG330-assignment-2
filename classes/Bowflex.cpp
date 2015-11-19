#include "Bowflex.h"
#include "Equipment.h"

Bowflex::Bowflex(std::string inBrand)
{
	brand = inBrand;
}	

/// Create a clone of this piece of equipment at the same state
Bowflex* Bowflex::clone() const
{ 
		return new Bowflex(this->brand);
}

/// Return a string representation of this piece of equipment, in this case 'Treadmill'
std::string Bowflex::toString() const
{
	return "Bowflex";
}

/// Serialize this piece of equipment as JSON 
void Bowflex::serialize(std::ostream& os) const 
{
    os << "{\n\t\t\"type\": \"Bowflex\",\n\t\t\"brand\": \"" << brand << "\"\n\t}";
}