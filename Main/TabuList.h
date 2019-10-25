#pragma once

#include "Creature.h"

class TabuEntry
{
public:
	friend class TabuList;
private:
	TabuEntry(const Creature& creature);
	TabuEntry(const std::vector<size_t>& cities);
	std::vector<size_t> cities;

};

class TabuList
{
public:
	void push(const Creature& creature);
	bool contains(const Creature&  creature);
private:
	std::vector<TabuEntry> entries;//set using fitness?
	size_t maxSize;
};