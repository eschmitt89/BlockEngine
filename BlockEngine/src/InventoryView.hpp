#ifndef InventoryView_hpp
#define InventoryView_hpp

#include "ItemCollection.hpp"
#include "ItemObject.hpp"
#include "Clickable.hpp"

using namespace std;

class InventoryView : public Clickable
{
public:
	InventoryView(ItemCollection* itemCollection, sf::Vector2f position, sf::Vector2f iconDimensions, sf::Vector2f iconPadding);
	~InventoryView();

	void Draw(sf::RenderWindow& window);

protected:
	void LeftClick(sf::Vector2f mousePosition);
	void RightClick();
	void MiddleClick();

private:
	ItemCollection* itemCollection;
	sf::Vector2i itemCollectionDimensions;
	sf::Vector2f iconDimensions;
	sf::Vector2f iconPadding;

	sf::Vector2f IndexToPosition(int column, int row);
	int PositionToIndex(sf::Vector2f position);
};

#endif /* InventoryView_hpp */