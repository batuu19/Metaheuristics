#pragma once

#include "Creature.h"

class TabuList
{
public:
	void push(const Creature& creature);
	bool contains(const Creature&  creature) const;
private:
	std::set<unsigned long long> hashes;
	size_t maxSize;
};