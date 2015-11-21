#include "Bowflex.h"
#include "Equipment.h"

Bowflex::Bowflex(){}

/// Construct a bowflex with a brand
Bowflex::Bowflex(std::string inBrand)
{
	brand = inBrand;
}	

/// Create a clone of this piece of equipment at the same state
Bowflex* Bowflex::clone() const
{ 
	Bowflex* clone = new Bowflex();

	if (! this->brand.empty())
	{
		clone->setBrand(this->brand);
	}
		
	return clone;
}

/// Return a string representation of this piece of equipment, in this case 'Treadmill'
std::string Bowflex::toString() const
{
	return brand + " brand Bowflex";
}

/// Serialize this piece of equipment as JSON 
void Bowflex::serialize(std::ostream& os) const 
{
    os << "{\n\t\t\"type\": \"Bowflex\",\n\t\t\"brand\": \"" << brand << "\"\n\t}";
}

/// Use the equipment
void Bowflex::use() const
{
	std::cout << "You did over 9000 reps!" << std::endl;
}