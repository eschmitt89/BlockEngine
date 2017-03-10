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
	XAxisLeft = -1,
	XAxisNone = 0,
	XAxisRight = 1,
};

enum YAxis
{
	YAxisUp = -1,
	YAxisNone = 0,
	YAxisDown = 1,
};

class MovementAxis
{
public:
	MovementAxis();
    ~MovementAxis();

	XAxis x;
	YAxis y;

private:
	
};

#endif /* MovementAxis_hpp */
