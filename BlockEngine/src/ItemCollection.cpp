#include "ItemCollection.hpp"

ItemCollection::ItemCollection(int capacity)
{
	this->capacity = capacity;
	this->availableSpace = capacity;

	for (int i = 0; i < capacity; i++)
	{
		items.push_back(nullptr);
	}
}

////////////////////////////////////////////////////////////////////////

ItemCollection::~ItemCollection()
{
    
}

////////////////////////////////////////////////////////////////////////

int ItemCollection::GetCapacity()
{
	return capacity;
}

////////////////////////////////////////////////////////////////////////

int ItemCollection::GetAvailableSpace()
{
	return availableSpace;
}

////////////////////////////////////////////////////////////////////////

void ItemCollection::Insert(Item * item)
{
	if (availableSpace > 0)
	{
		for (int i = 0; i < items.size(); i++)
		{
			if (!items[i])
			{
				items[i] = new Item(*item);
				availableSpace--;
				return;
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////

void ItemCollection::Remove(int index)
{
	if (index >= 0 && index < items.size())
	{
		delete items[index];
		items[index] = nullptr;
		availableSpace++;
	}
}

////////////////////////////////////////////////////////////////////////

vector<Item*>* ItemCollection::GetItems()
{
	return &items;
}

////////////////////////////////////////////////////////////////////////
