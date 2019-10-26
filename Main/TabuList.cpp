#include "TabuList.h"

void TabuList::push(const Creature& creature)
{
	hashes.insert(creature.getHash());//ignoring max size for now
	
}

bool TabuList::contains(const Creature& creature) const
{
	return hashes.find(creature.getHash()) != hashes.end();
}
