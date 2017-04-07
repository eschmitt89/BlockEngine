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

int ItemCollection::GetAvailableSpace()
{
	return availableSpace;
}

////////////////////////////////////////////////////////////////////////

void ItemCollection::InsertItem(Item * item)
{
	if (availableSpace > 0)
	{
		for (int i = 0; i < items.size(); i++)
		{
			if (!items[i])
			{
				items[i] = item;
				availableSpace--;
				return;
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////
