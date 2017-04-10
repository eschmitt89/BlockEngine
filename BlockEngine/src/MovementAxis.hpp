#ifndef MovementAxis_hpp
#define MovementAxis_hpp

#include "XAxis.hpp"
#include "YAxis.hpp"

using namespace std;

struct MovementAxis
{
	MovementAxis();
    ~MovementAxis();

	XAxis x;
	YAxis y;
};

#endif /* MovementAxis_hpp */
