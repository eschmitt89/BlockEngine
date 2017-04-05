#ifndef GridRoom_hpp
#define GridRoom_hpp

#include <SFML/System.hpp>

using namespace std;

struct GridRoom
{
	GridRoom(sf::Vector2i position, sf::Vector2i size);
    ~GridRoom();

	sf::Vector2i position;
	sf::Vector2i size;
};

#endif /* GridRoom_hpp */
