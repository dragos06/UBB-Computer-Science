#pragma once
#include <string>
using namespace std;

class Protein {
private:
	string orgranism;
	string name;
	string sequence;
public:
	Protein();
	Protein(string organism, string name, string sequence);
	string getOrganism();
	string getName();
	string getSequence();
};