#ifndef Item_hpp
#define Item_hpp

#include "SFML/Window.hpp"
#include "ItemType.hpp"
#include "Utilities.hpp"

class Item
{
public:
	Item(ItemType itemType, const sf::Texture* texture);
	Item(const Item& item);
    virtual ~Item();

	ItemType GetItemType();
	const sf::Texture* GetTexture();

protected:
	ItemType itemType;
	const sf::Texture* texture;
};

#endif /* Item_hpp */
