#ifndef ScrollGenerator_hpp
#define ScrollGenerator_hpp

#include "Scroll.hpp"

class ScrollGenerator
{
public:
	ScrollGenerator();
    virtual ~ScrollGenerator();

	Scroll* Generate(int level);

protected:

};

#endif /* ScrollGenerator_hpp */
