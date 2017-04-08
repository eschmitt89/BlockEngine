#ifndef CoinGenerator_hpp
#define CoinGenerator_hpp

#define COIN_VALUE 1
#define MAX_COINS 50

#include "Coin.hpp"

class CoinGenerator
{
public:
	CoinGenerator();
    virtual ~CoinGenerator();

	Coin* Generate(int value);

protected:
};

#endif /* CoinGenerator_hpp */
