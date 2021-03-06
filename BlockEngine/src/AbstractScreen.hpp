#ifndef AbstractScreen_hpp
#define AbstractScreen_hpp

#include "Updates.hpp"
#include "HandlesInput.hpp"
#include "Draws.hpp"

using namespace std;

class AbstractScreen
{
public:
    AbstractScreen();
    virtual ~AbstractScreen();
    virtual bool DoesHandleInput();
    virtual void HandleInput(const sf::RenderWindow& window);
    virtual bool DoesUpdate();
    virtual void Update(float dt);
    virtual bool DoesDraw();
    virtual void Draw(sf::RenderWindow& window);
    
private:
    
};

#endif /* AbstractScreen_hpp */
