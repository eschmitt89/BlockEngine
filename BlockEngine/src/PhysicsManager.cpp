//
//  PhysicsObject.cpp
//  BlockEngine
//
//  Created by Eric Schmitt on 3/2/17.
//  Copyright © 2017 Eric Schmitt. All rights reserved.
//

#include "PhysicsManager.hpp"

PhysicsManager::PhysicsManager()
{
}

////////////////////////////////////////////////////////////////////////

PhysicsManager::~PhysicsManager()
{
	ClearPhyiscsObjects();
}

////////////////////////////////////////////////////////////////////////

void PhysicsManager::Update(float dt)
{
	for (int i = 0; i < physicsObjects.size(); i++)
	{
		physicsObjects[i]->Update(dt);
	}
}

////////////////////////////////////////////////////////////////////////

void PhysicsManager::Draw(sf::RenderWindow & window)
{
	for (int i = 0; i < physicsObjects.size(); i++)
	{
		physicsObjects[i]->Draw(window);
	}
}

////////////////////////////////////////////////////////////////////////

void PhysicsManager::AddPhysicsObject(PhysicsObject * physicsObject)
{
	physicsObjects.push_back(physicsObject);
}

////////////////////////////////////////////////////////////////////////

void PhysicsManager::ClearPhyiscsObjects()
{
	for (int i = 0; i < physicsObjects.size(); i++)
	{
		delete physicsObjects[i];
	}
	physicsObjects.clear();
}
