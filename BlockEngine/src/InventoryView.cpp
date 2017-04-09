#include "InventoryView.hpp"

InventoryView::InventoryView(ItemCollection* itemCollection, sf::Vector2f position, sf::Vector2f iconDimensions, sf::Vector2f iconPadding)
	:Clickable(position, sf::Vector2f())
{
	this->itemCollection = itemCollection;
	this->iconDimensions = iconDimensions;
	this->iconPadding = iconPadding;

	itemCollectionDimensions = sf::Vector2i(sqrt(itemCollection->GetCapacity()), ceil(itemCollection->GetCapacity() / sqrt(itemCollection->GetCapacity())));

	hitBox.setFillColor(sf::Color(64, 64, 64, 255));
	hitBox.setSize(sf::Vector2f(itemCollectionDimensions.x * (iconDimensions.x + iconPadding.x) + iconPadding.x, itemCollectionDimensions.y * (iconDimensions.y + iconPadding.y) + iconPadding.y));
}

////////////////////////////////////////////////////////////////////////

InventoryView::~InventoryView()
{

}

////////////////////////////////////////////////////////////////////////

void InventoryView::Draw(sf::RenderWindow & window)
{
	Clickable::Draw(window);

	vector<Item*>* items = itemCollection->GetItems();

	int currentItem = 0;

	for (int y = 0; y < itemCollectionDimensions.y; y++)
	{
		for (int x = 0; x < itemCollectionDimensions.x; x++)
		{
			if (currentItem >= (*items).size())
			{
				return;
			}

			if ((*items)[currentItem])
			{
				ItemObject item = ItemObject((*items)[currentItem], IndexToPosition(x, y), iconDimensions);
				item.Draw(window);
			}

			currentItem++;
		}
	}
}

////////////////////////////////////////////////////////////////////////

void InventoryView::LeftClick(sf::Vector2f mousePosition)
{
	int index = PositionToIndex(mousePosition);
	itemCollection->Remove(index);
}

////////////////////////////////////////////////////////////////////////

void InventoryView::RightClick()
{
}

////////////////////////////////////////////////////////////////////////

void InventoryView::MiddleClick()
{
}

////////////////////////////////////////////////////////////////////////

sf::Vector2f InventoryView::IndexToPosition(int column, int row)
{
	return hitBox.getPosition() + iconPadding + sf::Vector2f(column * (iconDimensions.x + iconPadding.x), row * (iconDimensions.y + iconPadding.y));
}

////////////////////////////////////////////////////////////////////////

int InventoryView::PositionToIndex(sf::Vector2f position)
{
	sf::Vector2f relativePosition = position - hitBox.getPosition();

	int column = relativePosition.x / (iconDimensions.x + iconPadding.x);
	int row = relativePosition.y / (iconDimensions.y + iconPadding.y);

	return column + (row * itemCollectionDimensions.x);
}

////////////////////////////////////////////////////////////////////////
