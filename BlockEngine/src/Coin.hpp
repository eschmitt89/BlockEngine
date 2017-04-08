#ifndef Coin_hpp
#define Coin_hpp

#include "Item.hpp"

class Coin : public Item
{
public:
	Coin(int value);
    virtual ~Coin();
    
	int GetValue();

protected:
	int value;
};

#endif /* Coin_hpp */
