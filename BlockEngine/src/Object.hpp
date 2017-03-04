//
//  Object.hpp
//  BlockEngine
//
//  Created by Eric Schmitt on 3/2/17.
//  Copyright © 2017 Eric Schmitt. All rights reserved.
//

#ifndef Object_hpp
#define Object_hpp

#include <SFML/Graphics.hpp>

class Object
{
public:
	Object(sf::Vector2f position);
    ~Object();
    
private:
	sf::Sprite sprite;
};

#endif /* Object_hpp */
