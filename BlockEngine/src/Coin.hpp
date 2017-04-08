#ifndef Coin_hpp
#define Coin_hpp

#include "PhysicsObject.hpp"

class Coin : public PhysicsObject
{
public:
	Coin(sf::Vector2f position, int value);
    virtual ~Coin();
	virtual ObjectType GetObjectType() { return ObjectType_Coin; }
    
	int GetValue();

protected:
	int value;
};

#endif /* Coin_hpp */
