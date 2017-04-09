#ifndef ItemCollection_hpp
#define ItemCollection_hpp

#include "Item.hpp"

class ItemCollection
{
public:
	ItemCollection(int capacity);
    ~ItemCollection();

	int GetCapacity();
	int GetAvailableSpace();
	void Insert(Item * item);
	void Remove(int index);

	vector<Item*>* GetItems();

private:
	int capacity;
	int availableSpace;
	vector<Item*> items;
};

#endif /* ItemCollection_hpp */
