#pragma once

#include "Creature.h"
#include <iterator>
#include <map>

constexpr size_t DEFAULT_TABULIST_MAXSIZE = 99999999999;

class TabuList
{
public:
	void push(const Creature& creature);
	bool contains(const Creature&  creature) const;
	typedef std::map<size_t, unsigned long long> tabuMap;
	typedef tabuMap::iterator iterator;
	typedef tabuMap::const_iterator const_iterator;
	iterator begin();
	iterator end();
	const const_iterator begin() const;
	const const_iterator end() const;

private:
	tabuMap indexHashMap;
	size_t maxSize = DEFAULT_TABULIST_MAXSIZE;
	size_t indexBegin = 0, indexEnd = 0,size = 0;
};