//
//  PhysicsObject.cpp
//  BlockEngine
//
//  Created by Eric Schmitt on 3/2/17.
//  Copyright © 2017 Eric Schmitt. All rights reserved.
//

#include "PhysicsManager.hpp"

PhysicsManager::PhysicsManager(Grid* grid)
{
	this->grid = grid;
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
		DetectAndResolveGridCollisions(physicsObjects[i]);
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

void PhysicsManager::DetectAndResolveGridCollisions(PhysicsObject * physicsObject)
{
	Vector4i collidedBlocks = grid->GetBlockIndicies(physicsObject->GetPosition(), physicsObject->GetSize());

	for (int column = collidedBlocks.x1; column <= collidedBlocks.x2; column++)
	{
		for (int row = collidedBlocks.y1; row <= collidedBlocks.y2; row++)
		{
			if (grid->IsValidNonEmptyBlockIndex(column, row))
			{
				if (physicsObject->GetGlobalBounds().intersects(grid->GetBlockGlobalBounds(column, row)))
				{
					// collision detected
				}
			}
		}
	}
}
