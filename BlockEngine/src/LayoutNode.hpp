//
//  LayoutNode.hpp
//  BlockEngine
//
//  Created by Eric Schmitt on 3/2/17.
//  Copyright © 2017 Eric Schmitt. All rights reserved.
//

#ifndef LayoutNode_hpp
#define LayoutNode_hpp

using namespace std;

class LayoutNode
{
public:
	LayoutNode();
	~LayoutNode();

	bool Visited;

	bool CorridorUp;
	bool CorridorDown;
	bool CorridorLeft;
	bool CorridorRight;

	bool UpInvalid;
	bool DownInvalid;
	bool LeftInvalid;
	bool RightInvalid;
};

#endif /* LayoutNode_hpp */
