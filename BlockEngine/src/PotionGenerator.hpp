//
//  PotionGenerator.hpp
//  BlockEngine
//
//  Created by Eric Schmitt on 3/2/17.
//  Copyright © 2017 Eric Schmitt. All rights reserved.
//

#ifndef PotionGenerator_hpp
#define PotionGenerator_hpp

#include "Potion.hpp"

class PotionGenerator
{
public:
	PotionGenerator();
    virtual ~PotionGenerator();

	Potion* Generate(int level);

protected:

};

#endif /* PotionGenerator_hpp */
