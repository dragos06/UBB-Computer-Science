#include "Medication.h"

Medication::Medication(std::string category, std::string name, std::string effects): category{category}, name{name}, effects{effects}
{
}

std::string Medication::getCategory()
{
	return category;
}

std::string Medication::getName()
{
	return name;
}

std::string Medication::getEffects()
{
	return effects;
}
