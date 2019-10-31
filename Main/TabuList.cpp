#include "TabuList.h"

void TabuList::push(const Creature& creature)
{
	//always insert
	indexHashMap.insert({ indexEnd, creature.getHash() });
	indexEnd++;
	size++;
	//if exceeded max size remove first element
	if (size > maxSize)
	{
		indexHashMap.erase(indexBegin);
		indexBegin++;
		size--;
	}


}

bool TabuList::contains(const Creature& creature) const
{
	return indexHashMap.find(creature.getHash()) != indexHashMap.end();
}

TabuList::iterator TabuList::begin()
{
	return indexHashMap.begin();
}

TabuList::iterator TabuList::end()
{
	return indexHashMap.end();
}

const TabuList::const_iterator TabuList::begin() const
{
	return indexHashMap.begin();
}

const TabuList::const_iterator TabuList::end() const
{
	return indexHashMap.end();
}
