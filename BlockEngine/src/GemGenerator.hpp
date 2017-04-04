//
//  GemGenerator.hpp
//  BlockEngine
//
//  Created by Eric Schmitt on 3/2/17.
//  Copyright © 2017 Eric Schmitt. All rights reserved.
//

#ifndef GemGenerator_hpp
#define GemGenerator_hpp

#include "Gem.hpp"

class GemGenerator
{
public:
	GemGenerator();
    virtual ~GemGenerator();

	Gem* Generate(int level);

protected:

};

#endif /* GemGenerator_hpp */
