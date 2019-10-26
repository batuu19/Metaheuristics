#include "TabuList.h"

void TabuList::push(const Creature& creature)
{
	hashes.insert(creature.getHash());//ignoring max size for now
	
}

bool TabuList::contains(const Creature& creature) const
{
	return hashes.find(creature.getHash()) != hashes.end();
}

TabuList::iterator TabuList::begin()
{
    return hashes.begin();
}

TabuList::iterator TabuList::end()
{
    return hashes.end();
}

const TabuList::const_iterator TabuList::begin() const
{
    return hashes.begin();
}

const TabuList::const_iterator TabuList::end() const
{
    return hashes.end();
}
