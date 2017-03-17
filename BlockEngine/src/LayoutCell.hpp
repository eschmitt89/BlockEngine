//
//  LayoutCell.hpp
//  BlockEngine
//
//  Created by Eric Schmitt on 3/2/17.
//  Copyright © 2017 Eric Schmitt. All rights reserved.
//

#ifndef LayoutCell_hpp
#define LayoutCell_hpp

using namespace std;

class LayoutCell
{
public:
	LayoutCell();
	~LayoutCell();

	bool Visited;

	bool CorridorUp;
	bool CorridorDown;
	bool CorridorLeft;
	bool CorridorRight;
};

#endif /* LayoutCell_hpp */
