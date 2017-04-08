#ifndef ItemTooltip_hpp
#define ItemTooltip_hpp

#include "Armor.hpp"
#include "Weapon.hpp"
#include "Potion.hpp"
#include "Scroll.hpp"
#include "Gem.hpp"

using namespace std;

class ItemTooltip
{
public:
	ItemTooltip();
	~ItemTooltip();

	void Draw(Item* item, sf::Vector2f position);

private:
	sf::RectangleShape background;
	sf::Text text;
};

#endif /* ItemTooltip_hpp */