#ifndef Scroll_hpp
#define Scroll_hpp

#include "Item.hpp"

class Scroll : public Item
{
public:
	Scroll(const sf::Texture* texture);
    virtual ~Scroll();

protected:
};

#endif /* Scroll_hpp */
