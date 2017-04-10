#ifndef Gem_hpp
#define Gem_hpp

#include "Item.hpp"

class Gem : public Item
{
public:
	Gem(const sf::Texture* texture);
    virtual ~Gem();

protected:
};

#endif /* Gem_hpp */
