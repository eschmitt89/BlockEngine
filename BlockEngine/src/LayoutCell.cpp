//
//  LayoutCell.cpp
//  BlockEngine
//
//  Created by Eric Schmitt on 3/2/17.
//  Copyright © 2017 Eric Schmitt. All rights reserved.
//

#include "LayoutCell.hpp"

LayoutCell::LayoutCell()
{
	Visited = false;
	CorridorUp = false;
	CorridorDown = false;
	CorridorLeft = false;
	CorridorRight = false;
}

////////////////////////////////////////////////////////////////////////

LayoutCell::~LayoutCell()
{

}
