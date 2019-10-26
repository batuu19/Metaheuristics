#pragma once

#include "Creature.h"
#include <iterator>
class TabuList
{
public:
	void push(const Creature& creature);
	bool contains(const Creature&  creature) const;
	typedef std::set<unsigned long long> tabuSet;
	typedef tabuSet::iterator iterator;
	typedef tabuSet::const_iterator const_iterator;
	iterator begin();
	iterator end();
	const const_iterator begin() const;
	const const_iterator end() const;

private:
	std::set<unsigned long long> hashes;
	size_t maxSize;
};