//
//  Grid.hpp
//  BlockEngine
//
//  Created by Eric Schmitt on 3/2/17.
//  Copyright © 2017 Eric Schmitt. All rights reserved.
//

#ifndef Grid_hpp
#define Grid_hpp

#include <SFML/Graphics.hpp>
#include <vector>
#include "BlockType.hpp"

using namespace std;

class Grid
{
public:
    Grid(int rows, int columns, int blockWidth, int blockHeight);
    ~Grid();
    
    void Draw(sf::RenderWindow& window);
    
private:
    vector<vector<BlockType>> blocks;
	sf::Vector2i gridDimensions;
	sf::Vector2i blockSize;

	sf::Vector2f GetBlockPosition(int row, int column);
	sf::Vector2i GetBlockIndex(sf::Vector2f position);

};

#endif /* Grid_hpp */
