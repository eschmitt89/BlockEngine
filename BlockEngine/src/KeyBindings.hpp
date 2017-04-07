//
//  KeyBindings.hpp
//  BlockEngine
//
//  Created by Eric Schmitt on 3/2/17.
//  Copyright © 2017 Eric Schmitt. All rights reserved.
//

#ifndef KeyBindings_hpp
#define KeyBindings_hpp

#include <SFML/Window.hpp>

static class KeyBindings
{
public:
	static const sf::Keyboard::Key MoveUp = sf::Keyboard::Key::W;
	static const sf::Keyboard::Key MoveDown = sf::Keyboard::Key::S;
	static const sf::Keyboard::Key MoveLeft = sf::Keyboard::Key::A;
	static const sf::Keyboard::Key MoveRight = sf::Keyboard::Key::D;
	static const sf::Keyboard::Key Jump = sf::Keyboard::Key::Space;
	static const sf::Keyboard::Key Attack = sf::Keyboard::Key::F;
    
private:

};

#endif /* KeyBindings_hpp */
