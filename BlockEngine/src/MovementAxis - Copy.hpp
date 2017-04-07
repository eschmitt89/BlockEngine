//
//  Player.hpp
//  MovementAxis
//
//  Created by Eric Schmitt on 3/2/17.
//  Copyright © 2017 Eric Schmitt. All rights reserved.
//

#ifndef MovementAxis_hpp
#define MovementAxis_hpp

using namespace std;

enum XAxis
{
	XAxis_Left = -1,
	XAxis_None = 0,
	XAxis_Right = 1,
};

enum YAxis
{
	YAxis_Up = -1,
	YAxis_None = 0,
	YAxis_Down = 1,
};

struct MovementAxis
{
	MovementAxis();
    ~MovementAxis();

	XAxis x;
	YAxis y;
};

#endif /* MovementAxis_hpp */
