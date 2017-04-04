//
//  ScrollGenerator.hpp
//  BlockEngine
//
//  Created by Eric Schmitt on 3/2/17.
//  Copyright © 2017 Eric Schmitt. All rights reserved.
//

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
