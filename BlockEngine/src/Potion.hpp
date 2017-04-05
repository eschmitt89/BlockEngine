//
//  Potion.hpp
//  BlockEngine
//
//  Created by Eric Schmitt on 3/2/17.
//  Copyright © 2017 Eric Schmitt. All rights reserved.
//

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
