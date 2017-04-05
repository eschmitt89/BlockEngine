//
//  Gem.hpp
//  BlockEngine
//
//  Created by Eric Schmitt on 3/2/17.
//  Copyright © 2017 Eric Schmitt. All rights reserved.
//

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
