#ifndef GoldCoin_hpp
#define GoldCoin_hpp

#include "PhysicsObject.hpp"

class GoldCoin : public PhysicsObject
{
public:
	GoldCoin(sf::Vector2f position, int value);
    virtual ~GoldCoin();
	virtual ObjectType GetObjectType() { return ObjectType_GoldCoin; }
    
	int GetValue();

protected:
	int value;
};

#endif /* GoldCoin_hpp */
