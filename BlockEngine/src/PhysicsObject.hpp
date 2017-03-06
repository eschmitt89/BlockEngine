//
//  PhysicsObject.hpp
//  BlockEngine
//
//  Created by Eric Schmitt on 3/2/17.
//  Copyright © 2017 Eric Schmitt. All rights reserved.
//

#ifndef PhysicsObject_hpp
#define PhysicsObject_hpp

#include "Object.hpp"

class PhysicsObject : public Object
{
public:
	PhysicsObject(sf::Texture& texture, sf::Vector2f position, sf::Vector2f size);
    ~PhysicsObject();
    
private:

};

#endif /* PhysicsObject_hpp */
