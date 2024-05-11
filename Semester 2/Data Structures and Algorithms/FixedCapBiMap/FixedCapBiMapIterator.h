#pragma once
#include "FixedCapBiMap.h"
class FixedCapBiMapIterator
{
	//DO NOT CHANGE THIS PART
	friend class FixedCapBiMap;
private:
	FixedCapBiMap& map;
	//TODO - Representation
	int currentPosition;

	FixedCapBiMapIterator(FixedCapBiMap& m);
public:
	void first();
	void next();
	TElem getCurrent();
	bool valid() const;
	TElem remove();
};

