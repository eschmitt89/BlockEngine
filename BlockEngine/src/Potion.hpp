#ifndef Potion_hpp
#define Potion_hpp

#include "Item.hpp"

class Potion : public Item
{
public:
	Potion(const sf::Texture* texture);
    virtual ~Potion();

protected:
};

#endif /* Potion_hpp */
