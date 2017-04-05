#ifndef GridNode_hpp
#define GridNode_hpp

#include <SFML/System.hpp>

using namespace std;

struct GridNode
{
	GridNode(int x, int y, sf::Vector2i dimensions);
    ~GridNode();

	sf::Vector2i index;

	bool visited;

	bool leftInvalid;
	bool rightInvalid;
	bool upInvalid;
	bool downInvalid;

	GridNode* leftNode;
	GridNode* rightNode;
	GridNode* upNode;
	GridNode* downNode;

	bool AllDirectionsInvalid();
};

#endif /* GridNode_hpp */
