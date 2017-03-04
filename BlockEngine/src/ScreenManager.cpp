//
//  ScreenManager.cpp
//  BlockEngine
//
//  Created by Eric Schmitt on 3/2/17.
//  Copyright © 2017 Eric Schmitt. All rights reserved.
//

#include "ScreenManager.hpp"
#include <iostream>

ScreenManager::ScreenManager()
{
    
}

////////////////////////////////////////////////////////////////////////

ScreenManager::~ScreenManager()
{
    cout << "Deleting " << screenStack.size() << " screens" << endl;
    
    for (int i = 0; i < screenStack.size(); i++)
    {
        delete screenStack[i];
    }
    
    screenStack.clear();
}

////////////////////////////////////////////////////////////////////////

void ScreenManager::HandleInput(const sf::RenderWindow& window)
{
    if (screenStack.size() && screenStack[screenStack.size() - 1]->DoesHandleInput())
    {
        screenStack[screenStack.size() - 1]->HandleInput(window);
    }
}

////////////////////////////////////////////////////////////////////////

void ScreenManager::Update(float dt)
{
    if (screenStack.size() && screenStack[screenStack.size() - 1]->DoesUpdate())
    {
        screenStack[screenStack.size() - 1]->Update(dt);
    }
}

////////////////////////////////////////////////////////////////////////

void ScreenManager::Draw(sf::RenderWindow& window)
{
    if (screenStack.size() && screenStack[screenStack.size() - 1]->DoesDraw())
    {
        screenStack[screenStack.size() - 1]->Draw(window);
    }
}


////////////////////////////////////////////////////////////////////////

void ScreenManager::AddScreen(AbstractScreen *screen)
{
    screenStack.push_back(screen);
}
