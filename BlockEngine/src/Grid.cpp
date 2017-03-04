//
//  Grid.cpp
//  BlockEngine
//
//  Created by Eric Schmitt on 3/2/17.
//  Copyright © 2017 Eric Schmitt. All rights reserved.
//

#include "Grid.hpp"


Grid::Grid(int rows, int columns, int blockWidth, int blockHeight)
{
    for (int column = 0; column < columns; column++)
    {
        vector<BlockType> blockColumn;
        
        for (int row = 0; row < rows; row++)
        {
            blockColumn.push_back(BlockType::Solid);
        }
        
        blocks.push_back(blockColumn);
    }
}

////////////////////////////////////////////////////////////////////////

Grid::~Grid()
{
    
}

////////////////////////////////////////////////////////////////////////

void Grid::Draw(sf::RenderWindow &window)
{
    sf::RectangleShape block;
    block.setSize(sf::Vector2f(20,20));
    
    for (int column = 0; column < blocks.size(); column++)
    {
        for (int row = 0; row < blocks[column].size(); row++)
        {
            blockColumn.push_back(BlockType::Solid);
        }
        
        blocks.push_back(blockColumn);
    }
}
