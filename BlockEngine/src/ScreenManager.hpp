#ifndef ScreenManager_hpp
#define ScreenManager_hpp

#include "AbstractScreen.hpp"
#include <vector>

class ScreenManager
{
public:
    ScreenManager();
    ~ScreenManager();
    void HandleInput(const sf::RenderWindow& window);
    void Update(float dt);
    void Draw(sf::RenderWindow& window);
    
    void AddScreen(AbstractScreen* screen);
    
private:
    vector<AbstractScreen*> screenStack;
    
};

#endif /* ScreenManager_hpp */
