#include "TabuList.h"

TabuEntry::TabuEntry(const Creature& creature)
	:
	cities(creature.getCities())
{}

TabuEntry::TabuEntry(const std::vector<size_t>& cities)
	:
	cities(cities)
{}

void TabuList::push(const Creature& creature)
{
	entries.push_back(creature);//ignoring max size for now
}

bool TabuList::contains(const Creature& creature)
{
	bool contains = false;
	size_t i = 0;
	while (!contains && i < entries.size())
	{
		if (entries[i].cities == creature.getCities())
			contains = true;
	}
	return contains;
}
