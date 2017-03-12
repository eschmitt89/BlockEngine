//
//  GridGenerator.hpp
//  BlockEngine
//
//  Created by Eric Schmitt on 3/2/17.
//  Copyright © 2017 Eric Schmitt. All rights reserved.
//

#ifndef GridGenerator_hpp
#define GridGenerator_hpp

#include "Grid.hpp"

using namespace std;

class GridGenerator
{
public:
	GridGenerator();
    ~GridGenerator();
    
	Grid* Generate();

private:
    

};

#endif /* GridGenerator_hpp */
