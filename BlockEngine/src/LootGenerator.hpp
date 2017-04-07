#ifndef LootGenerator_hpp
#define LootGenerator_hpp

#include "ItemGenerator.hpp"
#include "GoldCoin.hpp"

class LootGenerator
{
public:
	LootGenerator();
    virtual ~LootGenerator();

	

private:
	ItemGenerator itemGenerator;
};

#endif /* LootGenerator_hpp */
