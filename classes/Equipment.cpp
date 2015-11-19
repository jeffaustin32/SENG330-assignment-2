#include "Equipment.h"

void Equipment::setBrand(std::string inBrand)
{
	brand = inBrand;
}

std::string Equipment::getBrand()
{
	return brand;
}

std::ostream& operator<< (std::ostream& os, const Equipment& s) {
  s.serialize(os);
  return os;
}