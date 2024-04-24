#include "Domain.h"

Protein::Protein()
{
}

Protein::Protein(string organism, string name, string sequence)
{
    this->orgranism = organism;
    this->name = name;
    this->sequence = sequence;
}

string Protein::getOrganism()
{
    return this->orgranism;
}

string Protein::getName()
{
    return this->name;
}

string Protein::getSequence()
{
    return this->sequence;
}
