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
